#pragma once
#include "Intestazione.h"
//Classe triangolo. Serve come clase madre per il tiangolo 
class Triangle{
protected:
	Punti punti[3];//Punti del triangolo
	ALLEGRO_COLOR color;//Colore del triangolo

public:
	Triangle(Color c);//Costruttore
	~Triangle();//Costruttore
	void render();//Metodo di render
	virtual void move() = 0;//Metodo virtaule di movimento
};

//
class SelecTriangle : public Triangle {
private:
	std::vector<Punti> p; //Punti per spostare il triangolo
	std::vector<Scene> corrScene; //Corrispettiva scene collleggata al punto p

public:
	SelecTriangle(Color c);//Costruttore
	~SelecTriangle();//Distruttore
	void move() override;//Overide del metodo virtuale
	void addpoint(Punti p, Scene scene);//Aggiunge un punto in cui può spostarsi il tiangolo e l'azione collegata
	void addpoint(int x, int y, Scene scene);
	void changeScene(Scene *scene);//Cambio della scena
};

