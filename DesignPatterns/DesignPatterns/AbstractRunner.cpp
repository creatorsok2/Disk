#include "pch.h"
#include "AbstractRunner.h"
#include "AbstractFactory.h"

void AbstractRunner::Main()
{
	MazeGame game;
	auto aMaze = game.CreateMaze(BombedMazeFactory());
	ASSERT(aMaze == nullptr);
}