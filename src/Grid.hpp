#pragma once

#include <raylib.h>
#include <vector>
class Grid
{
public:
    Grid();
    void initialize();
    void Draw();
    bool IsCellEmpty(int row, int column);
    bool IsCellOutSide(int row, int column);
    int ClearFullRows();
    int cells[20][10];

private:
    bool IsRowFull(int row);
    void ClearRow(int row);
    void MoveRowDown(int row, int num_rows);
    int rows;
    int columns;
    int cell_size;
    std::vector<Color> colors;
};
