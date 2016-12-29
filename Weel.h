#pragma once
#include "Turner.h"
#define PI 3.141592653589793

class Weel
{
public:
	Weel(void);
	~Weel(void);
	bool init(const char* title, int xpos, int ypos, int height, int width, int flags);
	void draw();
	void update();
	void handleEvents();
	bool Running()
	{
		return m_bRunning;
	}
	bool Moving()
	{
		return canMoving;
	}
	int getX(){return mymouseposition_x;}
	int getY(){return mymouseposition_y;}
	void clean();
	int judAngle();
	void rollback();
	int Sound_Init()  
	{  
		const int    TMP_FREQ = MIX_DEFAULT_FREQUENCY;  
		const Uint16 TMP_FORMAT = MIX_DEFAULT_FORMAT;  
		const int    TMP_CHAN = 2;  
		const int    TMP_CHUNK_SIZE = 512;  
		return Mix_OpenAudio(TMP_FREQ,TMP_FORMAT,TMP_CHAN,TMP_CHUNK_SIZE);  
	}  
	Mix_Music * getMixmusic(){return mix_music;}
	int IsInCircle();
	int getangle(){return angle;}
private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;
	bool canMoving;
	SDL_Rect srcRect;
	SDL_Rect destRect,destTextRect;
	int mymouseposition_x,mymouseposition_y;
	SDL_Texture *pTexture,*pTextTexture;
	SDL_Surface* pTempSurface,*pTextSurface;
	SDL_Event event;
	Turner *turner;
	int angle,firstangle,temp;
	int circlex,circley,circler;
	Mix_Music *mix_music;  
	SDL_Point Point[10];
	TTF_Font *font; 
	string num;
	SDL_Color color;
};

int PlaySound(void *data);