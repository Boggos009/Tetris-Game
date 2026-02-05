#pragma once
#include <map>
#include <vector>
#include "Colors.h"
#include "position.h"
class Block
{
private:
    int cellSize;
    std::vector<Color> colors;
    int rowOffset;
    int columnOffset;
    int rotationState;  
    
public:
    int id;
    Block();
    std::map <int , std::vector<Position>> cells;
    void Draw(int offsetX , int offsetY);
    void Move(int rows , int columns);
    std::vector<Position> GetCellPostions();
    void Rotate();
    void UndoRotation();
    
};