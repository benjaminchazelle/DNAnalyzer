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
#include "Log.h"

//----------------------------------------------------------------- PUBLIC

Communication* Communication::instanceCommunication;

Communication & Communication::ObtenirInstance()
{
	return *(Communication::instanceCommunication);
}

void Communication::Ecouter(unsigned int port)
{
	LOG(T_DEBUG) << "[Communication] call Ecoute("<<port<<")";
	// Initialisation du serveur

	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 0), &WSAData);

	SOCKADDR_IN sin;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);

	if (bind(sock, (SOCKADDR *)&sin, sizeof(sin)) < 0)
	{
		LOG(T_ERROR) << "[Communication] Server binding error";
		throw runtime_error("Server binding error");
	}

	if (listen(sock, 0) < 0)
	{
		LOG(T_ERROR) << "[Communication] Server listening error";
		throw runtime_error("Server listening error");
	}

	LOG(T_INFO) << "[Communication] DNAnalyzer Server listening on port " << port;

	// Récéption des requêtes des clients
	while (1)
	{
		recevoirRequete();
	}
	LOG(T_DEBUG) << "[Communication] end Ecoute (exit of while 1 !!!)";
}

//----------------------------------------------------------------- PRIVEE

void Communication::recevoirRequete()
{
	LOG(T_DEBUG) << "[Communication] call recevoirRequete";
	SOCKET* csock = new SOCKET();

	SOCKADDR_IN* cin = new SOCKADDR_IN();

	int addrlen = sizeof(SOCKADDR_IN);

	// On attend la connexion d'un client
	if ((*csock = accept(sock, (SOCKADDR *)cin, &addrlen)) != INVALID_SOCKET)
	{
		LOG(T_DEBUG) << "[Communication] socket valide";
		Peer* peer = new Peer;
		peer->cin = cin;
		peer->csock = csock;

		// On lance un thread pour traiter la requête du client en parallèle
		threadServeurHandle = CreateThread(NULL, 0, &(Communication::threadRequete), peer, 0, NULL);

		if (threadServeurHandle != NULL) {

			LOG(T_INFO) << "[Communication] " <<inet_ntoa(cin->sin_addr)<<":"<< cin->sin_port <<" : Client accepted";

		}
		else {

			LOG(T_INFO) << "[Communication] " << inet_ntoa(cin->sin_addr) << ":" << cin->sin_port << " :  : Client refused (thread issue "<<  GetLastError()<<")";

			delete csock;
		}
	}
	else {

		LOG(T_INFO) << "[Communication] Client refused (connection issue)";
		delete csock;
	}
	LOG(T_DEBUG) << "[Communication] end recevoirRequete";
}

DWORD Communication::threadRequete(void * p)
{
	// Délégation du traitement de la requête à CommunciationThread::Traiter
	CommunicationThread t((Peer*) p);

	t.Traiter();

	return 0;
}

Communication::Communication()
{
	threadServeurHandle = NULL;
}


Communication::~Communication()
{
}
