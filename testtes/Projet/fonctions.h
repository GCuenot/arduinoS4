#ifndef FONCTIONS_H
#define FONCTIONS_H



extern bool soundOn;
// fonctions.h
extern bool bouton50cmClique;
extern bool bouton1mClique;
extern bool bouton5mClique;

extern bool clicSurFlecheDroite;
extern bool clicSurFlecheGauche;
extern bool clicSurFlecheHaut;
extern bool clicSurFlecheBas;



void afficheFondecran();
void flechedroite();
void flechegauche();
void flechehaut();
void flechebas();
void cercleOnOff();
void cercleOnOff2();
void dessineCercle(float centreX, float centreY, float rayon, int rouge, int vert, int bleu, int contourRouge, int contourVert, int contourBleu);
void rectanglesoundOnOff();
void carrerec();
void carreclic();
void carre50cm();
void carre1m();
void carre5m();




#endif