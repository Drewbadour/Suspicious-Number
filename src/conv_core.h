
#ifndef ALFREDWORKFLOW_CONV_H
#define ALFREDWORKFLOW_CONV_H

#include "alfredworkflow_io.h"

#define MAX_BYTES 256
#define MEMORY_BYTES 16384 + 1

// One char for each bit, with the number of bytes for spaces-between-bytes including null terminator.
#define BINARY_RESULT_WIDTH_FORMATTED (MAX_BYTES * 9 + 3)
#define BINARY_RESULT_WIDTH (MAX_BYTES + 3)
#define BINARY_TITLE "Binary"
#define BINARY_UID "bin"
#define BINARY_PREFIX "0b"

// A super rough over-calculation, better to be safe than sorry.
#define DECIMAL_RESULT_WIDTH_FORMATTED (MAX_BYTES * 8)
#define DECIMAL_RESULT_WIDTH (MAX_BYTES * 8)
#define DECIMAL_TITLE "Unsigned Decimal"
#define DECIMAL_UID "dec"

#define SIGNED_RESULT_WIDTH_FORMATTED (MAX_BYTES * 8)
#define SIGNED_RESULT_WIDTH (MAX_BYTES * 8)
#define SIGNED_TITLE "Signed Decimal"
#define SIGNED_UID "sign"

// +3 is +2 for 0x and +1 for termination.
#define HEX_RESULT_WIDTH_FORMATTED (MAX_BYTES * 2 + 3)
#define HEX_RESULT_WIDTH (MAX_BYTES * 2 + 1)
#define HEX_TITLE "Hexademical"
#define HEX_UID "hex"
#define HEX_PREFIX "0x"

// One char per byte + quotes
#define ASCII_RESULT_WIDTH (MAX_BYTES + 3)
#define ASCII_TITLE "ASCII String"
#define ASCII_UID "ascii"

// Length + quotes
#define UTF8_RESULT_WIDTH (MAX_BYTES + 3)
#define UTF8_TITLE "UTF-8 String"
#define UTF8_UID "utf8"

#define UINT8_ARR_RESULT_WIDTH_FORMATTED (MAX_BYTES * 8)
#define UINT8_ARR_RESULT_WIDTH (MAX_BYTES * 8)
#define UINT8_ARR_TITLE "uint8_t Array"
#define UINT8_ARR_UID "u8_arr"

#define AssertValid(x) if ((x) != Outcome_Valid) { PrintFailure((x)); return (int)(x); }


// Input data comes in LSB first!
// Output data (and all string numbers) go MSB first!


void BinaryStringForNum(uint8_t num, uint8_t* result)
{
	for (uint_fast8_t index = 0; index < 8; ++index)
	{
		bool isOne = num & 128;
		if (isOne)
		{
			result[index] = '1';
		}
		else
		{
			result[index] = '0';
		}
		num <<= 1;
	}
}

outcome_state FormatBinaryResult(uint8_t* inputData, uint32_t inputDataCount, uint8_t* outputData, uint8_t* outputDataFormatted)
{
	if (inputDataCount == 0)
	{
		return Outcome_Invalid;
	}

	CopyMemory(outputDataFormatted, "0b", 2);
	outputDataFormatted += 2;

	for (uint32_t inputIndex = inputDataCount; __builtin_sub_overflow(inputIndex, 1, &inputIndex) == false;)
	{
		uint8_t binaryChunk[10] = {};
		binaryChunk[8] = ' ';
		BinaryStringForNum(inputData[inputIndex], binaryChunk);

		CopyMemory(outputData, binaryChunk, 8);
		CopyMemory(outputDataFormatted, binaryChunk, 9);

		outputData += 8;
		outputDataFormatted += 9;
	}

	*(outputDataFormatted - 1) = '\0';

	return Outcome_Valid;
}


void AddCommasToDecimalResult(uint8_t* outputData, uint8_t* outputDataFormatted, int length)
{
	while (length > 0)
	{
		uint_fast8_t mod = length % 3;
		uint_fast8_t copyCount = 0;

		if (__builtin_expect(mod == 0, 1))
		{
			copyCount = 3;
		}
		else
		{
			copyCount = mod;
		}

		CopyMemory(outputDataFormatted, outputData, copyCount);
		outputData += copyCount;
		outputDataFormatted += copyCount;
		length -= copyCount;

		if (length > 0)
		{
			CopyMemory(outputDataFormatted, ",", 1);
			++outputDataFormatted;
		}
	}
}

outcome_state FormatDecimalResult(uint8_t* inputData, uint32_t inputDataCount, uint8_t* outputData, uint8_t* outputDataFormatted)
{
	if (inputDataCount == 0)
	{
		return Outcome_Empty;
	}
	else if (inputDataCount == 1)
	{
		uint8_t rawData = 0;
		CopyMemory(&rawData, inputData, inputDataCount);

		int length = snprintf((char*)outputData, DECIMAL_RESULT_WIDTH, "%u", rawData);
		if (length < 0)
		{
			return Outcome_Invalid;
		}

		// Impossible to have a comma, so it's the same.
		CopyMemory(outputDataFormatted, outputData, length);
	}
	else if (inputDataCount == 2)
	{
		uint16_t rawData = 0;
		CopyMemory(&rawData, inputData, inputDataCount);

		int length = snprintf((char*)outputData, DECIMAL_RESULT_WIDTH, "%u", rawData);
		if (length < 0)
		{
			return Outcome_Invalid;
		}

		AddCommasToDecimalResult(outputData, outputDataFormatted, length);
	}
	else if (inputDataCount <= 4)
	{
		uint32_t rawData = 0;
		CopyMemory(&rawData, inputData, inputDataCount);

		int length = snprintf((char*)outputData, DECIMAL_RESULT_WIDTH, "%u", rawData);
		if (length < 0)
		{
			return Outcome_Invalid;
		}
		AddCommasToDecimalResult(outputData, outputDataFormatted, length);
	}
	else if (inputDataCount <= 8)
	{
		uint64_t rawData = 0;
		CopyMemory(&rawData, inputData, inputDataCount);

		int length = snprintf((char*)outputData, DECIMAL_RESULT_WIDTH, "%llu", rawData);
		if (length < 0)
		{
			return Outcome_Invalid;
		}
		AddCommasToDecimalResult(outputData, outputDataFormatted, length);
	}
	else
	{
		return Outcome_Invalid;
	}

	return Outcome_Valid;
}

outcome_state FormatSignedResult(uint8_t* inputData, uint32_t inputDataCount, uint8_t* outputData, uint8_t* outputDataFormatted)
{
	if (inputDataCount == 0)
	{
		return Outcome_Empty;
	}
	else if ((inputDataCount == 1) && (inputData[0] & 0x80))
	{
		int8_t rawData = 0;
		CopyMemory(&rawData, inputData, inputDataCount);

		int length = snprintf((char*)outputData, DECIMAL_RESULT_WIDTH, "%d", rawData);
		if (length < 0)
		{
			return Outcome_Invalid;
		}

		// Impossible to have a comma, so it's the same.
		CopyMemory(outputDataFormatted, outputData, length);
	}
	else if ((inputDataCount == 2) && (inputData[1] & 0x80))
	{
		int16_t rawData = 0;
		CopyMemory(&rawData, inputData, inputDataCount);

		int length = snprintf((char*)outputData, DECIMAL_RESULT_WIDTH, "%d", rawData);
		if (length < 0)
		{
			return Outcome_Invalid;
		}

		AddCommasToDecimalResult(outputData, outputDataFormatted, length);
	}
	else if ((inputDataCount == 4) && (inputData[3] & 0x80))
	{
		int32_t rawData = 0;
		CopyMemory(&rawData, inputData, inputDataCount);

		int length = snprintf((char*)outputData, DECIMAL_RESULT_WIDTH, "%d", rawData);
		if (length < 0)
		{
			return Outcome_Invalid;
		}
		AddCommasToDecimalResult(outputData, outputDataFormatted, length);
	}
	else if ((inputDataCount == 8) && (inputData[7] & 0x80))
	{
		int64_t rawData = 0;
		CopyMemory(&rawData, inputData, inputDataCount);

		int length = snprintf((char*)outputData, DECIMAL_RESULT_WIDTH, "%lld", rawData);
		if (length < 0)
		{
			return Outcome_Invalid;
		}
		AddCommasToDecimalResult(outputData, outputDataFormatted, length);
	}
	else
	{
		return Outcome_Invalid;
	}

	return Outcome_Valid;
}



outcome_state HexCharForNum(uint8_t num, uint8_t* result)
{
	if (num <= 9)
	{
		*result = '0' + num;
		return Outcome_Valid;
	}
	else if (num <= 15)
	{
		*result = 'A' + (num - 10);
		return Outcome_Valid;
	}

	return Outcome_Invalid;
}

outcome_state FormatHexResult(uint8_t* inputData, uint32_t inputDataCount, uint8_t* outputData, uint8_t* outputDataFormatted)
{
	uint32_t inputIndex = 0;
	for (; inputIndex < inputDataCount; ++inputIndex)
	{
		outcome_state outcomeState = Outcome_Valid;
		uint8_t leastSignificantChar = 0;
		uint8_t mostSignificantChar = 0;

		uint32_t outputIndex = 0;
		if (__builtin_sub_overflow(inputDataCount, inputIndex, &outputIndex))
		{
			return Outcome_Overflow;
		}
		if (__builtin_sub_overflow(outputIndex, 1, &outputIndex))
		{
			return Outcome_Overflow;
		}
		if (__builtin_mul_overflow(outputIndex, 2, &outputIndex))
		{
			return Outcome_Overflow;
		}

		outcomeState = HexCharForNum(inputData[inputIndex] % 16, &leastSignificantChar);
		if (outcomeState != Outcome_Valid)
		{
			return outcomeState;
		}

		outcomeState = HexCharForNum(inputData[inputIndex] / 16, &mostSignificantChar);
		if (outcomeState != Outcome_Valid)
		{
			return outcomeState;
		}

		outputData[outputIndex] = mostSignificantChar;
		outputData[outputIndex + 1] = leastSignificantChar;
	}

	size_t prefixSize = sizeof(HEX_PREFIX) - 1;
	CopyMemory(outputDataFormatted, HEX_PREFIX, prefixSize);
	CopyMemory(outputDataFormatted + prefixSize, outputData, inputIndex * 2);

	return Outcome_Valid;
}

outcome_state FormatAsciiResult(uint8_t* inputData, uint32_t inputDataCount, uint8_t* outputData)
{
	uint32_t outputIndex = 2;
	outputData[0] = '\\';
	outputData[1] = '"';

	for (uint32_t inputIndex = 0; inputIndex < inputDataCount; ++inputIndex, ++outputIndex)
	{
		if ((inputData[inputIndex] >= ' ') && (inputData[inputIndex] <= '~'))
		{
			outputData[outputIndex] = inputData[inputIndex];
		}
		else
		{
			return Outcome_Invalid;
		}
	}

	outputData[outputIndex] = '\\';
	outputData[outputIndex + 1] = '"';
	outputData[outputIndex + 2] = '\0';
	return Outcome_Valid;
}

outcome_state FormatUTF8Result(uint8_t* inputData, uint32_t inputDataCount, uint8_t* outputData)
{
	uint32_t outputIndex = 2;
	outputData[0] = '\\';
	outputData[1] = '"';

	for (uint32_t inputIndex = 0; inputIndex < inputDataCount;)
	{
		if ((inputData[inputIndex] >= ' ') && (inputData[inputIndex] <= '~'))
		{
			CopyMemory(outputData + outputIndex, inputData + inputIndex, 1);
			outputIndex += 1;
			inputIndex += 1;
		}
		else if ((inputData[inputIndex] & 0xE0) == 0xC0)
		{
			if ((inputData[inputIndex + 1] & 0xC0) != 0x80)
			{
				return Outcome_Invalid;
			}

			CopyMemory(outputData + outputIndex, inputData + inputIndex, 2);
			outputIndex += 2;
			inputIndex += 2;
		}
		else if ((inputData[inputIndex] & 0xF0) == 0xE0)
		{
			if (((inputData[inputIndex + 1] & 0xC0) != 0x80) ||
				((inputData[inputIndex + 2] & 0xC0) != 0x80))
			{
				return Outcome_Invalid;
			}

			CopyMemory(outputData + outputIndex, inputData + inputIndex, 3);
			outputIndex += 3;
			inputIndex += 3;
		}
		else if ((inputData[inputIndex] & 0xF8) == 0xF0)
		{
			if (((inputData[inputIndex + 1] & 0xC0) != 0x80) ||
				((inputData[inputIndex + 2] & 0xC0) != 0x80) ||
				((inputData[inputIndex + 3] & 0xC0) != 0x80))
			{
				return Outcome_Invalid;
			}

			CopyMemory(outputData + outputIndex, inputData + inputIndex, 4);
			outputIndex += 4;
			inputIndex += 4;
		}
		else
		{
			return Outcome_Invalid;
		}
	}

	outputData[outputIndex] = '\\';
	outputData[outputIndex + 1] = '"';
	outputData[outputIndex + 2] = '\0';
	return Outcome_Valid;
}

outcome_state FormatAndPrintOutputs(uint8_t* parsedInput, uint32_t parsedNumBytes)
{
	outcome_state outcomeState = Outcome_Valid;
	// NOTE(Drew): We can have one less here since it's impossible to have signed AND ASCII.
	alfred_response responses[5] = {};
	uint32_t numResponses = 0;

	uint8_t binaryUnformatted[BINARY_RESULT_WIDTH] = {};
	uint8_t binaryFormatted[BINARY_RESULT_WIDTH_FORMATTED] = {};
	outcomeState = FormatBinaryResult(parsedInput, parsedNumBytes, binaryUnformatted, binaryFormatted);
	if (outcomeState == Outcome_Valid)
	{
		responses[numResponses].title = (char*)binaryFormatted;
		responses[numResponses].subtitle = BINARY_TITLE;
		responses[numResponses].uid = BINARY_UID;
		responses[numResponses].arg = (char*)binaryUnformatted;
		responses[numResponses].valid = true;
		++numResponses;
	}

	uint8_t decimalUnformatted[DECIMAL_RESULT_WIDTH] = {};
	uint8_t decimalFormatted[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	outcomeState = FormatDecimalResult(parsedInput, parsedNumBytes, decimalUnformatted, decimalFormatted);
	if (outcomeState == Outcome_Valid)
	{
		responses[numResponses].title = (char*)decimalFormatted;
		responses[numResponses].subtitle = DECIMAL_TITLE;
		responses[numResponses].uid = DECIMAL_UID;
		responses[numResponses].arg = (char*)decimalUnformatted;
		responses[numResponses].valid = true;
		++numResponses;
	}

	uint8_t signedUnformatted[DECIMAL_RESULT_WIDTH] = {};
	uint8_t signedFormatted[DECIMAL_RESULT_WIDTH_FORMATTED] = {};
	outcomeState = FormatSignedResult(parsedInput, parsedNumBytes, signedUnformatted, signedFormatted);
	if (outcomeState == Outcome_Valid)
	{
		responses[numResponses].title = (char*)signedFormatted;
		responses[numResponses].subtitle = SIGNED_TITLE;
		responses[numResponses].uid = SIGNED_UID;
		responses[numResponses].arg = (char*)signedUnformatted;
		responses[numResponses].valid = true;
		++numResponses;
	}

	uint8_t hexUnformatted[HEX_RESULT_WIDTH] = {};
	uint8_t hexFormatted[HEX_RESULT_WIDTH_FORMATTED] = {};
	outcomeState = FormatHexResult(parsedInput, parsedNumBytes, hexUnformatted, hexFormatted);
	if (outcomeState == Outcome_Valid)
	{
		responses[numResponses].title = (char*)hexFormatted;
		responses[numResponses].subtitle = HEX_TITLE;
		responses[numResponses].uid = HEX_UID;
		responses[numResponses].arg = (char*)hexUnformatted;
		responses[numResponses].valid = true;
		++numResponses;
	}

	uint8_t asciiString[ASCII_RESULT_WIDTH] = {};
	outcomeState = FormatAsciiResult(parsedInput, parsedNumBytes, asciiString);
	if (outcomeState == Outcome_Valid)
	{
		responses[numResponses].title = (char*)asciiString;
		responses[numResponses].subtitle = ASCII_TITLE;
		responses[numResponses].uid = ASCII_UID;
		responses[numResponses].arg = (char*)asciiString;
		responses[numResponses].valid = true;
		++numResponses;
	}

	uint8_t utf8String[UTF8_RESULT_WIDTH] = {};
	outcomeState = FormatUTF8Result(parsedInput, parsedNumBytes, utf8String);
	if (outcomeState == Outcome_Valid)
	{
		responses[numResponses].title = (char*)utf8String;
		responses[numResponses].subtitle = UTF8_TITLE;
		responses[numResponses].uid = UTF8_UID;
		responses[numResponses].arg = (char*)utf8String;
		responses[numResponses].valid = true;
		++numResponses;
	}

#if 0
	uint8_t uint8ArrUnformatted[HEX_RESULT_WIDTH] = {};
	uint8_t hexFormatted[HEX_RESULT_WIDTH_FORMATTED] = {};
	outcomeState = FormatHexResult(parsedInput, parsedNumBytes, hexUnformatted, hexFormatted);
	if (outcomeState == Outcome_Valid)
	{
		responses[numResponses].title = (char*)hexFormatted;
		responses[numResponses].subtitle = HEX_TITLE;
		responses[numResponses].uid = HEX_UID;
		responses[numResponses].arg = (char*)hexUnformatted;
		responses[numResponses].valid = true;
		++numResponses;
	}
#endif

	PrintRequest(responses, numResponses);

	return outcomeState;
}

#endif // ALFREDWORKFLOW_CONV_H
