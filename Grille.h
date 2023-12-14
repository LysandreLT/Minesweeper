#ifndef GRILLE
#define GRILLE

void placementBombes(int x, int y, std::array<std::array<int, 30>, 16>& grille);
int nombreRandom(int min, int max);
void affichageGrille(std::array<std::array<int, 30>, 16> grille);
void devoilement(std::array<std::array<int, 30>, 16> &grille, int ligne, int colonne);
void finDePartie(std::array<std::array<int, 30>, 16>& grille);

#endif







