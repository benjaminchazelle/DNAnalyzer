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


Master & Master::ObtenirInstance()
{
	// TODO: changer le retour par l'instance du singleton
	return *((Master*) nullptr);
}

//----------------------------------------------------------------- PRIVEE
void Master::InterpreterRequete(unsigned char request[], unsigned int taille, CommunicationThread & thread)
{
	
}

void Master::AnalysePrecise(unsigned char request[], unsigned int taille, CommunicationThread & thread)
{

}

void Master::AnalyseGlobale(unsigned char request[], unsigned int taille, CommunicationThread & thread)
{

}

void Master::ObtenirListeMaladies(unsigned char request[], unsigned int taille, CommunicationThread & thread)
{

}

void Master::RepondreServiceInconnu(unsigned char request[], unsigned int taille, CommunicationThread & thread)
{

}

void Master::RepondreRequetteHeaderInvalise(unsigned char request[], unsigned int taille, CommunicationThread & thread)
{

}

void Master::RepondreRequetteBodyInvalise(unsigned char request[], unsigned int taille, CommunicationThread & thread)
{

}

Master::Master()
{

}


Master::~Master()
{

}