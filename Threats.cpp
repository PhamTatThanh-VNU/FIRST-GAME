#include"AllHeaderFile.h"

const int posY = 435;
const int posX = SCREEN_WIDTH + 300; 

Threat::Threat()
{

    // Obstacle initial position
    mPosX = SCREEN_WIDTH ;
    mPosY = posY - 70;
    mWidth = OBS_WIDTH;
    mHeight = OBS_HEIGHT;

    //Fly obstacle initial position
    
    fPosX = SCREEN_WIDTH + 500;
    fPosY = posY - 180;
    fWidth = FLY_OBS_WIDTH;
    fHeight = FLY_OBS_HEIGHT;

    // Dog initial position
    dPosX = SCREEN_WIDTH + 10000;
    dPosY = posY - 50;

    // Rocket initial position
    rPosX = - 5000;
    rPosY = posY;
    rWidth = ROCKET_1_WIDTH;
    rHeight = ROCKET_1_HEIGHT;
}

void Threat::render_Obstacles(SDL_Rect* currentClip, SDL_Renderer* gRenderer, LTexture gObstacle)
{
    gObstacle.Render(mPosX, mPosY, gRenderer,currentClip);
}

void Threat::render_Fly_Obstacles(SDL_Rect* currentClip, SDL_Renderer* gRenderer, LTexture Fly_gObstacle) {
    Fly_gObstacle.Render(fPosX, fPosY, gRenderer, currentClip);
}


void Threat::render_Dog(SDL_Rect* currentClip, SDL_Renderer* gRenderer, LTexture& gWarning, LTexture& gDog,Mix_Chunk* gSua)
{

    if (dPosX >= SCREEN_WIDTH && dPosX <= SCREEN_WIDTH + 500)
    {
        Mix_PlayChannel(MIX_CHANNEL, gSua, NOT_REPEATITIVE);
        gWarning.Render(SCREEN_WIDTH - 55, GROUND + 40, gRenderer);
    }
    gDog.Render(dPosX, dPosY, gRenderer,currentClip);
}

void Threat::render_rocket(LTexture& gRocket2, LTexture& gWarning, SDL_Renderer*& gRenderer,Mix_Chunk* gRocket)
{
    if (rPosX >= -500 && rPosX <= -ROCKET_1_WIDTH)
    {
        Mix_PlayChannel(MIX_CHANNEL, gRocket, NOT_REPEATITIVE);
        gWarning.Render(0, GROUND + 40, gRenderer);
    }
    gRocket2.Render(rPosX, rPosY, gRenderer);
}

void Threat::threat_move(int acceleration)
{
        // Move continuously
        mPosX -= RUN_DISTANCE + acceleration;
        fPosX -= RUN_DISTANCE + acceleration;
        dPosX -= 2 * RUN_DISTANCE + acceleration;
        rPosX += 2 * RUN_DISTANCE + acceleration;
        // When threat reaches the end of the screen
        if (fPosX + fWidth < 0)
        {
            do
            {
                fPosX = SCREEN_WIDTH + rand() % (SCREEN_WIDTH - FLY_OBS_WIDTH);
            } while (abs(fPosX - mPosX) < 400);
        }
        if (mPosX + mWidth < 0)
        {
            do
            {
                mPosX = SCREEN_WIDTH + rand() % (SCREEN_WIDTH - OBS_WIDTH);
            } while (abs(mPosX - fPosX) < 400);
        }
        if (rPosX - rWidth > SCREEN_WIDTH) rPosX = -7000 - (rand() % 10000 + 100);
        if (dPosX + ROCKET_1_WIDTH < 0) dPosX = SCREEN_WIDTH + 2000;
}


SDL_Rect Threat::get_rocket_dimension()
{
    SDL_Rect res;
    res.x = rPosX;
    res.y = rPosY;
    res.w = rWidth;
    res.h = rHeight;
    return res;
}

SDL_Rect Threat::get_Dog_dimension() {
    SDL_Rect res;
    res.x = dPosX;
    res.y = dPosY;
    return res; 
}

SDL_Rect Threat::get_OBS_dimension() {
    const int Trash_Pixel_posX = 30;
    SDL_Rect res;
    res.x = mPosX+Trash_Pixel_posX;
    res.y = mPosY;
    return res;
}

SDL_Rect Threat::get_FOBS_dimension() {
    SDL_Rect res;
    res.x = fPosX;
    res.y = fPosY;
    return res;
}
void Threat::gameOver()
{
    mPosX = mPosX;
    fPosX = fPosX;
    dPosX = dPosX;
    rPosX = rPosX;
}