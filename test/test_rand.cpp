#include "catch2/catch.hpp"

#include <sstream>

//#include "fal/rand.hpp"
#include "src/fal/rand.cpp"

TEST_CASE("Test binary search") {

    int32_t test_arr[100];

    for(int32_t i=0; i < 100; i++){
        test_arr[i] = -50 + i*2;
    }

    int32_t* result = fal::rand::binary_search(-50, test_arr, test_arr+99);
    REQUIRE(result == test_arr);
    result = fal::rand::binary_search(-49, test_arr, test_arr+99);
    REQUIRE(result == test_arr);
    result = fal::rand::binary_search(-47, test_arr, test_arr+99);
    REQUIRE(result == test_arr+1);
    result = fal::rand::binary_search(0, test_arr, test_arr+99);
    REQUIRE(result == test_arr+25);
    result = fal::rand::binary_search(148, test_arr, test_arr+99);
    REQUIRE(result == test_arr+99);
    result = fal::rand::binary_search(149, test_arr, test_arr+99);
    REQUIRE(result == nullptr);
    result = fal::rand::binary_search(-100, test_arr, test_arr+99);
    REQUIRE(result == test_arr);

}

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
        REQUIRE(((average == Approx((uniform_end+uniform_start)/2).epsilon(0.01))
                ||
                (average - uniform_end+uniform_start)/2 < 1));
    }

}

TEST_CASE("Test generate_from_cpdf") {
    const size_t CPDF_SAMPLES = 1000;
    const size_t GENERATED_SAMPLE_COUNT = 10000;

    int32_t cpdf_values[CPDF_SAMPLES];
    int32_t cpdf_weigths[CPDF_SAMPLES];
    // Uniform pdf from 0 to 1000
    for(size_t i=0; i <CPDF_SAMPLES; i++){
        cpdf_values[i] = i;
        cpdf_weigths[i] = i;
    }

    int32_t sample_buffer[GENERATED_SAMPLE_COUNT];

    int result = fal::rand::generate_from_cpdf(cpdf_values, cpdf_weigths, CPDF_SAMPLES, sample_buffer, GENERATED_SAMPLE_COUNT);
    REQUIRE(result == 0);

    long double average = 0;
    for(size_t j=0; j < GENERATED_SAMPLE_COUNT; j++){
        average += (long double)sample_buffer[j] /(long double) GENERATED_SAMPLE_COUNT;
    }

    INFO("average: " << average);
    REQUIRE(average == Approx(500).epsilon(0.01));
}

TEST_CASE("Test multiply pdfs", "[multiply][pdf]") {
    int32_t y_vals[] = {1,2,10,15};
    int32_t y_weights[] = {1, 4, 20, 5};
    int32_t x_vals[] = {-100, -1, 1, 2, 3, 7, 11, 14, 15, 16, 100};
    int32_t x_weights[] = {1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000};

    int32_t expected[] = {0, 0, 1000, 4000, 6000, 14000, 17000, 8000, 5000, 2000, 0};

    int res = fal::rand::multiply_pdfs(x_vals, x_weights, y_vals, y_weights, 11, 4);

    std::stringstream s;
    s << "[";
    for(size_t i=0; i < 11; i++){
        s << x_weights[i];
        if(i == 10){
            s << "]";
        }
        else {
            s << ", ";
        }
    }

    INFO("result: \n" << s.str());

    for(size_t i=0; i<11; i++){
        REQUIRE(x_weights[i] == expected[i]);
    }
}