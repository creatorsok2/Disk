#include "pch.h"
#include "MazeBuilder.h"

void StandardMazeBuilder::BuildMaze()
{
	_currentMaze = std::make_shared<Maze>();
}

void StandardMazeBuilder::BuildRoom(int RoomNo)
{
	if (_currentMaze->RoomNo(RoomNo) != nullptr)
		return;

	auto aRoom = std::make_shared<Room>(RoomNo);
	aRoom->SetSide(Direction::North, std::make_shared<Wall>());
	aRoom->SetSide(Direction::South, std::make_shared<Wall>());
	aRoom->SetSide(Direction::East, std::make_shared<Wall>());
	aRoom->SetSide(Direction::West, std::make_shared<Wall>());

	_currentMaze->AddRoom(aRoom);
}

void StandardMazeBuilder::BuildDoor(int n1, int n2)
{
	auto r1 = _currentMaze->RoomNo(n1);
	auto r2 = _currentMaze->RoomNo(n2);

	auto aDoor = std::make_shared<Door>(r1, r2);

	r1->SetSide(CommonWall(r1, r2), aDoor);
	r2->SetSide(CommonWall(r2, r1), aDoor);
}

std::shared_ptr<Maze> StandardMazeBuilder::GetMaze()
{
	return _currentMaze;
}

Direction StandardMazeBuilder::CommonWall(std::shared_ptr<Room>, std::shared_ptr<Room>)
{
	return Direction();
}

void CountingMazeBuilder::BuildMaze()
{
}

void CountingMazeBuilder::BuildRoom(int)
{
	_rooms++;
}

void CountingMazeBuilder::BuildDoor(int, int)
{
	_doors++;
}

void CountingMazeBuilder::GetCount(int &rooms, int &doors) const
{
	rooms = _rooms;
	doors = _doors;
}
