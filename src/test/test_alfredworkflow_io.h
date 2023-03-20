
TEST alfredworkflow_io_CheckNumArgs_zero(void)
{
	outcome_state outcomeState = CheckNumArgs(0);
	ASSERT_ENUM_EQ(Outcome_Empty, outcomeState, outcome_stateToString);
	PASS();
}

TEST alfredworkflow_io_CheckNumArgs_one(void)
{
	outcome_state outcomeState = CheckNumArgs(1);
	ASSERT_ENUM_EQ(Outcome_Empty, outcomeState, outcome_stateToString);
	PASS();
}

TEST alfredworkflow_io_CheckNumArgs_two(void)
{
	outcome_state outcomeState = CheckNumArgs(2);
	ASSERT_ENUM_EQ(Outcome_Valid, outcomeState, outcome_stateToString);
	PASS();
}

TEST alfredworkflow_io_CheckNumArgs_three(void)
{
	outcome_state outcomeState = CheckNumArgs(3);
	ASSERT_ENUM_EQ(Outcome_Invalid, outcomeState, outcome_stateToString);
	PASS();
}

SUITE(alfredworkflow_io)
{
	RUN_TEST(alfredworkflow_io_CheckNumArgs_zero);
	RUN_TEST(alfredworkflow_io_CheckNumArgs_one);
	RUN_TEST(alfredworkflow_io_CheckNumArgs_two);
	RUN_TEST(alfredworkflow_io_CheckNumArgs_three);
}
