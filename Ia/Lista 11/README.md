# Análise do Dataset Titanic: Um Pipeline Completo de IA

Este projeto Jupyter Notebook realiza uma análise completa do famoso dataset Titanic, aplicando diversas técnicas de Inteligência Artificial para pré-processamento, modelagem e extração de insights. O objetivo principal é prever a sobrevivência dos passageiros e identificar padrões interessantes nos dados.

## Estrutura do Notebook

O notebook é dividido nas seguintes partes principais:

1.  **Parte 1: Pré-processamento da Base de Dados**
    * Instalação e importação das bibliotecas necessárias.
    * Criação de funções para importação e visualização inicial dos dados.
    * **Análise Exploratória Inicial:**
        * Visualização das informações do DataFrame (`.info()`), primeiras e últimas linhas (`.head()`, `.tail()`).
        * Estatísticas descritivas (`.describe()`).
        * Identificação e contagem de valores ausentes (`.isnull().sum()`).
    * **Tratamento de Dados Ausentes:**
        * Preenchimento da coluna `Age` com a mediana.
        * Preenchimento da coluna `Embarked` com a moda.
    * **Engenharia de Atributos:**
        * Criação da feature `FamilySize` (SibSp + Parch + 1).
        * Criação da feature `HasCabin` (indicando se a informação da cabine existe).
        * Remoção das colunas originais `SibSp`, `Parch`, e `Cabin`.
    * **Transformação de Variáveis Categóricas:**
        * Mapeamento da coluna `Sex` para valores numéricos (0 para male, 1 para female).
        * Aplicação de One-Hot Encoding na coluna `Embarked`.

2.  **Parte 2: Modelagem com Algoritmos de Classificação Supervisionada**
    * Preparação dos dados (seleção de features `X` e alvo `y`).
    * Remoção das colunas `Name` e `Ticket` para modelagem.
    * Divisão dos dados em conjuntos de treino e teste (`train_test_split`).
    * **Algoritmos Utilizados:**
        * **Random Forest Classifier:**
            * Treinamento do modelo (`n_estimators=100`, `random_state=42`, `class_weight='balanced'`).
            * Avaliação com Acurácia, Precisão, Recall, F1-Score e Relatório de Classificação.
        * **Naive Bayes (GaussianNB):**
            * Treinamento do modelo.
            * Avaliação com Precisão, Recall, F1-Score e Relatório de Classificação.

3.  **Parte 3: Modelagem com Algoritmos de Agrupamento**
    * **K-Means Clustering:**
        * Seleção de features para clusterização: `['Sex', 'Age', 'FamilySize', 'HasCabin', 'Embarked_Q', 'Embarked_S']`.
        * Padronização dos dados (`StandardScaler`).
        * Aplicação do K-Means com `k=4` clusters.
        * Adição dos rótulos dos clusters ao DataFrame de análise.
        * **Visualização dos Clusters:**
            * Redução de dimensionalidade com PCA (`n_components=2`).
            * Plotagem dos clusters usando `seaborn.scatterplot`.
        * **Interpretação dos Clusters:**
            * Análise das médias das features por cluster.
            * Análise da taxa de sobrevivência por cluster.
            * Análise da distribuição de sexo (original) por cluster.
            * Análise da distribuição de classe (original) por cluster.

4.  **Parte 4: Extração de Regras de Associação**
    * **Apriori Algorithm:**
        * **Preparação dos Dados:**
            * Discretização das colunas `Age` e `Fare` em grupos.
            * Criação de colunas de itens para `Pclass`, `Sex`, `Survived_Rule`, `FamilySize_Group`.
            * Remoção de NaNs e aplicação de `pd.get_dummies` para criar a matriz transacional.
        * **Geração de Regras:**
            * Encontrar itemsets frequentes com `apriori` (`min_support=0.01`).
            * Gerar regras de associação com `association_rules` (`metric="lift"`, `min_threshold=1.2`).
        * Impressão das top regras para interpretação (antecedents, consequents, support, confidence, lift).

## Bibliotecas Utilizadas

* `pandas`
* `os`
* `scikit-learn` (sklearn)
* `matplotlib`
* `seaborn`
* `mlxtend`

## Como Executar

1.  Certifique-se de ter todas as bibliotecas listadas acima instaladas no seu ambiente Python. A primeira célula do notebook contém os comandos `!pip install` necessários.
2.  Coloque o arquivo `train.csv` (dataset do Titanic) em uma subpasta chamada `titanic` no mesmo diretório do notebook, ou ajuste a função `importData` conforme necessário.
3.  Execute as células do notebook sequencialmente.

## Resultados e Observações

* **Classificação:** O modelo Random Forest apresentou uma acurácia de aproximadamente 85.47% e um F1-Score (para sobreviventes) de 0.8143. O Naive Bayes apresentou um F1-Score de 0.7742 para sobreviventes.
* **Clusterização:** Foram identificados 4 clusters de passageiros com perfis distintos em termos de características demográficas, socioeconômicas, familiares e, crucialmente, diferentes taxas de sobrevivência.
* **Regras de Associação:** Foram extraídas regras que indicam associações entre características dos passageiros e seu desfecho (sobrevivência ou não), com métricas de suporte, confiança e lift para avaliar a relevância dessas regras.

Este notebook serve como um exemplo prático de um pipeline de IA, desde a exploração e preparação dos dados até a aplicação e avaliação de diferentes tipos de algoritmos de aprendizado de máquina.