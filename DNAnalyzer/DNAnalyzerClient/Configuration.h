/*************************************************************************
Configuration - Classe de lecture d'un fichier de configurations serveurs
-------------------
d�but                :	06/05/17
copyright            :	(C) 2017 par CHAZELLE
e-mail               :	benjamin.chazelle@insa-lyon.fr
*************************************************************************/

//   Interface de la classe <Configuration> (fichier Configuration.h)   //

#if ! defined ( CONFIGURATION_H )
#define CONFIGURATION_H

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me
#include <unordered_set>
#include <string>

#include "Serveur.h"
struct Serveur;

using namespace std;

//------------------------------------------------------------------------
// R�le de la classe <Configuration>
//  La classe Configuration permet d'extraire la liste des configurations
//  serveurs depuis un fichier
//------------------------------------------------------------------------

class Configuration
{
protected:
	
	static Configuration* instanceConfiguration;
	// Description : Instance singleton de Configuration

	vector<struct Serveur> serveurs;
	// Description : Liste de configurations serveur

public:

	static Configuration& ObtenirInstance();
	// Mode d'emploi : Renvoie l'instance singleton de Configuration

	static void RafraichirInstance();
	// Mode d'emploi : R�initialise l'instance singleton

	vector<struct Serveur> ObtenirListeServeur() const;
	// Mode d'emploi : Cette m�thode renvoie un ensemble de configurations de connexions serveurs.
	
	bool ChargerFichier(const string &  fichierServeurs);
	// Mode d'emploi : Cette m�thode lit le contenu du fichier <fichierServeurs> pour le stocker dans <serveurs>
	// Renvoie true si le fichier a pu �tre charg�, false sinon

	Configuration & operator = (const Configuration &);
	// Mode d'emploi : Op�rateur d'affectation, non impl�ment�

	Configuration(const Configuration &);
	// Mode d'emploi : Constructeur de copie, non impl�ment�

protected:
	
	Configuration();
	// Mode d'emploi : Constructeur

	~Configuration();
	// Mode d'emploi : Destructeur

};

#endif