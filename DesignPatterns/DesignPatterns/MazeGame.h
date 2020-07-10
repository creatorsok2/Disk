#pragma once

#include "Maze.h"

class MazeFactory;
class MazeBuilder;
class MazeGame
{
public:
	std::shared_ptr<Maze> CreateMaze(const MazeFactory& factory);
	std::shared_ptr<Maze> CreateMaze(MazeBuilder& builder);
	std::shared_ptr<Maze> CreateComplexMaze(MazeBuilder& builder);

};