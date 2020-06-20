namespace Rendering
{
	namespace Texture
	{
		struct BMPHeader
		{
			unsigned char type[2];
			int f_lenght;
			short rezerved1;
			short rezerved2;
			int offBits;
		};
		struct BMPHeaderInfo
		{
			int size;
			int width;
			int height;
			short planes;
			short bitCount;
			int compresion;
			int sizeImage;
			int xPelsPerMeter;
			int yPelsPerMeter;
			int clrUsed;
			int clrImportant;
		};
	}
}