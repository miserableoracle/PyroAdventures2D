/*
File: Game.h
Author: Hiren Pandya (101198481)
Created On: 08/11/2018
Modified On: 08/12/2018
*/
#include "stdafx.h"
#include <iostream> // For debugs
#include "Game.h"
#include <chrono>
#include "Level.h"
#include "Player.h"
#include "SDL_image.h"
using namespace std;
using namespace chrono;

// Default constructor
Game::Game() {
	this->m_iFPS = FPS;
	this->m_bGotTick = false;
	this->m_bUpPressed = false;
	this->m_bDownPressed = false;
	this->m_bLeftPressed = false;
	this->m_bRightPressed = false;
}

/* Member Function: Game::init()
Initialization of the game engine
Input:	title - Title of the window,
xpos - X position of the window,
ypos - Y position of the window,
width - Width of the window,
height - Height of the window,
flags
Return: */

bool Game::init(const char* title, int xpos, int ypos, int width,
	int height, int flags) {
	// Attempt to initialize SDL.
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		cout << "SDL init success" << endl;
		// Init the window.
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_pWindow != 0) { // Window init success. can also be done with 'nullptr'
			cout << "Window creation successful" << endl;
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != 0) { // Renderer init success.
				cout << "renderer creation successful" << endl;
				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
				if (IMG_Init(IMG_INIT_PNG) != 0) { // Image Init Success
					cout << "Image Init Done" << endl;
				}
				else {
					cout << "Image init failure." << endl;
					return false;
				}
			}
			else {
				cout << "renderer init fail" << endl;
				return false; // Renderer init failed.
			}
		}
		else {
			cout << "window init fail" << endl;
			return false; // window init failed.
		}
	}
	else {
		cout << "SDL init fail" << endl;
		return false; // SDL init failed.
	}
	cout << "init success" << endl;
	m_bRunning = true; // Everything is okay, start the engine.
	return true;
}

/* Member Function: Game::running()
To check m_bRunning status
Input: N/A
Return: m_bRunning */

bool Game::running() {
	return this->m_bRunning;
}
/* Member Function: Game::tick()	
Input: N/A
Return: boolean m_bGotTick
*/
bool Game::tick() {
	auto duration = steady_clock::now().time_since_epoch();
	auto count = duration_cast<microseconds>(duration).count();
	int tick = 1000000 / m_iFPS;

	if (count % tick == 0) {
		if (m_bGotTick == false) {
			m_bGotTick = true;
			return true;
		}
		return false;
	}
	else {
		m_bGotTick = false;
	}
	return false;
}

/* Member Function: Game::update()
update the render, check for obstacles, check for hazard, move player on the map according to the key pressed.
Input: N/A
Return: N/A */

void Game::update(Level& l, Player& p, int& p_iCurrLevel) {
	// button press events
	// If UP button 'W' is pressed and player is alive on the map, move player
	// Check for the boundaries
	if (m_bUpPressed && p.isPlayerAlive) {
		// Check if next tile is an obstacle or not before moving the player to that tile
		if (l.map[p.m_rDst.y / 32 - 1][p.m_rDst.x / 32].m_bIsObstacle == false && p.m_y > 0) {
			p.MoveY(-32);
		}
		cout << p.m_x << " " << p.m_y << endl;
	}
	// If DOWN button 'S' is pressed and player is alive on the map, move player
	// Check for the boundaries
	if (m_bDownPressed && p.isPlayerAlive) {
		// Check if next tile is an obstacle or not before moving the player to that tile
		if (l.map[p.m_rDst.y / 32 + 1][p.m_rDst.x / 32].m_bIsObstacle == false && p.m_y < 768) {
			p.MoveY(32);
		}
		cout << p.m_x << " " << p.m_y << endl;
	}
	// If LEFT button 'A' is pressed and player is alive on the map, move player
	// Check for the boundaries
	if (m_bLeftPressed && p.isPlayerAlive) {
		// Check if next tile is an obstacle or not before moving the player to that tile
		if (l.map[p.m_rDst.y / 32][p.m_rDst.x / 32 - 1].m_bIsObstacle == false && p.m_x > 0) {
			p.MoveX(-32);
		}
		cout << p.m_x << " " << p.m_y << endl;
	}
	// If RIGHT button 'D' is pressed and player is alive on the map, move player
	// Check for the boundaries
	if (m_bRightPressed && p.isPlayerAlive) {
		// Check if next tile is an obstacle or not before moving the player to that tile
		if (l.map[p.m_rDst.y / 32][p.m_rDst.x / 32 + 1].m_bIsObstacle == false && p.m_x < 992) {
			p.MoveX(32);
		}
		cout << p.m_x << " " << p.m_y << endl;
	}

	// Check if player entered into the hazard zone. If so, player is dead
	if (l.map[p.m_rDst.y / 32][p.m_rDst.x / 32].m_bIsHazard == true && p.isPlayerAlive) {
		p.isPlayerAlive = false;
		cout << "Game Over" << endl; // Print game over in the console.
		p.m_rSrc.x += 32; // Update player's source tile to the next one.
	}
	// Check if player has arrived on the door or not. 
	// Match all the doors' coordinates with the player's coordinates.
	// If match, change the level to the level added using AddDoor() method.
	for (int i = 0; i < l.m_iNumDoors; i++) {
		if (p.m_rDst.x == l.doors[i].m_rDst.x && p.m_rDst.y == l.doors[i].m_rDst.y) {
			p_iCurrLevel = l.doors[i].GetToLevel(); // Change the current level to next level where the door leads
			p.m_rDst.x = p.m_x = l.doors[i].GetDestX(); // Update player's spawning X coordinate for the next level
			p.m_rDst.y = p.m_y = l.doors[i].GetDestY(); // Update player's spawning Y coordinate for the next level
		}
	}
}

/* Member Function: Game::handleEvents()
Handle the window events
Input: N/A
Return: N/A */

void Game::handleEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) // Keep polling for the events
	{
		switch (event.type)
		{
		case SDL_QUIT: // If QUIT event occurs
			m_bRunning = false;
			break;
		case SDL_KEYDOWN: // If user pressed a key, update related variables
			switch (event.key.keysym.sym)
			{
			case 'w':
			case 'W':
				if (!m_bUpPressed)
					m_bUpPressed = true;
				break;
			case 's':
			case 'S':
				if (!m_bDownPressed)
					m_bDownPressed = true;
				break;
			case 'a':
			case 'A':
				if (!m_bLeftPressed)
					m_bLeftPressed = true;
				break;
			case 'd':
			case 'D':
				if (!m_bRightPressed)
					m_bRightPressed = true;
				break;
			}
			break;
		case SDL_KEYUP: // When user releases the key on the keyboard
			switch (event.key.keysym.sym)
			{
			case 'w':
			case 'W':
				m_bUpPressed = false;
				break;
			case 's':
			case 'S':
				m_bDownPressed = false;
				break;
			case 'a':
			case 'A':
				m_bLeftPressed = false;
				break;
			case 'd':
			case 'D':
				m_bRightPressed = false;
				break;
			}
			break;
		}
	}
}

/* Member Function: Game::render()
Render the output on the screen
Input: N/A
Return: N/A */

void Game::render(Level& l, Player& p) {
	// Clear previous render output on the screen before rendering anything new
	SDL_RenderClear(m_pRenderer); // Clear the screen to draw the colors.
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			// Render each tile of the map with related images.
			SDL_RenderCopy(m_pRenderer, l.map[row][col].m_pTexture, &l.map[row][col].m_rSrc, &l.map[row][col].m_rDst);
		}
	}

	// Don't need to set the render for the door, as we already did that with above loop.
	// AddDoor will be handled while creating the level itself.
	// Door check is present in Game::update() module
	//for (int i = 0; i < 3; i++) {
		//SDL_RenderCopy(m_pRenderer, l.doors[i].m_pTexture, &l.doors[i].m_rSrc, &l.doors[i].m_rDst);
	//}
	SDL_RenderCopy(m_pRenderer, p.m_pTexture, &p.m_rSrc, &p.m_rDst);
	SDL_RenderPresent(m_pRenderer); // Draw anew
}

/* Member Function: Game::clean()
Clean the game
Input: N/A
Return: N/A */

void Game::clean() {
	cout << "cleaning game" << endl;
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

/* Member Function: Game::getRenderer()
Get the SDL Renderer pointer
Input: N/A
Output: SDL_Renderer pointer
*/

SDL_Renderer* Game::getRenderer() {
	return m_pRenderer;
}