#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "graph.hpp"
#include "algorithms/dijkstra.hpp"
#include <limits>
#include <algorithm>
#include <cmath>

using Catch::Approx;

TEST_CASE("Dijkstra: Simple 3-vertex graph", "[dijkstra]") {
    Graph g;
    g.add_vertex();
    g.add_vertex();
    g.add_vertex();
    
    // 0 -> 1 (weight 10)
    // 1 -> 2 (weight 20)
    // 0 -> 2 (weight 50)
    g.adj[0].push_back({1, 10.0});
    g.adj[1].push_back({2, 20.0});
    g.adj[0].push_back({2, 50.0});
    
    SECTION("All distances from vertex 0") {
        auto dist = algorithms::dijkstra(g, 0);
        
        REQUIRE(dist[0] == Approx(0.0));
        REQUIRE(dist[1] == Approx(10.0));
        REQUIRE(dist[2] == Approx(30.0));  
    }
    
    SECTION("Single target from vertex 0 to 2") {
        auto dist = algorithms::dijkstra_single_target(g, 0, 2);
        REQUIRE(dist == Approx(30.0));
    }
    
    SECTION("Path reconstruction from 0 to 2") {
        auto path = algorithms::dijkstra_path(g, 0, 2);
        
        REQUIRE(path.size() == 3);
        REQUIRE(path[0] == 0);
        REQUIRE(path[1] == 1);
        REQUIRE(path[2] == 2);
    }
}

TEST_CASE("Dijkstra: Disconnected graph", "[dijkstra]") {
    Graph g;
    g.add_vertex();
    g.add_vertex();
    g.add_vertex();
    
    g.adj[0].push_back({1, 10.0});
    
    SECTION("Unreachable vertex has infinite distance") {
        auto dist = algorithms::dijkstra(g, 0);
        
        REQUIRE(dist[0] == Approx(0.0));
        REQUIRE(dist[1] == Approx(10.0));
        REQUIRE(dist[2] == std::numeric_limits<Weight>::infinity());
    }
    
    SECTION("Single target to unreachable vertex") {
        auto dist = algorithms::dijkstra_single_target(g, 0, 2);
        REQUIRE(dist == std::numeric_limits<Weight>::infinity());
    }
    
    SECTION("Path to unreachable vertex is empty") {
        auto path = algorithms::dijkstra_path(g, 0, 2);
        
        REQUIRE(path.empty());
    }
}

TEST_CASE("Dijkstra: Single vertex graph", "[dijkstra]") {
    Graph g;
    g.add_vertex();
    
    SECTION("Distance to self is zero") {
        auto dist = algorithms::dijkstra(g, 0);
        REQUIRE(dist[0] == Approx(0.0));
    }
    
    SECTION("Path to self is just source") {
        auto path = algorithms::dijkstra_path(g, 0, 0);
        
        REQUIRE(path.size() == 1);
        REQUIRE(path[0] == 0);
    }
}

TEST_CASE("Dijkstra: Diamond graph with multiple paths", "[dijkstra]") {
    Graph g;
    for (int i = 0; i < 4; ++i) {
        g.add_vertex();
    }
    
    g.adj[0].push_back({1, 5.0});
    g.adj[0].push_back({2, 10.0});
    g.adj[1].push_back({3, 8.0});
    g.adj[2].push_back({3, 2.0});
    
    SECTION("Shortest path is via vertex 2") {
        auto dist = algorithms::dijkstra(g, 0);
        
        REQUIRE(dist[0] == Approx(0.0));
        REQUIRE(dist[1] == Approx(5.0));
        REQUIRE(dist[2] == Approx(10.0));
        REQUIRE(dist[3] == Approx(12.0));
    }
    
    SECTION("Path takes the shorter route") {
        auto path = algorithms::dijkstra_path(g, 0, 3);
        
        REQUIRE(path.size() == 3);
        REQUIRE(path[0] == 0);
        REQUIRE(path[1] == 2);
        REQUIRE(path[2] == 3);
    }
}

TEST_CASE("Dijkstra: Complete graph", "[dijkstra]") {
    Graph g;
    int n = 5;
    for (int i = 0; i < n; ++i) {
        g.add_vertex();
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                double weight = std::abs(i - j) * 10.0;
                g.adj[i].push_back({j, weight});
            }
        }
    }
    
    SECTION("All vertices reachable from 0") {
        auto dist = algorithms::dijkstra(g, 0);
        
        REQUIRE(dist[0] == Approx(0.0));
        REQUIRE(dist[1] == Approx(10.0));
        REQUIRE(dist[2] == Approx(20.0));
        REQUIRE(dist[3] == Approx(30.0));
        REQUIRE(dist[4] == Approx(40.0));
    }
}

TEST_CASE("Dijkstra: Linear chain", "[dijkstra]") {
    Graph g;
    int n = 10;
    for (int i = 0; i < n; ++i) {
        g.add_vertex();
    }
    
    for (int i = 0; i < n - 1; ++i) {
        g.adj[i].push_back({i + 1, 1.0});
    }
    
    SECTION("Distance increases linearly") {
        auto dist = algorithms::dijkstra(g, 0);
        
        for (int i = 0; i < n; ++i) {
            REQUIRE(dist[i] == Approx(i * 1.0));
        }
    }
    
    SECTION("Path is complete chain") {
        auto path = algorithms::dijkstra_path(g, 0, n - 1);
        
        REQUIRE(path.size() == n);
        for (int i = 0; i < n; ++i) {
            REQUIRE(path[i] == i);
        }
    }
}
