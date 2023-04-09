#pragma once

#include<SDL.h>
#include<iostream>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<sstream>
#include<fstream>
#include<string>
#include<vector>
#include<ctime> 

using namespace std; 


const int SCREEN_WIDTH = 928;
const int SCREEN_HEIGHT = 522;

#define SDL_ERROR 1
#define IMG_ERROR 2
#define MIX_ERROR 3
#define TTF_ERROR 4

#define MIX_CHANNEL -1

#define TIME_MAX 1000
#define GROUND 350
#define MAX_HEIGHT 270

#define BASE_OFFSET_SPEED 0

#define SPEED_INCREASEMENT 2
#define SCORE_INCREASEMENT 1
#define TIME_INCREASEMENT 1
#define FRAME_INCREASEMENT 1

#define GROUND_SPEED 4
#define ENEMY_SPEED 5
#define MAX_ENEMY_WIDTH 100

#define IN_AIR_ENEMY 1
#define ON_GROUND_ENEMY 0

#define SLOW_FRAME_CHAR 6
#define SLOW_FRAME_ENEMY 4
#define SLOW_FRAME_DOG 10
#define SLOW_FRAME_OBS 12

#define IS_REPEATITIVE -1
#define NOT_REPEATITIVE 0


const string WINDOW_TITLE = "CITY HUNTER RUNNING";

const int PLAY_BUTTON_POSX = 350;
const int PLAY_BUTTON_POSY = 190;
const int TT_BUTTON_POSX = 350;
const int TT_BUTTON_POSY = 280;
const int EXIT_BUTTON_POSX = 350;
const int EXIT_BUTTON_POSY = 370;
const int TEXT_1_POSX = 630;
const int TEXT_1_POSY = 20;
const int TEXT_2_POSX = 630;
const int TEXT_2_POSY = 65;
const int SCORE_POSX = 810;
const int SCORE_POSY = 20;
const int HIGH_SCORE_POSX = 810;
const int HIGH_SCORE_POSY = 65;

const double LAYER_1_SPEED = 0;
const double LAYER_2_SPEED = 0.5;
const double LAYER_3_SPEED = 1;
const double LAYER_4_SPEED = 1.5;
const double LAYER_5_SPEED = 2;


const int RUNNING_FRAMES = 8;
const int JUMP_FRAMES = 7;
const int BACKGROUND_LAYER = 5;

enum ButtonSprite {
	BUTTON_SELECTED = 1,
	BUTTON_SELECTED_2 = 2,
	BUTTON_SELECTED_3 = 3,
	BUTTON_TOTAL = 4,
	
};

void GetError(std::string er, int errorCode = SDL_ERROR);