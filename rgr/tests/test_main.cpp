#include "../src/analyzer.hpp"
#include <cassert>
#include <iostream>

void test_clean_word() {
    assert(clean_word("Hello,") == "hello");
    assert(clean_word("World123!!!") == "world");
    assert(clean_word("...Word...") == "word");
    std::cout << "Тест clean_word пройден!" << std::endl;
}

void test_analyze_text() {
    std::string text = "apple orange apple banana orange apple";
    auto res = analyze_text(text);
    
    // Проверяем сортировку по убыванию
    assert(res.size() == 3);
    assert(res[0].word == "apple" && res[0].count == 3);
    assert(res[1].word == "orange" && res[1].count == 2);
    assert(res[2].word == "banana" && res[2].count == 1);
    std::cout << "Тест analyze_text пройден!" << std::endl;
}

int main() {
    std::cout << "--- Запуск UNIT-тестов ---" << std::endl;
    test_clean_word();
    test_analyze_text();
    std::cout << "Все тесты успешно пройдены!" << std::endl;
    return 0;
}
