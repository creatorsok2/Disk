#pragma once

#include "Maze.h"

class MazeFactory
{
public:
	MazeFactory() = default;
	virtual ~MazeFactory() = default;

public:
	virtual std::shared_ptr<Maze> MakeMaze() const;
	virtual std::shared_ptr<Wall> MakeWall() const;
	virtual std::shared_ptr<Room> MakeRoom(int n) const;
	virtual std::shared_ptr<Door> MakeDoor(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2) const;
};

class EnchantedMazeFactory : public MazeFactory
{
public:
	EnchantedMazeFactory() = default;
	virtual ~EnchantedMazeFactory() = default;

public:
	virtual std::shared_ptr<Room> MakeRoom(int n) const;
	virtual std::shared_ptr<Door> MakeDoor(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2) const;
};

class BombedMazeFactory : public MazeFactory
{
public:
	BombedMazeFactory() = default;
	virtual ~BombedMazeFactory() = default;

public:
	virtual std::shared_ptr<Wall> MakeWall() const;
	virtual std::shared_ptr<Room> MakeRoom(int n) const;

};
