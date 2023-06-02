#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include "../PiPicApp/datamanager.h"
#include "../PiPicApp/pipiccommon.h"
#include "../PiPicApp/utility.h"

using namespace testing;

TEST(pipic_test_suite, pipic_decimalToHex) {
  char rr = decimalToHex(2);

  EXPECT_EQ(rr, '2');
  ASSERT_THAT(0, Eq(0));
}

TEST(pipic_test_suite, datamanager_WriteValue_EmptyFileName) {
  std::string fileName = "";

  datamanager dm;
  BhimInteger bh;

  PiPicError er = PiPicError::OK;

  try {
    dm.Write_Value(fileName, bh);
  } catch (PiPicException& err) {
    er = err.GetError();
  }

  EXPECT_EQ(er, PiPicError::BadFileName);
  ASSERT_THAT(0, Eq(0));
}
