/*************************************************************************
Communication - Classe de [...]
-------------------
d�but                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//--------- R�alisation de la classe <Communication> (fichier Communication.cpp) ---------//

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me

//------------------------------------------------------ Include personnel

#include "Communication.h"

//----------------------------------------------------------------- PUBLIC


Communication & Communication::ObtenirInstance()
{
	// TODO: changer le retour par l'instance du singleton
	return *((Communication*) nullptr);
}

void Communication::Ecouter(unsigned int port)
{
}

//----------------------------------------------------------------- PRIVEE


void Communication::threadServeur(unsigned int port)
{
}

void Communication::recevoirRequete()
{
}

DWORD Communication::threadRequete(void * p)
{
	return 0;
}

Communication::Communication()
{
}


Communication::~Communication()
{
}
