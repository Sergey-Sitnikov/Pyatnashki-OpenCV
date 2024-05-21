#include <map>
#include <vector>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <algorithm>

#include "pytnashki.h"

using namespace std;

Pyatnashki::Pyatnashki(int w, int h, int m)
    : width_(w), height_(h), number_row_(m)
{
    if (width_ > height_)
    {
        width_side_field_ = (width_ - height_) / 2;
    }
    else
    {
        cout << "высота поля больше ширины" << endl;
        return;
    }
    if (height_ % number_row_ == 0)
        side_square_ = height_ / number_row_;
    else
        side_square_ = (height_ / number_row_) + 1;
    x_ = width_side_field_ / 2;
    y_ = height_ * 0.8;

    keyboard_["up"] = {x_ - 40, y_ - 80, x_ + 35, y_ - 5};
    keyboard_["left"] = {x_ - 120, y_, x_ - 45, y_ + 75};
    keyboard_["right"] = {x_ + 40, y_, x_ + 115, y_ + 75};
    keyboard_["down"] = {x_ - 40, y_, x_ + 35, y_ + 75};
    keyboard_["start"] = {x_ - 80, y_ - 200, x_ - 5, y_ - 125};
    keyboard_["stop"] = {x_ - 0, y_ - 200, x_ + 75, y_ - 125};
}

void Pyatnashki::FillingSheet()
{
    for (int r = 0; r < height_; r += side_square_)
    {
        for (int c = width_side_field_; c < (width_side_field_ + number_row_ * side_square_); c += side_square_)
        {
            if (sheet_.size() < number_row_)
                sheet_.push_back({c, r});
            else
                sheet_.push_back({c, r + 25});
        }
    }
    empty_square_ = sheet_.size() - 1;
    sheet_control_ = sheet_;
}

int Pyatnashki::GetSideSquare() const
{
    return side_square_;
}

int Pyatnashki::GetWidthSideField() const
{
    return width_side_field_;
}

pair<int, int> Pyatnashki::GetSheet(int i) const
{
    return sheet_[i];
}

void Pyatnashki::MovePosition(int a)
{
    static int empty = empty_square_;
    swap(sheet_[VirtPos(a)], sheet_[empty]);
    empty_square_ = a;
}

int Pyatnashki::GetSheetSize() const
{
    return sheet_.size();
}

void Pyatnashki::Mixing()
{
    vector<int> var;
    int pos = 0;
    int i = 0;
    for (int j = 0; j < 1000; ++j)
    {
        pos = empty_square_ - number_row_;
        if (CheckPosition(pos))
            var.push_back(pos);
        pos = empty_square_ - 1;
        if (CheckPosition(pos))
            var.push_back(pos);
        pos = empty_square_ + number_row_;
        if (CheckPosition(pos))
            var.push_back(pos);
        pos = empty_square_ + 1;
        if (CheckPosition(pos))
            var.push_back(pos);

        i = ((rand() % 10) / (7 - var.size()));
        MovePosition(var[i]);
        var.clear();
        start_ = true;
    }
}

bool Pyatnashki::CheckPosition(int pos)
{
    if (pos >= 0 && pos <= sheet_.size() - 1)
    {
        int row_checked = empty_square_ / number_row_;
        int col_checked = empty_square_ % number_row_;

        if (row_checked < number_row_ - 1 && row_checked >= 0 && pos - empty_square_ == number_row_)
            return true;
        if (row_checked >= 1 && row_checked <= number_row_ - 1 && pos - empty_square_ == -number_row_)
            return true;
        if (col_checked < number_row_ - 1 && col_checked >= 0 && pos - empty_square_ == 1)
            return true;
        if (col_checked >= 1 && col_checked <= number_row_ && pos - empty_square_ == -1)
            return true;
    }
    return false;
}

map<string, vector<int>> Pyatnashki::GetKeyboard() const
{
    return keyboard_;
}

int Pyatnashki::GetEmptySquare() const
{
    return empty_square_;
}

int Pyatnashki::GetNumberRow() const
{
    return number_row_;
}

vector<pair<int, int>> Pyatnashki::GetSheetVector() const
{
    return sheet_;
}

vector<pair<int, int>> Pyatnashki::GetSheetControl() const
{
    return sheet_control_;
}

void Pyatnashki::Interface(string key)
{
    int pos = 0;
    if (key == "up")
    {
        pos = empty_square_ - number_row_;
        if (CheckPosition(pos) && sheet_ != sheet_control_)
            MovePosition(pos);
    }
    else if (key == "down")
    {
        pos = empty_square_ + number_row_;
        if (CheckPosition(pos) && sheet_ != sheet_control_)
            MovePosition(pos);
    }
    else if (key == "right")
    {
        pos = empty_square_ + 1;
        if (CheckPosition(pos) && sheet_ != sheet_control_)
            MovePosition(pos);
    }
    else if (key == "left")
    {
        pos = empty_square_ - 1;
        if (CheckPosition(pos) && sheet_ != sheet_control_)
            MovePosition(pos);
    }
    else if (key == "start")
        Mixing();
    else if (key == "stop")
        exit_ = true;
}

int Pyatnashki::VirtPos(int pos) const
{
    int virt_pos = 0;
    for (int i = 0; i <= GetSheetSize(); ++i)
    {
        if (sheet_[i] == sheet_control_[pos])
        {
            virt_pos = i;
            break;
        }
    }
    return virt_pos;
}

bool Pyatnashki::GetStart()
{
    return start_;
}

bool Pyatnashki::GetExit(){
    return exit_;
}