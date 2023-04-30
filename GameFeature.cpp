#include"AllHeaderFile.h"
SDL_Rect* currentClip_Continue;
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
string GetHighScoreFromFile(const string& path){
	fstream HighScoreFile;
	string HighScore;

	HighScoreFile.open(path, std::ios::in);
	HighScoreFile >> HighScore;
	return HighScore;
}
void ResetHighScore(const std::string& path) {
	std::ofstream HighScoreFile(path);
	HighScoreFile << "0";
	HighScoreFile.close();
}
void UpdateHighScore(const std::string& path,
	const int& score,
	const std::string& old_high_score)
{
	int oldHighScore = 0;
	std::fstream HighScoreFile;
	std::string newHighScore;
	std::stringstream ConvertToInt(old_high_score);

	HighScoreFile.open(path, std::ios::in | std::ios::out);

	if (HighScoreFile.is_open()) {
		if (ConvertToInt >> oldHighScore) {
			if (score > oldHighScore)
			{
				oldHighScore = score;
			}
		}
		else {
			std::cerr << "Error: Invalid old high score input: " << old_high_score << std::endl;
			return;
		}

		newHighScore = std::to_string(oldHighScore);

		HighScoreFile.seekp(0);
		HighScoreFile << newHighScore;
	}
	else {
		std::cerr << "Error: Could not open file " << path << std::endl;
		return;
	}
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
					End_Game = true; 
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
	SDL_Delay(13);
}

void HandleContinueButton(Button ContinueButton,
	LTexture gContinueButtonTexture,
	SDL_Event* e,
	SDL_Renderer* gRenderer,
	SDL_Rect(&gContinueButton)[2],
	bool& Game_State,
	Mix_Chunk* gClick)
{
	bool Back_To_Game = false;
	bool isKeyPressed = false;

	while (!Back_To_Game)
	{
		do
		{
			if (e->type == SDL_KEYDOWN && (e->key.keysym.sym == SDLK_p) && !isKeyPressed) {
				Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
				Mix_ResumeMusic();
				Game_State = true;
				Back_To_Game = true;
				isKeyPressed = true;
			}
			else {				
				currentClip_Continue = &gContinueButton[1];
				if (!isKeyPressed) {
					ContinueButton.Render(currentClip_Continue, gRenderer, gContinueButtonTexture);
				}
			}
			SDL_RenderPresent(gRenderer);
		} while (SDL_WaitEvent(e) != 0 && e->type == SDL_KEYDOWN && (e->key.keysym.sym == SDLK_p));
		isKeyPressed = false; // Reset biến đánh dấu phím P sau khi nhả nút
		SDL_RenderPresent(gRenderer);
	}
}

void HandlePauseButton(SDL_Event* e, SDL_Renderer* gRenderer, SDL_Rect(&gContinueButton)[2], Button ContinueButton, LTexture gContinueButtonTexture, bool& game_state, Mix_Chunk* gClick)
{
	static bool isKeyPressed = false;
	
	if (e->type == SDL_KEYUP && (e->key.keysym.sym == SDLK_p) && !isKeyPressed) {
		isKeyPressed = true;
		HandleContinueButton(ContinueButton, gContinueButtonTexture, e, gRenderer, gContinueButton, game_state, gClick);
	}
	else if (e->type == SDL_KEYDOWN && (e->key.keysym.sym == SDLK_p)) {
		isKeyPressed = false; // Reset biến đánh dấu phím P
	}
}