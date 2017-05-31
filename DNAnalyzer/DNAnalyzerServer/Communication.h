/*************************************************************************
Communication - Classe de récéption des requêtes réseau
-------------------
début                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//   Interface de la classe <Communication> (fichier Communication.h)   //

#if ! defined ( COMMUNICATION_H )
#define COMMUNICATION_H

//--------------------------------------------------- Interfaces utilisées
#include <winsock2.h>

using namespace std;


//------------------------------------------------------------------------
// Rôle de la classe <Communication>
//  La classe Communication est chargée, au moyen de serveur, de recevoir
//  des requêtes réseaux et de les achemnier pour traitement
//------------------------------------------------------------------------


class Communication
{
protected:

	HANDLE threadServeurHandle;
	// Description : Instance thread du serveur

	SOCKET sock;
	// Description : Socket serveur d'écoute

	static Communication* instanceCommunication;
	// Description : Instance singleton de Communication

public:
	static Communication& ObtenirInstance();
	// Mode d'emploi : Renvoie l'instance singleton de Communication

	void Ecouter(unsigned int port);
	// Mode d'emploi : Lance un serveur sur le port <port>
	// Exception "runtime_error" : Si le serveur ne peut se lancer

	Communication & operator = (const Communication &);
	// Mode d'emploi : Opérateur d'affectation, non implémenté

	Communication(const Communication &);
	// Mode d'emploi : Constructeur de copie, non implémenté

protected:

	void recevoirRequete();
	// Mode d'emploi : Attend une nouvelle connexion entrante puis lance un threadRequete

	static DWORD WINAPI threadRequete(void* p);
	// Mode d'emploi : Lance le traitement d'une requête via création d'un CommunicationThread
	// Le thread reçoit un Peer* <p> pointant vers les informations du client

	Communication();
	// Mode d'emploi : Constructeur

	virtual ~Communication();
	// Mode d'emploi : Destructeur
};

#endif