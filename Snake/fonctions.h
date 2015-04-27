/**
 * \file fonctions.h
 * \brief Programme de tests.
 * \author Maxime.C
 * \version 1.0
 * \date 14 novembre 2014
 *
 * Programme d'exécution d'un snake sur l'invite de commande
 *
 */

#ifndef FONCTIONS_H
#define FONCTIONS_H

#include "constantes.h"

void CoordonneesSnake(coordonnee position[H*L],char direction, int taille);
void GrandirSnake(coordonnee position[H*L],char direction, int taille);
void Fruits(char board[H][L],coordonnee* fruit);
int Collision(coordonnee position[H*L],int taille);

#endif