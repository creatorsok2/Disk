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

Door::Door(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2)
	: m_r1(r1), m_r2(r2)
{
}

void Door::Enter()
{
	TRACE(_T("Door::Enter"));
}

std::weak_ptr<Room> Door::OtherSideFrom(std::weak_ptr<Room>)
{
	return std::weak_ptr<Room>();
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

DoorNeedingSpell::DoorNeedingSpell(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2)
	: Door(r1, r2)
{
}

RoomWithABomb::RoomWithABomb(int RoomNo)
	: Room(RoomNo)
{
}
