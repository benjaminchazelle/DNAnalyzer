#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DNAnalyzerServer/Analyse.h"
#include "../DNAnalyzerServer/Dictionnaire.h"
#include "../DNAnalyzerServer/Mots.h"
#include "../TestUtil/FileUtil.h"
#include <exception>
#include <string>
#include <unordered_map>
#include <unordered_set>

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
			// Le mot d'une d�finition doit bien �tre retrouv�

			Maladie maladie;

			maladie.nom = "Nom de maladie test";

			maladie.definition.insert(Mots::ObtenirInstance().InsererMot("AAAA"));

			unordered_set<string> genome({"AAAA", "CCCC", "TTTT"});
			Assert::IsTrue(Analyse::AnalysePrecise(genome, maladie));
		}
		TEST_METHOD(AnalysePrecise_AllKnownWords)
		{
			// Tout les mots d'une d�finition doivent bien �tre tous retrouv�s

			Maladie maladie;

			maladie.nom = "Nom de maladie test";

			maladie.definition.insert(Mots::ObtenirInstance().InsererMot("AAAA"));
			maladie.definition.insert(Mots::ObtenirInstance().InsererMot("CCCC"));

			unordered_set<string> genome1({ "AAAA", "CCCC", "TTTT" });
			Assert::IsTrue(Analyse::AnalysePrecise(genome1, maladie));

			unordered_set<string> genome2({ "TTTT" , "CCCC" , "AAAA"});
			Assert::IsTrue(Analyse::AnalysePrecise(genome2, maladie));

			unordered_set<string> genome3({ "TTTT" , "AAAA" , "CCCC" });
			Assert::IsTrue(Analyse::AnalysePrecise(genome3, maladie));

			unordered_set<string> genome4({ "CCCC" , "AAAA" , "TTTT" });
			Assert::IsTrue(Analyse::AnalysePrecise(genome4, maladie));

			unordered_set<string> genome5({ "AAAA" , "TTTT" , "CCCC" });
			Assert::IsTrue(Analyse::AnalysePrecise(genome5, maladie));

			unordered_set<string> genome6({ "CCCC" , "TTTT" , "AAAA" });
			Assert::IsTrue(Analyse::AnalysePrecise(genome6, maladie));
		}

		TEST_METHOD(AnalysePrecise_UnknownWord)
		{
			// Un mot qui n'est pas dans une d�finition ne doit pas �tre retrouv�

			Maladie maladie;

			maladie.nom = "Nom de maladie test";

			maladie.definition.insert(Mots::ObtenirInstance().InsererMot("GGGG"));

			unordered_set<string> genome({ "AAAA", "CCCC", "TTTT" });
			Assert::IsFalse(Analyse::AnalysePrecise(genome, maladie));
		}

		TEST_METHOD(AnalysePrecise_AnyUnknownWords)
		{
			// Une maladie ne peut �tre reconnue s'il manque un ou plusieurs mots

			Maladie maladie;

			maladie.nom = "Nom de maladie test";

			maladie.definition.insert(Mots::ObtenirInstance().InsererMot("AAAA"));
			maladie.definition.insert(Mots::ObtenirInstance().InsererMot("GGGG"));

			unordered_set<string> genome1({ "AAAA", "CCCC", "TTTT" });
			Assert::IsFalse(Analyse::AnalysePrecise(genome1, maladie));

			unordered_set<string> genome2({ "TTTT" , "CCCC" , "AAAA" });
			Assert::IsFalse(Analyse::AnalysePrecise(genome2, maladie));

			unordered_set<string> genome3({ "TTTT" , "AAAA" , "CCCC" });
			Assert::IsFalse(Analyse::AnalysePrecise(genome3, maladie));

			unordered_set<string> genome4({ "CCCC" , "AAAA" , "TTTT" });
			Assert::IsFalse(Analyse::AnalysePrecise(genome4, maladie));

			unordered_set<string> genome5({ "AAAA" , "TTTT" , "CCCC" });
			Assert::IsFalse(Analyse::AnalysePrecise(genome5, maladie));

			unordered_set<string> genome6({ "CCCC" , "TTTT" , "AAAA" });
			Assert::IsFalse(Analyse::AnalysePrecise(genome6, maladie));
		}

		TEST_METHOD(AnalysePrecise_EmptyDefinition)
		{
			// Une maladie sans d�finition ne peut �tre retrouv� dans un g�nome

			Maladie maladie;

			maladie.nom = "Nom de maladie test";

			// Pas de maladie.definition.insert();

			unordered_set<string> genome({ "AAAA", "CCCC", "TTTT" });
			Assert::IsFalse(Analyse::AnalysePrecise(genome, maladie));
		}


		//AnalyseGlobale
		TEST_METHOD(AnalyseGlobale_Simple)
		{
			// Trouve ou non une maladie parmi plusieurs

			FileUtil::write("data.test.dico", "MA v1.0\r\nTEST_A;AAAA\r\nTEST_B;TTTT\r\n");

			Dictionnaire::ObtenirInstance().ChargerFichier("data.test.dico");

			string genomeData[] = { "AAAA", "CCCC", "GGGG" };
			unordered_set<string> genome (genomeData, genomeData + sizeof(genomeData) / sizeof(genomeData[0]));
			const unordered_set<Maladie *> resultats = Analyse::AnalyseGlobale(genome);

			Maladie TEST_A = Dictionnaire::ObtenirInstance().ObtenirMaladie("TEST_A");
			
			unordered_set<Maladie *>::iterator itResultat = resultats.begin();
			Assert::IsFalse(itResultat == resultats.end());	// si 0 Maladie trouv�
			Assert::IsTrue((*itResultat)->nom == TEST_A.nom);	// AAAA trouv�
			itResultat++;
			Assert::IsTrue(itResultat == resultats.end());  // Pas d'autre maladie trouver*/
		}

		TEST_METHOD(AnalyseGlobale_EmptyDefinition)
		{
			// Une maladie sans d�finition ne peut �tre trouv�e

			FileUtil::write("data.test.dico", "MA v1.0\r\nTEST_A;AAAA\r\nTEST_B;TTTT\r\nTEST_Z;\r\n");

			Dictionnaire::ObtenirInstance().ChargerFichier("data.test.dico");

			unordered_set<string> genome({ "AAAA", "CCCC", "GGGG" });
			const unordered_set<Maladie *> resultats = Analyse::AnalyseGlobale(genome);

			try {
				Maladie TEST_Z = Dictionnaire::ObtenirInstance().ObtenirMaladie("TEST_Z");

				for (unordered_set<Maladie *>::iterator itResultat = resultats.begin(); itResultat != resultats.end(); itResultat++) {
					Assert::IsFalse((*itResultat)->nom == TEST_Z.nom);
				}
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

			unordered_set<string> genome({ "GA", "GG", "TA", "TT", "CA", "CC", "AA"});
			const unordered_set<Maladie *> resultats = Analyse::AnalyseGlobale(genome);

			Maladie TEST_C = Dictionnaire::ObtenirInstance().ObtenirMaladie("TEST_C");
			Maladie TEST_D = Dictionnaire::ObtenirInstance().ObtenirMaladie("TEST_D");

			unordered_set<Maladie *>::iterator itResultat = resultats.begin();
			Assert::IsFalse(itResultat == resultats.end());	// si 0 Maladie trouv�
			Assert::IsTrue((*itResultat)->nom == TEST_C.nom);	// TEST_C trouv�
			itResultat++;
			Assert::IsTrue(itResultat == resultats.end());  // Pas d'autre maladie trouver
		}


	};
}