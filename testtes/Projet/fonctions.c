#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <math.h>	
#include "GfxLib.h" 
#include "BmpLib.h" 
#include "ESLib.h"	
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
bool captureEcran = false;


Carre carres[10];


void afficheTableauCarres(){
    // Définir les dimensions et positions des carrés
    float largeurCarre = 60.0; // Largeur d'un carré
    float hauteurCarre = 60.0; // Hauteur d'un carré
    float espacement = 10.0; // Espacement entre les carrés

    float largeur = largeurFenetre();
    float hauteur = hauteurFenetre();

    // Position de départ du tableau
    float debutX = (largeur - (3 * largeurCarre + 2 * espacement)) / 2;
    float debutY = hauteur - (3 * hauteurCarre + 2 * espacement) - 100;

    couleurCourante(255, 255, 255); // Couleur blanche pour les contours des carrés

    int chiffre = 1; // Chiffre à afficher dans les carrés

    // Boucle pour dessiner les 3 lignes et 3 colonnes de carrés
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            float x = debutX + j * (largeurCarre + espacement);
            float y = debutY - i * (hauteurCarre + espacement); // Ajustement pour descendre à chaque ligne

            // Stocker les coordonnées du carré
            carres[chiffre - 1].x = x;
            carres[chiffre - 1].y = y;
            carres[chiffre - 1].largeur = largeurCarre;
            carres[chiffre - 1].hauteur = hauteurCarre;

            // Dessiner le carré

            couleurCourante(255,255,255);
            
            
            rectangle(x, y, x + largeurCarre, y + hauteurCarre);

            // Afficher le chiffre dans le carré
           
            couleurCourante(0,0,0);
            

            char texte[2];
            snprintf(texte, 2, "%d", chiffre++);
            float texteX = x + (largeurCarre - tailleChaine(texte, 20.0)) / 2;
            float texteY = y + (hauteurCarre - 20.0) / 2;
            afficheChaine(texte, 20.0, texteX, texteY);
        }
    }

    // Position du carré supplémentaire en dessous, au milieu
    float carreSupX = (largeur - largeurCarre) / 2;
    float carreSupY = debutY - 3 * (hauteurCarre + espacement); // Ajustement pour placer en dessous

    // Stocker les coordonnées du carré contenant "0"
    carres[9].x = carreSupX;
    carres[9].y = carreSupY;
    carres[9].largeur = largeurCarre;
    carres[9].hauteur = hauteurCarre;

    
    couleurCourante(255,255,255);
            
    rectangle(carreSupX, carreSupY, carreSupX + largeurCarre, carreSupY + hauteurCarre);

    
    couleurCourante(0,0,0);
            
    char texte[2] = "0";
    float texteX = carreSupX + (largeurCarre - tailleChaine(texte, 20.0)) / 2;
    float texteY = carreSupY + (hauteurCarre - 20.0) / 2;
    afficheChaine(texte, 20.0, texteX, texteY);
}



void afficheFondecran(){
    // Rectangle de fond
    couleurCourante(50, 50, 50);
    rectangle(0, 0, largeurFenetre(), hauteurFenetre());

    // Définir la couleur des triangles et des lignes
    couleurCourante(255, 255, 255);

    float largeur = largeurFenetre();
    float hauteur = hauteurFenetre();
    float tailleTriangle = 60.0; // Taille des triangles
    float decalage = 3.0; // Décalage des triangles et des lignes vers le centre

    // Triangle en haut à gauche
    triangle(decalage, hauteur - decalage, tailleTriangle + decalage, hauteur - decalage, decalage, hauteur - tailleTriangle - decalage);

    // Triangle en haut à droite
    triangle(largeur - decalage, hauteur - decalage, largeur - tailleTriangle - decalage, hauteur - decalage, largeur - decalage, hauteur - tailleTriangle - decalage);

    // Triangle en bas à gauche
    triangle(decalage, decalage, tailleTriangle + decalage, decalage, decalage, tailleTriangle + decalage);

    // Triangle en bas à droite
    triangle(largeur - decalage, decalage, largeur - tailleTriangle - decalage, decalage, largeur - decalage, tailleTriangle + decalage);

    // Ligne horizontale supérieure
    ligne(tailleTriangle + decalage, hauteur - decalage, largeur - tailleTriangle - decalage, hauteur - decalage);
    
    // Ligne horizontale inférieure
    ligne(tailleTriangle + decalage, decalage, largeur - tailleTriangle - decalage, decalage);
    
    // Ligne verticale gauche
    ligne(decalage, hauteur - tailleTriangle - decalage, decalage, tailleTriangle + decalage);
    
    // Ligne verticale droite
    ligne(largeur - decalage, hauteur - tailleTriangle - decalage, largeur - decalage, tailleTriangle + decalage);
}


void acceuil() {
    // Définition des dimensions de la fenêtre
    float largeur = largeurFenetre();
    float hauteur = hauteurFenetre();

    // Définition des dimensions du rectangle
    float rectangleLargeur = largeur * 0.4; // 40% de la largeur de la fenêtre
    float rectangleHauteur = hauteur * 0.2; // 20% de la hauteur de la fenêtre

    // Position du rectangle centré horizontalement et verticalement
    float rectangleX = (largeur - rectangleLargeur) / 2;
    float rectangleY = (hauteur - rectangleHauteur) / 2;

    // Dessin du premier rectangle
    // couleurCourante(192, 192, 192); // Couleur gris
    // rectangle(rectangleX, rectangleY, rectangleX + rectangleLargeur, rectangleY + rectangleHauteur);

    // Dessin des contours du premier rectangle en blanc
    couleurCourante(255, 255, 255); // Couleur blanc
    rectangle(rectangleX, rectangleY, rectangleX + rectangleLargeur, rectangleY + rectangleHauteur);

    // Dessin des lignes sur les bords du premier rectangle
    couleurCourante(0, 0, 0); // Couleur noir
    ligne(rectangleX, rectangleY, rectangleX + rectangleLargeur, rectangleY);
    ligne(rectangleX, rectangleY, rectangleX, rectangleY + rectangleHauteur);
    ligne(rectangleX + rectangleLargeur, rectangleY, rectangleX + rectangleLargeur, rectangleY + rectangleHauteur);
    ligne(rectangleX, rectangleY + rectangleHauteur, rectangleX + rectangleLargeur, rectangleY + rectangleHauteur);

    // Définition des dimensions du deuxième rectangle
    float decalageX = -4; // Décalage vers la droite
    float decalageY = -4; // Décalage vers le bas

    // Dessin du deuxième rectangle
    couleurCourante(165, 162, 162); // Couleur noir
    rectangle(rectangleX + decalageX, rectangleY - decalageY, rectangleX + rectangleLargeur + decalageX, rectangleY + rectangleHauteur - decalageY);

    // Dessin des lignes sur les bords du deuxième rectangle
    couleurCourante(0, 0, 0); // Couleur noir
    ligne(rectangleX + decalageX, rectangleY - decalageY, rectangleX + rectangleLargeur + decalageX, rectangleY - decalageY);
    ligne(rectangleX + decalageX, rectangleY - decalageY, rectangleX + decalageX, rectangleY + rectangleHauteur - decalageY);
    ligne(rectangleX + rectangleLargeur + decalageX, rectangleY - decalageY, rectangleX + rectangleLargeur + decalageX, rectangleY + rectangleHauteur - decalageY);
    ligne(rectangleX + decalageX, rectangleY + rectangleHauteur - decalageY, rectangleX + rectangleLargeur + decalageX, rectangleY + rectangleHauteur - decalageY);

    // Dessin du texte "Camera control"
    couleurCourante(0, 0, 0); // Couleur noir
    float tailleTexte = 20.0; // Taille du texte
    float texteX = rectangleX * 1.108; // Ajustement de la position du texte
    float texteY = rectangleY * 1.22; // Ajustement de la position du texte
    afficheChaine("C A M E R A  C O N T R O L", tailleTexte, texteX, texteY);
}


void afficheDateHeure() {
    char datetime[20];
    getFormattedDateTime(datetime, sizeof(datetime));
    
    float largeur = largeurFenetre();
    float hauteur = hauteurFenetre();

    epaisseurDeTrait(1);

    // Définition des dimensions du rectangle principal
    float rectangleLargeur = largeur * 0.4; // 40% de la largeur de la fenêtre
    float rectangleHauteur = hauteur * 0.1; // 10% de la hauteur de la fenêtre

    // Position du rectangle principal centré horizontalement et en haut
    float rectangleX = (largeur - rectangleLargeur) / 2;
    float rectangleY = hauteur - rectangleHauteur - 10; // Position en haut, avec une marge de 10 pixels

    // Définition des dimensions du deuxième rectangle (décalé)
    float decalageX = 4; // Décalage vers la droite
    float decalageY = -4; // Décalage vers le bas

    // Dessin du deuxième rectangle (gris)
    couleurCourante(192, 192, 192); // Couleur gris
    rectangle(rectangleX + decalageX, rectangleY + decalageY, rectangleX + rectangleLargeur + decalageX, rectangleY + rectangleHauteur + decalageY);

    // Dessin des contours du deuxième rectangle en blanc
    couleurCourante(255, 255, 255); // Couleur blanc
    ligne(rectangleX + decalageX, rectangleY + decalageY, rectangleX + rectangleLargeur + decalageX, rectangleY + decalageY);
    ligne(rectangleX + decalageX, rectangleY + decalageY, rectangleX + decalageX, rectangleY + rectangleHauteur + decalageY);
    ligne(rectangleX + rectangleLargeur + decalageX, rectangleY + decalageY, rectangleX + rectangleLargeur + decalageX, rectangleY + rectangleHauteur + decalageY);
    ligne(rectangleX + decalageX, rectangleY + rectangleHauteur + decalageY, rectangleX + rectangleLargeur + decalageX, rectangleY + rectangleHauteur + decalageY);

    // Dessin du premier rectangle (principal, noir)
    couleurCourante(0, 0, 0); // Couleur noire
    rectangle(rectangleX, rectangleY, rectangleX + rectangleLargeur, rectangleY + rectangleHauteur);

    // Dessin des contours du premier rectangle en blanc
    couleurCourante(255, 255, 255); // Couleur blanc
    ligne(rectangleX, rectangleY, rectangleX + rectangleLargeur, rectangleY);
    ligne(rectangleX, rectangleY, rectangleX, rectangleY + rectangleHauteur);
    ligne(rectangleX + rectangleLargeur, rectangleY, rectangleX + rectangleLargeur, rectangleY + rectangleHauteur);
    ligne(rectangleX, rectangleY + rectangleHauteur, rectangleX + rectangleLargeur, rectangleY + rectangleHauteur);

    // Dessin du texte de la date et de l'heure
    couleurCourante(255, 255, 255); // Couleur blanc
    float tailleTexte = 20.0; // Taille du texte
    float texteX = (largeur - tailleChaine(datetime, tailleTexte)) / 2;
    float texteY = rectangleY + (rectangleHauteur - tailleTexte) / 2; // Centré verticalement dans le rectangle
    afficheChaine(datetime, tailleTexte, texteX, texteY);
}




void petitrond() {
    // Taille de la fenêtre
    float largeur = largeurFenetre();
    float hauteur = hauteurFenetre();

    // Rayon du cercle
    float rayon = hauteur * 0.013;

    // Déplacement en diagonale
    float decalage = rayon * 1.5;

    // Coordonnées des centres des cercles, légèrement décalées vers le centre
    float centresX[] = {rayon + decalage, largeur - rayon - decalage, rayon + decalage, largeur - rayon - decalage};
    float centresY[] = {rayon + decalage, rayon + decalage, hauteur - rayon - decalage, hauteur - rayon - decalage};

    // Dessin des cercles
    for (int i = 0; i < 4; i++) {
        float centreX = centresX[i];
        float centreY = centresY[i];

        // Dessiner le cercle
        dessineCercle(centreX, centreY, rayon, 174, 170, 170, 0, 0, 0);

        // Dessiner la ligne noire horizontale au milieu du cercle
        couleurCourante(0, 0, 0);
        epaisseurDeTrait(2);
        ligne(centreX - rayon, centreY, centreX + rayon, centreY);
    }

    // Dessin des bords de la fenêtre en noir avec une épaisseur plus large
    couleurCourante(0, 0, 0);
    epaisseurDeTrait(20); // Augmenter l'épaisseur des traits à 20

    // Ligne supérieure
    ligne(0, hauteur, largeur, hauteur);

    // Ligne inférieure
    ligne(0, 0, largeur, 0);

    // Ligne gauche
    ligne(0, 0, 0, hauteur);

    // Ligne droite
    ligne(largeur, 0, largeur, hauteur);
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
    dessineCercle(centreX, centreY, rayon, 104, 227, 77, 0, 0, 0); // Cercle rouge avec bord noir
    
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
    
    epaisseurDeTrait(1); // Augmenter l'épaisseur des bordures
    
    // Dessin du cercle avec bordures noires
    dessineCercle(centreX, centreY, rayon, 233, 2, 2 , 0, 0, 0); // Cercle rouge avec bord noir
    
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
        couleurCourante(233, 2, 2); 
    } else  if (soundOn == true){
        couleurCourante(104, 227, 77); 

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
    float posX = coinX + (largeur - tailleTexte) / 2.5;
    float posY = coinY - (hauteur / 2) - (taille / 2);
    afficheChaine("R E C", taille, posX, posY);
}

void carreclic() {
    float coinX = largeurFenetre() * 0.825;
    float coinY = hauteurFenetre() * 0.15; // Augmentation plus importante de la position en Y
    float largeur = largeurFenetre() * 0.15;
    float hauteur = hauteurFenetre() * 0.08;

    epaisseurDeTrait(3);
    couleurCourante(0, 0, 0); // Couleur noire pour le contour
    rectangle(coinX, coinY, coinX + largeur, coinY - hauteur);

    if (captureEcran) {
        couleurCourante(255, 0, 0); 
    } else {
        couleurCourante(0, 0, 0); 
    }

    rectangle(coinX + 1, coinY - 1, coinX + largeur - 1, coinY - hauteur + 1);

    couleurCourante(255, 255, 255); // Couleur blanche pour le texte
    float taille = 17;
    float tailleTexte = tailleChaine("CAPTURE", taille);
    float posX = coinX + (largeur - tailleTexte) / 4.5;
    float posY = coinY - (hauteur / 2) - (taille / 2);
    afficheChaine("S C R E E N", taille, posX, posY);
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












