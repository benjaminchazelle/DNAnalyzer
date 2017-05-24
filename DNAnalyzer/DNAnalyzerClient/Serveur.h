/*************************************************************************
Serveur - Structure d'une configuration serveur
-------------------
début                :	06/05/17
copyright            :	(C) 2017 par CHAZELLE
e-mail               :	benjamin.chazelle@insa-lyon.fr
*************************************************************************/

//       Interface de la structure <Serveur> (fichier Serveur.h)        //

#if ! defined ( SERVEUR_H )
#define SERVEUR_H

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

#include <string>

using namespace std;

struct Serveur {

	string host;
	// Description : Nom d'hôte du serveur

	unsigned int port;
	// Description : Port du serveur

	Serveur() : host(""), port(0) {

	}
	// Description : Constructeur

};

namespace std
{
	template<> struct hash<Serveur>
	{
		size_t operator()(Serveur const& s) const
		{
			string full = s.host;
			full += ":";
			full += s.port;

			return std::hash<std::string>()(full);
		}
	};
	// Description : Hash d'une struct Serveur
}

#endif