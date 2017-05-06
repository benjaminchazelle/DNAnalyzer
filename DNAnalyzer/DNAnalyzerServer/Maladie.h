/*************************************************************************
Maladie - Structure d'une maladie
-------------------
d�but                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

#if ! defined ( MALADIE_H )
#define MALADIE_H

//--------------------------------------------------- Interfaces utilis�es

#include <string>
#include <unordered_set>

//------------------------------------------------------------------------
// R�le de la structure <Maladie>
//  stock le nom et les mots d'une Maladie
//------------------------------------------------------------------------

struct Maladie
{
	string nom;
	// Description : nom de la maladie

	unordered_set<unsigned int> definition;
	// Description : contien la list de l'index de chaqu'un des mots de la maladie
};
#endif