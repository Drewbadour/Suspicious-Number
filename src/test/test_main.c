#include "greatest.h"


#define FORMAT_HELP_TITLE ""
#define FORMAT_HELP_SUBTITLE ""
#define FORMAT_ERROR_TITLE ""
#define FORMAT_ERROR_SUBTITLE ""
#define FORMAT_OVERFLOW_TITLE ""
#define FORMAT_OVERFLOW_SUBTITLE ""


#include "../conv_binary.c"
#include "../conv_decimal.c"
#include "../conv_hex.c"


#include "test_conv_core.h"
#include "test_alfredworkflow_io.h"

#include "test_conv_binary.h"
#include "test_conv_decimal.h"
#include "test_conv_hex.h"

// ASSERT(COND)
// ASSERT_FALSE(COND)
// ASSERT_EQ(EXPECTED, ACTUAL)
// ASSERT_NEQ(EXPECTED, ACTUAL)
// ASSERT_GT(EXPECTED, ACTUAL)
// ASSERT_GTE(EXPECTED, ACTUAL)
// ASSERT_LT(EXPECTED, ACTUAL)
// ASSERT_LTE(EXPECTED, ACTUAL)
// ASSERT_EQ_FMT(EXPECTED, ACTUAL, FORMAT)
// ASSERT_IN_RANGE(EXPECTED, ACTUAL, TOLERANCE)
// ASSERT_STR_EQ(EXPECTED, ACTUAL)
// ASSERT_STRN_EQ(EXPECTED, ACTUAL, SIZE)
// ASSERT_MEM_EQ(EXPECTED, ACTUAL, SIZE)
// ASSERT_ENUM_EQ(EXPECTED, ACTUAL, ENUM_STR_FUN)
// ASSERT_EQUAL_T(EXPECTED, ACTUAL, TYPE_INFO, UDATA)
// ASSERT_OR_LONGJMP(COND)


GREATEST_MAIN_DEFS();

int main(int argc, char** argv)
{
	GREATEST_MAIN_BEGIN();

	RUN_SUITE(conv_binary);
	RUN_SUITE(conv_decimal);
	RUN_SUITE(conv_hex);
	RUN_SUITE(conv_core);

	RUN_SUITE(alfredworkflow_io);




	GREATEST_MAIN_END();
}
