/*************************************************************************
Communication - Classe de [...]
-------------------
début                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//--------- Réalisation de la classe <Communication> (fichier Communication.cpp) ---------//

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel

#include "Communication.h"

//----------------------------------------------------------------- PUBLIC


Communication & Communication::ObtenirInstance()
{
	// TODO: changer le retour par l'instance du singleton
	return *((Communication*) nullptr);
}

//----------------------------------------------------------------- PRIVEE


Communication::Communication()
{
}


Communication::~Communication()
{
}
