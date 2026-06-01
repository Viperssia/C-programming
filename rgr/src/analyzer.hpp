#pragma once
#include <string>
#include <vector>
#include <map>


struct WordFreq {
    std::string word;
    int count;
};


enum class LogLevel { INFO, WARNING, ERROR };


void init_logger(const std::string& log_path);
void log_message(LogLevel level, const std::string& message);

std::map<std::string, std::string> parse_config(const std::string& config_path);
std::string clean_word(const std::string& raw_word);
std::vector<WordFreq> analyze_text(const std::string& text);
bool process_files(const std::string& input_path, const std::string& output_path);
