#include "catch2/catch.hpp"

#include "dt/dtbase.hpp"

#include <cstdint>

using namespace dt::dtbase;

template <typename T>
using Seconds = Base10Unit<T, 0, Base10UnitType::TIME>;

template <typename T>
using Desiseconds = Base10Unit<T, -1, Base10UnitType::TIME>;

template <typename T>
using Kiloseconds = Base10Unit<T, 3, Base10UnitType::TIME>;

template <typename T>
using Meters = Base10Unit<T, 0, Base10UnitType::DISTANCE>;

TEST_CASE("Test ctor", "[datatype]") {
        Seconds<uint8_t> a(100);
        Seconds<uint16_t> b(100);
        Seconds<uint32_t> c(100);
        Seconds<uint64_t> d(100);
        Seconds<int8_t> e(100);
        Seconds<int16_t> f(100);
        Seconds<int32_t> g(100);
        Seconds<int64_t> h(100);
        Seconds<float> i(100);
        Seconds<double> j(100);
}

TEST_CASE("Test conversion", "[datatype]") {
        Seconds<int> a(1000);
        Desiseconds<int> b(a);
        Kiloseconds<int> k(a);
        REQUIRE(a == b);
        REQUIRE(a == k);
        REQUIRE(k == b);
}

TEST_CASE("Test equal", "[datatype]") {
        Seconds<int> a(100);
        Desiseconds<int> b(100 * 10);
        Seconds<int8_t> c(100);
        REQUIRE(a == b);
        REQUIRE(b == a);
        REQUIRE(a == c);
        REQUIRE(c == a);
}

TEST_CASE("Test not equal", "[datatype]") {
        Seconds<int> a(100);
        Desiseconds<int> b(a + 1);

        REQUIRE(a != b);
}

TEST_CASE("Test less than", "[datatype]") {
        Seconds<int> a(100);
        Seconds<int> b(101);
        Desiseconds<int8_t> c(1);
        REQUIRE(a < b);
        REQUIRE(c < b);
}

TEST_CASE("Test greater than", "[datatype]") {
        Seconds<int> a(100);
        Seconds<int> b(101);
        Desiseconds<int8_t> c(100);
        REQUIRE(b > a);
        REQUIRE(b > c);
}

TEST_CASE("Test Second sum", "[datatype]") {
        Seconds<int> a(0);
        Desiseconds<int> b(0);
        Seconds<uint64_t> c(100);

        a = a + 1;
        b = b + 10;

        REQUIRE(a == b);

        a = a + c;
        b = b + c;

        REQUIRE(a == b);
}

TEST_CASE("Test Second sumassign", "[datatype]") {
        Seconds<int> a(0);
        Desiseconds<uint> b(0);
        Seconds<int8_t> c(127);

        a += 1;
        b += 10;
        REQUIRE(a == b);

        a += c;
        b += c;

        REQUIRE(a == b);
}
