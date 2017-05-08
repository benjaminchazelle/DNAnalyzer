/*************************************************************************
Analyse - Classe qui analyse la présence de maladies dans un génome
-------------------
début                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//--------- Réalisation de la classe <Analyse> (fichier Analyse.cpp) ---------//

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel

#include "Analyse.h"

//----------------------------------------------------------------- PUBLIC


Analyse & Analyse::ObtenirInstance()
{
	// TODO: changer le retour par l'instance du singleton
	return *((Analyse*) nullptr);
}

bool Analyse::AnalysePrecise(unsigned int size, const unsigned char genome[], const Maladie maladie) {
	// TODO
	return false;
}

unordered_map<const Maladie&, bool> Analyse::AnalyseGlobal(unsigned int size,const unsigned char genome[]) {
	// TODO
	return unordered_map<const Maladie&, bool>();
}


//----------------------------------------------------------------- PRIVEE


Analyse::Analyse()
{
}


Analyse::~Analyse()
{
}
