#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include <SDL_thread.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include<iostream>
#include<string>
using namespace std;
class Turner
{
public:
	Turner(void);
	~Turner(void);
	void draw(int x, int y, int width, int height, SDL_Renderer* pRenderer);
	void clean();
	void setangle(int angle1){angle=angle1;}
	int getangle(){return angle;}
private:
	bool state;//true为静止，可接受事件，false为运动，不接受命令
	SDL_Rect srcRect;
	SDL_Rect destRect;
	SDL_Surface* pTempSurface;
	SDL_Texture* pTexture;
	SDL_Point *center;
	int angle;
};

