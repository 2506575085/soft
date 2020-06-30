#include "stdafx.h"

#include <ctime>
#include "CppUnitTest.h"

#include "../bigint/unsigned_bigint.h"
#include "../AES/AES.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {

	TEST_CLASS(ASE_test) {
public:
	TEST_METHOD(ASE_Enc_Dec) {
		srand((unsigned)time(NULL));
		for (int i = 0; i < 1000; i++) {
			unsigned_bigint<2> key = unsigned_bigint<2>::rand();
			unsigned_bigint<8> data = unsigned_bigint<2>::rand();
			unsigned_bigint<8> buffer1, buffer2;
			aesEncrypt((uint8_t *)key.data, 16, (uint8_t *)data.data, (uint8_t *)buffer1.data, sizeof data.data);
			aesDecrypt((uint8_t *)key.data, 16, (uint8_t *)buffer1.data, (uint8_t *)buffer2.data, sizeof data.data);
			Assert::IsTrue(data == buffer2);
		}
	}
	};

}  // namespace UnitTest