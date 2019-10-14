/*
File: Game.h
Author: Hiren Pandya (101198481)
Created On: 08/11/2018
Modified On: 08/12/2018
*/
#pragma once
#include "SDL.h"
#include "Level.h"
#include "Player.h"
#define FPS 10

class Game {
private:
	// Boolean variable to confirm if the engine is running or not.
	bool m_bRunning;
	bool m_bGotTick;
	bool m_bUpPressed; // If player pressed up key 
	bool m_bDownPressed; // If player pressed down key
	bool m_bLeftPressed; // If player pressed left key
	bool m_bRightPressed; // If player pressed right key
	int m_iFPS;			// FPS for the player movement
	int m_iTickCtr = 0;
	int m_iTickMax = 8; // For animation speed
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

public:
	// Default Constructor
	Game();
	// Default Destructor
	~Game() {}

	/**** Function prototypes ****/

	// Initialization
	bool init(const char* title, int xpos, int ypos, int width,
		int height, int flags);
	// To check m_bRunning status
	bool running();
	bool tick();
	void update(Level&, Player&, int&);
	// Handle the window events
	void handleEvents();
	// Puts all the changes happening during a frame or a tick of the engine, and renders it back to the output window 
	void render(Level&, Player&);
	// Clear the game properties
	void clean();
	// Getter for the renderer 
	SDL_Renderer* getRenderer();
};