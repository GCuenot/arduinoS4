// #include "BmpLib.h"
// #include "operationsImages.h"

// void cree3matrices(unsigned char r[N][N], unsigned char v[N][N],
// 	unsigned char b[N][N], const DonneesImageRGB* image)
// {
// 	int k = 0;
// 	for (int i = 0; i < image->hauteurImage; ++i)
// 	{
// 		for (int j = 0; j < image->largeurImage; ++j)
// 		{
// 			b[i][j] = image->donneesRGB[k];
// 			v[i][j] = image->donneesRGB[k+1];
// 			r[i][j] = image->donneesRGB[k+2];
// 			k += 3;
// 		}
// 	}
// }

// void creeImage(const unsigned char r[N][N], const unsigned char v[N][N],
// 	const unsigned char b[N][N], DonneesImageRGB* image)
// {
// 	int k = 0;
// 	for (int i = 0; i < image->hauteurImage; ++i)
// 	{
// 		for (int j = 0; j < image->largeurImage; ++j)
// 		{
// 			image->donneesRGB[k  ] = b[i][j];
// 			image->donneesRGB[k+1] = v[i][j];
// 			image->donneesRGB[k+2] = r[i][j];
// 			k += 3;
// 		}
// 	}
// }

// void negatifImage(unsigned char r[N][N], unsigned char v[N][N],
// 	unsigned char b[N][N], DonneesImageRGB* image)
// {
// 	cree3matrices(r, v, b, image);
// 	for (int i = 0; i < image->hauteurImage; ++i)
// 	{
// 		for (int j = 0; j < image->largeurImage; ++j)
// 		{
// 			r[i][j] = 255 - r[i][j];
// 			v[i][j] = 255 - v[i][j];
// 			b[i][j] = 255 - b[i][j];
// 		}
// 	}
// 	creeImage(r, v, b, image);
// }

// void rougeImage(unsigned char r[N][N], unsigned char v[N][N],
// 	unsigned char b[N][N], DonneesImageRGB* image)
// {
// 	cree3matrices(r, v, b, image);
// 	for (int i = 0; i < image->hauteurImage; ++i)
// 	{
// 		for (int j = 0; j < image->largeurImage; ++j)
// 		{
// 			v[i][j] = 0;
// 			b[i][j] = 0;
// 		}
// 	}
// 	creeImage(r, v, b, image);
// }

// void vertImage(unsigned char r[N][N], unsigned char v[N][N],
// 	unsigned char b[N][N], DonneesImageRGB* image)
// {
// 	cree3matrices(r, v, b, image);
// 	for (int i = 0; i < image->hauteurImage; ++i)
// 	{
// 		for (int j = 0; j < image->largeurImage; ++j)
// 		{
// 			r[i][j] = 0;
// 			b[i][j] = 0;
// 		}
// 	}
// 	creeImage(r, v, b, image);
// }

// void bleuImage(unsigned char r[N][N], unsigned char v[N][N],
// 	unsigned char b[N][N], DonneesImageRGB* image)
// {
// 	cree3matrices(r, v, b, image);
// 	for (int i = 0; i < image->hauteurImage; ++i)
// 	{
// 		for (int j = 0; j < image->largeurImage; ++j)
// 		{
// 			r[i][j] = 0;
// 			v[i][j] = 0;
// 		}
// 	}
// 	creeImage(r, v, b, image);
// }

// void couleurNiveauDeGris_naif(unsigned char r[N][N], unsigned char v[N][N],
// 	unsigned char b[N][N], DonneesImageRGB* image)
// {
// 	cree3matrices(r, v, b, image);
// 	for (int i = 0; i < image->hauteurImage; ++i)
// 	{
// 		for (int j = 0; j < image->largeurImage; ++j)
// 		{
// 			unsigned char moyenne = (r[i][j] + v[i][j] + b[i][j]) / 3;
// 			r[i][j] = moyenne;
// 			v[i][j] = moyenne;
// 			b[i][j] = moyenne;
// 		}
// 	}
// 	creeImage(r, v, b, image);
// }

// void couleurNiveauDeGris(unsigned char r[N][N], unsigned char v[N][N],
// 	unsigned char b[N][N], DonneesImageRGB* image)
// {
// 	cree3matrices(r, v, b, image);
// 	for (int i = 0; i < image->hauteurImage; ++i)
// 	{
// 		for (int j = 0; j < image->largeurImage; ++j)
// 		{
// 			unsigned char gris = 0.2125 * r[i][j] + 0.7154 * v[i][j] + 0.0721 * b[i][j];
// 			r[i][j] = gris;
// 			v[i][j] = gris;
// 			b[i][j] = gris;
// 		}
// 	}
// 	creeImage(r, v, b, image);
// }

// void seuillageNiveauDeGris(unsigned char r[N][N], unsigned char v[N][N],
// 	unsigned char b[N][N], DonneesImageRGB* image, unsigned char seuil)
// {
// 	cree3matrices(r, v, b, image);
// 	for (int i = 0; i < image->hauteurImage; ++i)
// 	{
// 		for (int j = 0; j < image->largeurImage; ++j)
// 		{
// 			unsigned char gris = 0.2125 * r[i][j] + 0.7154 * v[i][j] + 0.0721 * b[i][j];
// 			gris = gris > seuil ? 255 : 0;
// 			r[i][j] = gris;
// 			v[i][j] = gris;
// 			b[i][j] = gris;
// 		}
// 	}
// 	creeImage(r, v, b, image);
// }
