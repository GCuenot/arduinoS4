#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include "GfxLib.h"
#include "BmpLib.h"
#include "ESLib.h"
#include "fonctions.h"
#include "moteur.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <libserialport.h>

#define LARGEUR_FENETRE 1200
#define HAUTEUR_FENETRE 700

#define PASS_1 9
#define PASS_2 9
#define PASS_3 1
#define PASS_4 2

static char distanceChoisie = 'X';
bool affichageInitial = true;
bool affichageprimaire = true;
volatile int keep_running = 1;
static int dernierEtatClic = 0;
struct sp_port *serial_port;
bool recOn = false;
bool codeValide = false;
time_t tempsErreur;
int tentativesIncorrectes = 0;
time_t debutBlocage = 0;
bool estBloque = false;





struct sp_port *open_serial_port(const char *port_name);
void *read_serial_port(void *arg);
void send_command(struct sp_port *port, char command);
void gestionEvenement(EvenementGfx evenement);
void writeToLogFile(const char *message);

int main(int argc, char **argv)
{
    srand(time(NULL));
    const char *port_name = "/dev/ttyACM0";
    serial_port = open_serial_port(port_name);
    if (serial_port == NULL)
    {
        return 1;
    }
    pthread_t serial_thread;
    if (pthread_create(&serial_thread, NULL, read_serial_port, (void *)serial_port))
    {
        fprintf(stderr, "Erreur: Impossible de créer le thread\n");
        return 1;
    }

    initialiseGfx(argc, argv);
    prepareFenetreGraphique("Camera: Anas,Emrys,Guillaume", LARGEUR_FENETRE, HAUTEUR_FENETRE);
    lanceBoucleEvenements();

    keep_running = 0;
    pthread_join(serial_thread, NULL);

    sp_close(serial_port);
    sp_free_port(serial_port);
    return 0;
}

void gestionEvenement(EvenementGfx evenement) {
    static int codeSaisi[4] = {0}; // Tableau pour stocker les chiffres saisis
    static int indexSaisie = 0;    // Indice pour suivre la saisie du code

    switch (evenement) {
        case Affichage:
		    

            if (affichageInitial && !affichageprimaire) {
                afficheFondecran();
                petitrond();
                cercleOnOff2();
                rafraichisFenetre();
                acceuil();
            } 
            else if (!affichageInitial && !affichageprimaire) {
                afficheFondecran();
                petitrond();
                cercleOnOff();
                flechedroite();
                flechegauche();
                flechehaut();
                flechebas();
                rectanglesoundOnOff();
                carre50cm();
                carre1m();
                carre5m();
                carrerec();
                carreclic();
            }

           


            else if (affichageprimaire) {
		    	rafraichisFenetre();
		        afficheTableauCarres();

		        // Affichage du code saisi au-dessus des touches
		        char codeAffiche[5];
		        snprintf(codeAffiche, 5, "%d%d%d%d", codeSaisi[0], codeSaisi[1], codeSaisi[2], codeSaisi[3]);

		        if (estBloque) {
		            // Calcul du temps restant de blocage
		            int secondesRestantes = 60 - (time(NULL) - debutBlocage);
		            if (secondesRestantes > 0) {
		                char messageBlocage[50];
		                snprintf(messageBlocage, 50, "Trop de tentatives. Attendre : %d s", secondesRestantes);

		                couleurCourante(255, 0, 0); // Rouge
		            	afficheChaine(messageBlocage, 24, 10, HAUTEUR_FENETRE - 150);
		            	 } else {
			                estBloque = false;
			                tentativesIncorrectes = 0;
			            }
		      	}

		        else {
		            if (time(NULL) - tempsErreur < 3) {
		                couleurCourante(255, 0, 0); // Rouge
		                
		            } else if (codeValide) {
		                couleurCourante(0, 255, 0); // Vert
		                
		            } else {
		                couleurCourante(255, 255, 255); // Blanc par défaut
		            }


                afficheChaine(codeAffiche, 35, (largeurFenetre() - (3 * 60 + 2 * 10)) / 1.79, hauteurFenetre() - (3 * 60 + 2 * 10));


                rafraichisFenetre();

            }

            afficheDateHeure(); // Affiche la date et l'heure
            rafraichisFenetre();
            break;

        case ClavierSpecial:
            if (!affichageInitial) {
                if (toucheClavier() == ToucheFlecheHaut) {
                    printf("Touche flèche haut pressée.\n");
                    send_command(serial_port, 'H');
                } else if (toucheClavier() == ToucheFlecheBas) {
                    printf("Touche flèche bas pressée.\n");
                    send_command(serial_port, 'B');
                } else if (toucheClavier() == ToucheFlecheDroite) {
                    printf("Touche flèche droite pressée.\n");
                    send_command(serial_port, 'D');
                } else if (toucheClavier() == ToucheFlecheGauche) {
                    printf("Touche flèche gauche pressée.\n");
                    send_command(serial_port, 'G');
                }
            }
            break;

        case Clavier:
            break;

        case BoutonSouris:

            if (etatBoutonSouris() == GaucheAppuye){

                if (affichageprimaire && !estBloque) {
	    			bool clicSurChiffre = false;

				    for (int i = 0; i < 9; i++) {
				        if (abscisseSouris() >= carres[i].x && abscisseSouris() <= carres[i].x + carres[i].largeur &&
				            ordonneeSouris() >= carres[i].y && ordonneeSouris() <= carres[i].y + carres[i].hauteur) {
				            printf("Carré %d cliqué.\n", i + 1);

				        	carreauinverse = true;

				            if (indexSaisie < 4) {
				                codeSaisi[indexSaisie] = i + 1;
				                indexSaisie++;
				                clicSurChiffre = true;
				            }
				            break;
				        }
				    }

				    if (abscisseSouris() >= carres[9].x && abscisseSouris() <= carres[9].x + carres[9].largeur &&
				        ordonneeSouris() >= carres[9].y && ordonneeSouris() <= carres[9].y + carres[9].hauteur) {
				        printf("Carré 0 cliqué.\n");

				    	carreauinverse = true;

				        if (indexSaisie < 4) {
				            codeSaisi[indexSaisie] = 0;
				            indexSaisie++;
				            clicSurChiffre = true;
				        }
				    }

				    if (indexSaisie == 4) {
				        if (codeSaisi[0] == PASS_1 && codeSaisi[1] == PASS_2 && codeSaisi[2] == PASS_3 && codeSaisi[3] == PASS_4) {
				            printf("Bon code !\n");
				            
				            codeValide = true;
				            tentativesIncorrectes = 0;
				            affichageprimaire = false;
				          
				            
				        } else {
				            printf("Mauvais code ! Réessayez.\n");
				            codeValide = false;
				            tempsErreur = time(NULL);
				            tentativesIncorrectes++;
				            if (tentativesIncorrectes >= 4) {
				                estBloque = true;
				                debutBlocage = time(NULL);
				            }
				            memset(codeSaisi, 0, sizeof(codeSaisi));
				            indexSaisie = 0;
				        }
				    }

				    rafraichisFenetre();
				}

				else if (estBloque && time(NULL) - debutBlocage >= 60) {
				    estBloque = false;
				    tentativesIncorrectes = 0;
				}
			
				            
           


















				if(affichageInitial == true && affichageprimaire == false){

					if (pow(abscisseSouris() - (largeurFenetre() * 0.9), 2) +
						pow(ordonneeSouris() - (hauteurFenetre() * 0.85), 2) <=
						pow(largeurFenetre() * 0.07, 2))
					{
						printf("Cercle ON/OFF cliqué.\n");

						if (affichageInitial)
						{
							send_command(serial_port, 'E'); // Envoie 'E' si l'affichage initial est activé
							affichageInitial = false;       // Désactive l'affichage initial
						}
						else
						{
							send_command(serial_port, 'e'); // Envoie 'e' si l'affichage initial est désactivé
							affichageInitial = true;        // Active l'affichage initial
						}

						rafraichisFenetre();
					}


				}

















				else if (affichageInitial == false && affichageprimaire == false){

					if (abscisseSouris() >= ((largeurFenetre()) / 5) * 3 && abscisseSouris() <= (largeurFenetre()) - (((largeurFenetre()) / 12) * 4) &&
						ordonneeSouris() >= (hauteurFenetre() / 6) * 3 && ordonneeSouris() <= (hauteurFenetre()) - ((hauteurFenetre() / 10) * 4.5))
					{
						printf("Flèche droite cliquée.\n");
						send_command(serial_port, 'D');
						clicSurFlecheDroite = true; // Active l'état du clic sur la flèche droite
						rafraichisFenetre();
					}
					else if (abscisseSouris() >= (largeurFenetre() - (largeurFenetre() - ((largeurFenetre() / 12) * 4))) &&
						abscisseSouris() <= (largeurFenetre() - ((largeurFenetre() / 5) * 3)) &&
						ordonneeSouris() >= ((hauteurFenetre() / 6) * 3) &&
						ordonneeSouris() <= (hauteurFenetre() - ((hauteurFenetre() / 10) * 4.5)))
					{
						printf("Flèche gauche cliquée.\n");
						send_command(serial_port, 'G');
						clicSurFlecheGauche = true; // Active l'état du clic sur la flèche gauche
						rafraichisFenetre();
					}
					else if (abscisseSouris() >= (largeurFenetre() / 5) * 2.4 && abscisseSouris() <= (largeurFenetre() / 5) * 2.6 &&
						ordonneeSouris() >= (hauteurFenetre() / 2) + (largeurFenetre() / 12) &&
						ordonneeSouris() <= (hauteurFenetre() / 2) + ((hauteurFenetre() / 10) * 2.7))
					{
						printf("Flèche haut cliquée.\n");
						send_command(serial_port, 'H');
						clicSurFlecheHaut = true; // Active l'état du clic sur la flèche haut
						rafraichisFenetre();
					}
					else if (abscisseSouris() >= (largeurFenetre() / 5) * 2.4 && abscisseSouris() <= (largeurFenetre() / 5) * 2.6 &&
						ordonneeSouris() >= (hauteurFenetre() / 2) - ((hauteurFenetre() / 10) * 2.7) &&
						ordonneeSouris() <= (hauteurFenetre() / 2) - (largeurFenetre() / 12))
					{
						printf("Flèche bas cliquée.\n");
						send_command(serial_port, 'B');
						clicSurFlecheBas = true; // Active l'état du clic sur la flèche bas
						rafraichisFenetre();
					}
					

					else if (abscisseSouris() >= (largeurFenetre() * 0.825) &&
						abscisseSouris() <= (largeurFenetre() * 0.825) + (largeurFenetre() * 0.15) &&
						ordonneeSouris() <= hauteurFenetre() * 0.65 &&
						ordonneeSouris() >= (hauteurFenetre() * 0.65) - (hauteurFenetre() * 0.08))
					{
						printf("Rectangle Sound ON/OFF cliqué.\n");
						if (soundOn == true)
						{
							send_command(serial_port, 's');
						}
						else
						{
							send_command(serial_port, 'S');
						}

						if (soundOn == true)
						{
							soundOn = false;
						}
						else if (soundOn == false)
						{
							soundOn = true;
						}

						rafraichisFenetre();
					}
					else if (abscisseSouris() >= largeurFenetre() * 0.828 &&
		                     abscisseSouris() <= largeurFenetre() * 0.878 &&
		                     ordonneeSouris() >= hauteurFenetre() * 0.5 - hauteurFenetre() * 0.08 &&
		                     ordonneeSouris() <= hauteurFenetre() * 0.5)
		            {
		                printf("50cm cliqué.\n");
		                send_command(serial_port, 'X');
		                distanceChoisie = 'X';
		 
		                bouton50cmClique = true;
		                bouton1mClique = false;
		                bouton5mClique = false;
		                rafraichisFenetre();
		            }
		            else if (abscisseSouris() >= largeurFenetre() * 0.878 &&
		                     abscisseSouris() <= largeurFenetre() * 0.928 &&
		                     ordonneeSouris() >= hauteurFenetre() * 0.5 - hauteurFenetre() * 0.08 &&
		                     ordonneeSouris() <= hauteurFenetre() * 0.5)
		            {
		                printf("1m cliqué.\n");
		                send_command(serial_port, 'Y');
		                distanceChoisie = 'Y';
		 
		                bouton50cmClique = false;
		                bouton1mClique = true;
		                bouton5mClique = false;
		                rafraichisFenetre();
		            }
		            else if (abscisseSouris() >= largeurFenetre() * 0.928 &&
		                     abscisseSouris() <= largeurFenetre() * 0.978 &&
		                     ordonneeSouris() >= hauteurFenetre() * 0.5 - hauteurFenetre() * 0.08 &&
		                     ordonneeSouris() <= hauteurFenetre() * 0.5)
		            {
		                printf("5m cliqué.\n");
		                send_command(serial_port, 'Z');
		                distanceChoisie = 'Z';
		 
		                bouton50cmClique = false;
		                bouton1mClique = false;
		                bouton5mClique = true;
		                rafraichisFenetre();
		            }
		 
					else if (abscisseSouris() >= largeurFenetre() * 0.825 &&
						abscisseSouris() <= largeurFenetre() * 0.975 &&
						ordonneeSouris() >= hauteurFenetre() * 0.22 &&
						ordonneeSouris() <= hauteurFenetre() * 0.3)
					{
						printf("Bouton REC cliqué.\n");
						recOn = !recOn; // Toggle l'état d'enregistrement

						if (recOn)
						{
							// Démarrer l'enregistrement
							printf("Démarrage de l'enregistrement...\n");
							// Obtenir la date et l'heure actuelles
							char datetime[20];
							getFormattedDateTime(datetime, sizeof(datetime));

							// Construire le nom du fichier
							char command[256];
							snprintf(command, sizeof(command), "mkdir -p videos && ffmpeg -f v4l2 -r 25 -s 640x480 -i /dev/video0 -c:v libx264 -pix_fmt yuv420p -preset ultrafast videos/video_%s.mp4 &", datetime);

							// Exécuter la commande
							system(command);
						}
						else
						{
							// Arrêter l'enregistrement
							printf("Arrêt de l'enregistrement...\n");
							system("pkill ffmpeg");
						}

						rafraichisFenetre();
					}
					else if (abscisseSouris() >= largeurFenetre() * 0.825 && abscisseSouris() <= largeurFenetre() * 0.975 &&
						ordonneeSouris() >= hauteurFenetre() * 0.07 && ordonneeSouris() <= hauteurFenetre() * 0.15)
					{
						printf("Bouton CLIC cliqué.\n");

						// Obtenir la date et l'heure actuelles
						char datetime[20];
						getFormattedDateTime(datetime, sizeof(datetime));

						// Construire le nom du fichier
						char command[256];
						snprintf(command, sizeof(command), "mkdir -p photos && ffmpeg -f v4l2 -video_size 640x480 -i /dev/video0 -frames:v 1 photos/photo_%s.png", datetime);

						captureEcran = true;

						// Prendre une capture d'écran
						system(command);

						rafraichisFenetre();
					}

					else if (pow(abscisseSouris() - (largeurFenetre() * 0.9), 2) +
						pow(ordonneeSouris() - (hauteurFenetre() * 0.85), 2) <=
						pow(largeurFenetre() * 0.07, 2))
					{
						printf("Cercle ON/OFF cliqué.\n");

						if (affichageInitial)
						{
							send_command(serial_port, 'E'); // Envoie 'E' si l'affichage initial est activé
							affichageInitial = false;       // Désactive l'affichage initial
						}
						else
						{
							send_command(serial_port, 'e'); // Envoie 'e' si l'affichage initial est désactivé
							affichageInitial = true;        // Active l'affichage initial
						}

						rafraichisFenetre();

					}
				}
			}

		

			else if (etatBoutonSouris() == GaucheRelache){

				clicSurFlecheDroite = false; // Désactive l'état du clic sur la flèche droite lorsque le clic est relâché
				clicSurFlecheGauche = false;
				clicSurFlecheHaut = false;
				clicSurFlecheBas = false;
				captureEcran = false;
				carreauinverse = false;


				rafraichisFenetre();
			}
		}	
		break;

		case Inactivite:
		rafraichisFenetre();
		break;

		case Redimensionnement:
		glViewport(0, 0, largeurFenetre(), hauteurFenetre());
		break;

		case Temporisation:
		rafraichisFenetre();
		break;
	}
}

struct sp_port *open_serial_port(const char *port_name)
{
	struct sp_port *port;
	sp_get_port_by_name(port_name, &port);
	if (port == NULL)
	{
		fprintf(stderr, "Erreur: Impossible d'ouvrir le port série %s\n", port_name);
		return NULL;
	}

	if (sp_open(port, SP_MODE_READ_WRITE) != SP_OK)
	{
		fprintf(stderr, "Erreur: Impossible d'ouvrir le port série %s\n", port_name);
		sp_free_port(port);
		return NULL;
	}

	if (sp_set_baudrate(port, 9600) != SP_OK)
	{
		fprintf(stderr, "Erreur: Impossible de configurer le baudrate du port série %s\n", port_name);
		sp_close(port);
		sp_free_port(port);
		return NULL;
	}

	return port;
}

void *read_serial_port(void *arg) {
	struct sp_port *port = (struct sp_port *)arg;
	char buffer[1];
	while (keep_running) {
		int bytes_read = sp_nonblocking_read(port, buffer, sizeof(buffer));
		if (bytes_read > 0 && buffer[0] == 'N' && soundOn == true) {
			printf("INTRUS !!!!! \n");

			// Obtenir la date et l'heure actuelles
			char datetime[20];
			getFormattedDateTime(datetime, sizeof(datetime));

				// Construire le nom du fichier
			char command[256];
			snprintf(command, sizeof(command), "mkdir -p photos && ffmpeg -f v4l2 -video_size 640x480 -i /dev/video0 -frames:v 1 photos/photo_%s.png", datetime);


				// Prendre une capture d'écran
			system(command);


			writeToLogFile("INTRUS !!!!!");
		} else if (bytes_read > 0 && buffer[0] == 'N' && soundOn == false) {
			printf("IL Y A QUELQU'UN DEVANT LA PORTE !!!!!\n");
			writeToLogFile("IL Y A QUELQU'UN DEVANT LA PORTE !!!!!");
		}
	}
	return NULL;
}

void send_command(struct sp_port *port, char command)
{
	sp_nonblocking_write(port, &command, 1);
}



void writeToLogFile(const char *message) {
    FILE *file = fopen("Historique_alerte.txt", "a");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }
 
    char datetime[20];
    getFormattedDateTime(datetime, sizeof(datetime));
    if (distanceChoisie == 'X') {
        fprintf(file, "[%s] %s (distance choisie : 50cm)\n", datetime, message);
    }
    if (distanceChoisie == 'Y') {
        fprintf(file, "[%s] %s (distance choisie : 1m)\n", datetime, message);
    }
    if (distanceChoisie == 'Z') {
        fprintf(file, "[%s] %s (distance choisie : 5m)\n", datetime, message);
    }
    fclose(file);
}