#pragma once
#include <raylib.h>
#include "Colors.h"
#include <vector>
class Grid
{
private:
    int numRows;
    int numCols;
    int cellSize;
    std::vector <Color> colors;
    bool IsRowFull(int row);
    void ClearRow(int row);
    void MoveRowDown(int row , int numrows);
public:
    Grid();
    int grid[20][10];
    void Initialize();
    void Print();
    void Draw();
    bool IsCellOut(int row , int column);
    bool IsCellEmpty(int row , int column);
    int ClearFullRows();
};