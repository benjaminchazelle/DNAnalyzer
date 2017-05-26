/*************************************************************************
Communication - Classe de gestion des communications réseaux
-------------------
début                :	10/05/17
copyright            :	(C) 2017 par CHAZELLE
e-mail               :	benjamin.chazelle@insa-lyon.fr
*************************************************************************/

// Réalisation de la classe <Communication> (fichier Communication.cpp) //

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

#include "stdafx.h"
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

//------------------------------------------------------ Include personnel

#include "Communication.h"
#include "Serveur.h"

//----------------------------------------------------------------- PUBLIC

string Communication::EnvoyerMessage(const Serveur & serveur, const string & message)
{
	// Initialisation WinSock
	WSADATA WSData;

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &WSData) != 0)
	{
		throw runtime_error("Winsock initialisation failed : " + WSAGetLastError());
	}

	printf("Initialised.\n");

	// Résolution de l'hostname

	char *hostname = new char[serveur.host.size() + 1];
	strcpy(hostname, serveur.host.c_str());

	char ip[100];
	struct hostent *he;
	struct in_addr **addr_list;

	if ((he = gethostbyname(hostname)) == NULL)
	{
		throw runtime_error("Hostname resolution failed : " + WSAGetLastError());
	}

	addr_list = (struct in_addr **) he->h_addr_list;

	for (int i = 0; addr_list[i] != NULL; i++)
	{
		strcpy(ip, inet_ntoa(*addr_list[i]));
		break;
	}

	// Création de la socket

	SOCKET sock;
	struct sockaddr_in sin;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		throw runtime_error("Socket creation failed : " + WSAGetLastError());
	}

	printf("Socket created.\n");

	// Connexion au serveur

	sin.sin_addr.s_addr = inet_addr(ip);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(serveur.port);
	int con = connect(sock, (struct sockaddr *)&sin, sizeof(sin));
	if (con < 0)
	{
		throw runtime_error("Connection failed : " + WSAGetLastError());
	}

	puts("Connected");

	// Envoi de la requête

	if (send(sock, message.c_str(), strlen(message.c_str()), 0) < 0)
	{
		throw runtime_error("Message sending fail : " + WSAGetLastError());
	}

	puts("Data Send\n");

	// Récéption de la réponse

	string response("");

	const int bufferSize = 512;
	char buffer[bufferSize + 1];

	int bytesReceived;

	do {

		bytesReceived = recv(sock, buffer, bufferSize, 0);

		if (bytesReceived == SOCKET_ERROR || bytesReceived == -1)
		{
			throw runtime_error("Response receiving fail : " + WSAGetLastError());
		}

		buffer[bytesReceived] = '\0';

		size_t len = response.size();

		response += buffer;

		size_t pos = response.rfind("\r\n\r\n");

		if (pos != string::npos) {

			response = response.substr(0, len + pos + 4);

			break;
		}

	} while (bytesReceived > 0);

	puts("Reply received\n");

	closesocket(sock);
	WSACleanup();

	return response;
}
