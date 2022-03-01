# include "Board.h"

void printSpriteSize(sf::Sprite& sprite) {

    std::cout << "Height: " << sprite.getGlobalBounds().height << std::endl;
    std::cout << "Width: " << sprite.getGlobalBounds().width << std::endl;

}
void loadResources(std::map<std::string, sf::Texture>& resources) {

    std::string tile = "images/grey-square.png";

    sf::Texture ws; ws.loadFromFile(tile);

    resources.insert(std::pair<std::string, sf::Texture>("Tile", ws));

    std::vector<std::string> pieceNames = { "Pawn","Knight","Bishop","Rook","Queen","King" };
    std::string prefix = "images/", suffix = ".png";

    for (std::string s : pieceNames) {

        std::string nameW = prefix + "W" + s + suffix;
        std::string nameB = prefix + "B" + s + suffix;

        sf::Texture pieceW; pieceW.loadFromFile(nameW);
        sf::Texture pieceB; pieceB.loadFromFile(nameB);

        resources.insert(std::pair<std::string, sf::Texture>("W" + s, pieceW));
        resources.insert(std::pair<std::string, sf::Texture>("B" + s, pieceB));

    }

}
void initializeTileSprites(Board& board, std::map<std::string, sf::Texture>& resources, 
                           std::vector<sf::Sprite>& sprites, sf::RenderWindow& window) {

    // For 600 x 700 window
    // Tile texture is 1200 x 1200
    // Tile sprites are 75 x 75

    // Keeping tiles square
    unsigned int sideLength = window.getSize().x / 8;
    float scaleFactor = (float) sideLength / resources["Tile"].getSize().x;
    
    for (unsigned int i = 0; i < board.tiles.size(); i++) {

        sf::Sprite s;

        s.setTexture(resources["Tile"]);
        s.setScale(sf::Vector2f(scaleFactor, scaleFactor));

        if (board.tiles[i]->color)
            s.setColor(sf::Color(147, 112, 219));
            
        s.setPosition((float) sideLength * board.tiles[i]->file, (float) sideLength * board.tiles[i]->rank);
        sprites.push_back(s);

    }

}
void initializePieceSprites(Board& board, std::map<std::string, sf::Texture>& resources, 
                            std::vector<sf::Sprite>& tiles, std::vector<sf::Sprite>& pieces) {

    for (unsigned int i = 0; i < board.pieceMatrix.size(); i++) {

        std::string pieceString = board.tiles[i]->piece->getPieceString();
        float scaleFactor = tiles[0].getGlobalBounds().width / resources[pieceString].getSize().x;

        sf::Sprite s;
        s.setTexture(resources[pieceString]);

        // In case adding piece type has negative consequences
        // float scaleFactor = tiles[0].getGlobalBounds().width / resources[board.getPieceString(i)].getSize().x;
        // s.setTexture(resources[board.getPieceString(i)]);


        s.setScale(sf::Vector2f(scaleFactor, scaleFactor));
        s.setPosition(tiles[i].getPosition());
        pieces.push_back(s);

    }

}
void drawSprites(std::vector<sf::Sprite>& sprites, sf::RenderWindow& window) {

    for (unsigned int i = 0; i < sprites.size(); i++)
        window.draw(sprites[i]);

}
unsigned int getClickedTileIndex(sf::Vector2i& click, sf::RenderWindow& window) {       

    if (click.y > window.getSize().x)
        return 100;

    unsigned int xmin = (unsigned int) (click.x) / (window.getSize().x / 8);
    unsigned int ymin = (unsigned int) (click.y) / ((window.getSize().y - 100) / 8);

    return (ymin * 8) + xmin;

}
bool onBoardClick(sf::Vector2i& click, sf::RenderWindow& window) {

    return (click.x >= 0 && click.x <= window.getSize().x) &&
           (click.y >= 0 && click.y <= .85 * window.getSize().y);

}
void testGetPossibleMoves(Board& board) {

    std::vector<unsigned int> m1 = board.getPossibleMoveIndices(board.tiles[56]);
    std::vector<unsigned int> m2 = board.getPossibleMoveIndices(board.tiles[62]);

    std::cout << "Rook: ";
    for (unsigned int i = 0; i < m1.size(); i++)
        std::cout << m1[i] << " ";
    std::cout << "\nKnight: ";
        for (unsigned int i = 0; i < m2.size(); i++)
            std::cout << m2[i] << " ";
}

int main()
{
    Board board = Board(); testGetPossibleMoves(board);
    sf::RenderWindow window(sf::VideoMode(600, 700), "Chess");
    
    // Fullscreen
    /*sf::RenderWindow window;
    window.create(sf::VideoMode::getFullscreenModes()[0], "Chess", sf::Style::Fullscreen);
    */

    // Sprite positions determined from top left of image

    std::map<std::string, sf::Texture> resources; 
    loadResources(resources);

    std::vector<sf::Sprite> tileSprites, pieceSprites;
    initializeTileSprites(board, resources, tileSprites, window);
    initializePieceSprites(board, resources, tileSprites, pieceSprites);
    drawSprites(tileSprites, window);
    drawSprites(pieceSprites, window);

    // Test sprites
    /*sf::Sprite testSprite1, testSprite2;
    sf::Texture testText;
    testText.loadFromFile("images/grey-square.png");
    testSprite1.setTexture(testText);
    testSprite1.setPosition(0, 0);
    testSprite1.setScale(1.2f, 1.2f);
    window.draw(testSprite1);

    std::cout << "Scale " << testSprite1.getScale().x << " " << testSprite1.getScale().y << std::endl;
    printSpriteSize(testSprite1);
    std::cout << resources["Tile"].getSize().x;*/

    window.display();

    while (window.isOpen()) {

        sf::Event event;

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::MouseButtonPressed) {

                if (event.type == sf::Mouse::Left) {

                    sf::Vector2i click = sf::Mouse::getPosition(window);

                    if (onBoardClick(click, window)) {

                        unsigned int clickedIndex = getClickedTileIndex(click, window);
                        if (board.pieceMatrix[clickedIndex] != 0) {



                        }

                    }


                }

            }

            if (event.type == sf::Event::Closed)
                window.close();

        }

    }

}