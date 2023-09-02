/* ========================================================================
   $Date: 8/20/2023$
   $Revision: $
   $Creator: Matt Brock $
   $Notice: (C) Copyright 2023 by CronoGames All Rights Reserved. $
   ======================================================================== */
#include "gen_dungeon.h"
#include <queue>
#include <stdint.h>
#include <list>
#include <random>


/****************************************
* https://gamedev.stackexchange.com/questions/82059/algorithm-for-procedural-2d-map-with-connected-paths
* https://www.roguebasin.com/index.php?title=C%2B%2B_Example_of_Dungeon-Building_Algorithm
*
* min room size / max room size
* dungeon width / height
* split cells until all in range of min / max room size
* cells will be a tree 2 rooms per branch
* connect the 2 rooms in that branch
****************************************/



static void SplitHorizontally(int32_t MinHeight, std::queue<gen_rect>* Cells, gen_rect Cell)
{
	std::random_device rd;     // Only used once to initialize (seed) engine
	std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(MinHeight, (Cell.bottom - Cell.top) - MinHeight); // Guaranteed unbiased

	int random_integer = uni(rng);
	
	gen_rect cell1 = {};
	cell1.left = Cell.left;
	cell1.right = Cell.right;
	cell1.top = Cell.top;
	cell1.bottom = Cell.bottom - random_integer;
	cell1.SisterRoom = gen_sister_room::ROOMRIGHT;
	Cells->push(cell1);

	gen_rect cell2 = {};
	cell2.left = Cell.left;
	cell2.right = Cell.right;
	cell2.top = Cell.top + random_integer;
	cell2.bottom = Cell.bottom;
	cell2.SisterRoom = gen_sister_room::ROOMLEFT;
	Cells->push(cell2);
}

static int32_t GetRandomIntInRange(int32_t Min, int32_t Max)
{
	std::random_device rd;     // Only used once to initialize (seed) engine
	std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(Min, Max); // Guaranteed unbiased

	return uni(rng);
}

static void SplitVertically(int32_t MinWidth, std::queue<gen_rect>* Cells, gen_rect Cell)
{
	//std::random_device rd;     // Only used once to initialize (seed) engine
	//std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
	//std::uniform_int_distribution<int> uni(MinWidth, (Cell.right - Cell.left) - MinWidth); // Guaranteed unbiased

	int random_integer = GetRandomIntInRange(MinWidth, (Cell.right - Cell.left) - MinWidth);

	gen_rect cell1 = {};
	cell1.left = Cell.left;
	cell1.right = Cell.right - random_integer;
	cell1.top = Cell.top;
	cell1.bottom = Cell.bottom;
	cell1.SisterRoom = gen_sister_room::ROOMDOWN;
	Cells->push(cell1);

	gen_rect cell2 = {};
	cell2.left = Cell.left + random_integer;
	cell2.right = Cell.right;
	cell2.top = Cell.top;
	cell2.bottom = Cell.bottom;
	cell2.SisterRoom = gen_sister_room::ROOMUP;
	Cells->push(cell2);
}

static void GenSplitCells(int32_t Width, int32_t Height, std::vector<gen_rect>* SplitCells)
{
	std::queue<gen_rect>* Cells = new std::queue<gen_rect>;
	gen_rect MainCell = {};
	MainCell.top = 0;
	MainCell.left = 0;
	MainCell.right = Width;
	MainCell.bottom = Height;
	Cells->push(MainCell);

	int32_t MinWidth = 17;
	int32_t MinHeight = 12;
	int32_t MaxRoomWidth = 29;
	int32_t MaxRoomHeight = 16;
	while (Cells->size() > 0)
	{
		gen_rect Cell = Cells->front();
		Cells->pop();
		if (Cell.bottom - Cell.top >= MinHeight && Cell.right - Cell.left >= MinWidth)
		{

			if ((double)rand() / (RAND_MAX + 1.0) > 0.5f)
			{
				if (Cell.bottom - Cell.top >= MinHeight * 2.25f)
				{
					SplitHorizontally(MinHeight, Cells, Cell);
				}
				else if (Cell.right - Cell.left >= MinWidth * 2.25f)
				{
					SplitVertically(MinWidth, Cells, Cell);
				}
				else if (Cell.bottom - Cell.top >= MinHeight && Cell.right - Cell.left >= MinWidth)
				{
					SplitCells->push_back(Cell);
				}
			}
			else
			{
				if (Cell.right - Cell.left >= MinWidth * 2.25f)
				{
					SplitVertically(MinWidth, Cells, Cell);
				}
				else if (Cell.bottom - Cell.top >= MinHeight * 2.25f)
				{
					SplitHorizontally(MinHeight, Cells, Cell);
				}
				else if (Cell.bottom - Cell.top >= MinHeight && Cell.right - Cell.left >= MinWidth)
				{
					SplitCells->push_back(Cell);
				}
			}
		}
	}
}

static void GenMakeRooms(std::vector<gen_rect>* SplitCells, std::vector<gen_room>* Rooms)
{
	int32_t RoomNumber = 0;
	for (gen_rect rect : *SplitCells)
	{
		gen_room Room;
		int32_t Height = rect.bottom - rect.top;
		int32_t Width = rect.right - rect.left;
		if (Height > Room.MaxRoomY)
		{
			Height = Room.MaxRoomY;
		}
		if (Width > Room.MaxRoomX)
		{
			Width = Room.MaxRoomX;
		}
		
		Room.Dim.top = rect.top;
		Room.Dim.bottom = rect.top + Height;
		Room.Dim.left = rect.left;
		Room.Dim.right = rect.left + Width;	

		Room.SisterRoom = rect.SisterRoom;

		Room.RoomNumber = RoomNumber;

		for (int row = 0; row < Height; row++)
		{
			for (int col = 0; col < Width; col++)
			{	
				gen_tile g = {};
				g.Type = TileType::DIRT_FLOOR;
				if (row == 0)
				{
					g.Type = TileType::STONE_WALL;
				}
				else if (row == Height-1)
				{
					g.Type = TileType::STONE_WALL;
				}
				if (col == 0)
				{
					g.Type = TileType::STONE_WALL;
				}
				else if (col == Width - 1)
				{
					g.Type = TileType::STONE_WALL;
				}
				Room.Tiles.push_back(g);
			}
		}
		Rooms->push_back(Room);
		RoomNumber++;
	}
}

static void GenMakeDoors(std::vector<gen_room>* Rooms)
{
	int32_t RoomNumber = 0;
	while (RoomNumber < Rooms->size())
	{
		bool SecondDoor = true;
		//assert(Rooms->at(RoomNumber).RoomNumber != RoomNumber); // #TODO: Need a platform file
		if (RoomNumber % 2 == 0)
		{
			SecondDoor = false;
		}
	
		switch (Rooms->at(RoomNumber).SisterRoom)
		{
		case ROOMUP:
		{
			if (Rooms->size() >= RoomNumber)
			{
				// create door on top for room 1 and door on bottom for room 2
				int32_t Hsize = Rooms->at(RoomNumber).Dim.right - Rooms->at(RoomNumber).Dim.left;
				int32_t rInt = GetRandomIntInRange(1, Hsize - 1); // #TODO: Check if this is right
				gen_tile t;
				t.Type = TileType::DUNGEON_WOOD_DOOR;
				t.IsDoor = true;
				t.DoorTo = RoomNumber - 1;
				Rooms->at(RoomNumber).Tiles[rInt] = t;
				if (SecondDoor)
				{
					int32_t Vsize = Rooms->at(RoomNumber).Dim.bottom - Rooms->at(RoomNumber).Dim.top;
					rInt = GetRandomIntInRange(1, Vsize - 2);
					t.Type = TileType::DUNGEON_WOOD_DOOR;
					t.DoorTo = RoomNumber - 2;
					t.IsDoor = true;
					int num = Hsize * rInt - 1;
					Rooms->at(RoomNumber).Tiles[num] = t;
				}
			}
		}break;
		case ROOMDOWN:
		{
			if (Rooms->size() >= RoomNumber)
			{
				int32_t Hsize = Rooms->at(RoomNumber).Dim.right - Rooms->at(RoomNumber).Dim.left;
				int32_t Vsize = Rooms->at(RoomNumber).Dim.bottom - Rooms->at(RoomNumber).Dim.top;
				int32_t rInt = GetRandomIntInRange(1, Hsize - 1);
				gen_tile t;
				t.Type = TileType::DUNGEON_WOOD_DOOR;
				t.IsDoor = true;
				t.DoorTo = RoomNumber + 1;
				int num = ((Vsize - 1) * Hsize) + rInt;
				Rooms->at(RoomNumber).Tiles[num] = t;
				if (SecondDoor)
				{
					rInt = GetRandomIntInRange(1, Vsize - 2);
					t.Type = TileType::DUNGEON_WOOD_DOOR;
					t.IsDoor = true;
					t.DoorTo = RoomNumber + 2;
					int num = Hsize * rInt - 1;
					Rooms->at(RoomNumber).Tiles[num] = t;
				}
			}
		}break;
		case ROOMLEFT:
		{
			if (Rooms->size() >= RoomNumber)
			{
				int32_t Hsize = Rooms->at(RoomNumber).Dim.right - Rooms->at(RoomNumber).Dim.left;
				int32_t Vsize = Rooms->at(RoomNumber).Dim.bottom - Rooms->at(RoomNumber).Dim.top;
				int32_t rInt = GetRandomIntInRange(1, Vsize - 2);
				gen_tile t;
				t.Type = TileType::DUNGEON_WOOD_DOOR;
				t.IsDoor = true;
				t.DoorTo = RoomNumber - 1;
				int num = rInt * Hsize;
				Rooms->at(RoomNumber).Tiles[num] = t;
				if (SecondDoor)
				{
					int32_t rInt = GetRandomIntInRange(1, Hsize - 1);
					t.Type = TileType::DUNGEON_WOOD_DOOR;
					t.IsDoor = true;
					t.DoorTo = RoomNumber - 2;
					int num = ((Vsize - 1) * Hsize) + rInt;
					Rooms->at(RoomNumber).Tiles[num] = t;
				}
			}
		}break;
		case ROOMRIGHT:
		{
			if (Rooms->size() >= RoomNumber)
			{
				int32_t Hsize = Rooms->at(RoomNumber).Dim.right - Rooms->at(RoomNumber).Dim.left;
				int32_t Vsize = Rooms->at(RoomNumber).Dim.bottom - Rooms->at(RoomNumber).Dim.top;
				int32_t rInt = GetRandomIntInRange(2, Vsize - 2);
				gen_tile t;
				t.Type = TileType::DUNGEON_WOOD_DOOR;
				t.IsDoor = true;
				t.DoorTo = RoomNumber + 1;
				int num = Hsize * rInt - 1; // #TODO: Needs testing
				Rooms->at(RoomNumber).Tiles[num] = t;
				if (SecondDoor)
				{
					int32_t rInt = GetRandomIntInRange(1, Hsize - 1);
					t.Type = TileType::DUNGEON_WOOD_DOOR;
					t.IsDoor = true;
					t.DoorTo = RoomNumber + 2;
					int num = ((Vsize - 1) * Hsize) + rInt;
					Rooms->at(RoomNumber).Tiles[num] = t;
				}
			}
		}break;
		default:
		{
			throw;
			// #TODO: log error
		}
		}
		RoomNumber += 1;
	}
}

static std::vector<gen_room> GenDungeon(int32_t MinCellWidth, int32_t MinCellHeight)
{	
	std::vector<gen_rect> SplitCells;
	std::vector<gen_room> Rooms;
	GenSplitCells(MinCellWidth, MinCellHeight, &SplitCells);
	GenMakeRooms(&SplitCells, &Rooms);
	GenMakeDoors(&Rooms);

	return Rooms;
}