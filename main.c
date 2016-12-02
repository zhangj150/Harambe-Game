#include "myLib.h"
#include "harambe.h"
#include "bullets.h"
#include "zookeeper.h"
#include "game.h"
#include "title.h"
int prevX = 80;
int prevY = 80; //harambe's position
//gamestates defined here.
enum GBAState {
	START,
	START_NODRAW, CASE1, DRAWHARAMBEDOWN,
	DRAWHARAMBEUP, DRAWLEFT, DRAWRIGHT, GAMEOVER
};
//main contains state machine that runs game's storyboard
int main() {
	int lives = 5;
	int toren = 1;
	REG_DISPCNT = MODE3 | BG2_ENABLE;
	enum GBAState state = START;
	while(1) {
		waitForVblank();
		switch(state) {
			case START:
				toren = 1;
				lives = 5;
				drawImage(0, 0, TITLE_WIDTH, TITLE_HEIGHT, title);
				while (toren) {
					if (KEY_DOWN_NOW(BUTTON_A)) {
						toren = 0;
					}
				}
				fillScreen(BLACK);
				state = START_NODRAW;
				break;
			case START_NODRAW:
				rainBullets();
				int toren1 = 1;
				//detects collisions and decrement lives.
				if (detectCollision(prevX, prevY)) {
					drawChar(4, 220, lives+48, BLACK);
					lives--;
					if (lives <= 0) {
						state = GAMEOVER;
					}
				}
				drawChar(4, 220, lives+48, GREEN);
				drawString(4, 180, "LIVES: ", GREEN);
				//displays score on top left
				drawImage(prevY, prevX, HARAMBE_WIDTH, HARAMBE_HEIGHT, harambe);
				//while(toren1) { //determines which way to move based on keypress
				if (KEY_DOWN_NOW(BUTTON_DOWN)
					&& prevY + HARAMBE_HEIGHT < 160) {
					toren1 = 0;
					state = DRAWHARAMBEDOWN;
				}
				if (KEY_DOWN_NOW(BUTTON_UP)
					&& prevY > 0) {
					toren1 = 0;
					state = DRAWHARAMBEUP;
				}
				if (KEY_DOWN_NOW(BUTTON_LEFT)
					&& prevX > 0) {
					toren1 = 0;
					state = DRAWLEFT;
				}
				if (KEY_DOWN_NOW(BUTTON_RIGHT)
					&& prevX + HARAMBE_WIDTH < 240) {
					toren1 = 0;
					state = DRAWRIGHT;
				}
				if (KEY_DOWN_NOW(BUTTON_SELECT)) {
					//fillScreen(BLACK);
					nullifyBullets();
					state = START;
					break;
				}
				//}
				break;
			case CASE1:
				state = START_NODRAW;
				break;
			case DRAWHARAMBEDOWN: //the following cases determine how harambe should move
				if (lives <= 0) {
					state = GAMEOVER;
				}
				drawImage(prevY + 2, prevX, HARAMBE_WIDTH, HARAMBE_HEIGHT, harambe);
				drawRect(prevY, prevX, 2, HARAMBE_WIDTH, BLACK); //fils in background again
				prevY += 2;
				state = START_NODRAW;
				break;
			case DRAWHARAMBEUP:
				if (lives <= 0) {
					state = GAMEOVER;
				}
				drawImage(prevY-2, prevX, HARAMBE_WIDTH, HARAMBE_HEIGHT, harambe);
				drawRect(prevY+HARAMBE_HEIGHT, prevX, 2, HARAMBE_WIDTH, BLACK);
				prevY -= 2;
				state = START_NODRAW;
				break;
			case DRAWLEFT:
				if (lives <= 0) {
					state = GAMEOVER;
				}
				drawImage(prevY, prevX - 2, HARAMBE_WIDTH, HARAMBE_HEIGHT, harambe);
				drawRect(prevY, prevX+HARAMBE_WIDTH, HARAMBE_HEIGHT, HARAMBE_WIDTH, BLACK);
				prevX -= 2;
				state = START_NODRAW;
				break;
			case DRAWRIGHT:
				if (lives <= 0) {
					state = GAMEOVER;
				}
				drawImage(prevY, prevX+2, HARAMBE_WIDTH, HARAMBE_HEIGHT, harambe);
				drawRect(prevY, prevX-2, HARAMBE_HEIGHT, 2, BLACK);
				prevX += 2;
				state = START_NODRAW;
				break;
			case GAMEOVER:
				drawImage(0, 0, ZOOKEEPER_WIDTH, ZOOKEEPER_HEIGHT, zookeeper);
				drawString(150, 10, "Game OVER!!     Backspace to main", BLUE);
				int torenado = 1;
				while(torenado) {
					if (KEY_DOWN_NOW(BUTTON_SELECT)) {
						nullifyBullets();
						state = START;
						break;
					}
				}
				break;

		}
	}

	return 0;
}

