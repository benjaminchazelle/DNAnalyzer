/*************************************************************************
Analyse - Classe qui analyse la pr�sence de maladies dans un g�nome
-------------------
d�but                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//------ R�alisation de la classe <Analyse> (fichier Analyse.cpp) ------//

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me

//------------------------------------------------------ Include personnel

#include "Analyse.h"
#include "Mots.h"
#include "Dictionnaire.h"
#include "Log.h"

#define UNREFERENCE_PARAMETER(P) (P)

//----------------------------------------------------------------- PUBLIC



bool Analyse::AnalysePrecise(const unordered_set<string> & genome, const Maladie & maladie) {
	LOG(T_DEBUG) << "[Analyse] call AnalysePrecise(genome de taile " << genome.size() << " , maladie(" << maladie.nom << ") )" ;
	unsigned int count = 0;
	for (unordered_set<string>::iterator motGenom = genome.begin(); motGenom != genome.end(); motGenom++) {
		try {
			unsigned int indexMotGenom = Mots::ObtenirInstance().ObtenirIndex(motGenom->c_str());
			if (maladie.definition.find(indexMotGenom) != maladie.definition.end()) {
				count++;
			}
		}
		catch (exception const& e) {
			UNREFERENCE_PARAMETER(e);
			// Si le mot n'est pas ref�renc� alors il n'est pas dans une maladie (rien � faire)
		}
	}
	LOG(T_DEBUG) << "[Analyse] find  "<<count<<"/"<< maladie.definition.size()<<" mots";
	LOG(T_DEBUG) << "[Analyse] end AnalysePrecise : return " << (count == maladie.definition.size() ? "true":"false");
	return count == maladie.definition.size();
}

const unordered_set<const Maladie *> Analyse::AnalyseGlobale(const unordered_set<string> & genome) {
	LOG(T_DEBUG) << "[Analyse] call AnalysePrecise(genome de taile " << genome.size() << " )";
	unordered_map<const Maladie *, unsigned int> nbMotMaladieFind;
	unordered_set<const Maladie *> resutat;
	for (unordered_set<string>::iterator motGenom = genome.begin(); motGenom != genome.end(); motGenom++) {
		try {
			unsigned int indexMotGenom = Mots::ObtenirInstance().ObtenirIndex((*motGenom).c_str());
			const unordered_set<const Maladie *> maladiesDuMot = Dictionnaire::ObtenirInstance().ObtenirMaladies(indexMotGenom);
			for (unordered_set<const Maladie *>::iterator uneMaladieDuMotIt = maladiesDuMot.begin(); uneMaladieDuMotIt != maladiesDuMot.end(); uneMaladieDuMotIt++) {
				const Maladie * uneMaladieDuMot = *uneMaladieDuMotIt;
				if (uneMaladieDuMot->definition.size() == ++nbMotMaladieFind[uneMaladieDuMot]) {
					LOG(T_DEBUG) << "[Analyse] find maladie : " << uneMaladieDuMot->nom << " maladie";
					resutat.insert(uneMaladieDuMot);
				}
			}
		}
		catch (exception const& e) {
			UNREFERENCE_PARAMETER(e);
			// Si le mot n'est pas r�frenc� alors il n'est pas dans une maladie (rien � faire)
		}
	}
	LOG(T_DEBUG) << "[Analyse] end AnalysePrecise : return " << resutat.size() << " maladies";
	return resutat;
}


//----------------------------------------------------------------- PRIVEE

