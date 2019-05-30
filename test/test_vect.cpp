#include "catch2/catch.hpp"
#include "fal/vect.hpp"


#define MIN(a, b) ((a) < (b) ? (a) : (b))

const size_t BUFSIZE = 1000;

int32_t* buf1;
int32_t* buf2;
int64_t* outbuf;
int64_t* expected_out;

static void init(){
    buf1 = fal::vect::allocate<int32_t>(BUFSIZE);
    buf2 = fal::vect::allocate<int32_t>(BUFSIZE);
    outbuf = fal::vect::allocate<int64_t>(BUFSIZE);
    expected_out = fal::vect::allocate<int64_t>(BUFSIZE);

    for(size_t i=0; i < BUFSIZE; i++){
        buf1[i] = 1;
        buf2[i] = 1;
        outbuf[i] = 0;
        expected_out[i] = 0;
    }



}

static void deinit(){
    fal::vect::deallocate(buf1);
    fal::vect::deallocate(buf2);
    fal::vect::deallocate(outbuf);
    fal::vect::deallocate(expected_out);
}

TEST_CASE("Test sum", "[sum]"){

    init();
    buf1[0] = 100;
    buf2[0] = 300;
    buf1[1] = -1;
    buf2[1] = -3;
    buf1[2] = 1000;
    buf2[2] = -10010;
    buf1[3] = -123123;
    buf2[3] = 12345;
    buf1[4] = 2147483647;
    buf2[4] = 2147483647;
    buf1[5] = 2147483647;
    buf2[5] = -2147483648;
    buf1[6] = -2147483648;
    buf2[6] = 2147483647;

    for(auto i=0; i < BUFSIZE; i++){
        expected_out[i] = (int64_t)buf1[i] + buf2[i];
    }
    int res = fal::vect::elemwise_add(buf1, buf2, outbuf, BUFSIZE);
    REQUIRE(res == 0);

    for(size_t i=0; i < BUFSIZE; i++){
        REQUIRE(expected_out[i] == outbuf[i]);
    }


    deinit();
}


TEST_CASE("Test sum scalar"){
    init();

    int32_t scalar_values[] = {0, 100, -2147483648, 2147483647, -1};

    buf1[0] = 0;
    buf1[1] = -1;
    buf1[2] = -700;
    buf1[3] = -2147483648;
    buf1[4] = 2147483647;

    for(size_t i=0; i < sizeof(scalar_values)/sizeof(int32_t); i++){
        for(size_t j=0; j < BUFSIZE; j++){
            expected_out[j] = (int64_t)buf1[j] + scalar_values[i];
        }
        int res = fal::vect::elemwise_add(scalar_values[i], buf1, outbuf, BUFSIZE);
        REQUIRE(res == 0);
        for(size_t j=0; j < BUFSIZE; j++){
            INFO("Testing " << scalar_values[i] << " + " << buf1[j]);
            REQUIRE(expected_out[j] == outbuf[j]);
        }
    }
    deinit();
}


TEST_CASE("Test subtract"){
    init();

    buf1[0] = 100;
    buf2[0] = 300;
    buf1[1] = -1;
    buf2[1] = -3;
    buf1[2] = 1000;
    buf2[2] = -10010;
    buf1[3] = -123123;
    buf2[3] = 12345;
    buf1[4] = 2147483647;
    buf2[4] = 2147483647;
    buf1[5] = 2147483647;
    buf2[5] = -2147483648;
    buf1[6] = -2147483648;
    buf2[6] = 2147483647;

    for(size_t i=0; i<BUFSIZE; i++){
        expected_out[i] = (int64_t)buf1[i] - buf2[i];
    }
    int res = fal::vect::elemwise_sub(buf1, buf2, outbuf, BUFSIZE);
    REQUIRE(res == 0);
    for(auto i=0; i<BUFSIZE; i++){
        REQUIRE(expected_out[i] == outbuf[i]);
    }
    deinit();
}


TEST_CASE("Test subtract scalar") {
    init();
    buf1[0] = 100;
    buf2[0] = 300;
    buf1[1] = -1;
    buf2[1] = -3;
    buf1[2] = 1000;
    buf2[2] = -10010;
    buf1[3] = -123123;
    buf2[3] = 12345;
    buf1[4] = 2147483647;
    buf2[4] = 2147483647;
    buf1[5] = 2147483647;
    buf2[5] = -2147483648;
    buf1[6] = -2147483648;
    buf2[6] = 2147483647;

    for(auto i=0; i<6; i++){
        int res = fal::vect::elemwise_sub(buf1[i], buf2, outbuf, BUFSIZE);
        REQUIRE(res == 0);

        for(auto j=0; j < BUFSIZE; j++){
            expected_out[j] = (int64_t)buf1[i] - buf2[j];
            REQUIRE(outbuf[j] == expected_out[j]);
        }

        res = fal::vect::elemwise_sub(buf2, buf1[i], outbuf, BUFSIZE);
        REQUIRE(res == 0);

        for(auto j=0; j < BUFSIZE; j++){
            expected_out[j] = (int64_t)buf2[j] - buf1[i];
            REQUIRE(outbuf[j] == expected_out[j]);
        }

    }
    deinit();
}


TEST_CASE("Test multiply"){
    init();
    buf1[0] = 100;
    buf2[0] = 300;
    buf1[1] = -1;
    buf2[1] = -3;
    buf1[2] = 1000;
    buf2[2] = -10010;
    buf1[3] = -123123;
    buf2[3] = 12345;
    buf1[4] = 2147483647;
    buf2[4] = 2147483647;
    buf1[5] = 2147483647;
    buf2[5] = -2147483648;
    buf1[6] = -2147483648;
    buf2[6] = 2147483647;

    for(auto i=0; i < BUFSIZE; i++){
        expected_out[i] = (int64_t)buf1[i] * buf2[i];
    }

    int res = fal::vect::elemwise_mul(buf1, buf2, outbuf, BUFSIZE);

    REQUIRE(res == 0);

    for(auto i=0; i < BUFSIZE; i++){
        REQUIRE(expected_out[i] == outbuf[i]);
    }
    deinit();
}

TEST_CASE("Test multiply scalar") {
    init();
    buf1[0] = 100;
    buf2[0] = 300;
    buf1[1] = -1;
    buf2[1] = -3;
    buf1[2] = 1000;
    buf2[2] = -10010;
    buf1[3] = -123123;
    buf2[3] = 12345;
    buf1[4] = 2147483647;
    buf2[4] = 2147483647;
    buf1[5] = 2147483647;
    buf2[5] = -2147483648;
    buf1[6] = -2147483648;
    buf2[6] = 2147483647;

    for(auto i=0; i < 6; i++){
        int res = fal::vect::elemwise_mul(buf1[i], buf2, outbuf, BUFSIZE);
        REQUIRE(res == 0);

        for(auto j=0; j < BUFSIZE; j++){
            expected_out[j] = (int64_t)buf1[i]*buf2[j];
            REQUIRE(expected_out[j] == outbuf[j]);
        }
    }
    deinit();
}


TEST_CASE("Test division") {
    init();
    buf1[0] = 100;
    buf2[0] = 300;
    buf1[1] = -1;
    buf2[1] = -3;
    buf1[2] = 1000;
    buf2[2] = -10010;
    buf1[3] = -123123;
    buf2[3] = 12345;
    buf1[4] = 2147483647;
    buf2[4] = 2147483647;
    buf1[5] = 2147483647;
    buf2[5] = -2147483648;
    buf1[6] = -2147483648;
    buf2[6] = 2147483647;

    int32_t* div_outbuf = fal::vect::allocate<int32_t>(BUFSIZE);

    for(auto i=0; i<BUFSIZE; i++){
        expected_out[i] = buf1[i] / buf2[i];
    }

    int res = fal::vect::elemwise_div(buf1, buf2, div_outbuf, BUFSIZE);

    REQUIRE(res == 0);

    for(auto i=0; i<BUFSIZE; i++){
        INFO("Testing " << buf1[i] << " / " << buf2[i]);
        REQUIRE(expected_out[i] == div_outbuf[i]);
    }


    fal::vect::deallocate<int32_t>(div_outbuf);
    deinit();
}


TEST_CASE("Test division scalar") {
    init();
    buf1[0] = 100;
    buf2[0] = 300;
    buf1[1] = -1;
    buf2[1] = -3;
    buf1[2] = 1000;
    buf2[2] = -10010;
    buf1[3] = -123123;
    buf2[3] = 12345;
    buf1[4] = 2147483647;
    buf2[4] = 2147483647;
    buf1[5] = 2147483647;
    buf2[5] = -2147483648;
    buf1[6] = -2147483648;
    buf2[6] = 2147483647;
    int32_t* div_outbuf = fal::vect::allocate<int32_t>(BUFSIZE);
    for(auto i=0; i<7; i++){
        int res = fal::vect::elemwise_div(buf1[i], buf2, div_outbuf, BUFSIZE);
        REQUIRE(res == 0);

        for(auto j=0; j<BUFSIZE; j++){
            expected_out[j] = buf1[i] / buf2[j];
            REQUIRE(expected_out[j] == div_outbuf[j]);
        }

        res = fal::vect::elemwise_div(buf2, buf1[i], div_outbuf, BUFSIZE);

        for(auto j=0; j<BUFSIZE; j++) {
            expected_out[j] = MIN((int64_t)buf2[j] / buf1[i], 2147483647);
            REQUIRE(expected_out[j] == div_outbuf[j]);
        }
    }

    fal::vect::deallocate<int32_t>(div_outbuf);
    deinit();
}