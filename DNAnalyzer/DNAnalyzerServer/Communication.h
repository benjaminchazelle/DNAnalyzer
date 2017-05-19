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

	static HANDLE threadServeurHandle;
	// Description : thread du serveur

	static SOCKET sock;
	// Description : socket serveur d'�coute

	static Communication* instanceCommunication;
	// Description : Instance singleton de Communication

public:
	static Communication& ObtenirInstance();
	// Mode d'emploi : renvoit l'instance singleton de Communication

	void Ecouter(unsigned int port);
	// Mode d'emploi : lance un serveur sur le port <port>

	Communication & operator = (const Communication &);
	// Mode d'emploi : op�rateur d'affectation, non impl�ment�

	Communication(const Communication &);
	// Mode d'emploi : constructeur de copie, non impl�ment�

protected:

	static void recevoirRequete();
	// Mode d'emploi : attend une nouvelle connexion entrante puis lance un threadRequete

	static DWORD WINAPI threadRequete(void* p);
	// Mode d'emploi : lance le traitement d'une requ�te via cr�ation d'un CommunicationThread

	Communication();
	// Mode d'emploi : constructeur

	virtual ~Communication();
	// Mode d'emploi : destructeur
};

#endif