#pragma once
#include "LTexture.h"

#define RUN 0 
#define JUMP 1
#define FALL 2

class Character
{
public:
	static const int JUMP_SPEED = 10;
	static const int FALL_SPEED = 1;
	Character();

	bool OnGround();

	void HandleEvent(SDL_Event& e, Mix_Chunk* gJump,Mix_Chunk* gTele);

	void Move();

	void Render(SDL_Rect* currentClip, SDL_Renderer* gRenderer, LTexture gCharacterTexture);

	void DrawTextShift(LTexture gTextTexture,SDL_Color textColor,SDL_Renderer* gRenderer,TTF_Font* gFont,const string& path);

	int GetPosX();

	int GetPosY();

	int GetStatus();
	bool check_collision_clips(SDL_Rect Threat, SDL_Rect Threat1, SDL_Rect Threat2, SDL_Rect* clips_threat, SDL_Rect* clips_threat1, SDL_Rect* clips_threat2, SDL_Rect* currentClips_character);
	bool check_collision(SDL_Rect& threat, SDL_Rect* currentClips_character);
	bool GetcEvent();
	bool GetcEvent1();
	static Uint32 TimerCallback(Uint32 interval, void* param);
private:
	int posX, posY;
	int status;
	int jumpStartTime;

	bool cEvent,cEvent1,isFalling;

	Uint32 lastShiftTime;
};