#include "Grid.hpp"
#include "Color.hpp"
Grid::Grid()
{
    rows = 20;
    columns = 10;
    cell_size = 30;
    initialize();
    colors = GetCellColors();
}

void Grid::initialize()
{
    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column < columns; column++)
        {
            cells[row][column] = 0;
        }
    }
}

void Grid::Draw()
{
    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column < columns; column++)
        {
            DrawRectangle(column * cell_size + 11, row * cell_size + 11, cell_size - 1, cell_size - 1, colors[cells[row][column]]);
        }
    }
}

bool Grid::IsCellEmpty(int row, int column)
{
    return cells[row][column] == 0;
}

bool Grid::IsCellOutSide(int row, int column)
{
    if (row >= 0 && row < rows && column >= 0 && column < columns)
        return false;
    return true;
}

int Grid::ClearFullRows()
{
    int completed = 0;
    for (int row = rows - 1; row >= 0; row--)
    {
        if (IsRowFull(row))
        {
            ClearRow(row);
            completed++;
        }
        else if (completed > 0)
        {
            MoveRowDown(row, completed);
        }
    }
    return completed;
}

bool Grid::IsRowFull(int row)
{
    for (int column = 0; column < columns; column++)
    {
        if (cells[row][column] == 0)
            return false;
    }
    return true;
}

void Grid::ClearRow(int row)
{
    for (int column = 0; column < columns; column++)
    {
        cells[row][column] = 0;
    }
}

void Grid::MoveRowDown(int row, int num_rows)
{
    for (int column = 0; column < columns; column++)
    {
        cells[row + num_rows][column] = cells[row][column];
    }
    ClearRow(row);
}
