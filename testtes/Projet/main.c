#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
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

static int dernierEtatClic = 0; // Déclaration de la variable globale
struct sp_port* serial_port; // Pointeur vers le port série

// États des éléments
static int etatFlecheDroite = 0;
static int etatFlecheGauche = 0;
static int etatFlecheHaut = 0;
static int etatFlecheBas = 0;
static int etatCercleOnOff = 0;
static int etatRectangleSoundOnOff = 0;
static int etatRectangleRec = 0;
static int etatRectangleClic = 0;

// Déclaration de la fonction pour ouvrir le port série
struct sp_port* open_serial_port(const char* port_name);

// Déclaration de la fonction pour envoyer une commande à l'Arduino
void send_command(struct sp_port* port, char command);

void gestionEvenement(EvenementGfx evenement);

int main(int argc, char **argv){
    srand(time(NULL));

    // Ouverture du port série
    const char* port_name = "/dev/ttyACM0"; // Changez cela selon le port série de votre Arduino
    serial_port = open_serial_port(port_name);
    if (serial_port == NULL) {
        return 1;
    }

    initialiseGfx(argc, argv);
    prepareFenetreGraphique("GfxLib", LARGEUR_FENETRE, HAUTEUR_FENETRE);
    lanceBoucleEvenements();

    // Fermeture du port série
    sp_close(serial_port);
    sp_free_port(serial_port);

    return 0;
}

void gestionEvenement(EvenementGfx evenement) {
    switch (evenement) {
        case Affichage:
            afficheFondecran();
            flechedroite();
            flechegauche();
            flechehaut();
            flechebas();
            cercleOnOff();
            rectanglesoundOnOff();
            carrerec();
            carreclic();
            break;

        case Clavier:
            // Ajoutez ici le code pour gérer les événements de clavier si nécessaire
            break;

        case Souris:
            int etatClic = etatBoutonSouris();
            if (etatClic != dernierEtatClic) {
                if (etatClic == GaucheAppuye) {
                    // Ajoutez ici le code pour gérer le clic de la souris
                    printf("Clic de la souris enfoncé.\n");
                } else {
                    // Ajoutez ici le code pour gérer le relâchement du clic de la souris
                    printf("Clic de la souris relâché.\n");
                }
                dernierEtatClic = etatClic; // Met à jour le dernier état du clic
            }
            break;

        case BoutonSouris:
            if (etatBoutonSouris() == GaucheAppuye) {
                // Vérifie si la souris est cliquée sur la flèche droite
                if (abscisseSouris() >= ((largeurFenetre())/ 5) * 3 && abscisseSouris() <= (largeurFenetre()) - (((largeurFenetre())/ 12) *4) &&
                    ordonneeSouris() >= (hauteurFenetre() / 6) * 3 && ordonneeSouris() <= (hauteurFenetre()) -((hauteurFenetre() / 10) * 4.5)) {
                    // Action pour la flèche droite
                    printf("Flèche droite cliquée.\n");
                    if (etatFlecheDroite) {
                        send_command(serial_port, 'A');
                        etatFlecheDroite = 0;
                    } else {
                        send_command(serial_port, 'a');
                        etatFlecheDroite = 1;
                    }
                }
                // Vérifie si la souris est cliquée sur la flèche gauche
                else if (abscisseSouris() >= (largeurFenetre() - (largeurFenetre() - ((largeurFenetre() / 12) * 4))) && 
                         abscisseSouris() <= (largeurFenetre() - ((largeurFenetre() / 5) * 3)) &&
                         ordonneeSouris() >= ((hauteurFenetre() / 6) * 3) && 
                         ordonneeSouris() <= (hauteurFenetre() - ((hauteurFenetre() / 10) * 4.5)) ) {
                    // Action pour la flèche gauche
                    printf("Flèche gauche cliquée.\n");
                    if (etatFlecheGauche) {
                        send_command(serial_port, 'B');
                        etatFlecheGauche = 0;
                    } else {
                        send_command(serial_port, 'b');
                        etatFlecheGauche = 1;
                    }
                }
                // Vérifie si la souris est cliquée sur la flèche haut
                else if (abscisseSouris() >= (largeurFenetre() / 5) * 2.4 && abscisseSouris() <= (largeurFenetre() / 5) * 2.6 &&
                         ordonneeSouris() >= (hauteurFenetre() / 2) + (largeurFenetre() / 12) && ordonneeSouris() <= (hauteurFenetre() / 2) + ((hauteurFenetre() / 10) * 2.7)) {
                    // Action pour la flèche haut
                    printf("Flèche haut cliquée.\n");
                    if (etatFlecheHaut) {
                        send_command(serial_port, 'C');
                        etatFlecheHaut = 0;
                    } else {
                        send_command(serial_port, 'c');
                        etatFlecheHaut = 1;
                    }
                }
                // Vérifie si la souris est cliquée sur la flèche bas
                else if (abscisseSouris() >= (largeurFenetre() / 5) * 2.4 && abscisseSouris() <= (largeurFenetre() / 5) * 2.6 &&
                         ordonneeSouris() >= (hauteurFenetre() / 2) - ((hauteurFenetre() / 10) * 2.7) && ordonneeSouris() <= (hauteurFenetre() / 2) - (largeurFenetre() / 12)) {
                    // Action pour la flèche bas
                    printf("Flèche bas cliquée.\n");
                    if (etatFlecheBas) {
                        send_command(serial_port, 'D');
                        etatFlecheBas = 0;
                    } else {
                        send_command(serial_port, 'd');
                        etatFlecheBas = 1;
                    }
                }
                // Vérifie si la souris est cliquée sur le cercle ON/OFF
                else if (pow(abscisseSouris() - (largeurFenetre() * 0.9), 2) + pow(ordonneeSouris() - (hauteurFenetre() * 0.85), 2) <= pow(largeurFenetre() * 0.07, 2)) {
                    // Action pour le cercle ON/OFF
                    printf("Cercle ON/OFF cliqué.\n");
                    if (etatCercleOnOff) {
                        send_command(serial_port, 'E');
                        etatCercleOnOff = 0;
                    } else {
                        send_command(serial_port, 'e');
                        etatCercleOnOff = 1;
                    }
                }
                // Vérifie si la souris est cliquée sur le rectangle Sound ON/OFF
                else if (abscisseSouris() >= (largeurFenetre() * 0.825) && abscisseSouris() <= (largeurFenetre() * 0.825) + (largeurFenetre() * 0.15) &&
                         ordonneeSouris() <= hauteurFenetre() * 0.65 && ordonneeSouris() >= (hauteurFenetre() * 0.65) - (hauteurFenetre() * 0.08)) {
                    // Action pour le rectangle Sound ON/OFF
                    printf("Rectangle Sound ON/OFF cliqué.\n");
                    if (etatRectangleSoundOnOff) {
                        send_command(serial_port, 'F');
                        etatRectangleSoundOnOff = 0;
                    } else {
                        send_command(serial_port, 'f');
                        etatRectangleSoundOnOff = 1;
                    }
                }
                // Vérifie si la souris est cliquée sur le rectangle REC
                else if (abscisseSouris() >= (largeurFenetre() * 0.825) && abscisseSouris() <= (largeurFenetre() * 0.825) + (largeurFenetre() * 0.15) &&
                         ordonneeSouris() <= hauteurFenetre() * 0.4 && ordonneeSouris() >= (hauteurFenetre() * 0.4) - (hauteurFenetre() * 0.08)) {
                    // Action pour le rectangle REC
                    printf("Rectangle REC cliqué.\n");
                    if (etatRectangleRec) {
                        send_command(serial_port, 'G');
                        etatRectangleRec = 0;
                    } else {
                        send_command(serial_port, 'g');
                        etatRectangleRec = 1;
                    }
                }
                // Vérifie si la souris est cliquée sur le rectangle CLIC
                else if (abscisseSouris() >= (largeurFenetre() * 0.825) && abscisseSouris() <= (largeurFenetre() * 0.825) + (largeurFenetre() * 0.15) &&
                         ordonneeSouris() <= hauteurFenetre() * 0.3 && ordonneeSouris() >= (hauteurFenetre() * 0.3) - (hauteurFenetre() * 0.08)) {
                    // Action pour le rectangle CLIC
                    printf("Rectangle CLIC cliqué.\n");
                    if (etatRectangleClic) {
                        send_command(serial_port, 'H');
                        etatRectangleClic = 0;
                    } else {
                        send_command(serial_port, 'h');
                        etatRectangleClic = 1;
                    }
                }
            }
            break;

        case Inactivite:
            // Ajoutez ici le code pour gérer les événements d'inactivité si nécessaire
            break;

        case Redimensionnement:
            // Ajoutez ici le code pour gérer les événements de redimensionnement de la fenêtre si nécessaire
            break;
    }
}

// Fonction pour ouvrir le port série
struct sp_port* open_serial_port(const char* port_name) {
    struct sp_port* port;
    enum sp_return result = sp_get_port_by_name(port_name, &port);
    if (result != SP_OK) {
        fprintf(stderr, "Erreur: Impossible d'obtenir le port série\n");
        return NULL;
    }

    result = sp_open(port, SP_MODE_WRITE);
    if (result != SP_OK) {
        fprintf(stderr, "Erreur: Impossible d'ouvrir le port série\n");
        return NULL;
    }

    result = sp_set_baudrate(port, 9600);
    if (result != SP_OK) {
        fprintf(stderr, "Erreur: Impossible de régler la vitesse en bauds\n");
        sp_close(port);
        return NULL;
    }

    return port;
}

// Fonction pour envoyer une commande à l'Arduino
void send_command(struct sp_port* port, char command) {
    int bytes_written = sp_nonblocking_write(port, &command, 1);
    if (bytes_written < 0) {
        fprintf(stderr, "Erreur: Impossible d'écrire sur le port série\n");
    } else {
        printf("Commande '%c' envoyée\n", command);
    }
}
