
// MARK: BinaryStringForNum

TEST conv_core_BinaryStringForNum_all_zeroes(void)
{
	uint8_t outputData[9] = {};
	BinaryStringForNum(0, outputData);

	ASSERT_STR_EQ("00000000", outputData);
	PASS();
}

TEST conv_core_BinaryStringForNum_all_ones(void)
{
	uint8_t outputData[9] = {};
	BinaryStringForNum(255, outputData);

	ASSERT_STR_EQ("11111111", outputData);
	PASS();
}

TEST conv_core_BinaryStringForNum_half_ones(void)
{
	uint8_t outputData[9] = {};
	BinaryStringForNum(240, outputData);

	ASSERT_STR_EQ("11110000", outputData);
	PASS();
}

TEST conv_core_BinaryStringForNum_zero_one_repeating(void)
{
	uint8_t outputData[9] = {};
	BinaryStringForNum(85, outputData);

	ASSERT_STR_EQ("01010101", outputData);
	PASS();
}

TEST conv_core_BinaryStringForNum_one_zero_repeating(void)
{
	uint8_t outputData[9] = {};
	BinaryStringForNum(170, outputData);

	ASSERT_STR_EQ("10101010", outputData);
	PASS();
}


// MARK: FormatBinaryResult

TEST conv_core_FormatBinaryResult_all_zeroes(void)
{
	uint8_t inputData[] = { 0 };
	uint8_t outputData[BINARY_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[BINARY_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatBinaryResult(inputData, 1, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("00000000", outputData);
	ASSERT_STR_EQ("0b00000000", outputDataFormatted);
	PASS();
}

TEST conv_core_FormatBinaryResult_all_ones(void)
{
	uint8_t inputData[] = { 255 };
	uint8_t outputData[BINARY_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[BINARY_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatBinaryResult(inputData, 1, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("11111111", outputData);
	ASSERT_STR_EQ("0b11111111", outputDataFormatted);
	PASS();
}

TEST conv_core_FormatBinaryResult_two_wide(void)
{
	uint8_t inputData[] = { 15, 240 };
	uint8_t outputData[BINARY_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[BINARY_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatBinaryResult(inputData, 2, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("1111000000001111", outputData);
	ASSERT_STR_EQ("0b11110000 00001111", outputDataFormatted);
	PASS();
}

TEST conv_core_FormatBinaryResult_three_wide(void)
{
	uint8_t inputData[] = { 110, 117, 102 };
	uint8_t outputData[BINARY_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[BINARY_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatBinaryResult(inputData, 3, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("011001100111010101101110", outputData);
	ASSERT_STR_EQ("0b01100110 01110101 01101110", outputDataFormatted);
	PASS();
}


// MARK : AddCommasToDecimalResult

TEST conv_core_AddCommasToDecimalResult_one_wide(void)
{
	uint8_t unformattedData[] = "7";
	uint8_t formattedData[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	AddCommasToDecimalResult(unformattedData, formattedData, 1, false);

	ASSERT_STR_EQ("7", formattedData);
	PASS();
}

TEST conv_core_AddCommasToDecimalResult_three_wide(void)
{
	uint8_t unformattedData[] = "123";
	uint8_t formattedData[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	AddCommasToDecimalResult(unformattedData, formattedData, 3, false);

	ASSERT_STR_EQ("123", formattedData);
	PASS();
}

TEST conv_core_AddCommasToDecimalResult_four_wide(void)
{
	uint8_t unformattedData[] = "1234";
	uint8_t formattedData[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	AddCommasToDecimalResult(unformattedData, formattedData, 4, false);

	ASSERT_STR_EQ("1,234", formattedData);
	PASS();
}

TEST conv_core_AddCommasToDecimalResult_six_wide(void)
{
	uint8_t unformattedData[] = "123456";
	uint8_t formattedData[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	AddCommasToDecimalResult(unformattedData, formattedData, 6, false);

	ASSERT_STR_EQ("123,456", formattedData);
	PASS();
}

TEST conv_core_AddCommasToDecimalResult_seven_wide(void)
{
	uint8_t unformattedData[] = "1234567";
	uint8_t formattedData[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	AddCommasToDecimalResult(unformattedData, formattedData, 7, false);

	ASSERT_STR_EQ("1,234,567", formattedData);
	PASS();
}

TEST conv_core_AddCommasToDecimalResult_nine_wide(void)
{
	uint8_t unformattedData[] = "123456789";
	uint8_t formattedData[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	AddCommasToDecimalResult(unformattedData, formattedData, 9, false);

	ASSERT_STR_EQ("123,456,789", formattedData);
	PASS();
}

TEST conv_core_AddCommasToDecimalResult_ten_wide(void)
{
	uint8_t unformattedData[] = "1234567890";
	uint8_t formattedData[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	AddCommasToDecimalResult(unformattedData, formattedData, 10, false);

	ASSERT_STR_EQ("1,234,567,890", formattedData);
	PASS();
}


// MARK: FormatDecimalResult

TEST conv_core_FormatDecimalResult_one_wide(void)
{
	uint8_t inputData[] = { 76 };
	uint8_t outputData[DECIMAL_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatDecimalResult(inputData, 1, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("76", outputData);
	ASSERT_STR_EQ("76", outputDataFormatted);
	PASS();
}

TEST conv_core_FormatDecimalResult_two_wide(void)
{
	uint8_t inputData[] = { 123, 45 };
	uint8_t outputData[DECIMAL_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatDecimalResult(inputData, 2, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("11643", outputData);
	ASSERT_STR_EQ("11,643", outputDataFormatted);
	PASS();
}

TEST conv_core_FormatDecimalResult_three_wide(void)
{
	uint8_t inputData[] = { 86, 52, 18 };
	uint8_t outputData[DECIMAL_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatDecimalResult(inputData, 3, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("1193046", outputData);
	ASSERT_STR_EQ("1,193,046", outputDataFormatted);
	PASS();
}

TEST conv_core_FormatDecimalResult_four_wide(void)
{
	uint8_t inputData[] = { 120, 86, 52, 18 };
	uint8_t outputData[DECIMAL_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatDecimalResult(inputData, 4, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("305419896", outputData);
	ASSERT_STR_EQ("305,419,896", outputDataFormatted);
	PASS();
}

TEST conv_core_FormatDecimalResult_five_wide(void)
{
	uint8_t inputData[] = { 144, 120, 86, 52, 18 };
	uint8_t outputData[DECIMAL_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatDecimalResult(inputData, 5, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("78187493520", outputData);
	ASSERT_STR_EQ("78,187,493,520", outputDataFormatted);
	PASS();
}

// NOTE(Drew): This test exists since this, at one point, returned -1 instead of 4294967295.
// due to an incorrect printf specifier.
TEST conv_core_FormatDecimalResult_uint32_max(void)
{
	uint8_t inputData[] = { 0xFF, 0xFF, 0xFF, 0xFF };
	uint8_t outputData[DECIMAL_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatDecimalResult(inputData, 4, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("4294967295", outputData);
	ASSERT_STR_EQ("4,294,967,295", outputDataFormatted);
	PASS();
}


// MARK: FormatSignedResult

TEST conv_core_FormatSignedResult_zero(void)
{
	uint8_t inputData[] = { 0 };
	uint8_t outputData[DECIMAL_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatSignedResult(inputData, 1, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Invalid, outcomeState, outcome_stateToString);
	PASS();
}

TEST conv_core_FormatSignedResult_not_signed(void)
{
	uint8_t inputData[] = { 76 };
	uint8_t outputData[DECIMAL_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatSignedResult(inputData, 1, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Invalid, outcomeState, outcome_stateToString);
	PASS();
}

TEST conv_core_FormatSignedResult_max_one_wide(void)
{
	uint8_t inputData[] = { 0xFF };
	uint8_t outputData[DECIMAL_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatSignedResult(inputData, 1, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("-1", outputData);
	ASSERT_STR_EQ("-1", outputDataFormatted);
	PASS();
}

TEST conv_core_FormatSignedResult_min_one_wide(void)
{
	uint8_t inputData[] = { 0x80 };
	uint8_t outputData[DECIMAL_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatSignedResult(inputData, 1, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("-128", outputData);
	ASSERT_STR_EQ("-128", outputDataFormatted);
	PASS();
}

TEST conv_core_FormatSignedResult_unsigned_one_wide(void)
{
	uint8_t inputData[] = { 0x01 };
	uint8_t outputData[DECIMAL_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatSignedResult(inputData, 1, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Invalid, outcomeState, outcome_stateToString);
	PASS();
}

TEST conv_core_FormatSignedResult_max_two_wide(void)
{
	uint8_t inputData[] = { 0xFF, 0xFF };
	uint8_t outputData[DECIMAL_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatSignedResult(inputData, 2, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("-1", outputData);
	ASSERT_STR_EQ("-1", outputDataFormatted);
	PASS();
}

TEST conv_core_FormatSignedResult_min_two_wide(void)
{
	uint8_t inputData[] = { 0x00, 0x80 };
	uint8_t outputData[DECIMAL_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatSignedResult(inputData, 2, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("-32768", outputData);
	ASSERT_STR_EQ("-32,768", outputDataFormatted);
	PASS();
}

TEST conv_core_FormatSignedResult_unsigned_two_wide(void)
{
	uint8_t inputData[] = { 0x01, 0x01 };
	uint8_t outputData[DECIMAL_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatSignedResult(inputData, 2, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Invalid, outcomeState, outcome_stateToString);
	PASS();
}

TEST conv_core_FormatSignedResult_three_wide(void)
{
	uint8_t inputData[] = { 0xFF, 0xFF, 0xFF };
	uint8_t outputData[DECIMAL_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatSignedResult(inputData, 3, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Invalid, outcomeState, outcome_stateToString);
	PASS();
}

TEST conv_core_FormatSignedResult_max_four_wide(void)
{
	uint8_t inputData[] = { 0xFF, 0xFF, 0xFF, 0xFF };
	uint8_t outputData[DECIMAL_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatSignedResult(inputData, 4, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("-1", outputData);
	ASSERT_STR_EQ("-1", outputDataFormatted);
	PASS();
}

TEST conv_core_FormatSignedResult_min_four_wide(void)
{
	uint8_t inputData[] = { 0x00, 0x00, 0x00, 0x80 };
	uint8_t outputData[DECIMAL_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatSignedResult(inputData, 4, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("-2147483648", outputData);
	ASSERT_STR_EQ("-2,147,483,648", outputDataFormatted);
	PASS();
}

TEST conv_core_FormatSignedResult_unsigned_four_wide(void)
{
	uint8_t inputData[] = { 0x01, 0x01, 0x01, 0x01 };
	uint8_t outputData[DECIMAL_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatSignedResult(inputData, 4, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Invalid, outcomeState, outcome_stateToString);
	PASS();
}

TEST conv_core_FormatSignedResult_five_wide(void)
{
	uint8_t inputData[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	uint8_t outputData[DECIMAL_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatSignedResult(inputData, 5, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Invalid, outcomeState, outcome_stateToString);
	PASS();
}

TEST conv_core_FormatSignedResult_six_wide(void)
{
	uint8_t inputData[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	uint8_t outputData[DECIMAL_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatSignedResult(inputData, 6, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Invalid, outcomeState, outcome_stateToString);
	PASS();
}

TEST conv_core_FormatSignedResult_seven_wide(void)
{
	uint8_t inputData[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	uint8_t outputData[DECIMAL_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatSignedResult(inputData, 7, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Invalid, outcomeState, outcome_stateToString);
	PASS();
}

TEST conv_core_FormatSignedResult_max_eight_wide(void)
{
	uint8_t inputData[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	uint8_t outputData[DECIMAL_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatSignedResult(inputData, 8, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("-1", outputData);
	ASSERT_STR_EQ("-1", outputDataFormatted);
	PASS();
}

TEST conv_core_FormatSignedResult_min_eight_wide(void)
{
	uint8_t inputData[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80 };
	uint8_t outputData[DECIMAL_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatSignedResult(inputData, 8, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("-9223372036854775808", outputData);
	ASSERT_STR_EQ("-9,223,372,036,854,775,808", outputDataFormatted);
	PASS();
}

TEST conv_core_FormatSignedResult_unsigned_eight_wide(void)
{
	uint8_t inputData[] = { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	uint8_t outputData[DECIMAL_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatSignedResult(inputData, 8, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Invalid, outcomeState, outcome_stateToString);
	PASS();
}

TEST conv_core_FormatSignedResult_leading_negative_at_first_comma(void)
{
	uint8_t inputData[] = { 0x00, 0xFF };
	uint8_t outputData[DECIMAL_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatSignedResult(inputData, 2, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("-256", outputData);
	ASSERT_STR_EQ("-256", outputDataFormatted);
	PASS();
}

TEST conv_core_FormatSignedResult_leading_negative_at_comma(void)
{
	uint8_t inputData[] = { 0xFF, 0xFF, 0xF3, 0xFF };
	uint8_t outputData[DECIMAL_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatSignedResult(inputData, 4, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("-786433", outputData);
	ASSERT_STR_EQ("-786,433", outputDataFormatted);
	PASS();
}


// MARK: HexCharForNum

TEST conv_core_HexCharForNum_int(void)
{
	uint8_t result = 0;
	outcome_state outcomeState = HexCharForNum(5, &result);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT('5', result, "%c");
	PASS();
}

TEST conv_core_HexCharForNum_char(void)
{
	uint8_t result = 0;
	outcome_state outcomeState = HexCharForNum(11, &result);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_EQ_FMT('B', result, "%c");
	PASS();
}

TEST conv_core_HexCharForNum_out_of_range(void)
{
	uint8_t result = 0;
	outcome_state outcomeState = HexCharForNum(16, &result);

	ASSERT_ENUM_EQ(Outcome_Invalid, outcomeState, outcome_stateToString);
	PASS();
}


// MARK: FormatHexResult

TEST conv_core_FormatHexResult_direct(void)
{
	uint8_t inputData[] = { 8 };
	uint8_t outputData[HEX_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[HEX_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatHexResult(inputData, 1, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("08", outputData);
	ASSERT_STR_EQ("0x08", outputDataFormatted);
	PASS();
}

TEST conv_core_FormatHexResult_simple(void)
{
	uint8_t inputData[] = { 254 };
	uint8_t outputData[HEX_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[HEX_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatHexResult(inputData, 1, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("FE", outputData);
	ASSERT_STR_EQ("0xFE", outputDataFormatted);
	PASS();
}

TEST conv_core_FormatHexResult_two_wide(void)
{
	uint8_t inputData[] = { 86, 4 };
	uint8_t outputData[HEX_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[HEX_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatHexResult(inputData, 2, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("0456", outputData);
	ASSERT_STR_EQ("0x0456", outputDataFormatted);
	PASS();
}

TEST conv_core_FormatHexResult_three_wide(void)
{
	uint8_t inputData[] = { 239, 205, 11 };
	uint8_t outputData[HEX_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[HEX_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatHexResult(inputData, 3, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("0BCDEF", outputData);
	ASSERT_STR_EQ("0x0BCDEF", outputDataFormatted);
	PASS();
}

TEST conv_core_FormatHexResult_four_wide(void)
{
	uint8_t inputData[] = { 16, 50, 84, 118 };
	uint8_t outputData[HEX_RESULT_WIDTH] = {};
	uint8_t outputDataFormatted[HEX_RESULT_WIDTH_FORMATTED] = {};
	outcome_state outcomeState = FormatHexResult(inputData, 4, outputData, outputDataFormatted);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("76543210", outputData);
	ASSERT_STR_EQ("0x76543210", outputDataFormatted);
	PASS();
}


// MARK: FormatAsciiResult

TEST conv_core_FormatAsciiResult_not_ascii_byte(void)
{
	uint8_t inputData[] = { 0x10 };
	uint8_t outputData[ASCII_RESULT_WIDTH] = {};
	outcome_state outcomeState = FormatAsciiResult(inputData, 1, outputData);

	ASSERT_ENUM_EQ(Outcome_Invalid, outcomeState, outcome_stateToString);
	PASS();
}

TEST conv_core_FormatAsciiResult_one_wide(void)
{
	uint8_t inputData[] = { 'Z' };
	uint8_t outputData[ASCII_RESULT_WIDTH] = {};
	outcome_state outcomeState = FormatAsciiResult(inputData, 1, outputData);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("\\\"Z\\\"", outputData);
	PASS();
}

TEST conv_core_FormatAsciiResult_four_wide(void)
{
	uint8_t inputData[] = { 'A', 'B', 'C', 'D' };
	uint8_t outputData[ASCII_RESULT_WIDTH] = {};
	outcome_state outcomeState = FormatAsciiResult(inputData, 4, outputData);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("\\\"ABCD\\\"", outputData);
	PASS();
}

TEST conv_core_FormatAsciiResult_quotes(void)
{
	uint8_t inputData[] = { 0x22 };
	uint8_t outputData[ASCII_RESULT_WIDTH] = {};
	outcome_state outcomeState = FormatAsciiResult(inputData, 1, outputData);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("\\\"\\\"\\\"", outputData);
	PASS();
}


// MARK: FormatUTF8Result

TEST conv_core_FormatUTF8Result_not_utf8_byte(void)
{
	uint8_t inputData[] = { 0x10 };
	uint8_t outputData[UTF8_RESULT_WIDTH] = {};
	outcome_state outcomeState = FormatUTF8Result(inputData, 1, outputData);

	ASSERT_ENUM_EQ(Outcome_Invalid, outcomeState, outcome_stateToString);
	PASS();
}

TEST conv_core_FormatUTF8Result_one_wide(void)
{
	uint8_t inputData[] = { 'Z' };
	uint8_t outputData[UTF8_RESULT_WIDTH] = {};
	outcome_state outcomeState = FormatUTF8Result(inputData, 1, outputData);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("\\\"Z\\\"", outputData);
	PASS();
}

TEST conv_core_FormatUTF8Result_two_wide(void)
{
	uint8_t inputData[] = { 0xC2, 0xA9 };
	uint8_t outputData[UTF8_RESULT_WIDTH] = {};
	outcome_state outcomeState = FormatUTF8Result(inputData, 2, outputData);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("\\\"©\\\"", outputData);
	PASS();
}

TEST conv_core_FormatUTF8Result_three_wide(void)
{
	uint8_t inputData[] = { 0xEF, 0xA5, 0x80 };
	uint8_t outputData[UTF8_RESULT_WIDTH] = {};
	outcome_state outcomeState = FormatUTF8Result(inputData, 3, outputData);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("\\\"鹿\\\"", outputData);
	PASS();
}

TEST conv_core_FormatUTF8Result_four_wide(void)
{
	uint8_t inputData[] = { 0xF0, 0x90, 0x8C, 0xB8 };
	uint8_t outputData[UTF8_RESULT_WIDTH] = {};
	outcome_state outcomeState = FormatUTF8Result(inputData, 4, outputData);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("\\\"𐌸\\\"", outputData);
	PASS();
}

TEST conv_core_FormatUTF8Result_multichar(void)
{
	uint8_t inputData[] = { 0xE3, 0x81, 0x93, 0xE3, 0x82, 0x93, 0xE3, 0x81, 0xAB, 0xE3, 0x81, 0xA1, 0xE3, 0x81, 0xAF };
	uint8_t outputData[UTF8_RESULT_WIDTH] = {};
	outcome_state outcomeState = FormatUTF8Result(inputData, 15, outputData);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("\\\"こんにちは\\\"", outputData);
	PASS();
}

TEST conv_core_FormatUTF8Result_quotes(void)
{
	uint8_t inputData[] = { 0x22 };
	uint8_t outputData[UTF8_RESULT_WIDTH] = {};
	outcome_state outcomeState = FormatUTF8Result(inputData, 1, outputData);

	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	ASSERT_STR_EQ("\\\"\\\"\\\"", outputData);
	PASS();
}


// MARK: Suite

SUITE(conv_core)
{
	RUN_TEST(conv_core_BinaryStringForNum_all_zeroes);
	RUN_TEST(conv_core_BinaryStringForNum_all_ones);
	RUN_TEST(conv_core_BinaryStringForNum_half_ones);
	RUN_TEST(conv_core_BinaryStringForNum_zero_one_repeating);
	RUN_TEST(conv_core_BinaryStringForNum_one_zero_repeating);

	RUN_TEST(conv_core_FormatBinaryResult_all_zeroes);
	RUN_TEST(conv_core_FormatBinaryResult_all_ones);
	RUN_TEST(conv_core_FormatBinaryResult_two_wide);
	RUN_TEST(conv_core_FormatBinaryResult_three_wide);

	RUN_TEST(conv_core_AddCommasToDecimalResult_one_wide);
	RUN_TEST(conv_core_AddCommasToDecimalResult_three_wide);
	RUN_TEST(conv_core_AddCommasToDecimalResult_four_wide);
	RUN_TEST(conv_core_AddCommasToDecimalResult_six_wide);
	RUN_TEST(conv_core_AddCommasToDecimalResult_seven_wide);
	RUN_TEST(conv_core_AddCommasToDecimalResult_nine_wide);
	RUN_TEST(conv_core_AddCommasToDecimalResult_ten_wide);

	RUN_TEST(conv_core_FormatDecimalResult_one_wide);
	RUN_TEST(conv_core_FormatDecimalResult_two_wide);
	RUN_TEST(conv_core_FormatDecimalResult_three_wide);
	RUN_TEST(conv_core_FormatDecimalResult_four_wide);
	RUN_TEST(conv_core_FormatDecimalResult_five_wide);
	RUN_TEST(conv_core_FormatDecimalResult_uint32_max);

	RUN_TEST(conv_core_FormatSignedResult_zero);
	RUN_TEST(conv_core_FormatSignedResult_not_signed);
	RUN_TEST(conv_core_FormatSignedResult_max_one_wide);
	RUN_TEST(conv_core_FormatSignedResult_min_one_wide);
	RUN_TEST(conv_core_FormatSignedResult_unsigned_one_wide);
	RUN_TEST(conv_core_FormatSignedResult_max_two_wide);
	RUN_TEST(conv_core_FormatSignedResult_min_two_wide);
	RUN_TEST(conv_core_FormatSignedResult_unsigned_two_wide);
	RUN_TEST(conv_core_FormatSignedResult_three_wide);
	RUN_TEST(conv_core_FormatSignedResult_max_four_wide);
	RUN_TEST(conv_core_FormatSignedResult_min_four_wide);
	RUN_TEST(conv_core_FormatSignedResult_unsigned_four_wide);
	RUN_TEST(conv_core_FormatSignedResult_five_wide);
	RUN_TEST(conv_core_FormatSignedResult_six_wide);
	RUN_TEST(conv_core_FormatSignedResult_seven_wide);
	RUN_TEST(conv_core_FormatSignedResult_max_eight_wide);
	RUN_TEST(conv_core_FormatSignedResult_min_eight_wide);
	RUN_TEST(conv_core_FormatSignedResult_unsigned_eight_wide);
	RUN_TEST(conv_core_FormatSignedResult_leading_negative_at_first_comma);
	RUN_TEST(conv_core_FormatSignedResult_leading_negative_at_comma);

	RUN_TEST(conv_core_HexCharForNum_int);
	RUN_TEST(conv_core_HexCharForNum_char);
	RUN_TEST(conv_core_HexCharForNum_out_of_range);

	RUN_TEST(conv_core_FormatAsciiResult_not_ascii_byte);
	RUN_TEST(conv_core_FormatAsciiResult_one_wide);
	RUN_TEST(conv_core_FormatAsciiResult_four_wide);
	RUN_TEST(conv_core_FormatAsciiResult_quotes);

	RUN_TEST(conv_core_FormatUTF8Result_not_utf8_byte);
	RUN_TEST(conv_core_FormatUTF8Result_one_wide);
	RUN_TEST(conv_core_FormatUTF8Result_two_wide);
	RUN_TEST(conv_core_FormatUTF8Result_three_wide);
	RUN_TEST(conv_core_FormatUTF8Result_four_wide);
	RUN_TEST(conv_core_FormatUTF8Result_multichar);
	RUN_TEST(conv_core_FormatUTF8Result_quotes);

	RUN_TEST(conv_core_FormatHexResult_direct);
	RUN_TEST(conv_core_FormatHexResult_simple);
	RUN_TEST(conv_core_FormatHexResult_two_wide);
	RUN_TEST(conv_core_FormatHexResult_three_wide);
	RUN_TEST(conv_core_FormatHexResult_four_wide);
}
