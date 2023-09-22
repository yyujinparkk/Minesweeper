#include <iostream>
#include <sstream>
#include <cctype>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include "tile.h"
using namespace std;

void Tile::loadTileTexture(string filename) {
    tileTexture.loadFromFile(filename);
}

void Tile::drawSprite(sf::RenderWindow& gameWindow) {
    //load the tile revealed texture only once during initialization, not everytime a sprite is drawn
    sf::Texture tileRevealedTexture;
    sf::Texture flagTexture;
    sf::Texture tileHiddenTexture;
    sf::Texture mineTexture;
    flagTexture.loadFromFile("files/images/flag.png");
    tileRevealedTexture.loadFromFile("files/images/tile_revealed.png");
    tileHiddenTexture.loadFromFile("files/images/tile_hidden.png");
    mineTexture.loadFromFile("files/images/mine.png");

    ifstream boardFile("files/board_config.cfg");

    string readLine;
    getline(boardFile, readLine);
    int numOfCols = stoi(readLine);
    getline(boardFile, readLine);
    int numOfRows = stoi(readLine);
    getline(boardFile, readLine);

    //if tile is clicked, reveal the other side of tile
    //if the chosen tile is a mine (if mineClicked is true), set the tile to mine.png
    if(isClicked && mineClicked){
        for (int rowNum = 0; rowNum < numOfRows; rowNum++) {
            for(int colNum = 0; colNum < numOfCols; colNum++){
                if (hasMine) {
                    mineClicked = true;
                    mineRevealed = true;

                    //have to have two separate sprites to layer, a sprite can only take in one texture
                    mineSprite.setTexture(mineTexture);
                    mineSprite.setPosition(tileSprite.getPosition());
                    //draw hidden tile first
                    gameWindow.draw(tileSprite);
                    //then layer the mine.png on top
                    gameWindow.draw(mineSprite);

                    //if the adjacent tile has no adjacent mines, recursively reveal its neighbors
                    /*if (tile->value == 0) {
                        tile->revealAdjacentMines();
                    }*/
                }
            }
        }
    }

    else if(isClicked){
        //if a regulalr tile is clicked instead of one w a mine, draw the revealed tile
        tileSprite.setTexture(tileRevealedTexture);
        gameWindow.draw(tileSprite);
    }
    else if(isRightClicked){
        isClicked = false;
        hasFlag = true;
        tileSprite.setTexture(tileHiddenTexture);
        flagSprite.setTexture(flagTexture);
        flagSprite.setPosition(tileSprite.getPosition());
        gameWindow.draw(tileSprite);
        //then layer the flag.png on top
        gameWindow.draw(flagSprite);
    }
    else if(hasFlag && isRightClicked){
        isClicked = false;
        isRightClicked = false;
        hasFlag = false;
        //tileHiddenSprite.setTexture(tileHiddenTexture);
        //gameWindow.draw(tileSprite);
    }
    else{
        gameWindow.draw(tileSprite);
    }
}

void Tile::drawSpriteRevealed(sf::RenderWindow &gameWindow) {
    sf::Texture tileRevealedTexture;
    tileRevealedTexture.loadFromFile("files/images/tile_revealed.png");
    revealedSprite.setTexture(tileRevealedTexture);
    gameWindow.draw(revealedSprite);
}

void Tile::drawSpriteMine(sf::RenderWindow &gameWindow) {
    sf::Texture mineTexture;
    mineTexture.loadFromFile("files/images/mine.png");
    mineSprite.setTexture(mineTexture);
    gameWindow.draw(mineSprite);
}

void Tile::drawSpriteHappyFace(sf::RenderWindow &gameWindow) {
    happyFaceTexture.loadFromFile("files/images/face_happy.png");
    happyFaceSprite.setTexture(happyFaceTexture);
    loseFaceTexture.loadFromFile("files/images/face_lose.png");
    loseFaceSprite.setTexture(loseFaceTexture);
    //sets lose face pos to be directly on top of happy face
    loseFaceSprite.setPosition(happyFaceSprite.getPosition());
    if(mineClicked){
        gameWindow.draw(loseFaceSprite);
    }
    else{
        gameWindow.draw(happyFaceSprite);
    }
}

void Tile::drawSpriteLoseFace(sf::RenderWindow &gameWindow) {
    loseFaceTexture.loadFromFile("files/images/face_lose.png");
    loseFaceSprite.setTexture(loseFaceTexture);
    gameWindow.draw(loseFaceSprite);
}

void Tile::drawSpriteDebug(sf::RenderWindow &gameWindow) {
    sf::Texture debugTexture;
    debugTexture.loadFromFile("files/images/debug.png");
    //just a temp to see if clicking is working
    debugSprite.setTexture(debugTexture);

    //if tile is clicked, reveal the other side of tile
    if (isClicked) {
        debugSprite.setTexture(debugTexture);
    }

    gameWindow.draw(debugSprite);
}

void Tile::drawSpritePlay(sf::RenderWindow &gameWindow) {
    sf::Texture playTexture;
    sf::Texture pauseTexture;
    playTexture.loadFromFile("files/images/play.png");
    //just a temp to see if clicking is working
    pauseTexture.loadFromFile("files/images/pause.png");
    playSprite.setTexture(playTexture);

    if (isClicked) {
        playSprite.setTexture(pauseTexture);
    }

    gameWindow.draw(playSprite);
}

void Tile::drawSpritePause(sf::RenderWindow &gameWindow) {
    sf::Texture pauseTexture;
    pauseTexture.loadFromFile("files/images/pause.png");

    gameWindow.draw(pauseSprite);
}

void Tile::drawSpriteLeaderBoard(sf::RenderWindow &gameWindow) {
    sf::Texture leaderBoardTexture;
    //sf::Texture hFClicked;
    leaderBoardTexture.loadFromFile("files/images/leaderboard.png");
    //just a temp to see if clicking is working
    //hFClicked.loadFromFile("files/images/face_win.png");
    leaderBoardSprite.setTexture(leaderBoardTexture);

    //if tile is clicked, reveal the other side of tile
    if (isClicked) {
        leaderBoardSprite.setTexture(leaderBoardTexture);
    }

    gameWindow.draw(leaderBoardSprite);
}

void Tile::drawSpriteFlag(sf::RenderWindow &gameWindow) {
    flagTexture.loadFromFile("files/images/flag.png");
    flagSprite.setTexture(flagTexture);
    if (isRightClicked) {
        hasFlag = true;
        flagSprite.setPosition(tileSprite.getPosition());
        gameWindow.draw(flagSprite);
    }
}

void Tile::drawSpriteDigit1(sf::RenderWindow &gameWindow) {
    digit1Texture.loadFromFile("files/images/number_1.png");
    digit1Sprite.setTexture(digit1Texture);
    hasNumber = true;
    if(isClicked){
        digit1Sprite.setPosition(tileSprite.getPosition());
        gameWindow.draw(digit1Sprite);
    }
}

void Tile::drawSpriteDigit2(sf::RenderWindow &gameWindow) {
    digit2Texture.loadFromFile("files/images/number_2.png");
    digit2Sprite.setTexture(digit2Texture);
    hasNumber = true;
    if(isClicked){
        digit2Sprite.setPosition(tileSprite.getPosition());
        gameWindow.draw(digit2Sprite);
    }
}

void Tile::drawSpriteDigit3(sf::RenderWindow &gameWindow) {
    digit3Texture.loadFromFile("files/images/number_3.png");
    digit3Sprite.setTexture(digit3Texture);
    hasNumber = true;
    if(isClicked){
        digit3Sprite.setPosition(tileSprite.getPosition());
        gameWindow.draw(digit3Sprite);
    }
}

void Tile::drawSpriteDigit4(sf::RenderWindow &gameWindow) {
    digit4Texture.loadFromFile("files/images/number_4.png");
    digit4Sprite.setTexture(digit4Texture);
    hasNumber = true;
    if(isClicked){
        digit4Sprite.setPosition(tileSprite.getPosition());
        gameWindow.draw(digit4Sprite);
    }
}

void Tile::drawSpriteDigit5(sf::RenderWindow &gameWindow) {
    digit5Texture.loadFromFile("files/images/number_5.png");
    digit5Sprite.setTexture(digit5Texture);
    hasNumber = true;
    if(isClicked){
        digit5Sprite.setPosition(tileSprite.getPosition());
        gameWindow.draw(digit5Sprite);
    }
}


void Tile::setTexture() {
    tileSprite.setTexture(tileTexture);
}


void Tile::setHappyFaceTexture() {
    happyFaceSprite.setTexture(happyFaceTexture);
}

//mouse position for a regular tile
bool Tile::mousePositionInBounds(float x, float y) {
    //auto takes in a return type from sfml
    auto tileBounds = tileSprite.getGlobalBounds();
    //if mouse click is within bounds, return true2
    if(tileBounds.contains(x, y)){
        cout << x << "boundX" << endl;
        cout << y << "boundY" << endl;
        //if the tile that is clicked has a mine, mineClicked = true
        if(hasMine && !isRightClicked){
            mineClicked = true;
            //gameWindow.draw(mineSprite);
        }
        if(hasFlag){
            isRightClicked = true;
            isClicked = false;
        }
        //if isClicked is true, will load tile revealed png
        if(!hasMine && !isRightClicked){
            isClicked = true;
        }
        return true;
    }
    return false;
}

bool Tile::mousePositionInBoundsRight(float x, float y) {
    //auto takes in a return type from sfml
    auto tileRightBounds = tileSprite.getGlobalBounds();
    //if mouse click is within bounds, return true2
    if(tileRightBounds.contains(x, y)){
        cout << x << "boundX" << endl;
        cout << y << "boundY" << endl;
        //if the tile that is clicked has a mine, mineClicked = true
        //if isClicked is true, will load tile revealed png
        isRightClicked = true;
        hasFlag = true;
        return true;
    }
    return false;
}

bool Tile::mousePosInBoundsHappyFace(float x, float y) {
    //auto takes in a return type from sfml
    auto happyFaceBounds = happyFaceSprite.getGlobalBounds();
    //if mouse click is within bounds, return true
    if(happyFaceBounds.contains(x, y)){
        //if isClicked is true, will load tile revealed png
        /////////////////////
        //isClicked = true;
        return true;
    }
    return false;
}

bool Tile::mousePosInBoundsDebug(float x, float y) {
    auto debugBounds = debugSprite.getGlobalBounds();
    if(debugBounds.contains(x, y)){
        isClicked = true;
        return true;
    }
    return false;
}

bool Tile::mousePosInBoundsPlay(float x, float y) {
    auto playBounds = playSprite.getGlobalBounds();
    if(playBounds.contains(x, y)){
        isClicked = true;
        return true;
    }
    return false;
}

bool Tile::mousePosInBoundsPause(float x, float y) {
    auto pauseBounds = pauseSprite.getGlobalBounds();
    if(pauseBounds.contains(x, y)){
        isClicked = true;
        return true;
    }
    return false;
}

bool Tile::mousePosInBoundsLeaderBoard(float x, float y) {
    int widthLB = numOfCols * 16;
    int heightLB = (numOfRows * 16) + 50;
    cout << widthLB << "width" << endl;

    sf::Font font;
    font.loadFromFile("files/font.ttf");

    sf::Text textLB("LEADERBOARD", font, 20);
    textLB.setStyle(sf::Text::Underlined | sf::Text::Bold);
    //textLB.setFillColor(sf::Color::White);
    textLB.setPosition(widthLB/3, heightLB/2 - 120);


    sf::Text leaderboardText;
    leaderboardText.setFont(font);
    leaderboardText.setCharacterSize(18);
    leaderboardText.setFillColor(sf::Color::White);
    leaderboardText.setStyle(sf::Text::Bold);

    //read file
    ifstream leaderboardFile("files/leaderboard.txt");
    stringstream buffer;
    buffer << leaderboardFile.rdbuf();
    string fileContent = buffer.str();

    //adds empty line after each name in file
    //size_t type represents size of object in bytes to acccurately represent size of data
    size_t pos = 0;
    while ((pos = fileContent.find("\n", pos)) != std::string::npos) {
        fileContent.insert(pos + 1, "\n");
        pos += 2; // Move to the next line
    }

    leaderboardText.setString(fileContent);
    sf::FloatRect textRect = leaderboardText.getLocalBounds();
    leaderboardText.setPosition(widthLB/2 - 60,heightLB/2 - 80);

    auto leaderBoardBounds = leaderBoardSprite.getGlobalBounds();
    if (leaderBoardBounds.contains(x, y)) {
        sf::RenderWindow leaderBoardWindow(sf::VideoMode(widthLB, heightLB), "LeaderBoard", sf::Style::Close);

        isClicked = true;
        cout << numOfCols << "num of cols! " << endl;

        //sf::RenderWindow leaderBoardWindow(sf::VideoMode(numOfCols * 16, (numOfRows * 16) + 50), "LeaderBoard", sf::Style::Close);

        // Enter the event loop for the new window
        while (leaderBoardWindow.isOpen()) {
            sf::Event event;
            while (leaderBoardWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    leaderBoardWindow.close();
                }
            }

            leaderBoardWindow.clear(sf::Color::Blue);
            leaderBoardWindow.draw(textLB);
            leaderBoardWindow.draw(leaderboardText);
            leaderBoardWindow.display();
        }

        //return false because we've handled the click event and opened a new window
        return false;
    }
    return false;
}

bool Tile::mousePositionInBoundsMine(float x, float y) {
    auto mineBounds = mineSprite.getGlobalBounds();
    if(mineBounds.contains(x, y)){
        isClicked = true;
        return true;
    }
    return false;
}

Tile::Tile() {
    this->hasFlag = false;
    this->hasMine = false;
    hidden = true;
    numOfAdjacentMines = 0;
    flagged = false;
    freeze = false;
    x = 0;
    y = 0;
    ifstream boardFile("files/board_config.cfg");

    string readLine;
    getline(boardFile, readLine);
    numOfCols = stoi(readLine);
    //cout << numOfCols << "UHIDSOFOHWEIHFIHWFHOIFWO";
    getline(boardFile, readLine);
    numOfRows = stoi(readLine);
    getline(boardFile, readLine);
}

Tile::Tile(int x, int y, bool hasMine, bool hasFlag, bool hidden, int numOfAdjacentMines, int numOfRows, int numOfCols) {
    this->x = x;
    this->y = y;
    this->hasMine = hasMine;
    this->hasFlag = hasFlag;
    this->hidden = hidden;
    this->numOfAdjacentMines = numOfAdjacentMines;
    this->numOfRows = numOfRows;
    this->numOfCols = numOfCols;
}


Tile::Tile(string filename, float scale, vector<Tile *> adjacentTiles, vector<vector<Tile>> adjTile) {
    mineTexture.loadFromFile("files/images/mine.png");
    hiddenTexture.loadFromFile("files/images/tile_hidden.png");

    mineSprite.setTexture(mineTexture);
    hiddenSprite.setTexture(hiddenTexture);
    loadTileTexture(filename);
    setTexture();
    //set up tile scales to be the same for x and y
    tileSprite.scale(scale, scale);
}

Tile::Tile(string filename, float scale) {
    mineTexture.loadFromFile("files/images/mine.png");
    hiddenTexture.loadFromFile("files/images/tile_hidden.png");

    mineSprite.setTexture(mineTexture);
    hiddenSprite.setTexture(hiddenTexture);
    loadTileTexture(filename);
    setTexture();
    //set up tile scales to be the same for x and y
    tileSprite.scale(scale, scale);
}

void Tile::revealALlMines(vector<Tile *> &adjacentTiles) {

    for (Tile* tile : adjacentTiles) {
        //if the tile contains a mine and it's not already revealed, reveal it
        if (tile->hasMine) {
            tile->isClicked = true;
            tile->mineClicked = true;
            tile->mineRevealed = true;
            hiddenSprite.setTexture(hiddenTexture);
            tileSprite.setTexture(mineTexture);
        }
    }
}

void Tile::resetTiles(){
    //isClicked = false means that all the tiles will stay as is, which is the hidden form, so in order to reset all the tiles (bring them back to their hidden form), you must make the boolean = to false
    //putting isClicked equal to true will output the revealed version of the tiles
    isClicked = false;
    isRightClicked = false;
    //reload the hidden tile texture and set it as the current texture
    tileTexture.loadFromFile("files/images/tile_hidden.png");
    tileSprite.setTexture(tileTexture);
    //revealALlMines(adjacentTiles);
}

void Tile::resetHappyFace(){
    //mineclicked = false means to reset the button to its default form (happy face)
    mineClicked = false;
}


void Tile::drawSpriteTimer(sf::RenderWindow &gameWindow) {

}

bool Tile::mousePosInBoundsTimer(float x, float y) {
    return false;
}

void Tile::randomizeMines(vector<Tile *> &adjacentTiles, int numMines, std::mt19937 &rng) {
    int totalTiles = adjacentTiles.size();

    for (Tile* tile : adjacentTiles) {
        tile->resetTilesAfterClickingHF();
    }

    //makes sure numMines does not exceed the total number of tiles
    if (numMines > totalTiles)
        numMines = totalTiles;

    //create copy of the vector to shuffle
    vector<Tile*> shuffledTiles = adjacentTiles;

    //shuffle the copied vector using the provided random number generator
    std::shuffle(shuffledTiles.begin(), shuffledTiles.end(), rng);

    //set first 'numMines' tiles from the shuffled vector as containing mines
    for (int i = 0; i < numMines; ++i) {
        shuffledTiles[i]->setMine();
    }
}//revert everything back to the starting positions

void Tile::resetTilesAfterClickingHF() {
    hasMine = false;
    isClicked = false;
    isRightClicked = false;
    hasFlag = false;
    mineClicked = false;
    mineRevealed = false;
}


//returns a vector containing pointers to the adjacent tiles of the specified tile
bool Tile::gameLost(vector<Tile*>& adjTiles, int row, int col){
    Tile inst;
    int totalCols = inst.numOfCols;
    //curent index
    int index = row * totalCols + col;
    if (adjTiles[index]->hasMine){
        gameFinished = true;
        return true;
    }
    return false;
}
