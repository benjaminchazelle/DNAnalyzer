/*************************************************************************
Master - Classe qui gére la communication entre un clientInfo et le service demander 
-------------------
début                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//------- Réalisation de la classe <Master> (fichier Master.cpp) -------//

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>

//------------------------------------------------------ Include personnel

#include "Master.h"
#include "CommunicationThread.h"

//----------------------------------------------------------------- PUBLIC

void Master::InterpreterRequete(CommunicationThread & thread)
{
	//TODO : Change
}

//----------------------------------------------------------------- PRIVEE

Route Master::routerRequete(const string & serviceLigne)
{
	return Route();
}

void Master::analysePrecise(const string & maladie, unordered_set<string> & genome, CommunicationThread & thread)
{
}

void Master::analyseGlobale(const unordered_set<string> & genome, CommunicationThread & thread)
{
}

void Master::obtenirListeMaladies(CommunicationThread & thread)
{
}

void Master::repondreServiceInconnu(const string & serviceName, CommunicationThread & thread)
{
}

void Master::repondreErreurRequete(const string & textes, CommunicationThread & thread)
{
}
