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

struct Tile {
	u32 width;
	u32 height;
};

struct Offsets {
	u32 left;
	u32 right;
	u32 top;
	u32 bottom;
};

#include <windows.h>

#pragma pack(1)
struct BMPFileHeader
{
	WORD   FileType;     /* File type, always 4D42h ("BM") */
	DWORD  FileSize;     /* Size of the file in bytes */
	WORD   Reserved1;    /* Always 0 */
	WORD   Reserved2;    /* Always 0 */
	DWORD  BitmapOffset; /* Starting position of image data in bytes */
};
#pragma pack()

struct BMPDataHeader
{
	DWORD Size;            /* Size of this header in bytes */
	LONG  Width;           /* Image width in pixels */
	LONG  Height;          /* Image height in pixels */
	WORD  Planes;          /* Number of color planes */
	WORD  BitsPerPixel;    /* Number of bits per pixel */
	DWORD Compression;     /* Compression methods used */
	DWORD SizeOfBitmap;    /* Size of bitmap in bytes */
	LONG  HorzResolution;  /* Horizontal resolution in pixels per meter */
	LONG  VertResolution;  /* Vertical resolution in pixels per meter */
	DWORD ColorsUsed;      /* Number of colors in the image */
	DWORD ColorsImportant; /* Minimum number of important colors */
	/* Fields added for Windows 4.x follow this line */

	DWORD RedMask;       /* Mask identifying bits of red component */
	DWORD GreenMask;     /* Mask identifying bits of green component */
	DWORD BlueMask;      /* Mask identifying bits of blue component */
	DWORD AlphaMask;     /* Mask identifying bits of alpha component */
	DWORD CSType;        /* Color space type */
	LONG  RedX;          /* X coordinate of red endpoint */
	LONG  RedY;          /* Y coordinate of red endpoint */
	LONG  RedZ;          /* Z coordinate of red endpoint */
	LONG  GreenX;        /* X coordinate of green endpoint */
	LONG  GreenY;        /* Y coordinate of green endpoint */
	LONG  GreenZ;        /* Z coordinate of green endpoint */
	LONG  BlueX;         /* X coordinate of blue endpoint */
	LONG  BlueY;         /* Y coordinate of blue endpoint */
	LONG  BlueZ;         /* Z coordinate of blue endpoint */
	DWORD GammaRed;      /* Gamma red coordinate scale value */
	DWORD GammaGreen;    /* Gamma green coordinate scale value */
	DWORD GammaBlue;     /* Gamma blue coordinate scale value */
};

#pragma pack(1)
struct BMPPaletteElement
{
	BYTE Blue;      /* Blue component */
	BYTE Green;     /* Green component */
	BYTE Red;       /* Red component */
	BYTE ALPHA;		// Probs...
};
#pragma pack()

#define return Sleep(5000); return

i32 main(i32 numArguments, char** arguments)
{
	char* tilemapFilename = NULL;
	
	u32 screenWidth = 0;
	u32 screenHeight = 0;
	
	Tile tmTile;
	tmTile.width = 0;
	tmTile.height = 0;
	
	Offsets tmOffsets;
	tmOffsets.left = 0;
	tmOffsets.right = 0;
	tmOffsets.top = 0;
	tmOffsets.bottom = 0;

	if (numArguments == 10)
	{
		tilemapFilename = *(arguments + 1);
		
		screenWidth = (u32)atoi(*(arguments + 2));
		screenHeight = (u32)atoi(*(arguments + 3));
		
		tmTile.width = (u32)atoi(*(arguments + 4));
		tmTile.height = (u32)atoi(*(arguments + 5));

		tmOffsets.left = (u32)atoi(*(arguments + 6));
		tmOffsets.right = (u32)atoi(*(arguments + 9));
		tmOffsets.top = (u32)atoi(*(arguments + 7));
		tmOffsets.bottom = (u32)atoi(*(arguments + 8));

		cout << "Tilemap: " << tilemapFilename << endl;
		cout << "Screen Dimensions: " << screenWidth << " x " << screenHeight << endl;
		cout << "Tile Dimensions: " << tmTile.width << " x " << tmTile.height << endl;
		cout << "Offsets (TRBL): " << tmOffsets.top << " " << tmOffsets.right << " " << tmOffsets.bottom << " " << tmOffsets.left << endl;
	}
	else
	{
		cout << "Incorrect number of arguments specified" << endl;
		cout << "Please specify arguments as: path\\to\\file screenWidth screenHeight tileWidth tileHeight offsetLeft offsetTop offsetBottom offsetRight" << endl;
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

	BMPFileHeader tilemapFileHeader;
	BMPDataHeader tilemapDataHeader;
	DWORD numBytesRead = 0;

	BOOL fileHeaderRead = ReadFile(
		tilemapHandle,
		&tilemapFileHeader,
		sizeof(tilemapFileHeader),
		&numBytesRead,
		NULL
		);
	if (fileHeaderRead == FALSE || (numBytesRead != sizeof(tilemapFileHeader)))
	{
		cout << "Failed to read .bmp file header" << endl;
		return 0;
	}



	numBytesRead = 0;
	BOOL dataHeaderRead = ReadFile(
		tilemapHandle,
		&tilemapDataHeader,
		sizeof(tilemapDataHeader),
		&numBytesRead,
		NULL
		);

	if (dataHeaderRead == FALSE || (numBytesRead != sizeof(tilemapDataHeader)))
	{
		cout << "Failed to read .bmp data header" << endl;
		return 0;
	}

	u32 numColorPaletteEntries = (tilemapFileHeader.BitmapOffset - sizeof(tilemapFileHeader)-sizeof(tilemapDataHeader)) / sizeof(BMPPaletteElement); //1 << tilemapDataHeader.BitsPerPixel;
	BMPPaletteElement* tilemapColorPalette = new BMPPaletteElement[numColorPaletteEntries];
	numBytesRead = 0;
	BOOL colorPaletteRead = ReadFile(
		tilemapHandle,
		tilemapColorPalette,
		sizeof(BMPPaletteElement)*numColorPaletteEntries,
		&numBytesRead,
		NULL
		);
	if (colorPaletteRead == FALSE || (numBytesRead != sizeof(BMPPaletteElement)*numColorPaletteEntries))
	{
		cout << "Failed to read .bmp color palette" << endl;
		return 0;
	}

	cout << "tilemap is: " << tilemapDataHeader.Width << " x " << tilemapDataHeader.Height << endl;


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
	Sleep(5000);
	return 0;
}