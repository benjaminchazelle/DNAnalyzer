/*************************************************************************
Master - Classe de [...]
-------------------
d�but                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//--------- R�alisation de la classe <Master> (fichier Master.cpp) ---------//

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me

//------------------------------------------------------ Include personnel

#include "Master.h"

//----------------------------------------------------------------- PUBLIC


Master & Master::ObtenirInstance()
{
	// TODO: changer le retour par l'instance du singleton
	return *((Master*) nullptr);
}

//----------------------------------------------------------------- PRIVEE


Master::Master()
{
}


Master::~Master()
{
}
