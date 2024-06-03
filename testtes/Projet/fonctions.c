#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
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


bool soundOn = true;

bool bouton50cmClique = true;
bool bouton1mClique = false;
bool bouton5mClique = false;
extern bool recOn;
bool clicSurFlecheDroite = false;
bool clicSurFlecheGauche = false;
bool clicSurFlecheHaut = false;
bool clicSurFlecheBas = false;




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


	if (clicSurFlecheDroite) {
        couleurCourante(255,255,255); // Change la couleur en blanc pendant le clic
    } else {
        couleurCourante(0,0,0); // Reviens à la couleur noire lorsque le clic est relâché
    }

	rectangle(x1,y1,x2,y2);
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

    if (clicSurFlecheGauche) {
        couleurCourante(255,255,255); // Change la couleur en blanc pendant le clic
    } else {
        couleurCourante(0,0,0); // Reviens à la couleur noire lorsque le clic est relâché
    }

	
	rectangle(x1milieu,y1,x2milieu,y2);
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


    if (clicSurFlecheHaut) {
        couleurCourante(255,255,255); // Change la couleur en blanc pendant le clic
    } else {
        couleurCourante(0,0,0); // Reviens à la couleur noire lorsque le clic est relâché
    }

    rectangle(x1, y1, x2, y2);
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


    if (clicSurFlecheBas) {
        couleurCourante(255,255,255); // Change la couleur en blanc pendant le clic
    } else {
        couleurCourante(0,0,0); // Reviens à la couleur noire lorsque le clic est relâché
    }


    rectangle(x1, y1, x2, y2);
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
    dessineCercle(centreX, centreY, rayon, 0, 255, 0, 0, 0, 0); // Cercle rouge avec bord noir
    
    epaisseurDeTrait(1); // Rétablir l'épaisseur par défaut pour le reste du dessin
    
    // Affichage du texte "ON / OFF"
    couleurCourante(0, 0, 0); // Texte en blanc
    float taille = 15; // Taille du texte
    float tailleTexte = tailleChaine("ON / OFF", taille); // Taille du texte en X
    float posX = centreX - (tailleTexte / 1.45); // Position en X pour centrer le texte
    float posY = centreY * 0.99; // Position en Y pour centrer le texte
    afficheChaine("O N / O F F", taille, posX, posY); // Affichage du texte centré dans le cercle
}

void cercleOnOff2() {
    float centreX = largeurFenetre() * 0.9; // Ajustez ces valeurs pour positionner le cercle
    float centreY = hauteurFenetre() * 0.85; // à 50 pixels du coin supérieur droit
    float rayon = largeurFenetre() * 0.07; // Rayon du cercle
    
    epaisseurDeTrait(3); // Augmenter l'épaisseur des bordures
    
    // Dessin du cercle avec bordures noires
    dessineCercle(centreX, centreY, rayon, 255, 0, 0, 0, 0, 0); // Cercle rouge avec bord noir
    
    epaisseurDeTrait(1); // Rétablir l'épaisseur par défaut pour le reste du dessin
    
    // Affichage du texte "ON / OFF"
    couleurCourante(0, 0, 0); // Texte en blanc
    float taille = 15; // Taille du texte
    float tailleTexte = tailleChaine("ON / OFF", taille); // Taille du texte en X
    float posX = centreX - (tailleTexte / 1.45); // Position en X pour centrer le texte
    float posY = centreY * 0.99; // Position en Y pour centrer le texte
    afficheChaine("O N / O F F", taille, posX, posY); // Affichage du texte centré dans le cercle
}


void rectanglesoundOnOff() {
    float coinX = largeurFenetre() * 0.825;
    float coinY = hauteurFenetre() * 0.65;
    float largeur = largeurFenetre() * 0.15;
    float hauteur = hauteurFenetre() * 0.08;

    epaisseurDeTrait(3);
    if (soundOn == false) {
        couleurCourante(255, 0, 0); 
    } else  if (soundOn == true){
        couleurCourante(0, 200, 0); 

    }
    rectangle(coinX, coinY, coinX + largeur, coinY - hauteur);

    couleurCourante(0, 0, 0); // Texte en noir
    float taille = 15;
    float tailleTexte = tailleChaine("Sound ON/OFF", taille);
    float posX = coinX + (largeur - tailleTexte) / 2;
    float posY = coinY - (hauteur / 2) - (taille / 2);
    afficheChaine("Sound ON/OFF", taille, posX, posY);
}

void carrerec() {
    float coinX = largeurFenetre() * 0.825;
    float coinY = hauteurFenetre() * 0.3;
    float largeur = largeurFenetre() * 0.15;
    float hauteur = hauteurFenetre() * 0.08;

    epaisseurDeTrait(3);
    couleurCourante(recOn ? 255 : 0, 0, 0);  // Rouge si enregistrement en cours, sinon noir
    rectangle(coinX, coinY, coinX + largeur, coinY - hauteur);

    couleurCourante(255, 255, 255);  // Texte en blanc
    float taille = 15;
    float tailleTexte = tailleChaine("REC", taille);
    float posX = coinX + (largeur - tailleTexte) / 2;
    float posY = coinY - (hauteur / 2) - (taille / 2);
    afficheChaine("R E C", taille, posX, posY);
}

void carreclic() {
    float coinX = largeurFenetre() * 0.825;
    float coinY = hauteurFenetre() * 0.1;
    float largeur = largeurFenetre() * 0.15;
    float hauteur = hauteurFenetre() * 0.08;

    epaisseurDeTrait(3);
    couleurCourante(0, 0, 0); // Couleur noire pour le contour
    rectangle(coinX, coinY, coinX + largeur, coinY - hauteur);

    couleurCourante(70, 130, 180); // Couleur bleue pour le remplissage
    rectangle(coinX + 1, coinY - 1, coinX + largeur - 1, coinY - hauteur + 1);

    couleurCourante(255, 255, 255); // Couleur blanche pour le texte
    float taille = 17;
    float tailleTexte = tailleChaine("CLIC", taille);
    float posX = coinX + (largeur - tailleTexte) / 2;
    float posY = coinY - (hauteur / 2) - (taille / 2);
    afficheChaine("C L I C", taille, posX, posY);
}


void carre50cm(){


    float coinX = largeurFenetre() * 0.828; // Coin supérieur gauche du rectangle "REC"
    float coinY = hauteurFenetre() * 0.5; // Coin supérieur gauche du rectangle "REC"
    float largeur = largeurFenetre() * 0.05; // Largeur du rectangle "REC"
    float hauteur = hauteurFenetre() * 0.08; // Hauteur du rectangle "REC"
    
    epaisseurDeTrait(3); // Augmenter l'épaisseur des bordures
    
    

    
    if (bouton50cmClique) {
        couleurCourante(255, 255, 255); // Blanc
    } else {
        couleurCourante(192, 192, 192); // Gris
    }
    rectangle(coinX + 1, coinY- 1, coinX+ largeur - 1, coinY- hauteur + 1); // Dessin du rectangle sans les bordures
    
  
    couleurCourante(0, 0, 0); 
    float taille = 15; // Taille du texte
    float tailleTexte = tailleChaine("ON / OFF", taille); // Taille du texte en X
    float posX = coinX - (tailleTexte / 1.15); // Position en X pour centrer le texte
    float posY = coinY * 1.045; // Position en Y pour centrer le texte
    afficheChaine("50cm", taille, posX * 1.095, posY * 0.87);  // Affichage du texte "REC"
}


void carre1m(){


    float coinX = largeurFenetre() * 0.878; // Coin supérieur gauche du rectangle "REC"
    float coinY = hauteurFenetre() * 0.5; // Coin supérieur gauche du rectangle "REC"
    float largeur = largeurFenetre() * 0.05; // Largeur du rectangle "REC"
    float hauteur = hauteurFenetre() * 0.08; // Hauteur du rectangle "REC"
    
    epaisseurDeTrait(3); // Augmenter l'épaisseur des bordures
    
    if (bouton1mClique) {
        couleurCourante(255, 255, 255); // Blanc
    } else {
        couleurCourante(192, 192, 192); // Gris
    }
    rectangle(coinX + 1, coinY- 1, coinX+ largeur - 1, coinY- hauteur + 1); // Dessin du rectangle sans les bordures
    
  
    couleurCourante(0, 0, 0); 
    float taille = 15; // Taille du texte
    float tailleTexte = tailleChaine("ON / OFF", taille); // Taille du texte en X
    float posX = coinX - (tailleTexte / 1.2); // Position en X pour centrer le texte
    float posY = coinY * 1.045; // Position en Y pour centrer le texte
    afficheChaine("1m", taille, posX * 1.095, posY * 0.87);  // Affichage du texte "REC"
}


void carre5m(){


    float coinX = largeurFenetre() * 0.928; // Coin supérieur gauche du rectangle "REC"
    float coinY = hauteurFenetre() * 0.5; // Coin supérieur gauche du rectangle "REC"
    float largeur = largeurFenetre() * 0.05; // Largeur du rectangle "REC"
    float hauteur = hauteurFenetre() * 0.08; // Hauteur du rectangle "REC"
    
    epaisseurDeTrait(3); // Augmenter l'épaisseur des bordures
    
   
   if (bouton5mClique) {
        couleurCourante(255, 255, 255); // Blanc
    } else {
        couleurCourante(192, 192, 192); // Gris
    }
    rectangle(coinX + 1, coinY- 1, coinX+ largeur - 1, coinY- hauteur + 1); // Dessin du rectangle sans les bordures
    
  
    couleurCourante(0, 0, 0); 
    float taille = 15; // Taille du texte
    float tailleTexte = tailleChaine("ON / OFF", taille); // Taille du texte en X
    float posX = coinX - (tailleTexte / 1.13); // Position en X pour centrer le texte
    float posY = coinY * 1.045; // Position en Y pour centrer le texte
    afficheChaine("5m", taille, posX * 1.095, posY * 0.87);  // Affichage du texte "REC"
}

void getFormattedDateTime(char *buffer, size_t bufferSize) {
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, bufferSize, "%Y-%m-%d_%H:%M:%S", timeinfo);
}
