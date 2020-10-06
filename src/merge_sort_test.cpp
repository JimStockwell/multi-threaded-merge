// (c) 2020 Jim Stockwell
// This code is licensed under MIT license
// (see http://opensource.org/licenses/MIT for details)

//
// Uses the Catch library for testing.
// See https://github.com/catchorg/Catch2
//

#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

extern int *merge_sort(int *data, size_t len);

int isEqual(int *data1, int *data2, size_t num)
{
    return !memcmp(data1, data2, num * sizeof(int));
}

TEST_CASE("length 0")
{
    /* We are just testing that it doesn't crash */
    merge_sort(nullptr, 0);
}

TEST_CASE("lengths 1")
{
    int data[] = {5};
    int expected[] = {5};
    int len = sizeof(data) / sizeof(*data);

    REQUIRE(isEqual(merge_sort(data, len), expected, len));
}

TEST_CASE("length 2 - reverse order")
{
    int data[] = {2, 1};
    int expected[] = {1, 2};
    int len = 2;

    REQUIRE(isEqual(merge_sort(data, len), expected, len));
}

TEST_CASE("length 2 - in order")
{
    int data[] = {2, 3};
    int expected[] = {2, 3};
    int len = 2;

    REQUIRE(isEqual(merge_sort(data, len), expected, len));
}

TEST_CASE("length 4 - merge required, all right then all left")
{
    int data[] = {2, 3, 0, 1};
    int expected[] = {0, 1, 2, 3};
    int len = 4;

    REQUIRE(isEqual(merge_sort(data, len), expected, len));
}

TEST_CASE("length 10 - merge required, but no other sorting")
{
    int data[] = {1, 3, 4, 6, 8, 0, 2, 5, 7, 9};
    int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int len = 10;

    REQUIRE(isEqual(merge_sort(data, len), expected, len));
}

TEST_CASE("length 10 - merge and sort required")
{
    int data[] = {8, 6, 4, 2, 0, 3, 1, 5, 7, 9};
    int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int len = 10;

    REQUIRE(isEqual(merge_sort(data, len), expected, len));
}