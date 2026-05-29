#include "calculator.h"
#include <stdlib.h>
#include <string.h>

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

double divide(int a, int b) {
    if (b == 0) {
        return 0.0;  // ошибка: деление на ноль
    }
    return (double)a / b;
}

char* get_error_message(int error_code) {
    switch(error_code) {
        case 0: return "Success";
        case 1: return "Division by zero";
        case 2: return "Invalid input";
        default: return "Unknown error";
    }
}

int is_prime(int n) {
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;
    
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}