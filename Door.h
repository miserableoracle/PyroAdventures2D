/* File: Door.h
Author: Hiren Pandya (101198481)
Created On: 19/11/2018
Modified On: 08/12/2018
*/
#pragma once
#ifndef _DOOR_H_
#define _DOOR_H_
#include "LOTile.h"

class Door : public LOTile {
private:
	int m_iToLevel; //Represents an index of a Level object
	int m_iDestX; // Represents the x coordinate at which to spawn the player once they go through the door
	int m_iDestY; // Represents the y coordinate at which to spawn the player 
public:
	// Default constructor
	Door() {
		this->m_cOutput = 'D';
	}
	// Setter method to set all the member variables
	void SetDoor(const int p_x, const int p_y, const int p_iToLevel, const int p_iDestX, const int p_iDestY, SDL_Renderer* p_pRenderer, SDL_Texture* p_pTexture) {
		this->m_x = p_x; // Set player's position's x coordinate
		this->m_y = p_y; // Set player's position's y coordinate
		this->m_iToLevel = p_iToLevel; // Set the level where player will spawn
		this->m_iDestX = p_iDestX; // Set x coordinate of spawning location
		this->m_iDestY = p_iDestY; // Set y coordinate of spawning location
		this->SetX(p_x);	// Set X of the tile
		this->SetY(p_y);	// Set Y of the tile
		this->SetImage(p_pRenderer, p_pTexture); // Set the image of the tile
		this->m_rDst.h = 32; // Init dest rect height
		this->m_rDst.w = 32; // Init dest rect width
	}

	// Getter methods for private member functions.
	int GetToLevel() {
		return this->m_iToLevel; // Get the level number where player will spawn if entered the door
	}
	int GetDestX() {
		return this->m_iDestX; // Get X coordinate of spawning location 
	}
	int GetDestY() {
		return this->m_iDestY; // Get x coordinate of spawning location
	}
};
#endif // !_DOOR_H_
