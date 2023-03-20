
TEST conv_decimal_ParseDecimal_undersized_max_length(void)
{
	// NOTE(Drew): Currently doesn't do max length;
	SKIP();

	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseDecimal("1234", 2, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Overflow, outcomeState, outcome_stateToString);
	PASS();
}

TEST conv_decimal_ParseDecimal_zero(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseDecimal("0", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(0, parsedInput[0], "%i");
	ASSERT_EQ_FMT(1, outNumBytes, "%i");
	PASS();
}

TEST conv_decimal_ParseDecimal_single_digit(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseDecimal("7", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(7, parsedInput[0], "%i");
	ASSERT_EQ_FMT(1, outNumBytes, "%i");
	PASS();
}

TEST conv_decimal_ParseDecimal_two_digit(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseDecimal("42", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(42, parsedInput[0], "%i");
	ASSERT_EQ_FMT(1, outNumBytes, "%i");
	PASS();
}

TEST conv_decimal_ParseDecimal_three_digit_fits_uint8(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseDecimal("123", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(123, parsedInput[0], "%i");
	ASSERT_EQ_FMT(1, outNumBytes, "%i");
	PASS();
}

TEST conv_decimal_ParseDecimal_three_digit_oversize_uint8(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseDecimal("789", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(21, parsedInput[0], "%i");
	ASSERT_EQ_FMT(3, parsedInput[1], "%i");
	ASSERT_EQ_FMT(2, outNumBytes, "%i");
	PASS();
}

TEST conv_decimal_ParseDecimal_fits_uint32(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseDecimal("98765", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(205, parsedInput[0], "%i");
	ASSERT_EQ_FMT(129, parsedInput[1], "%i");
	ASSERT_EQ_FMT(1, parsedInput[2], "%i");
	ASSERT_EQ_FMT(3, outNumBytes, "%i");
	PASS();
}

TEST conv_decimal_ParseDecimal_comma_separators(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseDecimal("98,765", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(205, parsedInput[0], "%i");
	ASSERT_EQ_FMT(129, parsedInput[1], "%i");
	ASSERT_EQ_FMT(1, parsedInput[2], "%i");
	ASSERT_EQ_FMT(3, outNumBytes, "%i");
	PASS();
}

TEST conv_decimal_ParseDecimal_max_u64(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseDecimal("18,446,744,073,709,551,615", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(0xFF, parsedInput[0], "0x%X");
	ASSERT_EQ_FMT(0xFF, parsedInput[1], "0x%X");
	ASSERT_EQ_FMT(0xFF, parsedInput[2], "0x%X");
	ASSERT_EQ_FMT(0xFF, parsedInput[3], "0x%X");
	ASSERT_EQ_FMT(0xFF, parsedInput[4], "0x%X");
	ASSERT_EQ_FMT(0xFF, parsedInput[5], "0x%X");
	ASSERT_EQ_FMT(0xFF, parsedInput[6], "0x%X");
	ASSERT_EQ_FMT(0xFF, parsedInput[7], "0x%X");
	ASSERT_EQ_FMT(8, outNumBytes, "%i");
	PASS();
}

TEST conv_decimal_ParseDecimal_number_with_zero_byte(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseDecimal("1,179,700", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(0x34, parsedInput[0], "0x%X");
	ASSERT_EQ_FMT(0x00, parsedInput[1], "0x%X");
	ASSERT_EQ_FMT(0x12, parsedInput[2], "0x%X");
	ASSERT_EQ_FMT(3, outNumBytes, "%i");
	PASS();
}

TEST conv_decimal_ParseDecimal_negative_single_digit(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseDecimal("-7", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(0b11111001, parsedInput[0], "0x%X");
	ASSERT_EQ_FMT(1, outNumBytes, "%i");
	PASS();
}

TEST conv_decimal_ParseDecimal_negative_two_digit(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseDecimal("-42", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(0b11010110, parsedInput[0], "0x%X");
	ASSERT_EQ_FMT(1, outNumBytes, "%i");
	PASS();
}

TEST conv_decimal_ParseDecimal_negative_three_digit_fits_uint8(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseDecimal("-123", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(0b10000101, parsedInput[0], "0x%X");
	ASSERT_EQ_FMT(1, outNumBytes, "%i");
	PASS();
}

TEST conv_decimal_ParseDecimal_negative_three_digit_oversize_uint8(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseDecimal("-789", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(0b11101011, parsedInput[0], "0x%X");
	ASSERT_EQ_FMT(0b11111100, parsedInput[1], "0x%X");
	ASSERT_EQ_FMT(2, outNumBytes, "%i");
	PASS();
}

TEST conv_decimal_ParseDecimal_negative_fits_int16(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseDecimal("-12345", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(0b11000111, parsedInput[0], "0x%X");
	ASSERT_EQ_FMT(0b11001111, parsedInput[1], "0x%X");
	ASSERT_EQ_FMT(2, outNumBytes, "%i");
	PASS();
}

TEST conv_decimal_ParseDecimal_negative_fits_three_bytes(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseDecimal("-98765", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(0b00110011, parsedInput[0], "0x%X");
	ASSERT_EQ_FMT(0b01111110, parsedInput[1], "0x%X");
	ASSERT_EQ_FMT(0b11111110, parsedInput[2], "0x%X");
	ASSERT_EQ_FMT(0b11111111, parsedInput[3], "0x%X");
	ASSERT_EQ_FMT(4, outNumBytes, "%i");
	PASS();
}

TEST conv_decimal_ParseDecimal_number_with_all_ones_byte(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseDecimal("-1879052066", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(0b11011110, parsedInput[0], "0x%X");
	ASSERT_EQ_FMT(0b11110000, parsedInput[1], "0x%X");
	ASSERT_EQ_FMT(0b11111111, parsedInput[2], "0x%X");
	ASSERT_EQ_FMT(0b10001111, parsedInput[3], "0x%X");
	ASSERT_EQ_FMT(4, outNumBytes, "%i");
	PASS();
}

SUITE(conv_decimal)
{
    RUN_TEST(conv_decimal_ParseDecimal_undersized_max_length);
    RUN_TEST(conv_decimal_ParseDecimal_zero);
    RUN_TEST(conv_decimal_ParseDecimal_single_digit);
    RUN_TEST(conv_decimal_ParseDecimal_two_digit);
    RUN_TEST(conv_decimal_ParseDecimal_three_digit_fits_uint8);
    RUN_TEST(conv_decimal_ParseDecimal_three_digit_oversize_uint8);
    RUN_TEST(conv_decimal_ParseDecimal_fits_uint32);
    RUN_TEST(conv_decimal_ParseDecimal_comma_separators);
    RUN_TEST(conv_decimal_ParseDecimal_max_u64);
    RUN_TEST(conv_decimal_ParseDecimal_number_with_zero_byte);
    RUN_TEST(conv_decimal_ParseDecimal_negative_single_digit);
    RUN_TEST(conv_decimal_ParseDecimal_negative_two_digit);
    RUN_TEST(conv_decimal_ParseDecimal_negative_three_digit_fits_uint8);
    RUN_TEST(conv_decimal_ParseDecimal_negative_three_digit_oversize_uint8);
    RUN_TEST(conv_decimal_ParseDecimal_negative_fits_int16);
    RUN_TEST(conv_decimal_ParseDecimal_negative_fits_three_bytes);
    RUN_TEST(conv_decimal_ParseDecimal_number_with_all_ones_byte);
}
