"use strict";
function algoritmo(graph, origem) {
    const distances = {};
    const visited = new Set();
    const previous = {};
    const queue = new Set(Object.keys(graph));
    for (let vertex of queue) {
        distances[vertex] = Infinity;
    }
    distances[origem] = 0;
    while (queue.size > 0) {
        let current = [...queue].reduce((a, b) => distances[a] < distances[b] ? a : b);
        queue.delete(current);
        visited.add(current);
        for (let neighbor in graph[current]) {
            if (visited.has(neighbor))
                continue;
            let newDistance = distances[current] + graph[current][neighbor];
            if (newDistance < distances[neighbor]) {
                distances[neighbor] = newDistance;
                previous[neighbor] = current;
            }
        }
    }
    return { distances, previous };
}
const graph = {
    A: { B: 1, D: 10 },
    B: { C: 3 },
    C: { D: 3 },
    D: {},
};
const result = algoritmo(graph, 'A');
console.log(result.distances);
console.log(result.previous);
