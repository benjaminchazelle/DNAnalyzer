/*************************************************************************
Mots - Classe de manipulation d'un ensemble de mots génétiques
-------------------
début                :	31/04/17
copyright            :	(C) 2017 par CHAZELLE
e-mail               :	benjamin.chazelle@insa-lyon.fr
*************************************************************************/

//--------- Réalisation de la classe <Mots> (fichier Mots.cpp) ---------//

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <exception>
#include <cstring>

//------------------------------------------------------ Include personnel

#include "Mots.h"

//----------------------------------------------------------------- PUBLIC

Mots* Mots::instanceMots = new Mots();

Mots & Mots::ObtenirInstance()
{
	return *(Mots::instanceMots);
}

unsigned int Mots::ObtenirIndex(const char mot[])
{
	//Verifi si le mot n'est pas un pointeur null
	if(mot == nullptr)
		throw invalid_argument("nullptr n'est pas autoriser pour cette method");

	//Recuperation d'un iterateur de chaque resultat obtenu (max 1)
	unordered_map<char*, unsigned int>::iterator t = mots.find((char*)mot);

	//Si l'iterateur est deja a la fin (pas de resultat)
	if (t == mots.end())
		throw range_error("mot non trouver");
	
	return t->second;
}

unsigned int Mots::InsererMot(const char mot[])
{
	//Verifi des paramétre
	if (mot == nullptr)
		throw invalid_argument("nullptr n'est pas autoriser pour cette method");

	//Recherche d'un mot deja present dans la map
	unordered_map<char*, unsigned int>::iterator t = mots.find((char*)mot);
	if (t != mots.end()) {
		throw overflow_error("Mot déja present");
	}

	//copy du mot a inserter
	char * str = new char[strlen(mot) + 1];
	strcpy(str, mot);

	//insertion du mot dans les maps
	pair<char*, unsigned int> pair1(str, this->counter);
	pair<unsigned int, char *> pair2(this->counter, str);
	mots.insert(pair1);
	mots_revers.insert(pair2);

	this->counter++;

	return this->counter-1;
}

char const * Mots::RecupererMot(const unsigned int i)
{
	if (i < 0 || i >= counter)
		throw range_error("Mot inexistant");

	return mots_revers[i];
}

unsigned int Mots::ObtenirNombreMots()
{
	return counter;
}

//----------------------------------------------------------------- PRIVEE


Mots::Mots()
{
	this->counter = 0;
}


Mots::~Mots()
{
}
