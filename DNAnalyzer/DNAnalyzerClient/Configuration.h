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

	vector<struct Serveur> serveurs;

public:

	static Configuration& ObtenirInstance();
	// Mode d'emploi : renvoit l'instance singleton de Configuration

	static void RafraichirInstance();
	// Mode d'emploi : r�initialise l'instance singleton

	vector<struct Serveur> ObtenirListeServeur() const;
	// Mode d'emploi : Cette m�thode renvoie un ensemble de configurations de connexions serveurs.
	
	bool ChargerFichier(const string &  fichierServeurs);
	// Mode d'emploi : Cette m�thode lit le contenu du fichier <fichierServeurs> pour le stocker dans <serveurs>
	// Renvoit true si le fichier a pu �tre charg�, false sinon

	Configuration & operator = (const Configuration &);
	// Mode d'emploi : op�rateur d'affectation, non impl�ment�

	Configuration(const Configuration &);
	// Mode d'emploi : constructeur de copie, non impl�ment�

protected:
	
	Configuration();
	// Mode d'emploi : constructeur

	~Configuration();
	// Mode d'emploi : destructeur

};

#endif