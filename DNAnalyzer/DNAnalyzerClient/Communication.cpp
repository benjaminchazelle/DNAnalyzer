/*************************************************************************
Communication - Classe de gestion des communications r�seaux
-------------------
d�but                :	10/05/17
copyright            :	(C) 2017 par CHAZELLE
e-mail               :	benjamin.chazelle@insa-lyon.fr
*************************************************************************/

// R�alisation de la classe <Communication> (fichier Communication.cpp) //

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me

#include "stdafx.h"
#include <string>

using namespace std;

//------------------------------------------------------ Include personnel

#include "Communication.h"
#include "Serveur.h"

//----------------------------------------------------------------- PUBLIC

string Communication::EnvoyerMessage(const Serveur & serveur, const string & message)
{
	return string();
}
