/*************************************************************************
CommunicationThread - Classe de [...]
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


//------------------------------------------------------------------------
// R�le de la classe <CommunicationThread>
//  La classe CommunicationThread de g�rer le traitement d'une requ�te et 
//  l'envoit de sa r�ponse
//------------------------------------------------------------------------


class CommunicationThread
{
protected:

	SOCKET * csock;
	// Description : socket client

public:
	void Repondre(string & reponse);
	// Mode d'emploi : permet d'envoyer un flux de sortie sur la socket
	// <csock> puis de fermer la connexion

	CommunicationThread & operator = (const CommunicationThread &);
	// Mode d'emploi : op�rateur d'affectation, non implement�

	CommunicationThread(const CommunicationThread &);
	// Mode d'emploi : constructeur de copie, non implement�

	CommunicationThread(SOCKET * csock);
	// Mode d'emploi : constructeur, appel de traiter()

	virtual ~CommunicationThread();
	// Mode d'emploi : destructeur

protected:

	void traiter();
	// Mode d'emploi : lit le flux entrant sur la socket <csock> puis
	// transfert la requ�te au traitement Master sp�cifique

};

#endif