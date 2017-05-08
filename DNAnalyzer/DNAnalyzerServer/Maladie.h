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
#include <utility>
//#include <boost/functional/hash.hpp>

using namespace std;

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
namespace std
{
	template<> struct hash<Maladie>
	{
		size_t operator()(Maladie const& maladie) const
		{// NON SUR (FAIR DES TESTS)
			std::size_t res = 0;
			hash<string> stringHash;
			res ^= stringHash(maladie.nom) + 0x9e3779b9 + (res << 6) + (res >> 2);
			unordered_set<unsigned int>::iterator iter = maladie.definition.begin();

			for (; iter != maladie.definition.end(); iter++)
			{
				res += *iter;
			}
			return res;
		}
	};

	template<> struct hash<Maladie*>
	{
		size_t operator()(const Maladie *const& maladie) const
		{// NON SUR (FAIR DES TESTS)
			std::size_t res = 0;
			hash<string> stringHash;
			res ^= stringHash(maladie->nom) + 0x9e3779b9 + (res << 6) + (res >> 2);
			unordered_set<unsigned int>::iterator iter = maladie->definition.begin();

			for (; iter != maladie->definition.end(); iter++)
			{
				res += *iter;
			}
			return res;
		}
	};
}
#endif