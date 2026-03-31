/*
 * mainMenu.cpp
 *
 *  Created on: 13 Mar 2026
 *      Author: Engin Kutlu
 */

#include "mainMenu.h"
#include "gCanvas.h"

mainMenu::mainMenu(gApp* root) : gBaseCanvas(root) {
	this->root = root;
}

mainMenu::~mainMenu() {
}

void mainMenu::setup() {
	background.loadImage("PNG/black.png");
	menu.loadImage("PNG/gray.png");
	button1.loadImage("PNG/button.png");
	button2.loadImage("PNG/button.png");
	startfont.loadFont("FreeSans.ttf", 20);
	menuw = menu.getWidth();
	menuh = menu.getHeight();
	menux = (getWidth() - menuw) / 2;
	menuy = (getHeight() - menuh) / 2;

	bw = button1.getWidth();
	bh = button1.getHeight();
	bx = menux + (menuw - bw) / 2;
	by = menuy + menuh / 2;

	fontx = bx + (bw - startfont.getStringWidth("Start")) / 2;
	fonty = by - bh + (bh + startfont.getStringHeight("Start")) / 2;

	int button2y = by + 20;

	font1x = bx + (bw - startfont.getStringWidth("Options")) / 2;
	font1y = button2y + (bh / 2) + (startfont.getStringHeight("Options") / 2) - 2;

	menu.setScreenScaling(222);
}

void mainMenu::update() {
//	gLogi("menuCanvas") << "update";
}

void mainMenu::draw() {
	background.draw(0, 0, getWidth() * 1.4, getHeight() * 1.4);
	menu.draw(menux, menuy);

	button1.draw(bx, by - bh);
	button2.draw(bx, by + 20);

	setColor(0, 0, 0);
	startfont.drawText("Start", fontx, fonty);
	startfont.drawText("Options", font1x, font1y);
}

void mainMenu::keyPressed(int key) {
}

void mainMenu::keyReleased(int key) {
}

void mainMenu::charPressed(unsigned int codepoint) {
}

void mainMenu::mouseMoved(int x, int y) {
}

void mainMenu::mouseDragged(int x, int y, int button) {
}

void mainMenu::mousePressed(int x, int y, int button) {
}

void mainMenu::mouseReleased(int x, int y, int button) {
	int bx1 = bx;
	int by1 = menuy + menuh / 2 - bh;

	int bx2 = bx1 + bw;
	int by2 = by1 + bh;

	if(x >= bx1 && x <= bx2 && y >= by1 && y <= by2) {
	    gCanvas* cnv = new gCanvas(root);
	    root->setCurrentCanvas(cnv);
	    return;
	}
}

void mainMenu::mouseScrolled(int x, int y) {
}

void mainMenu::mouseEntered() {
}

void mainMenu::mouseExited() {
}

void mainMenu::windowResized(int w, int h) {
}

void mainMenu::showNotify() {
}

void mainMenu::hideNotify() {
}
