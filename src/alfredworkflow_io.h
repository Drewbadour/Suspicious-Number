
#ifndef ALFREDWORKFLOW_IO_H
#define ALFREDWORKFLOW_IO_H

typedef enum {
	Outcome_Valid,
	Outcome_Empty,
	Outcome_Invalid,
	Outcome_Overflow,
} outcome_state;
#if TESTING == 1
const char* outcome_stateToString(int outcomeState)
{
	switch (outcomeState)
	{
		case Outcome_Valid: return "Outcome_Valid";
		case Outcome_Empty: return "Outcome_Empty";
		case Outcome_Invalid: return "Outcome_Invalid";
		case Outcome_Overflow: return "Outcome_Overflow";
		default: return "Invalid";
	}
}
#endif

outcome_state CheckNumArgs(int argc)
{
	if (__builtin_expect((argc == 2), 1))
	{
		return Outcome_Valid;
	}
	else if (argc <= 1)
	{
		return Outcome_Empty;
	}
	else
	{
		return Outcome_Invalid;
	}
}

void PrintFailure(outcome_state outcomeState)
{
	Assert(outcomeState != Outcome_Valid);

	switch (outcomeState)
	{
		case Outcome_Empty:
			EmptyRequest();
			break;
		case Outcome_Valid:
		case Outcome_Invalid:
			InvalidRequest();
			break;
		case Outcome_Overflow:
			OverflowRequest();
			break;
	}

	if (outcomeState == Outcome_Empty)
	{
		EmptyRequest();
	}
	else if (outcomeState == Outcome_Invalid)
	{
		InvalidRequest();
	}
	else if (outcomeState == Outcome_Overflow)
	{
		OverflowRequest();
	}
}

#endif // ALFREDWORKFLOW_IO_H
