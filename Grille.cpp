#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <ctime>
#include <array>


int nombreRandom(int min, int max)
{
	//srand((unsigned)time(0));
	static constexpr double fraction{ 1.0 / (RAND_MAX + 1.0) };  
	return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}


void placementBombes(int x, int y, std::array<std::array<int, 30>, 16> &grille)
{
	int bombesRestantes = 100;
	int bombesUtilisees{ 0 };
	grille[x][y] = 0;
	if (x + 1 < 16)
	{
		grille[x + 1][y] = 0;
	}
	if (x - 1 >= 0)
	{
		grille[x - 1][y] = 0;
	}
	if (x + 1 < 16 and y + 1 < 30)
	{
		grille[x + 1][y + 1] = 0;
	}
	if (x + 1 < 16 and y - 1 >= 0)
	{
		grille[x + 1][y-1] = 0;
	}
	if (x - 1 > 0 and y + 1 < 30)
	{
		grille[x - 1][y + 1] = 0;
	}
	if (x - 1 > 0 and y - 1 > 0)
	{
		grille[x - 1][y - 1] = 0;
	}
	if (y + 1 < 30)
	{
		grille[x][y + 1] = 0;
	}
	if (y - 1 > 0)
	{
		grille[x][y - 1] = 0;
	}
	while (bombesRestantes != 0)
	{
		//Random first tile
		int tilex = nombreRandom(0, 29);
		int tiley = nombreRandom(0, 15);
		if (grille[tiley][tilex] != 0 and (grille[tiley][tilex] != 19))
		{
			grille[tiley][tilex] = 19;
			bombesRestantes--;
			bombesUtilisees++;
		}
	}

	//Remplissage
	for (int lignes{ 0 }; lignes < 16; lignes++)
	{
		for (int colonnes{ 0 }; colonnes < 30; colonnes++)
		{
			int voisins{ 10 };
			if (grille[lignes][colonnes] != 19)
			{
				if (lignes+1<16 and colonnes+1<30 and grille[lignes+1][colonnes+1] == 19)
				{
					voisins++;
				}
				if (lignes+1<16 and grille[lignes+1][colonnes] == 19)
				{
					voisins++;
				}
				if(lignes+1 < 16 and colonnes-1 >= 0 and grille[lignes+1][colonnes-1] == 19)
				{
					voisins++;
				}
				if (colonnes+1<30 and grille[lignes][colonnes+1] == 19)
				{
					voisins++;
				}
				if (colonnes-1 >= 0 and grille[lignes][colonnes-1] == 19)
				{
					voisins++;
				}
				if (lignes-1 >= 0 and colonnes+1 < 30 and grille[lignes-1][colonnes+1] == 19)
				{
					voisins++;
				}
				if (lignes-1>=0 and grille[lignes-1][colonnes] == 19)
				{
					voisins++;
				}
				if (colonnes-1 >= 0 and lignes-1 >= 0 and grille[lignes-1][colonnes-1] == 19)
				{
					voisins++;
				}
				grille[lignes][colonnes] = voisins;
			}
		}
	}

}


void affichageGrille(std::array<std::array<int, 30>, 16> grille)
{
	for (int lignes{ 0 }; lignes < 16; lignes++)
	{
		for (int colonnes{ 0 }; colonnes < 30; colonnes++)
		{
			std::cout << grille[lignes][colonnes] << " ";
		}
		std::cout << " \n";
	}
}

void devoilement(std::array<std::array<int, 30>, 16> &grille, int ligne, int colonne)
{
	if (ligne + 1 < 16 and grille[ligne + 1][colonne] == 10)
	{
		grille[ligne + 1][colonne] = 0;
		devoilement(grille, ligne+1, colonne);
	}
	if (ligne - 1 >= 0 and grille[ligne - 1][colonne] == 10)
	{
		grille[ligne - 1][colonne] = 0;
		devoilement(grille, ligne - 1, colonne);
	}
	if (colonne + 1 < 30 and grille[ligne][colonne + 1] == 10)
	{
		grille[ligne][colonne + 1] = 0;
		devoilement(grille, ligne, colonne + 1);
	}
	if (colonne - 1 >= 0 and grille[ligne][colonne - 1] == 10)
	{
		grille[ligne][colonne - 1] = 0;
		devoilement(grille, ligne, colonne - 1);
	}
	if (colonne + 1 < 30 and ligne + 1 < 16 and grille[ligne + 1][colonne + 1] == 10)
	{
		grille[ligne + 1][colonne + 1] = 0;
		devoilement(grille, ligne + 1, colonne + 1);
	}
	if (colonne - 1 >= 0 and ligne - 1 >= 0 and grille[ligne - 1][colonne - 1] == 10)
	{
		grille[ligne - 1][colonne - 1] = 0;
		devoilement(grille, ligne-1, colonne - 1);
	}
	if (colonne - 1 >= 0 and ligne + 1 < 16 and grille[ligne + 1][colonne - 1] == 10)
	{
		grille[ligne + 1][colonne - 1] = 0;
		devoilement(grille, ligne + 1, colonne - 1);
	}
	if (colonne + 1 < 30 and ligne - 1 >= 0 and grille[ligne - 1][colonne + 1] == 10)
	{
		grille[ligne - 1][colonne + 1] = 0;
		devoilement(grille, ligne - 1, colonne + 1);
	}
	if (ligne + 1 < 16 and grille[ligne + 1][colonne] > 10)
	{
		grille [ligne + 1][colonne] -= 10;
	}
	if (ligne - 1 >= 0 and grille[ligne - 1][colonne] > 10)
	{
		grille[ligne - 1][colonne] -= 10;
	}
	if (colonne + 1 < 30 and grille[ligne][colonne + 1] > 10)
	{
		grille[ligne][colonne + 1] -= 10;
	}
	if (colonne - 1 >= 0 and grille[ligne][colonne - 1] > 10)
	{
		grille[ligne][colonne - 1] -= 10;
	}
	if (colonne + 1 < 30 and ligne + 1 < 16 and grille[ligne + 1][colonne + 1] > 10)
	{
		grille[ligne + 1][colonne + 1] -= 10;
	}
	if (colonne - 1 >= 0 and ligne - 1 >= 0 and grille[ligne - 1][colonne - 1] > 10)
	{
		grille[ligne - 1][colonne - 1] -= 10;
	}
	if (colonne - 1 >= 0 and ligne + 1 < 16 and grille[ligne + 1][colonne - 1] > 10)
	{
		grille[ligne + 1][colonne - 1] -= 10;
	}
	if (colonne + 1 < 30 and ligne - 1 >= 0 and grille[ligne - 1][colonne + 1] > 10)
	{
		grille[ligne - 1][colonne + 1] -= 10;
	}
}

void finDePartie(std::array<std::array<int, 30>, 16> &grille)
{
	for (int ligne{ 0 }; ligne < 16; ligne++)
	{
		for (int colonne{ 0 }; colonne < 30; colonne++)
		{
			if (grille[ligne][colonne] == 19)
			{
				grille[ligne][colonne] -= 10;
			}
		}
	}
}



