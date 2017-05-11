/*************************************************************************
Dictionnaire - Classe de stockage des données de maladies
-------------------
début                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//- Réalisation de la classe <Dictionnaire> (fichier Dictionnaire.cpp) -//

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel

#include "Dictionnaire.h"
#include <string>

//----------------------------------------------------------------- PUBLIC


Dictionnaire & Dictionnaire::ObtenirInstance()
{
	// TODO: changer le retour par l'instance du singleton
	return *((Dictionnaire*) nullptr);
}

void Dictionnaire::RafraichirInstance()
{
	/* EXEMPLE
	if (instanceMots != nullptr) {
		delete instanceMots;
	}

	instanceMots = new Mots();
	*/
}

void Dictionnaire::ChargerFichier(const string & fichierDico)
{
	// TODO
}

const Maladie & Dictionnaire::ObtenirMaladie(const string & name) {
	// TODO
	return Maladie();
}

const unordered_set<Maladie *> Dictionnaire::ObtenirMaladies(const unsigned int indexMot) {
	// TODO
	return unordered_set< Maladie *>();
}

const unordered_set<string> Dictionnaire::ObtenirNomsMaladies() {
	// TODO
	return unordered_set<string>();
}


//----------------------------------------------------------------- PRIVEE

Dictionnaire::Dictionnaire()
{
}


Dictionnaire::~Dictionnaire()
{
}
