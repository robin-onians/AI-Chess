
#include "pieces.h"

void BlackPieces::init(const std::vector<std::vector<sf::IntRect>> g) {

    grid = g;

    // load a 32x32 rectangle that starts at (10, 10)
    if (!texture.loadFromFile("art/blackPieces.png"))
    {
        std::cout << "error could not open texture: blackPieces.png\n\n";
    }

    //pieces row
    rook1.setTexture(texture);
    rook1.setTextureRect(sf::IntRect(0, 0, 90, 90));
    blackPieces.push_back(rook1);
    knight1.setTexture(texture);
    knight1.setTextureRect(sf::IntRect(400, 0, 90, 90));
    blackPieces.push_back(knight1);
    bishop1.setTexture(texture);
    bishop1.setTextureRect(sf::IntRect(90, 0, 100, 90));
    blackPieces.push_back(bishop1);
    queen.setTexture(texture);
    queen.setTextureRect(sf::IntRect(190, 0, 100, 90));
    blackPieces.push_back(queen);
    king.setTexture(texture);
    king.setTextureRect(sf::IntRect(295, 0, 100, 90));
    blackPieces.push_back(king);
    bishop2.setTexture(texture);
    bishop2.setTextureRect(sf::IntRect(90, 0, 100, 90));
    blackPieces.push_back(bishop2);
    knight2.setTexture(texture);
    knight2.setTextureRect(sf::IntRect(400, 0, 90, 90));
    blackPieces.push_back(knight2);
    rook2.setTexture(texture);
    rook2.setTextureRect(sf::IntRect(0, 0, 90, 90));
    blackPieces.push_back(rook2);
    //pawns row
    pawn1.setTexture(texture);
    pawn1.setTextureRect(sf::IntRect(500, 0, 90, 90));
    blackPieces.push_back(pawn1);
    pawn2.setTexture(texture);
    pawn2.setTextureRect(sf::IntRect(500, 0, 90, 90));
    blackPieces.push_back(pawn2);
    pawn3.setTexture(texture);
    pawn3.setTextureRect(sf::IntRect(500, 0, 90, 90));
    blackPieces.push_back(pawn3);
    pawn4.setTexture(texture);
    pawn4.setTextureRect(sf::IntRect(500, 0, 90, 90));
    blackPieces.push_back(pawn4);
    pawn5.setTexture(texture);
    pawn5.setTextureRect(sf::IntRect(500, 0, 90, 90));
    blackPieces.push_back(pawn5);
    pawn6.setTexture(texture);
    pawn6.setTextureRect(sf::IntRect(500, 0, 90, 90));
    blackPieces.push_back(pawn6);
    pawn7.setTexture(texture);
    pawn7.setTextureRect(sf::IntRect(500, 0, 90, 90));
    blackPieces.push_back(pawn7);
    pawn8.setTexture(texture);
    pawn8.setTextureRect(sf::IntRect(500, 0, 90, 90));
    blackPieces.push_back(pawn8);

    int pos = 4;

    //organise initial board state for black
    for (int i = 0; i < 8; i++)
    {
        blackPieces.at(i).setPosition(pos, 5);
        pos += 100;
    }
    pos = 5;
    for (int i = 8; i < blackPieces.size(); i++)
    {
        blackPieces.at(i).setPosition(pos, 105);
        pos += 100;
    }
}

void BlackPieces::draw(sf::RenderWindow& window, sf::Vector2i pos)
{
    if (hasMoved)
        blackPieces[n].setPosition(pos.x - dx, pos.y - dy);

    for (int i = 0; i < blackPieces.size(); i++)
    {
        window.draw(blackPieces.at(i));
    }
}

bool BlackPieces::move(sf::Vector2i mousePos)
{
    for (int i = 0; i < 16; i++)
    {
        if (blackPieces[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            hasMoved = true; n = i;
            dx = mousePos.x - blackPieces[i].getPosition().x;
            dy = mousePos.y - blackPieces[i].getPosition().y;
            oldPos = blackPieces[i].getPosition();
            return true;
        }
        else n = -1;
    }
    return false;
}

int BlackPieces::place(sf::Vector2i mousePos, std::vector<sf::Sprite> oppPieces)
{

    if (n != -1)
    {
        hasMoved = false;
        //loop through grid and find which square the new position lays in
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                //allign piece on grid square
                sf::IntRect square = grid[i][j];
                float w = blackPieces[n].getGlobalBounds().width;
                float h = blackPieces[n].getGlobalBounds().height;
                sf::Vector2i p = sf::Vector2i(blackPieces[n].getPosition()) + sf::Vector2i(w / 2, h / 2);
                if (square.contains(p))
                {
                    squarePos.i = i;
                    squarePos.j = j;

                    float w;
                    float h;
                    sf::Vector2i op;
                    sf::Vector2i bp;
                    for (int k = 0; k < 16; k++)
                    {
                        //find if there is an opposing piece already on the square
                        w = oppPieces[k].getGlobalBounds().width;
                        h = oppPieces[k].getGlobalBounds().height;
                        op = sf::Vector2i(oppPieces[k].getPosition()) + sf::Vector2i(w / 2, h / 2);
                        if (square.contains(op))
                        {
                            blackPieces[n].setPosition(sf::Vector2f(square.left, square.top));
                            return k;
                        }

                        if (k != n)
                        {
                            //find if there is a black piece already on the square
                            w = blackPieces[k].getGlobalBounds().width;
                            h = blackPieces[k].getGlobalBounds().height;
                            bp = sf::Vector2i(blackPieces[k].getPosition()) + sf::Vector2i(w / 2, h / 2);
                            if (square.contains(bp))
                            {
                                blackPieces[n].setPosition(oldPos);
                                return -1;
                            }
                        }
                    }

                    //square is valid, drop piece on square 
                    blackPieces[n].setPosition(sf::Vector2f(square.left, square.top));
                    return -1;
                }
               
            }
        }
    }
    return -1;
}

void BlackPieces::removePiece(int i)
{
    blackPieces[i].setPosition(-100, -100);
}


void BlackPieces::opponentMove(int pieceIndex, int squareIndexi, int squareIndexj)
{
    sf::IntRect square = grid[squareIndexi][squareIndexj];
    blackPieces[pieceIndex].setPosition(sf::Vector2f(square.left, square.top));
}



//------------White Pieces----------------------------


void WhitePieces::init(const std::vector<std::vector<sf::IntRect>> g)
{
    grid = g;

    // load a 32x32 rectangle that starts at (10, 10)
    if (!texture.loadFromFile("art/whitePieces.png"))
    {
        std::cout << "error could not open texture: whitePieces.png\n\n";
    }

    //pieces row
    rook1.setTexture(texture);
    rook1.setTextureRect(sf::IntRect(0, 0, 90, 90));
    whitePieces.push_back(rook1);
    knight1.setTexture(texture);
    knight1.setTextureRect(sf::IntRect(384, 0, 90, 90));
    whitePieces.push_back(knight1);
    bishop1.setTexture(texture);
    bishop1.setTextureRect(sf::IntRect(90, 0, 100, 90));
    whitePieces.push_back(bishop1);
    queen.setTexture(texture);
    queen.setTextureRect(sf::IntRect(190, 0, 100, 90));
    whitePieces.push_back(queen);
    king.setTexture(texture);
    king.setTextureRect(sf::IntRect(285, 0, 100, 90));
    whitePieces.push_back(king);
    bishop2.setTexture(texture);
    bishop2.setTextureRect(sf::IntRect(90, 0, 100, 90));
    whitePieces.push_back(bishop2);
    knight2.setTexture(texture);
    knight2.setTextureRect(sf::IntRect(384, 0, 90, 90));
    whitePieces.push_back(knight2);
    rook2.setTexture(texture);
    rook2.setTextureRect(sf::IntRect(0, 0, 90, 90));
    whitePieces.push_back(rook2);
    //pawns row
    pawn1.setTexture(texture);
    pawn1.setTextureRect(sf::IntRect(500, 0, 80, 90));
    whitePieces.push_back(pawn1);
    pawn2.setTexture(texture);
    pawn2.setTextureRect(sf::IntRect(500, 0, 80, 90));
    whitePieces.push_back(pawn2);
    pawn3.setTexture(texture);
    pawn3.setTextureRect(sf::IntRect(500, 0, 80, 90));
    whitePieces.push_back(pawn3);
    pawn4.setTexture(texture);
    pawn4.setTextureRect(sf::IntRect(500, 0, 80, 90));
    whitePieces.push_back(pawn4);
    pawn5.setTexture(texture);
    pawn5.setTextureRect(sf::IntRect(500, 0, 80, 90));
    whitePieces.push_back(pawn5);
    pawn6.setTexture(texture);
    pawn6.setTextureRect(sf::IntRect(500, 0, 80, 90));
    whitePieces.push_back(pawn6);
    pawn7.setTexture(texture);
    pawn7.setTextureRect(sf::IntRect(500, 0, 80, 90));
    whitePieces.push_back(pawn7);
    pawn8.setTexture(texture);
    pawn8.setTextureRect(sf::IntRect(500, 0, 80, 90));
    whitePieces.push_back(pawn8);

    int pos = 4;

    //organise initial board state for white
    for (int i = 0; i < 8; i++)
    {
        whitePieces.at(i).setPosition(pos, 705);
        pos += 100;
    }
    pos = 18;
    for (int i = 8; i < whitePieces.size(); i++)
    {
        whitePieces.at(i).setPosition(pos, 605);
        pos += 100;
    }
}

void WhitePieces::draw(sf::RenderWindow& window, sf::Vector2i pos)
{
    if(hasMoved)
        whitePieces[n].setPosition(pos.x - dx, pos.y - dy);

    for (int i = 0; i < whitePieces.size(); i++)
    {
        window.draw(whitePieces.at(i));
    }
}

bool WhitePieces::move(sf::Vector2i pos)
{
    for (int i = 0; i < 16; i++)
    {
        sf::FloatRect r = whitePieces[i].getGlobalBounds();
        if (r.contains(pos.x, pos.y))
        {
            hasMoved = true; n = i;
            dx = pos.x - whitePieces[i].getPosition().x;
            dy = pos.y - whitePieces[i].getPosition().y;
            oldPos = whitePieces[i].getPosition();
            return true;
        }
        else n = -1;
    }
    return false;
}

int WhitePieces::place(sf::Vector2i mousePos, std::vector<sf::Sprite> oppPieces)
{

    //loop through grid and find which square the new position lays in
    if (n != -1)
    {
        hasMoved = false;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                //check on grid
                sf::IntRect square = grid[i][j];
                float w = whitePieces[n].getGlobalBounds().width;
                float h = whitePieces[n].getGlobalBounds().height;
                sf::Vector2i p = sf::Vector2i(whitePieces[n].getPosition()) + sf::Vector2i(w / 2, h / 2);
                if (square.contains(p))
                {
                    squarePos.i = i;
                    squarePos.j = j;

                    float w;
                    float h;
                    sf::Vector2i op;
                    sf::Vector2i bp;
                   
                    for (int k = 0; k < 16; k++)
                    {
                        //find if there is an opposing piece on the square
                        w = oppPieces[k].getGlobalBounds().width;
                        h = oppPieces[k].getGlobalBounds().height;
                        sf::Vector2i op = sf::Vector2i(oppPieces[k].getPosition()) + sf::Vector2i(w / 2, h / 2);
                        if (square.contains(op))
                        {
                            if ((n == 0) || (n >= 7 && n < 16))
                                whitePieces[n].setPosition(sf::Vector2f(square.left + 17, square.top + 5));
                            else
                                whitePieces[n].setPosition(sf::Vector2f(square.left, square.top));
                            return k;
                        }

                        if (k != n)
                        {
                            //find if there is a white piece already on the square
                            w = whitePieces[k].getGlobalBounds().width;
                            h = whitePieces[k].getGlobalBounds().height;
                            bp = sf::Vector2i(whitePieces[k].getPosition()) + sf::Vector2i(w / 2, h / 2);
                            if (square.contains(bp))
                            {
                                whitePieces[n].setPosition(oldPos);
                                return -1;
                            }
                        }
                    }

                    if ((n == 0) || (n >= 7 && n < 16))
                        whitePieces[n].setPosition(sf::Vector2f(square.left + 17, square.top + 5));
                    else
                        whitePieces[n].setPosition(sf::Vector2f(square.left, square.top));
                    return -1;
                }
            }
        }
    }
    return -1;
}

void WhitePieces::removePiece(int i)
{
    whitePieces[i].setPosition(-100, -100);
}

void WhitePieces::opponentMove(int pieceIndex, int squareIndexi, int squareIndexj)
{
    sf::IntRect square = grid[squareIndexi][squareIndexj];
    whitePieces[pieceIndex].setPosition(sf::Vector2f(square.left, square.top));
}