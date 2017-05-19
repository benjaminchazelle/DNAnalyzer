/*************************************************************************
CommunicationThread - Classe de traitement d'une requ�te
-------------------
d�but                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//Interface de la classe <CommunicationThread> (CommunicationThread.h)  //

#if ! defined ( COMMUNICATION_THREAD_H )
#define COMMUNICATION_THREAD_H

//--------------------------------------------------- Interfaces utilis�es

#include <winsock2.h>

using namespace std;


struct Peer {
	SOCKADDR_IN* cin;
	SOCKET* csock;
};

//------------------------------------------------------------------------
// R�le de la classe <CommunicationThread>
//  La classe CommunicationThread de g�rer le traitement d'une requ�te et 
//  l'envoit de sa r�ponse
//------------------------------------------------------------------------


class CommunicationThread
{
protected:

	SOCKET * csock;
	// Description : socket clientInfo

	string clientInfo;
	// Description : adresse ip et port de connexion du clientInfo

public:
	void Repondre(const string & reponse);
	// Mode d'emploi : permet d'envoyer un flux de sortie sur la socket
	// <csock> puis de fermer la connexion

	CommunicationThread & operator = (const CommunicationThread &);
	// Mode d'emploi : op�rateur d'affectation, non impl�ment�

	CommunicationThread(const CommunicationThread &);
	// Mode d'emploi : constructeur de copie, non impl�ment�

	CommunicationThread(Peer* peer);
	// Mode d'emploi : constructeur, appel de traiter()

	virtual ~CommunicationThread();
	// Mode d'emploi : destructeur

protected:

	void traiter();
	// Mode d'emploi : lit le flux entrant sur la socket <csock> puis
	// transfert la requ�te au traitement Master sp�cifique

};

#endif