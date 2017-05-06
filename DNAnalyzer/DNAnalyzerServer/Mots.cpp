/*************************************************************************
Mots - Classe de manipulation d'un ensemble de mots g�n�tiques
-------------------
d�but                :	31/04/17
copyright            :	(C) 2017 par CHAZELLE
e-mail               :	benjamin.chazelle@insa-lyon.fr
*************************************************************************/

//--------- R�alisation de la classe <Mots> (fichier Mots.cpp) ---------//

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me
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

void Mots::RafraichirInstance()
{
	if (instanceMots != nullptr) {
		delete instanceMots;
	}

	instanceMots = new Mots();
}

unsigned int Mots::ObtenirIndex(const char mot[])
{
	// V�rifie si le mot n'est pas un pointeur null
	if(mot == nullptr)
		throw invalid_argument("Un pointeur null n'est pas autoris� pour cette m�thode");

	// R�cuperation d'un it�rateur de chaque resultat obtenu (max 1)
	unordered_map<char*, unsigned int>::iterator t = mots.find((char*) mot);

	// Si l'it�rateur est d�j� � la fin (aucun r�sultat)
	if (t == mots.end())
		throw range_error("Mot non trouv�");
	
	return t->second;
}

unsigned int Mots::InsererMot(const char mot[])
{
	// V�rifie si le mot n'est pas un pointeur null
	if (mot == nullptr)
		throw invalid_argument("Un pointeur null n'est pas autoris� pour cette m�thode");

	// Recherche d'un mot d�j� pr�sent dans la map
	unordered_map<char*, unsigned int>::iterator t = mots.find((char*) mot);
	if (t != mots.end()) {
		throw overflow_error("Mot d�ja present");
	}

	// Copie du mot � ins�rer
	char* str = new char[strlen(mot) + 1];
	strcpy(str, mot);

	// Insertion du mot dans les maps
	pair<char*, unsigned int> pair1(str, counter);
	pair<unsigned int, char*> pair2(counter, str);
	mots.insert(pair1);
	mots_revers.insert(pair2);

	counter++;

	return counter - 1;
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


Mots::Mots() : counter(0)
{
}


Mots::~Mots()
{
}
