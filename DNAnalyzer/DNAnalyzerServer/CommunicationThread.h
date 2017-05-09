/*************************************************************************
CommunicationThread - Classe de [...]
-------------------
début                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//Interface de la classe <CommunicationThread> (CommunicationThread.h)  //

#if ! defined ( COMMUNICATION_THREAD_H )
#define COMMUNICATION_THREAD_H

//--------------------------------------------------- Interfaces utilisées

#include <winsock2.h>

using namespace std;


//------------------------------------------------------------------------
// Rôle de la classe <CommunicationThread>
//  La classe CommunicationThread de gérer le traitement d'une requête et 
//  l'envoit de sa réponse
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
	// Mode d'emploi : opérateur d'affectation, non implementé

	CommunicationThread(const CommunicationThread &);
	// Mode d'emploi : constructeur de copie, non implementé

	CommunicationThread(SOCKET * csock);
	// Mode d'emploi : constructeur, appel de traiter()

	virtual ~CommunicationThread();
	// Mode d'emploi : destructeur

protected:

	void traiter();
	// Mode d'emploi : lit le flux entrant sur la socket <csock> puis
	// transfert la requête au traitement Master spécifique

};

#endif