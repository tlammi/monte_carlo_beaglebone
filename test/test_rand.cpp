#include "catch2/catch.hpp"


#include "fal/rand.hpp"

TEST_CASE("Test generate uniform") {

    int32_t limit_array[]= {17, 100,
                            -1, 2,
                            (1<<31), (1<<31)^((int32_t)(-1))};

    for(size_t i=0; i < sizeof(limit_array)/sizeof(limit_array[0]); i+= 2){
        int32_t uniform_start = limit_array[i];
        int32_t uniform_end = limit_array[i+1];
        INFO("Testing with limits " << uniform_start << " and " << uniform_end);
        const size_t SAMPLE_COUNT = 1000000;
        int32_t sample_buffer[SAMPLE_COUNT];

        int res = fal::rand::generate_uniform(uniform_start, uniform_end, sample_buffer, SAMPLE_COUNT);
        REQUIRE(res == 0);

        for(size_t j=0; j < SAMPLE_COUNT; j++){
            REQUIRE(sample_buffer[j] < uniform_end);
            REQUIRE(sample_buffer[j] >= uniform_start);
        }

        long double average = 0;
        for(size_t j=0; j < SAMPLE_COUNT; j++){
            average += (long double)sample_buffer[j] / (long double) SAMPLE_COUNT;
        }
        INFO("average: " << average);
        using namespace Catch::literals;
        REQUIRE(((average == Approx((uniform_end+uniform_start)/2).epsilon(0.01))
                ||
                (average - uniform_end+uniform_start)/2 < 1));
    }

}