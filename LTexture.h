#pragma once
#include"Game_Base.h"
#include<string>
class LTexture {
public:
	LTexture();
	~LTexture();
	void Free();
	bool LoadFromFileTTF(string textureText, TTF_Font* gFont, SDL_Color textColor, SDL_Renderer* gRenderer);
	bool LoadFromFile(std::string path, SDL_Renderer* gRenderer);
	void Render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip = nullptr);
	int getWidth();
	int getHeight();
private: 
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
};