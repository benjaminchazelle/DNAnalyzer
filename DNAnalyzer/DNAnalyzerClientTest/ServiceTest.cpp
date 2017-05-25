#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DNAnalyzerClient/Service.h"
#include "../TestUtil/FileUtil.h"

#include <unordered_map>
#include <unordered_set>
#include <exception>
#include <stdexcept>

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
			catch (...) {
				throw;
			}

		}

		static bool analysePreciseParseur(const string & response)
		{
			try {
				return Service::analysePreciseParseur(response);
			}
			catch (...) {
				throw;
			}
		}

		static unordered_set<string> analyseGlobaleParseur(const string & response)
		{
			try {
				return Service::analyseGlobaleParseur(response);
			}
			catch (...) {
				throw;
			}
		}

		static unordered_set<string> obtenirMaladiesParseur(const string & response)
		{
			try {
				return Service::obtenirMaladiesParseur(response);
			}
			catch (...) {
				throw;
			}
		}

		static void verifierLigneErreur(const string & line)
		{
			try {
				return Service::verifierLigneErreur(line);
			}
			catch (...) {
				throw;
			}
		}

		static void trimCarriageReturn(string & str)
		{
			Service::trimCarriageReturn(str);
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
			// On doit réussir à lire un fichier existant et lisible

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
			// Essayer de lire un fichier inexistant lève une exception "runtime_error"

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

		TEST_METHOD(obtenirMaladiesParseur_GoodProtocol)
		{
			// On doit pouvoir parser une réponse ObtenirMaladie du protocole actuel

			string response = "MA v1.0\r\n";
			response += "DISEASES\r\n";
			response += "Maladie1\r\n";
			response += "Maladie2\r\n";
			response += "Maladie3\r\n";
			response += "\r\n";

			unordered_set<string> maladies;

			try {
				maladies = ServiceTestInterface::obtenirMaladiesParseur(response);
			}
			catch (std::exception const& e) {
				UNREFERENCE_PARAMETER(e);
				Assert::Fail();
			}

			Assert::IsTrue(maladies.size() == 3);

			Assert::IsTrue(maladies.find("Maladie1") != maladies.end());
			Assert::IsTrue(maladies.find("Maladie2") != maladies.end());
			Assert::IsTrue(maladies.find("Maladie3") != maladies.end());
		}

		TEST_METHOD(obtenirMaladiesParseur_RetroProtocol)
		{
			// On doit pouvoir parser une réponse ObtenirMaladie du protocole antérieur

			string response = "MA v1.0\r\n";
			response += "DESEASES\r\n";
			response += "Maladie1\r\n";
			response += "Maladie2\r\n";
			response += "Maladie3\r\n";
			response += "\r\n";

			unordered_set<string> maladies;

			try {
				maladies = ServiceTestInterface::obtenirMaladiesParseur(response);
			}
			catch (std::exception const& e) {
				UNREFERENCE_PARAMETER(e);
				Assert::Fail();
			}

			Assert::IsTrue(maladies.size() == 3);

			Assert::IsTrue(maladies.find("Maladie1") != maladies.end());
			Assert::IsTrue(maladies.find("Maladie2") != maladies.end());
			Assert::IsTrue(maladies.find("Maladie3") != maladies.end());
		}

		TEST_METHOD(obtenirMaladiesParseur_InvalidResponseError)
		{
			// On doit pouvoir détécter une réponse serveur invalide lors d'un ObtenirMaladie

			string response = "MA v1.0\r\n";
			response += "INVALID RESPONSE\r\n";
			response += "Maladie1\r\n";
			response += "Maladie2\r\n";
			response += "Maladie3\r\n";
			response += "\r\n";

			bool invalidArgumentException = false;

			unordered_set<string> maladies;

			try {
				maladies = ServiceTestInterface::obtenirMaladiesParseur(response);
				Assert::Fail();
			}
			catch (invalid_argument const& e) {
				UNREFERENCE_PARAMETER(e);
				invalidArgumentException = true;
			}

			Assert::IsTrue(invalidArgumentException);
		}

		TEST_METHOD(obtenirMaladiesParseur_InvalidRequestError)
		{
			// On doit pouvoir détécter une requête invalide lors d'un ObtenirMaladie

			string response = "MA v1.0\r\n";
			response += "ERROR ErrorDescription\r\n";
			response += "\r\n";

			bool runtimeErrorException = false;

			unordered_set<string> maladies;

			try {
				maladies = ServiceTestInterface::obtenirMaladiesParseur(response);
				Assert::Fail();
			}
			catch (runtime_error const& e) {
				UNREFERENCE_PARAMETER(e);
				runtimeErrorException = true;
				Assert::AreEqual(e.what(), "ErrorDescription");
			}

			Assert::IsTrue(runtimeErrorException);
		}

		TEST_METHOD(analysePreciseParseur_GoodProtocol)
		{
			// On doit pouvoir parser une réponse AnalysePrecise du protocole actuel

			{
				string response = "MA v1.0\r\n";
				response += "DISEASE Maladie1\r\n";
				response += "1\r\n";
				response += "\r\n";

				bool result;

				try {
					result = ServiceTestInterface::analysePreciseParseur(response);
				}
				catch (exception const& e)
				{
					UNREFERENCE_PARAMETER(e);
					Assert::Fail();
				}

				Assert::IsTrue(result);
			}

			{
				string response = "MA v1.0\r\n";
				response += "DISEASE Maladie1\r\n";
				response += "0\r\n";
				response += "\r\n";

				bool result;

				try {
					result = ServiceTestInterface::analysePreciseParseur(response);
				}
				catch (exception const& e)
				{
					UNREFERENCE_PARAMETER(e);
					Assert::Fail();
				}
				Assert::IsFalse(result);

			}
		}

		TEST_METHOD(analysePreciseParseur_RetroProtocol)
		{
			// On doit pouvoir parser une réponse AnalysePrecise du protocole antérieur

			{
				string response = "MA v1.0\r\n";
				response += "DESEASE Maladie1\r\n";
				response += "1\r\n";
				response += "\r\n";

				bool result;

				try {
					result = ServiceTestInterface::analysePreciseParseur(response);
				}
				catch (exception const& e)
				{
					UNREFERENCE_PARAMETER(e);
					Assert::Fail();
				}

				Assert::IsTrue(result);
			}

			{
				string response = "MA v1.0\r\n";
				response += "DESEASE Maladie1\r\n";
				response += "0\r\n";
				response += "\r\n";

				bool result;

				try {
					result = ServiceTestInterface::analysePreciseParseur(response);
				}
				catch (exception const& e)
				{
					UNREFERENCE_PARAMETER(e);
					Assert::Fail();
				}

				Assert::IsFalse(result);

			}
		}

		TEST_METHOD(analysePreciseParseur_InvalidResponseError)
		{
			// On doit pouvoir détécter une réponse serveur invalide lors d'un AnalysePrecise


			string response = "MA v1.0\r\n";
			response += "INVALID RESPONSE\r\n";
			response += "1\r\n";
			response += "\r\n";

			bool invalidArgumentException = false;

			bool result;

			try {
				ServiceTestInterface::analysePreciseParseur(response);
				Assert::Fail();
			}
			catch (invalid_argument const& e)
			{
				UNREFERENCE_PARAMETER(e);
				invalidArgumentException = true;
			}

			Assert::IsTrue(invalidArgumentException);

		}

		TEST_METHOD(analysePreciseParseur_InvalidRequestError)
		{
			// On doit pouvoir détécter une requête invalide lors d'un AnalysePrecise

			string response = "MA v1.0\r\n";
			response += "ERROR ErrorDescription\r\n";
			response += "1\r\n";
			response += "\r\n";

			bool runtimeErrorException = false;

			bool result;

			try {
				ServiceTestInterface::analysePreciseParseur(response);
				Assert::Fail();
			}
			catch (runtime_error const& e)
			{
				UNREFERENCE_PARAMETER(e);
				runtimeErrorException = true;

				Assert::AreEqual(e.what(), "ErrorDescription");
			}

			Assert::IsTrue(runtimeErrorException);

		}

		TEST_METHOD(analyseGlobaleParseur_GoodProtocol)
		{
			// On doit pouvoir parser une réponse AnalyseGlobale du protocole actuel

			string response = "MA v1.0\r\n";
			response += "DISEASE Maladie1\r\n";
			response += "DISEASE Maladie2\r\n";
			response += "DISEASE Maladie3\r\n";
			response += "\r\n";

			unordered_set<string> results;

			try
			{
				results = ServiceTestInterface::analyseGlobaleParseur(response);
			}
			catch (exception const& e)
			{
				Assert::Fail();
			}

			Assert::IsTrue(results.size() == 3);

			Assert::IsTrue(results.find("Maladie1") != results.end());
			Assert::IsTrue(results.find("Maladie2") != results.end());
			Assert::IsTrue(results.find("Maladie3") != results.end());

		}

		TEST_METHOD(analyseGlobaleParseur_RetroProtocol)
		{
			// On doit pouvoir parser une réponse AnalyseGlobale du protocole antérieur

			string response = "MA v1.0\r\n";
			response += "DESEASE Maladie1\r\n";
			response += "DESEASE Maladie2\r\n";
			response += "DESEASE Maladie3\r\n";
			response += "\r\n";

			unordered_set<string> results;

			try
			{
				results = ServiceTestInterface::analyseGlobaleParseur(response);
			}
			catch (exception const& e)
			{
				Assert::Fail();
			}

			Assert::IsTrue(results.size() == 3);

			Assert::IsTrue(results.find("Maladie1") != results.end());
			Assert::IsTrue(results.find("Maladie2") != results.end());
			Assert::IsTrue(results.find("Maladie3") != results.end());

		}

		TEST_METHOD(analyseGlobaleParseur_InvalidResponseError)
		{
			// On doit pouvoir détécter une réponse serveur invalide lors d'un AnalyseGlobale

			string response = "MA v1.0\r\n";
			response += "INVALID RESPONSE\r\n";
			response += "DESEASE Maladie2\r\n";
			response += "DESEASE Maladie3\r\n";
			response += "\r\n";

			bool invalidArgumentException = false;

			unordered_set<string> results;

			try
			{
				results = ServiceTestInterface::analyseGlobaleParseur(response);
				Assert::Fail();
			}
			catch (invalid_argument const& e)
			{
				UNREFERENCE_PARAMETER(e);
				invalidArgumentException = true;
			}

			Assert::IsTrue(invalidArgumentException);

		}

		TEST_METHOD(analyseGlobaleParseur_InvalidRequestError)
		{
			// On doit pouvoir détécter une requête invalide lors d'un AnalyseGlobale

			string response = "MA v1.0\r\n";
			response += "ERROR ErrorDescription\r\n";
			response += "\r\n";

			bool runtimeErrorException = false;

			unordered_set<string> results;

			try
			{
				results = ServiceTestInterface::analyseGlobaleParseur(response);
				Assert::Fail();
			}
			catch (runtime_error const& e)
			{
				runtimeErrorException = true;
				Assert::AreEqual(e.what(), "ErrorDescription");
			}

			Assert::IsTrue(runtimeErrorException);


		}

		TEST_METHOD(verifierErreurLigne_Error)
		{
			// Une exception "runtime_error" contenant l'erreur est levée si l'erreur existe

			const string line = "ERROR DescriptionError";

			bool runtimeExceptionError = false;

			try
			{
				ServiceTestInterface::verifierLigneErreur(line);
				Assert::Fail();
			}
			catch (runtime_error const &e)
			{
				Assert::AreEqual(e.what(), "DescriptionError");
				runtimeExceptionError = true;
			}

			Assert::IsTrue(runtimeExceptionError);

		}

		TEST_METHOD(verifierErreurLigne_NoError)
		{
			// Aucune exception n'est levée si aucune erreur existe

			const string line = "DISEASE Maladie\r";

			try
			{
				ServiceTestInterface::verifierLigneErreur(line);
			}
			catch (exception &e)
			{
				Assert::Fail();
			}

		}

		TEST_METHOD(trimCarriageReturn_Without)
		{
			string str = "Hello world !";

			ServiceTestInterface::trimCarriageReturn(str);

			Assert::IsTrue(str == "Hello world !");
		}

		TEST_METHOD(trimCarriageReturn_With)
		{
			string str = "Hello world !\r";

			ServiceTestInterface::trimCarriageReturn(str);

			Assert::IsTrue(str == "Hello world !");
		}
	};
}