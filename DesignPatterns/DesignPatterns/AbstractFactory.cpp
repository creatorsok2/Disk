#include "pch.h"
#include "AbstractFactory.h"

std::shared_ptr<Maze> MazeFactory::MakeMaze() const
{
	return std::make_shared<Maze>();
}

std::shared_ptr<Wall> MazeFactory::MakeWall() const
{
	return std::make_shared<Wall>();
}

std::shared_ptr<Room> MazeFactory::MakeRoom(int n) const
{
	return std::make_shared<Room>(n);
}

std::shared_ptr<Door> MazeFactory::MakeDoor(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2) const
{
	return std::make_shared<Door>(r1, r2);
}

std::shared_ptr<Maze> MazeGame::CreateMaze(MazeFactory & factory)
{
	auto aMaze = factory.MakeMaze();
	auto r1 = factory.MakeRoom(1);
	auto r2 = factory.MakeRoom(2);
	auto theDoor = factory.MakeDoor(r1, r2);

	aMaze->AddRoom(r1);
	aMaze->AddRoom(r2);
	r1->SetSide(Direction::East, theDoor);
	r2->SetSide(Direction::West, theDoor);

	return nullptr;
}
