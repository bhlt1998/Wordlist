#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Wordlist/Core.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Core* core = new Core();
			char* result[100];
			char* words[] = { "Algebra","apple","zoo","elephant","under","fox","dog","moon","leaf","trick","peudopseudohypoparathyroidism" };
			int resultlen = core->gen_chain_word(words, 11, result, 0, 0, false);
			Assert::AreEqual(resultlen, 4);
		}

	};
}