#include "pch.h"
#include <iostream>
#include "BuilderRunner.h"
#include "MazeBuilder.h"
#include "MazeGame.h"

void BuilderRunner::Main()
{
	{
		MazeGame game;
		StandardMazeBuilder builder;

		auto aMaze = game.CreateMaze(builder); 
		ASSERT(aMaze != nullptr);
	}

	{
		MazeGame game;
		CountingMazeBuilder builder;

		int rooms, doors;
		auto aMaze = game.CreateMaze(builder);
		builder.GetCount(rooms, doors);

		std::cout << _T("the Maze has ")
			<< rooms << " rooms and "
			<< doors << " doors" << std::endl;
	}
}
