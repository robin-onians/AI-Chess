#include "board.h"


void Board::initialise()
{
    //define size of board vector
    board = std::vector<std::vector<sf::RectangleShape>> (8, std::vector<sf::RectangleShape>(8));
    //define size of grid vector
    grid = std::vector<std::vector<sf::IntRect>>(numRows, std::vector<sf::IntRect>(numRows));

    //initialise board squares
    for (int row = 0; row < numRows; row++)
    {

        for (int square = 0; square < numSquaresperRow; square++)
        {
            //defining grid 2 squares per iteration
            sf::IntRect gridSquare1(gridSquarePosx, gridSquarePosy, 100, 100);
            grid[row][square] = gridSquare1;
            gridSquarePosx += 100;

            //defining board
            if (lightSquarePosx < darkSquarePosx)
            {
                sf::RectangleShape lightSquare(sf::Vector2f(100, 100));                
                lightSquare.setFillColor(sf::Color(227, 207, 197));
                lightSquare.setPosition(lightSquarePosx, lightSquarePosy);
                board[row][square] = lightSquare;
                lightSquarePosx += 200;

                square++;

                sf::RectangleShape darkSquare(sf::Vector2f(100, 100));
                darkSquare.setFillColor(sf::Color(148, 109, 90));
                darkSquare.setPosition(darkSquarePosx, darkSquarePosy);
                board[row][square] = darkSquare;
                darkSquarePosx += 200;
            }
            else
            {
                sf::RectangleShape darkSquare(sf::Vector2f(100, 100));
                darkSquare.setFillColor(sf::Color(148, 109, 90));
                darkSquare.setPosition(darkSquarePosx, darkSquarePosy);
                board[row][square] = darkSquare;
                darkSquarePosx += 200;

                square++;

                sf::RectangleShape lightSquare(sf::Vector2f(100, 100));
                lightSquare.setFillColor(sf::Color(227, 207, 197));
                lightSquare.setPosition(lightSquarePosx, lightSquarePosy);
                board[row][square] = lightSquare;
                lightSquarePosx += 200;
            }

            sf::IntRect gridSquare2(gridSquarePosx, gridSquarePosy, 100, 100);
            grid[row][square] = gridSquare2;
            gridSquarePosx += 100;
        }

        gridSquarePosx = 0;
        gridSquarePosy += 100;

        //decide which colour to start with on new row for board
        if (lightSquarePosx > darkSquarePosx)
        {
            lightSquarePosx = 0;
            lightSquarePosy += 100;

            darkSquarePosx = 100;
            darkSquarePosy += 100;
        }
        else
        {
            lightSquarePosx = 100;
            lightSquarePosy += 100;

            darkSquarePosx = 0;
            darkSquarePosy += 100;
        }
    }
}

void Board::draw(sf::RenderWindow& window)
{
    //draw board
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            window.draw(board[i][j]);
        }
    }
}