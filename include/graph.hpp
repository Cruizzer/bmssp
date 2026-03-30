#pragma once
#include <vector>
#include <cstddef>
#include <string>
#include <utility>

// Vertex and weight types
using Vertex = std::size_t;
using Weight = double;

// Edge structure
struct Edge {
    Vertex to;
    Weight weight;
};

// Graph with adjacency list and coordinates for each vertex
struct Graph {
    std::vector<std::vector<Edge>> adj;

    std::size_t size() const { return adj.size(); }
    bool empty() const { return adj.empty(); }

    std::vector<Edge>& operator[](std::size_t i) { return adj[i]; }
    const std::vector<Edge>& operator[](std::size_t i) const { return adj[i]; }

    void add_vertex() {
        adj.emplace_back();
    }
};
