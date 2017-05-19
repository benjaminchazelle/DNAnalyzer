/*************************************************************************
Communication - Classe de gestion des communications réseaux
-------------------
début                :	10/05/17
copyright            :	(C) 2017 par CHAZELLE
e-mail               :	benjamin.chazelle@insa-lyon.fr
*************************************************************************/

//   Interface de la classe <Communication> (fichier Communication.h)   //

#if ! defined ( COMMUNICATION_H )
#define COMMUNICATION_H

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <string>

#include "Serveur.h"

using namespace std;

//------------------------------------------------------------------------
// Rôle de la classe <Communication>
//  La classe Communication permet d'envoyer des requêtes réseaux aux
//  serveurs, et de recevoir leur réponse
//------------------------------------------------------------------------

class Communication
{
public:

	static string EnvoyerMessage(const struct Serveur & serveur, const string & message);
	// Mode d'emploi : envoie une requête <message> au serveur <serveur> et renvoie sa réponse
	// Exception "runtime_error" : si une erreur de communication survient

	Communication & operator = (const Communication &);
	// Mode d'emploi : opérateur d'affectation, non implémenté
	
	Communication (const Communication &);
	// Mode d'emploi : constructeur de copie, non implémenté

protected:

	Communication();
	// Mode d'emploi : constructeur, non implémenté

	~Communication();
	// Mode d'emploi : destructeur, non implémenté

};

#endif