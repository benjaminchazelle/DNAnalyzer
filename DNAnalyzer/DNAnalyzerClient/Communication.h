/*************************************************************************
Communication - Classe de gestion des communications r�seaux
-------------------
d�but                :	10/05/17
copyright            :	(C) 2017 par CHAZELLE
e-mail               :	benjamin.chazelle@insa-lyon.fr
*************************************************************************/

//   Interface de la classe <Communication> (fichier Communication.h)   //

#if ! defined ( COMMUNICATION_H )
#define COMMUNICATION_H

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me
#include <string>

#include "Serveur.h"

using namespace std;

//------------------------------------------------------------------------
// R�le de la classe <Communication>
//  La classe Communication permet d'envoyer des requ�tes r�seaux aux
//  serveurs, et de recevoir leur r�ponse
//------------------------------------------------------------------------

class Communication
{
public:

	static string EnvoyerMessage(const struct Serveur & serveur, const string & message);
	// Mode d'emploi : envoie une requ�te <message> au serveur <serveur> et renvoie sa r�ponse
	// Exception "runtime_error" : si une erreur de communication survient

	Communication & operator = (const Communication &);
	// Mode d'emploi : op�rateur d'affectation, non impl�ment�
	
	Communication (const Communication &);
	// Mode d'emploi : constructeur de copie, non impl�ment�

protected:

	Communication();
	// Mode d'emploi : constructeur, non impl�ment�

	~Communication();
	// Mode d'emploi : destructeur, non impl�ment�

};

#endif