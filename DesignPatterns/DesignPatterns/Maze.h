#pragma once

enum class Direction { North, South, East, West, Num };

#pragma region BASE

class MapSite
{
public:
	MapSite() = default;
	virtual ~MapSite() = default;

public:
	virtual void Enter() = 0;
	virtual std::shared_ptr<MapSite> Clone() const = 0;
};

class Room : public MapSite
{
public:
	Room() = default;
	Room(int RoomNo);
	Room(const Room&) = default;
	virtual ~Room() = default;

public:
	virtual void Enter();
	virtual std::shared_ptr<MapSite> Clone() const override;	

public:
	int GetRoomNo();
	std::weak_ptr<MapSite> GetSide(Direction);
	void SetSide(Direction, std::weak_ptr<MapSite>);

protected:
	int m_RoomNo = 0;
	std::weak_ptr<MapSite> m_aSides[4];
	std::shared_ptr<MapSite> m_aDefaultWall;

};

class Wall : public MapSite
{
public:
	Wall() = default;
	Wall(const Wall&) = default;
	virtual ~Wall() = default;

public:
	virtual void Enter();
	virtual std::shared_ptr<MapSite> Clone() const override;

};

class Door : public MapSite
{
public:
	Door() = default;
	Door(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2);
	Door(const Door&) = default;
	virtual ~Door() = default;

public:
	virtual void Enter();
	virtual std::shared_ptr<MapSite> Clone() const override;

public:
	void Initialize(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2);

protected:
	std::shared_ptr<Room> m_r1 = nullptr;
	std::shared_ptr<Room> m_r2 = nullptr;
	bool m_isOpen;

};

class Maze
{
public:
	Maze() = default;
	Maze(const Maze&) = default;
	virtual ~Maze() = default;

public:
	void AddRoom(std::shared_ptr<Room>);
	std::shared_ptr<Room> RoomNo(int) const;

private:
	std::unordered_map<int, std::shared_ptr<Room>> m_mRoom;
};

#pragma endregion

class EnchantedRoom : public Room
{
public:
	EnchantedRoom() = default;
	EnchantedRoom(int RoomNo);
	EnchantedRoom(const EnchantedRoom&) = default;
	virtual ~EnchantedRoom() = default;

public:
	virtual std::shared_ptr<MapSite> Clone() const override;
};

class DoorNeedingSpell : public Door
{
public:
	DoorNeedingSpell() = default;
	DoorNeedingSpell(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2);
	DoorNeedingSpell(const DoorNeedingSpell&) = default;
	virtual ~DoorNeedingSpell() = default;

public:
	virtual std::shared_ptr<MapSite> Clone() const override;
};

class BombedWall : public Wall
{
public:
	BombedWall() = default;
	BombedWall(const BombedWall&) = default;
	virtual ~BombedWall() = default;

public:
	virtual std::shared_ptr<MapSite> Clone() const override;
};

class RoomWithABomb : public Room
{
public:
	RoomWithABomb() = default;
	RoomWithABomb(int RoomNo);
	RoomWithABomb(const RoomWithABomb&) = default;
	virtual ~RoomWithABomb() = default;

public:
	virtual std::shared_ptr<MapSite> Clone() const override;

};
