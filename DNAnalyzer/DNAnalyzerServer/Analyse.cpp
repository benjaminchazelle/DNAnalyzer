/*************************************************************************
Analyse - Classe de [...]
-------------------
d�but                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//--------- R�alisation de la classe <Analyse> (fichier Analyse.cpp) ---------//

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me

//------------------------------------------------------ Include personnel

#include "Analyse.h"

//----------------------------------------------------------------- PUBLIC


Analyse & Analyse::ObtenirInstance()
{
	// TODO: changer le retour par l'instance du singleton
	return *((Analyse*) nullptr);
}

//----------------------------------------------------------------- PRIVEE


Analyse::Analyse()
{
}


Analyse::~Analyse()
{
}
