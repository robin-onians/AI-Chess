#pragma comment(lib,"ws2_32.lib") 	// Use this library whilst linking - contains the Winsock2 implementation.

// game
#include "pieces.h"
#include "board.h"
#include "gameWindow.h"
#include <iostream>

// network
#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <vector>
#include <list>
#include <deque>
#include <istream>


bool recved = false;
const int recvSize = 256;
char message[recvSize];

DWORD WINAPI RecvThread(void* data) {
    SOCKET s = (SOCKET)data;

    bool fin = false;

    while (!fin) {
        recv(s, message, recvSize, 0);
        recved = true;
        Sleep(10);
    }

    return 0;
}

bool GetHasRecv() {
    return recved;
}

char* GetMessagee() {
    recved = false;
    return message;
}


int main()
{
    // Initialise Winsock
    WSADATA WsaDat;
    if (WSAStartup(MAKEWORD(2, 2), &WsaDat) != 0)
    {
        std::cout << "Winsock error - Winsock initialization failed\r\n";
        WSACleanup();
        return 0;
    }

    // Create our socket
    SOCKET Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (Socket == INVALID_SOCKET)
    {
        std::cout << "Winsock error - Socket creation Failed!\r\n";
        WSACleanup();
        return 0;
    }

    // Resolve IP address for hostname.
    struct hostent* host;

    // Change this to point to server, or ip address...

    if ((host = gethostbyname("localhost")) == NULL)   // In this case 'localhost' is the local machine. Change this to a proper IP address if connecting to another machine on the network.
    {
        std::cout << "Failed to resolve hostname.\r\n";
        WSACleanup();
        return 0;
    }

    // Setup our socket address structure.
    SOCKADDR_IN SockAddr;
    SockAddr.sin_port = htons(8888);	// Port number
    SockAddr.sin_family = AF_INET;		// Use the Internet Protocol (IP)
    SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

    // Attempt to connect to server...
    if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0)
    {
        std::cout << "Failed to establish connection with server\r\n";
        WSACleanup();
        return 0;
    }

    CreateThread(nullptr, 0, RecvThread, (void*)Socket, 0, nullptr);

    bool fin = false;
    bool firstmessagesent = false;
    // Receive and then display the message returned from the server....
    int bufferSize = 100;
    char buffer[100];
    memset(buffer, 0, bufferSize);



    // Initialise game
    GameWindow window;
    Board board;
    board.initialise();
    WhitePieces wpieces;
    BlackPieces bpieces;
    wpieces.init(board.getGrid());
    bpieces.init(board.getGrid());

    int deadPiece = -1;
    bool whiteMoved = false;
    bool blackMoved = false;
    const int whitePiece = 0;
    const int blackPiece = 1;

    while (window.getWindow()->isOpen())
    {
        sf::Vector2i pos = sf::Mouse::getPosition(*window.getWindow());

        sf::Event event;
        while (window.getWindow()->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.getWindow()->close();

            ///drag and drop
            if (event.type == sf::Event::MouseButtonPressed)
                if (event.key.code == sf::Mouse::Left)
                {
                    if (wpieces.move(pos))
                        whiteMoved = true;
                    else
                        whiteMoved = false;

                    if (bpieces.move(pos))
                        blackMoved = true;
                    else
                        blackMoved = false;
                }
            if (event.type == sf::Event::MouseButtonReleased)
                if (event.key.code == sf::Mouse::Left)
                {
                    //places piece and returns dead piece index if applicable

                    if (whiteMoved)
                    {
                        deadPiece = wpieces.place(pos, *bpieces.getBlackPieces());
                        if (deadPiece != -1)
                        {
                            bpieces.removePiece(deadPiece);
                        }

                        // populate buffer { colour of piece, index of piece, square index i, square index j }
                        char tempBuffer[4] = { whitePiece, wpieces.getMovedPiecedIndex(), wpieces.getPlacedSquareIndex().i, wpieces.getPlacedSquareIndex().j };
                        for (int i = 0; i < 4; i++)
                        {
                            message[i] = tempBuffer[i];
                        }

                        send(Socket, message, bufferSize, 0);
                    }

                    if (blackMoved)
                    {
                        deadPiece = bpieces.place(pos, *wpieces.getWhitePieces());
                        if (deadPiece != -1)
                        {
                            wpieces.removePiece(deadPiece);
                        }
                        // populate buffer { colour of piece, index of piece, square index i, square index j }
                        char tempBuffer[4] = { blackPiece, bpieces.getMovedPiecedIndex(), bpieces.getPlacedSquareIndex().i, bpieces.getPlacedSquareIndex().j };
                        for (int i = 0; i < 4; i++)
                        {
                            message[i] = tempBuffer[i];
                        }

                        //send data to server address
                        send(Socket, message, bufferSize, 0);
                    }

                    whiteMoved = false;
                    blackMoved = false;
                }
        }

        //recieve a move from opponent
        if (GetHasRecv()) {
            printf("message recieved!");
            char* msg = GetMessagee();

            int colourPiece = msg[0];
            int pieceIndex = msg[1];
            int squarePosi = msg[2];
            int squarePosj = msg[3];

            //printf("Recv: %s", std::to_string(colourPiece + pieceIndex + squarePosi + squarePosj + deadPiece));

            //process opponent data
            //move a white piece
            if (colourPiece == 0)
            {
                wpieces.opponentMove(pieceIndex, squarePosi, squarePosj);
            }
            //move a black piece
            if (colourPiece == 1)
            {
                bpieces.opponentMove(pieceIndex, squarePosi, squarePosj);
            }
        }

        window.getWindow()->clear();
        //draw board
        board.draw(*window.getWindow());
        //draw pieces
        wpieces.draw(*window.getWindow(), pos);
        bpieces.draw(*window.getWindow(), pos);
        window.getWindow()->display();
    }

    //Shutdown our socket.
	shutdown(Socket, SD_SEND);

	// Close our socket entirely.
	closesocket(Socket);

	// Cleanup Winsock.
	WSACleanup();
    return 0;
}