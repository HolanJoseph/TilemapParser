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

u32 padVal(u32 x, u32 padTo)
{
	u32 retval = (x + padTo) & ((u32)0-padTo);
	return retval;
}

typedef u32 tile[256];

i32 main(i32 numArguments, char** arguments)
{

	tile x = { 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 
		0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 
		0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 
		0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 
		0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 
		0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 
		0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 
		0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 
		0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 
		0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 
		0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 
		0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 
		0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 
		0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 
		0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 
		0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 
		0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 
		0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 
		0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 
		0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 
		0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 
		0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 
		0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 
		0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 
		0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x22222222, 
		0x11111111, 0x22222222, 0x11111111, 0x22222222, 0x11111111, 0x99999999
	};
	
	u32 (*x2)[256] = (u32(*)[256])malloc(sizeof(tile));
	for (u64 i = 0; i < 256; ++i)
	{
		(*x2)[i] = x[i];
	}

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


	// read in .bmp file
	// open file
	// read in bmp header to get file size
	// create a buffer to hold the data
	// close the file
	HANDLE tmHandle = CreateFileA(
										tilemapFilename,
										GENERIC_READ,
										(FILE_SHARE_READ | FILE_SHARE_WRITE),
										NULL,
										OPEN_EXISTING,
										FILE_ATTRIBUTE_NORMAL,
										NULL
   									);
	if (tmHandle == INVALID_HANDLE_VALUE)
	{
		cout << "Specified file could not be opened" << endl;
		return 0;
	}

	BMPFileHeader tmFileHeader;
	BMPDataHeader tmDataHeader;
	DWORD numBytesRead = 0;

	BOOL fileHeaderRead = ReadFile(
		tmHandle,
		&tmFileHeader,
		sizeof(tmFileHeader),
		&numBytesRead,
		NULL
		);
	if (fileHeaderRead == FALSE || (numBytesRead != sizeof(tmFileHeader)))
	{
		cout << "Failed to read .bmp file header" << endl;
		return 0;
	}



	numBytesRead = 0;
	BOOL dataHeaderRead = ReadFile(
		tmHandle,
		&tmDataHeader,
		sizeof(tmDataHeader),
		&numBytesRead,
		NULL
		);
	if (dataHeaderRead == FALSE || (numBytesRead != sizeof(tmDataHeader)))
	{
		cout << "Failed to read .bmp data header" << endl;
		return 0;
	}

	u32 numColorPaletteEntries = (tmFileHeader.BitmapOffset - sizeof(tmFileHeader)-sizeof(tmDataHeader)) / sizeof(BMPPaletteElement); //1 << tilemapDataHeader.BitsPerPixel;
	BMPPaletteElement* tmColorPalette = new BMPPaletteElement[numColorPaletteEntries];
	numBytesRead = 0;
	BOOL colorPaletteRead = ReadFile(
		tmHandle,
		tmColorPalette,
		sizeof(BMPPaletteElement)*numColorPaletteEntries,
		&numBytesRead,
		NULL
		);
	if (colorPaletteRead == FALSE || (numBytesRead != sizeof(BMPPaletteElement)*numColorPaletteEntries))
	{
		cout << "Failed to read .bmp color palette" << endl;
		return 0;
	}
	//cout << "tilemap is: " << tilemapDataHeader.Width << " x " << tilemapDataHeader.Height << endl;


	u64 tmIndexedDataWidth = tmDataHeader.Width;
	u64 tmIndexedDataHeight = tmDataHeader.Height;
	u8* tmIndexedData = (u8*)malloc(tmDataHeader.SizeOfBitmap); // (tilemapDataHeader.BitsPerPixel / 8)*tilemapDataHeader.Width*tilemapDataHeader.Height);
	numBytesRead = 0;
	BOOL bitmapRead = ReadFile(
		tmHandle,
		tmIndexedData,
		tmDataHeader.SizeOfBitmap,
		&numBytesRead,
		NULL
		);
	if (bitmapRead == FALSE || (numBytesRead != tmDataHeader.SizeOfBitmap))
	{
		cout << "Failed to read .bmp bitmap indexed data" << endl;
		return 0;
	}

	// Convert to rgba values
	// bottom up
	// bgra
// 	   (0xbb << 0 |
// 		0x66 << 8 |
// 		0x55 << 16 |
// 		0xaa << 24);
	// working on the indexed data which has different indices from the non indexed data
	u64 tmBGRADataWidth = (tmDataHeader.Width - tmOffsets.right - tmOffsets.left);
	u64 tmBGRADataHeight = (tmDataHeader.Height - tmOffsets.top - tmOffsets.bottom);
	u32* tmBGRAData = (u32*)malloc(sizeof(u32)*tmBGRADataWidth * tmBGRADataHeight);
	
	u64 numRows = tmDataHeader.Height;
	u64 numColumns = tmDataHeader.Width;
	for (u64 indexedRow = tmOffsets.bottom, row=0; indexedRow < numRows - tmOffsets.top; ++indexedRow, ++row)
	{
		for (u64 indexedColumn = tmOffsets.left, column = 0; indexedColumn < numColumns - tmOffsets.right; ++indexedColumn, ++column)
		{
			u8 paletteIndex = tmIndexedData[indexedRow*tmIndexedDataWidth + indexedColumn];
			BMPPaletteElement pe = tmColorPalette[paletteIndex];
			tmBGRAData[row*tmBGRADataWidth + column] = (pe.Blue << 0 |
														pe.Green << 8 |
														pe.Red << 16 |
														0xff << 24);
		}
	}

	CloseHandle(tmHandle);


	u64 tileElementCount = tmTile.width * tmTile.height;
	u64 sizeOfTile = sizeof(u32) * tileElementCount;
	u64 numTileColumns = tmBGRADataWidth / tmTile.width;
	u64 numTileRows = tmBGRADataHeight / tmTile.height;
	u32* tileData = (u32*)malloc(sizeOfTile * numTileColumns * numTileRows);


	for (u64 row = 0; row < numTileRows; ++row)
	{
		for (u64 column = 0; column < numTileColumns; ++column)
		{
			u32* tile = tileData + (tileElementCount*numTileColumns*row) + (tileElementCount*column);
			
			for (u64 h = 0; h < tmTile.height; ++h)
			{
				for (u64 w = 0; w < tmTile.width; ++w)
				{
					u32* tilePx = tile + (h*tmTile.width) + w;
					u32* tmPx = tmBGRAData + (((row*tmTile.height) + h) * tmBGRADataWidth) + ((column*tmTile.width) + w);

					*tilePx = *tmPx;
				}
			}
			//*tile = 0x11111111;
		}
	}

	u64 n = 0;
	for (u64 i = 0; i < tileElementCount * numTileColumns * numTileRows; ++i)
	{
		if (*(tileData + i) == 0x11111111)
		{
			++n;
		}
	}
	n;

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


	// Test create bmp
// 	char* dirPath = "C:/tilemap_tiles";
// 	BOOL dir = CreateDirectoryA( dirPath, NULL ); // only creates the directory if it doesn't exist

	// Create output file
	char* outfilePath = "testout.bmp";
	HANDLE outfileHandle = CreateFile(
		outfilePath,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);
	if (outfileHandle == INVALID_HANDLE_VALUE)
	{
		cout << "Could not output individual tile bmp files" << endl;
		return 0;
	}

	BMPFileHeader outfileFileHeader = { 0 };
	outfileFileHeader.FileType = 0x4D42;
	outfileFileHeader.FileSize = sizeof(BMPFileHeader)+sizeof(BMPDataHeader) + (sizeof(u32)*tmBGRADataWidth*tmBGRADataHeight);
	outfileFileHeader.Reserved1 = 0;
	outfileFileHeader.Reserved2 = 0;
	outfileFileHeader.BitmapOffset = sizeof(BMPFileHeader) + sizeof(BMPDataHeader);

	BMPDataHeader outfileDataHeader = { 0 };
	outfileDataHeader.Size = 108;
	outfileDataHeader.Width = tmBGRADataWidth;
	outfileDataHeader.Height = tmBGRADataHeight;
	outfileDataHeader.Planes = 1;
	outfileDataHeader.BitsPerPixel = 32;
	outfileDataHeader.Compression = 0;
	outfileDataHeader.SizeOfBitmap = 0;
	outfileDataHeader.HorzResolution = tmDataHeader.HorzResolution;
	outfileDataHeader.VertResolution = tmDataHeader.VertResolution;
	outfileDataHeader.ColorsUsed = 0;
	outfileDataHeader.ColorsImportant = 0;
	outfileDataHeader.RedMask = 0x00ff0000;
	outfileDataHeader.GreenMask = 0x0000ff00;
	outfileDataHeader.BlueMask = 0x000000ff;
	outfileDataHeader.AlphaMask = 0xff000000;
	outfileDataHeader.CSType = 0x01;
	outfileDataHeader.RedX = 0;
	outfileDataHeader.RedY = 0;
	outfileDataHeader.RedZ = 0;
	outfileDataHeader.GreenX = 0;
	outfileDataHeader.GreenY = 0;
	outfileDataHeader.GreenZ = 0;
	outfileDataHeader.BlueX = 0;
	outfileDataHeader.BlueY = 0;
	outfileDataHeader.BlueZ = 0;
	outfileDataHeader.GammaRed = 0;
	outfileDataHeader.GammaGreen = 0;
	outfileDataHeader.GammaBlue = 0;

	DWORD numBytesWritten = 0;
	BOOL ofhw = WriteFile(
		outfileHandle,
		&outfileFileHeader,
		sizeof(outfileFileHeader),
		&numBytesWritten,
		NULL
		);

	BOOL odhw = WriteFile(
		outfileHandle,
		&outfileDataHeader,
		sizeof(outfileDataHeader),
		&numBytesWritten,
		NULL
		);

	BOOL odw = WriteFile(
		outfileHandle,
		tmBGRAData,
		sizeof(u32) * tmBGRADataWidth * tmBGRADataHeight,
		&numBytesWritten,
		NULL
		);


	CloseHandle(outfileHandle);
	Sleep(5000);
	return 0;
}