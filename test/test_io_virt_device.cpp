#include "catch2/catch.hpp"
#include "io/virtdevice.hpp"

TEST_CASE("Test Init", "[device]") {

    io::VirtDevice dev("/hello/world");

    REQUIRE(dev.open("rw") != 0);
}