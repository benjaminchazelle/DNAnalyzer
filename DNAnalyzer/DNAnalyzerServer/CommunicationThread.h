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
#include <unordered_set>
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
	// Description : Socket du client

	string clientInfo;
	// Description : Adresse IP et port de connexion du client

	string requestBuffer;
	// Description : Buffer de lecture de la requ�te

public:

	void Traiter();
	// Mode d'emploi : Lit le flux entrant sur la socket <csock> puis
	//                 transfert la requ�te au traitement Master sp�cifique

	void Repondre(const string & reponse);
	// Mode d'emploi : Permet d'envoyer un message <reponse> sur le flux de sortie de la socket <csock>

	string LireLigne();
	// Mode d'emploi : Lit une ligne de la requ�te du client depuis le buffer, 
	//                 puis depuis la socket si le buffer ne contient pas de ligne enti�re
	// Exception "runtime_error" : Si un probl�me est survenu avec le serveur

	void FermerConnexion();
	// Mode d'emploi : Ferme la connexion avec le client

	CommunicationThread & operator = (const CommunicationThread &);
	// Mode d'emploi : Op�rateur d'affectation, non impl�ment�

	CommunicationThread(const CommunicationThread &);
	// Mode d'emploi : Constructeur de copie, non impl�ment�

	CommunicationThread(Peer* peer);
	// Mode d'emploi : Constructeur, initalise les informations du client <peer> dans l'instance

	virtual ~CommunicationThread();
	// Mode d'emploi : Destructeur


};

#endif