#include "Game_Base.h"
#include "LTexture.h"
#include "Button.h"
#include "GameFeature.h"
#include "Character.h"
#include "Threats.h"

const std::string LAYER[BACKGROUND_LAYER] = {
	"imgs/background/4.png",
	"imgs/background/5.png",
	"imgs/background/3.png",
	"imgs/background/2.png",	
	"imgs/background/1.png",
};

// Init 
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
Mix_Music* gMusic = nullptr;
Mix_Music* gMenuMusic = nullptr;
Mix_Chunk* gClick = nullptr;
Mix_Chunk* gButton = nullptr;
SDL_Color textColor = { 255,255, 255 };
TTF_Font* gFont = nullptr; 
Mix_Chunk* gJump = nullptr;
Mix_Chunk* gLose = nullptr;
Mix_Chunk* gTele = nullptr;
Mix_Chunk* gSua = nullptr;
Mix_Chunk* gRocketSound = nullptr;

//SDL RECT
SDL_Rect gPlayButton[2];
SDL_Rect gTutorialsButton[2];
SDL_Rect gExitButton[2];
SDL_Rect gCharacterClips[RUNNING_FRAMES];
SDL_Rect gCharacterRunClips[RUNNING_FRAMES];
SDL_Rect gCharacterJumpClips[JUMP_FRAMES];
SDL_Rect Dog[8],Obstacles[10],Fly_gObstacle[6];
SDL_Rect Rocket; 
SDL_Rect Threat1, Threat2, Threat3;

//Create object of LTexture 
LTexture gMenu;
LTexture gBackgroundTexture[BACKGROUND_LAYER];
LTexture gPlayButtonTexture;
LTexture gExitButtonTexture;
LTexture gTutorialsTexture; 
LTexture gGroundTexture;
LTexture gCharacterTexture;
LTexture gCharacterTexture1;
LTexture gCharacterTexture2;
LTexture gInstructionTexture;
LTexture gLoseTexture;
LTexture gText1Texture; 
LTexture gText2Texture;
LTexture gScoreTexture;
LTexture gHighScoreTexture;
LTexture gObstacles, gFly_Obstacle;
LTexture gDog, gRocket, gWarning;

//create object Button
Button PlayButton(PLAY_BUTTON_POSX, PLAY_BUTTON_POSY);
Button TutorialsButton(TT_BUTTON_POSX, TT_BUTTON_POSY);
Button ExitButton(EXIT_BUTTON_POSX, EXIT_BUTTON_POSY);

Character character;
Threat Obstacle , FLYOBS;
Threat TDog,TRocket; 


bool Init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		gWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{

			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED |  SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				GetError("Renderer could not be created! SDL Error: %s\n", SDL_ERROR);
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					GetError("SDL_image could not initialize! SDL_image Error: %s\n", IMG_ERROR);
					success = false;
				}
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
					printf("SDL Mixer could not initialize! Error: %s\n", Mix_GetError());
				}
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

bool LoadMedia()
{
	//Loading success flag
	bool success = true;
	//Load media
	gMenuMusic = Mix_LoadMUS("sounds/Menu_Sound.mp3"); 
	if (gMenuMusic == nullptr) {
		GetError("Failed to load Menu sound\n", MIX_ERROR);
		success = false;
	}
	gMusic = Mix_LoadMUS("sounds/bkgr_sound.mp3");
	if (gMusic == nullptr) {
		GetError("Failed to load BackGround sound\n", MIX_ERROR);
		success = false;
	}
	gClick = Mix_LoadWAV("sounds/click_sound.wav");
	if (gClick == nullptr) {
		GetError("Failed to load click sound\n", MIX_ERROR);
		success = false;
	}
	gButton = Mix_LoadWAV("sounds/button_sound.wav");
	if (gButton == nullptr) {
		GetError("Failed to load button sound\n", MIX_ERROR);
		success = false;
	}
	gTele = Mix_LoadWAV("sounds/tele_sound.wav");
	if (gTele == nullptr) {
		GetError("Failed to load tele sound", MIX_ERROR);
		success = false;
	}
	gJump = Mix_LoadWAV("sounds/jump_sound.wav");
	if (gJump == nullptr) {
		GetError("Failed to load jumping sound", MIX_ERROR);
		success = false;
	}
	gSua = Mix_LoadWAV("sounds/sua_sound.wav");
	if (gSua == nullptr) {
		GetError("Failed to load sua? sound", MIX_ERROR);
		success = false;
	}
	gRocketSound = Mix_LoadWAV("sounds/rocket_sound.wav");
	if (gRocketSound == nullptr) {
		GetError("Failed to load rocket sound", MIX_ERROR);
		success = false;
	}
	//Load TEXT
	gFont = TTF_OpenFont("font/fonts.ttf", 40);
	if (gFont == NULL)
		{
			GetError("Failed to load font", MIX_ERROR);
			success = false;
		}
	else {
		if (!gText1Texture.LoadFromFileTTF("Your score: ", gFont, textColor, gRenderer))
		{
			std::cout << "Failed to render text1 texture" << std::endl;
			success = false;
		}
		if (!gText2Texture.LoadFromFileTTF("Best score: ", gFont, textColor, gRenderer))
		{
			std::cout << "Failed to render text2 texture" << std::endl;
			success = false;
		}
			
	}
	// Display Menu and Button + Background game 
	if (!gMenu.LoadFromFile("imgs/background/CityMenu.png", gRenderer)) {
		printf("Failed to load texture image!\n");
		success = false;
	}
	if (!gPlayButtonTexture.LoadFromFile("imgs/button/big_button/Play game.png", gRenderer)) {
		printf("Fail to load play_button image!\n");
		success = false;
	}

	else
	{
		for (int i = 0; i < 2; ++i)
		{
			gPlayButton[i].x = 222 * i;
			gPlayButton[i].y = 0;
			gPlayButton[i].w = 222;
			gPlayButton[i].h = 78;
		}
	}
	if (!gExitButtonTexture.LoadFromFile("imgs/button/big_button/exit_button.png", gRenderer)) {
		printf("Fail to load play_button image!\n");
		success = false;
	}

	else
	{
		for (int i = 0; i < 2; ++i)
		{
			gExitButton[i].x = 222 * i;
			gExitButton[i].y = 0;
			gExitButton[i].w = 222;
			gExitButton[i].h = 78;
		}
	}
	if (!gTutorialsTexture.LoadFromFile("imgs/button/big_button/Tutorials.png", gRenderer))
	{
		std::cout << "Failed to load help_button image" << std::endl;
		success = false;
	}
	else
	{
		for (int i = 0; i < 2; ++i)
		{
			gTutorialsButton[i].x = 222 * i;
			gTutorialsButton[i].y = 0;
			gTutorialsButton[i].w = 222;
			gTutorialsButton[i].h = 78;
		}
	}
	if (!gLoseTexture.LoadFromFile("imgs/background/lose.png",gRenderer)) {
		std::cout << "Failed to load lose image" << std::endl;
		success = false;
	}
	if (!gInstructionTexture.LoadFromFile("imgs/background/tutorials.png",gRenderer)) {
		printf("Fail to load instruction image\n");
		success = false;
	}
	for (int i = 0; i < BACKGROUND_LAYER; ++i)
	{
		if (!gBackgroundTexture[i].LoadFromFile(LAYER[i].c_str(), gRenderer))
		{
			std::cout << "Failed to load background image" << std::endl;
			success = false;
		}
	}


	if (!gGroundTexture.LoadFromFile("imgs/background/ground.png", gRenderer))
	{
		std::cout << "Failed to load ground image" << std::endl;
		success = false;
	}

	// Display Character
	if (!gCharacterTexture.LoadFromFile("imgs/character/char.png", gRenderer))
	{
		std::cout << "Failed to load character_run image." << std::endl;
		success = false;
	}
	else
	{
		gCharacterClips[0] = { 128 * 0,0,128,128 };
		gCharacterClips[1] = { 128 * 1,0,128,128 };
		gCharacterClips[2] = { 128 * 2,0,128,128 };
		gCharacterClips[3] = { 128 * 3,0,128,128 };
		gCharacterClips[4] = { 128 * 4,0,128,128 };
		gCharacterClips[5] = { 128 * 5,0,128,128 };
		gCharacterClips[6] = { 128 * 6,0,128,128 };
		gCharacterClips[7] = { 128 * 7,0,128,128 };
	}
	if (!gCharacterTexture1.LoadFromFile("imgs/character/tele.png", gRenderer))
	{
		std::cout << "Failed to load character_run image." << std::endl;
		success = false;
	}
	else
	{
		gCharacterRunClips[0] = { 128 * 0,0,128,128 };
		gCharacterRunClips[1] = { 128 * 1,0,128,128 };
		gCharacterRunClips[2] = { 128 * 2,0,128,128 };
		gCharacterRunClips[3] = { 128 * 3,0,128,128 };
		gCharacterRunClips[4] = { 128 * 4,0,128,128 };
		gCharacterRunClips[5] = { 128 * 5,0,128,128 };
		gCharacterRunClips[6] = { 128 * 6,0,128,128 };
		gCharacterRunClips[7] = { 128 * 7,0,128,128 };
	}
	if (!gCharacterTexture2.LoadFromFile("imgs/character/jump.png", gRenderer))
	{
		std::cout << "Failed to load character_run image." << std::endl;
		success = false;
	}
	else
	{
		gCharacterJumpClips[0] = { 128 * 0,0,128,128 };
		gCharacterJumpClips[1] = { 128 * 1,0,128,128 };
		gCharacterJumpClips[2] = { 128 * 2,0,128,128 };
		gCharacterJumpClips[3] = { 128 * 3,0,128,128 };
		gCharacterJumpClips[4] = { 128 * 4,0,128,128 };
		gCharacterJumpClips[5] = { 128 * 5,0,128,128 };
		gCharacterJumpClips[6] = { 128 * 6,0,128,128 };
	}
	//Load Threat
	if (!gObstacles.LoadFromFile("imgs/Threats/obstacle.png", gRenderer))
	{
		cout << "Failed to load obstacle image" <<endl;
		success = false;
	}
	else {
		for (int i = 0; i < 10; ++i) {
			Obstacles[i] = { 131 * i,0,131,101 };			
		}
	}
	if (!gFly_Obstacle.LoadFromFile("imgs/Threats/Drop.png", gRenderer)) {
		cout << "Failed to load fly_obstacle image" << endl;
		success = false;
	}
	else {
		for (int i = 0; i < 6; ++i) {
			Fly_gObstacle[i] = {140*i,0,140,140};
		}
	}
	if (!gDog.LoadFromFile("imgs/Threats/dog.png", gRenderer))
	{
		cout << "Failed to load threat image" << endl;
		success = false;
	}
	else 
	{
		for (int i = 0; i < 8; ++i) {
			Dog[i] = {176*i,0,176,110};
		}
	}
	if (!gRocket.LoadFromFile("imgs/Threats/rocket.png", gRenderer))
	{
		cout << "Failed to load threat image" << endl;
		success = false;
	}
	if (!gWarning.LoadFromFile("imgs/Threats/warning.png", gRenderer))
	{
		cout << "Failed to load threat image" << endl;
		success = false;
	}
	return success;
}

void Close()
{
	gMenu.Free();
	gPlayButtonTexture.Free();
	for (int i = 0; i < BACKGROUND_LAYER; ++i) {
		gBackgroundTexture[i].Free();
	}
	gGroundTexture.Free();
	gCharacterTexture.Free();
	gInstructionTexture.Free();
	gTutorialsTexture.Free();
	gExitButtonTexture.Free();

	Mix_FreeChunk(gJump);
	Mix_FreeMusic(gMusic);
	Mix_FreeMusic(gMenuMusic);
	Mix_FreeChunk(gTele);
	gJump = nullptr; 
	gMusic = nullptr;
	gMenuMusic = nullptr;
	gTele = nullptr;
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;


	//Quit SDL subsystems
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	if (!Init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!LoadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool Quit_Menu = false;
			bool Play_Again = false;
			bool Start_Tutorials = false;
			Mix_PlayMusic(gMenuMusic, IS_REPEATITIVE);
			//While application is running
			while (!Quit_Menu)
			{
				SDL_Event e;
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						Quit_Menu = true;
					}
					bool Quit_Game = false;
					HandlePlayButton(&e, PlayButton, Quit_Menu, Play_Again,gClick,gButton);
					HandleTTButton(&e,TutorialsButton,gInstructionTexture,gRenderer,Quit_Game,gClick, gButton);
					HandleExitButton(&e,ExitButton,Quit_Menu,gClick,gButton);
					if (Quit_Game == true) {
						return 0;
					}

				}
				gMenu.Render(0, 0, gRenderer);
				SDL_Rect* playButton = &gPlayButton[0];
				PlayButton.Render(playButton, gRenderer, gPlayButtonTexture);
				SDL_Rect* TTButton = &gTutorialsButton[0];
				TutorialsButton.Render(TTButton, gRenderer, gTutorialsTexture);
				SDL_Rect* EXButton = &gExitButton[0];
				ExitButton.Render(EXButton, gRenderer, gExitButtonTexture);
				if (PlayButton.currentSprite == BUTTON_SELECTED) {
					SDL_Rect* currentClip_Play = &gPlayButton[1];
					PlayButton.Render(currentClip_Play, gRenderer, gPlayButtonTexture);
				}
				else if (TutorialsButton.currentSprite == BUTTON_SELECTED_2) {
					SDL_Rect* currentClip_TT = &gTutorialsButton[1];
					TutorialsButton.Render(currentClip_TT, gRenderer, gTutorialsTexture);
				}
				else if (ExitButton.currentSprite == BUTTON_SELECTED_3) {
					SDL_Rect* EXButton = &gExitButton[1];
					ExitButton.Render(EXButton, gRenderer, gExitButtonTexture);
				}

				// Update screen
				SDL_RenderPresent(gRenderer);
			}
			while (Play_Again)
			{
				srand(time(NULL));
				int time = 0;
				int score = 0;
				int acceleration = 0;
				int frame_Character = 0;
				int frame_Enemy = 0;
				string highscore = "0";

				Mix_PlayMusic(gMusic, IS_REPEATITIVE);

				SDL_Event e;
				int OffsetSpeed_Ground = BASE_OFFSET_SPEED;
				std::vector <double> OffsetSpeed_Bkgr(BACKGROUND_LAYER, BASE_OFFSET_SPEED);

				bool Quit = false;
				bool Game_State = true;
				while (!Quit)
				{
					if (Game_State)
					{
						UpdateGameTimeAndScore(time, acceleration, score);
						while (SDL_PollEvent(&e) != 0)
						{
							if (e.type == SDL_QUIT)
							{
								Quit = true;
								Play_Again = false;
							}

							character.HandleEvent(e,gJump,gTele);
						}
						SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
						SDL_RenderClear(gRenderer);

						character.Move();
						RenderScrollingBackground(OffsetSpeed_Bkgr, gBackgroundTexture, gRenderer);
						RenderScrollingGround(OffsetSpeed_Ground, acceleration, gGroundTexture, gRenderer);

						//Render Character
						SDL_Rect* currentClip_Character = nullptr;
						if (character.OnGround() && character.GetcEvent() == false)
						{
							currentClip_Character = &gCharacterClips[frame_Character / SLOW_FRAME_CHAR];
							character.Render(currentClip_Character, gRenderer, gCharacterTexture);
						}
						else if (character.OnGround() && character.GetcEvent() == true) {
							currentClip_Character = &gCharacterRunClips[frame_Character / SLOW_FRAME_CHAR];
							character.Render(currentClip_Character, gRenderer, gCharacterTexture1);
						}	
						else if (character.GetcEvent1() == true) {
							currentClip_Character = &gCharacterRunClips[(frame_Character / 50)];
							character.Render(currentClip_Character, gRenderer, gCharacterTexture2);
						}
						else
						{
							currentClip_Character = &gCharacterClips[0];
							character.Render(currentClip_Character, gRenderer, gCharacterTexture);
						}
						character.Move();

						//Render Threat

						SDL_Rect* currentclip_Obstacles = &Obstacles[frame_Character / SLOW_FRAME_OBS];
						Obstacle.render_Obstacles(currentclip_Obstacles,gRenderer, gObstacles);
						Obstacle.threat_move(acceleration);						
						Threat1 = Obstacle.get_OBS_dimension();

						SDL_Rect* currentclip_FlyOBS = &Fly_gObstacle[frame_Character / SLOW_FRAME_OBS];
						FLYOBS.render_Fly_Obstacles(currentclip_FlyOBS, gRenderer, gFly_Obstacle);
						FLYOBS.threat_move(acceleration);
						Threat2 = FLYOBS.get_FOBS_dimension();

						SDL_Rect* currentClip_Dog = &Dog[frame_Character / SLOW_FRAME_DOG];
						TDog.render_Dog(currentClip_Dog, gRenderer, gWarning ,gDog,gSua);	
						TDog.threat_move(acceleration);
						Threat3 = TDog.get_Dog_dimension();

						TRocket.render_rocket(gRocket, gWarning, gRenderer,gRocketSound);
						TRocket.threat_move(acceleration);	
						Rocket = TRocket.get_rocket_dimension();

						DrawPlayerScore(gText1Texture, gScoreTexture, textColor, gRenderer, gFont, score);
						DrawPlayerHighScore(gText2Texture, gHighScoreTexture, textColor, gRenderer, gFont, highscore);
							
						//Check_collision
						if (character.check_collision(Rocket, currentClip_Character) ==true || character.check_collision_clips(Threat1,Threat3,Threat2,currentclip_Obstacles,currentClip_Dog,currentclip_FlyOBS,currentClip_Character) == false ){
							Quit = true;
						}
						SDL_RenderPresent(gRenderer);
						ControlCharFrame(frame_Character);
					}
				}
				DrawEndGameSelection(gLoseTexture, &e, gRenderer, Play_Again);
				if (!Play_Again) {
					Obstacle.gameOver();
					FLYOBS.gameOver();					
					TDog.gameOver();
					TRocket.gameOver();
				}
			}
		}
	}
	//Free resources and close SDL
	Close();

	return 0;
}

