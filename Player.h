/* File: Player.h
Author: Hiren Pandya (101198481)
Created On: 19/11/2018
Modified On: 08/12/2018
*/
#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "LOTile.h"

/* Important note: x coordinate is player's COLUMN position and
y coordinate is player's ROW position. Don't mix these up! */

class Player : public LOTile
{
public:
	int m_iMoveSpeed = 32;
	bool isPlayerAlive = true;

	Player(int p_x, int p_y, SDL_Renderer* p_pRenderer, SDL_Texture* p_pTexture) : LOTile(p_x, p_y) // Calling constructor of the super class
	{
		//this->m_cOutput = '@';
		this->m_pRenderer = p_pRenderer; // Set the renderer
		this->m_x = p_x; // X coordinate of player's location
		this->m_y = p_y; // Y coordinate of player's location
		this->m_rSrc = { 0, 0, 32, 32 }; // Set default properties of m_rSrc rect
		this->SetImage(p_pRenderer, p_pTexture); // Set the player image
		updateDst(); // Update player's location on the map
		m_rDst.w = 32; // Set dest rect width
		m_rDst.h = 32; // Set dest rect height
	}
	// Update player's location on the map
	void updateDst() {
		m_rDst.x = m_x;
		m_rDst.y = m_y;
	}
	// Move player by chaning X coordinate
	void MoveX(int p_iX) {
		this->m_x += p_iX;
		updateDst();
	}
	// Move player by changing Y coordinate
	void MoveY(int p_iY) {
		this->m_y += p_iY;
		updateDst();
	}
	// Getters for src and dest rect
	const SDL_Rect* GetSrc() { return &m_rSrc; }
	const SDL_Rect* GetDst() { return &m_rDst; }
};

#endif  