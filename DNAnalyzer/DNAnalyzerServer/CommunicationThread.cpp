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
	LOG(T_DEBUG) << "[CommunicationThread] c:" << this << " call Repondre";
	// Envoit un message sur la socket 
	int bytesSent = send(*csock, reponse.c_str(), reponse.length(), 0);

	if (bytesSent == SOCKET_ERROR) {

		if (10054 == WSAGetLastError()) {
			LOG(T_WARN) << "[CommunicationThread] c:" << this << " : Connection closed by client";
		}
		else
		{
			LOG(T_WARN) << "[CommunicationThread] c:" << this << " : Error " << WSAGetLastError() << " during responding";
		}

		return;
	}

	LOG(T_INFO) << "[CommunicationThread] c:" << this << " : Response sent (" << bytesSent << " bytes)";
	LOG(T_DEBUG) << "[CommunicationThread] c:" << this << " end Repondre";
}


CommunicationThread::CommunicationThread(Peer * peer) : csock(peer->csock), clientInfo("")
{
	// Initialisation des données du client dans le CommunicationThread
	clientInfo = string(inet_ntoa(peer->cin->sin_addr));
	clientInfo += ":" + to_string(peer->cin->sin_port);

	LOG(T_INFO) << "[CommunicationThread] New client " << clientInfo << " id : " << this;

	delete peer;
}
void CommunicationThread::Traiter() {
	
	// Délégation du traitement de la requête au Master
	Master::InterpreterRequete(*this);

}

CommunicationThread::~CommunicationThread()
{
}

string CommunicationThread::LireLigne() {

	const string eolMarker = "\r\n";
	const size_t eolMarkerLength = eolMarker.size();

	// Si le buffer est déjà rempli, on essaye d'y lire une ligne
	if (requestBuffer.size() > 0) {

		size_t eolPosition = requestBuffer.find(eolMarker);

		// Si on a trouvé une ligne, on la renvoie
		if (eolPosition != string::npos) {

			string line = requestBuffer.substr(0, eolPosition);

			requestBuffer = requestBuffer.substr(eolPosition + eolMarkerLength);

			return line;

		}

	}

	// Si aucune ligne n'était dans le buffer, on lit le flux d'entrée réseau

	int bytesReceived;

	do {

		const int inputBufferSize = 512;

		char inputBuffer[inputBufferSize + 1];

		bytesReceived = recv(*csock, inputBuffer, inputBufferSize, 0);

		if (bytesReceived > 0) {

			// Si on a réussi à lire le réseau, on y cherche une ligne
			// On met à jour le buffer

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
		else {

			// Si une erreur survient

			if (10054 == WSAGetLastError()) {
				LOG(T_WARN) << "[CommunicationThread] c:" << this << " Connection closed by client ";
			}
			else
			{
				LOG(T_WARN) << "[CommunicationThread] c:" << this << " Error " << WSAGetLastError() << " during receiving\n ";
			}


			break;
		}

	} while (bytesReceived > 0);

	return "";
}

void CommunicationThread::FermerConnexion() {

	// On ferme proprement la connexion
	LOG(T_DEBUG) << "[CommunicationThread] c:" << this << " call FermerConnexion";

	unsigned int bytesReceived = shutdown(*csock, SD_SEND);

	if (bytesReceived == SOCKET_ERROR) {

		closesocket(*csock);
		WSACleanup();
	}

	LOG(T_DEBUG) << "[CommunicationThread] c:" << this << " : Connection closed by server";


	delete csock;
	LOG(T_DEBUG) << "[CommunicationThread] c:" << this << " end FermerConnexion";
}
//----------------------------------------------------------------- PRIVEE