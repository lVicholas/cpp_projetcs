#include "Board.h"

void initializeTopLayer(Board&, std::map<std::string, sf::Texture>&, std::vector<sf::Sprite>&);
void initializeMidLayer(Board&, std::map<std::string, sf::Texture>&, std::vector<sf::Sprite>&);
void initializeBottom(Board&, std::map<std::string, sf::Texture>&, std::vector<sf::Sprite>&);
void buttonsAndCounter(Board&, std::map<std::string, sf::Texture>&, std::vector<sf::Sprite>&);
void loadResources(std::map<std::string, sf::Texture>&);
void loadBoards(std::vector<std::string>&);
bool checkArea(sf::Vector2f, sf::Vector2f);
int buttonClicked(sf::Vector2i, std::vector<sf::Sprite>&);
void updateCounter(Board&, std::map<std::string, sf::Texture>&, std::vector<sf::Sprite>&);
void updateTopLayer(Board&, std::map<std::string, sf::Texture>&, std::vector<sf::Sprite>&);
void updateMidLayer(Board&, std::map<std::string, sf::Texture>&, std::vector<sf::Sprite>&);
void printBoard(Board&, std::vector<sf::Sprite>&, std::vector<sf::Sprite>&, std::vector<sf::Sprite>&, std::vector<sf::Sprite>&, sf::RenderWindow&);

int main() {

	srand(time(0));

	Board board = Board();
	std::map<std::string, sf::Texture> resources; loadResources(resources);
	std::vector<std::string> boards; loadBoards(boards);

	sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");

	/*

	Top Layer: Mines and flags
	Mid Layer: Hidden tiles and numbers
	Bottom Layer: Revealed tiles
	Extras: Counter and buttons

	*/

	std::vector<sf::Sprite> midLayer, bottomLayer, topLayer, extras;
	initializeTopLayer(board, resources, topLayer);
	initializeMidLayer(board, resources, midLayer);
	initializeBottom(board, resources, bottomLayer);
	buttonsAndCounter(board, resources, extras);

	window.display();

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed) {

				if (event.mouseButton.button == sf::Mouse::Left) {

					if (board.onBoard(sf::Mouse::getPosition(window)) && !board.gameOver) {

						Tile* target = board.getClickedBoi(sf::Mouse::getPosition(window));
						board.revealTile(target, resources, midLayer, extras);
						updateTopLayer(board, resources, topLayer);

					}

					else {

						int button = buttonClicked(sf::Mouse::getPosition(window), extras);

						if (button == 0) {

							board.reset();
							initializeMidLayer(board, resources, midLayer);
							initializeTopLayer(board, resources, topLayer);
							buttonsAndCounter(board, resources, extras);

						}

						if (button == 1 && !board.gameOver) {

							board.debugClicked(resources, topLayer);
							updateTopLayer(board, resources, topLayer);

						}

						else if (button == 2 && !board.gameOver) {

							board.testBoard(boards[0], resources, midLayer);
							initializeMidLayer(board, resources, midLayer);
							initializeTopLayer(board, resources, topLayer);
							buttonsAndCounter(board, resources, extras);

						}

						else if (button == 3 && !board.gameOver) {

							board.testBoard(boards[1], resources, midLayer);
							initializeMidLayer(board, resources, midLayer);
							initializeTopLayer(board, resources, topLayer);
							buttonsAndCounter(board, resources, extras);

						}

						else if (button == 4 && !board.gameOver) {

							board.testBoard(boards[2], resources, midLayer);
							initializeMidLayer(board, resources, midLayer);
							initializeTopLayer(board, resources, topLayer);
							buttonsAndCounter(board, resources, extras);


						}

					}

				}

				else if (event.mouseButton.button == sf::Mouse::Right) {

					if (board.onBoard(sf::Mouse::getPosition(window)) && !board.gameOver) {

						Tile* target = board.getClickedBoi(sf::Mouse::getPosition(window));
						board.markFlag(target, resources, topLayer);
						updateTopLayer(board, resources, topLayer);

					}

				}

			}

			if (board.revealedTiles == board.tiles.size() - board.mines)
				board.winSprites(resources, topLayer, extras);

			else if (board.gameOver) {

				for (unsigned int x = 0; x < board.tiles.size(); x++) {

					if (board.tiles[x]->mine)
						topLayer[x].setTexture(resources["mine"]);

				}

			}

			window.clear();

			updateCounter(board, resources, extras);
			printBoard(board, topLayer, midLayer, bottomLayer, extras, window);

		}

	}

	return 0;

}
void loadResources(std::map<std::string, sf::Texture>& resources) {

	std::vector<std::string> names = { "debug", "digits", "face_happy", "face_lose",
									   "face_win", "flag", "mine", "number_1", "number_2",
									   "number_3", "number_4", "number_5", "number_6", "number_7",
									   "number_8", "test_1", "test_2", "Test_3", "tile_hidden", "tile_revealed" };

	std::string pre = "images/", suf = ".png";

	for (std::string s : names) {

		std::string anew = s;
		anew.insert(0, pre); anew = anew + suf;
		sf::Texture t;
		t.loadFromFile(anew);
		resources.insert(std::pair<std::string, sf::Texture>(s, t));

	}

}
void loadBoards(std::vector<std::string>& boards) {

	std::string files = "boards/testboard";

	for (unsigned int x = 1; x <= 3; x++) {

		std::string file = files + std::to_string(x) + ".brd";
		std::string buffer, last;

		std::ifstream stream(file);

		while (std::getline(stream, buffer))
			last = last + buffer;

		boards.push_back(last);

	}

}
void initializeTopLayer(Board& board, std::map<std::string, sf::Texture>& resources, std::vector<sf::Sprite>& sprites) {

	if (sprites.size() > 1)
		sprites.clear();

	unsigned int row, col; row = col = 0;
	for (unsigned int x = 0; x < board.tiles.size(); x++) {

		sf::Sprite s;

		if (board.tiles[x]->mine)
			s.setTexture(resources["mine"]);

		s.setPosition(col * board.tileW, row * board.tileH);
		sprites.push_back(s);

		if ((x + 1) % 25 == 0) {

			col = 0;
			row++;

		}
		else col++;

	}

}
void initializeMidLayer(Board& board, std::map<std::string, sf::Texture>& resources, std::vector<sf::Sprite>& sprites) {

	if (sprites.size() > 1)
		sprites.clear();

	unsigned int col, row; col = row = 0;
	for (unsigned int x = 0; x < board.tiles.size(); x++) {

		sf::Sprite s(resources["tile_hidden"]);
		s.setPosition(col * board.tileW, row * board.tileH);
		sprites.push_back(s);

		if ((x + 1) % 25 == 0) {

			col = 0;
			row++;

		}
		else col++;

	}

}
void initializeBottom(Board& board, std::map<std::string, sf::Texture>& resources, std::vector<sf::Sprite>& sprites) {

	if (sprites.size() > 1)
		sprites.clear();

	unsigned int col, row; col = row = 0;
	for (unsigned int x = 0; x < board.w * board.h; x++) {

		sf::Sprite s(resources["tile_revealed"]);
		s.setPosition(col * board.tileW, row * board.tileH);
		sprites.push_back(s);

		if ((x + 1) % 25 == 0) {

			col = 0;
			row++;

		}
		else col++;

	}

}
void buttonsAndCounter(Board& board, std::map<std::string, sf::Texture>& resources, std::vector<sf::Sprite>& sprites) {

	if (sprites.size() > 1)
		sprites.clear();

	unsigned int y = board.h * board.tileH, x = 0;
	sf::Sprite nega(resources["digits"]), num1(resources["digits"]), num2(resources["digits"]),
		face(resources["face_happy"]), debu(resources["debug"]),
		tes1(resources["test_1"]), tes2(resources["test_2"]), tes3(resources["Test_3"]);

	nega.setTextureRect(sf::IntRect(210, 0, 21, 32));
	num1.setTextureRect(sf::IntRect(21 * (board.counter / 10), 0, 21, 32));
	num2.setTextureRect(sf::IntRect(21 * (board.counter % 10), 0, 21, 32));

	nega.setPosition(x, y); x = x + 21;
	num1.setPosition(x, y); x = x + 21;
	num2.setPosition(x, y); x = 336;
	face.setPosition(x, y); x = x + 128;
	debu.setPosition(x, y); x = x + 64;
	tes1.setPosition(x, y); x = x + 64;
	tes2.setPosition(x, y); x = x + 64;
	tes3.setPosition(x, y); x = x + 64;

	sprites.push_back(nega); sprites.push_back(num1); sprites.push_back(num2);
	sprites.push_back(face); sprites.push_back(debu);
	sprites.push_back(tes1); sprites.push_back(tes2); sprites.push_back(tes3);

}
bool checkArea(sf::Vector2i click, sf::Vector2f sprite) {

	return (click.x >= sprite.x && click.x <= sprite.x + 64 && click.y >= sprite.y && click.y <= sprite.y + 64);

}
int  buttonClicked(sf::Vector2i pos, std::vector<sf::Sprite>& sprites) {

	std::vector<sf::Vector2f> positions = { sprites[3].getPosition(), sprites[4].getPosition(),
											sprites[5].getPosition(), sprites[6].getPosition(), sprites[7].getPosition() };

	for (unsigned int x = 0; x < positions.size(); x++) {

		if (checkArea(pos, positions[x]))
			return x;

	}

	return -1;

}
void updateCounter(Board& board, std::map<std::string, sf::Texture>& resources, std::vector<sf::Sprite>& buttons) {

	buttons[1].setTextureRect(sf::IntRect(21 * (std::abs(board.counter) / 10), 0, 21, 32));
	buttons[2].setTextureRect(sf::IntRect(21 * (std::abs(board.counter) % 10), 0, 21, 32));

}
void updateTopLayer(Board& board, std::map<std::string, sf::Texture>& resources, std::vector<sf::Sprite>& top) {

	for (unsigned int x = 0; x < board.tiles.size(); x++) {

		if (board.tiles[x]->flag && !board.debug)
			top[x].setTexture(resources["flag"]);

		else if (board.debug && board.tiles[x]->mine)
			top[x].setTexture(resources["mine"]);

	}

}
void updateMidLayer(Board& board, std::map<std::string, sf::Texture>& resources, std::vector<sf::Sprite>& top) {

	for (unsigned int x = 0; x < board.tiles.size(); x++) {

		if (!board.tiles[x]->revealed)
			top[x].setTexture(resources["tile_hidden"]);

		else if (board.determineMines(board.tiles[x]) != 0)
			top[x].setTexture(resources["number_" + std::to_string(board.determineMines(board.tiles[x]))]);
	}

}
void printBoard(Board& board, std::vector<sf::Sprite>& top, std::vector<sf::Sprite>& mid, std::vector<sf::Sprite>& bot, std::vector<sf::Sprite>& ext, sf::RenderWindow& window) {

	for (unsigned int x = 0; x < bot.size(); x++)
		window.draw(bot[x]);

	for (unsigned int x = 0; x < mid.size(); x++)
		window.draw(mid[x]);

	for (unsigned int x = 0; x < top.size(); x++) {

		if ((board.tiles[x]->mine && board.debug) || board.tiles[x]->flag || (board.gameOver && board.tiles[x]->mine))
			window.draw(top[x]);

	}

	for (unsigned int x = 0; x < ext.size(); x++) {

		if (x == 0 && board.counter >= 0)
			continue;

		window.draw(ext[x]);

	}

	window.display();

}