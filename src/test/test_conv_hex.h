
TEST conv_hex_ParseHex_header_only(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseHex("0x", MAX_BYTES, parsedInput, &outNumBytes);

    ASSERT_ENUM_EQ(Outcome_Empty, outcomeState, outcome_stateToString);
    PASS();
}

TEST conv_hex_ParseHex_header_trap(void)
{
	// Intentionally undersized maxDataCount,
	// where the header is more bytes than maxDataCount.

	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseHex("0x1234", 1, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Overflow, outcomeState, outcome_stateToString);
	PASS();
}

TEST conv_hex_ParseHex_undersized_max_length(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseHex("0x1234", 4, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Overflow, outcomeState, outcome_stateToString);
	PASS();
}

TEST conv_hex_ParseHex_zero(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseHex("0", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(0x00, parsedInput[0], "0x%X");
	ASSERT_EQ_FMT(1, outNumBytes, "%i");
	PASS();
}

TEST conv_hex_ParseHex_single_digit(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseHex("1", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(0x01, parsedInput[0], "0x%X");
	ASSERT_EQ_FMT(1, outNumBytes, "%i");
	PASS();
}

TEST conv_hex_ParseHex_two_digit(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseHex("23", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(0x23, parsedInput[0], "0x%X");
	ASSERT_EQ_FMT(1, outNumBytes, "%i");
	PASS();
}

TEST conv_hex_ParseHex_three_digit(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseHex("456", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(0x56, parsedInput[0], "0x%X");
	ASSERT_EQ_FMT(0x04, parsedInput[1], "0x%X");
	ASSERT_EQ_FMT(2, outNumBytes, "%i");
	PASS();
}

TEST conv_hex_ParseHex_four_digit(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseHex("789A", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(0x9A, parsedInput[0], "0x%X");
	ASSERT_EQ_FMT(0x78, parsedInput[1], "0x%X");
	ASSERT_EQ_FMT(2, outNumBytes, "%i");
	PASS();
}

TEST conv_hex_ParseHex_five_digit(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseHex("BCDEF", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(0xEF, parsedInput[0], "0x%X");
	ASSERT_EQ_FMT(0xCD, parsedInput[1], "0x%X");
	ASSERT_EQ_FMT(0x0B, parsedInput[2], "0x%X");
	ASSERT_EQ_FMT(3, outNumBytes, "%i");
	PASS();
}

TEST conv_hex_ParseHex_leading_zero(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseHex("0x0123", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(0x23, parsedInput[0], "0x%X");
	ASSERT_EQ_FMT(0x01, parsedInput[1], "0x%X");
	ASSERT_EQ_FMT(2, outNumBytes, "%i");
	PASS();
}

TEST conv_hex_ParseHex_floating_leading_zero(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseHex("0x000123", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(0x23, parsedInput[0], "0x%X");
	ASSERT_EQ_FMT(0x01, parsedInput[1], "0x%X");
	ASSERT_EQ_FMT(2, outNumBytes, "%i");
	PASS();
}

TEST conv_hex_ParseHex_lowercase(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseHex("0xabcdef", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(0xEF, parsedInput[0], "0x%X");
	ASSERT_EQ_FMT(0xCD, parsedInput[1], "0x%X");
	ASSERT_EQ_FMT(0xAB, parsedInput[2], "0x%X");
	ASSERT_EQ_FMT(3, outNumBytes, "%i");
	PASS();
}

TEST conv_hex_ParseHex_uppercase(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseHex("0xABCDEF", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(0xEF, parsedInput[0], "0x%X");
	ASSERT_EQ_FMT(0xCD, parsedInput[1], "0x%X");
	ASSERT_EQ_FMT(0xAB, parsedInput[2], "0x%X");
	ASSERT_EQ_FMT(3, outNumBytes, "%i");
	PASS();
}

TEST conv_hex_ParseHex_zero_byte(void)
{
	uint32_t outNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcome_state outcomeState = ParseHex("0x123400", MAX_BYTES, parsedInput, &outNumBytes);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT(0x00, parsedInput[0], "0x%X");
	ASSERT_EQ_FMT(0x34, parsedInput[1], "0x%X");
	ASSERT_EQ_FMT(0x12, parsedInput[2], "0x%X");
	ASSERT_EQ_FMT(3, outNumBytes, "%i");
	PASS();
}

// TODO(Drew): Leading/trailing space cleanup?

SUITE(conv_hex)
{
    RUN_TEST(conv_hex_ParseHex_header_only);
    RUN_TEST(conv_hex_ParseHex_header_trap);
    RUN_TEST(conv_hex_ParseHex_undersized_max_length);
    RUN_TEST(conv_hex_ParseHex_zero);
    RUN_TEST(conv_hex_ParseHex_single_digit);
    RUN_TEST(conv_hex_ParseHex_two_digit);
    RUN_TEST(conv_hex_ParseHex_three_digit);
    RUN_TEST(conv_hex_ParseHex_four_digit);
    RUN_TEST(conv_hex_ParseHex_five_digit);
    RUN_TEST(conv_hex_ParseHex_leading_zero);
    RUN_TEST(conv_hex_ParseHex_floating_leading_zero);
    RUN_TEST(conv_hex_ParseHex_lowercase);
    RUN_TEST(conv_hex_ParseHex_uppercase);
    RUN_TEST(conv_hex_ParseHex_zero_byte);
}
