import tensorflow as tf
from tensorflow.keras.preprocessing.text import Tokenizer
from tensorflow.keras.preprocessing.sequence import pad_sequences
import numpy as np

# Frases de exemplo com dependência de longo prazo
text_data = [
    "O gato que estava no telhado, pulou para a árvore e depois de um tempo, miou.",
    "O cachorro que correu pelo parque, brincou com a bola e finalmente, latia.",
    "A criança que jogava no jardim, encontrou um brinquedo e começou a chorar.",
    "O gato que comeu a ração, bebeu água e depois de um cochilo, miou.",
    "O cachorro que farejou o chão, encontrou um osso e em seguida, latia.",
    "A criança que desenhava na parede, foi repreendida e por fim, chorar."
]

# 1. Tokenização e Vocabulário
tokenizer = Tokenizer(num_words=None, oov_token="<unk>") # <unk> para palavras fora do vocabulário
tokenizer.fit_on_texts(text_data)
word_index = tokenizer.word_index
vocab_size = len(word_index) + 1 # +1 para o token <unk>

print(f"Tamanho do vocabulário: {vocab_size}")
print(f"Mapeamento de palavras: {word_index}")

# 2. Criar sequências de treinamento (entrada e saída)
input_sequences = []
for line in text_data:
    token_list = tokenizer.texts_to_sequences([line])[0]
    for i in range(1, len(token_list)):
        n_gram_sequence = token_list[:i+1]
        input_sequences.append(n_gram_sequence)

# 3. Padding das sequências (para terem o mesmo comprimento)
max_sequence_len = max([len(x) for x in input_sequences])
padded_sequences = np.array(pad_sequences(input_sequences, maxlen=max_sequence_len, padding='pre'))

# 4. Separar entrada (X) e saída (y)
X = padded_sequences[:, :-1] # Todas as palavras exceto a última
y = padded_sequences[:, -1]  # A última palavra (a ser prevista)

# 5. One-hot encode a saída (para classificação multiclasse)
y = tf.keras.utils.to_categorical(y, num_classes=vocab_size)

print(f"\nExemplo de X (entrada):\n{X[0]}")
print(f"Exemplo de y (saída one-hot):\n{y[0]}")
print(f"Comprimento máximo da sequência: {max_sequence_len}")

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Embedding, LSTM, Dense

# Dimensões
embedding_dim = 100 # Tamanho do vetor de embedding para cada palavra

# Modelo LSTM
model = Sequential([
    Embedding(vocab_size, embedding_dim, input_length=max_sequence_len-1),
    LSTM(150, return_sequences=False), # 150 unidades LSTM, não retorna sequência completa
    Dense(vocab_size, activation='softmax') # Camada de saída com softmax para probabilidades
])

model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])

model.summary()

# Treinamento
history = model.fit(X, y, epochs=100, verbose=1) # 100 épocas devem ser suficientes para este dataset pequeno

def predict_next_word(model, tokenizer, text_sequence, max_len):
    token_list = tokenizer.texts_to_sequences([text_sequence])[0]
    padded_token_list = pad_sequences([token_list], maxlen=max_len-1, padding='pre')
    
    predicted_probabilities = model.predict(padded_token_list, verbose=0)[0]
    predicted_word_index = np.argmax(predicted_probabilities)
    
    # Mapear índice de volta para palavra
    for word, index in tokenizer.word_index.items():
        if index == predicted_word_index:
            return word
    return "<unk>" # Caso não encontre (improvável se o vocabulário for completo)

# Frases para teste
test_phrases = [
    "O gato que estava no telhado, pulou para a árvore e depois de um tempo,",
    "O cachorro que correu pelo parque, brincou com a bola e finalmente,",
    "A criança que jogava no jardim, encontrou um brinquedo e começou a",
    "O gato que comeu a ração, bebeu água e depois de um cochilo,",
    "O cachorro que farejou o chão, encontrou um osso e em seguida,",
    "A criança que desenhava na parede, foi repreendida e por fim,"
]

print("\n--- Previsões ---")
for phrase in test_phrases:
    predicted_word = predict_next_word(model, tokenizer, phrase, max_sequence_len)
    print(f"Frase: '{phrase}' -> Próxima palavra prevista: '{predicted_word}'")

# Exemplo de uma frase com uma dependência longa e uma palavra-chave no meio
# (Se o modelo for bem treinado, ele deve ignorar o ruído e focar no sujeito)
new_long_phrase = "O gato, que estava dormindo profundamente, e que sonhava com peixes, agora acordou e vai ____"
predicted_word_long = predict_next_word(model, tokenizer, new_long_phrase, max_sequence_len)
print(f"Frase Longa: '{new_long_phrase}' -> Próxima palavra prevista: '{predicted_word_long}'")