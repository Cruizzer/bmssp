#pragma once
#include "graph.hpp"
#include <vector>

namespace algorithms {

// BMSSP algorithm interface (stubbed)
// For now these forward to Dijkstra as a placeholder; implementation deferred.
std::vector<Weight> bmssp(const Graph& graph, Vertex source);
Weight bmssp_single_target(const Graph& graph, Vertex source, Vertex target);
std::vector<Vertex> bmssp_path(const Graph& graph, Vertex source, Vertex target);

} // namespace algorithms
