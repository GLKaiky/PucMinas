var __spreadArray = (this && this.__spreadArray) || function (to, from, pack) {
    if (pack || arguments.length === 2) for (var i = 0, l = from.length, ar; i < l; i++) {
        if (ar || !(i in from)) {
            if (!ar) ar = Array.prototype.slice.call(from, 0, i);
            ar[i] = from[i];
        }
    }
    return to.concat(ar || Array.prototype.slice.call(from));
};
function algoritmo(graph, origem) {
    var distances = {};
    var visited = new Set();
    var previous = {};
    var queue = new Set(Object.keys(graph));
    for (var _i = 0, queue_1 = queue; _i < queue_1.length; _i++) {
        var vertex = queue_1[_i];
        distances[vertex] = Infinity;
    }
    distances[origem] = 0;
    while (queue.size > 0) {
        var current = __spreadArray([], queue, true).reduce(function (a, b) {
            return distances[a] < distances[b] ? a : b;
        });
        queue.delete(current);
        visited.add(current);
        for (var neighbor in graph[current]) {
            if (visited.has(neighbor))
                continue;
            var newDistance = distances[current] + graph[current][neighbor];
            if (newDistance < distances[neighbor]) {
                distances[neighbor] = newDistance;
                previous[neighbor] = current;
            }
        }
    }
    return { distances: distances, previous: previous };
}
var graph = {
    A: { B: 1, D: 10 },
    B: { C: 3 },
    C: { D: 3 },
    D: {},
};
var result = algoritmo(graph, 'A');
console.log(result.distances);
console.log(result.previous);
