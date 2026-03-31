 /*
 * gCanvas.h
 *
 *  Created on: May 6, 2020
 *      Author: noyan
 */

#ifndef GCANVAS_H_
#define GCANVAS_H_

#include "gBaseCanvas.h"
#include "gApp.h"
#include "gImage.h"
#include "gFont.h"


class gCanvas : public gBaseCanvas {
public:
	gCanvas(gApp* root);
	virtual ~gCanvas();

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void charPressed(unsigned int codepoint);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseScrolled(int x, int y);
	void mouseEntered();
	void mouseExited();
	void windowResized(int w, int h);

	void showNotify();
	void hideNotify();



private:
	static const int KEY_NONE = 0, KEY_W = 1, KEY_S = 2, KEY_D = 4, KEY_A = 8;
	static const int trackframenum = 2;

	void moveCharacter();
	void moveCamera();
	void drawCharacter();
	void drawMap();
	void trackAnimation();
	void playAnimations();
	void moveBullets();
	void drawBullets();
	void generateBullet(float bulletX, float bulletY, float bulletDx, float bulletDy, float bulletRotation, int bulletSender);

	gApp* root;

	gImage map;
	gImage tank1;
	gImage track[trackframenum];
	gImage gun;
	gImage bulletimage;

	gFont namefont;

	//tank
	float cx, cy;
	int cw, ch;
	int cwh, chh;
	float cdx, cdy;
	float cspeed;

	float cangle;
	float cangletr;
	float canglegun;

	int keystate;

	float camx, camy;
	float camw, camh;
	float camleftlimit, camrightlimit, camtoplimit, cambottomlimit;

	int mapw, maph;

	//track
	float tx, ty;
	int tw, th;
	int twh, thh;
	float tdx, tdy;
	int trackframeno;
	int trackframecounter, trackframecounterlimit;

	//gun
	float gx, gy;
	int gw, gh;
	int gwh, ghh;
	float gdx, gdy;


	std::vector<std::vector<float>> bullets;
	float muzzleangle, muzzledistance;

	int fontx, fonty;
	std::string name;
};

#endif /* GCANVAS_H_ */
