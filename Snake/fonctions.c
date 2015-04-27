/**
 * \file      fonctions.c
 * \author    Maxime.C
 * \version   1.0
 * \date      14 novembre 2014
 * \brief     Fonctions usuelles pour gérer le snake (en dehors des fonctions graphiques)
 *
 */

 #include <stdlib.h>
#include <sys/times.h>

#include "fonctions.h"
#include "constantes.h"


/**
 * \brief Fonction déplaçant le snake
 * \param position tableau contenant les coordonnéées du Snake
 * \param direction touche directionnelle (e = haut, s = gauche, d = bas, f = droite)
 * \param taille du Snake
 */

void CoordonneesSnake(coordonnee position[H*L],char direction, int taille)
{
	int i;
	for (i=0;i<taille-1;i++)
	{
		position[i]=position[i+1];
	}
	switch (direction)
	{
		case 'd':
		case 0x0042: /* flèche du bas */
			position[taille-1].y=position[taille-1].y+1; if (position[taille-1].y==H) position[taille-1].y = 0;
			break;
		case 'e':
		case 0x0041: /* flèche du haut */
			position[taille-1].y=position[taille-1].y-1; if (position[taille-1].y<0) position[taille-1].y = H-1;
			break;
		case 'f':
		case 0x0043: /* flèche de droite */
			position[taille-1].x=position[taille-1].x+1; if (position[taille-1].x==L) position[taille-1].x = 0;
			break;
		case 's':
		case 0x0044: /* flèche de gauche */
			position[taille-1].x=position[taille-1].x-1; if (position[taille-1].x<0) position[taille-1].x = L-1;
			break;
		default:
		break;
	}	
}

/**
 * \brief Fonction conservant la queue du Snake, tout en l'agrandissant
 * \param position tableau contenant les coordonnéées du Snake
 * \param direction touche directionnelle (e = haut, s = gauche, d = bas, f = droite)
 * \param taille du Snake
 */

void GrandirSnake(coordonnee position[H*L],char direction, int taille)
{
	int i;
	for(i=taille-1;i>0;i=i-1)
	{
		position[i]=position[i-1];
	}

		switch (direction)
	{
		case 'd':
		case 0x0042: /* flèche du bas */
			position[taille].y=position[taille].y+1; if (position[taille].y==H) position[taille].y = 0;
			break;
		case 'e':
		case 0x0041: /* flèche du haut */
			position[taille].y=position[taille].y-1; if (position[taille].y<0) position[taille].y = H-1;
			break;
		case 'f':
		case 0x0043: /* flèche de droite */
			position[taille].x=position[taille].x+1; if (position[taille].x==L) position[taille].x = 0;
			break;
		case 's':
		case 0x0044: /* flèche de gauche */
			position[taille].x=position[taille].x-1; if (position[taille].x<0) position[taille].x = L-1;
			break;
		default:
		break;
	}	
}

/**
 * \brief Fonction faisant apparaître un nouveau fruit
 * \param board tableau de caractères de hauteur H et de largeur L
 * \param fruit contenant les coordonnées du fruit à afficher
 */

void Fruits(char board[H][L],coordonnee* fruit)
{
	int x,y;
	struct tms clk;
	srand(times(&clk));
	x=rand()%L;
	y=rand()%H;
	while (board[y][x]!=' ') 
	{
		x=rand()%L;
		y=rand()%H;
	}
	fruit->x=x;
	fruit->y=y;
}

/**
 * \brief Fonction s'occupant des collisions (si jamais collision il y a, le jeu s'arrête)
 * \param position tableau contenant les coordonnéées du Snake
 * \param taille du Snake
 */

int Collision(coordonnee position[H*L],int taille)
{
	int res=1;
	int i;
	for (i=0;i<taille-1;i++)
	{
		if (position[i].x==position[taille-1].x && position[i].y==position[taille-1].y) res=0; 
	}
	return res;
}