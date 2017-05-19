/*************************************************************************
CommunicationThread -  Classe de traitement d'une requête
-------------------
début                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

// Réalisation de la classe <CommunicationThread> (CommunicationThread.cpp)//

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <string>

//------------------------------------------------------ Include personnel

#include "CommunicationThread.h"
#include "Master.h"

//----------------------------------------------------------------- PUBLIC

void CommunicationThread::Repondre(const string & reponse)
{
	int bytesSent = send(*csock, reponse.c_str(), reponse.length(), 0);
	
	if (bytesSent == SOCKET_ERROR) {

		printf("%s : Error %d during responding\n", clientInfo.c_str(), WSAGetLastError());

		closesocket(*csock);
		WSACleanup();
	}

	printf("%s : Response sent (%d bytes)\n", clientInfo.c_str(), bytesSent);
}


CommunicationThread::CommunicationThread(Peer * peer) : csock(peer->csock), clientInfo("")
{
	clientInfo = string(inet_ntoa(peer->cin->sin_addr));
	clientInfo += ":" + to_string(peer->cin->sin_port);

	delete peer;

	traiter();
}

CommunicationThread::~CommunicationThread()
{
}

//----------------------------------------------------------------- PRIVEE

void CommunicationThread::traiter()
{
	string request("");

	int bytesReceived;

	do {

		const int bufferSize = 512;

		char buffer[bufferSize + 1];

		bytesReceived = recv(*csock, buffer, bufferSize, 0);

		if (bytesReceived > 0) {

			buffer[bytesReceived] = '\0';

			request += buffer;

			if (request.rfind("\r\n\r\n") != string::npos || request.rfind(";\r\n") != string::npos) {

				Master::InterpreterRequete(request, *this);

				break;
			}

		}
		else if (bytesReceived == 0) {

			Master::InterpreterRequete(request, *this);

			break;
		}
		else {

			if (10054 == WSAGetLastError()) {
				printf("%s : Connection closed by client\n", clientInfo.c_str());
			}
			else
			{
				printf("%s : Error %d during receiving\n", clientInfo.c_str(), WSAGetLastError());
			}

			
			break;
		}

	} while (bytesReceived > 0);

	bytesReceived = shutdown(*csock, SD_SEND);

	if (bytesReceived == SOCKET_ERROR) {

		closesocket(*csock);
		WSACleanup();
	}

	printf("%s : Connection closed by server\n", clientInfo.c_str());
	

	delete csock;

}