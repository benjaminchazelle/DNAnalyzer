#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DNAnalyzerServer/Analyse.h"
#include "../DNAnalyzerServer/Dictionnaire.h"
#include "../DNAnalyzerServer/Mots.h"
#include "../TestUtil/FileUtil.h"
#include <exception>
#include <string>
#include <unordered_map>

using namespace std;

#define UNREFERENCE_PARAMETER(P) (P)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DNAnalyzerServerTest
{
	TEST_CLASS(AnalyseTest)
	{
	public:

		//AnalysePrecise
		TEST_METHOD(AnalysePrecise_KnownWord)
		{
			// Le mot d'une définition doit bien être retrouvé

			Maladie maladie;

			maladie.nom = "Nom de maladie test";

			maladie.definition.insert(Mots::ObtenirInstance().InsererMot("AAAA"));

			Assert::IsTrue(Analyse::AnalysePrecise("AAAA;CCCC;TTTT", maladie));
		}

		TEST_METHOD(AnalysePrecise_AllKnownWords)
		{
			// Tout les mots d'une définition doivent bien être tous retrouvés

			Maladie maladie;

			maladie.nom = "Nom de maladie test";

			maladie.definition.insert(Mots::ObtenirInstance().InsererMot("AAAA"));
			maladie.definition.insert(Mots::ObtenirInstance().InsererMot("CCCC"));

			Assert::IsTrue(Analyse::AnalysePrecise("AAAA;CCCC;TTTT", maladie));

			Assert::IsTrue(Analyse::AnalysePrecise("TTTT;CCCC;AAAA", maladie));

			Assert::IsTrue(Analyse::AnalysePrecise("TTTT;AAAA;CCCC", maladie));

			Assert::IsTrue(Analyse::AnalysePrecise("CCCC;AAAA;TTTT", maladie));

			Assert::IsTrue(Analyse::AnalysePrecise("AAAA;TTTT;CCCC", maladie));

			Assert::IsTrue(Analyse::AnalysePrecise("CCCC;TTTT;AAAA", maladie));
		}

		TEST_METHOD(AnalysePrecise_UnknownWord)
		{
			// Un mot qui n'est pas dans une définition ne doit pas être retrouvé

			Maladie maladie;

			maladie.nom = "Nom de maladie test";

			maladie.definition.insert(Mots::ObtenirInstance().InsererMot("GGGG"));

			Assert::IsFalse(Analyse::AnalysePrecise("AAAA;CCCC;TTTT", maladie));
		}

		TEST_METHOD(AnalysePrecise_AnyUnknownWords)
		{
			// Une maladie ne peut être reconnue s'il manque un ou plusieurs mots

			Maladie maladie;

			maladie.nom = "Nom de maladie test";

			maladie.definition.insert(Mots::ObtenirInstance().InsererMot("AAAA"));
			maladie.definition.insert(Mots::ObtenirInstance().InsererMot("GGGG"));

			Assert::IsFalse(Analyse::AnalysePrecise("AAAA;CCCC;TTTT", maladie));

			Assert::IsFalse(Analyse::AnalysePrecise("TTTT;CCCC;AAAA", maladie));

			Assert::IsFalse(Analyse::AnalysePrecise("TTTT;AAAA;CCCC", maladie));

			Assert::IsFalse(Analyse::AnalysePrecise("CCCC;AAAA;TTTT", maladie));

			Assert::IsFalse(Analyse::AnalysePrecise("AAAA;TTTT;CCCC", maladie));

			Assert::IsFalse(Analyse::AnalysePrecise("CCCC;TTTT;AAAA", maladie));
		}

		TEST_METHOD(AnalysePrecise_EmptyDefinition)
		{
			// Une maladie sans définition ne peut être retrouvé dans un génome

			Maladie maladie;

			maladie.nom = "Nom de maladie test";

			// Pas de maladie.definition.insert();

			Assert::IsFalse(Analyse::AnalysePrecise("AAAA;TTTT;CCCC", maladie));
		}


		//AnalyseGlobale
		TEST_METHOD(AnalyseGlobale_Simple)
		{
			// Trouve ou non une maladie parmi plusieurs

			FileUtil::write("data.test.dico", "MA v1.0\r\nTEST_A;AAAA\r\nTEST_B;TTTT\r\n");

			Dictionnaire::ObtenirInstance().ChargerFichier("data.test.dico");

			unordered_map<Maladie, bool> resultats = Analyse::AnalyseGlobale("AAAA;CCCC;GGGG");

			Maladie TEST_A = Dictionnaire::ObtenirInstance().ObtenirMaladie("TEST_A");
			Maladie TEST_B = Dictionnaire::ObtenirInstance().ObtenirMaladie("TEST_B");
			
			Assert::IsTrue(resultats.at(TEST_A));	// AAAA trouvé
			Assert::IsFalse(resultats.at(TEST_B));  // TTTT non trouvé
		}

		TEST_METHOD(AnalyseGlobale_EmptyDefinition)
		{
			// Une maladie sans définition ne peut être trouvée

			FileUtil::write("data.test.dico", "MA v1.0\r\nTEST_A;AAAA\r\nTEST_B;TTTT\r\nTEST_Z;\r\n");

			Dictionnaire::ObtenirInstance().ChargerFichier("data.test.dico");

			unordered_map<Maladie, bool> resultats = Analyse::AnalyseGlobale("AAAA;CCCC;GGGG");

			try {
				Maladie TEST_Z = Dictionnaire::ObtenirInstance().ObtenirMaladie("TEST_Z");

				Assert::IsFalse(resultats.at(TEST_Z));
			}
			catch (range_error const& e) {

				UNREFERENCE_PARAMETER(e);
			}


		}

		TEST_METHOD(AnalyseGlobale_Complex)
		{
			// Trouve ou non une maladie parmi plusieurs, version complexe

			FileUtil::write("data.test.dico", "MA v1.0\r\nTEST_C;AA;CA;TA;GA\r\nTEST_D;AA;CC;AAA;AAAA;TT\r\n");

			Dictionnaire::ObtenirInstance().ChargerFichier("data.test.dico");

			unordered_map<Maladie, bool> resultats = Analyse::AnalyseGlobale("GA;GG;TA;TT;CA;CC;AA");

			Maladie TEST_C = Dictionnaire::ObtenirInstance().ObtenirMaladie("TEST_C");
			Maladie TEST_D = Dictionnaire::ObtenirInstance().ObtenirMaladie("TEST_D");

			Assert::IsTrue(resultats.at(TEST_C));  // Dans le désordre, mais ok
			Assert::IsFalse(resultats.at(TEST_D)); // Manque AAA et AAAA
		}


	};
}