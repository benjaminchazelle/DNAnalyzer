#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DNAnalyzerServer/Dictionnaire.h"
#include "../DNAnalyzerServer/Mots.h"
#include <exception>
#include <unordered_set>
#include <cstring>
#include <string>
#include "../TestUtil/FileUtil.h"

#define UNREFERENCE_PARAMETER(P) (P)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DNAnalyzerServerTest
{
	TEST_CLASS(DictionnaireTest)
	{
	protected:

		const string _dicoTestFile = "data.test.dico";

	public:
		TEST_CLASS_INITIALIZE(initialize) {
			Mots::RafraichirInstance();
			Dictionnaire::RafraichirInstance();
		}

		TEST_METHOD_CLEANUP(CleanUp)
		{
			Mots::RafraichirInstance();
			Dictionnaire::RafraichirInstance();
		}

		//ObtenirInstance
		TEST_METHOD(ObtenirInstance_NotNull)
		{
			// L'instance retournée ne doit pas être null
			Assert::IsTrue(&(Dictionnaire::ObtenirInstance()) != (Dictionnaire*) nullptr);
		}

		TEST_METHOD(ObtenirInstance_SameReference)
		{
			// L'instance retournée doit toujours être la même
			Assert::IsTrue(&(Dictionnaire::ObtenirInstance()) == &(Dictionnaire::ObtenirInstance()));
		}

		TEST_METHOD(ChargerFichier_InexistantFile)
		{
			// Un fichier inexistant lève une exception "runtime_error"

			FileUtil::unlink(_dicoTestFile);

			bool runtimeErrorException = false;

			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				Assert::Fail();
			}
			catch (runtime_error const& e) {
				UNREFERENCE_PARAMETER(e);

				runtimeErrorException = true;
			}

			Assert::IsTrue(runtimeErrorException);
						
			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);
		}

		TEST_METHOD(ChargerFichier_CorrectSyntaxes_OK_One)
		{
			// Syntaxe de fichier mono maladie correcte

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);

			FileUtil::write(_dicoTestFile, "MA v1.0\r\nNAME;AA;CC;GG;TT\r\n");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				const Maladie * NAME = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME");
				Assert::IsTrue(NAME->definition.size() == 4);
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 1);

		}

		TEST_METHOD(ChargerFichier_CorrectSyntaxes_OK_Multiple)
		{
			// Syntaxe de fichier multi maladie correcte

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);

			FileUtil::write(_dicoTestFile, "MA v1.0\r\nNAME;AA;CC;GG;TT\r\nNAME2;AAAA;CCCC\r\n");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				const Maladie * NAME = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME");
				Assert::IsTrue(NAME->definition.size() == 4);
				const Maladie * NAME2 = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME2");
				Assert::IsTrue(NAME2->definition.size() == 2);
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 2);
		}

		TEST_METHOD(ChargerFichier_CorrectSyntaxes_EmptyWord_One)
		{
			// Mots vides ignorés dans un dictionnaire à une seule entrée

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);

			FileUtil::write(_dicoTestFile, "MA v1.0\r\nNAME;;AA;CC;;GG;TT;;\r\n");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				const Maladie * NAME = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME");
				Assert::IsTrue(NAME->definition.size() == 4);

				for (auto i : NAME->definition)
				{
					Assert::IsTrue(Mots::ObtenirInstance().RecupererMot(i) != "");
				}

			}
			catch (...) {
				Assert::Fail();
			}
			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 1);

		}

		TEST_METHOD(ChargerFichier_CorrectSyntaxes_EmptyWord_Multiple)
		{
			// Mots vides ignorés dans un dictionnaire à plusieurs entrées

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);

			FileUtil::write(_dicoTestFile, "MA v1.0\r\nNAME;;AA;CC;;GG;TT\r\nNAME2;AAAA;;;CCCC\r\n");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				const Maladie * NAME = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME");
				Assert::IsTrue(NAME->definition.size() == 4);

				for (auto i : NAME->definition)
				{
					Assert::IsTrue(Mots::ObtenirInstance().RecupererMot(i) != "");
				}

				const Maladie * NAME2 = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME2");
				Assert::IsTrue(NAME2->definition.size() == 2);

				for (auto i : NAME2->definition)
				{
					Assert::IsTrue(Mots::ObtenirInstance().RecupererMot(i) != "");
				}
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 2);
		}

		TEST_METHOD(ChargerFichier_CorrectSyntaxes_BadHeader)
		{
			// L'en-tête du fichier doit être correcte, sinon quoi le fichier n'est pas chargé

			bool invalidArgumentException = false;

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);

			FileUtil::write(_dicoTestFile, "Mauvais header\r\nNAME;AA;CC;GG;TT\r\n");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				Assert::Fail();				
			}
			catch (invalid_argument const& e) {
				UNREFERENCE_PARAMETER(e);

				invalidArgumentException = true;

				Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);
			}

			Assert::IsTrue(invalidArgumentException);

		}

		TEST_METHOD(ChargerFichier_CorrectSyntaxes_SemiColon_One)
		{
			// Les lignes peuvent se finir avec un point-virgule sans incidence
			// Test sur un dictionnaire à une entrée unique

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);

			FileUtil::write(_dicoTestFile, "MA v1.0\r\nNAME;AA;CC;GG;TT;\r\n");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 1);
				const Maladie * NAME = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME");
				Assert::IsTrue(NAME->definition.size() == 4);
			}
			catch (...) {
				Assert::Fail();
			}

		}
	
		TEST_METHOD(ChargerFichier_CorrectSyntaxes_SemiColon_Multiple)
		{
			// Les lignes peuvent se finir avec un point-virgule sans incidence
			// Test sur un dictionnaire à plusieurs entrées

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);

			FileUtil::write(_dicoTestFile, "MA v1.0\r\nNAME;AA;CC;GG;TT;\r\nNAME2;AAAA;CCCC;\r\n");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 2);
				const Maladie * NAME = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME");
				Assert::IsTrue(NAME->definition.size() == 4);
				const Maladie * NAME2 = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME2");
				Assert::IsTrue(NAME2->definition.size() == 2);
			}
			catch (...) {
				Assert::Fail();
			}
		}

		TEST_METHOD(ChargerFichier_CorrectSyntaxes_NoLastCRLF_One)
		{
			// La dernière ligne peut omettre \r\n
			// Test sur un dictionnaire à une entrée unique

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);

			FileUtil::write(_dicoTestFile, "MA v1.0\r\nNAME;AA;CC;GG;TT");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 1);
				const Maladie * NAME = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME");
				Assert::IsTrue(NAME->definition.size() == 4);
			}
			catch (...) {
				Assert::Fail();
			}

		}

		TEST_METHOD(ChargerFichier_CorrectSyntaxes_NoLastCRLF_Multiple)
		{
			// La dernière ligne peut omettre \r\n
			// Test sur un dictionnaire à plusieurs entrées

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);
			
			FileUtil::write(_dicoTestFile, "MA v1.0\r\nNAME;AA;CC;GG;TT\r\nNAME2;AAAA;CCCC");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 2);
				const Maladie * NAME = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME");
				Assert::IsTrue(NAME->definition.size() == 4);
				const Maladie * NAME2 = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME2");
				Assert::IsTrue(NAME2->definition.size() == 2);
			}
			catch (...) {
				Assert::Fail();
			}
		}

		TEST_METHOD(ObtenirMaladie_KnownMaladie) {

			// Une maladie connue doit pouvoir être retrouvée dans le dictionnaire

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);

			FileUtil::write(_dicoTestFile, "MA v1.0\r\nNAME;AA;CC;GG;TT\r\n");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				const Maladie * NAME = Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME");
				Assert::IsTrue(NAME->definition.size() == 4);
				Assert::IsTrue(NAME->nom == "NAME");

				unsigned int indexAA = Mots::ObtenirInstance().ObtenirIndex("AA");
				Assert::IsTrue((*(Dictionnaire::ObtenirInstance().ObtenirMaladies(indexAA).find(NAME)))->nom == "NAME");
			}
			catch (...) {
				Assert::Fail();
			}

		}

		TEST_METHOD(ObtenirMaladie_UnknownMaladie) {

			// CHercher une maladie inconnue lève une exception "range_error"

			bool rangeErrorException = false;

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);

			FileUtil::write(_dicoTestFile, "MA v1.0\r\nNAME;AA;CC;GG;TT\r\n");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);
				
				Dictionnaire::ObtenirInstance().ObtenirMaladie("MALADIE_INEXISTANTE");

				Assert::Fail();
			}
			catch (range_error const& e) {
				UNREFERENCE_PARAMETER(e);
				
				rangeErrorException = true;

			}
			
			Assert::IsTrue(rangeErrorException);

		}

		TEST_METHOD(ObtenirMaladie_KnownMaladies) {

			// Des maladies connues doivent pouvoir être retrouvée dans le dictionnaire 

			FileUtil::write(_dicoTestFile, "MA v1.0\r\nNAME;AA;CC;GG;TT\r\nNAME2;AA;CCCC\r\n");
			try {
				Dictionnaire::ObtenirInstance().ChargerFichier(_dicoTestFile);

				Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 2);

				const unordered_set<const Maladie*> maladies = Dictionnaire::ObtenirInstance().ObtenirMaladies(0);

				Assert::IsTrue(maladies.size() == 2);

				Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME")->nom == "NAME");

				Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirMaladie("NAME2")->nom == "NAME2");

			}
			catch (...) {
				Assert::Fail();
			}
		}
	
		TEST_METHOD(ObtenirMaladies_NoMaladies) {

			// On doit obtenir aucune maladie pour un mot inexistant

			char motInexistant[] = "ATCGINEXISTANT";
			
			unsigned int indexMotInexistant = Mots::ObtenirInstance().InsererMot(motInexistant);
			const unordered_set<const Maladie*> resultat = Dictionnaire::ObtenirInstance().ObtenirMaladies(indexMotInexistant);
			
			Assert::IsTrue(0 == resultat.size());
		}

		TEST_METHOD(ObtenirNomsMaladies_EmptyDictionnaire) {
			
			// On ne doit pas pouvoir récupérer de maladies dans un dictionnaire vide

			FileUtil::write(_dicoTestFile, "MA v1.0\r\n");

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);

			unsigned int inexistantMaladieId = 42;

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirMaladies(inexistantMaladieId).size() == 0);

			FileUtil::write(_dicoTestFile, "");

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirNomsMaladies().size() == 0);

			Assert::IsTrue(Dictionnaire::ObtenirInstance().ObtenirMaladies(inexistantMaladieId).size() == 0);

		}
	

	};
}