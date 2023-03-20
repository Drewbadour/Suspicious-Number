
#if TESTING != 1
	#define FORMAT_HELP_TITLE "Convert hexadecimal number"
	#define FORMAT_HELP_SUBTITLE "Try typing something like '0x12' or 'ab' to see its equivalents in other number systems."
	#define FORMAT_ERROR_TITLE "Invalid hexadecimal number"
	#define FORMAT_ERROR_SUBTITLE "Valid hex numbers can start with '0x' and contain only numbers and letters A through F."
	#define FORMAT_OVERFLOW_TITLE "Hexadecimal number too large"
	#define FORMAT_OVERFLOW_SUBTITLE "Program does not support hexadecimal numbers of this size. Please contact the developer with your concerns if you believe this is an error."
#endif

#include "alfredworkflow_platform.h"
#include "alfredworkflow_output_formatting.h"
#include "conv_core.h"

outcome_state HexCharToNum(uint8_t input, uint8_t* result)
{
	if (input < '0')
	{
		return Outcome_Invalid;
	}
	else if (input <= '9')
	{
		*result = input - '0';
	}
	else if (input < 'A')
	{
		return Outcome_Invalid;
	}
	else if (input <= 'F')
	{
		*result = input - ('A' - 10);
	}
	else if (input < 'a')
	{
		return Outcome_Invalid;
	}
	else if (input <= 'f')
	{
		*result = input - ('a' - 10);
	}
	else
	{
		return Outcome_Invalid;
	}

	return Outcome_Valid;
}

outcome_state ParseHex(char* inputString, uint32_t maxDataCount, uint8_t* outputData, uint32_t* outputNumBytes)
{
	*outputNumBytes = 0;

	if (CompareToConstString(inputString, HEX_PREFIX))
	{
		inputString += 2;
		if (__builtin_sub_overflow(maxDataCount, 2, &maxDataCount))
		{
			// NOTE(Drew): If maxDataCount is <= 2, then there's probably something very wrong
			return Outcome_Overflow;
		}
	}

	uint32_t inputLength = StringLength(inputString, maxDataCount);
	if (inputLength >= maxDataCount)
	{
		return Outcome_Overflow;
	}
	else if (inputLength == 0)
	{
		return Outcome_Empty;
	}

	uint32_t outputIndex = 0;
	for (uint32_t index = 0, inputIndex = inputLength; inputIndex > 0; --inputIndex, ++index)
	{
		outputIndex = (inputIndex - 1) / 2;
		uint8_t resultStorage = 0;
		outcome_state outcomeState = Outcome_Valid;

		outcomeState = HexCharToNum(inputString[index], &resultStorage);

		if (outcomeState != Outcome_Valid)
		{
			*outputNumBytes = 0;
			return outcomeState;
		}

		if ((inputIndex % 2) == 0)
		{
			resultStorage <<= 4;
		}

		outputData[outputIndex] |= resultStorage;
	}

	for (uint32_t index = 0; index < (inputLength + 1) / 2; ++index)
	{
		if (outputData[index] != 0)
		{
			// NOTE(Drew): lastSeenNumber is one-indexed for convenience
			*outputNumBytes = index + 1;
		}
	}

	if (*outputNumBytes == 0)
	{
		// NOTE(Drew): User just entered a "0"
		*outputNumBytes = 1;
		outputData[0] = 0;
	}

	return Outcome_Valid;
}

int HexMain(int argc, char** argv)
{
	outcome_state outcomeState = Outcome_Valid;

	outcomeState = CheckNumArgs(argc);
	AssertValid(outcomeState);

	uint32_t parsedNumBytes = 0;
	uint8_t parsedInput[MAX_BYTES] = {};
	outcomeState = ParseHex(argv[1], MAX_BYTES, parsedInput, &parsedNumBytes);
	AssertValid(outcomeState);

	outcomeState = FormatAndPrintOutputs(parsedInput, parsedNumBytes);
	return outcomeState;
}

#if TESTING != 1
int main(int argc, char** argv)
{
	return HexMain(argc, argv);
}
#endif
