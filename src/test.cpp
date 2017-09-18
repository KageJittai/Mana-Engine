#include <Mana/test.hpp>

using namespace Mana;

Test::Test(int x) : mX(x)
{

}

int Test::TestValue() const
{
    return mX * 5;
}
