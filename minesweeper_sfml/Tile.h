#pragma once
#include <vector>
#include <iostream>
#include <time.h>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

/*
To include SFML files, in Visual Studio 2019...
	  1. Select ALL CONFIGURATIONS in Project properties
	  2. Add ...SFML\include to include path via
		 Project properties -> C/C++ -> General -> Additional Include Directories
	  3. Add ...SFML\lib to
		 Project Properties -> Linker -> General-> Additional Library Directories
	  4. In Linker -> Input -> Additional Dependencies, add each SFML library file you need
		 (e.g., sfml-window.lib)
	  5. For DEBUG configuration, add debug library files to Additional Dependencies
		 (e.g., sfml-window-d.lib)
*/

struct Tile {

	unsigned int pixX, pixY, index;
	bool mine;
	bool flag;
	bool revealed;
	std::vector<Tile*> neighborhood;
	const unsigned int w = 32, h = 32, bWidth = 25, bHeight = 16;

	~Tile() = default;
	Tile(bool mine_, unsigned int x_, unsigned int y_, unsigned int _index) { mine = mine_; pixX = x_; pixY = y_; index = _index; flag = revealed = false; }
	std::vector<bool> neighborExistence() {

		// 0) topLeft, 1) top, 2) topRight, 3) Left, 
		// 4) Right, 5) BottomLeft, 6) Bottom, 7) BottomRight

		std::vector<bool> n(8);
		n[0] = (index > 24 && index % 25 != 0);
		n[1] = (index > 24);
		n[2] = (index > 24 && (index + 1) % 25 != 0);
		n[3] = (index % 25 != 0);
		n[4] = ((index + 1) % 25 != 0);
		n[5] = (index < bWidth* (bHeight - 1) && index % 25 != 0);
		n[6] = (index < bWidth* (bHeight - 1));
		n[7] = (index < bWidth* (bHeight - 1) && (index + 1) % 25 != 0);

		return n;

	}
	std::vector<int> neighborIndices() {

		std::vector<int> indices(8);
		const std::vector<bool> neighbors = neighborExistence();

		for (unsigned int x = 0; x < neighbors.size(); x++) {

			if (!neighbors[x])
				indices[x] = -1;

			else {

				if (x <= 2)
					indices[x] = index - bWidth + (x - 1);

				else if (x <= 4)
					indices[x] = index + ((x == 3) ? -1 : 1);

				else if (x <= 7)
					indices[x] = index + bWidth + (x - 6);

			}

		}

		return indices;

	}

};