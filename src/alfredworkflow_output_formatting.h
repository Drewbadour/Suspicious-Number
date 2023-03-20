// TODO(Drew): If you feel really ambitious, add unicode support.

#ifndef ALFREDWORKFLOW_OUTPUT_FORMATTING_H
#define ALFREDWORKFLOW_OUTPUT_FORMATTING_H

#include "alfredworkflow_color_themeing.h"

typedef struct
{
	char* title;
	char* subtitle;
	char* uid;
	char* arg;
	bool valid;
} alfred_response;

void PrintRequest(alfred_response* requests, uint8_t numRequests)
{
	Assert(numRequests > 0);

	char iconPath[16] = {};
	GetIconPath(iconPath, 16);

	// Easier to mangle if it's minus one here.
	--numRequests;

	fputs("{\"items\":[", stdout);

	for (uint8_t requestIndex = 0; requestIndex <= numRequests; ++requestIndex)
	{
		alfred_response* request = requests + requestIndex;
		Assert(request->title);
		Assert(request->subtitle);

		fputs("{\"title\":\"", stdout);
		fputs(request->title, stdout);

		fputs("\",\"subtitle\":\"", stdout);
		fputs(request->subtitle, stdout);

		if (request->uid)
		{
			fputs("\",\"uid\":\"", stdout);
			fputs(request->uid, stdout);
		}

		if (request->arg)
		{
			fputs("\",\"arg\":\"", stdout);
			fputs(request->arg, stdout);
		}

		fputs("\",\"valid\":\"", stdout);
		fputs(request->valid ? "true" : "false", stdout);

		// fputs("\",\"icon\":{\"path\":\"icon_light.png\"}}", stdout);
		fputs("\",\"icon\":{\"path\":\"", stdout);
		fputs(iconPath, stdout);
		fputs("\"}}", stdout);

		// Less than means that there's more to go. Add a comma.
		if (requestIndex < numRequests)
		{
			fputs(",", stdout);
		}
	}

	fputs("]}\n", stdout);
}


#ifndef FORMAT_HELP_TITLE
#error "Please add a #define FORMAT_HELP_TITLE before including conv_shared.h for your conversion type to be shown when only the keyword is typed."
#endif
#ifndef FORMAT_HELP_SUBTITLE
#error "Please add a #define FORMAT_HELP_SUBTITLE before including conv_shared.h for your conversion type to be shown when only the keyword is typed."
#endif
void EmptyRequest(void)
{
	alfred_response response = {
		.title = FORMAT_HELP_TITLE,
		.subtitle = FORMAT_HELP_SUBTITLE,
		.valid = false
	};
	PrintRequest(&response, 1);
}

#ifndef FORMAT_ERROR_TITLE
#error "Please add a #define FORMAT_ERROR_TITLE before including conv_shared.h for your conversion type to be shown when the input is invalid."
#endif
#ifndef FORMAT_ERROR_SUBTITLE
#error "Please add a #define FORMAT_ERROR_SUBTITLE before including conv_shared.h for your conversion type to be shown when the input is invalid."
#endif
void InvalidRequest(void)
{
	alfred_response response = {
		.title = FORMAT_ERROR_TITLE,
		.subtitle = FORMAT_ERROR_SUBTITLE,
		.valid = false
	};
	PrintRequest(&response, 1);
}

#ifndef FORMAT_OVERFLOW_TITLE
#error "Please add a #define FORMAT_OVERFLOW_TITLE before including conv_shared.h for your conversion type to be shown when the input overflows."
#endif
#ifndef FORMAT_OVERFLOW_SUBTITLE
#error "Please add a #define FORMAT_OVERFLOW_SUBTITLE before including conv_shared.h for your conversion type to be shown when the input overflows."
#endif
void OverflowRequest(void)
{
	alfred_response response = {
		.title = FORMAT_OVERFLOW_TITLE,
		.subtitle = FORMAT_OVERFLOW_SUBTITLE,
		.valid = false
	};
	PrintRequest(&response, 1);
}

#endif // ALFREDWORKFLOW_OUTPUT_FORMATTING_H
