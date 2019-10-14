/* File: Level.h
Author: Hiren Pandya (101198481)
Created On: 19/11/2018
Modified On: 08/12/2018
*/
#pragma once
#ifndef _LEVEL_H_
#define _LEVEL_H_
#include "BGTile.h"
#include <fstream>
#include <iostream>
#include "Door.h"
#define ROWS 24
#define COLS 32
#define TOTALDOORS 3
using namespace std;

// To easily organize a level into a class
class Level {
public:
	int m_iNumDoors; // increases when a door is added in the level.
	BGTile map[ROWS][COLS]; // Level map
	Door doors[TOTALDOORS];

	// Default constructor
	Level() {
		this->m_iNumDoors = 0;
	}

	// Non default - parameterized contructor to construct the level
	Level(const char* fileName, SDL_Renderer* p_pRenderer, SDL_Texture* p_pTexture) {
		this->m_iNumDoors = 0;
		// Read the characters from the file and check if any door is present
		ifstream inFileTemp(fileName);
		char temp;
		int doorToLevel, destCol, destRow;
		if (inFileTemp.is_open()) {
			for (int i = 0; i < ROWS; i++) {
				for (int j = 0; j < COLS; j++) {
					inFileTemp >> temp;
					// If the door is present, next 3 things will be toLevel, destX, destY.
					if (temp == 'Q') {
						inFileTemp >> doorToLevel; // Next - To which level this door will lead
						inFileTemp >> destCol; // Next - In which column shall player be spawning
						inFileTemp >> destRow; // Next - In which row shall player be spawning
						// Add the door with given parameters
						this->AddDoor(j, i, doorToLevel, destCol * 32, destRow * 32, p_pRenderer, p_pTexture);
					}
					temp = ' '; // Reset temp variable for next character
				}
			}
		}
		inFileTemp.close();
		ifstream inFile(fileName); // Open the file passed while object creation
		char output; // Variable to store output
		if (inFile.is_open()) // If file open success
		{
			for (int row = 0; row < ROWS; row++)
			{
				for (int col = 0; col < COLS; col++)
				{
					inFile >> output; // Get the single character from file into the temp. variable
					this->map[row][col].SetBGTile(output); // Call SetBGTile method to set the output variable m_cOutput
					this->map[row][col].SetImage(p_pRenderer, p_pTexture);
					this->map[row][col].m_rDst = { col * 32, row * 32, 32, 32 }; // Set the source rect properties
					if (output == 'Q') {
						// If it's a door, next 3 characters will be door properties. 
						inFile >> doorToLevel >> destCol >> destRow;
					}
				}
			}
			inFile.close(); // Thanks Jack for the reminder. I put it in the right place this time.
		}
	}

	// A method to add new door
	void AddDoor(const int p_x, const int p_y, const int p_iToLevel, const int p_iDestX, const int p_iDestY, SDL_Renderer* p_pRenderer, SDL_Texture* p_pTexture) {
		if (this->m_iNumDoors < 3) {
			doors[this->m_iNumDoors++].SetDoor(p_x, p_y, p_iToLevel, p_iDestX, p_iDestY, p_pRenderer, p_pTexture);
		}
	}
};
#endif // !_LEVEL_H_