#pragma once

#include <raylib.h>
#include <vector>
#include "Grid.hpp"
#include "Block.hpp"
#include "Color.hpp"
#include "Blocks.cpp"

class Game
{
public:
    Game();
    ~Game();
    Block GetRandomBlock();
    std::vector<Block> GetAllBlocks();
    void Draw();
    void HandleInput();
    bool IsBlockOutside();
    void MoveBlockLeft();
    void MoveBlockRight();
    void MoveBlockDown();
    void RotateBlock();
    void LockBlock();
    bool BlockFits();
    void UpdatingScore(int lines_cleared, int move_down_points);
    Grid grid;
    bool game_over;
    int score;
    Music music;
    Sound rotate_sound;
    Sound clear_sound;

private:
    std::vector<Block> blocks;
    Block current_block;
    Block next_block;
    void Reset();
};