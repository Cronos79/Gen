/* ========================================================================
   $Date: 8/20/2023$
   $Revision: $
   $Creator: Matt Brock $
   $Notice: (C) Copyright 2023 by CronoGames All Rights Reserved. $
   ======================================================================== */
#include "gen_dungeon.h"
#include <vector>


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

struct gen_cell
{
	int top;
	int left;
	int width;
	int height;
};

struct gen_leaf
{
	std::vector<gen_cell> cells; // Each leaf is 2 cells
};

static void TestCode(int32_t DungionSide)
{
	std::vector<gen_leaf> leafs;

	int buffer = 400;
	int Width = DungionSide;
	int Height = DungionSide;
	// This is 4 rooms across even split + buffer
	if (Width < 7680 + buffer)
	{
		Width = 7680 + buffer;
	}
	Height = Width; //keep master cell square
	gen_cell MasterCell{ 0, 0, Width, Height };
	// Split hor or vert and make 2 cells.. repeat until all rooms desired size .. // humm how to make sisters //add them to a leaf push the leaf to leafs
	// tile 64 1920x1080 29 across max 16 down
	//Width / 4 = cellwidth; 
	//cellwidth / 64 = max cellswide;
	// min width is 1920 * 4
	int min = (DungionSide / 2) - (buffer / 2);
	int max = (DungionSide / 2) + (buffer / 2);
	// find rand num between min / max
	// split cells by DungionSide and rand num

	for (gen_leaf& leaf : leafs)
	{
		//
	}
}