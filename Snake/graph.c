/**
 * \file      graph.c
 * \author    Maxime.C
 * \version   1.0
 * \date      14 novembre 2014
 * \brief     Fonctions graphiques du snake
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/times.h>
#include <termios.h>
#include <unistd.h>

#include "graph.h"
#include "constantes.h"
#include "fonctions.h"

/**
 * \brief lit l'entrée clavier
 * \details Lit un unique caractère tapé
 *          Si aucun caractère n'est tapé à temps, renvoie -1
 *          Appuyer sur Entrée n'est pas nécessaire
 *          N'affiche pas le caractère à l'écran
 *          Renvoie le code ASCII du caractère
 * \param taille du Snake
 * \param speed définissant la taille à partir de laquelle le snake accélère
*/

 int readKey(int taille,int speed) 
{
	struct termios oldattr, newattr;
	int ch;
	tcgetattr( STDIN_FILENO, &oldattr );
	newattr = oldattr;
	newattr.c_lflag &= ~( ICANON | ECHO );
	newattr.c_cc[VMIN] = 0;
	newattr.c_cc[VTIME] = (taille < speed) ? 2 : 1;
	tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
	return ch;
}

/**
 * \brief Fonction d'initialisation de la matrice à des caractères vides
 * \param board tableau de caractères de hauteur H et de largeur L
 */

void init(char board[H][L])
{
	int i,j;
	for(i=0;i<H;i++) {
		for(j=0;j<L;j++) {
			board[i][j]=' ';
		}
	}
		
}

/**
 * \brief Fonction faisant une update du tableau à l'écran
 * \param board tableau de caractères de hauteur H et de largeur L
 */

void display(char board[H][L]) 
{
	int i,j;
	system("clear");
	for (i=0;i<L+1;i++)
	{
		printf("*");
	}
	printf("*\n");
	for(i=0;i<H;i++) {
		printf("*");
		for(j=0;j<L;j++) {
			printf("%c",board[i][j]);
		}
		printf("*\n");
	}
	for (i=0;i<L+1;i++)
	{
		printf("*");
	}
	printf("*\n");
	printf("Touches :\nHaut E, Bas D\nGauche S, Droite F\nPour quitter, appuyez sur Q\n");
}

/**
 * \brief Fonction utilisée uniquement lors du debug, affichant les coordonnées du snake
 * \param board tableau de caractères de hauteur H et de largeur L* \param board tableau de caractères de hauteur H et de largeur L
 */

void display2(coordonnee position[H*L],int taille)
{

	int i;
	for (i=0;i<taille;i++)
	{
		printf("Coordonnées de l'élément %d :[%d,%d]\n",i,position[i].x,position[i].y);
	}
}

/**
 * \brief Fonction initialisant chaque paramètre :
 * \param position tableau contenant les coordonnées du snake
 * \param b matrice contenant la représentation graphique du snake (affichée par display)
 * \param px et py les coordonnées de la tête initialement
 * \param fruit valeur contenant les coordonnées du premier fruit affiché
 * \param taille du Snake
 */

void InitialiserSnake(coordonnee position[H*L], char b[H][L],int px,int py,coordonnee* fruit,int taille)
{
	int i;
	int x,y;
	struct tms clk;
	srand(times(&clk));
	x=rand()%L;
	y=rand()%H;
	fruit->x=x;
	fruit->y=y;
	for (i=0;i<taille;i++)
	{
	 	b[py][px-i]='#';
		position[i].x=px-taille+i;
		position[i].y=py;
	}
	for (i=taille;i<H*L;i++)
	{
		position[i].x=0;
		position[i].y=0;
	}
	b[py][px]='@';
	Fruits(b,fruit);
	b[fruit->y][fruit->x]='o';
}