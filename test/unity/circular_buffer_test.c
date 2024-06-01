#include "unity.h"

void setUp(void) {
}

void tearDown(void) {
}

void test(void) {
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test);
    return UNITY_END();
}

