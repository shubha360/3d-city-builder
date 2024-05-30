#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>

#include <iostream>

enum class GameState 
{
	PLAY, 
	EXIT
};

class Game 
{
public:
	
	/// default constructor initializes everything
	Game();
	/// destructor frees the everything
	~Game();
	
	/// runs the main game loop
	void run();

private:
	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGHT = 768;
	GameState state_ = GameState::PLAY;
	
	SDL_Window* window = nullptr;

	void processInput();
};

