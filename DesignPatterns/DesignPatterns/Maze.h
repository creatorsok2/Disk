#pragma once

enum class Direction { North, South, East, West, Num };
class MapSite
{
public:
	MapSite() = default;
	virtual ~MapSite() = default;

public:
	virtual void Enter() = 0;
};

class Room : public MapSite
{
public:
	Room(int RoomNo = 0);
	virtual ~Room() = default;

public:
	virtual void Enter();

public:
	int GetRoomNo();
	std::weak_ptr<MapSite> GetSide(Direction);
	void SetSide(Direction, std::weak_ptr<MapSite>);

protected:
	int m_RoomNo;
	std::weak_ptr<MapSite> m_aSides[4];
	std::shared_ptr<MapSite> m_aDefaultWall;

};

class Wall : public MapSite
{
public:
	Wall() = default;
	virtual ~Wall() = default;

public:
	virtual void Enter();

};

class Door : public MapSite
{
public:
	Door(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2);
	virtual ~Door() = default;

public:
	virtual void Enter();

public:
	std::weak_ptr<Room> OtherSideFrom(std::weak_ptr<Room>);

protected:
	std::weak_ptr<Room> m_r1;
	std::weak_ptr<Room> m_r2;
	bool m_isOpen;

};

class Maze
{
public:
	Maze() = default;
	virtual ~Maze() = default;

public:
	void AddRoom(std::shared_ptr<Room>);
	std::weak_ptr<Room> RoomNo(int) const;

private:
	std::unordered_map<int, std::shared_ptr<Room>> m_mRoom;
};
