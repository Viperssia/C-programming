#include "analyzer.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iostream>

static std::ofstream log_file;

void init_logger(const std::string& log_path) {
    log_file.open(log_path, std::ios::app);
}

void log_message(LogLevel level, const std::string& message) {
    std::string lvl_str;
    switch (level) {
        case LogLevel::INFO:    lvl_str = "[INFO] "; break;
        case LogLevel::WARNING: lvl_str = "[WARNING] "; break;
        case LogLevel::ERROR:   lvl_str = "[ERROR] "; break;
    }
    if (log_file.is_open()) {
        log_file << lvl_str << message << std::endl;
    }
    std::cout << lvl_str << message << std::endl; 
}


std::map<std::string, std::string> parse_config(const std::string& config_path) {
    std::map<std::string, std::string> config;
    std::ifstream file(config_path);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть конфигурационный файл: " + config_path);
    }
    std::string line;
    while (std::getline(file, line)) {
        size_t delim = line.find('=');
        if (delim != std::string::npos) {
            std::string key = line.substr(0, delim);
            std::string value = line.substr(delim + 1);
            config[key] = value;
        }
    }
    return config;
}


std::string clean_word(const std::string& raw_word) {
    std::string cleaned;
    for (char ch : raw_word) {
        
        if (std::isalpha(static_cast<unsigned char>(ch)) || (ch & 0x80)) {
            cleaned += std::tolower(static_cast<unsigned char>(ch));
        }
    }
    return cleaned;
}


std::vector<WordFreq> analyze_text(const std::string& text) {
    std::map<std::string, int> freq_map;
    std::stringstream ss(text);
    std::string raw_word;

    while (ss >> raw_word) {
        std::string word = clean_word(raw_word);
        if (!word.empty()) {
            freq_map[word]++;
        }
    }

    std::vector<WordFreq> result;
    for (const auto& pair : freq_map) {
        result.push_back({pair.first, pair.second});
    }

    
    std::sort(result.begin(), result.end(), [](const WordFreq& a, const WordFreq& b) {
        return a.count > b.count;
    });

    return result;
}


bool process_files(const std::string& input_path, const std::string& output_path) {
    std::ifstream in_file(input_path);
    if (!in_file.is_open()) {
        log_message(LogLevel::ERROR, "Входной файл не найден: " + input_path);
        return false;
    }

    std::stringstream buffer;
    buffer << in_file.rdbuf();
    std::string text = buffer.str();
    in_file.close();

    if (text.empty()) {
        log_message(LogLevel::WARNING, "Входной файл пуст: " + input_path);
    }

    auto frequencies = analyze_text(text);

    std::ofstream out_file(output_path);
    if (!out_file.is_open()) {
        log_message(LogLevel::ERROR, "Не удалось создать выходной файл: " + output_path);
        return false;
    }

    for (const auto& item : frequencies) {
        out_file << item.word << ": " << item.count << "\n";
    }
    out_file.close();

    log_message(LogLevel::INFO, "Анализ успешно завершен. Результаты записаны в " + output_path);
    return true;
}
