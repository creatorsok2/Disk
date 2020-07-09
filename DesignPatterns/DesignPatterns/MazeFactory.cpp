#include "pch.h"
#include "MazeFactory.h"

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

std::shared_ptr<Room> EnchantedMazeFactory::MakeRoom(int n) const
{
	return std::make_shared<EnchantedRoom>(n);
}

std::shared_ptr<Door> EnchantedMazeFactory::MakeDoor(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2) const
{
	return std::make_shared<DoorNeedingSpell>(r1, r2);
}

std::shared_ptr<Wall> BombedMazeFactory::MakeWall() const
{
	return std::make_shared<BombedWall>();
}

std::shared_ptr<Room> BombedMazeFactory::MakeRoom(int n) const
{
	return std::make_shared<RoomWithABomb>(n);
}
