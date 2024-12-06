
#ifndef ALFREDWORKFLOW_COLOR_THEMEING_H
#define ALFREDWORKFLOW_COLOR_THEMEING_H

#define ICON_DARK "icon_dark.png"
#define ICON_LIGHT "icon_light.png"

typedef union
{
	struct
	{
		double r;
		double g;
		double b;
	};
	double data[3];
} ColorF64;

void ParseRGBAText(const char* backgroundColorStr, ColorF64* color)
{
	double bigR;
	double bigG;
	double bigB;
	double transparency;

	sscanf(backgroundColorStr, "rgba(%lf,%lf,%lf,%lf)", &bigR, &bigG, &bigB, &transparency);

	color->r = bigR / 255.0;
	color->g = bigG / 255.0;
	color->b = bigB / 255.0;
}

// NOTE(Drew): Adopted from: https://stackoverflow.com/questions/596216/formula-to-determine-perceived-brightness-of-rgb-color
bool ShouldUseLightIcon(const ColorF64* backgroundColor)
{
	ColorF64 linearColor = {};

	for (uint_fast8_t index = 0; index < 3; ++index)
	{
		if (backgroundColor->data[index] <= 0.04045)
		{
			linearColor.data[index] = backgroundColor->data[index] / 12.92;
		}
		else
		{
			linearColor.data[index] = pow((backgroundColor->data[index] + 0.055) / 1.055, 2.4);
		}
	}

	double luminance =
		0.2126 * linearColor.r +
		0.7152 * linearColor.g +
		0.0722 * linearColor.b;

	Assert(luminance >= 0.0);
	Assert(luminance <= 1.0);

	double percievedLightness;
	if (luminance <= (216 / 24389))
	{
		percievedLightness = luminance * (24389 / 27);
	}
	else
	{
		percievedLightness = pow(luminance, (1 / 3.0)) * 116 - 16;
	}

	if (percievedLightness < 50.0)
	{
		return true;
	}
	else
	{
		return false;
	}

}

void GetIconPath(char* path, uint16_t availableMemoryLength)
{
	const char* backgroundColorStr = getenv("alfred_theme_background");
	if (backgroundColorStr != NULL)
	{
		Assert(CompareMemory(backgroundColorStr, "rgba(", 5));

		ColorF64 backgroundColor = {};
		ParseRGBAText(backgroundColorStr, &backgroundColor);

		if (ShouldUseLightIcon(&backgroundColor))
		{
			CopyConstString(path, ICON_LIGHT, availableMemoryLength);
		}
		else
		{
			CopyConstString(path, ICON_DARK, availableMemoryLength);
		}
	}
	else
	{
		fprintf(stderr, "Using light icon path due to null alfred_theme_background.\n");
		CopyConstString(path, ICON_LIGHT, availableMemoryLength);
	}
}

#endif // ALFREDWORKFLOW_COLOR_THEMEING_H
