#include "game.h"
#include <random>
Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock=GetRandomBlock();
    nextBlock=GetRandomBlock();
    gameOver = false;
    score = 0;
    InitAudioDevice();
    music = LoadMusicStream("music.mp3");
    PlayMusicStream(music);
    clearSound = LoadSound("clear.mp3");
    rotateSound = LoadSound("rotate.mp3");
}

Game::~Game()
{
    UnloadMusicStream(music);
    UnloadSound(clearSound);
    UnloadSound(rotateSound);
    CloseAudioDevice();
}

Block Game::GetRandomBlock()
{
    if(blocks.empty())
    {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand()% blocks.size();
    
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw(11,11);
    switch (nextBlock.id)
    {
    case 3:
        nextBlock.Draw(255,290);
        break;
    case 4:
        nextBlock.Draw(255,280);
        break;
    default:
        nextBlock.Draw(270,270);
        break;
    }
}


std::vector<Block> Game::GetAllBlocks()
{
    return {IBlock() , JBlock() , OBlock() , SBlock() , TBlock() , ZBlock()};
}

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();
    if(gameOver&& keyPressed!=0)
    {
        gameOver = false;
        Reset();
    }
    switch(keyPressed)
    {
    case KEY_LEFT:
        MoveBlockLeft();
        break;
    case KEY_RIGHT:
        MoveBlockRight();
        break;
    case KEY_DOWN:
        MoveBlockDown();
        UpdateScore(0 , 1);
        break;
    case KEY_UP:
        RotateBlock();
        break;
    }
}

void Game::MoveBlockLeft()
{
    if(!gameOver)
    {
        currentBlock.Move(0,-1);
        if(IsBlockOutside()||!BlockFits())
        {
            currentBlock.Move(0,1);
        }
    }

}

void Game::MoveBlockRight()
{
    if(!gameOver)
    {
        currentBlock.Move(0,1);
        if(IsBlockOutside()||!BlockFits())
        {
            currentBlock.Move(0,-1);
        }
    }
    
}

void Game::MoveBlockDown()
{
    if(!gameOver)
    {
        currentBlock.Move(1,0);
        if(IsBlockOutside()||!BlockFits())
        {
            currentBlock.Move(-1 , 0);
            LockBlock();
        }
        
    }
    
}



bool Game::IsBlockOutside()
{
    std::vector<Position> tiles = currentBlock.GetCellPostions();

    for(Position &item: tiles)
    {
        if(grid.IsCellOut(item.row , item.column))
        {
            return true;
        }
    }
    return false;
}

void Game::LockBlock()
{
    std::vector<Position> tiles = currentBlock.GetCellPostions();
    for(Position &item: tiles)
    {
        grid.grid[item.row] [item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    nextBlock = GetRandomBlock();
    if(BlockFits()==false)
    {
        gameOver = true;
    }
    int completed = grid.ClearFullRows();
    if(completed>0)
    {
        UpdateScore(completed , 0);
        PlaySound(clearSound);
    }
    
}

bool Game::BlockFits()
{
    std::vector<Position> tiles = currentBlock.GetCellPostions();

    for(Position&item : tiles)
    {
        if(!grid.IsCellEmpty(item.row , item.column))
        {
            return false;
        }
    }
    return true;
}

void Game::Reset()
{
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
    switch (linesCleared)
    {
    case 1:
        score+=100;
        break;
    case 2:
        score+=300;
        break;
    case 3:
        score+=500;
        break;
    default:
        break;
    }
    score+=moveDownPoints;
}

void Game::RotateBlock()
{
    if(!gameOver)
    {
        currentBlock.Rotate();
        if(IsBlockOutside()||BlockFits()==false)
        {
            currentBlock.UndoRotation();
        }
        else
        {
            PlaySound(rotateSound);
        }
    }

}