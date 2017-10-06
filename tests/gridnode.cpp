#include <catch.hpp>

#include <Mana/gridnode.hpp>

using namespace Mana;

TEST_CASE("GridNode class", "[GridNode]")
{
    const GridNode a(4, 12);
    const GridNode b(8, 34);
    const GridNode c(8, 34);

    SECTION("should have x() getter")
    {
        REQUIRE(a.x() == 4);
        REQUIRE(b.x() == 8);
        REQUIRE(c.x() == 8);
    }

    SECTION("should have y() getter")
    {
        REQUIRE(a.y() == 12);
        REQUIRE(b.y() == 34);
        REQUIRE(c.y() == 34);
    }

    SECTION("should support equivalence operators")
    {
        REQUIRE(a == a);
        REQUIRE(b == c);
        REQUIRE((a != a) == false);
        REQUIRE(a != b);
    }

    SECTION("should have unique ids")
    {
        REQUIRE(a.id() == a.id());
        REQUIRE(b.id() == c.id());
        REQUIRE(a.id() != b.id());
    }
}
