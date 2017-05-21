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
#include <stdexcept>

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
}
void CommunicationThread::Traiter() {
	
	Master::InterpreterRequete(*this);

}

CommunicationThread::~CommunicationThread()
{
}

string CommunicationThread::LireLigne() {

	const string eolMarker = "\r\n";
	const size_t eolMarkerLength = eolMarker.size();


	if (requestBuffer.size() > 0) {

		size_t eolPosition = requestBuffer.find(eolMarker);

		if (eolPosition != string::npos) {

			string line = requestBuffer.substr(0, eolPosition);

			requestBuffer = requestBuffer.substr(eolPosition + eolMarkerLength);

			return line;

		}

	}

	int bytesReceived;

	do {

		const int inputBufferSize = 512;

		char inputBuffer[inputBufferSize + 1];

		bytesReceived = recv(*csock, inputBuffer, inputBufferSize, 0);

		if (bytesReceived > 0) {

			inputBuffer[bytesReceived] = '\0';

			size_t findFrom;

			if (requestBuffer.length() >= eolMarkerLength)
			{
				findFrom = requestBuffer.length() - eolMarkerLength;
			}
			else
			{
				findFrom = 0;
			}

			requestBuffer += inputBuffer;

			size_t eolPosition = requestBuffer.find(eolMarker, findFrom);

			if (eolPosition != string::npos) {

				string line = requestBuffer.substr(0, eolPosition);

				requestBuffer = requestBuffer.substr(eolPosition + eolMarkerLength);

				return line;

			}

		}
		else if (bytesReceived == 0) {

			cerr << "erreur"; // TODO

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

	return "";
}

void CommunicationThread::FermerConnexion() {

	unsigned int bytesReceived = shutdown(*csock, SD_SEND);

	if (bytesReceived == SOCKET_ERROR) {

		closesocket(*csock);
		WSACleanup();
	}

	printf("%s : Connection closed by server\n", clientInfo.c_str());


	delete csock;
}
//----------------------------------------------------------------- PRIVEE