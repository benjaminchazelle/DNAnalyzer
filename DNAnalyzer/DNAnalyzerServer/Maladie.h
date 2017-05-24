/*************************************************************************
Maladie - Structure d'une maladie
-------------------
début                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//-------  Interface de la classe <Maladie> (fichier Maladie.h)  -------//

#if ! defined ( MALADIE_H )
#define MALADIE_H

//--------------------------------------------------- Interfaces utilisées

#include <string>
#include <set>
#include <utility>
//#include <boost/functional/hash.hpp>

using namespace std;

//------------------------------------------------------------------------
// Rôle de la structure <Maladie>
//  Stock le nom et les mots d'une Maladie
//------------------------------------------------------------------------

struct Maladie
{
	string nom;
	// Description : Nom de la maladie

	set<unsigned int> definition;
	// Description : Contient la liste de l'index de chacun des mots de la maladie


	bool operator==(const Maladie& m)const
	{
		return m.nom == nom && m.definition == definition;
	}
	// Mode d'emploi : Opérateur de comparaison d'une struct Maladie
};
namespace std
{
	template<> struct hash<Maladie>
	{
		size_t operator()(Maladie const& maladie) const
		{
			std::size_t res = 0;
			hash<string> stringHash;
			hash<unsigned int> uintHash;
			res ^= stringHash(maladie.nom) + 0x9e3779b9 + (res << 6) + (res >> 2);
			set<unsigned int>::iterator iter = maladie.definition.begin();

			for (; iter != maladie.definition.end(); iter++)
			{
				res ^= uintHash(*iter) + 0x9e3779b9 + (res << 6) + (res >> 2);
			}
			return res;
		}
	};

	template<> struct hash<Maladie*>
	{
		size_t operator()(const Maladie *const& maladie) const
		{
			hash<Maladie> hashMaladie;
			return hashMaladie(*maladie);
		}
	};
}
#endif