#include "analyzer.hpp"
#include <iostream>

int main() {
    init_logger("app.log");
    log_message(LogLevel::INFO, "Запуск программы частотного анализа текста...");

    try {
        // Шаг 1: Чтение конфигурации (Критерий на «5»)
        auto config = parse_config("config.txt");
        std::string input_file = config["input_file"];
        std::string output_file = config["output_file"];

        // Шаг 2: Валидация параметров конфига (Критерий на «4»)
        if (input_file.empty() || output_file.empty()) {
            log_message(LogLevel::ERROR, "Ошибка конфига: отсутствуют параметры input_file или output_file.");
            return 1;
        }

        // Шаг 3: Основная работа алгоритма
        if (!process_files(input_file, output_file)) {
            log_message(LogLevel::ERROR, "Программа завершилась с ошибкой выполнения.");
            return 1;
        }

    } catch (const std::exception& e) {
        log_message(LogLevel::ERROR, std::string("Критическое исключение: ") + e.what());
        return 1;
    }

    log_message(LogLevel::INFO, "Программа успешно завершила работу.");
    return 0;
}
