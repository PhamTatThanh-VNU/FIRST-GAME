#include "Button.h"

Button::Button() {
	position.x = 0;
	position.y = 0;
}
Button::Button(int x, int y) {
	position.x = x;
	position.y = y;
}

void Button::SetPosition(int x, int y) {
	position.x = x;
	position.y = y;
}
bool Button::IsSelected(SDL_Event * ev,Mix_Chunk* gClick,Mix_Chunk* gButton) {
        if (ev->type == SDL_KEYDOWN && (ev->key.keysym.sym == SDLK_UP || ev->key.keysym.sym == SDLK_DOWN || ev->key.keysym.sym == SDLK_SPACE)) {
            if (ev->key.keysym.sym == SDLK_UP) {
                Mix_PlayChannel(MIX_CHANNEL, gButton, NOT_REPEATITIVE);          
                if (currentSprite <= 0) {
                    currentSprite = BUTTON_TOTAL;
                }
                currentSprite = static_cast<ButtonSprite>((currentSprite - 1) % BUTTON_TOTAL);
            }
            if (ev->key.keysym.sym == SDLK_DOWN) {
                Mix_PlayChannel(MIX_CHANNEL, gButton, NOT_REPEATITIVE);
                    currentSprite = static_cast<ButtonSprite>((currentSprite + 1) % BUTTON_TOTAL);
            }
            if (ev->key.keysym.sym == SDLK_SPACE) {
                Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
                return true;
            }
           
        }
	return false;
}
void Button::Render(SDL_Rect* currentClip, SDL_Renderer* gRenderer, LTexture gButtonTexture) {
    gButtonTexture.Render(position.x, position.y, gRenderer, currentClip);
}
