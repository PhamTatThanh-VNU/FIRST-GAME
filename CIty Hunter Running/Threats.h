#pragma once
#include "LTexture.h"

#define OBS_WIDTH 131
#define OBS_HEIGHT 101

#define ROCKET_1_WIDTH 75
#define ROCKET_1_HEIGHT 45

#define ROCKET_2_WIDTH 93
#define ROCKET_2_HEIGHT 45

#define FLY_OBS_WIDTH 96
#define FLY_OBS_HEIGHT 96

#define ENEMY_MAX_HEIGHT 300
#define ENEMY_MIN_HEIGHT 330

#define ENEMY_POSITION_RANGE 250
#define ENEMY1_RANGE 100
#define ENEMY2_RANGE 350
#define ENEMY3_RANGE 500

#define RUN_DISTANCE 5
class Threat
{
public:
    Threat();

    void render_Obstacles(SDL_Rect* currentClip, SDL_Renderer* gRenderer, LTexture gObstacle);
    void render_Dog(SDL_Rect* currentClip, SDL_Renderer* gRenderer, LTexture& gWarning,LTexture& gDog,Mix_Chunk* gSua);
    void render_Fly_Obstacles(SDL_Rect* currentClip, SDL_Renderer* gRenderer, LTexture Fly_gObstacle);
    void render_rocket(LTexture& gRocket2, LTexture& gWarning, SDL_Renderer*& gRenderer,Mix_Chunk* gRocket);    


    void threat_move(int acceleration);
    void pause(SDL_Event e);

    SDL_Rect get_rocket_dimension();
    SDL_Rect get_Dog_dimension();
    SDL_Rect get_OBS_dimension();
    SDL_Rect get_FOBS_dimension();
    void reset();
    void gameOver();

private:
    bool is_pause;
    //Obstacle
    int mPosX, mPosY;
    int mWidth ,mHeight;
    //Fly obstacle
    int fPosX, fPosY;
    int fWidth, fHeight;
    //DOG
    int dPosX, dPosY;
    //Rocket 
    int rPosX, rPosY;
    int rWidth, rHeight;
};

