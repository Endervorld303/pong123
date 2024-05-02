#include "Pallina.h"
#include <allegro5/allegro5.h>

//Costruttore che costruisce la pallina in base alle collisioni dello schermo e in base al colore datogli in input
Pallina::Pallina(Punti* schren, Color c) {
	scr = schren;//Puntano alla stessa area di memoria cosi che se lo schermo cambiasse dimensioni anche la pallina cambierebbe le sue collissioni
	color = colortype(c);
	x = scr[1].x / 2;
	y = scr[1].x / 2;
	acc = 0.5;
	condx = true;
	condy = true;
	
	ray = 10;
}

//Costruttore di coppia(serve per sdopiare la pallina per una meccanica WIP)
Pallina::Pallina(Pallina* p){
	color = p->color;
	x = p->scr[1].x / 2;
	y = p->scr[1].y / 2;
	condx = !p->condy;
	condy = !p->condx;
	scr = p->scr;
	ray = p->ray;
	acc = p->acc;
}

//Distruttore
Pallina::~Pallina() {
	scr = nullptr;
}


//Movimento single player
void Pallina::movement(Rectangle *p, Scene *scene)
{
	//Movimento sulla x
	if (condx) {//Va a destra se è vera condx
		if (x + ray < scr[1].x) { //Se la pallina è dentro il bordo va avanti
			x += acc * MOVPALLINA;
		}
		else {//Senno se tocca lo schermo torna indietro
			condx = false;
		}
	}
	else {//Va a sinistra se la condx è falsa

		if (x - ray > p->getx2())//Se la pallina è più a destra del player va a sinistra
			x -= acc * MOVPALLINA;

		//Se la pallina viene toccata dal player il player guadagna un punto e la pallina torna indietro
		else if ((x - ray) <= p->getx2() && (x + ray) > p->getx1() && (y - ray) > p->gety2() && (y + ray) < p->gety1()) {
			condx = true;
			p->gotaPoint();
		}
		else {//Se la pallina non tocca il player va avanti
			x -= acc * MOVPALLINA;
		}
	}

	//Movimento sulla Y
	if (condy) {//Va su se conddy è vera sennno va giù e se tocca uno dei bordi la condy si inverte
		if (y + ray < scr[1].y)
			y += acc * MOVPALLINA;
		else
			condy = false;
	}
	else {
		if (y - ray > scr[0].y)
			y -= acc * MOVPALLINA;
		else
			condy = true;
	}

}

void Pallina::movement(Rectangle *p1, Rectangle *p2){
	//Movimento asse x
	if (condx) {
		if (x + ray < p2->getx2())
			x += acc * MOVPALLINA;
		
		else if (x + ray >= p2->getx2() && x - ray < p2->getx1() && y - ray >= p2->gety2() && y + ray <= p2->gety1())
			condx = false;
		
		else if (x + ray >= p2->getx2() && x - ray < scr[1].x)
			x += acc * MOVPALLINA;
		
		else{
			p1->gotaPoint();
			reset();
			p1->reset();
			p2->reset();
			al_rest(0.5);
		}
	}else{
		if (x - ray > p1->getx2()) 
			x -= acc * MOVPALLINA;
		
		else if (x - ray <= p1->getx2() && x + ray > p1->getx1() && y - ray >= p1->gety2() && y + ray <= p1->gety1()) 
			condx = true;
		
		else if (x - ray <= p1->getx2() && x + ray > scr[0].x)
			x -= acc * MOVPALLINA;
		

		else {
			p2->gotaPoint();
			p1->reset();
			p2->reset();
			reset();
			al_rest(0.5);
		}
	}


	//Movimento asse y
	if (condy) {
		if (y + ray < scr[1].y)
			y += acc * MOVPALLINA;
		else
			condy = false;
	}
	else {
		if (y - ray > scr[0].y)
			y -= acc * MOVPALLINA;
		else
			condy = true;
	}

	//Per vedere se l'accelerazione è maggiore di 0.5
	if (acc > 0.5) {
		acc -= 0.1;
	}
}

void Pallina::render()
{
	al_draw_filled_circle(x,y,ray,color);
}


void Pallina::reset(){
	x = scr[1].x / 2;
	y = scr[1].y / 2;
	condx = rand() % 2;
	condy = rand() % 2;
}

void Pallina::speedUp(float acceleration){
	acc = acceleration;
}

float Pallina::getX(){
	return x;
}
float Pallina::getY() {
	return y;
}
float Pallina::getRay() {
	return ray;
}

