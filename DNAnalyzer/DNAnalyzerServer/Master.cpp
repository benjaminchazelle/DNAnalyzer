/*************************************************************************
Master - Classe qui gére la communication entre un client et le service demander 
-------------------
début                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//--------- Réalisation de la classe <Master> (fichier Master.cpp) ---------//

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel

#include "Master.h"
#include "CommunicationThread.h"
//----------------------------------------------------------------- PUBLIC

void Master::InterpreterRequete(string & requete, CommunicationThread & thread)
{
}

void Master::analysePrecise(string & requete, CommunicationThread & thread)
{
}

void Master::analyseGlobale(string & requete, CommunicationThread & thread)
{
}

void Master::obtenirListeMaladies(string & requete, CommunicationThread & thread)
{
}

void Master::repondreServiceInconnu(string & requete, CommunicationThread & thread)
{
}

void Master::repondreErreurRequete(string & requete, CommunicationThread & thread)
{
}
