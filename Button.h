#pragma once

#include "LTexture.h"
#include "Game_Base.h"

class Button {
	public:
		ButtonSprite currentSprite; 
		Button();
		Button(int x, int y);
		void SetPosition(int x, int y);
		bool IsSelected(SDL_Event* e,Mix_Chunk* gClick,Mix_Chunk* gButton);
		void Render(SDL_Rect* currentClip, SDL_Renderer* gRenderer, LTexture gButtonTexture);
	private:
		SDL_Point position; 
		
};