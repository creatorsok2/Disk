#include "pch.h"
#include "Maze.h"

Room::Room(int RoomNo)
	: m_RoomNo(RoomNo)
{
	m_aDefaultWall = std::make_shared<Wall>();

	auto directionNum = static_cast<int>(Direction::Num);
	for (auto idx = 0; idx < directionNum; ++idx)
		m_aSides[idx] = m_aDefaultWall;
}

void Room::Enter()
{
	TRACE(_T("Room::Enter"));
}

std::shared_ptr<MapSite> Room::Clone() const
{
	return std::make_shared<Room>(*this);
}

int Room::GetRoomNo()
{
	return m_RoomNo;
}

std::weak_ptr<MapSite> Room::GetSide(Direction direction)
{
	return m_aSides[static_cast<int>(direction)];
}

void Room::SetSide(Direction direction, std::weak_ptr<MapSite> mapsite)
{
	m_aSides[static_cast<int>(direction)] = mapsite;
}

void Wall::Enter()
{
	TRACE(_T("Wall::Enter"));
}

std::shared_ptr<MapSite> Wall::Clone() const
{
	return std::make_shared<Wall>(*this);
}

Door::Door(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2)
	: m_r1(r1), m_r2(r2)
{
}

void Door::Enter()
{
	TRACE(_T("Door::Enter"));
}

std::shared_ptr<MapSite> Door::Clone() const
{
	return std::make_shared<Door>(*this);
}

void Door::Initialize(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2)
{
	m_r1 = r1;
	m_r2 = r2;
}

void Maze::AddRoom(std::shared_ptr<Room> room)
{
	auto RoomNo = room->GetRoomNo();
	auto itr = m_mRoom.find(RoomNo);
	if (itr == m_mRoom.cend())
		m_mRoom.emplace(RoomNo, room);
}

std::shared_ptr<Room> Maze::RoomNo(int RoomNo) const
{
	auto itr = m_mRoom.find(RoomNo);
	return itr != m_mRoom.cend() ? itr->second : nullptr;
}

EnchantedRoom::EnchantedRoom(int RoomNo)
	: Room(RoomNo)
{
}

std::shared_ptr<MapSite> EnchantedRoom::Clone() const
{
	return std::make_shared<EnchantedRoom>(*this);
}

DoorNeedingSpell::DoorNeedingSpell(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2)
	: Door(r1, r2)
{
}

std::shared_ptr<MapSite> DoorNeedingSpell::Clone() const
{
	return std::make_shared<DoorNeedingSpell>(*this);
}

RoomWithABomb::RoomWithABomb(int RoomNo)
	: Room(RoomNo)
{
}

std::shared_ptr<MapSite> RoomWithABomb::Clone() const
{
	return std::make_shared<RoomWithABomb>(*this);
}

std::shared_ptr<MapSite> BombedWall::Clone() const
{
	return std::make_shared<BombedWall>(*this);
}
