#include "stdafx.h"

#include <ctime>
#include "CppUnitTest.h"

#include "../bigint/unsigned_bigint.h"
#include "../DES/des.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {

	TEST_CLASS(DES_test) {
public:
	TEST_METHOD(DES_Enc_Dec) {
		srand((unsigned)time(NULL));
		for (int i = 0; i < 1000; i++) {
			unsigned_bigint<2> rand_source = unsigned_bigint<2>::rand();
			std::bitset<64> key(rand_source.data[0]), data(rand_source.data[1]), buffer1, buffer2;
			buffer1 = DES::encro(data, key);
			buffer2 = DES::decro(buffer1, key);
			Assert::IsTrue(data == buffer2);
		}
	}
	};

}  // namespace UnitTest