/*************************************************************************
Master - Classe qui permet de g�rer le traitement sp�cifique d'une requ�te 
-------------------
d�but                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//-------- Interface de la classe <Master> (fichier Master.h)  ---------//

#if ! defined ( MASTER_H )
#define MASTER_H

//--------------------------------------------------- Interfaces utilis�es

#include <string>
#include "CommunicationThread.h"
using namespace std;

enum Route {ANALYSE_PRECISE, ANALYSE_GLOBALE, LISTE_MALADIES, SERVICE_INCONNU, ERREUR_SYNTAXE};

//------------------------------------------------------------------------
// R�le de la classe <Master>
//  La classe Master contient different methode pour chaqu'un des service
//  proposer par le server. Elle a pour objectif de recup�rer les donn�e du
//  client et de lui repondres
//  
//------------------------------------------------------------------------


class Master
{
public:

	static void InterpreterRequete(const string & requete, CommunicationThread & thread);
	// Mode d'emploi : Interprete la requ�te pour invoquer le traitement qui lui est sp�cifique

	Master & operator = (const Master &);
	// Mode d'emploi : Op�rateur d'affectation, non impl�ment�

	Master(const Master &);
	// Mode d'emploi : Constructeur de copie, non impl�ment�
	

protected:

	static Route routerRequete(const string & requete);
	// Mode d'emploi : Renvoie le traitement � invoquer en fonction de la requ�te


	static void analysePrecise(const string & requete, CommunicationThread & thread);
	// Mode d'emploi : Retourne au client le r�sultat de l'analyse pr�cise demand�e

	static void analyseGlobale(const string & requete, CommunicationThread & thread);
	// Mode d'emploi : Retourne au client le r�sultat de l'analyse globale demand�e

	static void obtenirListeMaladies(const string & requete, CommunicationThread & thread);
	// Mode d'emploi : Retourne au client la liste des maladies connues par le serveur

	static void repondreServiceInconnu(const string & requete, CommunicationThread & thread);
	// Mode d'emploi : Informe le client qu'aucun service n'existe pour traiter sa requ�te

	static void repondreErreurRequete(const string & requete, CommunicationThread & thread);
	// Mode d'emploi : Informe le client que sa requ�te est syntaxiquement invalide 

	Master();
	// Mode d'emploi : Constructeur, non impl�ment�

	virtual ~Master();
	// Mode d'emploi : Destructeur, non impl�ment�
};

#endif