/*************************************************************************
Dictionnaire - Classe de stockage des donn�es de maladie
-------------------
d�but                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//--------- R�alisation de la classe <Dictionnaire> (fichier Dictionnaire.cpp) ---------//

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me

//------------------------------------------------------ Include personnel

#include "Dictionnaire.h"
#include <string>

//----------------------------------------------------------------- PUBLIC


Dictionnaire & Dictionnaire::ObtenirInstance()
{
	// TODO: changer le retour par l'instance du singleton
	return *((Dictionnaire*) nullptr);
}

//----------------------------------------------------------------- PRIVEE
const Maladie Dictionnaire::ObtenirMaladie(const string name) {
	// TODO
	return Maladie();
}

const unordered_set<const Maladie *> ObtenirMaladies(const unsigned int indexMot) {
	// TODO
	return unordered_set<const Maladie *>();
}

const unordered_set<string> ObtenirNomsMaladies() {
	// TODO
	return unordered_set<string>();
}


Dictionnaire::Dictionnaire(string path_dictionnaire)
{
}


Dictionnaire::~Dictionnaire()
{
}
