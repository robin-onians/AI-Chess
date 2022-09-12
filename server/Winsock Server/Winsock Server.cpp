// Winsock Server Application

#include "stdafx.h"

#include <iostream>
#include <winsock2.h>
#include <vector>
#include <list>
#include <deque>

#pragma comment(lib, "ws2_32.lib")	// Use this library whilst linking - contains the Winsock2 implementation.


SOCKET player1s, player2s;
bool player1, player2;

void SendInt(SOCKET &s, int &n)
{
	send(s, (char*)&n, sizeof(int), 0);
}


DWORD WINAPI ClientThread(void* userdata) {
	SOCKET s = (SOCKET)userdata;
	SOCKET opponentSock;
	const int mMessageSize = 256;
	char mMessageData[mMessageSize];
	char messageToSend[mMessageSize];

	bool playernumb;

	if (player1 == false) {
		player1 = true;
		player1s = s;
		playernumb = false;
		printf("Server: user 1 connected");
	}
	else {
		player2 = true;
		player2s = s;
		playernumb = true;
		printf("Server: user 2 connected");
	}

	while (!player2) {
		Sleep(10);
	}

	if(playernumb) {
		opponentSock = player1s;
	} else{
		opponentSock = player2s;
	}

	printf("Gameloop started");

	int colourPiece;
	int pieceIndex;
	int squarePosi;
	int squarePosj;

	bool fin = false;

	while (!fin) {
		//Recv data from client
		recv(s, mMessageData, mMessageSize, 0);

		//Process data
		{
			messageToSend[0] = mMessageData[0];
			messageToSend[1] = mMessageData[1];
			messageToSend[2] = mMessageData[2];
			messageToSend[3] = mMessageData[3];
		}

		send(opponentSock, messageToSend, mMessageSize, 0);
	}

	return 0;
}


int main()
{
	WSADATA WsaDat;

	// Initialise Windows Sockets
	if (WSAStartup(MAKEWORD(2,2), &WsaDat)!=0)
	{
		std::cout << "WSA Initialization failed!\r\n";
		WSACleanup();
		return 0;
	}
	
	// Create a unbound socket.
	SOCKET Socket = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
	
	if (Socket == INVALID_SOCKET)
	{
		std::cout << "Socket creation failed.\r\n";
		WSACleanup();
		return 0;
	}

	// Now, try and bind the socket to any incoming IP address on Port 8888.
	SOCKADDR_IN serverInf;

	serverInf.sin_family		= AF_INET;
	serverInf.sin_addr.s_addr	= INADDR_ANY;
	serverInf.sin_port			= htons(8888);

	if (bind(Socket, (SOCKADDR*)(&serverInf), sizeof(serverInf)) == SOCKET_ERROR)
	{
		std::cout << "Unable to bind socket!\r\n";
		WSACleanup();
		return 0;
	}

	bool fin = true;

	//Loop to search for new users and start a user thread
	while(fin) {

		// Listen for incoming connections from any IP address on Port 8888.
		listen(Socket, 1);

		SOCKET TempSock = SOCKET_ERROR;
		while (TempSock == SOCKET_ERROR)
		{
			std::cout << "\nWaiting for incoming connections...\r\n";
			// Signal to accept the connection on this IP address on this Port number.
			TempSock = accept(Socket, NULL, NULL);
		}

		CreateThread(nullptr, 0, ClientThread, (void*)TempSock, 0, nullptr);

		std::cout << "Client connected And thread started\r\n\r\n";
	}



	//std::string s = "This is a string sent by the server.";

	//send(Socket, s.c_str(), 36, 0);	// Send the string (36 butes in this case).




	// Shutdown the socket.
	shutdown(Socket, SD_SEND);

	// Close our socket entirely.
	closesocket(Socket);

	// Cleanup Winsock - release any resources used by Winsock.
	WSACleanup();

	return 0;
}
