#include "calculator.h"
#include <limits>
#include <string>
#include <cmath>
#include <sstream>
#include <iostream>
#include <unordered_set>


// Функция чтения числа из std::cin после операторов
bool ReadNumber(Number& result) {
    if (std::cin >> result) {
        return true;
    } else {
        return false;
    }
}


// Вспомогательная функция для проверки, является ли строка числом
bool StringToNumber(const std::string& str, Number& result) {
    std::istringstream iss(str);
    char remaining_char;
    if ((iss >> result) && !(iss >> remaining_char)) {
        return true;
    }
    return false;
}

void RunCalculatorCycle() {
    Number current_result = 0.0;
    Number memory = 0.0;
    bool is_memory_set = false; 
    bool has_number = false; 
    std::string line;

    // Читаем ввод строго построчно
    while (std::getline(std::cin, line)) {
        std::istringstream line_stream(line);
        std::string command;
        bool error_occurred = false;

        while (line_stream >> command) {
            // 1. Обработка команд разделения, сброса и выхода
            if (command == ":") {
                continue;
            }
            if (command == "q" || command == "exit") {
                return;
            }
            if (command == "c") {
                current_result = 0.0; 
                has_number = false; 
                continue;
            }

            // 2. Обработка операций с памятью
            if (command == "MS" || command == "s") {
                memory = current_result;
                is_memory_set = true;
                continue;
            }
            if (command == "MR" || command == "l") { 
                if (!is_memory_set) {
                    std::cerr << "Error: Memory is empty" << std::endl;
                } else {
                    current_result = memory;
                    has_number = true; 
                }
                continue;
            }
            if (command == "MC") {
                memory = 0.0;
                is_memory_set = false;
                continue;
            }
            if (command == "=") {
                std::cout << current_result << std::endl;
                has_number = false; 
                continue;
            }

            // 3. Обработка арифметических операторов
            if (std::unordered_set<std::string>{"+", "-", "*", "/", "**"}.count(command)) {
                std::string op = command;
                Number next_number = 0.0;
                std::string next_token;

                // Пытаемся прочитать следующий токен как число
                if (line_stream >> next_token) {
                    if (StringToNumber(next_token, next_number)) {
                        if (op == "+") current_result += next_number;
                        else if (op == "-") current_result -= next_number;
                        else if (op == "*") current_result *= next_number;
                        else if (op == "**") current_result = std::pow(current_result, next_number);
                        else if (op == "/") current_result /= next_number;
                        
                        has_number = true;
                        continue;
                    }
                }
                
                // Если не смогли прочитать число после оператора
                std::cerr << "Error: Numeric operand expected" << std::endl;
                error_occurred = true;
                break;
            }

            // 4. Если токен не подошел под команды и операторы
            if (StringToNumber(command, current_result)) {
                has_number = true; 
                continue;
            } else {
                if (!has_number) {
                    std::cerr << "Error: Numeric operand expected" << std::endl;
                } else {
                    std::cerr << "Error: Unknown token " << command << std::endl;
                }
                error_occurred = true;
                break;
            }
        }

        // Если в процессе разбора строки произошла ошибка, проверяем, был ли в ней знак "="
        if (error_occurred) {
            current_result = 0.0; // Сбрасываем результат при ошибке
            has_number = false;
            
            // Ищем, есть ли дальше в этой же строке знак "="
            // Мы можем искать как в остатке line_stream, так и просто подстроку в исходной строке
            if (line.find('=') != std::string::npos) {
                std::cout << current_result << std::endl; // Выведет 0
            }
        }
    }
}
