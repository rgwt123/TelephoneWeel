#include "Weel.h"

int main(int argc, char * argv[])  
{  
  
    Weel *weel=new Weel();
	
	weel->init("Tel",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_OPENGL);//SDL_WINDOW_SHOWN
	while(weel->Running())
	{
		weel->handleEvents();
		weel->update();
		weel->draw();
		SDL_Delay(6);
	}
	weel->clean();
	return 0;
}  