/*************************************************************************
CommunicationThread - Classe de [...]
-------------------
d�but                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//----------- Interface de la classe <CommunicationThread> (fichier CommunicationThread.h)  ----------//

#if ! defined ( COMMUNICATION_THREAD_H )
#define COMMUNICATION_THREAD_H

//--------------------------------------------------- Interfaces utilis�es

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;


//------------------------------------------------------------------------
// R�le de la classe <CommunicationThread>
//  La classe CommunicationThread permet [...
//  ...]
//------------------------------------------------------------------------


class CommunicationThread
{
protected:

	SOCKET * csock;
	//socket de la communication entre le serveur et le cleint

	void Traiter();
	// Methode de utiliser pour la resseption de la requette

public:
	void Repondre(const unsigned char data[],const unsigned int longeur);
	// Permet de repondre a une requette d'un client

	CommunicationThread & operator = (const CommunicationThread &);
	// Mode d'emploi : op�rateur d'affectation, non implement�

	CommunicationThread(const CommunicationThread &);
	// Mode d'emploi : constructeur de copie, non implement�

	CommunicationThread(SOCKET * csock);
	// Mode d'emploi : constructeur


	virtual ~CommunicationThread();
};

#endif