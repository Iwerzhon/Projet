/**
 * \file graph.h
 * \brief Programme de tests.
 * \author Maxime.C
 * \version 1.0
 * \date 14 novembre 2014
 *
 * Programme d'exécution d'un snake sur l'invite de commande
 *
 */

#ifndef GRAPH_H
#define GRAPH_H

#include "constantes.h"

int readKey(int taille,int speed);
void init(char board[H][L]);
void display(char board[H][L]);
void display2(coordonnee position[H*L],int taille);
void InitialiserSnake(coordonnee position[H*L], char b[H][L],int px,int py,coordonnee* fruit,int taille);

#endif