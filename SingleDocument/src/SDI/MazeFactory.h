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
	virtual std::shared_ptr<Room> MakeRoom(int n) const override;
	virtual std::shared_ptr<Door> MakeDoor(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2) const override;
};

class BombedMazeFactory : public MazeFactory
{
public:
	BombedMazeFactory() = default;
	virtual ~BombedMazeFactory() = default;

public:
	virtual std::shared_ptr<Wall> MakeWall() const override;
	virtual std::shared_ptr<Room> MakeRoom(int n) const override;

};

class MazePrototypeFactory : public MazeFactory
{
public:
	MazePrototypeFactory(std::shared_ptr<Maze>, std::shared_ptr<Wall>
		, std::shared_ptr<Room>, std::shared_ptr<Door>);
	virtual ~MazePrototypeFactory() = default;

public:
	virtual std::shared_ptr<Wall> MakeWall() const override;
	virtual std::shared_ptr<Door> MakeDoor(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2) const override;

private:
	std::shared_ptr<Maze> _prototypeMaze = nullptr;
	std::shared_ptr<Wall> _prototypeWall = nullptr;
	std::shared_ptr<Room> _prototypeRoom = nullptr;
	std::shared_ptr<Door> _prototypeDoor = nullptr;

};

class MazeSingletonFactory : public MazeFactory
{
public:
	static MazeSingletonFactory* Instance();
	
public:
	MazeSingletonFactory() = default;
	virtual ~MazeSingletonFactory();

private:
	static std::unique_ptr<MazeSingletonFactory> _instance;
};