// #ifndef MOTEUR_H
// #define MOTEUR_H
// #include "settings.h"

// struct carte {
//     int rang;
//     int couleur;
//     DonneesImageRGB *image; 
// };

// struct main {
//     struct carte cartes[TAILLE_MAIN_MAX];
//     int nb_cartes;
// };

// struct info{

// 	int valeur;

// };


// struct test{

// 	int pomme ;
// 	int pomme1 ;
// };

// void initialiseTas(struct carte tas[NUM_CARTES]);
// void melangerTas(struct carte tas[NUM_CARTES]);

// struct carte tirerCarte(struct carte tas[], int *index);
// int calculerValeurMain(struct main *joueur_main);

// int afficherValeurMain(struct main *joueur_main);
// void ajouterCarteALaMain(struct main *joueur_main, struct carte carte_tiree);
// void jouerCroupier(struct main *main_croupier, struct carte tas[NUM_CARTES], int *index_tas);
// void reinitialiserPartie(struct main *main_joueur, struct main *main_croupier, struct carte tas[], int *index_tas);
// void afficherScores(int score_joueur, int score_croupier, int mise, char *solde_joueur);
// int rejouer();
// void jouerBlackjack();

// #endif  // BLACKJACK_H