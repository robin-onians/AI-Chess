#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Board
{
public:
    Board() {

    };

    void initialise();
    std::vector<std::vector<sf::IntRect>> getGrid() { return grid; };
    void draw(sf::RenderWindow&);
private:

    std::vector<std::vector<sf::RectangleShape>> board;
    std::vector<std::vector<sf::IntRect>> grid;

    int numRows = 8;
    int numSquaresperRow = 8;
    int gridSquarePosx = 0;
    int gridSquarePosy = 0;
    int lightSquarePosx = 0;
    int lightSquarePosy = 0;
    int darkSquarePosx = 100;
    int darkSquarePosy = 0;

};
