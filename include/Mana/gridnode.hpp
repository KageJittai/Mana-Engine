#ifndef GRIDNODE_H
#define GRIDNODE_H

#include <cstddef>

namespace Mana {

/**
 * @brief The Node class An example of a simple node class.
 */
class GridNode {
    std::size_t mX, mY;
public:
    /**
     * @brief Node constructor based on two grid coords.
     * @param x
     * @param y
     */
    GridNode(std::size_t x, std::size_t y) : mX(x), mY(y) { }

    /**
     * @brief id Gets a unique id for this grid node
     * @return A uniquie id for this grid node.
     */
    std::size_t id() const {
        return mY * 4294967296 + mX;
    }

    bool operator==(const GridNode &other) const {
        return mX == other.mX && mY == other.mY;
    }

    bool operator!=(const GridNode &other) const {
        return mX != other.mX || mY != other.mY;
    }

    std::size_t x() const { return mX; }
    std::size_t y() const { return mY; }
};

}

#endif // GRIDNODE_HPP
