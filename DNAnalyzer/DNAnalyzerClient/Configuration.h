/*************************************************************************
Mots - Classe de lecture d'un fichier de configurations serveurs
-------------------
début                :	06/05/17
copyright            :	(C) 2017 par CHAZELLE
e-mail               :	benjamin.chazelle@insa-lyon.fr
*************************************************************************/

//   Interface de la classe <Configuration> (fichier Configuration.h)   //

#if ! defined ( CONFIGURATION_H )
#define CONFIGURATION_H

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <unordered_set>
#include <string>

#include "Serveur.h"
struct Serveur;

using namespace std;

//------------------------------------------------------------------------
// Rôle de la classe <Configuration>
//  La classe Configuration permet d'extraire la liste des configurations
//  serveurs depuis un fichier
//------------------------------------------------------------------------

class Configuration
{
public:

	static const string fichierServeurs;

protected:
	
	static Configuration* instanceConfiguration;

	vector<struct Serveur> serveurs;

public:

	static Configuration& ObtenirInstance();
	// Mode d'emploi : renvoit l'instance singleton de Configuration

	static void RafraichirInstance();
	// Mode d'emploi : réinitialise l'instance singleton

	vector<struct Serveur> ObtenirListeServeur();
	// Mode d'emploi : Cette méthode permet de renvoyer un ensemble de configurations de connexions serveurs.

	Configuration & operator = (const Configuration &);
	// Mode d'emploi : opérateur d'affectation, non implementé

	Configuration(const Configuration &);
	// Mode d'emploi : constructeur de copie, non implementé

protected:
	
	Configuration();
	// Mode d'emploi : constructeur, lit le contenu du fichier <fichierServeurs> pour le stocker dans <serveurs>

	~Configuration();
	// Mode d'emploi : destructeur

};

#endif