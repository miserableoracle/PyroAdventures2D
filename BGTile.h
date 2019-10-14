/* File: BGTile.h
Author: Hiren Pandya (101198481)
Created On: 19/11/2018
Modified On: 08/12/2018
*/
#pragma once
#ifndef _BGTILE_H_
#define _BGTILE_H_
#include <iostream>
#include "Sprite.h"
using namespace std;

// Class for background tiles
class BGTile : public Sprite {
public:
	bool m_bIsObstacle; // If the tile is an obstacle
	bool m_bIsHazard; // If the tile is a hazard zone

	void SetBGTile(const char p_cOutput) {
		// Set the output character
		this->m_cOutput = p_cOutput;
		// Check if the character is an obstacle
		// Currently considering followings as obstacles
		// 'M' for rocks, 'm' for mossy rocks, 'M' for rocks,  'O' for cut tree trunks, '=' for wood walls, 'B' for stone bricks/dungeon walls
		if (p_cOutput == 'M' || p_cOutput == 'm' || p_cOutput == 'O' || p_cOutput == '=' || p_cOutput == 'B') {
			this->m_bIsObstacle = true;
		}
		else
			this->m_bIsObstacle = false;
		// Check if the character is a hazard 'X'
		if (p_cOutput == 'X') {
			this->m_bIsHazard = true;
		}
		else {
			this->m_bIsHazard = false;
		}
		// Set the source rect properties according to the output character taken from the level.
		SetSrcRect(p_cOutput);
	}

	void SetSrcRect(const char p_cOutput) {
		if (p_cOutput == ',') {	// Top tile 1 - Grass
			m_rSrc.x = 0;
			m_rSrc.y = 0;
		}
		else if (p_cOutput == ';') { // Top tile 2 - Tall Grass
			m_rSrc.x = 32;
			m_rSrc.y = 0;
		}
		else if (p_cOutput == 'M') { // Top tile 3 - Rocks
			m_rSrc.x = 64;
			m_rSrc.y = 0;
		}
		else if (p_cOutput == 'm') { // Top tile 4 - Rocks mossy
			m_rSrc.x = 96;
			m_rSrc.y = 0;
		}
		else if (p_cOutput == '.') { // Top tile 5 - Dirt
			m_rSrc.x = 128;
			m_rSrc.y = 0;
		}
		else if (p_cOutput == '-') { // Top tile 6 - Sand
			m_rSrc.x = 160;
			m_rSrc.y = 0;
		}
		else if (p_cOutput == '~') { // Top tile 7 - Water
			m_rSrc.x = 192;
			m_rSrc.y = 0;
		}
		else if (p_cOutput == 'X') { // Top tile 8 - Lava
			m_rSrc.x = 224;
			m_rSrc.y = 0;
		}
		else if (p_cOutput == '#') { // Bottom tile 1 - Tree Leaves
			m_rSrc.x = 0;
			m_rSrc.y = 32;
		}
		else if (p_cOutput == 'O') { // Bottom tile 2 - Tree trunk
			m_rSrc.x = 32;
			m_rSrc.y = 32;
		}
		else if (p_cOutput == '=') { // Bottom tile 3 - Wood wall
			m_rSrc.x = 64;
			m_rSrc.y = 32;
		}
		else if (p_cOutput == 'H') { // Bottom tile 4 - Wood roof
			m_rSrc.x = 96;
			m_rSrc.y = 32;
		}
		else if (p_cOutput == 'B') { // Bottom tile 5 - Dungeon wall
			m_rSrc.x = 128;
			m_rSrc.y = 32;
		}
		else if (p_cOutput == '_') { // Bottom tile 6 - Dungeon Floor
			m_rSrc.x = 160;
			m_rSrc.y = 32;
		}
		else if (p_cOutput == 'Q') { // Bottom tile 7 - All Level Doors
			m_rSrc.x = 192;
			m_rSrc.y = 32;
		}
		else if (p_cOutput == '%') { // Bottom tile 8 - Bone pile
			m_rSrc.x = 224;
			m_rSrc.y = 32;
		}
	}
};

#endif // !_BGTILE_H_