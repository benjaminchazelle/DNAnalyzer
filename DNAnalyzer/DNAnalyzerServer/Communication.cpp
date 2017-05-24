/*************************************************************************
Communication - Classe de récéption des requêtes réseau
-------------------
début                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

// Réalisation de la classe <Communication> (fichier Communication.cpp) //

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <winsock2.h>
#include <iostream>
#include <string>
//------------------------------------------------------ Include personnel

#include "Communication.h"
#include "CommunicationThread.h"

//----------------------------------------------------------------- PUBLIC

HANDLE Communication::threadServeurHandle = NULL;

SOCKET Communication::sock;

Communication* Communication::instanceCommunication;

Communication & Communication::ObtenirInstance()
{
	return *(Communication::instanceCommunication);
}

void Communication::Ecouter(unsigned int port)
{
	// Initialisation du serveur

	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 0), &WSAData);

	SOCKADDR_IN sin;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);

	bind(sock, (SOCKADDR *)&sin, sizeof(sin));

	listen(sock, 0);

	cout << "DNAnalyzer Server listening on port " << port << endl;

	// Récéption des requêtes des clients
	while (1)
	{
		recevoirRequete();
	}
}

//----------------------------------------------------------------- PRIVEE

void Communication::recevoirRequete()
{
	SOCKET* csock = new SOCKET();

	SOCKADDR_IN* cin = new SOCKADDR_IN();

	int addrlen = sizeof(SOCKADDR_IN);

	// On attend la connexion d'un client
	if ((*csock = accept(sock, (SOCKADDR *)cin, &addrlen)) != INVALID_SOCKET)
	{		
		Peer* peer = new Peer;
		peer->cin = cin;
		peer->csock = csock;

		// On lance un thread pour traiter la requête du client en parallèle
		threadServeurHandle = CreateThread(NULL, 0, &Communication::threadRequete, peer, 0, NULL);

		if (threadServeurHandle != NULL) {

			printf("%s:%d : Client accepted\n", inet_ntoa(cin->sin_addr), cin->sin_port);

		}
		else {

			printf("%s:%d : Client refused (thread issue %d)\n", inet_ntoa(cin->sin_addr), cin->sin_port, GetLastError());

			delete csock;
		}
	}
	else {

		printf("Client refused (connection issue)\n");
		delete csock;
	}
}

DWORD Communication::threadRequete(void * p)
{
	// Délégation du traitement de la requpete à CommunciationThread::Traiter
	CommunicationThread t((Peer*) p);

	t.Traiter();

	return 0;
}

Communication::Communication()
{
}


Communication::~Communication()
{
}
