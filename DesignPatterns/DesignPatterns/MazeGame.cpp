#include "pch.h"
#include "MazeGame.h"
#include "MazeFactory.h"
#include "MazeBuilder.h"

std::shared_ptr<Maze> MazeGame::CreateMaze(const MazeFactory & factory)
{
	auto aMaze = factory.MakeMaze();
	auto r1 = factory.MakeRoom(1);
	auto r2 = factory.MakeRoom(2);
	auto aDoor = factory.MakeDoor(r1, r2);

	aMaze->AddRoom(r1);
	aMaze->AddRoom(r2);

	r1->SetSide(Direction::North, factory.MakeWall());
	r1->SetSide(Direction::South, factory.MakeWall());
	r1->SetSide(Direction::East, aDoor);
	r1->SetSide(Direction::West, factory.MakeWall());

	r2->SetSide(Direction::North, factory.MakeWall());
	r2->SetSide(Direction::South, factory.MakeWall());
	r2->SetSide(Direction::East, factory.MakeWall());
	r2->SetSide(Direction::West, aDoor);

	return aMaze;
}

std::shared_ptr<Maze> MazeGame::CreateMaze(MazeBuilder & builder)
{
	builder.BuildMaze();
	
	builder.BuildRoom(1);
	builder.BuildRoom(2);
	builder.BuildDoor(1, 2);

	return builder.GetMaze();
}

std::shared_ptr<Maze> MazeGame::CreateComplexMaze(MazeBuilder & )
{
	return std::shared_ptr<Maze>();
}