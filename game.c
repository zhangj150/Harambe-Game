#include "myLib.h"
#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include "bullets.h"
#include "harambe.h"

typedef struct {
	int prevPosX;
	int prevPosY;
	int x;
	int y;
	int collide;
} BULLETS;

#define MAX_BULLET 21
BULLETS b[MAX_BULLET];
int tempo = 0;
int currentBullet = 0;
//int lives = 5;

void rainBullets() {
	if (tempo%10 == 0) {
		//drawImage(prevPosY, prevPosX, BULLETS_WIDTH, BULLETS_HEIGHT, bullets);
		b[currentBullet].x = rand()%(240-BULLETS_WIDTH/2);
		b[currentBullet].y = 0;
		b[currentBullet].collide = 1;
		currentBullet++;
		currentBullet = currentBullet%MAX_BULLET;
	}
	tempo++;
	for (int i=0; i<MAX_BULLET; i++) {
		if (b[i].collide > 0) { //determines if bullet has been nullified (see below)
			drawRect(b[i].prevPosY, b[i].prevPosX, 3, BULLETS_WIDTH, BLACK);
			//fills space behind bullet as it moves.
			if (b[i].y > 160) {
				b[i].collide = 0;
			} else { //draw bullets moving downwards
				b[i].prevPosX = b[i].x;
				b[i].prevPosY = b[i].y;
				b[i].y += 3;
				drawImage(b[i].y, b[i].x, BULLETS_WIDTH, BULLETS_HEIGHT, bullets);
			}
		}
	}
}

//self explanatory: detect bullet collision with harambe
int detectCollision(int harambeX, int harambeY) {
	//move hitboxes to center of harambe image
	harambeX = harambeX + HARAMBE_WIDTH/2;
	harambeY = harambeY + HARAMBE_HEIGHT/2;
	for (int i=0; i < MAX_BULLET; i++) {
		//move hitboxes to center of bullet images
		int bulletCenterX = BULLETS_WIDTH/2;
		int bulletCenterY = BULLETS_HEIGHT/2;
		if ((abs(harambeX-(b[i].x+bulletCenterX)) < 16)
			&& (abs(harambeY-(b[i].y+bulletCenterY)) < 26) && b[i].collide){
			drawRect(b[i].y-30, b[i].x, BULLETS_HEIGHT+100, BULLETS_WIDTH+100, BLACK);
			//this line is being stupid
			b[i].collide = 0;
			return 1;
		}
	}
	return 0;
}

//method to reset game state
//turns off hitboxes of bullets
void nullifyBullets() {
	for (int i=0; i < MAX_BULLET; i++) {
		b[i].collide = 0;
		drawRect(b[i].y, b[i].x, 4, BULLETS_WIDTH, BLACK);
	}
}

// int redrawScore(int prevX, int prevY, int lives) {
// 	if (detectCollision(prevX, prevY)) {
// 		lives -= 1;
// 	}
// 	drawRect(4, 180, 50, 100, BLACK);
// 	drawChar(4, 220, lives+48, GREEN);
// 	drawString(4, 180, "LIVES: ", GREEN);
// 	return lives;
// }
