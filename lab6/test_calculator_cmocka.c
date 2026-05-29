#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <math.h>
#include "calculator.h"


static void test_add_positive(void **state) {
    (void)state;
    assert_int_equal(add(5, 3), 8);
    assert_int_equal(add(100, 200), 300);
}

static void test_add_negative(void **state) {
    (void)state;
    assert_int_equal(add(-5, -3), -8);
    assert_int_equal(add(-10, 5), -5);
}

static void test_add_zero(void **state) {
    (void)state;
    assert_int_equal(add(0, 10), 10);
    assert_int_equal(add(0, 0), 0);
}

static void test_subtract_normal(void **state) {
    (void)state;
    assert_int_equal(subtract(10, 4), 6);
    assert_int_equal(subtract(100, 50), 50);
}

static void test_subtract_negative(void **state) {
    (void)state;
    assert_int_equal(subtract(5, 10), -5);
    assert_int_equal(subtract(-5, -3), -2);
}

static void test_multiply_normal(void **state) {
    (void)state;
    assert_int_equal(multiply(6, 7), 42);
    assert_int_equal(multiply(10, 10), 100);
}

static void test_multiply_by_zero(void **state) {
    (void)state;
    assert_int_equal(multiply(100, 0), 0);
    assert_int_equal(multiply(0, 100), 0);
}

static void test_multiply_negative(void **state) {
    (void)state;
    assert_int_equal(multiply(-4, 5), -20);
    assert_int_equal(multiply(-4, -5), 20);
}

static void test_divide_normal(void **state) {
    (void)state;
    assert_float_equal(divide(10, 2), 5.0, 0.0001);
    assert_float_equal(divide(7, 2), 3.5, 0.0001);
}

static void test_divide_by_zero(void **state) {
    (void)state;
    assert_float_equal(divide(10, 0), 0.0, 0.0001);
    assert_float_equal(divide(-5, 0), 0.0, 0.0001);
}

static void test_divide_negative(void **state) {
    (void)state;
    assert_float_equal(divide(-10, 2), -5.0, 0.0001);
    assert_float_equal(divide(10, -2), -5.0, 0.0001);
}

static void test_error_messages(void **state) {
    (void)state;
    assert_string_equal(get_error_message(0), "Success");
    assert_string_equal(get_error_message(1), "Division by zero");
    assert_string_equal(get_error_message(2), "Invalid input");
    assert_string_equal(get_error_message(99), "Unknown error");
}

static void test_prime_numbers(void **state) {
    (void)state;
    assert_true(is_prime(2));
    assert_true(is_prime(3));
    assert_true(is_prime(5));
    assert_true(is_prime(7));
    assert_true(is_prime(11));
    assert_true(is_prime(13));
    assert_true(is_prime(17));
    assert_true(is_prime(19));
    assert_true(is_prime(97));
}

static void test_composite_numbers(void **state) {
    (void)state;
    assert_false(is_prime(1));
    assert_false(is_prime(4));
    assert_false(is_prime(6));
    assert_false(is_prime(8));
    assert_false(is_prime(9));
    assert_false(is_prime(10));
    assert_false(is_prime(15));
    assert_false(is_prime(21));
}

static void test_negative_and_zero(void **state) {
    (void)state;
    assert_false(is_prime(0));
    assert_false(is_prime(-1));
    assert_false(is_prime(-5));
    assert_false(is_prime(-10));
}

int main(void) {
    const struct CMUnitTest tests[] = {
        
        cmocka_unit_test(test_add_positive),
        cmocka_unit_test(test_add_negative),
        cmocka_unit_test(test_add_zero),
        
        
        cmocka_unit_test(test_subtract_normal),
        cmocka_unit_test(test_subtract_negative),
        
        
        cmocka_unit_test(test_multiply_normal),
        cmocka_unit_test(test_multiply_by_zero),
        cmocka_unit_test(test_multiply_negative),
        
        
        cmocka_unit_test(test_divide_normal),
        cmocka_unit_test(test_divide_by_zero),
        cmocka_unit_test(test_divide_negative),
        
        
        cmocka_unit_test(test_error_messages),
        
        
        cmocka_unit_test(test_prime_numbers),
        cmocka_unit_test(test_composite_numbers),
        cmocka_unit_test(test_negative_and_zero),
    };
    
    return cmocka_run_group_tests(tests, NULL, NULL);
}