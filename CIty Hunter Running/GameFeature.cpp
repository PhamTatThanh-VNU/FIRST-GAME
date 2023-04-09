#include"GameFeature.h"

void HandlePlayButton(SDL_Event* e,
	Button& PlayButton,
	bool& QuitMenu,
	bool& Play,Mix_Chunk* gClick,Mix_Chunk* gButton) {

	if (e->type == SDL_QUIT) {	
		QuitMenu = true;
	}

	if (PlayButton.IsSelected(e,gClick,gButton)) {
		if (PlayButton.currentSprite == BUTTON_SELECTED) {
			Play = true;
			QuitMenu = true;
		}
	}
}
void HandleTTButton(SDL_Event* e,
	Button& TutorialsButton,
	LTexture gTutorialsTexture,
	SDL_Renderer* gRenderer,
	bool& Quit_Game,
	Mix_Chunk* gClick, Mix_Chunk* gButton)
{
	if (TutorialsButton.IsSelected(e, gClick, gButton)) {
		if (TutorialsButton.currentSprite == BUTTON_SELECTED_2) {
			bool ReadDone = false;
			while (!ReadDone) {
				do {
					if (e->type == SDL_QUIT) {
						ReadDone = true;
						Quit_Game = true;
					}
					else if (e->type == SDL_KEYDOWN && (e->key.keysym.sym == SDLK_TAB)) {
						ReadDone = true;
						Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
					}
					gTutorialsTexture.Render(0, 0, gRenderer);
					SDL_RenderPresent(gRenderer);
				} while (SDL_PollEvent(e) != 0 && e->type == SDL_KEYDOWN && (e->key.keysym.sym == SDLK_TAB));
			}
		}
	}
}

void HandleExitButton(SDL_Event* e,
	Button& ExitButton,
	bool& Quit,
	Mix_Chunk* gClick,Mix_Chunk* gButton)
{
	if (ExitButton.IsSelected(e,gClick,gButton)) {
		if (ExitButton.currentSprite == BUTTON_SELECTED_3) {
			Quit = true;
		}
	}
}
int UpdateGameTimeAndScore(int& time,
	int& speed,
	int& score)
{
	if (time == TIME_MAX)
	{
		speed += SPEED_INCREASEMENT;
	}

	if (time > TIME_MAX)
	{
		time = 0;
	}
	if (time % 5 == 0)
	{
		score += SCORE_INCREASEMENT;
	}

	time += TIME_INCREASEMENT;

	return time;
}


void RenderScrollingBackground(std::vector <double>& offsetSpeed,
	LTexture(&gBackgroundTexture)[BACKGROUND_LAYER],
	SDL_Renderer* gRenderer)
{
	std::vector <double> layer_speed;
	layer_speed.push_back(LAYER_1_SPEED);
	layer_speed.push_back(LAYER_2_SPEED);
	layer_speed.push_back(LAYER_3_SPEED);
	layer_speed.push_back(LAYER_4_SPEED);
	layer_speed.push_back(LAYER_5_SPEED);
	for (int i = 0; i < BACKGROUND_LAYER; ++i)
	{
		offsetSpeed[i] -= layer_speed[i];
		if (offsetSpeed[i] < -gBackgroundTexture[i].getWidth())
		{
			offsetSpeed[i] = 0;
		}
		gBackgroundTexture[i].Render(offsetSpeed[i], 0, gRenderer);
		gBackgroundTexture[i].Render(offsetSpeed[i] + gBackgroundTexture[i].getWidth(), 0, gRenderer);
	}
}
void RenderScrollingGround(int& speed,
	const int acceleration,
	LTexture gGroundTexture,
	SDL_Renderer* gRenderer)
{
	speed -= GROUND_SPEED + acceleration;
	if (speed < -gGroundTexture.getWidth())
	{
		speed = 0;
	}
	gGroundTexture.Render(speed, 0, gRenderer);
	gGroundTexture.Render(speed + gGroundTexture.getWidth(), 0, gRenderer);
}


void DrawPlayerScore(LTexture gTextTexture,
	LTexture gScoreTexture,
	SDL_Color textColor,
	SDL_Renderer* gRenderer,
	TTF_Font* gFont,
	const int& score)
{
	gTextTexture.Render(TEXT_1_POSX, TEXT_1_POSY, gRenderer);
	if (gScoreTexture.LoadFromFileTTF(to_string(score), gFont, textColor, gRenderer))
	{
		gScoreTexture.Render(SCORE_POSX, SCORE_POSY, gRenderer);
	}
}
void DrawPlayerHighScore(LTexture gTextTexture,
	LTexture gHighScoreTexture,
	SDL_Color textColor,
	SDL_Renderer* gRenderer,
	TTF_Font* gFont,
	const std::string& HighScore) {
	gTextTexture.Render(TEXT_2_POSX, TEXT_2_POSY, gRenderer);
	if (gHighScoreTexture.LoadFromFileTTF(HighScore, gFont, textColor, gRenderer))
	{
		gHighScoreTexture.Render(HIGH_SCORE_POSX, HIGH_SCORE_POSY, gRenderer);
	}
}
void DrawEndGameSelection(LTexture gLoseTexture,
	SDL_Event* e,
	SDL_Renderer* gRenderer,
	bool& Play_Again)
{
	if (Play_Again)
	{
		bool End_Game = false;
		while (!End_Game)
		{
			while (SDL_PollEvent(e) != 0)
			{
				if (e->type == SDL_QUIT)
				{
					Play_Again = false;
				}

				if (e->type == SDL_KEYDOWN)
				{
					switch (e->key.keysym.sym)
					{
					case SDLK_SPACE:
						End_Game = true;
						break;
					case SDLK_ESCAPE:
						End_Game = true;
						Play_Again = false;
						break;
					}
				}
			}

			gLoseTexture.Render(0, 0, gRenderer);

			SDL_RenderPresent(gRenderer);
		}
	}
}

void ControlCharFrame(int& frame)
{
	frame += FRAME_INCREASEMENT;
	if (frame / SLOW_FRAME_CHAR >= RUNNING_FRAMES)
	{
		frame = 0;
	}
	SDL_Delay(15);
}

