/*
 * mainMenu.h
 *
 *  Created on: 13 Mar 2026
 *      Author: Engin Kutlu
 */

#ifndef SRC_MAINMENU_H_
#define SRC_MAINMENU_H_

#include "gBaseCanvas.h"
#include "gApp.h"
#include "gFont.h"

class mainMenu: public gBaseCanvas {
public:
	mainMenu(gApp* root);
	virtual ~mainMenu();

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
	gApp* root;
	gImage background;
	gImage menu;
	gImage button1, button2;

	gFont startfont;

	int menux, menuy;
	int menuw, menuh;
	int bx, by;
	int bw, bh;

	int fontx, fonty;
	int font1x, font1y;
};
#endif /* SRC_MAINMENU_H_ */
