#ifndef FONCTIONS_H
#define FONCTIONS_H



extern bool soundOn;

extern bool bouton50cmClique;
extern bool bouton1mClique;
extern bool bouton5mClique;

extern bool clicSurFlecheDroite;
extern bool clicSurFlecheGauche;
extern bool clicSurFlecheHaut;
extern bool clicSurFlecheBas;
extern bool captureEcran;




typedef struct {
    float x, y, largeur, hauteur;
} Carre;

extern Carre carres[10];



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
void getFormattedDateTime(char *buffer, size_t bufferSize);
void petitrond();
void acceuil();
void afficheDateHeure();
void afficheTableauCarres();
void afficherTexte(const char *texte, float x, float y);
void texte1();
void texte2();



#endif