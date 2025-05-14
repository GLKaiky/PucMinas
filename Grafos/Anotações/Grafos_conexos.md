
---

# **Subgrafos**

## **Componentes Conexos**

Em um grafo não direcionado, um **componente conexo** é um subconjunto de vértices e arestas em que **todos os vértices estão conectados entre si** por algum caminho, e **não há conexão com vértices fora desse subconjunto**.

### **Definição Formal**

Um **componente conexo** de um grafo \( G = (V, E) \) é um **subgrafo maximal conexo**, ou seja, um subgrafo no qual:

- Para qualquer par de vértices \( u \) e \( v \) dentro do componente, existe um **caminho** ligando \( u \) a \( v \).
- Se adicionarmos qualquer outro vértice fora do componente, ele **deixaria de ser conexo**.

### **Propriedades**

1. **Cada vértice pertence a exatamente um componente conexo**.
2. Se um grafo for totalmente conexo (todos os vértices podem ser alcançados a partir de qualquer outro), ele tem **apenas um componente conexo**.
3. Se o grafo for **desconexo**, ele pode ser dividido em vários componentes conexos **independentes**.

### **Exemplo**

Considere o seguinte grafo:

```
A -- B    D -- E  
     |  
     C  
```

- Aqui temos **dois componentes conexos**:
  1. \( \{A, B, C\} \) → Todos os vértices estão conectados.
  2. \( \{D, E\} \) → Esses vértices formam outro componente separado.

### **Tamanho de um Grafo**

O tamanho de um grafo \( G \) é dado por:

\[
|G| = |V| + |E|
\]

Onde:

- \( |V| \) é o número de **vértices**.
- \( |E| \) é o número de **arestas**.

### **Subgrafos e Relação com o Grafo Original**

Se \( G' \) é um subgrafo de \( G \), então seus conjuntos de vértices e arestas devem ser subconjuntos dos de \( G \):

\[
V' \subseteq V, \quad E' \subseteq E
\]

Ou seja, o subgrafo contém apenas vértices e arestas que já pertencem ao grafo original.

---

## **Grau dos Vértices**

- Se todos os vértices possuem o mesmo grau, ele é chamado de grafo regular.

### **Grafo Regular**

---

## **Menor Número de Arestas Possível em um Grafo**

Para que um grafo seja **conexo**, cada componente conexo deve ter **pelo menos** o número mínimo de arestas necessário para conectar todos os seus vértices.

A fórmula para o **número mínimo de arestas** em um grafo com **\( V \) vértices** e **\( C \) componentes conexos** é:

\[
|E| = |V| - |C|
\]

### **Explicação:**

- Em um **grafo conexo**, para conectar \( n \) vértices no **formato de uma árvore** (estrutura mais simples sem ciclos), é necessário exatamente **\( n - 1 \) arestas**.
- Se tivermos **\( C \) componentes conexos**, cada um precisa de **\( |V_i| - 1 \) arestas** (sendo \( |V_i| \) o número de vértices no \( i \)-ésimo componente).
- Somando para todos os componentes, o número total mínimo de arestas no grafo é **\( |V| - |C| \)**.

### **Exemplo:**

Suponha um grafo com **7 vértices** e **3 componentes conexos**. O número mínimo de arestas será:

\[
|E| = 7 - 3 = 4
\]

---

## **Exercício**

- Determinar o número de componentes conexos de um grafo não direcionado. (Maior quantidade possivel de arestas se há |C| componentes)

---
