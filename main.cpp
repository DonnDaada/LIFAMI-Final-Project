/*
 
 Mon projet est inspiré du jeu Blooby Volley. Le principe est simple, deux joueurs
 et une balle, le but est de mettre la balle dans le camp adverse.
 La balle aura une physique et rebondira au contact avec les joueurs ou les
 murs prédéfinis.
 Pour le moment seulement les décors sont en place, je les améliorerai au fil
 des semaines.
 
 */

#include <Grapic.h>
using namespace grapic;

const int DIMW = 400;
const int DIMV = 300;
const float d = 4.8f;

struct Complex{
  float x, y;
};

Complex make_complex(float r, float i)
{
    Complex c;
    c.x = r;
    c.y = i;
    return c;
}

//  backGr est le background du jeu
void    backGr(void)
{
    color(224,205,169);
    rectangleFill(0, 0, DIMW, 200);
}

//  fillet représente les filets et sera considéré comme un obstacle
void    fillet(void)
{
    color(0,0,0);
    rectangleFill((DIMW / 2) - 5, 0, (DIMW / 2) + 5, DIMV / 2.5);
}

//  setWall sera une fonction me permettant d'ajouter des murs dans les 4 coins de la fenêtre de manière efficace et ainsi qu'au fillet.
void   setWall(int minx, int miny, int maxx, int maxy)
{
    color(0,0,0);
    rectangleFill((DIMW / 2) - 5, 0, (DIMW / 2) + 5, 200);
}

// Structure de la balle
struct Ball
{
    Complex c;
    float angle;
};

// Structure joueur
struct Player
{
    Complex c;
    float angle;
};

// Fonction d'initialisation de la balle
void  initBall(Ball &b)
{
    b.c = make_complex(DIMW/2, DIMW/2);
    b.angle = 15;
}

// Fonction d'initialisation des joueurs
void  initPlayer(Player &p)
{
    p.angle = 15;
}

// Fonction affichant la balle
void drawBall(Ball &b)
{
    color(255,255,255);
    circleFill( b.c.x, b.c.y, 25);
}

// Fonction affichant les joueurs
void drawPlayers(Player &p)
{
    circleFill( p.c.x, p.c.y, 25);
}

// upadate mets à jour la position de la balle et si celle-ci touche le sol, elle retourne à son emplacement de départ
void update(Ball &b, Player &p1, Player &p2)
{
  // fait tomber la balle au commencement d'une partie (dès qu'une touche de controle est actionnée)
    if (isKeyPressed('s') || isKeyPressed('f') || isKeyPressed('e') || isKeyPressed('k') || isKeyPressed('m') || isKeyPressed('o'))
      while(b.c.y > 25)
        b.c.y-=d;

//Initialise la forme et couleur des joueurs
      color(255,0,0);
      drawPlayers(p1);
      color(0,255,0);
      drawPlayers(p2);
  
// Contrôles des deux joueurs pour aller à gauche
    if (isKeyPressed('s') || isKeyPressed('k'))
    {
      if (isKeyPressed('s') && p1.c.x > 25)
      {
        p1.c.x-=5;
      }
      if (isKeyPressed('k') && p2.c.x > (DIMW / 2) + 30)
      {
        p2.c.x-=5;
      }
      color(255,0,0);
      drawPlayers(p1);
      color(0,255,0);
      drawPlayers(p2);
    }

  // Contrôles des deux joueurs pour aller à droite
    if (isKeyPressed('f') || isKeyPressed('m'))
    {
      if (isKeyPressed('f') && p1.c.x < (DIMW / 2) - 30)
      {
        p1.c.x+=5;
      }
      if (isKeyPressed('m') && p2.c.x < DIMW - 25)
      {
        p2.c.x+=5;
      }
      color(255,0,0);
      drawPlayers(p1);
      color(0,255,0);
      drawPlayers(p2);
    }

  // Contrôles des deux joueurs pour sauter
    if (isKeyPressed('e') || isKeyPressed('o'))
    {
      if (isKeyPressed('e') && p1.c.x < DIMV - 25)
      {
        p1.c.y += 2.f*d;
        p1.c.y -= d;
      }
      if (isKeyPressed('o') && p2.c.x < DIMV - 25)
      {
        p2.c.y += 2.f*d;
        p2.c.y-= d;
      }
      color(255,0,0);
      drawPlayers(p1);
      color(0,255,0);
      drawPlayers(p2);
    }
}

int main(int , char** )
{
    bool stop=false;
    winInit("Flobby Volley", DIMW, DIMV);
    backgroundColor(150, 180, 250);
    backGr();
    Ball b;
    Player p1;

  //Emplacement de départ du joueur 1
    p1.c.x = 100;
    p1.c.y = 25;
    initPlayer(p1);
    Player p2;
  //Emplacement de départ du joueur 2
    p2.c.x = 300;
    p2.c.y = 25;
    initPlayer(p2);
    initBall(b);
    while(!stop)
    {
        winClear();
        backGr();
        fillet();
        setKeyRepeatMode(true);
        drawBall(b);
        drawPlayers(p1);
        drawPlayers(p2);
        update(b, p1, p2);
        stop = winDisplay();
    }
    winQuit();
    return 0;
}

