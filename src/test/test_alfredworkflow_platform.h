#if 0
void AlfredWorkflow_CompareToConstSubstringTests(void)
{
	fprintf(stdout, "CompareToConstSubstring() Tests:\n");
	{
		uint32_t matchLength = 0;
		if (CompareToConstSubstring("", "0x", &matchLength) != false)
		{
			AssertString("CompareToConstSubstring should have returned false for empty string.\n");
		}
	}
	{
		uint32_t matchLength = 0;
		if (CompareToConstSubstring("z", "0x", &matchLength) != false)
		{
			AssertString("CompareToConstSubstring should have returned false for non-match string.\n");
		}
	}
	{
		uint32_t matchLength = 0;
		if (CompareToConstSubstring("0", "0x", &matchLength) != true)
		{
			AssertString("CompareToConstSubstring should have returned true for single character substring match.\n");
		}
		if (matchLength != 1)
		{
			DebugInt(matchLength);
			AssertString("CompareToConstSubstring should have returned matchLength of 1 for single character substring match.\n");
		}
	}
	{
		uint32_t matchLength = 0;
		if (CompareToConstSubstring("0x", "0x", &matchLength) != true)
		{
			AssertString("CompareToConstSubstring should have returned true for two character substring match.\n");
		}
		if (matchLength != 2)
		{
			DebugInt(matchLength);
			AssertString("CompareToConstSubstring should have returned matchLength of 2 for two character substring match.\n");
		}
	}
	{
		uint32_t matchLength = 0;
		if (CompareToConstSubstring("0x1234", "0x", &matchLength) != true)
		{
			AssertString("CompareToConstSubstring should have returned true for leading substring match.\n");
		}
		if (matchLength != 2)
		{
			DebugInt(matchLength);
			AssertString("CompareToConstSubstring should have returned matchLength of 2 for leading substring match.\n");
		}
	}
	fprintf(stdout, "Done.\n\n");
}

TEST alfredworkflow_platform_CompareToConstSubstring_empty_input(void)
{
	bool result = CompareToConstSubstring("", "0x", &matchLength);
	ASSERT_FALSE(result);
	PASS();
}

TEST alfredworkflow_platform_CompareToConstSubstring_empty_input(void)
{
	bool result = CompareToConstSubstring("", "0x", &matchLength);
	ASSERT_FALSE(result);
	PASS();
}

SUITE(alfredworkflow_platform)
{
	RUN_TEST(alfredworkflow_platform_CompareToConstSubstring_empty_input);
}
#endif
