#include "Game_Base.h"
void GetError(string er, int errorCode) {
	if (errorCode == SDL_ERROR) {
		cout << er << SDL_GetError() << endl;
	}
	if (errorCode == IMG_ERROR) {
		cout << er << IMG_GetError() << endl;
	}
	if (errorCode == MIX_ERROR) {
		cout << er << Mix_GetError() << endl;
	}
	if (errorCode == TTF_ERROR) {
		cout << er << TTF_GetError() << endl;
	}
}