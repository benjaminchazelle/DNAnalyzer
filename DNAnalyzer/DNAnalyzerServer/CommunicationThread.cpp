/*************************************************************************
CommunicationThread - Classe de [...]
-------------------
début                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//--------- Réalisation de la classe <CommunicationThread> (fichier CommunicationThread.cpp) ---------//

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

#include <string>

//------------------------------------------------------ Include personnel

#include "CommunicationThread.h"

//----------------------------------------------------------------- PUBLIC

void CommunicationThread::traiter()
{
	/* EXAMPLE
	cout << "Traiter" << endl;

	string request("");

	int iResult;
	// Receive until the peer shuts down the connection
	do {

		const int recvbuflen = 512;
		char recvbuf[recvbuflen + 1];



		iResult = recv(*csock, recvbuf, recvbuflen, 0);
		cout << "recv " << iResult << endl;

		if (iResult > 0) {

			
			//char* sub = new char[iResult + 1];
			//memcpy(sub, &recvbuf[recvbuflen], iResult);
			//sub[iResult] = '\0';
			


			//cout << "iResult" << iResult << endl;
			recvbuf[iResult] = '\0';

			request += recvbuf;

			cout << "nreq " << request << endl;

			if (request.rfind("\r\n\r\n") != string::npos || request.rfind(";\r\n") != string::npos) {
				Master::Handle(request, *this);

				break;
			}



			//printf("Bytes received: %d\n", iResult);

			// Echo the buffer back to the sender

			//					cout << recvbuf;


		}
		else if (iResult == 0) {

			cout << "pre handle" << endl;

			Master::Handle(request, *this);

			printf("Connection closing...\n");
		}
		else {
			printf("recv failed with error: %d\n", WSAGetLastError());
			//closesocket(*csock);
			//WSACleanup();
			//return 1;
			break;
		}

	} while (iResult > 0);

	// shutdown the connection since we're done
	iResult = shutdown(*csock, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(*csock);
		WSACleanup();
		//	return 1;
	}
	*/

}


void CommunicationThread::Repondre(string & reponse)
{
	/* EXAMPLE pour un paramétre (string msg)
	int iSendResult = send(*csock, msg.c_str(), msg.length(), 0);
	if (iSendResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(*csock);
		WSACleanup();
		//	return 1;
	}
	printf("Bytes sent: %d\n", iSendResult);
	*/
}


CommunicationThread::CommunicationThread(SOCKET * csock)
{
	/* EXEMPLE
	cout << "Thread inited" << endl;
	Traiter();
	*/
}

CommunicationThread::~CommunicationThread()
{
}

//----------------------------------------------------------------- PRIVEE

