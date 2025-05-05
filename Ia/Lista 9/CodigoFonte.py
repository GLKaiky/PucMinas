import heapq
from collections import deque
import time

def encontrar_vazio(estado):
    """Encontra a posição (linha, coluna) do espaço vazio (0) no estado."""
    for i in range(len(estado)):
        for j in range(len(estado[i])):
            if estado[i][j] == 0:
                return i, j
    return None

def obter_vizinhos(estado):
    """Gera todos os estados válidos que podem ser alcançados a partir do estado atual."""
    linha_vazio, coluna_vazio = encontrar_vazio(estado)
    tamanho = len(estado)
    vizinhos = []
    movimentos = [(0, 1), (0, -1), (1, 0), (-1, 0)]  # Direita, Esquerda, Baixo, Cima

    for dl, dc in movimentos:
        nova_linha, nova_coluna = linha_vazio + dl, coluna_vazio + dc
        if 0 <= nova_linha < tamanho and 0 <= nova_coluna < tamanho:
            novo_estado = [list(linha) for linha in estado]
            novo_estado[linha_vazio][coluna_vazio], novo_estado[nova_linha][nova_coluna] = \
                novo_estado[nova_linha][nova_coluna], novo_estado[linha_vazio][coluna_vazio]
            vizinhos.append(tuple(tuple(linha) for linha in novo_estado))
    return vizinhos

def eh_objetivo(estado, estado_objetivo):
    """Verifica se o estado atual é igual ao estado objetivo."""
    return estado == estado_objetivo

def bfs(estado_inicial_tuple, estado_objetivo_tuple):
    """Implementa o algoritmo de Busca em Largura."""
    fila = deque([(estado_inicial_tuple, [])])
    visitados = {estado_inicial_tuple}
    nos_visitados = 0

    while fila:
        estado_atual_tuple, caminho = fila.popleft()
        nos_visitados += 1

        if estado_atual_tuple == estado_objetivo_tuple:
            return caminho, nos_visitados

        for vizinho_tuple in obter_vizinhos(estado_atual_tuple):
            if vizinho_tuple not in visitados:
                visitados.add(vizinho_tuple)
                novo_caminho = caminho + [vizinho_tuple]
                fila.append((vizinho_tuple, novo_caminho))

    return None, nos_visitados

def dfs(estado_inicial_tuple, estado_objetivo_tuple, limite_profundidade):
    """Implementa o algoritmo de Busca em Profundidade com limite de profundidade."""
    pilha = [(estado_inicial_tuple, [])]
    visitados = {estado_inicial_tuple}
    nos_visitados = 0

    while pilha:
        estado_atual_tuple, caminho = pilha.pop()
        nos_visitados += 1

        if estado_atual_tuple == estado_objetivo_tuple:
            return caminho, nos_visitados

        if len(caminho) < limite_profundidade:
            for vizinho_tuple in obter_vizinhos(estado_atual_tuple):
                if vizinho_tuple not in visitados:
                    visitados.add(vizinho_tuple)
                    novo_caminho = caminho + [vizinho_tuple]
                    pilha.append((vizinho_tuple, novo_caminho))

    return None, nos_visitados

def distancia_manhattan(estado_tuple, estado_objetivo_tuple):
    """Calcula a Distância de Manhattan entre dois estados."""
    tamanho = len(estado_tuple)
    distancia = 0
    posicoes_objetivo = {}
    for i in range(tamanho):
        for j in range(tamanho):
            posicoes_objetivo[estado_objetivo_tuple[i][j]] = (i, j)

    for i in range(tamanho):
        for j in range(tamanho):
            peca = estado_tuple[i][j]
            if peca != 0:
                linha_objetivo, coluna_objetivo = posicoes_objetivo[peca]
                distancia += abs(i - linha_objetivo) + abs(j - coluna_objetivo)
    return distancia

def pecas_fora_lugar(estado_tuple, estado_objetivo_tuple):
    """Calcula o Número de Peças Fora do Lugar entre dois estados."""
    tamanho = len(estado_tuple)
    fora_do_lugar = 0
    for i in range(tamanho):
        for j in range(tamanho):
            if estado_tuple[i][j] != 0 and estado_tuple[i][j] != estado_objetivo_tuple[i][j]:
                fora_do_lugar += 1
    return fora_do_lugar

def a_estrela(estado_inicial_tuple, estado_objetivo_tuple, heuristica):
    """Implementa o algoritmo A*."""
    fila_prioridade = [(heuristica(estado_inicial_tuple, estado_objetivo_tuple), 0, estado_inicial_tuple, [])]
    visitados = {estado_inicial_tuple}
    nos_visitados = 0

    while fila_prioridade:
        prioridade, custo, estado_atual_tuple, caminho = heapq.heappop(fila_prioridade)
        nos_visitados += 1

        if estado_atual_tuple == estado_objetivo_tuple:
            return caminho, nos_visitados

        for vizinho_tuple in obter_vizinhos(estado_atual_tuple):
            if vizinho_tuple not in visitados:
                visitados.add(vizinho_tuple)
                novo_custo = custo + 1
                prioridade_vizinho = novo_custo + heuristica(vizinho_tuple, estado_objetivo_tuple)
                novo_caminho = caminho + [vizinho_tuple]
                heapq.heappush(fila_prioridade, (prioridade_vizinho, novo_custo, vizinho_tuple, novo_caminho))

    return None, nos_visitados

if __name__ == '__main__':
    estado_inicial = [[2, 8, 3], [1, 6, 4], [7, 0, 5]]
    estado_objetivo = [[1, 2, 3], [8, 0, 4], [7, 6, 5]]

    estado_inicial_tuple = tuple(tuple(linha) for linha in estado_inicial)
    estado_objetivo_tuple = tuple(tuple(linha) for linha in estado_objetivo)

    print("Resolvendo o 8-Puzzle:")
    print(f"Estado Inicial: {estado_inicial}")
    print(f"Estado Objetivo: {estado_objetivo}\n")

    # Busca em Largura
    inicio_tempo = time.time()
    solucao_bfs, nos_bfs = bfs(estado_inicial_tuple, estado_objetivo_tuple)
    fim_tempo = time.time()
    tempo_bfs = fim_tempo - inicio_tempo

    print("Busca em Largura (BFS):")
    if solucao_bfs:
        print(f"  Solução encontrada em {len(solucao_bfs)} movimentos.")
        print(f"  Número de nós visitados: {nos_bfs}")
        print(f"  Tempo de execução: {tempo_bfs:.3f} segundos\n")
    else:
        print("  Solução não encontrada.\n")

    # Busca em Profundidade (com limite)
    limite_dfs = 30
    inicio_tempo = time.time()
    solucao_dfs, nos_dfs = dfs(estado_inicial_tuple, estado_objetivo_tuple, limite_dfs)
    fim_tempo = time.time()
    tempo_dfs = fim_tempo - inicio_tempo

    print(f"Busca em Profundidade (DFS) com limite de {limite_dfs}:")
    if solucao_dfs:
        print(f"  Solução encontrada em {len(solucao_dfs)} movimentos.")
        print(f"  Número de nós visitados: {nos_dfs}")
        print(f"  Tempo de execução: {tempo_dfs:.3f} segundos\n")
    else:
        print("  Solução não encontrada dentro do limite de profundidade.\n")

    # Busca A* com Distância de Manhattan
    inicio_tempo = time.time()
    solucao_astar_manhattan, nos_astar_manhattan = a_estrela(
        estado_inicial_tuple, estado_objetivo_tuple, distancia_manhattan
    )
    fim_tempo = time.time()
    tempo_astar_manhattan = fim_tempo - inicio_tempo

    print("Busca A* com Distância de Manhattan:")
    if solucao_astar_manhattan:
        print(f"  Solução encontrada em {len(solucao_astar_manhattan)} movimentos.")
        print(f"  Número de nós visitados: {nos_astar_manhattan}")
        print(f"  Tempo de execução: {tempo_astar_manhattan:.3f} segundos\n")
    else:
        print("  Solução não encontrada.\n")

    # Busca A* com Número de Peças Fora do Lugar
    inicio_tempo = time.time()
    solucao_astar_pecas_fora, nos_astar_pecas_fora = a_estrela(
        estado_inicial_tuple, estado_objetivo_tuple, pecas_fora_lugar
    )
    fim_tempo = time.time()
    tempo_astar_pecas_fora = fim_tempo - inicio_tempo

    print("Busca A* com Número de Peças Fora do Lugar:")
    if solucao_astar_pecas_fora:
        print(f"  Solução encontrada em {len(solucao_astar_pecas_fora)} movimentos.")
        print(f"  Número de nós visitados: {nos_astar_pecas_fora}")
        print(f"  Tempo de execução: {tempo_astar_pecas_fora:.3f} segundos\n")
    else:
        print("  Solução não encontrada.\n")