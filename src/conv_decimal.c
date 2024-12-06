
#if TESTING != 1
	#define FORMAT_HELP_TITLE "Convert decimal number"
	#define FORMAT_HELP_SUBTITLE "Try typing something like '9' or '1337' to see its equivalents in other number systems."
	#define FORMAT_ERROR_TITLE "Invalid decimal number"
	#define FORMAT_ERROR_SUBTITLE "Valid decimal numbers contain only numbers."
	#define FORMAT_OVERFLOW_TITLE "Decimal number too large"
	#define FORMAT_OVERFLOW_SUBTITLE "Program does not support decimal numbers of this size. Please contact the developer with your concerns if you believe this is an error."
#endif

#include "alfredworkflow_platform.h"
#include "alfredworkflow_output_formatting.h"
#include "conv_core.h"

#define LLONG_MAX  9223372036854775807LL
#include <errno.h>
#include <stdlib.h>


outcome_state ParseDecimal(const char* inputString, uint32_t maxDataCount, uint8_t* outputData, uint32_t* outputNumBytes)
{
	uint8_t* cleanData = outputData;
	{
		uint32_t cleanIndex = 0;
		for (uint32_t sourceIndex = 0; cleanIndex < maxDataCount; ++sourceIndex)
		{
			uint8_t observingChar = inputString[sourceIndex];
			if (observingChar == 0)
			{
				break;
			}
			else if (observingChar == ',')
			{
				continue;
			}

			cleanData[cleanIndex] = inputString[sourceIndex];
			++cleanIndex;
		}
		cleanData[cleanIndex] = 0;
	}

	int128_t resultNumber = strtoll((char*)cleanData, NULL, 10);
	if ((resultNumber == LLONG_MAX) && (errno == ERANGE))
	{
		errno = 0;
		resultNumber = strtoull((char*)cleanData, NULL, 10);
	}
	if (errno == EINVAL || errno == ERANGE)
	{
		return Outcome_Invalid;
	}


	uint8_t* resultPtr = (uint8_t*)(&resultNumber);
	int32_t lastSeenNumber = 0;
	if (resultNumber > 0)
	{
		for (uint32_t testLength = 0; testLength < sizeof(resultNumber); ++testLength)
		{
			if (resultPtr[testLength] != 0)
			{
				// NOTE(Drew): lastSeenNumber is one-indexed for convenience
				lastSeenNumber = testLength + 1;
			}
		}

		*outputNumBytes = lastSeenNumber;
		CopyMemory(outputData, resultPtr, lastSeenNumber);
		return Outcome_Valid;
	}
	else if (resultNumber < 0)
	{
		for (uint32_t testLength = 0; testLength < sizeof(resultNumber); ++testLength)
		{
			if (resultPtr[testLength] != 0b11111111)
			{
				// NOTE(Drew): lastSeenNumber is one-indexed for convenience
				lastSeenNumber = testLength + 1;
			}
		}

		if (lastSeenNumber == 1)
		{
			*outputNumBytes = 1;
			int8_t smallestPossibleContainer = (int8_t)resultNumber;
			CopyMemory(outputData, &smallestPossibleContainer, 1);
			return Outcome_Valid;
		}
		else if (lastSeenNumber == 2)
		{
			*outputNumBytes = 2;
			int16_t smallestPossibleContainer = (int16_t)resultNumber;
			CopyMemory(outputData, &smallestPossibleContainer, 2);
			return Outcome_Valid;
		}
		else if (lastSeenNumber <= 4)
		{
			*outputNumBytes = 4;
			int32_t smallestPossibleContainer = (int32_t)resultNumber;
			CopyMemory(outputData, &smallestPossibleContainer, 4);
			return Outcome_Valid;
		}
		else if (lastSeenNumber <= 8)
		{
			*outputNumBytes = 8;
			int64_t smallestPossibleContainer = (int64_t)resultNumber;
			CopyMemory(outputData, &smallestPossibleContainer, 8);
			return Outcome_Valid;
		}
		else if (lastSeenNumber <= 16)
		{
			*outputNumBytes = 16;
			int128_t smallestPossibleContainer = (int128_t)resultNumber;
			CopyMemory(outputData, &smallestPossibleContainer, 16);
			return Outcome_Valid;
		}
		else
		{
			return Outcome_Overflow;
		}
	}
	else // resultNumber == 0
	{
		*outputData = 0;
		*outputNumBytes = 1;
		return Outcome_Valid;
	}
}

int DecimalMain(int argc, char** argv)
{
	outcome_state outcomeState = Outcome_Valid;

	outcomeState = CheckNumArgs(argc);
	AssertValid(outcomeState);

	uint8_t parsedInput[MAX_BYTES] = {};
	uint32_t parsedNumBytes = 0;
	outcomeState = ParseDecimal(argv[1], MAX_BYTES, parsedInput, &parsedNumBytes);
	AssertValid(outcomeState);

	outcomeState = FormatAndPrintOutputs(parsedInput, parsedNumBytes);
	return outcomeState;
}

#if TESTING != 1
int main(int argc, char** argv)
{
	return DecimalMain(argc, argv);
}
#endif
