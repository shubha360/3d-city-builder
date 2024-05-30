#include "Game.h"

/// default constructor initializes everything
Game::Game() 
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		printf("Error initializing SDL! Error: %s\n", SDL_GetError());

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window =
		SDL_CreateWindow("3D City Builder", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

	if (!window)
		printf("Error creating window! Error: %s\n", SDL_GetError());

	SDL_GLContext glContext = SDL_GL_CreateContext(window);

	if (!glContext)
		printf("Error creating SDL_GLContext! Error: %s\n", SDL_GetError());

	GLenum respone = glewInit();

	if (respone != GLEW_OK)
		printf("Error initializing GLEW!\n");
}

/// destructor frees the freeable memories
Game::~Game() 
{
	
	if (window) 
	{
		SDL_DestroyWindow(window);
		window = nullptr;
	}

	SDL_Quit();
}

void Game::run() 
{

	while (state_ == GameState::PLAY) 
	{
	
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		processInput();

		SDL_GL_SwapWindow(window);
	}
}

void Game::processInput() 
{
	static SDL_Event event;

	while (SDL_PollEvent(&event)) 
	{
		switch (event.type) {

		case SDL_QUIT:
			state_ = GameState::EXIT;
			break;

			/*case SDL_MOUSEMOTION:
				m_inputProcessor.setMouseCoords(event.motion.x, event.motion.y);
				break;

			case SDL_MOUSEBUTTONDOWN:
				m_inputProcessor.pressKey(event.button.button);
				break;

			case SDL_MOUSEBUTTONUP:
				m_inputProcessor.releaseKey(event.button.button);
				break;

			case SDL_KEYDOWN:
				m_inputProcessor.pressKey(event.key.keysym.sym);
				break;

			case SDL_KEYUP:
				m_inputProcessor.releaseKey(event.key.keysym.sym);
				break;*/
		}
	}
}