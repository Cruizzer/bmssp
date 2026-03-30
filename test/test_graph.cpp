#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "graph.hpp"

using Catch::Approx;

TEST_CASE("Graph: Basic vertex operations", "[graph]") {
    Graph g;
    
    SECTION("Add vertices") {
        g.add_vertex();
        g.add_vertex();
        g.add_vertex();
        
        REQUIRE(g.adj.size() == 3);
    }
    
    SECTION("Empty adjacency lists initially") {
        g.add_vertex();
        REQUIRE(g.adj[0].empty());
    }
}

TEST_CASE("Graph: Edge operations", "[graph]") {
    Graph g;
    g.add_vertex();
    g.add_vertex();
    
    SECTION("Add edge") {
        g.adj[0].push_back({1, 10.5});
        
        REQUIRE(g.adj[0].size() == 1);
        REQUIRE(g.adj[0][0].to == 1);
        REQUIRE(g.adj[0][0].weight == Approx(10.5));
    }
    
    SECTION("Multiple edges from same vertex") {
        g.add_vertex();
        
        g.adj[0].push_back({1, 10.0});
        g.adj[0].push_back({2, 20.0});
        
        REQUIRE(g.adj[0].size() == 2);
        REQUIRE(g.adj[0][0].to == 1);
        REQUIRE(g.adj[0][1].to == 2);
    }
}

TEST_CASE("Graph: Operator[] access", "[graph]") {
    Graph g;
    
    SECTION("Const access") {
        g.add_vertex();
        const Graph& cg = g;
        
        REQUIRE(cg[0].empty());
    }
    
    SECTION("Non-const access") {
        g.add_vertex();
        g.add_vertex();
        
        g[0].push_back({1, 5.0});
        REQUIRE(g[0].size() == 1);
    }
}

TEST_CASE("Graph: Empty graph", "[graph]") {
    Graph g;
    
    REQUIRE(g.adj.empty());
}

TEST_CASE("Graph: Large graph structure", "[graph]") {
    Graph g;
    int n = 1000;
    
    SECTION("Can handle many vertices") {
        for (int i = 0; i < n; ++i) {
            g.add_vertex();
        }
        
        REQUIRE(g.adj.size() == n);
    }
    
    SECTION("Can handle many edges") {
        for (int i = 0; i < n; ++i) {
            g.add_vertex();
        }
        
        // Add edges to form a chain
        for (int i = 0; i < n - 1; ++i) {
            g.adj[i].push_back({static_cast<Vertex>(i + 1), 1.0});
        }
        
        REQUIRE(g.adj[0].size() == 1);
        REQUIRE(g.adj[n - 1].empty());
    }
}
