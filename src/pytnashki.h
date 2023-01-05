#pragma once

#include <map>
#include <vector>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <algorithm>

class Pyatnashki
{
public:
    Pyatnashki(int w, int h, int m);

    void FillingSheet();                                         // заполненяет таблицы координатами ячеек
    int GetSideSquare() const;                                   // возвращает длину/ширину ячейки
    int GetWidthSideField() const;                               // возвращает ширину бокового поля
    std::pair<int, int> GetSheet(int i) const;                   // возвращает таблицу
    void MovePosition(int a);                                    // перемещает ячейку
    int GetSheetSize() const;                                    // возвращает размер таблицы
    void Mixing();                                               // перемешивает ячейки
    bool CheckPosition(int pos);                                 // проверяет возможность перемещения ячейки
    std::map<std::string, std::vector<int>> GetKeyboard() const; // возвращает клавиатуру
    int GetEmptySquare() const;                                  // возвращает индекс пустой ячейки
    int GetNumberRow() const;                                    // возвращаетколичество ячеек по длине/высоте
    std::vector<std::pair<int, int>> GetSheetVector() const;     // возвращает таблицу
    std::vector<std::pair<int, int>> GetSheetControl() const;    // возвращает таблицу с данными для проверки
    void Interface(std::string key);                             // осуществляет взаимодействие с клавиатурой
    int VirtPos(int pos) const;                                  // вспомогательный метод для перемещения по таблице
    bool GetStart();                                             // показывает была ли нажата кнопка "start"
    bool GetExit();                                              // активация выхода

private:
    std::vector<std::pair<int, int>> sheet_;           // таблица с координатами
    std::vector<std::pair<int, int>> sheet_control_;   // таблица с координатами для проверки выигрыша
    int width_side_field_ = 0;                         // ширина бокового поля
    int width_ = 0;                                    // ширина всего поля
    int height_ = 0;                                   // высота всего поля
    int side_square_ = 0;                              // ширина и высота квадрата
    int number_row_ = 0;                               // количество квадратов в строке и столбце
    int empty_square_ = 0;                             // индекс пустого поля
    bool start_ = false;                               // индикатор запуска игры
    bool exit_ = false;                                // индикатор выхода
    int x_ = 0;                                        // вспомогательная ось для размещения клавиатуры
    int y_ = 0;                                        // вспомогательная ось для размещения клавиатуры
    std::map<std::string, std::vector<int>> keyboard_; // клавиатура
};