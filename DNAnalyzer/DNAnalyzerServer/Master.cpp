/*************************************************************************
Master - Classe qui g�re la communication entre un client et le service demander 
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
