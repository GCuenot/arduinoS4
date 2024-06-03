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
#include <pthread.h>

#define LARGEUR_FENETRE 1200
#define HAUTEUR_FENETRE 700

bool affichageInitial = true;
volatile int keep_running = 1;
static int dernierEtatClic = 0;
struct sp_port* serial_port;

struct sp_port* open_serial_port(const char* port_name);
void* read_serial_port(void* arg);
void send_command(struct sp_port* port, char command);
void gestionEvenement(EvenementGfx evenement);

int main(int argc, char **argv) {
    srand(time(NULL));
    const char* port_name = "/dev/ttyACM0";
    serial_port = open_serial_port(port_name);
    if (serial_port == NULL) {
        return 1;
    }
    pthread_t serial_thread;
    if (pthread_create(&serial_thread, NULL, read_serial_port, (void*)serial_port)) {
        fprintf(stderr, "Erreur: Impossible de créer le thread\n");
        return 1;
    }

    initialiseGfx(argc, argv);
    prepareFenetreGraphique("GfxLib", LARGEUR_FENETRE, HAUTEUR_FENETRE);
    lanceBoucleEvenements();

    keep_running = 0;
    pthread_join(serial_thread, NULL);

    sp_close(serial_port);
    sp_free_port(serial_port);
    return 0;
}

void gestionEvenement(EvenementGfx evenement) {
    switch (evenement) {
        case Affichage:
            afficheFondecran();
            if (affichageInitial) {
                cercleOnOff2();
            } else {
                // if(soundOn == false){
                //     carrerec();
                // } else if(soundOn == true){
                //     carreclic();
                // }
                // Affiche tous les éléments lorsque l'affichage initial est désactivé
                cercleOnOff();
                flechedroite();
                flechegauche();
                flechehaut();
                flechebas();
                rectanglesoundOnOff();
                carre50cm();
                carre1m();
                carre5m();
            }
            break;

        case Clavier:
            break;

        case Souris:
            int etatClic = etatBoutonSouris();
            if (etatClic != dernierEtatClic) {
                if (etatClic == GaucheAppuye) {
                    printf("Clic de la souris enfoncé.\n");
                } else {
                    printf("Clic de la souris relâché.\n");
                }
                dernierEtatClic = etatClic;
            }
            break;

        case BoutonSouris:
            if (etatBoutonSouris() == GaucheAppuye) {
                if (abscisseSouris() >= ((largeurFenetre()) / 5) * 3 && abscisseSouris() <= (largeurFenetre()) - (((largeurFenetre()) / 12) * 4) &&
                    ordonneeSouris() >= (hauteurFenetre() / 6) * 3 && ordonneeSouris() <= (hauteurFenetre()) - ((hauteurFenetre() / 10) * 4.5)) {
                    printf("Flèche droite cliquée.\n");
                    send_command(serial_port, 'D');
                    clicSurFlecheDroite = true; // Active l'état du clic sur la flèche droite
                    rafraichisFenetre();
                } else if (abscisseSouris() >= (largeurFenetre() - (largeurFenetre() - ((largeurFenetre() / 12) * 4))) &&
                           abscisseSouris() <= (largeurFenetre() - ((largeurFenetre() / 5) * 3)) &&
                           ordonneeSouris() >= ((hauteurFenetre() / 6) * 3) &&
                           ordonneeSouris() <= (hauteurFenetre() - ((hauteurFenetre() / 10) * 4.5))) {
                    printf("Flèche gauche cliquée.\n");
                    send_command(serial_port, 'G');
                    clicSurFlecheGauche = true; // Active l'état du clic sur la flèche gauche
                    rafraichisFenetre();
                } else if (abscisseSouris() >= (largeurFenetre() / 5) * 2.4 && abscisseSouris() <= (largeurFenetre() / 5) * 2.6 &&
                           ordonneeSouris() >= (hauteurFenetre() / 2) + (largeurFenetre() / 12) &&
                           ordonneeSouris() <= (hauteurFenetre() / 2) + ((hauteurFenetre() / 10) * 2.7)) {
                    printf("Flèche haut cliquée.\n");
                    send_command(serial_port, 'H');
                    clicSurFlecheHaut = true; // Active l'état du clic sur la flèche haut
                    rafraichisFenetre();
                } else if (abscisseSouris() >= (largeurFenetre() / 5) * 2.4 && abscisseSouris() <= (largeurFenetre() / 5) * 2.6 &&
                           ordonneeSouris() >= (hauteurFenetre() / 2) - ((hauteurFenetre() / 10) * 2.7) &&
                           ordonneeSouris() <= (hauteurFenetre() / 2) - (largeurFenetre() / 12)) {
                    printf("Flèche bas cliquée.\n");
                    send_command(serial_port, 'B');
                    clicSurFlecheBas = true; // Active l'état du clic sur la flèche bas
                    rafraichisFenetre();
                } else if (pow(abscisseSouris() - (largeurFenetre() * 0.9), 2) +
                           pow(ordonneeSouris() - (hauteurFenetre() * 0.85), 2) <= pow(largeurFenetre() * 0.07, 2)) {
                    printf("Cercle ON/OFF cliqué.\n");

                    if (affichageInitial) {
                        send_command(serial_port, 'E'); // Envoie 'E' si l'affichage initial est activé
                        affichageInitial = false; // Désactive l'affichage initial
                    } else {
                        send_command(serial_port, 'e'); // Envoie 'e' si l'affichage initial est désactivé
                        affichageInitial = true; // Active l'affichage initial
                    }

                    rafraichisFenetre();
                } else if (abscisseSouris() >= (largeurFenetre() * 0.825) &&
                           abscisseSouris() <= (largeurFenetre() * 0.825) + (largeurFenetre() * 0.15) &&
                           ordonneeSouris() <= hauteurFenetre() * 0.65 &&
                           ordonneeSouris() >= (hauteurFenetre() * 0.65) - (hauteurFenetre() * 0.08)) {
                    printf("Rectangle Sound ON/OFF cliqué.\n");
                    if (soundOn == true) {
                        send_command(serial_port, 's');
                    } else {
                        send_command(serial_port, 'S');
                    }

                    if(soundOn == true){
                        soundOn = false;
                    } else if (soundOn == false){
                        soundOn = true;
                    }

                    rafraichisFenetre();
                } else if (abscisseSouris() >= largeurFenetre() * 0.828 &&
                           abscisseSouris() <= largeurFenetre() * 0.878 &&
                           ordonneeSouris() >= hauteurFenetre() * 0.5 - hauteurFenetre() * 0.08 &&
                           ordonneeSouris() <= hauteurFenetre() * 0.5) {
                    printf("50cm cliqué.\n");
                    send_command(serial_port, 'X');

                    bouton50cmClique = true;
                    bouton1mClique = false;
                    bouton5mClique = false;
                    rafraichisFenetre();
                } else if (abscisseSouris() >= largeurFenetre() * 0.878 &&
                           abscisseSouris() <= largeurFenetre() * 0.928 &&
                           ordonneeSouris() >= hauteurFenetre() * 0.5 - hauteurFenetre() * 0.08 &&
                           ordonneeSouris() <= hauteurFenetre() * 0.5) {
                    printf("1m cliqué.\n");
                    send_command(serial_port, 'Y');

                    bouton50cmClique = false;
                    bouton1mClique = true;
                    bouton5mClique = false;
                    rafraichisFenetre();
                } else if (abscisseSouris() >= largeurFenetre() * 0.928 &&
                           abscisseSouris() <= largeurFenetre() * 0.978 &&
                           ordonneeSouris() >= hauteurFenetre() * 0.5 - hauteurFenetre() * 0.08 &&
                           ordonneeSouris() <= hauteurFenetre() * 0.5) {
                    printf("5m cliqué.\n");
                    send_command(serial_port, 'Z');

                    bouton50cmClique = false;
                    bouton1mClique = false;
                    bouton5mClique = true;
                    rafraichisFenetre();
                }
            } else if (etatBoutonSouris() == GaucheRelache) {
                clicSurFlecheDroite = false; // Désactive l'état du clic sur la flèche droite lorsque le clic est relâché
                clicSurFlecheGauche = false;
                clicSurFlecheHaut = false;
                clicSurFlecheBas = false;
                rafraichisFenetre();
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

struct sp_port* open_serial_port(const char* port_name) {
    struct sp_port* port;
    sp_get_port_by_name(port_name, &port);
    if (port == NULL) {
        fprintf(stderr, "Erreur: Impossible d'ouvrir le port série %s\n", port_name);
        return NULL;
    }

    if (sp_open(port, SP_MODE_READ_WRITE) != SP_OK) {
        fprintf(stderr, "Erreur: Impossible d'ouvrir le port série %s\n", port_name);
        sp_free_port(port);
        return NULL;
    }

    if (sp_set_baudrate(port, 9600) != SP_OK) {
        fprintf(stderr, "Erreur: Impossible de configurer le baudrate du port série %s\n", port_name);
        sp_close(port);
        sp_free_port(port);
        return NULL;
    }

    return port;
}

void* read_serial_port(void* arg) {
    struct sp_port* port = (struct sp_port*)arg;
    char buffer[1];
    while (keep_running) {
        int bytes_read = sp_nonblocking_read(port, buffer, sizeof(buffer));
        if (bytes_read > 0 && buffer[0] == 'N' && soundOn == true) {
            printf("INTRUS !!!!! \n");
        } else if (bytes_read > 0 && buffer[0] == 'N' && soundOn == false) {
            printf("IL Y A QUELQU'UN DEVANT LA PORTE !!!!!\n");
        }
    }
    return NULL;
}

void send_command(struct sp_port* port, char command) {
    sp_nonblocking_write(port, &command, 1);
}

















// #include <stdlib.h> 
// #include <stdio.h> 
// #include <math.h> 
// #include <string.h> 
// #include <time.h> 
// #include <unistd.h> 
// #include "GfxLib.h" 
// #include "BmpLib.h" 
// #include "ESLib.h" 
// #include "fonctions.h" 
// #include "moteur.h" 
// #include <GL/gl.h> 
// #include <GL/glu.h> 
// #include <GL/glut.h> 
// #include <libserialport.h> 
// #include <pthread.h> 
// #define LARGEUR_FENETRE 1200 
// #define HAUTEUR_FENETRE 700 





// volatile int keep_running = 1; 
// static int dernierEtatClic = 0; // Déclaration de la variable globale 
// struct sp_port* serial_port; // Pointeur vers le port série 
// // Variable globale pour suivre l'état du son 
// int soundOn = 0; // 0 = Sound OFF, 1 = Sound ON 
// // Déclaration de la fonction pour ouvrir le port série 
// struct sp_port* open_serial_port(const char* port_name); 
// struct sp_port* open_serial_port_read(const char* port_name); 
// void* read_serial_port(void* arg); 
// // Déclaration de la fonction pour envoyer une commande à l'Arduino 
// void send_command(struct sp_port* port, char command); 
// void gestionEvenement(EvenementGfx evenement); 
// int main(int argc, char **argv){ 
//     srand(time(NULL)); 
//     // Ouverture du port série 
//     const char* port_name = "/dev/ttyACM0"; // Changez cela selon le port série de votre Arduino 
//     serial_port = open_serial_port(port_name); 
//     if (serial_port == NULL) { 
//         return 1; 
//     } 
//     // Créer un thread pour la lecture du port série 
//     pthread_t serial_thread; 
//     if (pthread_create(&serial_thread, NULL, read_serial_port, (void*)serial_port)) { 
//         fprintf(stderr, "Erreur: Impossible de créer le thread\n"); 
//         return 1; 
//     } 
//     initialiseGfx(argc, argv); 
//     prepareFenetreGraphique("GfxLib", LARGEUR_FENETRE, HAUTEUR_FENETRE); 
//     lanceBoucleEvenements(); 
//     // Indiquer au thread de s'arrêter 
//     keep_running = 0; 
//     pthread_join(serial_thread, NULL); 
//     // Fermeture du port série 
//     sp_close(serial_port); 
//     sp_free_port(serial_port); 
//     return 0; 
// } 
// void gestionEvenement(EvenementGfx evenement) { 
//     switch (evenement) { 
//         case Affichage: 
//             afficheFondecran(); 
//             flechedroite(); 
//             flechegauche(); 
//             flechehaut(); 
//             flechebas(); 
//             cercleOnOff(); 
//             rectanglesoundOnOff(); 
//             carre50cm(); 
//             carre1m(); 
//             carre5m(); 
//             break; 
//         case Clavier: 
//             // Ajoutez ici le code pour gérer les événements de clavier si nécessaire 
//             break; 
//         case Souris: 
//             int etatClic = etatBoutonSouris(); 
//             if (etatClic != dernierEtatClic) { 
//                 if (etatClic == GaucheAppuye) { 
//                     // Ajoutez ici le code pour gérer le clic de la souris 
//                     printf("Clic de la souris enfoncé.\n"); 
//                 } else { 
//                     // Ajoutez ici le code pour gérer le relâchement du clic de la souris 
//                     printf("Clic de la souris relâché.\n"); 
//                 } 
//                 dernierEtatClic = etatClic; // Met à jour le dernier état du clic 
//             } 
//             break; 
//          case BoutonSouris: 
//             if (etatBoutonSouris() == GaucheAppuye) { 
//                 // Vérifie si la souris est cliquée sur la flèche droite 
//                 if (abscisseSouris() >= ((largeurFenetre())/ 5) * 3 && abscisseSouris() <= (largeurFenetre()) - (((largeurFenetre())/ 12) *4) && 
//                     ordonneeSouris() >= (hauteurFenetre() / 6) * 3 && ordonneeSouris() <= (hauteurFenetre()) -((hauteurFenetre() / 10) * 4.5)) { 
//                     // Action pour la flèche droite 
//                     printf("Flèche droite cliquée.\n"); 
//                     send_command(serial_port, 'D'); 
//                 } 
//                 // Vérifie si la souris est cliquée sur la flèche gauche 
//                 else if (abscisseSouris() >= (largeurFenetre() - (largeurFenetre() - ((largeurFenetre() / 12) * 4))) && 
//                          abscisseSouris() <= (largeurFenetre() - ((largeurFenetre() / 5) * 3)) && 
//                          ordonneeSouris() >= ((hauteurFenetre() / 6) * 3) && 
//                          ordonneeSouris() <= (hauteurFenetre() - ((hauteurFenetre() / 10) * 4.5)) ) { 
//                     // Action pour la flèche gauche 
//                     printf("Flèche gauche cliquée.\n"); 
//                     send_command(serial_port, 'G'); 
//                 } 
//                 // Vérifie si la souris est cliquée sur la flèche haut 
//                 else if (abscisseSouris() >= (largeurFenetre() / 5) * 2.4 && abscisseSouris() <= (largeurFenetre() / 5) * 2.6 && 
//                          ordonneeSouris() >= (hauteurFenetre() / 2) + (largeurFenetre() / 12) && 
//                          ordonneeSouris() <= (hauteurFenetre() / 2) + ((hauteurFenetre() / 10) * 2.7)) { 
//                     // Action pour la flèche haut 
//                     printf("Flèche haut cliquée.\n"); 
//                     send_command(serial_port, 'H'); 
//                 } 
//                 // Vérifie si la souris est cliquée sur la flèche bas 
//                 else if (abscisseSouris() >= (largeurFenetre() / 5) * 2.4 && abscisseSouris() <= (largeurFenetre() / 5) * 2.6 && 
//                          ordonneeSouris() >= (hauteurFenetre() / 2) - ((hauteurFenetre() / 10) * 2.7) && 
//                          ordonneeSouris() <= (hauteurFenetre() / 2) - (largeurFenetre() / 12)) { 
//                     // Action pour la flèche bas 
//                     printf("Flèche bas cliquée.\n"); 
//                     send_command(serial_port, 'B'); 
//                 } 
//                 // Vérifie si la souris est cliquée sur le cercle ON/OFF 
//                 else if (pow(abscisseSouris() - (largeurFenetre() * 0.9), 2) + 
//                          pow(ordonneeSouris() - (hauteurFenetre() * 0.85), 2) <= pow(largeurFenetre() * 0.07, 2)) { 
//                     // Action pour le cercle ON/OFF 
//                     printf("Cercle ON/OFF cliqué.\n"); 
//                     send_command(serial_port, 'e'); 
//                 } 
//                 // Vérifie si la souris est cliquée sur le rectangle Sound ON/OFF 
//                 else if (abscisseSouris() >= (largeurFenetre() * 0.825) && 
//                          abscisseSouris() <= (largeurFenetre() * 0.825) + 
//                          (largeurFenetre() * 0.15) && 
//                          ordonneeSouris() <= hauteurFenetre() * 0.65 && 
//                          ordonneeSouris() >= (hauteurFenetre() * 0.65) - 
//                          (hauteurFenetre() * 0.08)) { 
//                     // Action pour le rectangle Sound ON/OFF 
//                     printf("Rectangle Sound ON/OFF cliqué.\n"); 
//                     if (soundOn) { 
//                         send_command(serial_port, 's'); 
//                     } else { 
//                         send_command(serial_port, 'S'); 
//                     } 
//                     soundOn = !soundOn; // Alterne l'état du son 
//                 } 
//                 // Check for 50cm rectangle click 
//                 else if (abscisseSouris() >= largeurFenetre() * 0.828 && 
//                          abscisseSouris() <= largeurFenetre() * 0.878 && 
//                          ordonneeSouris() >= hauteurFenetre() * 0.5 - 
//                          hauteurFenetre() * 0.08 && 
//                          ordonneeSouris() <= hauteurFenetre() * 0.5) { 
//                     printf("50cm cliqué.\n"); 
//                     send_command(serial_port, 'X'); 
//                 } 
//                 // Check for 1m rectangle click 
//                 else if (abscisseSouris() >= largeurFenetre() * 0.878 && 
//                          abscisseSouris() <= largeurFenetre() * 0.928 && 
//                          ordonneeSouris() >= hauteurFenetre() * 0.5 - 
//                          hauteurFenetre() * 0.08 && 
//                          ordonneeSouris() <= hauteurFenetre() * 0.5) { 
//                     printf("1m cliqué.\n"); 
//                     send_command(serial_port, 'Y'); 
//                 } 
//                 // Check for 5m rectangle click 
//                 else if (abscisseSouris() >= largeurFenetre() * 0.928 && 
//                          abscisseSouris() <= largeurFenetre() * 0.978 && 
//                          ordonneeSouris() >= hauteurFenetre() * 0.5 - 
//                          hauteurFenetre() * 0.08 && 
//                          ordonneeSouris() <= hauteurFenetre() * 0.5) { 
//                     printf("5m cliqué.\n"); 
//                     send_command(serial_port, 'Z'); 
//                 } 
//             } 
//             break; 
//         case Inactivite: 
//             // Ajoutez ici le code pour gérer les événements d'inactivité si nécessaire 
//             break; 
//         case Redimensionnement: 
//             // Ajoutez ici le code pour gérer les événements de redimensionnement de la fenêtre si nécessaire 
//             break; 
//     } 
// }// Fonction pour ouvrir le port série 
// struct sp_port* open_serial_port(const char* port_name) { 
//     struct sp_port* port; 
//     enum sp_return result = sp_get_port_by_name(port_name, &port); 
//     if (result != SP_OK) { 
//         fprintf(stderr, "Erreur: Impossible d'obtenir le port série\n"); 
//         return NULL; 
//     } 
//     result = sp_open(port, SP_MODE_WRITE); 
//     if (result != SP_OK) { 
//         fprintf(stderr, "Erreur: Impossible d'ouvrir le port série\n"); 
//         return NULL; 
//     } 
//     result = sp_set_baudrate(port, 9600); 
//     if (result != SP_OK) { 
//         fprintf(stderr, "Erreur: Impossible de régler la vitesse en bauds\n"); 
//         sp_close(port); 
//         return NULL; 
//     } 
//     return port; 
// } 
// void* read_serial_port(void* arg) { 
//     struct sp_port* port = (struct sp_port*)arg; 
//     unsigned char buffer[1]; 
//     while (keep_running) { 
//         int bytes_read = sp_nonblocking_read(port, buffer, 1); 
//         if (bytes_read > 0) { 
//             if (buffer[0] == 'N') { 
//                 printf("Il y a quelqu'un !!!!!!\n"); 
//                 // Action supplémentaire si nécessaire 
//             } 
//         } 
//         usleep(100000); // Pause de 100ms pour éviter de monopoliser le CPU 
//     } 
//     return NULL; 
// } 
// // Fonction pour envoyer une commande à l'Arduino 
// void send_command(struct sp_port* port, char command) { 
//     int bytes_written = sp_nonblocking_write(port, &command, 1); 
//     if (bytes_written < 0) { 
//         fprintf(stderr, "Erreur: Impossible d'écrire sur le port série\n"); 
//     } else { 
//         printf("Commande '%c' envoyée\n", command); 
//     } 
// }



















