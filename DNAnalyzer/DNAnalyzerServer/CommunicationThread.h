/*************************************************************************
CommunicationThread - Classe de traitement d'une requête
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
#include <unordered_set>
using namespace std;


struct Peer {
	SOCKADDR_IN* cin;
	SOCKET* csock;
};

//------------------------------------------------------------------------
// Rôle de la classe <CommunicationThread>
//  La classe CommunicationThread de gérer le traitement d'une requête et 
//  l'envoit de sa réponse
//------------------------------------------------------------------------


class CommunicationThread
{
protected:

	SOCKET * csock;
	// Description : socket clientInfo

	string clientInfo;
	// Description : adresse ip et port de connexion du clientInfo

	string requestBuffer;
	// Description : buffer de lecture de la requête

public:

	void Traiter();
	// Mode d'emploi : lit le flux entrant sur la socket <csock> puis
	// transfert la requête au traitement Master spécifique

	void Repondre(const string & reponse);
	// Mode d'emploi : permet d'envoyer un flux de sortie sur la socket
	// <csock>

	string LireLigne();
	// Mode d'emploi : lit une ligne de la requête du client depuis le buffer, 
	// puis depuis la socket si le buffer ne contient pas de ligne entière
	//runtime_error -> connexion FermerConnexion

	void FermerConnexion();
	// Mode d'emploi : ferme la connexion avec le client

	CommunicationThread & operator = (const CommunicationThread &);
	// Mode d'emploi : opérateur d'affectation, non implémenté

	CommunicationThread(const CommunicationThread &);
	// Mode d'emploi : constructeur de copie, non implémenté

	CommunicationThread(Peer* peer);
	// Mode d'emploi : constructeur

	virtual ~CommunicationThread();
	// Mode d'emploi : destructeur


};

#endif