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

//----------------------------------------------------------------- PUBLIC


Dictionnaire & Dictionnaire::ObtenirInstance()
{
	// TODO: changer le retour par l'instance du singleton
	return *((Dictionnaire*) nullptr);
}

//----------------------------------------------------------------- PRIVEE


Dictionnaire::Dictionnaire()
{
}


Dictionnaire::~Dictionnaire()
{
}
