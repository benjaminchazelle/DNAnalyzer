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

//------------------------------------------------------ Include personnel

#include <exception>
#include "Mots.h"

//----------------------------------------------------------------- PUBLIC

Mots* Mots::instanceMots = new Mots();

Mots & Mots::ObtenirInstance()
{
	return *(Mots::instanceMots);
}

unsigned int Mots::ObtenirIndex(const char const mot[])//non tester
{
	if(mot == nullptr)
		throw invalid_argument("nullptr n'est pas autoriser pour cette method");
	char * str = new char[strlen(mot) + 1];
	strcpy(str, mot);
	unordered_map<char*, unsigned int>::iterator t = mots.find((char*)str);
	free(str);
	if (t == mots.end())
		throw range_error("mot non trouver");
	return t->second;
}

unsigned int Mots::InsererMot(const char const mot[])//non tester
{
	if (mot == nullptr)
		throw invalid_argument("nullptr n'est pas autoriser pour cette method");
	char * str = new char[strlen(mot) + 1];
	strcpy(str, mot);
	unordered_map<char*, unsigned int>::iterator t = mots.find((char*)str);
	if (t != mots.end()) {
		free(str);
		throw range_error("Mot deja present");
	}

	std::pair<char*, unsigned int> pair1(str, this->counter);
	std::pair<unsigned int, char *> pair2(this->counter, str);
	mots.insert(pair1);
	mots_revers.insert(pair2);

	this->counter++;

	free(str);

	return this->counter-1;
}

char const * Mots::RecupererMot(const unsigned int i)//non tester
{
	if (i < 0 || i >= counter)
		throw range_error("Mot inexistant");
	return mots_revers[i];
}

unsigned int Mots::ObtenirNombreMots()//non tester
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
