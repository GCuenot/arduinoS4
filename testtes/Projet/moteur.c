// #include <stdlib.h> // Pour pouvoir utiliser exit()
// #include <stdio.h>  // Pour pouvoir utiliser printf()
// #include <math.h>   // Pour pouvoir utiliser sin() et cos()
// #include "GfxLib.h" // Seul cet include est nécessaire pour faire du graphique
// #include "BmpLib.h" // Cet include permet de manipuler des fichiers BMP
// #include "ESLib.h"  // Pour utiliser valeurAleatoire()
// #include "moteur.h"
// #include <string.h>
// #include <time.h>
// #include <unistd.h>
// #include "fonctions.h"
// #include "settings.h"

// int index_tas = 0;





// void initialiseTas(struct carte tas[NUM_CARTES]) {
//     int nbr_cartes = 0;
//     for (int couleur = 0; couleur < 4; couleur++) {
//         for (int rang = 0; rang < 13; rang++) {
//             tas[nbr_cartes].rang = rang;
//             tas[nbr_cartes].couleur = couleur;
//             nbr_cartes++;
//          }
//      }
// }

// void melangerTas(struct carte tas[NUM_CARTES]) {
//     for (int i = NUM_CARTES-1; i>=1 ; --i) {
//         int j = rand() % (i+1);
//         struct carte temp = tas[i];
//         tas[i] = tas[j];
//         tas[j] = temp;
//     }
// }



// struct carte tirerCarte(struct carte tas[], int *index) {
//     struct carte carte_tiree = tas[*index];
//     (*index)++;
//     return carte_tiree;
// }

// int calculerValeurMain(struct main *joueur_main) {

    
//     int valeur = 0;
//     int num_as = 0;

//      for (int i = 0; i < joueur_main->nb_cartes; i++) {
//          int rang = joueur_main->cartes[i].rang;
//          if (rang >= 1 && rang < 9) {
//              valeur += rang+1;
//          } else if (rang >= 9 && rang <= 12) {
//              valeur += 10;
//          } else if (rang == 0) {
//              valeur += 11;
//              num_as++;
//          }
//      }

//      while (valeur > SCORE_BLACKJACK && num_as > 0) {
//          valeur -= 10;
//          num_as--;
//   }

    
    



//     return valeur;
    
// }


//  int afficherValeurMain(struct main *joueur_main) {
//      int valeur = calculerValeurMain(joueur_main);

    
//     return valeur;
//  }

// void ajouterCarteALaMain(struct main *joueur_main, struct carte carte_tiree) {

//     joueur_main->cartes[joueur_main->nb_cartes] = carte_tiree;
//     joueur_main->nb_cartes++;
// }

// void jouerCroupier(struct main *main_croupier, struct carte tas[NUM_CARTES], int *index_tas) {
//     while (calculerValeurMain(main_croupier) < SEUIL_CROUPIER) {
//         ajouterCarteALaMain(main_croupier, tirerCarte(tas, index_tas));
        
      
//         afficherValeurMain(main_croupier);
        
//     }
    
    
// }

// void reinitialiserPartie(struct main *main_joueur, struct main *main_croupier, struct carte tas[], int *index_tas) {
//     main_joueur->nb_cartes = 0;
//     main_croupier->nb_cartes = 0;
//     *index_tas = 0;
//     melangerTas(tas);
// }

// void afficherScores(int score_joueur, int score_croupier, int mise, char *solde_joueur) {
//     printf("\nVotre score : %d\n", score_joueur);
//     printf("Score du croupier : %d\n", score_croupier);

//     if ((score_joueur > score_croupier || score_croupier > SCORE_BLACKJACK) && (score_joueur <= SCORE_BLACKJACK)) {
//         printf("\nVous avez gagné !\n");
//         sprintf(solde_joueur, "%d", atoi(solde_joueur) + mise);
//     } else if (score_croupier > score_joueur || score_joueur > SCORE_BLACKJACK) {
//         printf("\nVous avez perdu.\n");
//         sprintf(solde_joueur, "%d", atoi(solde_joueur) - mise);
//     } else {
//         printf("\nÉgalité !\n");
//     }
// }

// int rejouer() {
//     char choix_rejouer;
//     printf("Voulez-vous continuer à jouer ? (o/n) ");
//     scanf(" %c", &choix_rejouer);
//     if (choix_rejouer != 'o') {
//         return 1;
//     }
//     return 0;
// }


