#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "board.h"

struct tupleStruct
{
    int i = -1;
    int j = -1;
};

class WhitePieces
{
public:
    WhitePieces() {};
    void init(const std::vector<std::vector<sf::IntRect>>);
    void draw(sf::RenderWindow&, sf::Vector2i);
    bool move(sf::Vector2i);
    int place(sf::Vector2i, std::vector<sf::Sprite>);
    std::vector<sf::Sprite>* getWhitePieces() { return &whitePieces; };
    void removePiece(int);
    void opponentMove(int pieceIndex, int squareIndexi, int squareIndexj);
    int getMovedPiecedIndex() { return n; };
    tupleStruct getPlacedSquareIndex() { return squarePos; };

private:
    std::vector<sf::Sprite> whitePieces;
    sf::Texture texture;

    //white pieces
    sf::Sprite rook1;
    sf::Sprite rook2;
    sf::Sprite bishop1;
    sf::Sprite bishop2;
    sf::Sprite knight1;
    sf::Sprite knight2;
    sf::Sprite king;
    sf::Sprite queen;
    sf::Sprite pawn1;
    sf::Sprite pawn2;
    sf::Sprite pawn3;
    sf::Sprite pawn4;
    sf::Sprite pawn5;
    sf::Sprite pawn6;
    sf::Sprite pawn7;
    sf::Sprite pawn8;

    //variables for moving pieces
    float dx = 0, dy = 0;
    int n = 0;
    sf::Vector2f oldPos, newPos;
    bool hasMoved = false;
    std::vector<std::vector<sf::IntRect>> grid;
    tupleStruct squarePos;
};


class BlackPieces
{
public:
    BlackPieces() {};
    void init(const std::vector<std::vector<sf::IntRect>>);
    void draw(sf::RenderWindow&, sf::Vector2i);
    bool move(sf::Vector2i);
    int place(sf::Vector2i, std::vector<sf::Sprite>);
    std::vector<sf::Sprite>* getBlackPieces() { return &blackPieces; };
    void removePiece(int);
    void opponentMove(int pieceIndex, int squareIndexi, int squareIndexj);
    int getMovedPiecedIndex() { return n; };
    tupleStruct getPlacedSquareIndex() { return squarePos; };
private:
    std::vector<sf::Sprite> blackPieces;
    sf::Texture texture;

    //black pieces
    sf::Sprite rook1;
    sf::Sprite rook2;
    sf::Sprite bishop1;
    sf::Sprite bishop2;
    sf::Sprite knight1;
    sf::Sprite knight2;
    sf::Sprite king;
    sf::Sprite queen;
    sf::Sprite pawn1;
    sf::Sprite pawn2;
    sf::Sprite pawn3;
    sf::Sprite pawn4;
    sf::Sprite pawn5;
    sf::Sprite pawn6;
    sf::Sprite pawn7;
    sf::Sprite pawn8;

    //variables for moving pieces 
    float dx = 0, dy = 0;
    int n = 0;
    sf::Vector2f oldPos, newPos;
    bool hasMoved = false;
    std::vector<std::vector<sf::IntRect>> grid;
    tupleStruct squarePos;
};
