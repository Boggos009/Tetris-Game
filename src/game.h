#pragma once
#include "grid.h"
#include "position.h"
#include "blocks.cpp"

class Game
{
private:
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    bool IsBlockOutside();
    void LockBlock();
    bool BlockFits();
    void Reset();
    void UpdateScore(int linesCleared , int moveDownPoints);
    std::vector<Block> GetAllBlocks();
    Block GetRandomBlock();
    Grid grid;
    void MoveBlockLeft();
    void MoveBlockRight();
    Sound clearSound;
    Sound rotateSound;
public:
    Game();
    ~Game();
    void Draw();
    void HandleInput();
    void MoveBlockDown();
    void RotateBlock();
    bool gameOver;
    int score;
    Music music;
};