#pragma once
#include "Intestazione.h"
class Rectangle
{
protected:
	static int playerNum;//Variabile per vedere quante istanze di rectangle o classe figlie di rectangle ci siano
	int actualIstance;//Variabile pe vedere che istanza sia di rectangle
	//Vari punti del rettangolo
	float x1;
	float x2;
	float y1;
	float y2;

	int score;//Punteggio
	ALLEGRO_COLOR color;//Colore del rettangolo
	Punti *scr;//Punti dello schermo

public:
	Rectangle(Punti *scr, Color c);//Costruttore
	virtual ~Rectangle(); //Distruttore
	//getter
	float getx1();
	float getx2();
	float gety1();
	float gety2();
	int getScore();

	virtual void gotaPoint();//Per far ottenerte pla player un punto
	void render();//Renderizza il rettangolo
	virtual void movement() = 0;//Metodo astratta per il movimento
	void reset();//Reset del rettangolo
};


//Classe figlia di rectangle
class Player : public Rectangle {
protected:
	std::string name;

	int keyUp;//Tasto con cui il player va su
	int keyDown;//Tasto con il player va giù
public:
	Player(Punti *scr, Color c, std::string name);//Costruttore
	~Player();//Distruttore
	virtual void movement() override;//Over ride del metodo astratta
	std::string getName();//Getter del nome
	void resetAll();//Resetta tutto
};



//Classe di player speciale per la modalita speciale del singleplayer e multiplayer
class SpecialPlayer : public Player {
private:
	int healt;//Vita
	powerUp power;//Potere usabile 
	int keyPower;
public:
	SpecialPlayer(Punti* scr, Color c, std::string name);
	~SpecialPlayer();
	int getPkey();
	powerUp getPowerup();
	void freeze();//Freezza il personaggio per 3 secondi
	/*void loseHealth();//Perdi vita
	void decrease();//Diminuisce la dimensione per 10 secondi
	void increase();//Aumenta la dimmensione per 10 secondi
	void gotaPoint() override;//Ottieni un punto, override perché riscrive il gotapoint di Player
	*/
};



//Classe Npc (WIP)
class Npc : public Rectangle {};