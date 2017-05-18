#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DNAnalyzerServer/Master.h"
#include <exception>

#define UNREFERENCE_PARAMETER(P) (P)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DNAnalyzerServerTest
{


	#ifndef TEST_MASTER_INTERFACE
	#define TEST_MASTER_INTERFACE

	class TestMasterInterface : public Master {
	public:
		static Route routerRequete(const string & requete) {
			return Master::routerRequete(requete);
		}
	};
	#endif // TEST_MASTER_INTERFACE

	TEST_CLASS(MasterTest)
	{
	public:


		//routerRequete
		TEST_METHOD(routerRequete_Empty)
		{
			// Requête vide

			string requete = "";

			Assert::IsTrue(TestMasterInterface::routerRequete(requete) == Route::ERREUR_SYNTAXE);

		}

		//routerRequete
		TEST_METHOD(routerRequete_AnalyseGlobale_OK)
		{
			// Requête d'analyse globale bien formée

			string requete;
			requete += "MA v1.0\r\n";
			requete += "CHECK ALL\r\n";
			requete += "AA;CC;TT;GG;\r\n";

			Assert::IsTrue(TestMasterInterface::routerRequete(requete) == Route::ANALYSE_GLOBALE);

		}

		TEST_METHOD(routerRequete_AnalyseGlobale_Vide)
		{
			// Requête d'analyse globale bien formée

			string requete;
			requete += "MA v1.0\r\n";
			requete += "CHECK ALL\r\n";
			requete += "\r\n";

			Assert::IsTrue(TestMasterInterface::routerRequete(requete) == Route::ERREUR_SYNTAXE);

		}

		TEST_METHOD(routerRequete_AnalysePrecise_OK)
		{
			// Requête d'analyse globale bien formée

			string requete;
			requete += "MA v1.0\r\n";
			requete += "CHECK DISEASE\r\n";
			requete += "AA;CC;TT;GG;\r\n";

			Assert::IsTrue(TestMasterInterface::routerRequete(requete) == Route::ANALYSE_PRECISE);

		}

		TEST_METHOD(routerRequete_AnalysePrecise_Vide)
		{
			// Requête d'analyse globale bien formée

			string requete;
			requete += "MA v1.0\r\n";
			requete += "CHECK DISEASE\r\n";
			requete += "\r\n";

			Assert::IsTrue(TestMasterInterface::routerRequete(requete) == Route::ERREUR_SYNTAXE);

		}

		TEST_METHOD(routerRequete_ListeMaladies_OK)
		{
			// Requête de listage des maladies bien formée

			string requete;
			requete += "MA v1.0\r\n";
			requete += "GET DISEASES\r\n";
			requete += "\r\n";

			Assert::IsTrue(TestMasterInterface::routerRequete(requete) == Route::LISTE_MALADIES);

		}

		TEST_METHOD(routerRequete_ServiceInconnu_OK)
		{
			// Requête d'analyse globale bien formée

			string requete;
			requete += "MA v1.0\r\n";
			requete += "UNKNOWN SERVICE\r\n";
			requete += "AA;CC;TT;GG;\r\n";

			Assert::IsTrue(TestMasterInterface::routerRequete(requete) == Route::SERVICE_INCONNU);

			requete = "";
			requete += "MA v1.0\r\n";
			requete += "UNKNOWN SERVICE\r\n";
			requete += "\r\n";

			Assert::IsTrue(TestMasterInterface::routerRequete(requete) == Route::SERVICE_INCONNU);

		}

		TEST_METHOD(routerRequete_ErreurSyntaxe_Header)
		{
			// Requête d'analyse globale bien formée

			string requete;
			requete += "INCORRECT HEADER\r\n";
			requete += "CHECK ALL\r\n";
			requete += "AA;CC;TT;GG;\r\n";

			Assert::IsTrue(TestMasterInterface::routerRequete(requete) == Route::ERREUR_SYNTAXE);

			requete = "";
			requete += "INCORRECT HEADER\r\n";
			requete += "CHECK ALL\r\n";
			requete += "\r\n";

			Assert::IsTrue(TestMasterInterface::routerRequete(requete) == Route::ERREUR_SYNTAXE);

		}

		TEST_METHOD(routerRequete_ErreurSyntaxe_Endl)
		{
			// Requête d'analyse globale bien formée

			string requete;
			requete += "MA v1.0\n";
			requete += "CHECK ALL\n";
			requete += "AA;CC;TT;GG;\n";

			Assert::IsTrue(TestMasterInterface::routerRequete(requete) == Route::ERREUR_SYNTAXE);

			requete = "";
			requete += "MA v1.0\n";
			requete += "CHECK ALL\n";
			requete += "\n";

			Assert::IsTrue(TestMasterInterface::routerRequete(requete) == Route::ERREUR_SYNTAXE);

		}


	};
}