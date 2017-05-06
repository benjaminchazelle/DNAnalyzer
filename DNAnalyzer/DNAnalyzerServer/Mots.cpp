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

void Mots::RafraichirInstance()
{
	if (instanceMots != nullptr) {
		delete instanceMots;
	}

	instanceMots = new Mots();
}

unsigned int Mots::ObtenirIndex(const char mot[])
{
	// Vérifie si le mot n'est pas un pointeur null
	if(mot == nullptr)
		throw invalid_argument("Un pointeur null n'est pas autorisé pour cette méthode");

	// Récuperation d'un itérateur de chaque resultat obtenu (max 1)
	unordered_map<char*, unsigned int>::iterator t = mots.find((char*) mot);

	// Si l'itérateur est déjà à la fin (aucun résultat)
	if (t == mots.end())
		throw range_error("Mot non trouvé");
	
	return t->second;
}

unsigned int Mots::InsererMot(const char mot[])
{
	// Vérifie si le mot n'est pas un pointeur null
	if (mot == nullptr)
		throw invalid_argument("Un pointeur null n'est pas autorisé pour cette méthode");

	// Recherche d'un mot déjà présent dans la map
	unordered_map<char*, unsigned int>::iterator t = mots.find((char*) mot);
	if (t != mots.end()) {
		throw overflow_error("Mot déja present");
	}

	// Copie du mot à insérer
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
