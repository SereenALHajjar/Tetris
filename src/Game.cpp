#include "Game.hpp"
#include <random>
Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks();
    current_block = GetRandomBlock();
    next_block = GetRandomBlock();
    game_over = false;
    score = 0;
    InitAudioDevice();
    music = LoadMusicStream("sounds/music.mp3");
    PlayMusicStream(music);
    rotate_sound = LoadSound("sounds/rotate.mp3");
    clear_sound = LoadSound("sounds/clear.mp3");
}
Game::~Game()
{
    UnloadSound(rotate_sound);
    UnloadSound(clear_sound);
    UnloadMusicStream(music);
    CloseAudioDevice();
}
Block Game::GetRandomBlock()
{
    if (blocks.empty())
    {
        blocks = GetAllBlocks();
    }
    int rand_index = rand() % blocks.size();
    Block block = blocks[rand_index];
    blocks.erase(blocks.begin() + rand_index);
    return block;
}

std::vector<Block> Game::GetAllBlocks()
{
    return {TBlock(), ZBlock(), SBlock(), OBlock(), IBlock(), JBlock(), LBlock()};
}

void Game::Draw()
{
    grid.Draw();
    current_block.Draw(11, 11);
    switch (next_block.id)
    {
    case 3:
        next_block.Draw(255, 290);
        break;
    case 4:
        next_block.Draw(255, 280);
        break;
    default:
        next_block.Draw(270, 270);
        break;
    }
}

void Game::Reset()
{
    grid.initialize();
    blocks = GetAllBlocks();
    current_block = GetRandomBlock();
    next_block = GetRandomBlock();
    score = 0;
}
void Game::HandleInput()
{
    int key_pressed = GetKeyPressed();
    if (game_over && key_pressed != 0)
    {
        game_over = false;
        Reset();
    }
    if (key_pressed == KEY_LEFT)
        MoveBlockLeft();
    if (key_pressed == KEY_RIGHT)
        MoveBlockRight();
    if (key_pressed == KEY_DOWN)
    {
        MoveBlockDown();
        UpdatingScore(0, 1);
    }
    if (key_pressed == KEY_UP)
        RotateBlock();
}

bool Game::IsBlockOutside()
{
    std::vector<Position> tiles = current_block.GetCellPosition();
    for (Position item : tiles)
    {
        if (grid.IsCellOutSide(item.row, item.column))
        {
            return true;
        }
    }
    return false;
}

void Game::MoveBlockLeft()
{
    if (!game_over)
    {
        current_block.Move(0, -1);
        if (IsBlockOutside() || BlockFits() == false)
        {
            current_block.Move(0, 1);
        }
    }
}

void Game::MoveBlockRight()
{
    if (!game_over)
    {
        current_block.Move(0, 1);
        if (IsBlockOutside() || BlockFits() == false)
        {
            current_block.Move(0, -1);
        }
    }
}

void Game::MoveBlockDown()
{
    if (!game_over)
    {
        current_block.Move(1, 0);
        if (IsBlockOutside() || BlockFits() == false)
        {
            current_block.Move(-1, 0);
            LockBlock();
        }
    }
}

void Game::RotateBlock()
{
    if (!game_over)
    {
        current_block.Rotate();
        if (IsBlockOutside() || BlockFits() == false)
        {
            current_block.UndoRotation();
        }
        else
        {
            PlaySound(rotate_sound);
        }
    }
}

void Game::LockBlock()
{
    std::vector<Position> tiles = current_block.GetCellPosition();
    for (Position pos : tiles)
    {
        grid.cells[pos.row][pos.column] = current_block.id;
    }
    current_block = next_block;
    if (BlockFits() == false)
    {
        game_over = true;
        return;
    }
    next_block = GetRandomBlock();
    int rows_cleared = grid.ClearFullRows();
    if (rows_cleared)
    {
        PlaySound(clear_sound);
        UpdatingScore(rows_cleared, 0);
    }
}

bool Game::BlockFits()
{
    std::vector<Position> tiles = current_block.GetCellPosition();
    for (Position pos : tiles)
    {
        if (grid.IsCellEmpty(pos.row, pos.column) == false)
            return false;
    }
    return true;
}

void Game::UpdatingScore(int lines_cleared, int move_down_points)
{
    if (lines_cleared == 1)
        score += 100;
    else if (lines_cleared == 2)
        score += 300;
    else if (lines_cleared >= 3)
        score += 500;
    score += move_down_points;
}
