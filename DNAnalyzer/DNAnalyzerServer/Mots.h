/*************************************************************************
Mots - Classe de manipulation d'un ensemble de mots g�n�tiques
-------------------
d�but                :	31/04/17
copyright            :	(C) 2017 par CHAZELLE
e-mail               :	benjamin.chazelle@insa-lyon.fr
*************************************************************************/

//----------- Interface de la classe <Mots> (fichier Mots.h)  ----------//

#if ! defined ( MOTS_H )
#define MOTS_H

//--------------------------------------------------- Interfaces utilis�es
#include <unordered_map>

using namespace std;

//------------------------------------------------------------------------
// R�le de la classe <Mots>
//  La classe Mots permet de manipuler (ins�rer, rechercher) un ensemble 
//  de mots g�n�tiques gr�ce � leur d�finition ou leur index
//------------------------------------------------------------------------


class Mots
{
protected:

	static Mots* instanceMots;
	// Description : Instance singleton de Mots

	unordered_map<char*, unsigned int> mots;
	// Description : Dictionnaire d'un mot vers son index

	unordered_map<unsigned int, char*> mots_revers;
	// Description : Dictionnaire d'un index vers un mot

	unsigned int counter;
	// Description : Nombre de mots dans l'ensemble

public:

	static Mots& ObtenirInstance();
	// Mode d'emploi : renvoit l'instance singleton de Mots

	unsigned int ObtenirIndex(const char const []);
	// Mode d'emploi : renvoit l'index d'un mot s'il existe
	// Exception "invalid_argument" : si un index null est envoy�
	// Exception "" : si le mot est inconnu

	unsigned int InsererMot(const char const []);
	// Mode d'emploi : ins�re un mot dans l'ensemble et renvoit son index
	// Exception "invalid_argument" : si un index null est envoy�
	// Exception "overflow_error" : si le mot est d�j� connu

	char const * RecupererMot(const unsigned int);
	// Mode d'emploi : r�cup�re un mot par son index
	// Exception "range_error" : si l'index est inconnu

	unsigned int ObtenirNombreMots();
	// Mode d'emploi : renvoit le nombre de mots dans l'ensemble


	Mots & operator = (const Mots &);
	// Mode d'emploi : op�rateur d'affectation, non implement�

	Mots(const Mots &);
	// Mode d'emploi : constructeur de copie, non implement�

protected:

	Mots();
	// Mode d'emploi : constructeur

	virtual ~Mots();
	// Mode d'emploi : destructeur
};

#endif // !MOTS_H
