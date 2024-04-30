#include "Triangle.h"

Triangle::Triangle(Color c){
	punti[0].x = 0;
	punti[0].y = 0;
	punti[1].x = 0;
	punti[1].y = 0;
	punti[2].x = 0;
	punti[2].y = 0;
	color = colortype(c);
}

Triangle::~Triangle(){}

void Triangle::render(){
	if ( punti[0].x != 0) {
		al_draw_filled_triangle(punti[0].x, punti[0].y, punti[1].x, punti[1].y, punti[2].x, punti[2].y, color);
	}
}

SelecTriangle::SelecTriangle(Color c) : Triangle::Triangle(c){}


SelecTriangle::~SelecTriangle(){}

void SelecTriangle::move(){
	ALLEGRO_KEYBOARD_STATE key;
	al_get_keyboard_state(&key);
	for (int i = 0; i < p.size(); i++) {
		if (al_key_down(&key, ALLEGRO_KEY_1 + i)) {
			punti[0].x = p[i].x;
			punti[0].y = p[i].y;
			punti[1].x =punti[0].x - LATO;
			punti[1].y = punti[0].y + LATO/2;
			punti[2].x = punti[0].x - LATO;
			punti[2].y = punti[0].y - LATO/2;
		}
	}
}

void SelecTriangle::addpoint(Punti punto, Scene scene){
	p.push_back(punto);
	corrScene.push_back(scene);
}

void SelecTriangle::addpoint(int x, int y, Scene scene){
	Punti punt;
	punt.x = x;
	punt.y = y;
	p.push_back(punt);
	corrScene.push_back(scene);
}

void SelecTriangle::changeScene(Scene* scene){
	ALLEGRO_KEYBOARD_STATE key;
	al_get_keyboard_state(&key);
	if (al_key_down(&key, ALLEGRO_KEY_ENTER)) {
		for (int i = 0; i < corrScene.size(); i++) {
			if (punti[0].x == p[i].x && punti[0].y == p[i].y) {
				*scene = corrScene[i];
			}
		}
	}
}


