#pragma once

#include "Maze.h"

class MazeBuilder
{
public:
	MazeBuilder() = default;
	virtual ~MazeBuilder() = default;

public:
	virtual void BuildMaze() {}
	virtual void BuildRoom(int) {} // room
	virtual void BuildDoor(int, int) {}; // roomFrom, roomTo

	virtual std::shared_ptr<Maze> GetMaze() { return nullptr; }

};

class StandardMazeBuilder : public MazeBuilder
{
public:
	StandardMazeBuilder() = default;
	virtual ~StandardMazeBuilder() = default;

public:
	virtual void BuildMaze() override;
	virtual void BuildRoom(int) override;
	virtual void BuildDoor(int, int) override;

	virtual std::shared_ptr<Maze> GetMaze() override;

private:
	Direction CommonWall(std::shared_ptr<Room>, std::shared_ptr<Room>);

private:
	std::shared_ptr<Maze> _currentMaze = nullptr;

};

class CountingMazeBuilder : public MazeBuilder
{
public:
	CountingMazeBuilder() = default;
	virtual ~CountingMazeBuilder() = default;

public:
	virtual void BuildMaze() override;
	virtual void BuildRoom(int) override;
	virtual void BuildDoor(int, int) override;

public:
	void GetCount(int &rooms, int &doors) const;

private:
	int _doors = 0;
	int _rooms = 0;
};