#include "Rectangle.h"

int Rectangle::playerNum = 0;

Rectangle::Rectangle(Punti *punti, Color c) {
	playerNum++;
	actualIstance = playerNum;
	scr = punti;
	switch(playerNum){
	case 1:
		x1 = scr[0].x + 12;
		x2 = scr[0].x + 12 + RECTWIDTH;
		y1 = scr[1].y / 2 + RECTLENGHT;
		y2 = scr[1].y / 2 - RECTLENGHT;
		break;

	case 2:
		x1 = scr[1].x - 12;
		x2 = scr[1].x - 12 - RECTWIDTH;
		y1 = scr[1].y / 2 + RECTLENGHT;
		y2 = scr[1].y / 2 - RECTLENGHT;
		break;

	case 3:
		std::cerr << "Troppi player nel gioco";
		exit(-1);
		break;
	}
	score = 0;
	color = colortype(c);
	
}

Rectangle::~Rectangle(){
	scr = nullptr;
	playerNum--;
}



float Rectangle::getx1() { return x1; }

float Rectangle::getx2() { return x2; }

float Rectangle::gety1() { return y1; }

float Rectangle::gety2() { return y2; }

int Rectangle::getScore() { return score; }

void Rectangle::gotaPoint() {
	score++; 
}

void Rectangle::render() {
	al_draw_filled_rectangle(x1,y1,x2,y2, color);
}




//Resetta la posizione del player
void Rectangle::reset(){
	switch (actualIstance) {
	case 1:
		x1 = scr[0].x + 12;
		x2 = scr[0].x + 12 + RECTWIDTH;
		y1 = scr[1].y / 2 + RECTLENGHT;
		y2 = scr[1].y / 2 - RECTLENGHT;
		break;
	case 2:
		x1 = scr[1].x - 12;
		x2 = scr[1].x - 12 - RECTWIDTH;
		y1 = scr[1].y / 2 + RECTLENGHT;
		y2 = scr[1].y / 2 - RECTLENGHT;
		break;
	}
}




Player::Player(Punti* scr, Color c, std::string name) : Rectangle::Rectangle(scr, c){
	switch (playerNum){
	case 1:
		keyUp = ALLEGRO_KEY_W;
		keyDown = ALLEGRO_KEY_S;
		break;

	case 2:
		keyUp = ALLEGRO_KEY_UP;
		keyDown = ALLEGRO_KEY_DOWN;
		break;
	}
	this->name = name;
}

void Player::action(){
	ALLEGRO_KEYBOARD_STATE key;
	al_get_keyboard_state(&key);
	if (al_key_down(&key,keyUp) && y2 > scr[0].y) {
		y1 -= MOVEMENTRECT;
		y2 -= MOVEMENTRECT;
	}
	if (al_key_down(&key, keyDown) && y1 < scr[1].y) {
		y1 += MOVEMENTRECT;
		y2 += MOVEMENTRECT;
	}
}
Player::~Player(){
	scr = nullptr;
}

std::string Player::getName(){
	return name;
}

void Player::resetAll(){
	reset();
	score = 0;
}

void SpecialPlayer::action(){
	ALLEGRO_KEYBOARD_STATE key;
	al_get_keyboard_state(&key);

	//Azioni legate al movimento
	if (al_key_down(&key, keyUp) && y2 > scr[0].y) {
		y1 -= MOVEMENTRECT;
		y2 -= MOVEMENTRECT;
	}
	if (al_key_down(&key, keyDown) && y1 < scr[1].y) {
		y1 += MOVEMENTRECT;
		y2 += MOVEMENTRECT;
	}


	//Azioni slegate dal movimento
	if(al_key_down(&key,ALLEGRO_KEY_SPACE) && )


}
