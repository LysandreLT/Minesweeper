#include <SFML/Graphics.hpp>
#include <iostream>
#include "grille.h"
#include <array>

int main()
{
	int longueurFenetre{ 1450 };
	int largeurFenetre{ 790 };
	int longueurCase{ longueurFenetre / 30 };
	int largeurCase{ largeurFenetre / 16 };
	bool partieEnCours{false};

	//Chargement des textures
	sf::Texture case1;
	case1.loadFromFile("case1.bmp");
	sf::Sprite SCase1;
	SCase1.setTexture(case1);
	SCase1.setScale(float(3), float(3));

	sf::Texture case2;
	case2.loadFromFile("case2.bmp");
	sf::Sprite SCase2;
	SCase2.setTexture(case2);
	SCase2.setScale(float(3), float(3));

	sf::Texture case3;
	case3.loadFromFile("case3.bmp");
	sf::Sprite SCase3;
	SCase3.setTexture(case3);
	SCase3.setScale(float(3), float(3));

	sf::Texture case4;
	case4.loadFromFile("case4.bmp");
	sf::Sprite SCase4;
	SCase4.setTexture(case4);
	SCase4.setScale(float(3), float(3));

	sf::Texture case5;
	case5.loadFromFile("case5.bmp");
	sf::Sprite SCase5;
	SCase5.setTexture(case5);
	SCase5.setScale(float(3), float(3));

	sf::Texture case6;
	case6.loadFromFile("case6.bmp");
	sf::Sprite SCase6;
	SCase6.setTexture(case6);
	SCase6.setScale(float(3), float(3));

	sf::Texture case7;
	case7.loadFromFile("case7.bmp");
	sf::Sprite SCase7;
	SCase7.setTexture(case7);
	SCase7.setScale(float(3), float(3));

	sf::Texture case8;
	case8.loadFromFile("case8.bmp");
	sf::Sprite SCase8;
	SCase8.setTexture(case8);
	SCase8.setScale(float(3), float(3));

	sf::Texture drapeau;
	drapeau.loadFromFile("drapeau.bmp");
	sf::Sprite SDrapeau;
	SDrapeau.setTexture(drapeau);
	SDrapeau.setScale(float(3), float(3));

	sf::Texture mine;
	mine.loadFromFile("mine.bmp");
	sf::Sprite SMine;
	SMine.setTexture(mine);
	SMine.setScale(float(3), float(3));

	sf::Texture mine2;
	mine2.loadFromFile("mine2.bmp");
	sf::Sprite SMine2;
	SMine2.setTexture(mine2);
	SMine2.setScale(float(3), float(3));

	sf::Texture cache;
	cache.loadFromFile("cache.bmp");
	sf::Sprite SCache;
	SCache.setTexture(cache);
	SCache.setScale(float(3), float(3));

	sf::Texture perdu;
	perdu.loadFromFile("perdu.bmp");
	sf::Sprite SPerdu;
	SPerdu.setTexture(perdu);
	SPerdu.setScale(float(3), float(3));

	sf::Texture rien;
	rien.loadFromFile("rien.bmp");
	sf::Sprite SRien;
	SRien.setTexture(rien);
	SRien.setScale(float(3), float(3));



	//Chargement de la fenêtre
	sf::RenderWindow fenetre(sf::VideoMode(longueurFenetre, largeurFenetre), "Démineur");

	//Chargement de la grille
	srand(static_cast<unsigned int>(std::time(nullptr)));
	std::array<std::array<int, 30>, 16> grille;
	
	while (fenetre.isOpen())
	{
		//événements 
		sf::Event evenement;
		while (fenetre.pollEvent(evenement))
		{
			if (evenement.type == sf::Event::Closed)
			{
				fenetre.close();
			}
			if (evenement.type == sf::Event::MouseButtonReleased)
			{
				if (evenement.mouseButton.button == sf::Mouse::Left)
				{
					int ligne{ evenement.mouseButton.y / largeurCase };
					int colonne{ evenement.mouseButton.x / longueurCase };
					if (partieEnCours == false)
					{
						partieEnCours = true;
						placementBombes(ligne, colonne, grille);
						devoilement(grille, ligne, colonne);
					}
					else
					{
						if (grille[ligne][colonne] >= 10 and grille[ligne][colonne] <= 19)
						{
							grille[ligne][colonne] -= 10;
							if (grille[ligne][colonne] == 9)
							{
								grille[ligne][colonne] = 99;
								finDePartie(grille);
							}
							if (grille[ligne][colonne] == 0)
							{
								devoilement(grille, ligne, colonne);
							}
						}
					}
				}
				if (evenement.mouseButton.button == sf::Mouse::Right)
				{
					int ligne{ evenement.mouseButton.y / largeurCase };
					int colonne{ evenement.mouseButton.x / longueurCase };	
					if (grille[ligne][colonne] >= 20 and grille[ligne][colonne] < 30)
					{
						grille[ligne][colonne] -= 10;
					}
					else if (grille[ligne][colonne] >= 10 and grille[ligne][colonne] <= 19)
					{
						grille[ligne][colonne] += 10;
					}
				
				}
			}
		}
		//Affichage
		int tile{ 0 };
		if (partieEnCours == true)
		{
			fenetre.clear();
			for (float lignes{ 0 }; lignes < 16; lignes++)
			{
				for (float colonnes{ 0 }; colonnes < 30; colonnes++)
				{
					tile = grille[int(lignes)][int(colonnes)];
					switch (tile)
					{
					case 0:
						SRien.setPosition(sf::Vector2f(colonnes * longueurCase, lignes * largeurCase));
						fenetre.draw(SRien);
						break;
					case 1:
						SCase1.setPosition(sf::Vector2f(colonnes * longueurCase, lignes * largeurCase));
						fenetre.draw(SCase1);
						break;
					case 2:
						SCase2.setPosition(sf::Vector2f(colonnes * longueurCase, lignes * largeurCase));
						fenetre.draw(SCase2);
						break;
					case 3:
						SCase3.setPosition(sf::Vector2f(colonnes * longueurCase, lignes * largeurCase));
						fenetre.draw(SCase3);
						break;
					case 4:
						SCase4.setPosition(sf::Vector2f(colonnes * longueurCase, lignes * largeurCase));
						fenetre.draw(SCase4);
						break;
					case 5:
						SCase5.setPosition(sf::Vector2f(colonnes * longueurCase, lignes * largeurCase));
						fenetre.draw(SCase5);
						break;
					case 6:
						SCase6.setPosition(sf::Vector2f(colonnes * longueurCase, lignes * largeurCase));
						fenetre.draw(SCase6);
						break;
					case 7:
						SCase7.setPosition(sf::Vector2f(colonnes * longueurCase, lignes * largeurCase));
						fenetre.draw(SCase7);
						break;
					case 8:
						SCase8.setPosition(sf::Vector2f(colonnes * longueurCase, lignes * largeurCase));
						fenetre.draw(SCase8);
					case 9:
						SMine.setPosition(sf::Vector2f(colonnes * longueurCase, lignes * largeurCase));
						fenetre.draw(SMine);
						break;
					case 99:
						SPerdu.setPosition(sf::Vector2f(colonnes * longueurCase, lignes * largeurCase));
						fenetre.draw(SPerdu);
						partieEnCours = false;
						break;
					case 20: case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29:
						SDrapeau.setPosition(sf::Vector2f(colonnes * longueurCase, lignes * largeurCase));
						fenetre.draw(SDrapeau);
						break;
					default:
						SCache.setPosition(sf::Vector2f(colonnes * longueurCase, lignes * largeurCase));
						fenetre.draw(SCache);
						break;
					}
				}
			}
			fenetre.display();
		}
	}



	return 0;
}