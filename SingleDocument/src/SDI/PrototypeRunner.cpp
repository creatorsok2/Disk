#include "pch.h"
#include "PrototypeRunner.h"
#include "MazeFactory.h"
#include "MazeGame.h"

void PrototypeRunner::Main()
{
	{
		MazePrototypeFactory SimpleMazeFactory(
			std::make_shared<Maze>(), std::make_shared<Wall>(),
			std::make_shared<Room>(), std::make_shared<Door>());

		MazeGame game;
		auto aMaze = game.CreateMaze(SimpleMazeFactory);
		ASSERT(aMaze != nullptr);
	}

	{
		MazePrototypeFactory BombedMazeFactory(
			std::make_shared<Maze>(), std::make_shared<BombedWall>(),
			std::make_shared<RoomWithABomb>(), std::make_shared<Door>());

		MazeGame game;
		auto aMaze = game.CreateMaze(BombedMazeFactory);
		ASSERT(aMaze != nullptr);
	}
}
