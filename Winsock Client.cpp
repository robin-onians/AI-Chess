
// Creates a Winsock 'client' application.
// This application will try to conect to then obtain data from a 'server' application.

//#include "stdafx.h"
//
//#include <iostream>
//#include <winsock2.h>
//#include <vector>
//#include <list>
//#include <deque>
//#include <istream>
//
//#pragma comment(lib,"ws2_32.lib") 	// Use this library whilst linking - contains the Winsock2 implementation.

//int main()
//{
//	// Initialise Winsock
//	WSADATA WsaDat;
//	if (WSAStartup(MAKEWORD(2, 2), &WsaDat) != 0)
//	{
//		std::cout << "Winsock error - Winsock initialization failed\r\n";
//		WSACleanup();
//		return 0;
//	}
//
//	// Create our socket
//	SOCKET Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
//	if (Socket == INVALID_SOCKET)
//	{
//		std::cout << "Winsock error - Socket creation Failed!\r\n";
//		WSACleanup();
//		return 0;
//	}
//
//	// Resolve IP address for hostname.
//	struct hostent* host;
//
//	// Change this to point to server, or ip address...
//
//	if ((host = gethostbyname("localhost")) == NULL)   // In this case 'localhost' is the local machine. Change this to a proper IP address if connecting to another machine on the network.
//	{
//		std::cout << "Failed to resolve hostname.\r\n";
//		WSACleanup();
//		return 0;
//	}
//
//
//	// Sockets has now been initialised, so now can send some data to the server....
//
//
//	const int buffer_size = 1024;
//	char buffer[1024];
//	SecureZeroMemory(&buffer, buffer_size);
//
//	struct sockaddr_in server_address;
//	int server_address_size = (int)sizeof(server_address);
//	short port = 8888;	// Port number - can change this, but needs to be the same on both client and server.
//	const char* server_ip_address = "127.0.0.1";	// The local host - change this for proper IP address of server if not on the local machine.
//	server_address.sin_family = AF_INET;
//	server_address.sin_port = htons(port);
//	server_address.sin_addr.s_addr = inet_addr(server_ip_address);
//
//	std::cout << "Enter a string to send: ";
//	std::cin >> buffer;
//
//	std::cout << std::endl;
//	std::cout << "Sending datagram to the server." << std::endl;
//
//	//send data to server address
//	int clientResult = sendto(Socket, buffer, buffer_size, 0, (SOCKADDR*)&server_address, server_address_size);
//
//	// Sent the data, now wait for acknowledgement coming back...
//
//	//get some acknowldgment from server and data back
//	int bytes_received = recvfrom(Socket, buffer, buffer_size, 0, (SOCKADDR*)&server_address, &server_address_size);
//
//	if (bytes_received == SOCKET_ERROR)
//	{	// If there is an error, deal with it here...
//		std::cout << "recvfrom failed with error " << WSAGetLastError();
//	}
//	else
//	{
//		std::string acknowledge = buffer;
//		std::cout << acknowledge.c_str() << std::endl;
//		// At this point we have received an acknowledgement from the server, so we can carry on...
//	}
//
//	// Shutdown our socket.
//	shutdown(Socket, SD_SEND);
//
//	// Close our socket entirely.
//	closesocket(Socket);
//
//	// Cleanup Winsock.
//	WSACleanup();
//	system("PAUSE");
//	return 0;
//}