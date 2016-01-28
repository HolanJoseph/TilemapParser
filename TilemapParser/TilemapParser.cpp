// Good type names
#include <cstdint>
typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float  f32;
typedef double f64;

#include <iostream>
using std::cout;
using std::endl;

#include <cstdlib>

#include <windows.h>

i32 main(i32 numArguments, char** arguments)
{
	char* tilemapFilename = NULL;
	u32 screenWidth = 0;
	u32 screenHeight = 0;
	u32 tileWidth = 0;
	u32 tileHeight = 0;
	u32 offsetLeft = 0;
	u32 offsetRight = 0;
	u32 offsetTop = 0;
	u32 offsetBottom = 0;

	if (numArguments == 10)
	{
		tilemapFilename = *(arguments + 1);
		screenWidth = (u32)atoi(*(arguments + 2));
		screenHeight = (u32)atoi(*(arguments + 3));
		tileWidth = (u32)atoi(*(arguments + 4));
		tileHeight = (u32)atoi(*(arguments + 5));
		offsetLeft = (u32)atoi(*(arguments + 6));
		offsetRight = (u32)atoi(*(arguments + 9));
		offsetTop = (u32)atoi(*(arguments + 7));
		offsetBottom = (u32)atoi(*(arguments + 8));

		cout << "Tilemap: " << tilemapFilename << endl;
		cout << "Screen Dimensions: " << screenWidth << " x " << screenHeight << endl;
		cout << "Tile Dimensions: " << tileWidth << " x " << tileHeight << endl;
		cout << "Offsets (TRBL): " << offsetTop << " " << offsetRight << " " << offsetBottom << " " << offsetLeft << endl;
	}
	else
	{
		cout << "Incorrect number of arguments specified" << endl;
		cout << "Please specify arguments as: path\\to\\file screenWidth screenHeight tileWidth tileHeight offsetLeft offsetTop offsetBottom offsetRight" << endl;
		Sleep(5000);
		return 0;
	}

	HANDLE tilemapHandle = CreateFileA(
										tilemapFilename,
										GENERIC_READ,
										(FILE_SHARE_READ | FILE_SHARE_WRITE),
										NULL,
										OPEN_EXISTING,
										FILE_ATTRIBUTE_NORMAL,
										NULL
   									);
	if (tilemapHandle == INVALID_HANDLE_VALUE)
	{
		cout << "Specified file could not be opened" << endl;
		return 0;
	}

	// read in .bmp file
		// open file
		// read in bmp header to get file size
		// create a buffer to hold the data
		// close the file
	// cut it up into screens
		// subtract the offsets 
		// divide by screen size
		// allocate that many buffers to hold the data
	// cut screens into tiles
		// for each screen 
			// divide by the tile size
			// allocate that many buffers to hold the data
	// compare each tile to see how many unique tiles there are
		// start with an empty list
		// for each tile
		// if their pixel data DOES NOT match the pixel data of any of the tiles in the list add the tile to the list
		// else dont
	// create .bmp files for each unique tile
		// if the unique tile list isnt empty
			// create a new folder
			// inside the folder for each tile in the unique tile list create a new .bmp file with its pixel data
			

	CloseHandle(tilemapHandle);
	Sleep(10000);
	return 0;
}