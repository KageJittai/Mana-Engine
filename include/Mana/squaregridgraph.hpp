#ifndef SQUAREGRIDGRAPH_H
#define SQUAREGRIDGRAPH_H

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace Mana {

/**
 * @brief The SquareGridGraph class is a graph were all nodes in a regular or semi-regular grid.
 */
template<class NodeT>
class SquareGridGraph
{
protected:
     std::size_t mWidth, mHeight;
public:
    /**
     * @brief SquareGridGraph Constructor
     * @param width The width of the graph
     * @param height The height of the graph
     */
    SquareGridGraph(int width, int height) : mWidth(width), mHeight(height) {}

    std::size_t width() const { return mWidth; }
    std::size_t height() const { return mHeight; }

    std::size_t maxSize() const { return mWidth * mHeight; }

    /**
     * @brief isNeighbor Determines if two nodes are neighbors.
     * @param first
     * @param second
     * @return True if frist and second are neighbors.
     */
    virtual bool isNeighbor(const NodeT &first, const NodeT &second) const
    {
        return (abs(first.x() - second.x()) <= 1) &&
               (abs(first.y() - second.y()) <= 1) &&
               isNodeOnGraph(first) && isNodeOnGraph(second);
    }

    /**
     * @brief isNodeOnGraph Determines if a node belongs on the graph.
     * @param node
     * @return true if it is, false otherwise.
     */
    virtual bool isNodeOnGraph(const NodeT &node) const
    {
        return (node.x() >= 0 && node.x() < mWidth) &&
               (node.y() >= 0 && node.y() < mHeight);
    }

    /**
     * @brief findNeightbors Finds all the neighbors of node and adds them to neighbors
     * @param node The node to find neighbors.
     * @param neighbors std::vector to back fill with neighboring nodes of node.
     */
    void findNeighbors(const NodeT &node, std::vector<NodeT> &neighbors) const
    {
        NodeT t(node.x(), node.y() - 1);
        NodeT b(node.x(), node.y() + 1);
        NodeT l(node.x() - 1, node.y());
        NodeT r(node.x() + 1, node.y());

        if (isNodeOnGraph(t)) {
            neighbors.push_back(std::move(t));
        }
        if (isNodeOnGraph(b)) {
            neighbors.push_back(std::move(b));
        }
        if (isNodeOnGraph(l)) {
            neighbors.push_back(std::move(l));
        }
        if (isNodeOnGraph(r)) {
            neighbors.push_back(std::move(r));
        }
    }

    /**
     * @brief heuristicDistance Gets the heuristical distance between two nodes.
     * @param from Starting node.
     * @param to Target node.
     * @return Distance value
     */
    int heuristicDistance(const NodeT &from, const NodeT &to) const
    {
        // Manhatten distance by default
        return abs(to.x() - from.x()) + abs(to.y() - from.y());
    }

    /**
     * @brief moveToCost Get the cost between two nodes.  Note: these nodes must be neighbors.
     * @param start Node you are coming from.
     * @param target Node you are moving too.
     * @return Cost of moving between the nodes.
     */
    int moveCost(const NodeT &from, const NodeT &to) const
    {
        if (!isNeighbor(from, to)) {
            throw std::invalid_argument("Supplied nodes are not neighbors.");
        }
        return 1;
    }
};

}

#endif // SQUAREGRIDGRAPH_H
