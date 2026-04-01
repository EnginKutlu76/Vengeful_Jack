/*
 * gApp.cpp
 *
 *  Created on: May 6, 2020
 *      Author: Noyan Culum
 */

#include "gApp.h"
#include "gCanvas.h"
#include "mainMenu.h"


gApp::gApp() {
}

gApp::gApp(int argc, char **argv) : gBaseApp(argc, argv) {
}

gApp::~gApp() {
}

void gApp::setup() {
	mainMenu* cnv = new mainMenu(this);
	//gCanvas* cnv = new gCanvas(this);
	appmanager->setCurrentCanvas(cnv);
}

void gApp::update() {
}
