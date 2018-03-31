#include <catch.hpp>
#include "Colour.hpp"

using namespace TinyBox::Graphics;

TEST_CASE("Comparisons", "[Colour]")
{
    auto colour1 = Colour::black();
    auto colour2 = Colour::white();

    auto colour1_copy = colour1;
    auto colour2_copy = colour2;

    REQUIRE(colour1 != colour2);
    REQUIRE(colour2 != colour1);
    REQUIRE(colour1 == colour1_copy);
    REQUIRE(colour2 == colour2_copy);
}

TEST_CASE("Multiplication operator", "[Colour]")
{
    const auto colour1 = Colour::white();
    REQUIRE(colour1.r() == 1.0f);
    REQUIRE(colour1.g() == 1.0f);
    REQUIRE(colour1.b() == 1.0f);
    REQUIRE(colour1.a() == 1.0f);

    const auto colour2 = colour1 * 0.2;
    REQUIRE(colour2.r() == 0.2f);
    REQUIRE(colour2.g() == 0.2f);
    REQUIRE(colour2.b() == 0.2f);
    REQUIRE(colour2.a() == 0.2f);
}

TEST_CASE("Division operator", "[Colour]")
{
    const auto colour1 = Colour::white();
    REQUIRE(colour1.r() == 1.0f);
    REQUIRE(colour1.g() == 1.0f);
    REQUIRE(colour1.b() == 1.0f);
    REQUIRE(colour1.a() == 1.0f);

    const auto colour2 = colour1 / 5;
    REQUIRE(colour2.r() == 0.2f);
    REQUIRE(colour2.g() == 0.2f);
    REQUIRE(colour2.b() == 0.2f);
    REQUIRE(colour2.a() == 0.2f);
}

TEST_CASE("Construct a colour using a packed 32-bit unsinged integer", "[Colour]")
{
    const Colour red(0xffff0000);
    REQUIRE(red.r() == 1.0f);
    REQUIRE(red.g() == 0.0f);
    REQUIRE(red.b() == 0.0f);
    REQUIRE(red.a() == 1.0f);

    const Colour blue(0xff0000ff);
    REQUIRE(blue.r() == 0.0f);
    REQUIRE(blue.g() == 0.0f);
    REQUIRE(blue.b() == 1.0f);
    REQUIRE(blue.a() == 1.0f);

    const Colour white(UINT32_MAX);
    REQUIRE(white.r() == 1.0f);
    REQUIRE(white.g() == 1.0f);
    REQUIRE(white.b() == 1.0f);
    REQUIRE(white.a() == 1.0f);

    const Colour black(0xff000000);
    REQUIRE(black.r() == 0.0f);
    REQUIRE(black.g() == 0.0f);
    REQUIRE(black.b() == 0.0f);
    REQUIRE(black.a() == 1.0f);
}

TEST_CASE("Construct a colour from static factory methods", "[Colour]")
{
    const auto red = Colour::red();
    REQUIRE(red.r() == 1.0f);
    REQUIRE(red.g() == 0.0f);
    REQUIRE(red.b() == 0.0f);
    REQUIRE(red.a() == 1.0f);

    const auto blue = Colour::blue();
    REQUIRE(blue.r() == 0.0f);
    REQUIRE(blue.g() == 0.0f);
    REQUIRE(blue.b() == 1.0f);
    REQUIRE(blue.a() == 1.0f);

    const auto white = Colour::white();
    REQUIRE(white.r() == 1.0f);
    REQUIRE(white.g() == 1.0f);
    REQUIRE(white.b() == 1.0f);
    REQUIRE(white.a() == 1.0f);

    const auto black = Colour::black();
    REQUIRE(black.r() == 0.0f);
    REQUIRE(black.g() == 0.0f);
    REQUIRE(black.b() == 0.0f);
    REQUIRE(black.a() == 1.0f);
}

TEST_CASE("Construct a colour using floating point values", "[Colour]")
{
    const Colour red(1.0f, 0.0f, 0.0f);
    REQUIRE(red.r() == 1.0f);
    REQUIRE(red.g() == 0.0f);
    REQUIRE(red.b() == 0.0f);
    REQUIRE(red.a() == 1.0f);

    const Colour blue(0.0f, 0.0f, 1.0f, 0.0f);
    REQUIRE(blue.r() == 0.0f);
    REQUIRE(blue.g() == 0.0f);
    REQUIRE(blue.b() == 1.0f);
    REQUIRE(blue.a() == 0.0f);

    const Colour white(1.0f, 1.0f, 1.0f);
    REQUIRE(white.r() == 1.0f);
    REQUIRE(white.g() == 1.0f);
    REQUIRE(white.b() == 1.0f);
    REQUIRE(white.a() == 1.0f);

    const Colour black(0.0f, 0.0f, 0.0f, 1.0f);
    REQUIRE(black.r() == 0.0f);
    REQUIRE(black.g() == 0.0f);
    REQUIRE(black.b() == 0.0f);
    REQUIRE(black.a() == 1.0f);
}

TEST_CASE("Construct a colour using integer values", "[Colour]")
{
    const Colour red(255, 0, 0);
    REQUIRE(red.r() == 1.0f);
    REQUIRE(red.g() == 0.0f);
    REQUIRE(red.b() == 0.0f);
    REQUIRE(red.a() == 1.0f);

    const Colour blue(0, 0, 255, 255);
    REQUIRE(blue.r() == 0.0f);
    REQUIRE(blue.g() == 0.0f);
    REQUIRE(blue.b() == 1.0f);
    REQUIRE(blue.a() == 1.0f);

    const Colour white(255, 255, 255);
    REQUIRE(white.r() == 1.0f);
    REQUIRE(white.g() == 1.0f);
    REQUIRE(white.b() == 1.0f);
    REQUIRE(white.a() == 1.0f);

    const Colour black(0, 0, 0, 255);
    REQUIRE(black.r() == 0.0f);
    REQUIRE(black.g() == 0.0f);
    REQUIRE(black.b() == 0.0f);
    REQUIRE(black.a() == 1.0f);
}