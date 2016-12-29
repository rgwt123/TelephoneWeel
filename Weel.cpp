#include "Weel.h"
#include <math.h>


Weel::Weel(void)
{
	turner=new Turner();
	circlex=250;
	circley=300;
	circler=20;
	Point[0].x=322;Point[1].x=335;Point[2].x=285;Point[3].x=230;Point[4].x=176;Point[5].x=137;
	Point[6].x=135;Point[7].x=162;Point[8].x=210;Point[9].x=269;
	Point[0].y=386;Point[1].y=220;Point[2].y=187;Point[3].y=182;Point[4].y=209;Point[5].y=260;
	Point[6].y=322;Point[7].y=376;Point[8].y=407;Point[9].y=411;
	color.r=color.g=color.b=0;

	//num setting with ttf
	destTextRect.x=destTextRect.y=0;
	destTextRect.w=0;
	destTextRect.h=30;

	//the bg setting
	srcRect.x=destRect.x=0;
	srcRect.y=destRect.y=0;
	srcRect.w=destRect.w=500;
	srcRect.h=destRect.h=500;
}


Weel::~Weel(void)
{
}

int Weel::judAngle()//calculate angle with the mousepos now
{
	double temp;
	if(mymouseposition_x==circlex)
	{
		if(mymouseposition_y>=circley)
			angle=90;
		else
			angle=270;
	}

	else
	{
		temp=atan((double)((double)(mymouseposition_y-circley)/(double)(mymouseposition_x-circlex)));
		if(mymouseposition_x>circlex)
		{
			if(temp>0)
				angle=(int)(temp/(2*PI)*360);
			else
				angle=360+(int)(temp/(2*PI)*360);
		}
		else
		{
			if(temp>0)
				angle=180+(int)(temp/(2*PI)*360);
			else
				angle=180+(int)(temp/(2*PI)*360);
		}
	}
	return angle;
}

int Weel::IsInCircle()//judge if in circle
{
	int i;
	
	for(i=0;i<10;i++)
	{
		int temp=(mymouseposition_x-Point[i].x)*(mymouseposition_x-Point[i].x)+(mymouseposition_y-Point[i].y)*(mymouseposition_y-Point[i].y);
		if(temp<=circler*circler)
			return i+1;//if in numcircle,return num+1
	}
	return 0;//not in num,return 0
}

bool Weel::init(const char* title, int xpos, int ypos, int height, int width, int flags)
{
	// attempt to initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL init success\n";
		// init the window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos,width, height, flags);
		if(m_pWindow != 0) // window init success
		{
			std::cout << "window creation success\n";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if(m_pRenderer != 0) // renderer init success
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(m_pRenderer,180,180,180,255);//the green color
			}
			else
			{
				std::cout << "renderer init fail\n";
				return false; // renderer init fail
			}

			//TTF init
			if( TTF_Init() == -1 )  
				return false;  
			//open font
			font=TTF_OpenFont("basic.ttf", 36);  
			if(!font)  
			{   
				printf("TTF_OpenFont: Open basic.ttf %s\n", TTF_GetError());  
				return false;   
			} 
		}
		else
		{
			std::cout << "window init fail\n";
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false; // SDL init fail
	}
	
	pTempSurface = IMG_Load("bg.png");
	pTexture =SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);
	

	std::cout << "init success\n";
	m_bRunning = true; // everything inited successfully,start the main loop
	canMoving=false;
	angle=0;
	Sound_Init();
	mix_music = Mix_LoadMUS("1.wav");

	//create a thread to play sound when angle is changing
	SDL_Thread *thread;
	thread = SDL_CreateThread(PlaySound, "PlaySound", this);
	if( NULL == thread )
        printf("SDL_CreateThread failed: %s", SDL_GetError());

	return true;
}

void Weel::rollback()//after output the number,rollback the turner at a fixed speed
{
	if(angle>0)
	{
		angle-=2;
		turner->setangle(angle);
	}
	else if(angle<0)
	{
		angle+=1;
		turner->setangle(angle);
	}
}
void Weel::update()
{
	if(Moving()&&judAngle()<=350)
	{
		angle=judAngle()-firstangle;
		if(angle>=0)
		{
			turner->setangle(angle);
		}
		else
		{
			canMoving=false;
			angle=0;
			turner->setangle(angle);
		}
	}
	else if(Moving()&&judAngle()>350)
	{
		angle=judAngle()-firstangle;
		canMoving=false;
		printf("the output number is  %d\n",temp-1);
		string tempstring=to_string(temp-1);
		num+=tempstring;
		destTextRect.w+=20;
		if(num.length()>11)
		{
			num.clear();
			destTextRect.w=0;
		}
	}
	else
	{	
		rollback();
	}
}

void Weel::handleEvents()
{
	
	if(SDL_PollEvent(&event))//SDL_PollEvent
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;

		case SDL_KEYDOWN:
			if(event.key.keysym.sym==SDLK_ESCAPE)
				m_bRunning = false;
			break;

		case SDL_MOUSEBUTTONDOWN:
			if(event.button.button == SDL_BUTTON_LEFT)
			{
				mymouseposition_x=(int)event.motion.x;
				mymouseposition_y=(int)event.motion.y;
				if((temp=IsInCircle())!=0)
				{
					firstangle=judAngle();
					//printf("pos is %d\t%d\n",mymouseposition_x,mymouseposition_y);
					canMoving=true;
				}
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if(event.button.button == SDL_BUTTON_LEFT)
			{
				canMoving=false;
			}
			break;
		case SDL_MOUSEMOTION:
			if (event.motion.state)
			{
				mymouseposition_x=(int)event.motion.x;
				mymouseposition_y=(int)event.motion.y;
            }
			
			break;
		default:
			break;
		}
	}
}

void Weel::draw()
{
	SDL_RenderClear(m_pRenderer);
	pTextSurface = TTF_RenderText_Blended(font,num.c_str(),color);
	pTextTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTextSurface);  
	SDL_RenderCopy(m_pRenderer, pTexture, &srcRect,&destRect);
	SDL_RenderCopy(m_pRenderer, pTextTexture, NULL,&destTextRect);
	SDL_DestroyTexture(pTextTexture);
	SDL_FreeSurface(pTextSurface);
	turner->draw(100,150,300,300,m_pRenderer);
	SDL_RenderPresent(m_pRenderer);
}


void Weel::clean()
{
	std::cout << "cleaning it\n";
	Mix_FreeMusic(mix_music);
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

int PlaySound(void *data)
{
	Weel *weel=(Weel*)data;
	int tempangle=weel->getangle();
	Mix_PlayMusic(weel->getMixmusic(),-1);
	while(weel->Running())
	{
		
		if(tempangle!=weel->getangle())
		{
			Mix_VolumeMusic(10);
		}
		else
		{
			Mix_VolumeMusic(0);
		}
		tempangle=weel->getangle();
		SDL_Delay(25);
		}
	return 1;
}