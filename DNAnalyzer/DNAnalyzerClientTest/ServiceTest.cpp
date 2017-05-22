#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DNAnalyzerClient/Service.h"
#include "../TestUtil/FileUtil.h"

#include <unordered_map>
#include <unordered_set>

#define UNREFERENCE_PARAMETER(P) (P)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DNAnalyzerClientTest
{
	class ServiceTestInterface : public Service
	{
	public:
		static string lireFichier(string filename)
		{
			try {
				return Service::lireFichier(filename);
			}
			catch (runtime_error const& e) {
				throw runtime_error(e.what());
			}

		}

		static bool analysePreciseParseur(const string & response)
		{
			try {
				return Service::analysePreciseParseur(response);
			}
			catch (invalid_argument const& e) {
				throw invalid_argument(e.what());
			}
		}

		static unordered_set<string> analyseGlobaleParseur(const string & response)
		{
			try {
				return Service::analyseGlobaleParseur(response);
			}
			catch (invalid_argument const& e) {
				throw invalid_argument(e.what());
			}
		}

		static unordered_set<string> obtenirMaladiesParseur(const string & response)
		{
			try {
				return Service::obtenirMaladiesParseur(response);
			}
			catch (invalid_argument const& e) {
				throw invalid_argument(e.what());
			}
		}
	};

	TEST_CLASS(ServiceTest)
	{
	protected:

		const string _fichierGenome = "test.genome";

	public:

		TEST_METHOD_INITIALIZE(Initialize)
		{
			FileUtil::unlink(_fichierGenome);

		}

		TEST_METHOD_CLEANUP(CleanUp)
		{
			FileUtil::unlink(_fichierGenome);

		}

		TEST_METHOD(LireFichier_Existant)
		{
			string content = "Contenu du fichier";

			FileUtil::write(_fichierGenome, content);

			try {
				Assert::IsTrue(ServiceTestInterface::lireFichier(_fichierGenome) == content);
			}
			catch (std::exception const& e) {
				UNREFERENCE_PARAMETER(e);
				Assert::Fail();
			}

		}

		TEST_METHOD(LireFichier_Inexistant)
		{
			string content = "Contenu du fichier";

			FileUtil::unlink(_fichierGenome);

			bool runtimeErrorException = false;

			try {
				ServiceTestInterface::lireFichier(_fichierGenome);

				Assert::Fail();

			}
			catch (runtime_error const& e) {

				UNREFERENCE_PARAMETER(e);

				runtimeErrorException = true;
			}

			Assert::IsTrue(runtimeErrorException);
		}

		TEST_METHOD(ObtenirMaladies)
		{
			string response = "MA v1.0\r\n";
			response += "DESEASES\r\n";
			response += "Maladie1\r\n";
			response += "Maladie2\r\n";
			response += "Maladie3\r\n";
			response += "\r\n";

			unordered_set<string> maladies = ServiceTestInterface::obtenirMaladiesParseur(response);

			Assert::IsTrue(maladies.size() == 3);

			Assert::IsTrue(maladies.find("Maladie1") != maladies.end());
			Assert::IsTrue(maladies.find("Maladie2") != maladies.end());
			Assert::IsTrue(maladies.find("Maladie3") != maladies.end());

		}
		
		TEST_METHOD(AnalysePrecise)
		{

			{
				string response = "MA v1.0\r\n";
				response += "DESEASE Maladie1\r\n";
				response += "1\r\n";
				response += "\r\n";

				bool result = ServiceTestInterface::analysePreciseParseur(response);

				Assert::IsTrue(result);
			}

			{
				string response = "MA v1.0\r\n";
				response += "DESEASE Maladie1\r\n";
				response += "0\r\n";
				response += "\r\n";

				bool result = ServiceTestInterface::analysePreciseParseur(response);

				Assert::IsFalse(result);

			}
		}
		
		TEST_METHOD(AnalyseGlobale)
		{

			string response = "MA v1.0\r\n";
			response += "DESEASE Maladie1\r\n";
			response += "DESEASE Maladie2\r\n";
			response += "DESEASE Maladie3\r\n";
			response += "\r\n";

			unordered_set<string> results = ServiceTestInterface::analyseGlobaleParseur(response);

			Assert::IsTrue(results.size() == 3);

			Assert::IsTrue(results.find("Maladie1") != results.end());
			Assert::IsTrue(results.find("Maladie2") != results.end());
			Assert::IsTrue(results.find("Maladie3") != results.end());	

		}

	};
}