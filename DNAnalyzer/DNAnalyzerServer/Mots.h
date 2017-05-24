/*************************************************************************
Mots - Classe de manipulation d'un ensemble de mots génétiques
-------------------
début                :	31/04/17
copyright            :	(C) 2017 par CHAZELLE
e-mail               :	benjamin.chazelle@insa-lyon.fr
*************************************************************************/

//----------- Interface de la classe <Mots> (fichier Mots.h)  ----------//

#if ! defined ( MOTS_H )
#define MOTS_H

//--------------------------------------------------- Interfaces utilisées
#include <unordered_map>
#include <xhash>
#include <map>

using namespace std;

// Comparateur de clés pour l'unordered_map<char*, unsigned int ...>
struct cmp_charptr {
	bool operator()(char *first, char  *second) const
	{
		return strcmp(first, second) == 0;
	}
};
struct hash_charptr {
	size_t operator()(const char* p) const {
		size_t result = 0;
		const size_t prime = 312;
		for (size_t i = 0; p[i]!='\0'; ++i) {
			result = p[i] + (result * prime);
		}
		return result;
	}
};
typedef unordered_map<char*, unsigned int, hash_charptr, cmp_charptr> unordered_map_chars_uint;

//------------------------------------------------------------------------
// Rôle de la classe <Mots>
//  La classe Mots permet de manipuler (insérer, rechercher) un ensemble 
//  de mots génétiques grâce à leur définition ou leur index
//------------------------------------------------------------------------


class Mots
{
protected:

	static Mots* instanceMots;
	// Description : Instance singleton de Mots

	unordered_map_chars_uint mots;
	// Description : Dictionnaire d'un mot vers son index

	unordered_map<unsigned int, char*> mots_revers;
	// Description : Dictionnaire d'un index vers un mot

	unsigned int counter;
	// Description : Nombre de mots dans l'ensemble

public:

	static Mots& ObtenirInstance();
	// Mode d'emploi : Renvoie l'instance singleton de Mots

	static void RafraichirInstance();
	// Mode d'emploi : Réinitialise l'instance singleton

	unsigned int ObtenirIndex(const char mot[]);
	// Mode d'emploi : Renvoie l'index d'un mot <mot> s'il existe
	// Exception "invalid_argument" : Si un index null est envoyé
	// Exception "range_error" : Si le mot est inconnu

	unsigned int InsererMot(const char mot[]);
	// Mode d'emploi : Insère un mot <mot> dans l'ensemble et renvoie son index
	// Exception "invalid_argument" : Si un index null est envoyé
	// Exception "overflow_error" : Si le mot est déjà connu

	char const * RecupererMot(const unsigned int indexMot);
	// Mode d'emploi : Récupère un mot par son index <indexMot>
	// Exception "range_error" : Si l'index est inconnu

	unsigned int ObtenirNombreMots();
	// Mode d'emploi : Renvoie le nombre de mots dans l'ensemble


	Mots & operator = (const Mots &);
	// Mode d'emploi : Opérateur d'affectation, non implémenté

	Mots(const Mots &);
	// Mode d'emploi : Constructeur de copie, non implémenté

protected:

	Mots();
	// Mode d'emploi : Constructeur

	virtual ~Mots();
	// Mode d'emploi : Destructeur
};

#endif // !MOTS_H
