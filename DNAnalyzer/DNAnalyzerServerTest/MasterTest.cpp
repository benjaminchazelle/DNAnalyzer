#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DNAnalyzerServer/Master.h"
#include <exception>

#define UNREFERENCE_PARAMETER(P) (P)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DNAnalyzerServerTest
{
	TEST_CLASS(MasterTest)
	{
	public:

	
		//routerRequete
		TEST_METHOD(routerRequete_Empty)
		{
			// Requ�te vide

			string requete = "";

			Assert::IsTrue(Master::routerRequete(requete) == Route::ERREUR_SYNTAXE);

		}

		//routerRequete
		TEST_METHOD(routerRequete_AnalyseGlobale_Cool)
		{
			// Requ�te d'analyse globale bien form�e

			string requete;
			requete += "MA v1.0\r\n";
			requete += "CHECK ALL\r\n";
			requete += "AA;CC;TT;GG;\r\n";

			Assert::IsTrue(Master::routerRequete(requete) == Route::ANALYSE_GLOBALE);

		}

		TEST_METHOD(routerRequete_AnalyseGlobale_Vide)
		{
			// Requ�te d'analyse globale bien form�e

			string requete;
			requete += "MA v1.0\r\n";
			requete += "CHECK ALL\r\n";
			requete += "\r\n";

			Assert::IsTrue(Master::routerRequete(requete) == Route::ERREUR_SYNTAXE);

		}

		TEST_METHOD(routerRequete_AnalysePrecise_Cool)
		{
			// Requ�te d'analyse globale bien form�e

			string requete;
			requete += "MA v1.0\r\n";
			requete += "CHECK DISEASE\r\n";
			requete += "AA;CC;TT;GG;\r\n";

			Assert::IsTrue(Master::routerRequete(requete) == Route::ANALYSE_PRECISE);

		}

		TEST_METHOD(routerRequete_AnalysePrecise_Vide)
		{
			// Requ�te d'analyse globale bien form�e

			string requete;
			requete += "MA v1.0\r\n";
			requete += "CHECK DISEASE\r\n";
			requete += "\r\n";

			Assert::IsTrue(Master::routerRequete(requete) == Route::ERREUR_SYNTAXE);

		}

		TEST_METHOD(routerRequete_ListeMaladie_Cool)
		{
			// Requ�te de listage des maladies bien form�e

			string requete;
			requete += "MA v1.0\r\n";
			requete += "GET DISEASES\r\n";
			requete += "\r\n";

			Assert::IsTrue(Master::routerRequete(requete) == Route::LISTE_MALADIES);

		}

		TEST_METHOD(routerRequete_ServiceInconnu_Cool)
		{
			// Requ�te d'analyse globale bien form�e

			string requete;
			requete += "MA v1.0\r\n";
			requete += "UNKNOWN SERVICE\r\n";
			requete += "AA;CC;TT;GG;\r\n";

			Assert::IsTrue(Master::routerRequete(requete) == Route::SERVICE_INCONNU);

			requete = "";
			requete += "MA v1.0\r\n";
			requete += "UNKNOWN SERVICE\r\n";
			requete += "\r\n";

			Assert::IsTrue(Master::routerRequete(requete) == Route::SERVICE_INCONNU);

		}

		TEST_METHOD(routerRequete_ErreurSyntaxe_Header)
		{
			// Requ�te d'analyse globale bien form�e

			string requete;
			requete += "INCORRECT HEADER\r\n";
			requete += "CHECK ALL\r\n";
			requete += "AA;CC;TT;GG;\r\n";

			Assert::IsTrue(Master::routerRequete(requete) == Route::ERREUR_SYNTAXE);

			requete = "";
			requete += "INCORRECT HEADER\r\n";
			requete += "CHECK ALL\r\n";
			requete += "\r\n";

			Assert::IsTrue(Master::routerRequete(requete) == Route::ERREUR_SYNTAXE);

		}

		TEST_METHOD(routerRequete_ErreurSyntaxe_Endl)
		{
			// Requ�te d'analyse globale bien form�e

			string requete;
			requete += "MA v1.0\n";
			requete += "CHECK ALL\n";
			requete += "AA;CC;TT;GG;\n";

			Assert::IsTrue(Master::routerRequete(requete) == Route::ERREUR_SYNTAXE);

			requete = "";
			requete += "MA v1.0\n";
			requete += "CHECK ALL\n";
			requete += "\n";

			Assert::IsTrue(Master::routerRequete(requete) == Route::ERREUR_SYNTAXE);

		}

	
	};
}