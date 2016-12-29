#include "Turner.h"


Turner::Turner(void)
{
	angle=0.0;
	center=new SDL_Point;
	center->x=150;
	center->y=150;
}


Turner::~Turner(void)
{
}

void Turner::draw(int x, int y, int width, int height, SDL_Renderer* pRenderer)
{
	
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	pTempSurface = IMG_Load("turner.png");



	pTexture =SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);
	SDL_RenderCopyEx(pRenderer, pTexture, &srcRect,&destRect,angle,center,SDL_FLIP_NONE);
	SDL_DestroyTexture(pTexture);

}