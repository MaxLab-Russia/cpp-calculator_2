// В этом файле объявления функций.
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>

// 1. Сначала объявляем тип данных для калькулятора
using Number = double;

// 2. Теперь компилятор знает, что такое Number, и не выдаст ошибку
bool ReadNumber(Number& result);

// 3. Объявление главного цикла
void RunCalculatorCycle();

#endif // CALCULATOR_H
