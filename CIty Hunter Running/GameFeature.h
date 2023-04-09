#pragma once

#include"Game_Base.h"
#include"Button.h"
#include "Character.h"
#include "Threats.h"

bool Init();
bool LoadMedia();
void Close();

void HandlePlayButton(SDL_Event* e,
    Button& PlayButton,
    bool& QuitMenu,
    bool& Play,Mix_Chunk* gClick,Mix_Chunk* gButton);
void HandleTTButton(SDL_Event* e,
    Button& TutorialsButton,
    LTexture gTutorialsTexture,
    SDL_Renderer* gRenderer,
    bool& Quit_Game,
    Mix_Chunk* gClick, Mix_Chunk* gButton);
void HandleExitButton(SDL_Event* e,
    Button& ExitButton,
    bool& Quit,
    Mix_Chunk* gClick, Mix_Chunk* gButton);
void RenderScrollingBackground(std::vector <double>& offsetSpeed,
    LTexture(&gBackgroundTexture)[BACKGROUND_LAYER],
    SDL_Renderer* gRenderer);
void ControlCharFrame(int& frame);
void RenderScrollingGround(int& speed,
    const int acceleration,
    LTexture gGroundTexture,
    SDL_Renderer* gRenderer);
int UpdateGameTimeAndScore(int& time,int& speed,int& score);
void DrawPlayerScore(LTexture gTextTexture,
    LTexture gScoreTexture,
    SDL_Color textColor,
    SDL_Renderer* gRenderer,
    TTF_Font* gFont,
    const int& score);

void DrawPlayerHighScore(LTexture gTextTexture,
    LTexture gHighScoreTexture,
    SDL_Color textColor,
    SDL_Renderer* gRenderer,
    TTF_Font* gFont,
    const std::string& HighScore);
void DrawEndGameSelection(LTexture gLoseTexture,
    SDL_Event* e,
    SDL_Renderer* gRenderer,
    bool& Play_Again); 