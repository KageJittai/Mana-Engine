#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <Mana/test.hpp>

TEST_CASE( "Test Mana's Test class ")
{
    Mana::Test test(5);

    REQUIRE(test.TestValue() == 25);
}
