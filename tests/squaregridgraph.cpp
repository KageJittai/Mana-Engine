#include <catch.hpp>

#include <Mana/squaregridgraph.hpp>
#include <Mana/gridnode.hpp>

using namespace Mana;

TEST_CASE("Small SquareGridGraph", "[SquareGridGraph]")
{
    SquareGridGraph<GridNode> ssg(5, 3);

    SECTION("grid dimensions", "[Width],[Height],[maxSize]")
    {
        REQUIRE(ssg.width() == 5);
        REQUIRE(ssg.height() == 3);
        REQUIRE(ssg.maxSize() == 15);
    }

    SECTION("is node on graph check", "[isNodeOnGraph]")
    {
        REQUIRE(ssg.isNodeOnGraph({ 0,  0}) == true);
        REQUIRE(ssg.isNodeOnGraph({ 2,  2}) == true);
        //REQUIRE(ssg.isNodeOnGraph({-1, -1}) == false);
        REQUIRE(ssg.isNodeOnGraph({ 5,  3}) == false);
        REQUIRE(ssg.isNodeOnGraph({ 5,  2}) == false);
    }

    SECTION("check node neighbors", "[isNeighbor]")
    {
        SECTION ("valid neighbors")
        {
            REQUIRE(ssg.isNeighbor({2, 2}, {1, 2}) == true);
            REQUIRE(ssg.isNeighbor({2, 2}, {3, 2}) == true);
            REQUIRE(ssg.isNeighbor({2, 2}, {2, 1}) == true);
        }

        SECTION ("corner neighbors are invalid")
        {
            REQUIRE(ssg.isNeighbor({2, 2}, {1, 1}) == false);
            REQUIRE(ssg.isNeighbor({2, 2}, {1, 3}) == false);
            REQUIRE(ssg.isNeighbor({2, 2}, {3, 1}) == false);
            REQUIRE(ssg.isNeighbor({2, 2}, {3, 3}) == false);
        }

        SECTION ("self is not a neighbor")
        {
            REQUIRE(ssg.isNeighbor({2, 2}, {2, 2}) == false);
        }

        SECTION ("distance nodes aren't neighbors")
        {
            REQUIRE(ssg.isNeighbor({2, 2}, {0, 0}) == false);
            REQUIRE(ssg.isNeighbor({2, 2}, {4, 2}) == false);
        }

        SECTION ("off grid nodes aren't neighbors")
        {
            REQUIRE(ssg.isNeighbor({2, 2}, {2, 3}) == false);
        }
    }

    SECTION("get neighbor nodes")
    {
        std::vector<GridNode> output;

        SECTION("4 valid neighbors for a node")
        {
            ssg.findNeighbors({1,1}, output);
            REQUIRE(output.size() == 4);
            REQUIRE(std::find(output.begin(), output.end(), GridNode{1, 0}) != output.end());
            REQUIRE(std::find(output.begin(), output.end(), GridNode{1, 2}) != output.end());
            REQUIRE(std::find(output.begin(), output.end(), GridNode{0, 1}) != output.end());
            REQUIRE(std::find(output.begin(), output.end(), GridNode{2, 1}) != output.end());
        }

        SECTION("invalid nodes should not be returned")
        {
            ssg.findNeighbors({4,2}, output);
            REQUIRE(output.size() == 2);
            REQUIRE(std::find(output.begin(), output.end(), GridNode{4, 1}) != output.end());
            REQUIRE(std::find(output.begin(), output.end(), GridNode{3, 2}) != output.end());
        }
    }

    SECTION("Heuristic distance", "[heuristicDistance]")
    {
        REQUIRE(ssg.heuristicDistance({0,0}, {0, 3}) == 3);
        REQUIRE(ssg.heuristicDistance({3,0}, {0, 0}) == 3);
        REQUIRE(ssg.heuristicDistance({0,0}, {3, 3}) == 6);
    }

    SECTION("Move cost", "[moveCost]")
    {
        REQUIRE(ssg.moveCost({0, 0}, {0,1}) == 1);
        REQUIRE(ssg.moveCost({0, 0}, {1,0}) == 1);
        REQUIRE_THROWS_WITH(ssg.moveCost({0, 0}, {1,1}), "Supplied nodes are not neighbors.");
    }
}
