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

	static HANDLE threadServeurHandle;
	// Description : thread du serveur

	static SOCKET sock;
	// Description : socket serveur d'écoute

	static Communication* instanceCommunication;
	// Description : Instance singleton de Communication

public:
	static Communication& ObtenirInstance();
	// Mode d'emploi : renvoit l'instance singleton de Communication

	void Ecouter(unsigned int port);
	// Mode d'emploi : lance un serveur sur le port <port>

	Communication & operator = (const Communication &);
	// Mode d'emploi : opérateur d'affectation, non implémenté

	Communication(const Communication &);
	// Mode d'emploi : constructeur de copie, non implémenté

protected:

	static void recevoirRequete();
	// Mode d'emploi : attend une nouvelle connexion entrante puis lance un threadRequete

	static DWORD WINAPI threadRequete(void* p);
	// Mode d'emploi : lance le traitement d'une requête via création d'un CommunicationThread

	Communication();
	// Mode d'emploi : constructeur

	virtual ~Communication();
	// Mode d'emploi : destructeur
};

#endif