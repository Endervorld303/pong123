#pragma once
//File di intestazione che serve per includere una volta per tutte tutte le librerie senza doverle poi rincludere una ad una
//Serve anche per gestire le costanti, gli enum le funzioni e delle struct
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cstring>
#include <vector>
//Costanti/Direttive del processore
#define MOVPALLINA 1
#define MOVEMENTRECT 1
#define RECTLENGHT 100
#define RECTWIDTH 15
#define LATO 40
#define WINSCORE 5
#define FPS 60.0
#define FREEZETIME (FPS*5)

//Enum che serve per capire in che scena del gioco ci troviamo attualmente
enum Scene {
	MENU,

	INITSINGLE,
	SINGLEPLAYER,
	GAMEOVERS,
	DELSINGLE,

	INITMULTI, 
	MULTIPLAYER,
	GAMEOVERM,
	DELMULTY,	
};

//Enum per semplificare la gestione dei colori
enum Color {
	RED,
	BLUE,
	GREEN,
	YELLOW,
	PURPLE,
	BLACK,
	WHITE
};


//Enum che crea i tipi powerup/Azioni nellaa modalita speciale
enum powerUp {
	PNULL = NULL,//Potere Nullo(Messo perché senno non lo accettava)
	FREEZE,//Freeza il player avversario
	SPEEDUPBALL,//Aumenta la velocita della pallina
	SUPERPOINT,//Il prossimo punto che si fa varrà 2 punti
};


//Struct che serve per definire determinati punti con x e y. Questi punti possono essere punti di collissione perlo schermo e punti come punti di un triangolo
struct Punti {
	float x;
	float y;
};



//Funzione che prende in input l'enum Color e lo traduce nel corrispettivo ALLEGRO_COLOR
ALLEGRO_COLOR colortype(Color color);

//Funzione per mandare il gameover, usa la scena attuale e restituisce il corrispettivo gameover
void gameisover(Scene *acScene);