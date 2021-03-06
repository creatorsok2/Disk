#include "pch.h"
#include "AbstractRunner.h"
#include "MazeFactory.h"
#include "MazeGame.h"

void AbstractRunner::Main()
{
	MazeGame game;
	auto aMaze = game.CreateMaze(BombedMazeFactory());
	ASSERT(aMaze != nullptr);
}