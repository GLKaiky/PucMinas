from collections import defaultdict

class Grafo:
    def __init__(self):
        self.grafo = defaultdict(list)

    def adicionar_aresta(self, u, v):
        self.grafo[u].append(v)
        self.grafo[v].append(u)  # Grafo não-direcionado

    def buscar_ciclos(self):
        visitado = set()
        ciclos = []

        def dfs(atual, inicio, caminho):
            if atual in visitado and atual == inicio and len(caminho) > 2:
                ciclo = caminho[:]
                ciclo.append(inicio)  # Fechar o ciclo
                ciclos.append(ciclo)
                return
            
            if atual in visitado:
                return

            visitado.add(atual)
            caminho.append(atual)

            for vizinho in self.grafo[atual]:
                if len(caminho) > 1 and vizinho == caminho[-2]:
                    continue  # Evitar voltar para o nó anterior
                dfs(vizinho, inicio, caminho[:])

            visitado.remove(atual)

        for no in self.grafo:
            dfs(no, no, [])

        # Remover duplicatas considerando ciclos rotacionados iguais
        ciclos_unicos = []
        for ciclo in ciclos:
            ciclo_rotacionado = min([ciclo[i:] + ciclo[:i] for i in range(len(ciclo))])
            if ciclo_rotacionado not in ciclos_unicos:
                ciclos_unicos.append(ciclo_rotacionado)

        return ciclos_unicos

# Criando o grafo com base na imagem
grafo = Grafo()
arestas = [('A', 'B'), ('A', 'E'), ('B', 'D'), ('B', 'C'), ('B', 'E'),
           ('C', 'E'), ('C', 'F'), ('D', 'F'), ('C', 'D')]

for u, v in arestas:
    grafo.adicionar_aresta(u, v)

# Buscando e imprimindo ciclos
ciclos = grafo.buscar_ciclos()
for ciclo in ciclos:
    print(" → ".join(ciclo))

# Imprimindo a quantidade de ciclos encontrados
print(f"\nQuantidade de ciclos encontrados: {len(ciclos)}")
