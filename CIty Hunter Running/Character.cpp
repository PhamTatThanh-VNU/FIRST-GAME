#include "Character.h"

//TRASH PIXEL 
const int TRASH_CHARACTER_RIGHT = 72;
const int TRASH_CHARACTER_TOP = 55;
const int TRASH_CHARACTER_LEFT = 80;
const int TRASH_OBS_LEFT = 30;
const int TRASH_OBS_RIGHT = 15;
const int TRASH_OBS_TOP = 56;
const int TRASH_DOG_LEFT = 25;
const int TRASH_DOG_RIGHT = 60;
const int TRASH_DOG_TOP = 55;
const int TRASH_FOBS_BOT = 39;
const int TRASH_FOBS_LEFT = 8;
const int TRASH_FOBS_RIGHT = 15;

Character::Character()
{
	posX = SCREEN_WIDTH - 750;
	posY = GROUND ;

	status = 0;
}

bool Character::OnGround()
{
	return posY == GROUND;
}

void Character::HandleEvent(SDL_Event& e, Mix_Chunk* gJump, Mix_Chunk* gTele)
{
	Uint32 currentTime = SDL_GetTicks();
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
		{
			if (!cEvent1 && (currentTime - jumpStartTime) >= 400) { 
				Mix_PlayChannel(MIX_CHANNEL, gJump, NOT_REPEATITIVE);
				status = JUMP;
				jumpStartTime = currentTime;
				cEvent1 = true;
			}
			break;
		}
		case SDLK_LSHIFT:
		{	
			Mix_PlayChannel(MIX_CHANNEL, gTele, NOT_REPEATITIVE);
			cEvent = true;
			break;
		}
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
		{
			if (status == JUMP) {
				status = RUN;
			}
			cEvent1 = false;
			break;
		}
		case SDLK_LSHIFT:
		{
			cEvent = false;
			break;
		}
		}
	}
}

void Character::Move()
{
	if (status == JUMP && posY >= MAX_HEIGHT )
	{
		posY += -JUMP_SPEED;
		Uint32 jumpDuration = SDL_GetTicks() - jumpStartTime;
		if (jumpDuration > 50) {
			isFalling = true;
			status = FALL;
		}
	}
	else if (posY < GROUND) {
		posY += FALL_SPEED;
	}
	else if (isFalling || posY < GROUND ) {
		posY += FALL_SPEED;
		if (posY >= GROUND) { //stop falling when reaching ground
			posY = GROUND;
			isFalling = false;
			status = RUN;
		}
	}
}



bool Character::check_collision_clips(SDL_Rect Threat,SDL_Rect Threat1,SDL_Rect Threat2 , SDL_Rect* clips_threat, SDL_Rect* clips_threat1, SDL_Rect* clips_threat2, SDL_Rect* currentClips_character)
{
	bool is_collide = true;
	// The sides of character
	int left_player = posX;
	int right_player = posX + currentClips_character->w ;
	int top_player = posY;
	int bottom_player = posY + currentClips_character->h;

	// The sides of OBS
	int left_threat = Threat.x;
	int right_threat = Threat.x + clips_threat->w;
	int top_threat = Threat.y;
	int bottom_threat = Threat.y + clips_threat->h;


	//The sides of DOG 
	int left_threat1 = Threat1.x;
	int right_threat1 = Threat1.x + clips_threat1->w;
	int top_threat1 = Threat1.y;
	int bottom_threat1 = Threat1.y + clips_threat1->h;

	//The sides of FOBS 
	int left_threat2 = Threat2.x;
	int right_threat2 = Threat2.x + clips_threat2->w;
	int top_threat2 = Threat2.y;
	int bottom_threat2 = Threat2.y + clips_threat2->h;

	// check collision OBS
	if (right_player - TRASH_CHARACTER_RIGHT >= left_threat && left_player + TRASH_CHARACTER_LEFT <= right_threat - TRASH_OBS_RIGHT)
	{
		if (bottom_player - TRASH_OBS_TOP >= top_threat + 20)
		{
			is_collide = false;
		}
	}
	if (right_player - TRASH_CHARACTER_RIGHT >= left_threat1 +TRASH_DOG_LEFT&& left_player + TRASH_CHARACTER_LEFT  <= right_threat1 - TRASH_DOG_RIGHT)
	{
		if (bottom_player - TRASH_DOG_TOP >= top_threat1 + 10)
		{
			is_collide = false;
		}
	}
	if (right_player - TRASH_CHARACTER_RIGHT >= left_threat2 && left_player + TRASH_CHARACTER_LEFT <= right_threat2 )
	{
		if (bottom_player<= bottom_threat2 )
		{
			is_collide = false;
		}
	}
	if (cEvent) is_collide = true; 
	return is_collide;
}

bool Character::check_collision(SDL_Rect& threat, SDL_Rect* currentClips_character) {
	bool is_collide = true;
	// The sides of character
	int left_player = posX;
	int right_player = posX + currentClips_character->w;
	int top_player = posY;
	int bottom_player = posY + currentClips_character->h;

	// The sides of threat
	int left_threat = threat.x;
	int right_threat = threat.x + threat.w;
	int top_threat = threat.y;
	int bottom_threat = threat.y + threat.h;

	// Condition when 2 objects collide
	if (bottom_player - 30 <= top_threat) is_collide = false;
	if (top_player >= bottom_threat) is_collide = false;
	if (right_player -TRASH_CHARACTER_RIGHT <= left_threat) is_collide = false;
	if (left_player + TRASH_CHARACTER_LEFT >= right_threat) is_collide = false;
	if (cEvent) is_collide = false;

	return is_collide;
}



void Character::Render(SDL_Rect* currentClip, SDL_Renderer* gRenderer, LTexture gCharacterTexture)
{
	gCharacterTexture.Render(posX, posY, gRenderer, currentClip);
}


int Character::GetPosX()
{
	return posX;
}

int Character::GetPosY()
{
	return posY;
}
int Character::GetStatus() {
	return status; 
}

bool Character::GetcEvent() {
	return cEvent;
}
bool Character::GetcEvent1() {
	return cEvent1; 
}