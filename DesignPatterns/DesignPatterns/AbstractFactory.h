#pragma once

#include "Maze.h"

class MazeFactory
{
public:
	MazeFactory() = default;

public:
	virtual std::shared_ptr<Maze> MakeMaze() const;
	virtual std::shared_ptr<Wall> MakeWall() const;
	virtual std::shared_ptr<Room> MakeRoom(int n) const;
	virtual std::shared_ptr<Door> MakeDoor(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2) const;

};

class MazeGame
{
public:
	std::shared_ptr<Maze> CreateMaze(MazeFactory& factory);
		
};