#include <Mana/gridnode.hpp>

std::size_t Mana::GridNode::id() const {
    std::size_t uY = static_cast<std::size_t>(mY),
                uX = static_cast<std::size_t>(mX);

    return (uY << (sizeof(mY) * 4)) + uX;
}
