#include "AllHeaderFile.h"
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
			gameLoop();
		}
	}
	Close();
	return 0;
}

