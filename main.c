#include "GfxLib.h"
#include <stdio.h>

// Dimensions de la fenêtre graphique
#define LARGEUR_FENETRE 800
#define HAUTEUR_FENETRE 600

// Coordonnées du carré rouge
#define CARRE_X1 100
#define CARRE_Y1 100
#define CARRE_X2 200
#define CARRE_Y2 200

void gestionEvenement(EvenementGfx evenement);

int main(int argc, char **argv)
{
    initialiseGfx(argc, argv);
    prepareFenetreGraphique("TEST", LARGEUR_FENETRE, HAUTEUR_FENETRE);
    lanceBoucleEvenements();
    return 0;
}

void gestionEvenement(EvenementGfx evenement)
{
    switch (evenement)
    {
        case Initialisation:
            // Initialisation de la fenêtre
            couleurCourante(255, 255, 255);
            effaceFenetre(255, 255, 255);
            break;

        case Affichage:
            // Dessin du carré rouge
            couleurCourante(255, 0, 0);
            rectangle(CARRE_X1, CARRE_Y1, CARRE_X2, CARRE_Y2);
            break;

        case BoutonSouris:
            // Détection du clic sur le carré rouge
            if (etatBoutonSouris() == GaucheAppuye)
            {
                int x = abscisseSouris();
                int y = ordonneeSouris();

                if (x >= CARRE_X1 && x <= CARRE_X2 && y >= CARRE_Y1 && y <= CARRE_Y2)
                {
                    printf("hello\n");
                }
            }
            break;

        case Clavier:
            if (caractereClavier() == 'q')
            {
                termineBoucleEvenements();
            }
            break;

        default:
            break;
    }
}
