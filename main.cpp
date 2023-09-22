#include <iostream>
#include <cctype>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <random>
#include <fstream>
#include "tile.h"
using namespace std;


void setText(sf::Text &welcomeText, float x, float y) {
    sf::FloatRect textRect = welcomeText.getLocalBounds();
    welcomeText.setOrigin(textRect.left + textRect.width / 2.0f,textRect.top + textRect.height / 2.0f);
    welcomeText.setPosition(sf::Vector2f(x, y));
}


//function to randomly generate mines on the game board
void randomizeMines(vector<Tile*>& adjacentTiles, int numMines, std::mt19937& rng) {
    for (Tile *tile : adjacentTiles) {
        tile->originalState = true;
    }

    int totalTiles = adjacentTiles.size();

    //ensure numMines does not exceed the total number of tiles
    if (numMines > totalTiles)
        numMines = totalTiles;

    //create a copy of the vector to shuffle
    vector<Tile*> shuffledTiles = adjacentTiles;

    //shuffle the copied vector using the provided random number generator
    std::shuffle(shuffledTiles.begin(), shuffledTiles.end(), rng);

    //set the first 'numMines' tiles from the shuffled vector as containing mines
    for (int i = 0; i < numMines; ++i) {
        shuffledTiles[i]->setMine();
    }
}

void iterateTiles(string adjTileFileName, float tileScale, vector<Tile*>& adjacentTiles){
    Tile temp;
    int maxNumOfAdjTiles = 400;
    float tileSpacing = 32.0f;
    for(int rowNum = 0; rowNum < temp.numOfRows; rowNum++){
        for(int colNum = 0; colNum < temp.numOfCols; colNum++){
            adjTileFileName = "files/images/tile_hidden.png";
            tileScale = 0.97f;
            //create an instance of tile class to push into vector
            //dynamically allocate memory for the Tile object so tempTile doesn't go out of scope when exits the function
            Tile* tempTile = new Tile(adjTileFileName, tileScale);
            //take each tile sprite from the temp tile vector and sets its position side by side
            //i * tileSpacing takes the length of all the alr exisiting tiles on board, then adds the space need to insert the new tile
            tempTile->tileSprite.setPosition( colNum  * tileSpacing, 0.0f + (rowNum * tileSpacing));
            adjacentTiles.push_back(tempTile);
        }
    }
}

vector<Tile*>returnVectorOfAdjMines(vector<Tile*>& adjTiles, int row, int col) {
    Tile tempInstance;
    vector<Tile*> storeAdjacentTiles;
    //reset isCounterFor the current tile
    bool isCountedFor = false;
    //maybe i dont need to take instance of Tile...
    int totalRows = tempInstance.numOfRows;
    int totalCols = tempInstance.numOfCols;
    int currentIndex = row * totalCols + col;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            cout << row << "row hwereee!!!!" << endl;
            cout << col << "col hwereee!!!!" << endl;
            //adjacentX and adjacentY are the x and y coordinates of the adjacent tiles to the one that was clicked on
            //row and col are the coordinates of the current tile
            int adjacentX = row + dx;
            int adjacentY = col + dy;
            cout << "row " << adjacentX << endl;
            cout << "column " << adjacentY << endl;
            cout << totalRows << "rows here" << endl;
            //skip the current tile itself
            if (dx == 0 && dy == 0) {
                continue;
            }

            //ensure the adjacent tile is within the grid boundaries
            if (adjacentX >= 0 && adjacentX < totalRows && adjacentY >= 0 && adjacentY < totalCols) {
                //convert 2D indices to 1D index
                int index = adjacentX * totalCols + adjacentY;
                //int mines = adjTiles[index]->countNumOfAdjMines(adjTiles, row,  col);
                cout << "ROWSSSSSS" << row << "   " << "COLSSSSS" << col << endl;
                cout << "#" << index << " tile" << endl;
                storeAdjacentTiles.push_back(adjTiles[index]);
                //returnVectorOfAdjMines(adjTiles, adjacentX, adjacentY);
            }
        }
    }

    return storeAdjacentTiles;
}

bool newBoolIDK;
bool hi;

int countNumOfAdjMines(vector<Tile*>& adjTiles, int row, int col) {
    Tile instance;
    //get the vector containing pointers to the adjacent tiles
    int totalRows = instance.numOfRows;
    int totalCols = instance.numOfCols;
    vector<Tile *> storeAdjacentTiles = returnVectorOfAdjMines(adjTiles, row, col);

    int numOfAdjacentMines = 0;

    //iterate through adjacent tiles
    for (Tile *adjacentTile: storeAdjacentTiles) {
        if (adjacentTile->hasMine) {
            numOfAdjacentMines++;
        }
    }

    if(numOfAdjacentMines > 0){
        instance.isClickedOnce = true;
        newBoolIDK = true;
    }
    if(numOfAdjacentMines == 0) {
        for (Tile *adjacentTile: storeAdjacentTiles) {
            if (!adjacentTile->isClicked) {
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        //adjacentX and adjacentY are the x and y coordinates of the adjacent tiles to the one that was clicked on
                        int adjacentX = row + dx;
                        int adjacentY = col + dy;
                        cout << "column " << adjacentY << endl;
                        cout << totalRows << "rows here" << endl;
                        //skip the current tile itself
                        if (dx == 0 && dy == 0) {
                            continue;
                        }

                        //ensure the adjacent tile is within the grid boundaries
                        if (adjacentX >= 0 && adjacentX < totalRows && adjacentY >= 0 && adjacentY < totalCols) {
                            adjacentTile->isClicked = true;
                            adjacentTile->isClickedRecursion = true;
                            adjacentTile->isClickedBlank = true;
                            hi = true;
                            cout << "ROWW IN FUNC" << row << endl;
                            cout << "COL IN FUNC" << col << endl;
                            countNumOfAdjMines(adjTiles, adjacentX, adjacentY);
                        }
                    }
                }
            }
        }
    }
    if(hi == true){
        return numOfAdjacentMines;
    }
    return numOfAdjacentMines;
}

int returnNumberOfAdjacentMines(vector<Tile*>& adjTiles, int row, int col){
    Tile instance;
    //get the vector containing pointers to the adjacent tiles
    int totalRows = instance.numOfRows;
    int totalCols = instance.numOfCols;
    vector<Tile *> storeAdjacentTiles = returnVectorOfAdjMines(adjTiles, row, col);

    int numOfAdjacentMines = 0;

    //iterate through adjacent tiles
    for (Tile *adjacentTile: storeAdjacentTiles) {
        if (adjacentTile->hasMine) {
            numOfAdjacentMines++;
        }
    }
    return numOfAdjacentMines;
}



int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 612), "Minesweeper", sf::Style::Close);
    sf::Color blue(0, 0, 255);
    Tile tempGameTiles;


    //load font
    sf::Font font;
    font.loadFromFile("files/font.ttf");


    //create text object
    sf::Text welcomeText("WELCOME TO MINESWEEPER!", font, 24);
    //set welcome text color as white
    welcomeText.setFillColor(sf::Color::White);
    //set text style to underlined and bold
    welcomeText.setStyle(sf::Text::Underlined | sf::Text::Bold);




    sf::Text enterNameText("Enter your name:", font, 20);
    sf::Text enterNameInputText("",font, 18);
    sf::String playerNameInput;
    enterNameText.setFillColor(sf::Color::White);
    enterNameText.setStyle(sf::Text::Bold);
    enterNameInputText.setFillColor(sf::Color::Yellow);
    enterNameInputText.setStyle(sf::Text::Bold);


    //reposition text to be in center
    //width
    float x = window.getSize().x / 2.0f;
    //height
    //move text up from the center (origin) by 150 units
    float y = window.getSize().y / 2.0f - 150.0f;
    setText(welcomeText, x, y);


    //width
    float x1 = window.getSize().x / 2.0f;
    //height
    //move text up from the center (origin) by 75 units
    float y1= window.getSize().y / 2.0f - 75.0f;
    setText(enterNameText, x1, y1);


    //width
    //for when player enters name
    float x2 = window.getSize().x / 2.0f;
    //height
    //move text up from the center (origin) by 75 units
    float y2= window.getSize().y / 2.0f - 45.0f;
    setText(enterNameInputText, x2, y2);


    //add cursor
    sf::RectangleShape cursor(sf::Vector2f(2.0f, 20.0f));
    cursor.setFillColor(sf::Color::White);
    //set cursor position to be right after inputted text
    cursor.setPosition(x2 + enterNameInputText.getLocalBounds().width / 2.0f + 8.0f, y2);


    //setup for the blinking of the cursor
    sf::Clock cursorBlinkClock;
    bool cursorIsShown = true;


    //random number generator
    //seed with a high-resolution timestamp
    std::mt19937 rng;
    auto seed = static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    rng.seed(seed);


    //game window code
    vector<Tile*> tempAdjacentTiles;
    iterateTiles("files/images/tile_hidden.png", 0.5f, tempAdjacentTiles);


    //generate random mines on game board
    int numMines = 50;
    randomizeMines(tempAdjacentTiles, numMines, rng);


    Tile mines;
    mines.loadTileTexture("files/images/mine.png");
    mines.setTexture();


    Tile happyFace;
    happyFace.loadTileTexture("files/images/face_happy.png");
    happyFace.setTexture();
    happyFace.happyFaceSprite.setPosition((((happyFace.numOfCols) / 2.0) * 32) - 32, 32 *((happyFace.numOfRows)+0.5f));


    Tile loseFace;
    loseFace.loadTileTexture("files/images/face_lose.png");
    loseFace.setTexture();
    loseFace.loseFaceSprite.setPosition((((loseFace.numOfCols) / 2.0) * 32) - 32, 32 *((loseFace.numOfRows)+0.5f));


    /*Tile debugButton;
    debugButton.loadTileTexture("files/images/debug.png");
    debugButton.setTexture();
    debugButton.debugSprite.setPosition(((debugButton.numOfCols) * 32) - 304, 32 * ((debugButton.numOfRows)+0.5f));*/


    Tile leaderBoard;
    leaderBoard.loadTileTexture("files/images/leaderboard.png");
    leaderBoard.setTexture();
    leaderBoard.leaderBoardSprite.setPosition(((leaderBoard.numOfCols) * 32) - 226, 32 * ((leaderBoard.numOfRows)+0.5f));


    sf::Texture digitsText;
    digitsText.loadFromFile("files/images/digits.png");
    sf::Sprite digits;
    sf::Sprite mineCountSprite;
    digits.setTexture(digitsText);



    bool paused = false; //false when game is not paused, true when the game is paused
    bool happyFaceClicked = false;

    int numOfFlags = 0;

    //timer functionality
    map<int, sf::Sprite> digitsMap;


    sf::IntRect zeroRect(0,0,21,32);
    digits.setTextureRect(zeroRect);
    sf::Sprite zero = digits;
    digitsMap.emplace(0, zero);


    sf::IntRect oneRect(21,0,21,32);
    digits.setTextureRect(oneRect);
    sf::Sprite one = digits;
    digitsMap.emplace(1, one);


    sf::IntRect twoRect(42,0,21,32);
    digits.setTextureRect(twoRect);
    sf::Sprite two = digits;
    digitsMap.emplace(2, two);


    sf::IntRect threeRect(63,0,21,32);
    digits.setTextureRect(threeRect);
    sf::Sprite three = digits;
    digitsMap.emplace(3, three);


    sf::IntRect fourRect(84,0,21,32);
    digits.setTextureRect(fourRect);
    sf::Sprite four = digits;
    digitsMap.emplace(4, four);


    sf::IntRect fiveRect(105,0,21,32);
    digits.setTextureRect(fiveRect);
    sf::Sprite five = digits;
    digitsMap.emplace(5, five);


    sf::IntRect sixRect(126,0,21,32);
    digits.setTextureRect(sixRect);
    sf::Sprite six = digits;
    digitsMap.emplace(6, six);

    sf::IntRect sevenRect(147,0,21,32);
    digits.setTextureRect(sevenRect);
    sf::Sprite seven = digits;
    digitsMap.emplace(7, seven);

    sf::IntRect eightRect(168,0,21,32);
    digits.setTextureRect(eightRect);
    sf::Sprite eight = digits;
    digitsMap.emplace(8, eight);


    sf::IntRect nineRect(189,0,21,32);
    digits.setTextureRect(nineRect);
    sf::Sprite nine = digits;
    digitsMap.emplace(9, nine);
    //if game is over, should be equal to true
    bool isGameOver = false;

    //negative sign (not in map)
    sf::IntRect negRect(210,0,21,32);
    digits.setTextureRect(negRect);
    sf::Sprite negativeSign = digits;


    sf::Texture pauseText;
    pauseText.loadFromFile("files/images/pause.png");
    sf::Sprite pauseBttn;
    pauseBttn.setTexture(pauseText);
    pauseBttn.setPosition((tempGameTiles.numOfCols * 32) - 290, 32 * (tempGameTiles.numOfRows+0.5f));


    sf::Texture playButton;
    playButton.loadFromFile("files/images/play.png");
    sf::Sprite playBttn;




    int numOfChars = 0;
    int correctNumOfMines = 0;
    int mouseX;
    int mouseY;
    //int numOfAdjMinesMain = 0;
    vector<int> numOfAdjMinesList;

    //window = welcome window
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }


            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode != '\b' && numOfChars < 10 && std::isalpha(event.text.unicode)) {
                    playerNameInput += event.text.unicode;
                    //make actual text appear on window in allotted spot
                    enterNameInputText.setString(playerNameInput);
                    numOfChars += 1;
                }


                if (event.text.unicode == '\b' && !playerNameInput.isEmpty()) {
                    //removes the last letter of the user input when backspace is pressed
                    //playerNameInput.getSize() - 1 retrieves the last char
                    playerNameInput.erase(playerNameInput.getSize() - 1);
                    //make the deletion of letters actually visible in the window
                    enterNameInputText.setString(playerNameInput);
                    numOfChars -= 1;
                }


                //iterate through user's name to make sure the first char is upper case and the rest are lower case
                for (int i = 0; i < playerNameInput.getSize(); ++i) {
                    if (i == 0) {
                        playerNameInput[i] = static_cast<char>(std::toupper(playerNameInput[i]));
                    } else {
                        playerNameInput[i] = static_cast<char>(std::tolower(playerNameInput[i]));
                    }
                }


                //redefines size so cursor follows new inputted text
                float newInputWidth = enterNameInputText.getLocalBounds().width;
                float cursorOffset = 2.5f;


                //repositions cursor
                //x2 is width
                float cursorX = x2 + newInputWidth + cursorOffset;
                float cursorRightBound = x2 + enterNameInputText.getLocalBounds().width;
                float cursorLeftBound = x2 - enterNameInputText.getLocalBounds().width;


                //bounds for cursor
                if (cursorX > cursorRightBound)
                    cursorX = cursorRightBound;
                if (cursorX < cursorLeftBound)
                    cursorX = cursorLeftBound;


                cursor.setPosition(cursorX, y2);


            }

            //when the user presses the enter key after inputting name
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Return) {
                sf::RenderWindow gameWindow(sf::VideoMode(tempGameTiles.numOfCols*32, (tempGameTiles.numOfRows*32)+100), "Minesweeper", sf::Style::Close);
                //starting the timer when the program begins to run
                auto startTime = chrono::high_resolution_clock::now();
                //Below is just for initialization, in the end, this will be overwritten, just needed to equal something. TLDR: Ignore what it equals here (below).
                auto pauseTime = chrono::high_resolution_clock::now();
                auto elapsed_paused_time = chrono::duration_cast<chrono::seconds>(
                        chrono::high_resolution_clock::now() - pauseTime).count();

                while (gameWindow.isOpen()) {
                    ifstream boardFile("files/board_config.cfg");

                    string readLine;
                    getline(boardFile, readLine);
                    int column = stoi(readLine);
                    getline(boardFile, readLine);
                    int row = stoi(readLine);
                    getline(boardFile, readLine);
                    //numMines = stoi(readLine);
                    //sets the game window background to white

                    gameWindow.clear(sf::Color::White);

                    //.clear() is used to fill the window w a specified color
                    //when game is still going...
                    sf::Event gameEvent;
                    while (gameWindow.pollEvent(gameEvent)) {
                        sf::Vector2i vec = sf::Mouse::getPosition(gameWindow);
                        if (gameEvent.type == sf::Event::Closed)
                            gameWindow.close();
                        if (gameEvent.type == sf::Event::MouseButtonPressed) {
                            if (gameEvent.mouseButton.button == sf::Mouse::Right) {
                                mouseX = gameEvent.mouseButton.x;
                                mouseY = gameEvent.mouseButton.y;

                               /* for (Tile* tile : tempAdjacentTiles) {
                                    //tile->isRightClicked = true;
                                    //stops right clicking when game is over
                                    if(tile->mousePositionInBounds(mouseX, mouseY) && tile->hasFlag){
                                        tile->isRightClicked = false;
                                    }
                                }*/

                                if (isGameOver == false) {
                                    for (Tile *tile: tempAdjacentTiles) {
                                            // Handle flag interaction (remove flag)
                                            if (tile->mousePositionInBoundsRight(mouseX, mouseY)) {
                                                //tile->isClicked = true;
                                                tile->isRightClicked = true;
                                                tile->hasFlag = true;
                                                numOfFlags++;
                                            }
                                            /*if(tile->mousePositionInBounds(mouseX, mouseY) && tile->hasFlag){
                                                tile->isRightClicked = false;
                                            }*/
                                    }
                                }
                            }
                            if (gameEvent.mouseButton.button == sf::Mouse::Left){
                                //access the mouse from the event
                                mouseX = gameEvent.mouseButton.x;
                                mouseY = gameEvent.mouseButton.y;
                                //going to be storing the answer to if the tile is flipped or not inside the isClicked boolean in tile.h
                                //also entering the proper bounds for the tile
                                //debugButton.mousePosInBoundsDebug(mouseX, mouseY);
                                //playButton.mousePosInBoundsPlay(mouseX, mouseY);

                                if (pauseBttn.getGlobalBounds().contains(vec.x, vec.y)) {
                                    paused = !paused; //boolean changed everytime pause button is clicked
                                    if (paused) {
                                        cout << "paused" << endl;
                                        pauseTime = chrono::high_resolution_clock::now();
                                        pauseBttn.setTexture(playButton);
                                        pauseBttn.setPosition((tempGameTiles.numOfCols * 32) - 240, 32 * (tempGameTiles.numOfRows+0.5f));
                                        for (Tile *tile: tempAdjacentTiles) {
                                            //tile->originalState = tile->isClicked;
                                            //tile->isClicked = true;
                                            //if tile isn't already clicked/revealed
                                            if(!tile->isClickedBlank){
                                                //drawing a tile as it iterates through the tempAdjacentTiles vector
                                                //if isClicked is true all the tiles are revealed
                                                tile->isClickedBlank = true;
                                            }
                                        }
                                    }
                                    else {
                                        //unpaused
                                        pauseBttn.setTexture(pauseText);
                                        pauseBttn.setPosition((tempGameTiles.numOfCols * 32) - 240, 32 * (tempGameTiles.numOfRows+0.5f));
                                        // pauseButton.setPosition(50, 20);
                                        auto unPausedTime = chrono::steady_clock::now();
                                        //Addition is necessary for when hitting the pause button more than once
                                        elapsed_paused_time += chrono::duration_cast<chrono::seconds>(unPausedTime - pauseTime).count();
                                        //cout << elapsed_paused_time % 60 << " " << endl;
                                        for (Tile *tile: tempAdjacentTiles) {
                                            //drawing a tile as it iterates through the tempAdjacentTiles vector
                                            //if isClicked is true all the tiles are revealed
                                            //tile->isClicked = false;
                                            /*if (!tile->originalState) {
                                                tile->resetTiles(); // If it was the original state, reveal the tile again
                                            }*/
                                            //saves the tiles that were revealed through recursion before and after pause
                                            if (tile->originalState && !tile->isClickedRecursion) {
                                                tile->resetTiles(); // If it was the original state, reveal the tile again
                                               ////// tile->isClicked = true;
                                            }
                                        }
                                    }
                                }


                                leaderBoard.mousePosInBoundsLeaderBoard(mouseX, mouseY);
                                //tile is a pointer to the Tile object, and it iterates over each element in tempAdjacentTiles vector
                                //while game is still ongoing...
                                if(isGameOver == false){
                                    for (int i = 0; i < tempAdjacentTiles.size(); ++i) {
                                        Tile* tile = tempAdjacentTiles[i];

                                        //calculate the row and column indices
                                        int currentRow = (i / column); //currentRow is the number of columns in the grid
                                        int currentCol = (i % column); //the remainder gives the column index


                                        //for each iteration, it calls the mousePositionInBounds function on the Tile object that tile is pointing to
                                        if (tile->mousePositionInBounds(mouseX, mouseY)) {
                                            tile->isClickedOnce = true;
                                            newBoolIDK = true;
                                            cout << mouseX << "x" << endl;
                                            cout << mouseY << "y" << endl;
                                            if (tile->hasMine && !tile->hasFlag) {
                                                //tile->isClicked = true;
                                                //mines.drawSpriteMine(gameWindow)
                                                //alt ver: write func in main and use revealALlMines(tempAdjacentTiles)
                                                tile->revealALlMines(tempAdjacentTiles);
                                                happyFace.mineClicked = true;
                                                //game is over when mine is clicked
                                                paused = !paused;
                                                pauseTime = chrono::high_resolution_clock::now();
                                                isGameOver = true;

                                                tile->isClicked = true;
                                            }
                                            else if(tile->hasFlag){
                                                tile->isClicked = false;
                                                tile->isRightClicked = false;
                                                numOfFlags--;
                                            }
                                            else{
                                                tile->isClicked = true;
                                                tile->originalState = false;
                                                tile->numOfAdjMinesMain = countNumOfAdjMines(tempAdjacentTiles, currentRow, currentCol);
                                                cout << currentRow << "current row" << endl;
                                                cout << currentCol << "current col" << endl;
                                            }

                                        }
                                    }
                                }

                                if (happyFace.mousePosInBoundsHappyFace(mouseX, mouseY)) {
                                    happyFaceClicked = true;
                                    //reset all tiles to their hidden form
                                    happyFace.drawSpriteHappyFace(gameWindow);
                                    for (Tile *tile: tempAdjacentTiles) {
                                        //must use pointer to reference functions because tile is a pointer object Tile* tile
                                        tile->resetTiles();
                                        //tile->originalState = true resets the clicked tiles each time the happy face is clicked
                                        tile->originalState = true;
                                        //right now isClicked = false
                                        isGameOver = false;
                                        //paused = false;

                                        //reset the timer variables, this is very important to the funcitonality, timer will go all wonky if it isnt reset from starting point everytime the tiles arereset
                                        startTime = chrono::high_resolution_clock::now();
                                        pauseTime = chrono::high_resolution_clock::now();
                                        elapsed_paused_time = 0;

                                        //reset mine counter
                                        numOfFlags = 0;


                                        tile->randomizeMines(tempAdjacentTiles, 50, rng);
                                    }
                                    happyFace.resetHappyFace();
                                }
                            }
                        }
                        //draw always have to be between clear and display
                        //can use gameBoard class from header file here instead of built-in function .draww



                        window.close();
                    }
                    //this finds the time elapsed, so the current time - the time the window opened.
                    auto game_duration = std::chrono::duration_cast<std::chrono::seconds>(
                            chrono::high_resolution_clock::now() - startTime);
                    int total_time = game_duration.count(); //necessary to subtract elapsed time later because "game_duration.count()" is const
                    int minutes;
                    int seconds;


                    if (!paused) {
                        //enters if the game is NOT paused. This is the condition that keeps the timer from incrementing when paused.
                        total_time = total_time - elapsed_paused_time; //
                        minutes = total_time / 60;
                        seconds = total_time % 60;
                    }

                    //"separating" the integers. So.... 68 -> seconds0 = 6 and seconds1 = 8
                    int minutes0 = minutes / 10 % 10; //minutes index 0
                    int minutes1 = minutes % 10; // minutes index 1
                    int seconds0 = seconds / 10 % 10; // seconds index 0
                    int seconds1 = seconds % 10; // seconds index 1


                    digitsMap[minutes0].setPosition(((tempGameTiles.numOfCols) * 32) - 98, 32 * ((tempGameTiles.numOfRows) + 0.5f) + 16);
                    gameWindow.draw(digitsMap[minutes0]);

                    digitsMap[minutes1].setPosition(((tempGameTiles.numOfCols) * 32) - 77, 32 * ((tempGameTiles.numOfRows) + 0.5f) + 16);
                    gameWindow.draw(digitsMap[minutes1]);

                    digitsMap[seconds0].setPosition(((tempGameTiles.numOfCols) * 32) - 54, 32 * ((tempGameTiles.numOfRows) + 0.5f) + 16);
                    gameWindow.draw(digitsMap[seconds0]);

                    digitsMap[seconds1].setPosition(((tempGameTiles.numOfCols) * 32) - 33, 32 * ((tempGameTiles.numOfRows) + 0.5f) + 16);
                    gameWindow.draw(digitsMap[seconds1]);


                    //mine counter logic
                    int totalNumOfMines = 50;
                    int minesRemaining = totalNumOfMines - numOfFlags;
                    int minesRemainingPos = abs(totalNumOfMines - numOfFlags);


                    //split the minesRemaining integer up to its individual digit values
                    //by using the abs value of mines remaining, the three digits should only account for the numbers and not the negative sign
                    int minesRemaining1 = minesRemainingPos / 100; //first digit
                    int minesRemaining2 = (minesRemainingPos / 10) % 10; //second digit
                    int minesRemaining3 = minesRemainingPos % 10; //thrid digit

                    //display mine counter
                    //inserts the new ints to the digits map
                    //ex. if minesRemaining1 = 2, then digitsMap[2] would get the graphic associated with that number
                    digitsMap[minesRemaining1].setPosition(33, 32 * ((tempGameTiles.numOfRows)+0.5f)+16);
                    gameWindow.draw(digitsMap[minesRemaining1]);
                    digitsMap[minesRemaining2].setPosition(54, 32 * ((tempGameTiles.numOfRows)+0.5f)+16);
                    gameWindow.draw(digitsMap[minesRemaining2]);
                    digitsMap[minesRemaining3].setPosition(75, 32 * ((tempGameTiles.numOfRows)+0.5f)+16);
                    gameWindow.draw(digitsMap[minesRemaining3]);

                    if(minesRemaining < 0){
                        negativeSign.setPosition(12, 32 * ((tempGameTiles.numOfRows)+0.5f)+16);
                        gameWindow.draw(negativeSign);
                    }


                    for (int i = 0; i < tempAdjacentTiles.size(); ++i) {
                        Tile *tile = tempAdjacentTiles[i];
                        int currentRow = (i / column);
                        int currentCol = (i % column);
                        if (!tile->hasMine) {
                            tile->numOfAdjMinesMain = returnNumberOfAdjacentMines(tempAdjacentTiles, currentRow, currentCol);
                        }

                        cout << tile->numOfAdjMinesMain << "00000" << endl;
                        tile->drawSprite(gameWindow);
                        tile->drawSpriteFlag(gameWindow);
                        cout << tile->numOfAdjMinesMain << " numOfAdjMinesMain" << endl;
                        //tile->mousePositionInBounds(mouseX, mouseY);


                        if(tile->numOfAdjMinesMain == 1 && !tile->hasMine && newBoolIDK){
                            tile->drawSpriteDigit1(gameWindow);
                        }
                        else if(tile->numOfAdjMinesMain == 2 && !tile->hasMine && newBoolIDK){
                            tile->drawSpriteDigit2(gameWindow);
                        }
                        else if(tile->numOfAdjMinesMain == 3 && !tile->hasMine && newBoolIDK){
                            tile->drawSpriteDigit3(gameWindow);
                        }
                        else if(tile->numOfAdjMinesMain == 4 && !tile->hasMine && newBoolIDK){
                            tile->drawSpriteDigit4(gameWindow);
                        }
                        else if(tile->numOfAdjMinesMain == 5 && !tile->hasMine && newBoolIDK){
                            tile->drawSpriteDigit5(gameWindow);
                        }
                        cout << tile->numOfAdjMinesMain << " clicked numOfAdjMinesMain" << endl;
                    }


                    happyFace.drawSpriteHappyFace(gameWindow);


                    //debugButton.drawSpriteDebug(gameWindow);
                    //playButton.drawSpritePlay(gameWindow);
                    //pauseButton.drawSpritePause(gameWindow);
                    leaderBoard.drawSpriteLeaderBoard(gameWindow);
                    gameWindow.draw(pauseBttn);
                    gameWindow.display();
                }
            }
        }


        //if time elapsed surpasses 0.5 seconds, cursorIsShown boolean turns false
        if (cursorBlinkClock.getElapsedTime().asSeconds() >= 0.5f) {
            //toggle cursor visibility
            cursorIsShown = !cursorIsShown;
            cursorBlinkClock.restart();
        }


        //set the cursor's fill color based on cursorVisible flag
        if (cursorIsShown) {
            cursor.setFillColor(sf::Color::White); //set cursor color to white
        } else {
            //when cursorIsShown is false, color turns transparent, otherwise it is white
            cursor.setFillColor(sf::Color::Transparent); //set cursor color to transparent
        }


        //sets the window background color to blue
        window.clear(blue);
        //draws text on window
        window.draw(welcomeText);
        window.draw(enterNameText);
        window.draw(enterNameInputText);
        window.draw(cursor);
        window.display();
    }
    //free memory for each tile object before exiting since it is dynamically allocated memory
    for (Tile* tile : tempAdjacentTiles) {
        delete tile;
    }
    tempAdjacentTiles.clear();
    return 0;
}

