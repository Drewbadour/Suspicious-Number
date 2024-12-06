
#ifndef ALFREDWORKFLOW_PLATFORM_H
#define ALFREDWORKFLOW_PLATFORM_H

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


#ifdef __SIZEOF_INT128__
typedef __int128_t int128_t;
typedef __uint128_t uint128_t;
#else
// #warning "Please build with gcc that supports __uint128_t and __int128_t. Using uint64_t instead."
typedef uint64_t uint128_t;
#endif


#if RELEASE == 1
	#define Assert(expression)
	#define AssertString(expression)
#else
	#define Assert(expression) \
		_Pragma("GCC diagnostic push") \
		_Pragma("GCC diagnostic ignored \"-Wnull-dereference\"") \
		if(!(expression)) {*(int*)0 = 0;} \
		_Pragma("GCC diagnostic pop")

	#define AssertString(expression) \
		fprintf(stderr, expression); \
		Assert(!expression)


#endif

#if DEBUG == 1
	#define DebugLog(...) \
		fprintf(stdout, __VA_ARGS__)
	#define DebugVar(name, value, specifier) \
		fprintf(stdout, name " = " specifier "\n", value)
	#define DebugInt(variable) DebugVar(#variable, variable, "%d")
	#define DebugChar(variable) DebugVar(#variable, variable, "%c")
	#define DebugString(variable) DebugVar(#variable, variable, "%s")
	#define DebugPointer(variable) DebugVar(#variable, variable, "%p")
#else
	#define DebugLog(...)
	#define DebugInt(variable)
	#define DebugChar(variable)
	#define DebugString(variable)
	#define DebugPointer(variable)
#endif


#define Min(a,b) ((a) < (b) ? (a) : (b))
#define Max(a,b) ((a) > (b) ? (a) : (b))


uint32_t QuickPow(uint32_t base, uint32_t exponent)
{
	uint32_t result = 1;

	switch (exponent)
	{
		case 3:
			result *= base;
			// Intentional fall-through
		case 2:
			base *= base;
			// Intentional fall-through
		case 1:
			result *= base;
			// Intentional fall-through
		case 0:
			return result;
		default:
			return 0;
	}
}


void CopyMemory(void* destination, void* source, unsigned int count)
{
	for (; count > 0; --count)
	{
		*(uint8_t*)destination++ = *(uint8_t*)source++;
	}
}

bool CompareMemory(const void* a, const void* b, unsigned int count)
{
	bool result = true;

	for (unsigned int index = 0; index < count; ++index)
	{
		result &= (((uint8_t*)a)[index] == ((uint8_t*)b)[index]);
	}

	return result;
}

// bool CompareToConstSubstring(const void* a, const char* b, uint32_t* numMatch)
// {
// 	bool result = true;
// 	unsigned int index = 0;

// 	if (((char*)a)[0] == 0)
// 	{
// 		return false;
// 	}

// 	while ((((char*)a)[index] != 0) && (b[index] != 0) && result)
// 	{
// 		result &= (((uint8_t*)a)[index] == ((uint8_t*)b)[index]);
// 		++index;
// 	}

// 	*numMatch = index;
// 	return result;
// }

bool CompareToConstString(const void* a, const char* b)
{
	bool result = true;

	for (unsigned int index = 0; b[index] != 0; ++index)
	{
		result &= (((uint8_t*)a)[index] == ((uint8_t*)b)[index]);
	}

	return result;
}

void CopyConstString(void* void_dest, const char* source, unsigned int max)
{
	uint8_t* dest = (uint8_t*)void_dest;
	const char* maxPtr = source + max;
	for (; source < maxPtr;)
	{
		*dest++ = *source++;
	}
}

uint32_t StringLength(const void* void_source, uint32_t maxLength)
{
	uint32_t length = 0;
	uint8_t* source = (uint8_t*)void_source;

	for (length = 0; length < maxLength; ++length, ++source)
	{
		if (!*source)
		{
			break;
		}
	}

	return length;
}

#endif // ALFREDWORKFLOW_PLATFORM_H
