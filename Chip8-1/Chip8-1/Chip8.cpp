// Chip8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Chip8.h"
#include "Platform.h"
#include <string> 

int main(int argc, char** argv)
{

	int videoScale = 10;							//kept default
	int cycleDelay = 1;								//kept default
	char const* romFilename = "F:\ROMs\TETRIS.ch8";					//use your path of ROM files

	Platform platform("CHIP-8 Emulator", VIDEO_WIDTH * videoScale, VIDEO_HEIGHT * videoScale, VIDEO_WIDTH, VIDEO_HEIGHT);

	Chip8 chip8;
	chip8.LoadROM(romFilename);

	int videoPitch = sizeof(chip8.video[0]) * VIDEO_WIDTH;

	auto lastCycleTime = std::chrono::high_resolution_clock::now();
	bool quit = false;

	while (!quit)
	{
		quit = platform.ProcessInput(chip8.keypad);

		auto currentTime = std::chrono::high_resolution_clock::now();
		float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();

		if (dt > cycleDelay)
		{
			lastCycleTime = currentTime;

			chip8.Cycle();

			platform.Update(chip8.video, videoPitch);
		}
	}

	return 0;
}
