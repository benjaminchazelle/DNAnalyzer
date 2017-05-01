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

#include "Mots.h"

//----------------------------------------------------------------- PUBLIC


Mots & Mots::ObtenirInstance()
{
	// TODO: changer le retour par l'instance du singleton
	return *((Mots*) nullptr);
}

unsigned int Mots::ObtenirIndex(unsigned char[])
{
	return 0;
}

unsigned int Mots::InsererMot(unsigned char[])
{
	return 0;
}

unsigned char * Mots::RecupererMot(unsigned int)
{
	return nullptr;
}

unsigned int Mots::ObtenirNombreMots()
{
	return 0;
}

//----------------------------------------------------------------- PRIVEE


Mots::Mots()
{
}


Mots::~Mots()
{
}
