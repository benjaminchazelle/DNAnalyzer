#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DNAnalyzerServer/Master.h"
#include <unordered_set>
#include <string>
#define UNREFERENCE_PARAMETER(P) (P)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestUtil
{
	class MasterTestInterface : public Master
	{
	public:
		static unordered_set<string> encoderGenome(const string & genome)
		{
			return Master::encoderGenome(genome);
		}
	};

	TEST_CLASS(MasterTest)
	{

	public:

		// encoderGenome
		TEST_METHOD(encoderGenome_Success)
		{
			// On extrait un ensemble de mot depuis un génome valide

			string genome = "ATCG;AAAA;CC;TT;GG";

			try {

				unordered_set<string> genomeSet = MasterTestInterface::encoderGenome(genome);

				Assert::IsTrue(genomeSet.size() == 5);

				Assert::IsTrue(genomeSet.find("ATCG") != genomeSet.end());
				Assert::IsTrue(genomeSet.find("AAAA") != genomeSet.end());
				Assert::IsTrue(genomeSet.find("CC") != genomeSet.end());
				Assert::IsTrue(genomeSet.find("TT") != genomeSet.end());
				Assert::IsTrue(genomeSet.find("GG") != genomeSet.end());


			}
			catch (exception const& e)
			{
				UNREFERENCE_PARAMETER(e);

				Assert::Fail();
			}

		}

		TEST_METHOD(encoderGenome_Fail)
		{
			// On extrait un ensemble de mot depuis un génome invalide
			// Une exception "invalid_argument" est alors levée

			string genome = "ATCG;XXXX;CC;TT;GG";

			bool invalidArgumentException = false;

			try {

				unordered_set<string> genomeSet = MasterTestInterface::encoderGenome(genome);

				Assert::Fail();
			}
			catch (invalid_argument const& e)
			{
				UNREFERENCE_PARAMETER(e);

				invalidArgumentException = true;
			}

			Assert::IsTrue(invalidArgumentException);

		}


	};
}