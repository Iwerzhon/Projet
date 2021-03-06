/**
 * \file main.c
 * \brief Programme de tests.
 * \author Maxime.C
 * \version 1.0
 * \date 14 novembre 2014
 *
 * Programme d'exécution d'un snake sur l'invite de commande
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/times.h>
#include <termios.h>
#include <unistd.h>

#include "fonctions.h"
#include "graph.h"
#include "constantes.h"


/**
 * \brief Base du jeu
 * \details Après avoir initialisé le snake, on rentre dans la boucle
 * 			On ne prend en compte le readkey que si il est correct (un mouvement vers la gauche ou vers la droite uniquement)
 *			Si oui, on recalcule le snake 
 *			-> dans le cas où il mange un fruit on
 *			-> ou bien dans le cas où il va sur une case vide
 *			Si jamais il se mord la queue, la partie est finie.
 *			Le jeu accélère quand taille atteint la valeur speed.
 *			La taille du tableau (H,L) est définie dans le fichier constantes.h
 */

int main() {
	/* Initiation des variables */
	int go=1; 
	int i;
	int taille=5; /* taille initiale du snake */
	int px=L/2, py=H/2;
	char b[H][L], c='f'; /* b matrice contenant graphiquement le snake, mouvement initialisé vers la droite */
	int speed=15; /* Taille du snake à partir duquel le jeu accélère */
	char d;
	coordonnee position[H*L]; /* tableau de coordonnées du Snake */
	coordonnee fruit; 
	init(b);
	fruit.x=0;
	fruit.y=0;
	InitialiserSnake(position,b,px,py,&fruit,taille);
	while (go) 
	{
		display(b);
//		display2(position,taille);
		d=readKey(taille,speed);
		/* printf("%04x, %c",c,c);  Afficher le code hexa des touches pour l'analyse du clavier */
		if (d=='q') go=0;
		else 
		{
			switch(d) /* Modifier la direction en gérant les exceptions */
			{
				case 's': /* Si on se déplace initialement horizontalement... */
				case 'f':
					if(c == 'd' || c == 'e') /* et que la touche pressée est horizontale */
						c=d; /* Alors le mouvement est accepté */
					break;
				case 'd':
				case 'e':
					if(c == 's' || c == 'f')
						c=d;
					break;
			}
			CoordonneesSnake(position,c,taille);
			init(b);
			go=Collision(position,taille);
			if (position[taille-1].y==fruit.y && position[taille-1].x==fruit.x) /* Calculer et Afficher le snake si il mange un fruit */
			{
				taille=taille+1;
				GrandirSnake(position,c,taille);
				for (i=0;i<taille;i++)
				{
					b[position[i].y][position[i].x]='#';
				}
				Fruits(b,&fruit);
				b[fruit.y][fruit.x]='o';
				b[position[taille-1].y][position[taille-1].x]='@';
			}
			else
			{
				for (i=0;i<taille;i++) /* Calculer et Afficher le snake lors d'un mouvement où l'on ne mange pas de fruit */
				{
					b[position[i].y][position[i].x]='#';
				}
				b[fruit.y][fruit.x]='o';
				b[position[taille-1].y][position[taille-1].x]='@';
			}
		}
	}
	printf("\n#### #### #   # ####   #### #   # #### ####\n#    #  # ##### #      #  # #   # #    # #\n# ## #### # # # ###    #  # #   # ##   ##\n#  # #  # #   # #      #  #  # #  #    # #\n#### #  # #   # ####   ####   #   #### #  #\n\n");
	printf("Taille finale du serpent : %d\n\n",taille);
	return EXIT_SUCCESS;
}
