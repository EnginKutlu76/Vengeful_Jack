/*
* gCanvas.cpp
*
*  Created on: May 6, 2020
*      Author: noyan
*/


#include "gCanvas.h"


gCanvas::gCanvas(gApp* root) : gBaseCanvas(root) {
	this->root = root;
}

gCanvas::~gCanvas() {
}

void gCanvas::setup() {
	map.loadImage("haritalar/arkaplan1.jpg");
	tank1.loadImage("oyun/PNG/Hulls_Color_A/Hull_01.png");
	for(int i = 0; i < trackframenum; i++) {
		track[i].loadImage("oyun/PNG/Tracks/Track_1_" + gToStr(i) + ".png");
	}
	gun.loadImage("oyun/PNG/Weapon_Color_A/Gun_01.png");
	bulletimage.loadImage("oyun/PNG/Effects/Exhaust_Fire.png");

	namefont.loadFont("FreeSans.ttf", 20);

	keystate = KEY_NONE;
	cx = 0;
	cy = 0;
	cw = tank1.getWidth() * 0.4;
	ch = tank1.getHeight() * 0.4;
	cwh = cw / 2;
	chh = ch / 2;
	cdx = 0.0f;
	cdy = 0.0f;
	cangle = 0.0f;
	cangletr = 0.0f;
	canglegun = 0.0f;
	cspeed = 4.0f;

	tx = 0;
	ty = 0;
	tw = track[0].getWidth() * 0.4;
	th = track[0].getHeight() * 0.4;
	twh = tw / 2;
	thh = th / 2;
	tdx = 0.0f;
	tdy = 0.0f;

	gx = 0;
	gy = 0;
	gw = gun.getWidth() * 0.4;
	gh = gun.getHeight() * 0.4;
	gwh = gw / 2;
	ghh = gh / 2;
	gdx = 0.0f;
	gdy = 0.0f;

	camx = 0.0f;
	camy = 0.0f;
	camw = getWidth();
	camh = getHeight();
	camleftlimit = (float)getWidth() / 4.0f;
	camrightlimit = (float)getScreenWidth() * 3.0f / 4.0f;
	camtoplimit = (float)getHeight() / 4.0f;
	cambottomlimit = (float)getHeight() * 3.0f / 4.0f;
	mapw = map.getWidth();
	maph = map.getHeight();
	trackframecounter = 0;
	trackframeno = 0;
	trackframecounterlimit = 2;

	fontx = cwh;
	fonty = chh;
}

void gCanvas::update() {
	moveCharacter();
	moveCamera();
	playAnimations();
	moveBullets();
}

void gCanvas::drawCharacter() {
	float pivotoffset = ch * 0.6f;

	track[trackframeno].draw(cx + 15, cy, tw, th, cwh - 15, pivotoffset, cangle);
	track[trackframeno].draw(cx + 70, cy, tw, th, cwh - 70, pivotoffset, cangle);

	tank1.draw(cx, cy, cw, ch, cwh, pivotoffset, cangle);

	gun.draw(cx + 40, cy, gw, gh, gwh, gh * 0.85f, canglegun);
}

void gCanvas::draw() {
	drawMap();
	drawBullets();
	drawCharacter();
	setColor(255, 255, 255);
	namefont.drawText("Name", cx + cwh, cy + chh);
}

void gCanvas::moveCharacter() {
    cdx = 0.0f;
    cdy = 0.0f;

    if(keystate & KEY_A) {
        cangle -= 2.0f;
    }
    if(keystate & KEY_D) {
        cangle += 2.0f;
    }

    if(keystate & KEY_W) {
        cdx = std::sin(gDegToRad(cangle)) * cspeed;
        cdy = -std::cos(gDegToRad(cangle)) * cspeed;
    }
    if(keystate & KEY_S) {
        cdx = -std::sin(gDegToRad(cangle)) * cspeed;
        cdy = std::cos(gDegToRad(cangle)) * cspeed;
    }

    cx += cdx;
    cy += cdy;
}
void gCanvas::playAnimations() {
    if(cdx != 0.0f || cdy != 0.0f) {
        trackframecounter++;
        if(trackframecounter >= trackframecounterlimit) {
            trackframeno = (trackframeno + 1) % trackframenum;
            trackframecounter = 0;
        }
    }
}

void gCanvas::moveCamera() {
	camleftlimit = (float)getWidth() / 4.0f;
	if(camx <= 0.0f) camleftlimit = 0.0f;
	camrightlimit = (float)getWidth() * 3.0f / 4.0f;
	if(camx + camw >= mapw) camrightlimit = getWidth();
	if(cx < camleftlimit || cx + cw > camrightlimit) {
		cx -= cdx;
		camx += cdx;
		if(camx < 0.0f) {
			camx = 0.0f;
		}
		if(camx + camw > mapw) {
			camx = mapw - camw;
		}
	}

	camtoplimit = (float)getHeight() / 4.0f;
	if(camy <= 0.0f) camtoplimit = 0.0f;
	cambottomlimit = (float)getHeight() * 3.0f / 4.0f;
	if(camy + camh >= maph) cambottomlimit = getHeight();
	if(cy < camtoplimit || cy + ch > cambottomlimit) {
		cy -= cdy;
		camy += cdy;
		if(camy < 0.0f) {
			camy = 0.0f;
		}
		if(camy + camh > maph) {
			camy = maph - camh;
		}
	}
}

void gCanvas::drawMap() {
	map.drawSub(0, 0, getWidth(), getHeight(), camx, camy, camw, camh);
}

void gCanvas::moveBullets() {
    for(int i = bullets.size() - 1; i >= 0; i--) {
        bullets[i][0] += bullets[i][2];
        bullets[i][1] += bullets[i][3];
        if(bullets[i][0] < camx + 3 || bullets[i][0] >= camx + camw + 3 ||
           bullets[i][1] < camy + 3 || bullets[i][1] >= camy + camh + 3) {
            bullets.erase(bullets.begin() + i);
            continue;
        }

        float bx = bullets[i][0];
        float by = bullets[i][1];
        float bx2 = bx + bulletimage.getWidth();
        float by2 = by + bulletimage.getHeight();
     }
}

void gCanvas::drawBullets() {
	for(int i = 0; i < bullets.size(); i++) {
		bulletimage.draw(bullets[i][0] - camx, bullets[i][1] - camy, bulletimage.getWidth(), bulletimage.getHeight()/*, bulletimage.getWidth() / 2, bulletimage.getHeight() / 2*/, bullets[i][4]);
	}
}
void
gCanvas::generateBullet(float bulletX, float bulletY, float bulletDx, float bulletDy, float bulletRotation, int bulletSender) {
	std::vector<float> newbullet;
	newbullet.push_back(bulletX);
	newbullet.push_back(bulletY);
	newbullet.push_back(bulletDx);
	newbullet.push_back(bulletDy);
	newbullet.push_back(bulletRotation);
	newbullet.push_back((float)bulletSender);
	bullets.push_back(newbullet);
}

void gCanvas::keyPressed(int key) {
//	gLogi("gCanvas") << "keyPressed:" << key;
	int pressedkey = KEY_NONE;
	switch(key) {
		case G_KEY_W:
			pressedkey = KEY_W;
			break;
		case G_KEY_S:
			pressedkey = KEY_S;
			break;
		case G_KEY_D:
			pressedkey = KEY_D;
			break;
		case G_KEY_A:
			pressedkey = KEY_A;
			break;
		default:
			break;
	}
	keystate |= pressedkey;
}

void gCanvas::keyReleased(int key) {
//	gLogi("gCanvas") << "keyReleased:" << key;
	int pressedkey;
	switch(key) {
		case G_KEY_W:
			pressedkey = KEY_W;
			break;
		case G_KEY_S:
			pressedkey = KEY_S;
			break;
		case G_KEY_D:
			pressedkey = KEY_D;
			break;
		case G_KEY_A:
			pressedkey = KEY_A;
			break;
		default:
			break;
	}
	keystate &= ~pressedkey;
}

void gCanvas::charPressed(unsigned int codepoint) {
//	gLogi("gCanvas") << "charPressed:" << gCodepointToStr(codepoint);
}

void gCanvas::mouseMoved(int x, int y) {
    canglegun = (int)(
        gRadToDeg(
            std::atan2(
                y - (cy + chh),
                x - (cx + cwh)
            )
        ) + 90.0f + 360.0f
    ) % 360;
}

void gCanvas::mouseDragged(int x, int y, int button) {
//	gLogi("gCanvas") << "mouseDragged" << ", x:" << x << ", y:" << y << ", b:" << button;
}

void gCanvas::mousePressed(int x, int y, int button) {
//	gLogi("gCanvas") << "mousePressed" << ", x:" << x << ", y:" << y << ", b:" << button;
}

void gCanvas::mouseReleased(int x, int y, int button) {
//	gLogi("gCanvas") << "mouseReleased" << ", button:" << button;
	float px = (cx + 40) + camx + gwh;
	float py = cy + camy + gh * 0.85;
	float br = canglegun;
	float bx = px + std::sin(gDegToRad(br + muzzleangle)) * muzzledistance - bulletimage.getHeight() / 2;
	float by = py - std::cos(gDegToRad(br + muzzleangle)) * muzzledistance - bulletimage.getWidth() / 2;
	float bdx = std::sin(gDegToRad(br)) * 8.0f;
	float bdy = -std::cos(gDegToRad(br)) * 8.0f;
	int bs = 0; //0:character, 1:enemy
	generateBullet(bx, by, bdx, bdy, br, bs);

}

void gCanvas::mouseScrolled(int x, int y) {
//	gLogi("gCanvas") << "mouseScrolled" << ", x:" << x << ", y:" << y;
}

void gCanvas::mouseEntered() {

}

void gCanvas::mouseExited() {

}

void gCanvas::windowResized(int w, int h) {

}

void gCanvas::showNotify() {

}

void gCanvas::hideNotify() {

}

