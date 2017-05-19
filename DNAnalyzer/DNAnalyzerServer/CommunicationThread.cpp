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


CommunicationThread::CommunicationThread(Peer * peer) : csock(peer->csock), clientInfo(""), tailleRB(512), curseurPosRB(0), bytesReadRB(0), isCloseRB(false)
{
	clientInfo = string(inet_ntoa(peer->cin->sin_addr));
	clientInfo += ":" + to_string(peer->cin->sin_port);

	delete peer;
	readerBuffer = new char[tailleRB];
}
void CommunicationThread::traiter(){
	Master::InterpreterRequete(*this);

}

CommunicationThread::~CommunicationThread()
{
	delete[] readerBuffer;
}
string CommunicationThread::lireLigne() {
	if (isCloseRB) {
		throw runtime_error("socketIsCosed");
	}
	string res("");
	char lastChar('\0');
	while (1) {
		unsigned int startedPos = curseurPosRB;
		while (curseurPosRB < bytesReadRB) {
			if (lastChar = '\r' && readerBuffer[curseurPosRB] == '\n') {
				res.append(&readerBuffer[startedPos], (size_t)(curseurPosRB - startedPos - 2));
				return res;
			}
			lastChar = readerBuffer[curseurPosRB];
			curseurPosRB++;
		}
		res.append(&readerBuffer[startedPos], (size_t)(bytesReadRB - startedPos));
		curseurPosRB = 0;

		bytesReadRB = recv(*csock, readerBuffer, tailleRB, 0);

		if (bytesReadRB == 0) {
			isCloseRB = true;
			throw runtime_error("socketIsCosed");
		}
		else if (bytesReadRB < 0) {

			isCloseRB = true;

			if (10054 == WSAGetLastError()) {
				printf("%s : Connection closed by client\n", clientInfo.c_str());
			}
			else
			{
				printf("%s : Error %d during receiving\n", clientInfo.c_str(), WSAGetLastError());
			}
			throw runtime_error("socketFail");
		}

		if (lastChar == '\r'&&readerBuffer[0] == '\n') {
			res = res.substr(res.length() - 1);
			curseurPosRB++;
			return res;
		}
	}
}
void CommunicationThread::close() {

	unsigned int bytesReceived = shutdown(*csock, SD_SEND);

	if (bytesReceived == SOCKET_ERROR) {

		closesocket(*csock);
		WSACleanup();
	}

	printf("%s : Connection closed by server\n", clientInfo.c_str());


	delete csock;
}
//----------------------------------------------------------------- PRIVEE