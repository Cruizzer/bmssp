#include "algorithms/bmssp.hpp"
#include "algorithms/dijkstra.hpp"
#include <limits>

namespace algorithms {

std::vector<Weight> bmssp(const Graph& graph, Vertex source) {
    // Placeholder implementation: simply call Dijkstra for now.
    return dijkstra(graph, source);
}

Weight bmssp_single_target(const Graph& graph, Vertex source, Vertex target) {
    auto dist = dijkstra(graph, source);
    if (target >= dist.size()) return std::numeric_limits<Weight>::infinity();
    return dist[target];
}

std::vector<Vertex> bmssp_path(const Graph& graph, Vertex source, Vertex target) {
    // Use Dijkstra path reconstruction until I implement BMSSP.
    return dijkstra_path(graph, source, target);
}

} // namespace algorithms
