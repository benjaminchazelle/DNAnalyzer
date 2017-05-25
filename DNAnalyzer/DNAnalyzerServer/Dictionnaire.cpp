/*************************************************************************
Dictionnaire - Classe de stockage des données de maladies
-------------------
début                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//- Réalisation de la classe <Dictionnaire> (fichier Dictionnaire.cpp) -//

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel

#include "Dictionnaire.h"
#include "Mots.h"
#include "Log.h"
#include <string>
#include <fstream>
#include <sstream>

#define UNREFERENCE_PARAMETER(P) (P)

using namespace std;

//----------------------------------------------------------------- PUBLIC


Dictionnaire* Dictionnaire::instanceDictionnaire = new Dictionnaire();

Dictionnaire & Dictionnaire::ObtenirInstance()
{
	return *(instanceDictionnaire);
}

void Dictionnaire::RafraichirInstance()
{
	delete instanceDictionnaire;
	instanceDictionnaire = new Dictionnaire();
}

void Dictionnaire::ChargerFichier(const string & fichierDico)
{
	LOG(T_DEBUG) << "[Dictionnaire] call ChargerFichier ( " << fichierDico << " ) ";
	for (auto maladieIt = maladies.begin(); maladieIt != maladies.end(); maladieIt++) {
		delete maladieIt->second;
	}
	// Réinitialisation des attributs
	maladies= unordered_map<string,const Maladie*>();
	maladiesParMot = unordered_map<unsigned int, unordered_set<const Maladie*>>();

	// Variables locales
	unsigned int l = 0; // Numéro de ligne actuelle
	string ligne;

	ifstream inDico(fichierDico);

	if (!inDico)
	{
		LOG(T_ERROR) << "[Dictionnaire] file not readable";
		throw runtime_error("Impossible d'ouvrir le fichier");
	}
	LOG(T_DEBUG) << "[Dictionnaire] file readable";

	// 1ere ligne
	l++;
	if (!getline(inDico, ligne)||(ligne != "MA v1.0"&&ligne != "MA v1.0\r")) {//Si on n'arrive pas a lire la 1er ligne
		LOG(T_ERROR) << "[Dictionnaire] not dico file";
		throw invalid_argument("Type de fichier invalide");
	}
	LOG(T_DEBUG) << "[Dictionnaire] dico file";

	// Boucle sur toutes les autres lignes (les maladies)
	for (l++; getline(inDico, ligne);l++) {
		
		if (!ligne.empty() && ligne.at(ligne.length() - 1) == '\r') {
			ligne = ligne.substr(0, ligne.length() - 1);
		}
		if (ligne.empty()) {
			// On ignore les lignes vides
		}
		else {
			// Récuperation du nom de la maladie
			unsigned int pos = ligne.find(';');
			if (pos == string::npos || pos == ligne.length()-1) {
				LOG(T_ERROR) << "[Dictionnaire] Nom de maladie sans definition : ligne(" << ligne << "), at(" << l << ")";
				throw invalid_argument("Nom de maladie sans definition : " + ligne + " (L " + to_string(l) + ")");
			}
			Maladie * onreadMaladie = new Maladie();
			onreadMaladie->nom = ligne.substr(0, pos);



			// Récuperation de tous les mots de la maladie
			do {

				unsigned int lastpos = pos;
				for (pos = lastpos + 1; pos < ligne.length() && ligne[pos] != ';'; pos++);
				unsigned int length = pos - lastpos - 1; // Longeur du mot
				if (length!=0) {
					// Récuperation du mot dans un char *
					char * mot = new char[length + 1];
					for (unsigned int i = 0; i < length; i++) {
						mot[i] = ligne.at(i + lastpos + 1);
						if (mot[i] != 'A'    &&    mot[i] != 'T'    &&    mot[i] != 'C'    &&    mot[i] != 'G') {
							LOG(T_ERROR) << "[Dictionnaire] Mot d'une maladie invalide: maladie("<< onreadMaladie->nom << "), mot(" << mot[i] << "), ligne("<< l <<")";
							throw invalid_argument("Maladie avec un mot invalide : " + onreadMaladie->nom + " contien un mot avec '" + mot[i] + "' (L " + to_string(l) + ")");
						}
					}
					mot[length] = '\0';

					// Indexation du mot
					unsigned int indexMot;
					try {
						indexMot = Mots::ObtenirInstance().ObtenirIndex(mot);
					}
					catch (const range_error &e) {
						UNREFERENCE_PARAMETER(e);
						indexMot = Mots::ObtenirInstance().InsererMot(mot);
					}

					// Ajout du mot à la définition
					if (onreadMaladie->definition.find(indexMot) == onreadMaladie->definition.end()) {// Si le mot n'est pas dans la definition (filtre doublon)
						onreadMaladie->definition.insert(indexMot);
					}
				}
			} while (pos < ligne.length() - 1 || (pos == ligne.length() - 1 && ligne.at(pos) != ';'));
			
			// Nom de maladie sans définition ?
			if (onreadMaladie->definition.size() == 0) {
				LOG(T_ERROR) << "[Dictionnaire] Nom de maladie sans definition : ligne(" << ligne << "), at(" << l << ")";
				throw invalid_argument("Nom de maladie sans definition : " + ligne + " (L " + to_string(l) + ")");
			}
			
			// Multi définition d'une maladie
			unordered_map<string,const Maladie*>::iterator it = maladies.find(onreadMaladie->nom);
			if (it != maladies.end()) {// Si la maladie est déjà réferencée

				if (!(*(it->second) == *onreadMaladie)) {
					LOG(T_ERROR) << "[Dictionnaire] Multiple definition contradictoire du mot " << onreadMaladie->nom + " dans le fichier " << fichierDico << " L." << l;
					delete onreadMaladie;
					throw invalid_argument("Different definition d'une meme maladie : " + it->first + " (L " + to_string(l) + ")");
				}
				else {
					LOG(T_WARN) << "[Dictionnaire] Multiple definition identique du mot " << onreadMaladie->nom + " dans le fichier " << fichierDico <<" L." << l;
				}
				delete onreadMaladie;
			}
			else {// Si première définition
				maladies.insert(pair<string,Maladie *>(onreadMaladie->nom, onreadMaladie));
				for (set<unsigned int>::iterator motIt = onreadMaladie->definition.begin(); motIt != onreadMaladie->definition.end(); motIt++) {
					maladiesParMot[*motIt].insert(onreadMaladie);
				}
			}
		}
	}
	LOG(T_DEBUG) << "[Dictionnaire] end ChargerFichier";
}

const Maladie * Dictionnaire::ObtenirMaladie(const string & name) {
	LOG(T_DEBUG) << "[Dictionnaire] call ObtenirMaladie ( " << name << " ) ";
	unordered_map<string,const Maladie*>::iterator it = maladies.find(name);
	if (it == maladies.end()) {
		LOG(T_WARN) << "[Dictionnaire] Maladie non définie : " << name;
		throw range_error("maladie " + name + " non defini");
	}
	return it->second;
}

const unordered_set<const Maladie *> Dictionnaire::ObtenirMaladies(const unsigned int indexMot) {
	return maladiesParMot[indexMot];
}

const unordered_set<string> Dictionnaire::ObtenirNomsMaladies() {
	LOG(T_DEBUG) << "[Dictionnaire] ObtenirNomsMaladies()";
	unordered_set<string> * res = new unordered_set<string>();
	for (unordered_map<string,const Maladie *>::iterator it = maladies.begin(); it != maladies.end(); it++)
		res->insert(it->first);
	return *res;
}


//----------------------------------------------------------------- PRIVEE

Dictionnaire::Dictionnaire()
{
}


Dictionnaire::~Dictionnaire()
{
	for (auto maladieIt = maladies.begin(); maladieIt != maladies.end(); maladieIt++) {
		delete maladieIt->second;
	}
}
