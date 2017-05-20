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
#include <string>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

//----------------------------------------------------------------- PUBLIC


Dictionnaire* Dictionnaire::instanceDictionnaire = new Dictionnaire();

Dictionnaire & Dictionnaire::ObtenirInstance()
{
	return *(instanceDictionnaire);
}

void Dictionnaire::RafraichirInstance()
{
	instanceDictionnaire = new Dictionnaire();
}

void Dictionnaire::ChargerFichier(const string & fichierDico)
{
	//TODO Destroy Maladies *
	//Reinitialisation des attributs
	maladies= unordered_map<string,const Maladie*>();
	maladiesParMot = unordered_map<unsigned int, unordered_set<const Maladie*>>();

	//Variables local
	unsigned int l = 0; //numero de ligne actuel
	string ligne;

	ifstream inDico(fichierDico);

	//1er ligne
	l++;
	if (!getline(inDico, ligne)||(ligne != "MA v1.0"&&ligne != "MA v1.0\r")) {//Si on n'arrive pas a lire la 1er ligne
		throw runtime_error("FileTypeINVALIDE");
	}

	//boucle sur tous les autres ligne (les maladies)
	while (getline(inDico, ligne)) {
		l++;
		if (!ligne.empty() && ligne.at(ligne.length() - 1) == '\r') {
			ligne = ligne.substr(0, ligne.length() - 1);
		}
		if (ligne.empty()) {
			//On Ignor les ligne vide
		}
		/*else if (ligne.at(0)=='#') { // Pour l'implementation de ligne de commentaire
			//On Ignor les ligne de commentaire
		}*/
		else {
			//Recuperation du nom de la maladie
			unsigned int pos = ligne.find(';');
			if (pos == string::npos || pos == ligne.length()-1) {
				throw runtime_error("Nom de maladie sans definition : " + ligne + " (L " + to_string(l) + ")");
			}
			Maladie * onreadMaladie = new Maladie();
			onreadMaladie->nom = ligne.substr(0, pos);



			//Recuperation de tous les mots de la maladie
			do {

				unsigned int lastpos = pos;
				for (pos = lastpos + 1; pos < ligne.length() && ligne[pos] != ';'; pos++);
				unsigned int length = pos - lastpos - 1; //longeur du mot
				if (length==0) {
					throw runtime_error("Maladie avec un mot de taille 0 : " + onreadMaladie->nom);
				}

				//recuperation du mot dans un char *
				char * mot = new char[length + 1];
				for (int i = 0; i < length; i++) {
					mot[i] = ligne.at(i + lastpos + 1);
					switch (mot[i] != 'A'    &&    mot[i] != 'T'    &&    mot[i] != 'C'    &&    mot[i] != 'G') {
						throw runtime_error("Maladie avec un mot invalide : " + onreadMaladie->nom + " contien un mot avec '" + mot[i] + "' (L " + to_string(l) + ")");
					}
				}
				mot[length] = '\0';

				//indexation du mot
				unsigned int indexMot;
				try {
					indexMot = Mots::ObtenirInstance().ObtenirIndex(mot);
				}
				catch (const range_error &e) {
					indexMot = Mots::ObtenirInstance().InsererMot(mot);
				}

				//Ajout du mot a la definition
				if (onreadMaladie->definition.find(indexMot) == onreadMaladie->definition.end()) {// Si le mot n'est pas dans la definition (filtre doublon)
					onreadMaladie->definition.insert(indexMot);
				}
			} while (pos < ligne.length() - 1 || (pos == ligne.length() - 1 && ligne.at(pos) != ';'));

			//Multi definition
			unordered_map<string,const Maladie*>::iterator it = maladies.find(onreadMaladie->nom);
			if (it != maladies.end()) {// Si le Maladie est deja referancer
				if (!(*(it->second) == *onreadMaladie)) {
					delete onreadMaladie;
					throw runtime_error("Different definition d'une meme maladie : " + it->first + " (L " + to_string(l) + ")");
				}
				delete onreadMaladie;
			}
			else {//Fist definition
				maladies.insert(pair<string,Maladie *>(onreadMaladie->nom, onreadMaladie));
				for (set<unsigned int>::iterator motIt = onreadMaladie->definition.begin(); motIt != onreadMaladie->definition.end(); motIt++) {
					maladiesParMot[*motIt].insert(onreadMaladie);
				}
			}
		}
	}
}

const Maladie * Dictionnaire::ObtenirMaladie(const string & name) {
	unordered_map<string,const Maladie*>::iterator it = maladies.find(name);
	if (it == maladies.end()) {
		throw range_error("maladie " + name + " non defini");
	}
	return it->second;
}

const unordered_set<const Maladie *> Dictionnaire::ObtenirMaladies(const unsigned int indexMot) {
	return maladiesParMot[indexMot];
}

const unordered_set<string> Dictionnaire::ObtenirNomsMaladies() {
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
}
