#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libserialport.h>
#include "GfxLib.h"

// Dimensions de la fenêtre graphique
#define LARGEUR_FENETRE 800
#define HAUTEUR_FENETRE 600

// Coordonnées du carré rouge
#define CARRE_X1 100
#define CARRE_Y1 100
#define CARRE_X2 200
#define CARRE_Y2 200

// Déclaration de la fonction pour ouvrir le port série
struct sp_port* open_serial_port(const char* port_name);

// Déclaration de la fonction pour envoyer une commande à l'Arduino
void send_command(struct sp_port* port, char command);

// Fonction de gestion des événements graphiques
void gestionEvenement(EvenementGfx evenement);

// Pointeur vers le port série
struct sp_port* serial_port;

int main(int argc, char **argv) {
    // Ouverture du port série
    const char* port_name = "/dev/ttyACM0"; // Changez cela selon le port série de votre Arduino
    serial_port = open_serial_port(port_name);
    if (serial_port == NULL) {
        return 1;
    }

    // Initialisation de la fenêtre graphique
    initialiseGfx(argc, argv);
    prepareFenetreGraphique("TEST", LARGEUR_FENETRE, HAUTEUR_FENETRE);
    lanceBoucleEvenements();

    // Fermeture du port série
    sp_close(serial_port);
    sp_free_port(serial_port);

    return 0;
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

// Fonction de gestion des événements graphiques
void gestionEvenement(EvenementGfx evenement) {
    switch (evenement) {
        case Initialisation:
            couleurCourante(255, 255, 255);
            effaceFenetre(255, 255, 255);
            break;

        case Affichage:
            couleurCourante(255, 0, 0);
            rectangle(CARRE_X1, CARRE_Y1, CARRE_X2, CARRE_Y2);
            break;

        case BoutonSouris:
            if (etatBoutonSouris() == GaucheAppuye) {
                int x = abscisseSouris();
                int y = ordonneeSouris();
                if (x >= CARRE_X1 && x <= CARRE_X2 && y >= CARRE_Y1 && y <= CARRE_Y2) {
                    printf("Clic détecté : Allumer/Eteindre la LED\n");
                    // Envoyer la commande à l'Arduino pour allumer ou éteindre la LED
                    static char command = '0'; // Par défaut, éteindre la LED
                    if (command == '0') {
                        send_command(serial_port, '1'); // Allumer la LED
                        command = '1';
                    } else {
                        send_command(serial_port, '0'); // Eteindre la LED
                        command = '0';
                    }
                    sp_drain(serial_port);
                }
            }
            break;

        case Clavier:
            if (caractereClavier() == 'q') {
                termineBoucleEvenements();
            }
            break;

        default:
            break;
    }
}
