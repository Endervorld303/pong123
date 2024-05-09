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

ALLEGRO_COLOR Rectangle::getColor() {
	return color;
}

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
	if (name == "Ash Lynx")
		color = al_map_rgb(255,215,0);
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

void Player::movement(){
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
	Rectangle::~Rectangle();
}

std::string Player::getName(){
	return name;
}

void Player::resetAll(){
	reset();
	score = 0;
}



SpecialPlayer::SpecialPlayer(Punti* scr, Color c, std::string name) : Player(scr,c,name), Special(){
	healt = 3;//Vite disponibili
	power = FREEZE;//Nullo perché non si ha nessun power up
	condMov = true;
	doublePoint = false;
	movConter = 0;

	switch (actualIstance) {
	case 1:
		keyPower = ALLEGRO_KEY_SPACE;
		break;
	case 2:
		keyPower = ALLEGRO_KEY_ENTER;
		break;
	}
}

SpecialPlayer::~SpecialPlayer(){
	Player::~Player();
}

int SpecialPlayer::getPkey(){
	return keyPower;
}


void SpecialPlayer::movement(){
	if (condMov)
		Player::movement();
	else {
		if (movConter > FREEZETIME) {
			condMov = true;
			movConter = 0;
		}
			
		else
			movConter++;
	}
}

void SpecialPlayer::loseHealth(){
	healt--;
}


void SpecialPlayer::gotaPoint(){
	if (doublePoint) {
		score += 2;
		doublePoint = false;
	}
	else 
		score++;
}

Npc::Npc(Punti* scr, Color c) : Rectangle::Rectangle(scr,c){
	power = PNULL;
	condy = rand() % 2;
	condMov = true;
	doublePoint = false;
	movConter = 0;
}

Npc::~Npc(){
	scr = NULL;
}

void Npc::movement(){
	if (condMov) {
		if (condy) {
			if (y1 < scr[1].y) {
				y1 += MOVEMENTRECT;
				y2 += MOVEMENTRECT;
			}
			else {
				condy = false;
			}
		}
		else {
			if (y2 > scr[0].y) {
				y1 -= MOVEMENTRECT;
				y2 -= MOVEMENTRECT;
			}
			else {
				condy = true;
			}
		}
	}
	else {
		if (movConter > FREEZETIME) {
			condMov = true;
			movConter = 0;
		}

		else
			movConter++;
	}
}

void Npc::gotaPoint(){
	if (doublePoint) {
		score += 2;
		doublePoint = false;
	}
	else {
		score++;
	}
}








Special::Special(){
	power = PNULL;
	condMov = true;
	movConter = 0;
	doublePoint = false;
}

Special::~Special(){}

powerUp Special::getPowerup() {
	return power;
}

std::string Special::getPowerupStr()
{
	std::string powerStr;
	switch (power) {
	case PNULL:
		powerStr = "Nessuno";
		break;
	case FREEZE:
		powerStr = "Freeze";
		break;
	case SPEEDUPBALL:
		powerStr = "SpeedUp";
		break;
	case SUPERPOINT:
		powerStr = "SuperPoint";
		break;
	}
	return powerStr;
}

void Special::powerUsed() {
	power = PNULL;
}


void Special::freeze() {
	condMov = false;
	movConter = 0;
}

void Special::superPoint() {
	doublePoint = true;
}