/*************************************************************************
Master - Classe qui gére la communication entre un client et le service demander 
-------------------
début                :	06/05/17
copyright            :	(C) 2017 par VOGEL
e-mail               :	hugues.vogel@insa-lyon.fr
*************************************************************************/

//----------- Interface de la classe <Master> (fichier Master.h)  ----------//

#if ! defined ( MASTER_H )
#define MASTER_H

//--------------------------------------------------- Interfaces utilisées

using namespace std;


//------------------------------------------------------------------------
// Rôle de la classe <Master>
//  La classe Master contient different methode pour chaqu'un des service
//  proposer par le server. Elle a pour objectif de recupérer les donnée du
//  client et de lui repondres
//  
//------------------------------------------------------------------------


class Master
{
protected:

	static Master* instanceMaster;
	// Description : Instance singleton de Master

public:
	static Master& ObtenirInstance();
	// Mode d'emploi : renvoit l'instance singleton de Master

	void InterpreterRequete(unsigned char request[], unsigned int taille, CommunicationThread & thread);
	// Mode d'emploi : redirige la requete vers le bon servise a partir de toutes la requette, sa taille, et le CommunicationThread de la requette

	void AnalysePrecise(unsigned char request[], unsigned int taille, CommunicationThread & thread);
	// Mode d'emploi : retourne au client le resultat de l'annalise demander

	void AnalyseGlobale(unsigned char request[], unsigned int taille, CommunicationThread & thread);
	// Mode d'emploi : retourne au client le resultat de l'annalise demander

	void ObtenirListeMaladies(unsigned char request[], unsigned int taille, CommunicationThread & thread);
	// Mode d'emploi : retourne au client la liste des Maladies tréter par le server

	void RepondreServiceInconnu(unsigned char request[], unsigned int taille, CommunicationThread & thread);
	// Mode d'emploi : Informe le client que la request n'est pas valide car elle ne corespond a auqu'un service

	void RepondreRequetteHeaderInvalise(unsigned char request[], unsigned int taille, CommunicationThread & thread);
	// Mode d'emploi : Informe le client que l'entéte de la requette est male former ou n'est pas suporter par le server 

	void RepondreRequetteBodyInvalise(unsigned char request[], unsigned int taille, CommunicationThread & thread);
	// Mode d'emploi : Informe le client que le corp de la requette n'a pas la bonne s'intaxe pour le service demander

	Master & operator = (const Master &);
	// Mode d'emploi : opérateur d'affectation, non implementé

	Master(const Master &);
	// Mode d'emploi : constructeur de copie, non implementé

protected:

	Master();
	// Mode d'emploi : constructeur

	virtual ~Master();
};

#endif