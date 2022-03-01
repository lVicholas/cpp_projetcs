#pragma once
#include "Tile.h"

struct Board {

	std::vector<Tile*> tiles;
	unsigned int flags, mines, revealedTiles;
	int counter;
	bool debug, gameOver;
	const unsigned int w = 25, h = 16, tileW = 32, tileH = 32;

	///// Non-Sprite Methods /////

	Board() { reset(); }
	void testBoard(std::string& data, std::map<std::string, sf::Texture>& resources, std::vector<sf::Sprite>& sprites) {

		tiles.clear();
		mines = flags = counter = 0;
		unsigned int col, row; col = row = 0;

		for (unsigned int x = 0; x < w * h; x++) {

			bool m = (data[x] == '1');
			if (m) mines++;

			Tile* tile = new Tile(m, col * tileW, row * tileH, x);
			tiles.push_back(tile);

			if ((x + 1) % 25 == 0) {

				col = 0;
				row++;

			}

			else col++;

		}

		debug = gameOver = false;
		counter = mines; flags = revealedTiles = 0;
		connectTiles();

	}
	std::vector<unsigned int> randomize() {

		std::vector<unsigned int> nums;
		for (unsigned int x = 0; x < w * h; x++)
			nums.push_back(x);

		std::random_shuffle(nums.begin(), nums.end());

		auto f = nums.begin();
		auto l = nums.begin() + 50;

		std::vector<unsigned int> t(f, l);
		std::sort(t.begin(), t.end());

		return t;

	}
	static bool search(std::vector<unsigned int> nums, unsigned int key) {

		for (unsigned int x = 0; x < nums.size(); x++) {

			if (nums[x] > key)
				return false;

			if (nums[x] == key)
				return true;

		}

		return false;
	}
	static unsigned int determineMines(Tile* tile) {

		int c = 0;
		for (Tile* t : tile->neighborhood) {

			if (t == nullptr)
				continue;

			else if (t->mine)
				c++;

		}

		return c;

	}
	void connectTiles() {

		for (unsigned int x = 0; x < tiles.size(); x++) {

			std::vector<int> nIndices = tiles[x]->neighborIndices();

			for (unsigned int y = 0; y < nIndices.size(); y++) {

				if (nIndices[y] < 0)
					tiles[x]->neighborhood.push_back(nullptr);
				else {

					tiles[x]->neighborhood.push_back(tiles[nIndices[y]]);

				}

			}

		}

	}
	bool onBoard(sf::Vector2i pos) { return pos.y <= h * tileH; }
	Tile* getClickedBoi(sf::Vector2i pos) { return tiles[(pos.x / tileW) + ((pos.y / tileH) * w)]; }
	void chainReveal(Tile* tile) {

		// This tile has 0 surrounding mines
		tile->revealed = true;
		revealedTiles++;

		if (determineMines(tile) != 0)
			return;

		else {

			for (Tile* t : tile->neighborhood) {

				if (t != nullptr && !t->revealed && !t->flag)
					chainReveal(t);

			}

		}

	}
	void reset() {

		tiles.clear();
		std::vector<unsigned int> min = randomize();

		unsigned int col, row; col = row = 0;

		for (unsigned int x = 0; x < w * h; x++) {

			Tile* tile = new Tile(search(min, x), col * tileW, row * tileH, x);
			tiles.push_back(tile);

			if ((x + 1) % w == 0) {

				col = 0;
				row++;

			}
			else col++;

		}

		debug = gameOver = false;
		flags = revealedTiles = 0; mines = min.size();
		counter = mines - flags;
		connectTiles();
	}
	std::string determineSprite(Tile* tile) {

		if (!tile->revealed) {

			if (tile->flag)
				return "flag";
			else return "tile_hidden";

		}

		else {

			if (determineMines(tile) == 0)
				return "tile_revealed";
			else return "number_" + std::to_string(determineMines(tile));

		}

	}

	///// Sprite Methds /////

	void revealTile(Tile* tile, std::map<std::string, sf::Texture>& res, std::vector<sf::Sprite>& midLayer, std::vector<sf::Sprite>& extras) {

		if (tile->flag || tile->revealed)
			return;

		if (tile->mine) {

			gameOver = true;

			for (Tile* t : tiles) {

				if (t->mine)
					midLayer[t->index].setTexture(res["mine"]);

			}

			extras[3].setTexture(res["face_lose"]);

			return;

		}

		chainReveal(tile);
		revealedTiles_sprites(res, midLayer);

	}
	void revealedTiles_sprites(std::map<std::string, sf::Texture>& resources, std::vector<sf::Sprite>& sprites) {

		for (Tile* t : tiles) {

			if (t->revealed) {

				if (determineMines(t) != 0)
					sprites[t->index].setTexture(resources["number_" + std::to_string(determineMines(t))]);

				else sprites[t->index].setTexture(resources["tile_revealed"]);

			}

		}

	}
	void markFlag(Tile* tile, std::map<std::string, sf::Texture>& res, std::vector<sf::Sprite>& sprites) {

		if (tile->revealed)
			return;

		if (tile->flag) {

			if (!debug && !tile->mine)
				sprites[tile->index].setTexture(res["tile_hidden"]);

			else if (debug && tile->mine)
				sprites[tile->index].setTexture(res["mine"]);

			flags--; counter++;

		}

		else {

			sprites[tile->index].setTexture(res["flag"]);
			flags++; counter--;

		}

		tile->flag = !tile->flag;

	}
	void debugClicked(std::map<std::string, sf::Texture>& res, std::vector<sf::Sprite>& sprites) {

		if (!debug) {

			for (Tile* t : tiles) {

				if (t->mine)
					sprites[t->index].setTexture(res["mine"]);

			}

		}

		else {

			for (Tile* t : tiles) {

				if (t->mine) {

					if (t->flag)
						sprites[t->index].setTexture(res["flag"]);

					else sprites[t->index].setTexture(res["tile_hidden"]);

				}

			}

		}

		debug = !debug;

	}
	void winSprites(std::map<std::string, sf::Texture>& resources, std::vector<sf::Sprite>& top, std::vector<sf::Sprite>& extras) {

		if (revealedTiles == tiles.size() - mines) {

			gameOver = true;

			for (Tile* t : tiles) {

				if (t->mine)
					top[t->index].setTexture(resources["flag"]);

				else top[t->index].setTexture(resources[determineSprite(t)]);

			}

			extras[3].setTexture(resources["face_win"]);

		}

	}

};