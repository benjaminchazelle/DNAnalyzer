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
	// Description : Socket du client

	string clientInfo;
	// Description : Adresse IP et port de connexion du client

	string requestBuffer;
	// Description : Buffer de lecture de la requête

public:

	void Traiter();
	// Mode d'emploi : Lit le flux entrant sur la socket <csock> puis
	//                 transfert la requête au traitement Master spécifique

	void Repondre(const string & reponse);
	// Mode d'emploi : Permet d'envoyer un message <reponse> sur le flux de sortie de la socket <csock>

	string LireLigne();
	// Mode d'emploi : Lit une ligne de la requête du client depuis le buffer, 
	//                 puis depuis la socket si le buffer ne contient pas de ligne entière
	// Exception "runtime_error" : Si un problème est survenu avec le serveur

	void FermerConnexion();
	// Mode d'emploi : Ferme la connexion avec le client

	CommunicationThread & operator = (const CommunicationThread &);
	// Mode d'emploi : Opérateur d'affectation, non implémenté

	CommunicationThread(const CommunicationThread &);
	// Mode d'emploi : Constructeur de copie, non implémenté

	CommunicationThread(Peer* peer);
	// Mode d'emploi : Constructeur, initalise les informations du client <peer> dans l'instance

	virtual ~CommunicationThread();
	// Mode d'emploi : Destructeur


};

#endif