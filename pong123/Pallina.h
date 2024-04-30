#pragma once
//Intestazione della classe pallina
#include "Intestazione.h"
#include "Rectangle.h"

class Pallina
{
private:
	float x; 
	float y;
	float acc;
	float ray;//Raggio
	//Condizoni per il movimento della pallina
	bool condx;
	bool condy;
	Punti* scr;//Puntatore alla struct collision schreen per gestire le collisioni con lo schermo
	ALLEGRO_COLOR color;//Colore della pallina
public:
	~Pallina(); //Distruttore 
	Pallina(Punti* schren, Color c); //Costruttore 
	Pallina(Pallina *p); //Costruttore di copia
	void movement(Rectangle *p,Scene *scene); //Movimento in caso di singleplayer
	void movement(Rectangle *p1, Rectangle *p2); //Movimento in caso di multiplayer
	void render(); //Metodo per renderizzare la pallina
	void reset(); //Metodo per resettare la pallina nella sua posizione originale
	//Getter
	float getX();
	float getY();
	float getRay();
};
