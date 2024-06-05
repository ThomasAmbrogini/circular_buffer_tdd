#include "unity.h"

#include "circular_buffer.h"

/*
 * Circular buffer that holds a series of ints
 *
 *  1.  how is initialization done? and the init value?
 *  2.  Is it dynamic or static? 
 *  3.  Handling concurrent calls to the function
 *  4.  What should i do if i read before having an element inside?
 *      *   Runtime error?
 *      *   Error code? How should this be done? Returning an enum instead
 *          of the value and passing the extracted element with the 
 *          parameters?
 *  5.  
 *  
 *
 *
 * Problems
 * 1.   I can't really have the buffer passed in this way if more clients can
 *      use the module
 *      *   Is this think to be a single circular buffer for all the system?
 *          Then it's fine to have a static buffer inside the function,
 *          otherwise it will be a problem
 *
 */

static int32_t buffer[32];

static void resetBuffer(void);
static void insertMultipleElements(int32_t value_to_insert, 
                                   uint32_t number_of_values);

void setUp(void) {
    resetBuffer();
    circularBufferInit(buffer, sizeof(buffer)/sizeof(int32_t));
}

void tearDown(void) {
}

void circularBufferInitTest(void) {
    int32_t buffer[32];
    int32_t value = 4; 
    int32_t retrieved_value = 0; 

    circularBufferInit(buffer, sizeof(buffer)/sizeof(int32_t));
    circularBufferInsert(value);
    retrieved_value = circularBufferGet();

    TEST_ASSERT_EQUAL_INT32(value, retrieved_value);
}

void getAnElement(void) {
    int32_t value;
    circularBufferInsert(4);
    value = circularBufferGet();
    TEST_ASSERT_EQUAL_INT32(4, value);
}

void insertAnElement(void) {
    int32_t value_to_insert = 4;
    int32_t retrieved_value;
    circularBufferInsert(value_to_insert);
    retrieved_value = circularBufferGet();
    TEST_ASSERT_EQUAL_INT32(4, retrieved_value);
}

void insertTwoElementsAndGetOne(void) {
    int32_t first_value = 3;
    int32_t second_value = 4;
    int32_t first_retrieved_value = 0;
    int32_t second_retrieved_value = 0;

    circularBufferInsert(first_value);
    circularBufferInsert(second_value);

    first_retrieved_value = circularBufferGet(); 
    TEST_ASSERT_EQUAL_INT32(first_value, first_retrieved_value);
    second_retrieved_value = circularBufferGet(); 
    TEST_ASSERT_EQUAL_INT32(second_value, second_retrieved_value);
}

void readingBeforeFirstInsert(void) {
    int32_t retrieved_value = 0;
    retrieved_value = circularBufferGet();
    TEST_ASSERT_EQUAL_INT32(INT_MAX, retrieved_value);
}

void deletingUnreadElements(void) {
    int32_t retrieved_value = 0;
    insertMultipleElements(4, sizeof(buffer)/sizeof(int32_t)); 
    circularBufferInsert(5);
    retrieved_value = circularBufferGet();
    TEST_ASSERT_EQUAL_INT32(5, retrieved_value);
}

static void resetBuffer(void) {
    for (int i = 0; i < sizeof(buffer)/sizeof(int32_t); ++i) {
        buffer[i] = 0;
    }
}

static void insertMultipleElements(int32_t value_to_insert, 
                                   uint32_t number_of_values) {
    for (int i = 0; i < number_of_values; ++i) {
        circularBufferInsert(value_to_insert);
    }
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(circularBufferInitTest);
    RUN_TEST(getAnElement);
    RUN_TEST(insertAnElement);
    RUN_TEST(insertTwoElementsAndGetOne);
    RUN_TEST(readingBeforeFirstInsert);
    RUN_TEST(deletingUnreadElements);
    return UNITY_END();
}

