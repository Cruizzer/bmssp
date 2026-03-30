#include <iostream>
#include <string>
#include "graph_generator.hpp"
#include "benchmark/benchmark.hpp"
#include "algorithms/dijkstra.hpp"
#include "algorithms/bmssp.hpp"

int main(int argc, char** argv) {
    // Simple demo: generate a small random graph and compare algorithms
    size_t n = 100;
    double avg_deg = 4.0;

    if (argc > 1) {
        // Expect numeric args like: bmssp N [avg_deg]
        try {
            n = std::stoul(argv[1]);
        } catch (...) {
            std::cerr << "Usage: " << argv[0] << " [N] [avg_deg]\n";
            return 1;
        }
        if (argc > 2) {
            try {
                avg_deg = std::stod(argv[2]);
            } catch (...) {
                std::cerr << "Invalid avg_deg: " << argv[2] << "\n";
                return 1;
            }
        }
    }

    Graph g = generate_random_graph(n, avg_deg);
    Vertex source = 0;

    auto comp = benchmark::compare_algorithms(
        algorithms::dijkstra,
        algorithms::bmssp,
        g,
        source
    );

    benchmark::print_comparison(comp);
    return 0;
}
