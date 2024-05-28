#include <stdlib.h>
#include <stdio.h>
#include <math.h>	// Pour pouvoir utiliser sin() et cos()
#include "GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "ESLib.h"	// Pour utiliser valeurAleatoire()
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "fonctions.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>





void afficheFondecran(){
	
	// Rectangle
	couleurCourante(15, 46, 130);
	rectangle(0, 0, (largeurFenetre()), (hauteurFenetre()));
	
}

void flechedroite(){

	int x1 = ((largeurFenetre())/ 5) * 3;
	int y1 = (hauteurFenetre() / 6) * 3;
	int x2 = (largeurFenetre()) - (((largeurFenetre())/ 12) *4);
	int y2 = (hauteurFenetre()) -((hauteurFenetre() / 10) * 4.5);


	couleurCourante(0,0,0);
	//void rectangle(float xCoin1, float yCoin1, float xCoin2, float yCoin2);
	rectangle(x1,y1,x2,y2);
	// Dessine un triangle de couleur courante aux coordonnees donnees
	couleurCourante(0,0,0);
	//void triangle(float xCoin1, float yCoin1, float xCoin2, float yCoin2, float xCoin3, float yCoin3);
	triangle(x2,y2,x2 + ((x2-x1)/4),y1+((y2-y1)/2),x2,y1);

	/* Dessine une ligne de couleur courante aux coordonnees donnees */
	//void ligne(float xDepart, float yDepart, float xArrivee, float yArrivee);
	couleurCourante(255,255,255);
	epaisseurDeTrait(10);
	ligne(x1,y2,x2,y2);

	couleurCourante(255,255,255);
	epaisseurDeTrait(10);
	ligne(x2,y2,x2 + ((x2-x1)/4),y1+((y2-y1)/2));


}

void flechegauche(){

	

	int x1 = ((largeurFenetre())/ 5) * 3;
	int x2 = (largeurFenetre()) - (((largeurFenetre())/ 12) *4);

	int x1milieu = largeurFenetre() - x2;

	int y1 = (hauteurFenetre() / 6) * 3;
	int y2 = (hauteurFenetre()) -((hauteurFenetre() / 10) * 4.5);
	
	int x2milieu = largeurFenetre() - x1;



	couleurCourante(0,0,0);
	//void rectangle(float xCoin1, float yCoin1, float xCoin2, float yCoin2);
	rectangle(x1milieu,y1,x2milieu,y2);
	// Dessine un triangle de couleur courante aux coordonnees donnees
	couleurCourante(0,0,0);
	// void triangle(float xCoin1, float yCoin1, float xCoin2, float yCoin2, float xCoin3, float yCoin3);
	triangle(x1milieu,y1,largeurFenetre() -(x2 + ((x2-x1)/4)),y1+((y2-y1)/2),x1milieu,y2);

	// /* Dessine une ligne de couleur courante aux coordonnees donnees */
	// //void ligne(float xDepart, float yDepart, float xArrivee, float yArrivee);
	couleurCourante(255,255,255);
	epaisseurDeTrait(10);
	ligne(x1milieu,y2,x2milieu,y2);

	couleurCourante(255,255,255);
	epaisseurDeTrait(10);
	ligne(x1milieu,y2,largeurFenetre() -(x2 + ((x2-x1)/4)),y1+((y2-y1)/2));


}

void flechehaut() {
    int x1 = (largeurFenetre() / 5) * 2.4;
    int x2 = (largeurFenetre() / 5) * 2.6;
    int y1 = (hauteurFenetre() / 2) + (largeurFenetre() / 12);
    int y2 = (hauteurFenetre() / 2) + ((hauteurFenetre() / 10) * 2.7);

    // Couleur du rectangle
    couleurCourante(0, 0, 0);
    // Dessine le rectangle
    rectangle(x1, y1, x2, y2);

    // // Dessine un triangle pour la pointe de la flèche
    couleurCourante(0, 0, 0);
    triangle(x1,y2,x1 +((x2-x1)/2), y2 * 1.05,x2, y2);

    // // Dessine les lignes blanches à l'intérieur de la flèche
    couleurCourante(255, 255, 255);
    epaisseurDeTrait(10);
    ligne(x1,y2,x1 +((x2-x1)/2), y2 * 1.05);
    ligne(x1 +((x2-x1)/2), y2 * 1.05,x2,y2);

    ligne(x1,y1 +2 ,x1,y2);
   	ligne(x2,y1 + 2,x2,y2);

}


void flechebas() {
    int x1 = (largeurFenetre() / 5) * 2.4;
    int x2 = (largeurFenetre() / 5) * 2.6;
    int y1 = (hauteurFenetre() / 2) - ((hauteurFenetre() / 10) * 2.7);
    int y2 = (hauteurFenetre() / 2) - (largeurFenetre() / 12);

    // Couleur du rectangle
    couleurCourante(0, 0, 0);
    // Dessine le rectangle
    rectangle(x1, y1, x2, y2);

    // Dessine un triangle pour la pointe de la flèche
    couleurCourante(0, 0, 0);
    triangle(x1, y1, x1 + ((x2 - x1) / 2), y1 - ((y2 - y1) * 0.30), x2, y1);

    // Dessine les lignes blanches à l'intérieur de la flèche
    couleurCourante(255, 255, 255);
    epaisseurDeTrait(10);
    ligne(x1, y1, x1 + ((x2 - x1) / 2), y1 - ((y2 - y1) * 0.30));
    ligne(x1 + ((x2 - x1) / 2), y1 - ((y2 - y1) * 0.30), x2, y1);

    ligne(x1, y1, x1, y2 - 2);
    ligne(x2, y1, x2, y2 - 2);
}


void dessineCercle(float centreX, float centreY, float rayon, int rouge, int vert, int bleu, int contourRouge, int contourVert, int contourBleu) {
    int nombreDeSegments = 100; // Plus il y a de segments, plus le cercle sera lisse
    float angle;

    // Dessiner le cercle rempli
    couleurCourante(rouge, vert, bleu);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= nombreDeSegments; i++) {
        angle = 2 * M_PI * i / nombreDeSegments;
        float x = centreX + (rayon * cos(angle));
        float y = centreY + (rayon * sin(angle));
        glVertex2f(x, y);
    }
    glEnd();

    // Dessiner le contour du cercle
    couleurCourante(contourRouge, contourVert, contourBleu);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= nombreDeSegments; i++) {
        angle = 2 * M_PI * i / nombreDeSegments;
        float x = centreX + (rayon * cos(angle));
        float y = centreY + (rayon * sin(angle));
        glVertex2f(x, y);
    }
    glEnd();
}


void cercleOnOff() {
    float centreX = largeurFenetre() * 0.9; // Ajustez ces valeurs pour positionner le cercle
    float centreY = hauteurFenetre() * 0.85; // à 50 pixels du coin supérieur droit
    float rayon = largeurFenetre() * 0.07; // Rayon du cercle
    
    epaisseurDeTrait(3); // Augmenter l'épaisseur des bordures
    
    // Dessin du cercle avec bordures noires
    dessineCercle(centreX, centreY, rayon, 255, 0, 0, 0, 0, 0); // Cercle rouge avec bord noir
    
    epaisseurDeTrait(1); // Rétablir l'épaisseur par défaut pour le reste du dessin
    
    // Affichage du texte "ON / OFF"
    couleurCourante(255, 255, 255); // Texte en blanc
    float taille = 15; // Taille du texte
    float tailleTexte = tailleChaine("ON / OFF", taille); // Taille du texte en X
    float posX = centreX - (tailleTexte / 1.45); // Position en X pour centrer le texte
    float posY = centreY * 0.99; // Position en Y pour centrer le texte
    afficheChaine("O N / O F F", taille, posX, posY); // Affichage du texte centré dans le cercle
}


void rectanglesoundOnOff() {
    float coinX = largeurFenetre() * 0.825; // Coin supérieur gauche du rectangle
    float coinY = hauteurFenetre() * 0.65; // Coin supérieur gauche du rectangle
    float largeur = largeurFenetre() * 0.15; // Largeur du rectangle
    float hauteur = hauteurFenetre() * 0.08; // Hauteur du rectangle
    
    epaisseurDeTrait(3); // Augmenter l'épaisseur des bordures
    
    // Dessin du rectangle avec bordures noires
    couleurCourante(0, 0, 0); // Couleur des bordures en noir
    rectangle(coinX, coinY, coinX + largeur, coinY - hauteur); // Dessin du rectangle
    
    epaisseurDeTrait(1); // Rétablir l'épaisseur par défaut pour le reste du dessin
    
    // Dessin du rectangle sans bordures
    couleurCourante(255, 128, 0); // Remplissage orange
    rectangle(coinX + 1, coinY - 1, coinX + largeur - 1, coinY - hauteur + 1); // Dessin du rectangle sans les bordures
    
    // Affichage du texte "ON / OFF"
    couleurCourante(255, 255, 255); // Texte en blanc
    float taille = 18; // Taille du texte
    float tailleTexte = tailleChaine("ON / OFF", taille); // Taille du texte en X
    float posX = coinX - (tailleTexte / 1.45); // Position en X pour centrer le texte
    float posY = coinY; // Position en Y pour centrer le texte
    afficheChaine("S O U N D", taille, posX * 1.1, posY * 0.92); 
}

void carrerec() {
    float coinX_REC = largeurFenetre() * 0.825; // Coin supérieur gauche du rectangle "REC"
    float coinY_REC = hauteurFenetre() * 0.4; // Coin supérieur gauche du rectangle "REC"
    float largeur_REC = largeurFenetre() * 0.15; // Largeur du rectangle "REC"
    float hauteur_REC = hauteurFenetre() * 0.08; // Hauteur du rectangle "REC"
    
    epaisseurDeTrait(3); // Augmenter l'épaisseur des bordures
    
    // Dessin du rectangle avec bordures noires
    couleurCourante(0, 0, 0); // Couleur des bordures en noir
    rectangle(coinX_REC, coinY_REC, coinX_REC + largeur_REC, coinY_REC - hauteur_REC); // Dessin du rectangle
    
    epaisseurDeTrait(1); // Rétablir l'épaisseur par défaut pour le reste du dessin
    
    // Dessin du rectangle sans bordures
    couleurCourante(70, 130, 180); // Remplissage orange
    rectangle(coinX_REC + 1, coinY_REC - 1, coinX_REC + largeur_REC - 1, coinY_REC - hauteur_REC + 1); // Dessin du rectangle sans les bordures
    
    // Affichage du texte "REC"
    couleurCourante(255, 255, 255); // Texte en blanc
    float taille = 17; // Taille du texte
    float tailleTexte = tailleChaine("ON / OFF", taille); // Taille du texte en X
    float posX = coinX_REC - (tailleTexte / 1.45); // Position en X pour centrer le texte
    float posY = coinY_REC; // Position en Y pour centrer le texte
    afficheChaine("R E C O R D", taille, posX * 1.095, posY * 0.87);  // Affichage du texte "REC"
}

void carreclic() {
    float coinX_CLIC = largeurFenetre() * 0.825; // Coin supérieur gauche du rectangle "CLIC"
    float coinY_CLIC = hauteurFenetre() * 0.3; // Coin supérieur gauche du rectangle "CLIC"
    float largeur_CLIC = largeurFenetre() * 0.15; // Largeur du rectangle "CLIC"
    float hauteur_CLIC = hauteurFenetre() * 0.08; // Hauteur du rectangle "CLIC"
    
    epaisseurDeTrait(3); // Augmenter l'épaisseur des bordures
    
    // Dessin du rectangle avec bordures noires
    couleurCourante(0, 0, 0); // Couleur des bordures en noir
    rectangle(coinX_CLIC, coinY_CLIC, coinX_CLIC + largeur_CLIC, coinY_CLIC - hauteur_CLIC); // Dessin du rectangle
    
    epaisseurDeTrait(1); // Rétablir l'épaisseur par défaut pour le reste du dessin
    
    // Dessin du rectangle sans bordures
    couleurCourante(70, 130, 180); // Remplissage orange
    rectangle(coinX_CLIC + 1, coinY_CLIC - 1, coinX_CLIC + largeur_CLIC - 1, coinY_CLIC - hauteur_CLIC + 1); // Dessin du rectangle sans les bordures
    
    // Affichage du texte "CLIC"
    couleurCourante(255, 255, 255); // Texte en blanc
    float taille = 17; // Taille du texte
    float tailleTexte = tailleChaine("ON / OFF", taille); // Taille du texte en X
    float posX = coinX_CLIC - (tailleTexte / 1.45); // Position en X pour centrer le texte
    float posY = coinY_CLIC; // Position en Y pour centrer le texte
    afficheChaine("S C R E E N", taille, posX * 1.098, posY * 0.83); // Affichage du texte "CLIC"
}






