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
		TEST_METHOD_INITIALIZE(Analyse_init) {
			Mots::RafraichirInstance();
			Dictionnaire::RafraichirInstance();
		}
		//AnalysePrecise
		TEST_METHOD(AnalysePrecise_KnownWord)
		{
			// Le mot d'une définition doit bien être retrouvé

			Maladie maladie;

			maladie.nom = "Nom de maladie test";

			maladie.definition.insert(Mots::ObtenirInstance().InsererMot("AAAA"));

			unordered_set<string> genome({"AAAA", "CCCC", "TTTT"});
			Assert::IsTrue(Analyse::AnalysePrecise(genome, maladie));
		}
		TEST_METHOD(AnalysePrecise_AllKnownWords)
		{
			// Tout les mots d'une définition doivent bien être tous retrouvés

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
			// Un mot qui n'est pas dans une définition ne doit pas être retrouvé

			Maladie maladie;

			maladie.nom = "Nom de maladie test";

			maladie.definition.insert(Mots::ObtenirInstance().InsererMot("GGGG"));

			unordered_set<string> genome({ "AAAA", "CCCC", "TTTT" });
			Assert::IsFalse(Analyse::AnalysePrecise(genome, maladie));
		}

		TEST_METHOD(AnalysePrecise_AnyUnknownWords)
		{
			// Une maladie ne peut être reconnue s'il manque un ou plusieurs mots

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


		//AnalyseGlobale
		TEST_METHOD(AnalyseGlobale_Simple)
		{
			// Trouve ou non une maladie parmi plusieurs

			FileUtil::write("data.test.dico", "MA v1.0\r\nTEST_A;AAAA\r\nTEST_B;TTTT\r\n");

			Dictionnaire::ObtenirInstance().ChargerFichier("data.test.dico");

			string genomeData[] = { "AAAA", "CCCC", "GGGG" };
			unordered_set<string> genome (genomeData, genomeData + sizeof(genomeData) / sizeof(genomeData[0]));
			const unordered_set<const Maladie *> resultats = Analyse::AnalyseGlobale(genome);

			const Maladie * TEST_A = Dictionnaire::ObtenirInstance().ObtenirMaladie("TEST_A");
			
			unordered_set<const Maladie *>::iterator itResultat = resultats.begin();
			Assert::IsFalse(itResultat == resultats.end());	// si 0 Maladie trouvé
			Assert::IsTrue((*itResultat)->nom == TEST_A->nom);	// AAAA trouvé
			itResultat++;
			Assert::IsTrue(itResultat == resultats.end());  // Pas d'autre maladie trouver*/
		}

		
		TEST_METHOD(AnalyseGlobale_Complex)
		{
			// Trouve ou non une maladie parmi plusieurs, version complexe

			FileUtil::write("data.test.dico", "MA v1.0\r\nTEST_C;AA;CA;TA;GA\r\nTEST_D;AA;CC;AAA;AAAA;TT\r\n");

			Dictionnaire::ObtenirInstance().ChargerFichier("data.test.dico");

			unordered_set<string> genome({ "GA", "GG", "TA", "TT", "CA", "CC", "AA"});
			const unordered_set<const Maladie *> resultats = Analyse::AnalyseGlobale(genome);

			const Maladie * TEST_C = Dictionnaire::ObtenirInstance().ObtenirMaladie("TEST_C");
			const Maladie * TEST_D = Dictionnaire::ObtenirInstance().ObtenirMaladie("TEST_D");

			unordered_set<const Maladie *>::iterator itResultat = resultats.begin();
			Assert::IsFalse(itResultat == resultats.end());	// si 0 Maladie trouvé
			Assert::IsTrue((*itResultat)->nom == TEST_C->nom);	// TEST_C trouvé
			itResultat++;
			Assert::IsTrue(itResultat == resultats.end());  // Pas d'autre maladie trouver
		}


	};
}