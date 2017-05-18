/*************************************************************************
Master - Classe qui permet de gérer le traitement spécifique d'une requête 
-------------------
début                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//-------- Interface de la classe <Master> (fichier Master.h)  ---------//

#if ! defined ( MASTER_H )
#define MASTER_H

//--------------------------------------------------- Interfaces utilisées

#include <string>
#include "CommunicationThread.h"
using namespace std;

enum Route {ANALYSE_PRECISE, ANALYSE_GLOBALE, LISTE_MALADIES, SERVICE_INCONNU, ERREUR_SYNTAXE};

//------------------------------------------------------------------------
// Rôle de la classe <Master>
//  La classe Master contient different methode pour chaqu'un des service
//  proposer par le server. Elle a pour objectif de recupérer les donnée du
//  client et de lui repondres
//  
//------------------------------------------------------------------------


class Master
{
public:

	static void InterpreterRequete(const string & requete, CommunicationThread & thread);
	// Mode d'emploi : Interprete la requête pour invoquer le traitement qui lui est spécifique

	Master & operator = (const Master &);
	// Mode d'emploi : Opérateur d'affectation, non implémenté

	Master(const Master &);
	// Mode d'emploi : Constructeur de copie, non implémenté
	

protected:

	static Route routerRequete(const string & requete);
	// Mode d'emploi : Renvoie le traitement à invoquer en fonction de la requête


	static void analysePrecise(const string & requete, CommunicationThread & thread);
	// Mode d'emploi : Retourne au client le résultat de l'analyse précise demandée

	static void analyseGlobale(const string & requete, CommunicationThread & thread);
	// Mode d'emploi : Retourne au client le résultat de l'analyse globale demandée

	static void obtenirListeMaladies(const string & requete, CommunicationThread & thread);
	// Mode d'emploi : Retourne au client la liste des maladies connues par le serveur

	static void repondreServiceInconnu(const string & requete, CommunicationThread & thread);
	// Mode d'emploi : Informe le client qu'aucun service n'existe pour traiter sa requête

	static void repondreErreurRequete(const string & requete, CommunicationThread & thread);
	// Mode d'emploi : Informe le client que sa requête est syntaxiquement invalide 

	Master();
	// Mode d'emploi : Constructeur, non implémenté

	virtual ~Master();
	// Mode d'emploi : Destructeur, non implémenté
};

#endif