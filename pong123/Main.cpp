//Può essere eseguito solo su x86 sia release che debug. Non ho idea perché probabbilmente perché in x64 non linka le librerie
#include "Intestazione.h"
#include "Pallina.h"
#include "Rectangle.h"
#include "Triangle.h"

using std::vector;

//Funzioni definibili solo nel main perché non definibili in Intestazione.h perché richiedono classi in Rectangle e Pallina
void action(SpecialPlayer* p1, SpecialPlayer* p2, Pallina* pallina, ALLEGRO_KEYBOARD_STATE* key);


int main() {
	//Inizializzazione di tutte le addon di allegro che servono per il programma
	al_init();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();
	srand(time(NULL));//Per il rand delle condizioni della pallina

	Punti *scr = new Punti[2];//Bordi dello schermo
	scr[0].x = 0;
	scr[1].x = 1200;
	scr[0].y = 0;
	scr[1].y = 900;

	//Creazione delle cose necessarie per il gioco come il display, il font, il timer e la codo di eventi
	ALLEGRO_DISPLAY* display = al_create_display(1200,900);
	ALLEGRO_FONT *font = al_load_ttf_font("YARDSALE.TTF", 30, 0);
	ALLEGRO_TIMER *timer = al_create_timer(1.0/FPS);
	ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
	ALLEGRO_KEYBOARD_STATE key;

	//Inizializzazione dei puntatori agli oggetti del gioco
	Rectangle* player1 = nullptr;//Player1
	Rectangle* player2 = nullptr;//Player2
	Pallina* ball = nullptr;//Palla del gioco
	SelecTriangle* t = new SelecTriangle(RED);//Triangolo del Menu

	//Aggiungo i punti dove il triangolo può spostarsi e le azioni correlate al punto
	t->addpoint(150,315,INITSINGLE);//Singleplayer base
	t->addpoint(750,315, INITMULTI);//Multiplayerbase
	t->addpoint(100,465, INITSINGLES);//Singpeayer wip
	t->addpoint(680,465, INITMULTIS);//Multiplayer Speciale

	//Altre variabili per la logica del gioco
	bool running = true;
	Scene scene = MENU;
	bool win = NULL;

	//Registrazione degli eventi del gioco alla coda 
	al_register_event_source(queue,al_get_display_event_source(display));
	al_register_event_source(queue,al_get_timer_event_source(timer));
	//Inizio del timer
	al_start_timer(timer);

	//Ciclo di gioco
	while (running) {
		ALLEGRO_EVENT ev;//Eventi del gioco
		al_get_next_event(queue, &ev);//Cattura degli eventi

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			al_clear_to_color(colortype(BLACK));
			al_get_keyboard_state(&key);
			
			//Switch per vedere in che scena siamo
			switch (scene) {
			case MENU:
				//Siamo nel menu quindi crea le 4 scritte con le 4 modalita 
				//e poi in base al tasto premuto il triangolo si sposta su un opzione di gioco
				al_draw_text(font, colortype(BLUE), 600, 100, ALLEGRO_ALIGN_CENTER, "Selezione Modalita':");
				al_draw_text(font, colortype(BLUE), 300, 300, ALLEGRO_ALIGN_CENTER, "1)SinglePLayer");
				al_draw_text(font, colortype(BLUE), 900, 300, ALLEGRO_ALIGN_CENTER, "2)Multiplayer");
				al_draw_text(font, colortype(BLUE), 300, 450, ALLEGRO_ALIGN_CENTER, "3)Singleplayer (WIP)");
				al_draw_text(font, colortype(BLUE), 900, 450, ALLEGRO_ALIGN_CENTER, "4)Special Multiplayer ");
				//Render e move del triangolo del menu
				t->move();
				t->render();
				t->changeScene(&scene);
				break;



			case INITSINGLE:
				//Qui si istanziano tutti gli oggetti riguardanti il singleplayer e poi si cambia la scena nel gioco singleplayer
				player1 = new Player(scr, INDIGO, "Ash Lynx");
				ball = new Pallina(scr, WHITE);
				scene = SINGLEPLAYER;
				break;


			case SINGLEPLAYER:
				//Siamo nella scena singleplayer e quindi crea la scena del singleplayer, con la scritta col punteggio
				//E poi fa muovere il player e la pallina e poi li renderizza
				al_draw_textf(font, player1->getColor(), 600, 100, ALLEGRO_ALIGN_CENTER, "Punti di %s: %d", ((Player*)player1)->getName().c_str(), player1->getScore());
				
				//Movimenti
				player1->movement();
				ball->movement(player1, &scene);
				
				//Render
				player1->render();
				ball->render();

				//Condizione per vedere se la pallina va fuori dallo schermo
				if ((ball->getX() - ball->getRay()) < scr[0].x)
					gameisover(&scene);
				break;


			case GAMEOVERS:
				//Siamo nel gameover del Singleplayer
				al_draw_text(font, colortype(RED), 600, 300, ALLEGRO_ALIGN_CENTER, "HAI PERSO");
				al_draw_text(font, colortype(RED), 300, 450, ALLEGRO_ALIGN_CENTER, "Premi R per ricominciare");
				al_draw_text(font, colortype(RED), 900, 450, ALLEGRO_ALIGN_CENTER, "Premi M per il Menu");
				//Se viene premuto il tasto R il gioco si resetta e si torna al singleplayer
				if (al_key_down(&key, ALLEGRO_KEY_R)) {
					((Player*)player1)->resetAll();
					ball->reset();
					scene = SINGLEPLAYER;
				}
				//Se viene premuto il tasto M allora si tornera al Menu, non prima di aver distrutto gli oggetti del singleplayer 
				else if (al_key_down(&key, ALLEGRO_KEY_M))
					scene = DELSINGLE;
				break;


			case DELSINGLE:
				//Siamo nella distruzzione della scena del singleplayer 
				// e qui vengono distrutti tutti gli oggetti riguardanti il singleplayer e si cambia la scena nel menu
				delete ball;
				delete player1;
				player1 = nullptr;
				ball = nullptr;
				scene = MENU;
				break;



			case INITMULTI:
				//Qui si istanziano tutti gli oggetti riguardanti il multiplayer e poi si cambia la scena nel gioco multiplayer
				player1 = new Player(scr, WHITE, "Giocatore 1");
				player2 = new Player(scr, WHITE, "Giocatore 2");
				ball = new Pallina(scr, WHITE);
				scene = MULTIPLAYER;
				break;

			case MULTIPLAYER:
				//Siamo nella scena multiplayer quindi crea le scritte dei 2 player con i loro punteggi
				//E fa muovere i player e la pallina e poi li renderizza
				al_draw_textf(font, player1->getColor(), 300, 100, ALLEGRO_ALIGN_CENTER, "Punti di %s: %d", ((Player*)player1)->getName().c_str(), player1->getScore());
				al_draw_textf(font, player2->getColor(), 900, 100, ALLEGRO_ALIGN_CENTER, "Punti di %s: %d", ((Player*)player2)->getName().c_str(), player2->getScore());
				
				//Movimenti
				player1->movement();
				player2->movement();
				ball->movement(player1, player2);
				
				//Render
				player1->render();
				player2->render();
				ball->render();

				//Se uno dei player arriva allo score di vittoria vince e il gioco va in gameisover
				//In questo caso lo gestisco nel main perché la condizione di gameover è data dal player e non dalla pallina
				if (player1->getScore() >= WINSCORE || player2->getScore() >= WINSCORE) {
					gameisover(&scene);
					win = player1->getScore() > player2->getScore();
				}
				break;

			case GAMEOVERM:
				//Siamo nel gameover del multiplayer 
				if (win)//Se vince il primo player o il secondo player 
					al_draw_textf(font, colortype(RED), 600, 300, ALLEGRO_ALIGN_CENTER, "Ha vinto %s", ((Player*)player1)->getName().c_str());
				else 
					al_draw_textf(font, colortype(RED), 600, 300, ALLEGRO_ALIGN_CENTER, "Ha vinto ", ((Player*)player2)->getName().c_str());
				al_draw_text(font, colortype(RED), 300, 450, ALLEGRO_ALIGN_CENTER, "Premi R per ricominciare");
				al_draw_text(font, colortype(RED), 900, 450, ALLEGRO_ALIGN_CENTER, "Premi M per il Menu");
				
				//Se viene premuto il tasto R il multiplayer si resetta
				if (al_key_down(&key, ALLEGRO_KEY_R)) {
					((Player*)player1)->resetAll();
					((Player*)player2)->resetAll();
					ball->reset();
					scene = MULTIPLAYER;
				}
				//Senno se viene premuto il tasto M si torna al menu pero prima distruggendo gli oggetti usati nel Multiplayer 
				else if (al_key_down(&key, ALLEGRO_KEY_M))
					scene = DELMULTY;
				break;

			case DELMULTY:
				//Siamo nella distruzzione della scena del Multiplayer
				// e qui vengono distrutti tutti gli oggetti riguardanti il Multiplayer e si cambia la scena nel menu
				delete ball;
				delete player1;
				delete player2;
				player1 = nullptr;
				player2 = nullptr;
				ball = nullptr;
				scene = MENU;
				break;



			case INITMULTIS:
				player1 = new SpecialPlayer(scr, WHITE, "Giocatore 1");
				player2 = new SpecialPlayer(scr, WHITE, "Giocatore 2");
				ball = new Pallina(scr, WHITE);
				scene = SPECIALMULTI;
				al_rest(0.5);
				break;

			case SPECIALMULTI:
				al_draw_textf(font, player1->getColor(), 300, 100, ALLEGRO_ALIGN_CENTER, "Punti di %s: %d", ((Player*)player1)->getName().c_str(), player1->getScore());
				al_draw_textf(font,player1->getColor(),300,130,ALLEGRO_ALIGN_CENTER,"PowerUp attuale : %s", ((SpecialPlayer*)player1)->getPowerupStr().c_str());
				al_draw_textf(font, player2->getColor(), 900, 100, ALLEGRO_ALIGN_CENTER, "Punti di %s: %d", ((Player*)player2)->getName().c_str(), player2->getScore());
				al_draw_textf(font, player2->getColor(), 900, 130, ALLEGRO_ALIGN_CENTER, "PowerUp attuale : %s", ((SpecialPlayer*)player2)->getPowerupStr().c_str());

				((SpecialPlayer*)player1)->movement();
				((SpecialPlayer*)player2)->movement();
				ball->movement(player1,player2);

				action((SpecialPlayer*)player1, (SpecialPlayer*)player2, ball, &key);
				action((SpecialPlayer*)player2, (SpecialPlayer*)player1, ball, &key);
				
				player1->render();
				player2->render();
				ball->render();

				if (player1->getScore() >= WINSCORE || player2->getScore() >= WINSCORE) {
					gameisover(&scene);
					win = player1->getScore() > player2->getScore();
				}

				break;




			case INITSINGLES:
				player1 = new Player(scr, RED,"EMU OTORI");
				player2 = new Npc(scr,BLUE);
				ball = new Pallina(scr,INDIGO);
				scene = SPECIALSINGLE;
				al_rest(0.5);
				break;

			case SPECIALSINGLE:
				al_draw_textf(font, player1->getColor(), 600, 100, ALLEGRO_ALIGN_CENTER, "Punti di %s: %d", ((Player*)player1)->getName().c_str(), player1->getScore());
				al_draw_textf(font, player1->getColor(), 600, 130, ALLEGRO_ALIGN_CENTER, "PowerUp attuale : %s", ((SpecialPlayer*)player1)->getPowerupStr().c_str());
				player1->movement();
				player2->movement();
				ball->movement(player1,player2);
				player1->render();
				player2->render();
				ball->render();
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
			running = false;


		al_flip_display();
	}

	//Se alla chiusura del display i player o la pallina sono ancora esistenti allora li si distrugge
	if(player1 != nullptr) 
		delete player1;
	
	if(player2 != nullptr) 
		delete player2;
	
	if(ball != nullptr) 
		delete ball;

	delete t;
	delete[2] scr;
	al_destroy_display(display);
	al_uninstall_keyboard();
	al_shutdown_primitives_addon();
	al_shutdown_font_addon();
}









//Funzioni presenti in intestazione
//Funzione per tradurre un colore dal enum Color creato da me che traduce in un ALLEGRO_COLOR per seplificare la gestione dei colori
ALLEGRO_COLOR colortype(Color color) {
	ALLEGRO_COLOR colour;
	switch (color) {
	case RED:
		colour = al_map_rgb(255, 45, 70);
		break;
	case BLUE:
		colour = al_map_rgb(30, 40, 230);
		break;
	case GREEN:
		colour = al_map_rgb(20, 255, 60);
		break;
	case YELLOW:
		colour = al_map_rgb(235, 235, 40);
		break;
	case PURPLE:
		colour = al_map_rgb(240, 75, 240);
		break;
	case INDIGO:
		colour = al_map_rgb(6,2,112);
		break;
	case BLACK:
		colour = al_map_rgb(0, 0, 0);
		break;
	case WHITE:
		colour = al_map_rgb(255, 255, 255);
		break;

		return colour;
	}
}

void gameisover(Scene *acScene){
	if (*acScene == SINGLEPLAYER)
		*acScene = GAMEOVERS;
	else if (*acScene == MULTIPLAYER || *acScene == SPECIALMULTI)
		*acScene = GAMEOVERM;
	else
		std::cerr << "Niente gameover ";
}

void action(SpecialPlayer* p1, SpecialPlayer* p2, Pallina* pallina, ALLEGRO_KEYBOARD_STATE *key){
	al_get_keyboard_state(key);
	if (al_key_down(key, p1->getPkey())) {
		switch (p1->getPowerup()) {
		case FREEZE:
			p2->freeze();
			p1->powerUsed();
			break;
		case SPEEDUPBALL:
			pallina->speedUp(2.5);
			p1->powerUsed();
			break;
		case SUPERPOINT:
			p1->superPoint();
			p1->powerUsed();
			break;
		}
	}
}
