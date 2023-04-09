#pragma once
#include "LTexture.h"

#define RUN 0 
#define JUMP 1
#define LEFT 2
#define RIGHT 3 
#define FALL 4

class Character
{
public:
	static const int JUMP_SPEED = 10;
	static const int FALL_SPEED = 1;
	
	static const int LSHIFT_COOLDOWN = 10000; // 10 seconds
	static const int LSHIFT_DURATION = 2000; // 2 seconds
	Character();

	bool OnGround();

	void HandleEvent(SDL_Event& e, Mix_Chunk* gJump,Mix_Chunk* gTele);

	void Move();

	void Render(SDL_Rect* currentClip, SDL_Renderer* gRenderer, LTexture gCharacterTexture);

	int GetPosX();

	int GetPosY();

	int GetStatus();
	bool check_collision_clips(SDL_Rect Threat, SDL_Rect Threat1, SDL_Rect Threat2, SDL_Rect* clips_threat, SDL_Rect* clips_threat1, SDL_Rect* clips_threat2, SDL_Rect* currentClips_character);
	bool check_collision(SDL_Rect& threat, SDL_Rect* currentClips_character);
	bool GetcEvent();
	bool GetcEvent1();

private:
	int posX, posY;

	int status;
	int jumpStartTime;
	int jumpDuration; 
	int shiftCoolDown, lastShiftTime;

	bool cEvent,cEvent1,isFalling;

	Uint32 lastLShiftTime;
	Uint32 lshiftCooldownStart;
};