#ifndef GRIDNODE_H
#define GRIDNODE_H

#include <cstddef>

namespace Mana {

/**
 * @brief The Node class An example of a simple node class.
 */
class GridNode {
    int mX, mY;
public:
    /**
     * @brief Node constructor based on two grid coords.
     * @param x
     * @param y
     */
    GridNode(int x, int y) : mX(x), mY(y) { }

    /**
     * @brief id Gets a unique id for this grid node
     * @return A uniquie id for this grid node.
     */
    std::size_t id() const;

    bool operator==(const GridNode &other) const {
        return mX == other.mX && mY == other.mY;
    }

    bool operator!=(const GridNode &other) const {
        return !(*this == other);
    }

    int x() const { return mX; }
    int y() const { return mY; }
};

}

#endif // GRIDNODE_HPP
