#include "pch.h"
#include "PrototypeRunner.h"
#include "MazeFactory.h"
#include "MazeGame.h"

void PrototypeRunner::Main()
{
	MazePrototypeFactory simpleMazeFactory(
		std::make_shared<Maze>(), std::make_shared<Wall>(),
		std::make_shared<Room>(), std::make_shared<Door>());

	MazeGame game;
	auto aMaze = game.CreateMaze(simpleMazeFactory);
	ASSERT(aMaze != nullptr);
}
