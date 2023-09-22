#include <iostream>
#include <sstream>
#include <cctype>
#include <random>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
using namespace std;

class Tile{
public:
    vector<vector<Tile>> adjTiles;
    vector<vector<sf::Sprite>> topLayer;
    bool hidden;
    bool flagged;
    bool debug;
    int numOfAdjacentMines;
    int height;
    int width;
    bool freeze;
    int x;
    int y;
    int numOfRows;
    int numOfCols;


    //constructors
    Tile();
    Tile(int x, int y, bool hasMine,bool hasFlag, bool hidden, int adjacentMines, int numOfRows, int numOfCols);
    Tile(string filename);
    //might not need this, depends on if I use scales or not
    Tile(string filename, float scale);

    Tile(string basicString, float scale, vector<Tile *> adjacentTiles, vector<vector<Tile>> adjTile);

    vector<Tile*> adjacentTiles;


    sf::Sprite tileSprite;
    sf::Sprite mineSprite;
    sf::Sprite tileHiddenSprite;
    sf::Sprite hiddenSprite;
    sf::Sprite revealedSprite;
    sf::Sprite happyFaceSprite;
    sf::Sprite loseFaceSprite;
    sf::Sprite debugSprite;
    sf::Sprite playSprite;
    sf::Sprite pauseSprite;
    sf::Sprite leaderBoardSprite;
    sf::Sprite timer;
    sf::Sprite flagSprite;

    sf::Sprite digit1Sprite;
    sf::Texture digit1Texture;
    sf::Sprite digit2Sprite;
    sf::Texture digit2Texture;
    sf::Sprite digit3Sprite;
    sf::Texture digit3Texture;
    sf::Sprite digit4Sprite;
    sf::Texture digit4Texture;
    sf::Sprite digit5Sprite;
    sf::Texture digit5Texture;
    sf::Sprite digit6Sprite;
    sf::Texture digit6Texture;
    sf::Sprite digit7Sprite;
    sf::Texture digit7Texture;
    sf::Sprite digit8Sprite;
    sf::Texture digit8Texture;


    sf::Texture tileTexture;
    sf::Texture mineTexture;
    sf::Texture hiddenTexture;
    //idk if this does anythibg
    sf::Texture happyFaceTexture;
    sf::Texture loseFaceTexture;
    sf::Texture flagTexture;


    int value = 0;
    int numOfAdjMinesMain = 0;
    //turns true when tile is clicked
    bool isClicked = false;
    bool isClickedRecursion = false;
    bool isRevealed = false;
    bool isClickedBlank = false;
    //checks whether tile clicked has a mine or not
    bool hasMine = false;
    //turns true when tile is clicked
    bool mineClicked = false;
    bool mineRevealed = false;
    bool originalState;
    bool isVisited = false;
    bool isCountedFor = false;
    bool gameFinished = false;
    bool hasFlag = false;
    bool isRightClicked = false;
    bool hasNumber = false;
    bool isClickedOnce = false;
    bool gameLost(vector<Tile*>& adjTiles, int x, int y);


    //functions
    void loadTileTexture(string filename);
    //default behavior
    void setTexture();
    //is this right???
    void setHappyFaceTexture();
    void drawSprite(sf::RenderWindow &gameWindow);
    void drawSpriteRevealed(sf::RenderWindow &gameWindow);
    void drawSpriteMine(sf::RenderWindow &gameWindow);
    void drawSpriteHappyFace(sf::RenderWindow &gameWindow);
    void drawSpriteLoseFace(sf::RenderWindow &gameWindow);
    void drawSpriteDebug(sf::RenderWindow &gameWindow);
    void drawSpritePlay(sf::RenderWindow &gameWindow);
    void drawSpritePause(sf::RenderWindow &gameWindow);
    void drawSpriteLeaderBoard(sf::RenderWindow &gameWindow);
    void drawSpriteTimer(sf::RenderWindow &gameWindow);
    void drawSpriteDigit1(sf::RenderWindow &gameWindow);
    void drawSpriteDigit2(sf::RenderWindow &gameWindow);
    void drawSpriteDigit3(sf::RenderWindow &gameWindow);
    void drawSpriteDigit4(sf::RenderWindow &gameWindow);
    void drawSpriteDigit5(sf::RenderWindow &gameWindow);
    void drawSpriteFlag(sf::RenderWindow &gameWindow);

    void toggleFlag() {
        hasFlag = !hasFlag;
    }

    bool hasFlagged() const {
        return hasFlag;
    }

    bool mousePositionInBoundsRight(float x, float y);

    void resetTiles();
    void resetHappyFace();
    void resetTilesAfterClickingHF();
    void setMine() {
        hasMine = true;
    }
    void revealALlMines(vector<Tile*>& adjacentTiles);
    void randomizeMines(vector<Tile*>& adjacentTiles, int numMines, std::mt19937& rng);
    void checkAdjacentMines(vector<Tile*>& adjacentTiles);
    void startRecursion(vector<vector<int>>& adjNum);
    void endGame();

    //function to get number of adjacent mines
    //vector<Tile*> returnVectorOfAdjMines(vector<Tile*>& adjTiles, int row, int col);
    void revealTilesWithZeroAdjMines(vector<Tile*>& adjTiles, int row, int col);
    int countNumOfAdjMines(vector<Tile*>& adjTiles, int row, int col);
    void returnNumOfAdjMines(sf::RenderWindow &gameWindow);
    int getNumOfAdjMines();

    //booleans
    //checking whether mouse is in bounds or not
    bool mousePositionInBounds(float x, float y);
    bool mousePositionInBoundsMine(float x, float y);
    bool mousePosInBoundsHappyFace(float x, float y);
    bool mousePosInBoundsDebug(float x, float y);
    bool mousePosInBoundsPlay(float x, float y);
    bool mousePosInBoundsPause(float x, float y);
    bool mousePosInBoundsLeaderBoard(float x, float y);
    bool mousePosInBoundsTimer(float x, float y);

};