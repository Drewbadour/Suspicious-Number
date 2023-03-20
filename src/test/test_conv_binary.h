
TEST conv_binary_ParseBinary_header_only(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseBinary("0b", MAX_BYTES, parsedInput, &outNumBytes);

    ASSERT_ENUM_EQ(Outcome_Empty, outcomeState, outcome_stateToString);
    PASS();
}

TEST conv_binary_ParseBinary_header_trap(void)
{
	// Intentionally undersized maxDataCount,
	// where the header is more bytes than maxDataCount.

	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseBinary("0b1111", 1, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Overflow, outcomeState, outcome_stateToString);
	PASS();
}

TEST conv_binary_ParseBinary_undersized_max_length(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseBinary("0b1111", 4, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Overflow, outcomeState, outcome_stateToString);
	PASS();
}

TEST conv_binary_ParseBinary_zero(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseBinary("0", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
    ASSERT_EQ_FMT(0b0, parsedInput[0], "0x%X");
	ASSERT_EQ_FMT(1, outNumBytes, "%i");
	PASS();
}

TEST conv_binary_ParseBinary_single_digit(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseBinary("1", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(0b1, parsedInput[0], "0x%X");
	ASSERT_EQ_FMT(1, outNumBytes, "%i");
	PASS();
}

TEST conv_binary_ParseBinary_two_digit(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseBinary("10", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(0b10, parsedInput[0], "0x%X");
	ASSERT_EQ_FMT(1, outNumBytes, "%i");
	PASS();
}

TEST conv_binary_ParseBinary_three_digit(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseBinary("101", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(0b101, parsedInput[0], "0x%X");
	ASSERT_EQ_FMT(1, outNumBytes, "%i");
	PASS();
}

TEST conv_binary_ParseBinary_twelve_digit(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseBinary("101001010101", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(0b01010101, parsedInput[0], "0x%X");
	ASSERT_EQ_FMT(0b1010, parsedInput[1], "0x%X");
	ASSERT_EQ_FMT(2, outNumBytes, "%i");
	PASS();
}

TEST conv_binary_ParseBinary_sixteen_digit(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseBinary("1010101001010101", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(0b01010101, parsedInput[0], "0x%X");
	ASSERT_EQ_FMT(0b10101010, parsedInput[1], "0x%X");
	ASSERT_EQ_FMT(2, outNumBytes, "%i");
	PASS();
}

TEST conv_binary_ParseBinary_leading_zero(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseBinary("0b0101", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(0b0101, parsedInput[0], "0x%X");
	ASSERT_EQ_FMT(1, outNumBytes, "%i");
	PASS();
}

TEST conv_binary_ParseBinary_floating_leading_zero(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseBinary("0b00011111111", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(0b11111111, parsedInput[0], "0x%X");
	ASSERT_EQ_FMT(1, outNumBytes, "%i");
	PASS();
}

TEST conv_binary_ParseBinary_zero_byte(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseBinary("0b111111110000000011111111", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(0b11111111, parsedInput[0], "0x%X");
	ASSERT_EQ_FMT(0b00000000, parsedInput[1], "0x%X");
	ASSERT_EQ_FMT(0b11111111, parsedInput[2], "0x%X");
	ASSERT_EQ_FMT(3, outNumBytes, "%i");
	PASS();
}

SUITE(conv_binary)
{
	RUN_TEST(conv_binary_ParseBinary_header_only);
	RUN_TEST(conv_binary_ParseBinary_header_trap);
	RUN_TEST(conv_binary_ParseBinary_undersized_max_length);
	RUN_TEST(conv_binary_ParseBinary_zero);
	RUN_TEST(conv_binary_ParseBinary_single_digit);
	RUN_TEST(conv_binary_ParseBinary_two_digit);
	RUN_TEST(conv_binary_ParseBinary_three_digit);
	RUN_TEST(conv_binary_ParseBinary_twelve_digit);
	RUN_TEST(conv_binary_ParseBinary_sixteen_digit);
	RUN_TEST(conv_binary_ParseBinary_leading_zero);
	RUN_TEST(conv_binary_ParseBinary_floating_leading_zero);
	RUN_TEST(conv_binary_ParseBinary_zero_byte);
}
