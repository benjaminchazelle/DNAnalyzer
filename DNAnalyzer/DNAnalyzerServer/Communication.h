/*************************************************************************
Communication - Classe de r�c�ption des requ�tes r�seau
-------------------
d�but                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//   Interface de la classe <Communication> (fichier Communication.h)   //

#if ! defined ( COMMUNICATION_H )
#define COMMUNICATION_H

//--------------------------------------------------- Interfaces utilis�es
#include <winsock2.h>

using namespace std;


//------------------------------------------------------------------------
// R�le de la classe <Communication>
//  La classe Communication est charg�e, au moyen de serveur, de recevoir
//  des requ�tes r�seaux et de les achemnier pour traitement
//------------------------------------------------------------------------


class Communication
{
protected:

	HANDLE threadServeurHandle;
	// Description : Instance thread du serveur

	SOCKET sock;
	// Description : Socket serveur d'�coute

	static Communication* instanceCommunication;
	// Description : Instance singleton de Communication

public:
	static Communication& ObtenirInstance();
	// Mode d'emploi : Renvoie l'instance singleton de Communication

	void Ecouter(unsigned int port);
	// Mode d'emploi : Lance un serveur sur le port <port>
	// Exception "runtime_error" : Si le serveur ne peut se lancer

	Communication & operator = (const Communication &);
	// Mode d'emploi : Op�rateur d'affectation, non impl�ment�

	Communication(const Communication &);
	// Mode d'emploi : Constructeur de copie, non impl�ment�

protected:

	void recevoirRequete();
	// Mode d'emploi : Attend une nouvelle connexion entrante puis lance un threadRequete

	static DWORD WINAPI threadRequete(void* p);
	// Mode d'emploi : Lance le traitement d'une requ�te via cr�ation d'un CommunicationThread
	// Le thread re�oit un Peer* <p> pointant vers les informations du client

	Communication();
	// Mode d'emploi : Constructeur

	virtual ~Communication();
	// Mode d'emploi : Destructeur
};

#endif