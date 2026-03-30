#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "graph.hpp"
#include "algorithms/dijkstra.hpp"
#include "algorithms/bmssp.hpp"

using Catch::Approx;

TEST_CASE("Multi-source: super-source translation", "[multi-source]") {
    Graph g;

    for (int i = 0; i < 10; ++i) {
        g.add_vertex();
    }

    const size_t S = 0;
    const size_t A = 1;
    const size_t B = 2;
    const size_t C = 3;
    const size_t D = 4;
    const size_t E = 5;
    const size_t F = 6;
    const size_t G = 7;
    const size_t H = 8;
    const size_t I = 9;

    auto add_directed = [&](size_t u, size_t v, double w) {
        g.adj[u].push_back({v, w});
    };

    add_directed(S, B, 3.0);
    add_directed(S, C, 2.0);
    add_directed(A, C, 3.0);
    add_directed(A, D, 2.0);
    add_directed(B, E, 2.0);
    add_directed(C, E, 2.0);
    add_directed(E, G, 3.0);
    add_directed(F, H, 2.0);
    add_directed(G, I, 1.0);
    add_directed(H, I, 2.0);

    g.add_vertex();
    const size_t SUPER = g.size() - 1;

    g.adj[SUPER].push_back({S, 0.0});
    g.adj[SUPER].push_back({A, 1.0});
    g.adj[SUPER].push_back({C, 2.0});
    g.adj[SUPER].push_back({F, 5.0});

    auto dist_dijkstra = algorithms::dijkstra(g, SUPER);
    auto dist_bmssp = algorithms::bmssp(g, SUPER);

    std::vector<double> expected = {
        0.0, // s
        1.0, // a
        3.0, // b
        2.0, // c
        3.0, // d
        4.0, // e
        5.0, // f
        7.0, // g
        7.0, // h
        8.0  // i
    };

    REQUIRE(dist_dijkstra.size() == expected.size() + 1);
    REQUIRE(dist_bmssp.size() == expected.size() + 1);

    for (size_t v = 0; v < expected.size(); ++v) {
        REQUIRE(dist_dijkstra[v] == Approx(expected[v]));
        REQUIRE(dist_bmssp[v] == Approx(expected[v]));
    }

    REQUIRE(dist_dijkstra[SUPER] == Approx(0.0));
    REQUIRE(dist_bmssp[SUPER] == Approx(0.0));
}
