#include <catch.hpp>

#include <Mana/gridnode.hpp>
#include <Mana/squaregridgraph.hpp>
#include <Mana/astar.hpp>

using namespace Mana;

TEST_CASE("AStar on an empty map", "[AStar]")
{
    using grapht = SquareGridGraph<GridNode>;
    grapht graph(10, 10);

    SECTION("Shortest stright line path", "[findPath]")
    {
        AStar<grapht> astar(graph);
        auto path = astar.findPath({0,5}, {9, 5});
        REQUIRE(path.size() == 10);

        std::vector<GridNode> expectedPath = {
            {9, 5}, {8, 5}, {7, 5}, {6, 5}, {5, 5},
            {4, 5}, {3, 5}, {2, 5}, {1, 5}, {0, 5}
        };

        REQUIRE(expectedPath == path);
    }

    SECTION("Pathing to node out of reach", "[findPath]")
    {
        AStar<grapht> astar(graph);
        auto path = astar.findPath({0,5}, {10, 5});
        REQUIRE(path.size() == 0);
    }

    SECTION("Pathing to neighboring node", "[findPath]")
    {
        AStar<grapht> astar(graph);
        auto path = astar.findPath({0,5}, {1, 5});
        REQUIRE(path.size() == 2);
        std::vector<GridNode> expectedPath = {{1, 5}, {0,5}};
        REQUIRE(expectedPath == path);
    }
}

TEST_CASE("AStar path though a hole in the wall", "[AStar]")
{
    class WallGraph : public SquareGridGraph<GridNode>
    {
    public:
        WallGraph(int x, int y) : SquareGridGraph<GridNode>(x, y) {}

        bool isNodeOnGraph(const GridNode &node) const override
        {
            if (node.x() == 5 && node.y() != 8) {
                return false;
            }

            return SquareGridGraph<GridNode>::isNodeOnGraph(node);
        }
    };

    WallGraph graph(10, 10);

    SECTION("Shortest stright line path", "[findPath]")
    {
        AStar<WallGraph> astar(graph);
        auto path = astar.findPath({0,5}, {9, 5});
        REQUIRE(path.size() > 0);

        // Contain start, end and "hole"
        REQUIRE(std::find(path.begin(), path.end(), GridNode{0, 5}) != path.end());
        REQUIRE(std::find(path.begin(), path.end(), GridNode{9, 5}) != path.end());
        REQUIRE(std::find(path.begin(), path.end(), GridNode{5, 8}) != path.end());

        // All nodes should be on the graph
        for (auto &node : path) {
            REQUIRE(graph.isNodeOnGraph(node) == true);
        }
    }

    SECTION("Pathing to node out of reach", "[findPath]")
    {
        AStar<WallGraph> astar(graph);
        auto path = astar.findPath({0,5}, {10, 5});
        REQUIRE(path.size() == 0);
    }
}
