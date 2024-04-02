#pragma once
#include <vector>
#include <map>
#include <raylib.h>
#include "Position.hpp"

class Block
{
public:
    Block();
    void Draw(int offset_x, int offset_y);
    void Move(int row, int column);
    void Rotate();
    void UndoRotation();
    std::vector<Position> GetCellPosition();

    std::map<int, std::vector<Position>> cells;
    int id;

private:
    int cell_size;
    int rotation_state;
    std::vector<Color> colors;
    int row_offset;
    int column_offset;
};