#include "Block.hpp"
#include "Color.hpp"
Block::Block()
{
    cell_size = 30;
    rotation_state = 0;
    colors = GetCellColors();
    row_offset = 0;
    column_offset = 0;
}

void Block::Draw(int offset_x, int offset_y)
{
    std::vector<Position> tiles = GetCellPosition();
    for (Position item : tiles)
    {
        DrawRectangle(item.column * cell_size + offset_x, item.row * cell_size + offset_y, cell_size - 1, cell_size - 1, colors[id]);
    }
}

void Block::Move(int row, int column)
{
    row_offset += row;
    column_offset += column;
}

void Block::Rotate()
{
    rotation_state++;
    rotation_state %= cells.size();
}

void Block::UndoRotation()
{
    rotation_state--;
    if (rotation_state == -1)
    {
        rotation_state = cells.size() - 1;
    }
}
std::vector<Position> Block::GetCellPosition()
{
    std::vector<Position> tiles = cells[rotation_state];
    std::vector<Position> new_positions = cells[rotation_state];
    for (auto &pos : new_positions)
    {
        pos.row += row_offset;
        pos.column += column_offset;
    }
    return new_positions;
}