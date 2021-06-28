#include "stdafx.h"
Player playerr = PLAYER::PLAYER_ID();

int gGlareHandle;
int scaleform;

char* version = "1.1.1";

bool GUI::Settings::DrawTextOutline = false;
float GUI::Settings::menuX = 0.85f;
float Glarewidth = 1.0240f;
float Glareheight = 1.0215f;
float GlareY = 0.495f;

void GUI::Drawing::Text(const char * text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center)
{
	UI::SET_TEXT_CENTRE(center);
	UI::SET_TEXT_COLOUR(rgbaf.r, rgbaf.g, rgbaf.b, rgbaf.a);
	UI::SET_TEXT_FONT(rgbaf.f);
	UI::SET_TEXT_SCALE(size.w, size.h);
	UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((char*)text);
	UI::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y);
}
void GUI::Drawing::Title(const char * text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center)
{
	UI::SET_TEXT_CENTRE(center);
	UI::SET_TEXT_COLOUR(rgbaf.r, rgbaf.g, rgbaf.b, rgbaf.a);
	UI::SET_TEXT_FONT(rgbaf.f);
	UI::SET_TEXT_SCALE(size.w, size.h);
	UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((char*)text);
	UI::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y);
}

namespace Globe
{
	int gGlareHandle; // int
	float gGlareDir;

	// Function(s)
	float conv360(float base, float min, float max) {
		// This is the function the script used. I just adapted it for C++.
		float fVar0;
		if (min == max) return min;
		fVar0 = max - min;

		if (base < min) base += fVar0;
		return base;
	}
	void drawGlare(float pX, float pY, float sX = 1, float sY = 1, int r = 255, int g = 255, int b = 255) {

		gGlareHandle = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MP_MENU_GLARE");

		Vector3 rot = CAM::_GET_GAMEPLAY_CAM_ROT(2);

		float dir = conv360(rot.z, 0, 360);

		if ((gGlareDir == 0 || gGlareDir - dir > 0.5) || gGlareDir - dir < -0.5) {

			gGlareDir = dir;

			GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(gGlareHandle, "SET_DATA_SLOT");

			GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_FLOAT(gGlareDir);

			GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		}

		GRAPHICS::DRAW_SCALEFORM_MOVIE(gGlareHandle, pX, pY, sX, sY, r, g, b, 255, 0);

	}
};

void GUI::Drawing::Spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
{
	if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED((char*)Streamedtexture.c_str()))
	{
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT((char*)Streamedtexture.c_str(), false);
	}
	else
	{
		GRAPHICS::DRAW_SPRITE((char*)Streamedtexture.c_str(), (char*)textureName.c_str(), x, y, width, height, rotation, r, g, b, a);
	}
}
void GUI::Drawing::Rect(RGBA rgba, VECTOR2 position, VECTOR2_2 size)
{
	GRAPHICS::DRAW_RECT(position.x, position.y, size.w, size.h, rgba.r, rgba.g, rgba.b, rgba.a);
}

static fpFileRegister file_register = (fpFileRegister)(Memory::pattern("48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50 48 8B EA 4C 8B FA 48 8B D9 4D 85 C9").count(1).get(0).get<decltype(file_register)>());
bool FileExists(const std::string& fileName)
{
	struct stat buffer;
	return (stat(fileName.c_str(), &buffer) == 0);
}
void YTD()
{
	std::string path = "Project/Textures/";
	std::string banner = "mainbanner.ytd";
	std::string icon = "char_arsenic.ytd";
	const std::string bannerPath = path + banner;
	const std::string iconPath = path + icon;

	int textureID, textureID2;
	if (FileExists(bannerPath)) {
		file_register(&textureID, bannerPath.c_str(), true, banner.c_str(), false);
		file_register(&textureID2, iconPath.c_str(), true, icon.c_str(), false);
	}
}

bool GUI::Settings::selectPressed = false;
bool GUI::Settings::leftPressed = false;
bool GUI::Settings::rightPressed = false;
bool firstopen = true;
int GUI::Settings::maxVisOptions = 16;
int GUI::Settings::currentOption = 0;
int GUI::Settings::optionCount = 0;
SubMenus GUI::Settings::currentMenu;
int GUI::Settings::menuLevel = 0;
int GUI::Settings::optionsArray[1000];
SubMenus GUI::Settings::menusArray[1000];

int colorType = 0;
RGBAF GUI::Settings::PremiumTitle{ 31, 35, 43, 255, 1 };
RGBAF GUI::Settings::titleText{ 255, 255, 255, 255, 0 };
RGBA GUI::Settings::titleRect{ 65, 244, 89, 255 };
RGBAF GUI::Settings::integre{ 255, 255, 255, 255, 4 };
RGBAF GUI::Settings::integre2{ 0, 0, 0, 255, 4 };
RGBAF GUI::Settings::SelectedText{ 0, 0, 0, 255, 0 };
RGBAF GUI::Settings::count{ 255, 255, 255, 255, 0 };
RGBAF GUI::Settings::count1{ 255, 255, 255, 255, 0 };
RGBAF GUI::Settings::arrow{ 255, 255, 255, 255, 3 };
RGBAF GUI::Settings::arrow2{ 0, 0, 0, 255, 3 };
RGBAF GUI::Settings::breakText{ 255, 255, 255, 255, 0 };
RGBA GUI::Settings::titleEnd{ 53, 60, 66, 255 };
RGBA GUI::Settings::title_sprite{ 255,255,255,255 };
RGBA GUI::Settings::title_sprite2{ 255,255,255,255 };
RGBA GUI::Settings::titleline{ 255,0,0,255 };
RGBAF GUI::Settings::title_end{ 255,255,255,255, 4 };
RGBAF GUI::Settings::optionText{ 255, 255, 255, 255, 0 };
RGBAF GUI::Settings::optionText2{ 255, 255, 255, 255, 0 };
RGBA GUI::Settings::optionRect{ 53, 60, 66, 255 };
RGBA GUI::Settings::Footer{ 31, 35, 43, 255 };
RGBA GUI::Settings::scroller{ 38, 187, 142, 255 };
RGBA GUI::Settings::line{ 255,255,255,255 };


void GUI::DRAW_TEXTURE(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
{
	if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED((char*)Streamedtexture.c_str()))
	{
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT((char*)Streamedtexture.c_str(), false);
	}
	else
	{
		GRAPHICS::DRAW_SPRITE((char*)Streamedtexture.c_str(), (char*)textureName.c_str(), x, y, width, height, rotation, r, g, b, a);
	}
}

float titlebox = 0.17f;
void GUI::Title(const char * title)
{
	YTD();

	if (Features::customtheme == true)
	{
		Drawing::Title("Project", Settings::titleText, { Settings::menuX, 0.060f }, { 0.85f, 0.85f }, true);
		Drawing::Rect(Settings::titleRect, { Settings::menuX, 0.088125f }, { 0.21f, 0.1035f });
	}

	if (Features::spacetheme == true)
	{
		Drawing::Spriter("mainbanner", "space", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
	}

	if (Features::Rainbowmenu2 == true)
	{
		if (Features::intnumber == 0)
		{
			Drawing::Spriter("mainbanner", "72", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 1)
		{
			Drawing::Spriter("mainbanner", "1", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 2)
		{
			Drawing::Spriter("mainbanner", "2", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 3)
		{
			Drawing::Spriter("mainbanner", "3", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 4)
		{
			Drawing::Spriter("mainbanner", "4", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 5)
		{
			Drawing::Spriter("mainbanner", "5", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 6)
		{
			Drawing::Spriter("mainbanner", "6", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 7)
		{
			Drawing::Spriter("mainbanner", "7", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 8)
		{
			Drawing::Spriter("mainbanner", "8", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 9)
		{
			Drawing::Spriter("mainbanner", "9", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 10)
		{
			Drawing::Spriter("mainbanner", "10", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 11)
		{
			Drawing::Spriter("mainbanner", "11", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 12)
		{
			Drawing::Spriter("mainbanner", "12", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 13)
		{
			Drawing::Spriter("mainbanner", "13", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 14)
		{
			Drawing::Spriter("mainbanner", "14", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 15)
		{
			Drawing::Spriter("mainbanner", "15", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 16)
		{
			Drawing::Spriter("mainbanner", "16", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 17)
		{
			Drawing::Spriter("mainbanner", "17", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 18)
		{
			Drawing::Spriter("mainbanner", "18", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 19)
		{
			Drawing::Spriter("mainbanner", "19", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 20)
		{
			Drawing::Spriter("mainbanner", "20", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 21)
		{
			Drawing::Spriter("mainbanner", "21", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 22)
		{
			Drawing::Spriter("mainbanner", "22", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 23)
		{
			Drawing::Spriter("mainbanner", "23", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 24)
		{
			Drawing::Spriter("mainbanner", "24", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 25)
		{
			Drawing::Spriter("mainbanner", "25", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 26)
		{
			Drawing::Spriter("mainbanner", "26", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 27)
		{
			Drawing::Spriter("mainbanner", "27", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 28)
		{
			Drawing::Spriter("mainbanner", "28", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 29)
		{
			Drawing::Spriter("mainbanner", "29", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 30)
		{
			Drawing::Spriter("mainbanner", "30", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 31)
		{
			Drawing::Spriter("mainbanner", "31", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 32)
		{
			Drawing::Spriter("mainbanner", "32", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 33)
		{
			Drawing::Spriter("mainbanner", "33", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 34)
		{
			Drawing::Spriter("mainbanner", "34", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 35)
		{
			Drawing::Spriter("mainbanner", "35", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 36)
		{
			Drawing::Spriter("mainbanner", "36", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 37)
		{
			Drawing::Spriter("mainbanner", "37", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 38)
		{
			Drawing::Spriter("mainbanner", "38", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 39)
		{
			Drawing::Spriter("mainbanner", "39", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 40)
		{
			Drawing::Spriter("mainbanner", "40", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 41)
		{
			Drawing::Spriter("mainbanner", "41", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 42)
		{
			Drawing::Spriter("mainbanner", "42", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 43)
		{
			Drawing::Spriter("mainbanner", "43", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 44)
		{
			Drawing::Spriter("mainbanner", "44", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 45)
		{
			Drawing::Spriter("mainbanner", "45", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 46)
		{
			Drawing::Spriter("mainbanner", "46", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 47)
		{
			Drawing::Spriter("mainbanner", "47", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 48)
		{
			Drawing::Spriter("mainbanner", "48", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 49)
		{
			Drawing::Spriter("mainbanner", "49", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 50)
		{
			Drawing::Spriter("mainbanner", "50", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 51)
		{
			Drawing::Spriter("mainbanner", "51", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 51)
		{
			Drawing::Spriter("mainbanner", "51", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 52)
		{
			Drawing::Spriter("mainbanner", "52", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 53)
		{
			Drawing::Spriter("mainbanner", "53", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 54)
		{
			Drawing::Spriter("mainbanner", "54", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 55)
		{
			Drawing::Spriter("mainbanner", "55", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 56)
		{
			Drawing::Spriter("mainbanner", "56", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 57)
		{
			Drawing::Spriter("mainbanner", "57", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 58)
		{
			Drawing::Spriter("mainbanner", "58", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 59)
		{
			Drawing::Spriter("mainbanner", "59", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 60)
		{
			Drawing::Spriter("mainbanner", "60", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 61)
		{
			Drawing::Spriter("mainbanner", "61", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 62)
		{
			Drawing::Spriter("mainbanner", "62", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 63)
		{
			Drawing::Spriter("mainbanner", "63", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 64)
		{
			Drawing::Spriter("mainbanner", "64", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 65)
		{
			Drawing::Spriter("mainbanner", "65", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 66)
		{
			Drawing::Spriter("mainbanner", "66", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 67)
		{
			Drawing::Spriter("mainbanner", "67", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 68)
		{
			Drawing::Spriter("mainbanner", "68", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 69)
		{
			Drawing::Spriter("mainbanner", "69", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 70)
		{
			Drawing::Spriter("mainbanner", "70", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 71)
		{
			Drawing::Spriter("mainbanner", "71", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}

		if (Features::intnumber == 72)
		{
			Drawing::Spriter("mainbanner", "72", Settings::menuX, 0.0800f, 0.21f, 0.090f, 0.f, 255, 255, 255, 255);
		}
	}

	if (Features::globe == true)
	{
		Globe::drawGlare(GUI::Settings::menuX + 0.3355f, GlareY, Glarewidth, Glareheight, 255, 255, 255);
	}


	UI::HIDE_HELP_TEXT_THIS_FRAME();
	CAM::SET_CINEMATIC_BUTTON_ACTIVE(0);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(10);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(6);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(7);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(9);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(8);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_NEXT_CAMERA, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_CHARACTER_WHEEL, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_LIGHT, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_HEAVY, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MULTIPLAYER_INFO, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_PHONE, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_ALTERNATE, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_VEH_CIN_CAM, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MAP_POI, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_PHONE, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_VEH_RADIO_WHEEL, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_VEH_HEADLIGHT, true);
}

void GUI::Subtitle(const char * title)
{
	int opcount = Settings::optionCount;
	int currop = Settings::currentOption;
	Drawing::Spriter("CommonMenu", "", Settings::menuX, (Settings::optionCount + 1) * 0.035f + 0.1065f, 0.21f, 0.035f, 180, 31, 35, 43, 255);
	Drawing::Text(title, Settings::optionText2, { Settings::menuX - 0.099f, 0.128f }, { 0.32f, 0.32f }, false);
}

bool GUI::Option(const char * option)
{
	Settings::optionCount++;
	bool onThis = Settings::currentOption == Settings::optionCount ? true : false;
	if (Settings::currentOption <= 16 && Settings::optionCount <= 16)
	{
		Drawing::Text(option, onThis ? Settings::SelectedText : Settings::optionText, { Settings::menuX - 0.100f, (Settings::optionCount)*0.035f + 0.128f }, { 0.32f, 0.32f }, false);
		Drawing::Rect(Settings::optionRect, { Settings::menuX, (Settings::optionCount)*0.035f + 0.1415f }, { 0.21f, 0.035f });
		onThis ? Drawing::Rect(Settings::scroller, { Settings::menuX, (Settings::optionCount)*0.035f + 0.1415f, }, { 0.21f, 0.035f }) : NULL;
	}
	else if (Settings::optionCount > (Settings::currentOption - 16) && Settings::optionCount <= Settings::currentOption)
	{
		Drawing::Text(option, onThis ? Settings::SelectedText : Settings::optionText, { Settings::menuX - 0.100f, (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.128f }, { 0.32f, 0.32f }, false);
		Drawing::Rect(Settings::optionRect, { Settings::menuX,  (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.1415f }, { 0.21f, 0.035f });
		onThis ? Drawing::Rect(Settings::scroller, { Settings::menuX, (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.1415f, }, { 0.21f, 0.035f }) : NULL;
	}
	if (Settings::currentOption == Settings::optionCount)
	{
		if (Settings::selectPressed)
		{
			return true;
		}
	}
	return false;
}

bool GUI::ListVector(const char * option, std::vector<char*> Vector, int & position)
{
	constexpr static const VECTOR2_2 textSize = { 0.45f, 0.45f };
	bool onThis = Settings::currentOption == Settings::optionCount + 1 ? true : false;
	Option("");

	if (Settings::optionCount == Settings::currentOption) {
		size_t max = Vector.size() - 1;
		int min = 0;
		if (Settings::rightPressed) {
			position >= 1 ? position-- : position = max;
		}
		if (Settings::leftPressed) {
			position < max ? position++ : position = min;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions) {
		std::string SelectedChar
			= UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL($(Vector[position])));
		if (SelectedChar == "NULL") SelectedChar = Vector[position];

		UI::SET_TEXT_COLOUR(255, 255, 255, 255);
		UI::SET_TEXT_FONT(0);
		UI::SET_TEXT_SCALE(0.32f, 0.32f);
		UI::SET_TEXT_CENTRE(false);
		if (GUI::Settings::DrawTextOutline) {
			UI::SET_TEXT_DROPSHADOW(1, 0, 0, 0, 0);
			UI::SET_TEXT_EDGE(1, 0, 0, 0, 0);
			UI::SET_TEXT_OUTLINE();
		}
		UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		std::string s = option;
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(Tools::StringToChar(s + "      < " + SelectedChar + " >"));
		UI::END_TEXT_COMMAND_DISPLAY_TEXT(Settings::menuX - 0.09f, Settings::optionCount * 0.035f + 0.125f);
	}
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption) {
		std::string SelectedChar
			= UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL($(Vector[position])));
		if (SelectedChar == "NULL") SelectedChar = Vector[position];

		UI::SET_TEXT_COLOUR(255, 255, 255, 255);
		UI::SET_TEXT_FONT(0);
		UI::SET_TEXT_SCALE(0.32f, 0.32f);
		UI::SET_TEXT_CENTRE(false);
		UI::SET_TEXT_DROPSHADOW(1, 0, 0, 0, 0);
		UI::SET_TEXT_EDGE(1, 0, 0, 0, 0);
		UI::SET_TEXT_OUTLINE();
		UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		std::string s = option;
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(Tools::StringToChar(s + "      < " + SelectedChar + " >"));
		UI::END_TEXT_COMMAND_DISPLAY_TEXT(Settings::menuX - 0.09f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions))*0.035f + 0.125f);
	}

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return false;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return false;
	return false;
}

bool GUI::Break(const char * option)
{
	int upKey = VK_UP;
	int downKey = VK_DOWN;
	int numUpKey = VK_NUMPAD8;
	int numDownKey = VK_NUMPAD2;
	Settings::optionCount++;
	bool onThis = Settings::currentOption == Settings::optionCount ? true : false;
	if (Settings::currentOption <= 16 && Settings::optionCount <= 16)
	{
		Drawing::Text(option, Settings::breakText, { Settings::menuX, (Settings::optionCount)*0.035f + 0.125f }, { 0.35f, 0.35f }, true);
		Drawing::Rect(Settings::optionRect, { Settings::menuX, (Settings::optionCount)*0.035f + 0.1415f }, { 0.21f, 0.035f });
		if (onThis && GetAsyncKeyState(upKey)) {
			Settings::currentOption--;
		}
		if (onThis && GetAsyncKeyState(downKey)) {
			Settings::currentOption++;
		}
		if (onThis && GetAsyncKeyState(numUpKey)) {
			Settings::currentOption--;
		}
		if (onThis && GetAsyncKeyState(numDownKey)) {
			Settings::currentOption++;
		}
	}
	else if (Settings::optionCount > (Settings::currentOption - 16) && Settings::optionCount <= Settings::currentOption)
	{
		Drawing::Text(option, Settings::breakText, { Settings::menuX, (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.125f }, { 0.35f, 0.35f }, true);
		Drawing::Rect(Settings::optionRect, { Settings::menuX,  (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.1415f }, { 0.21f, 0.035f });
		if (onThis && GetAsyncKeyState(upKey)) {
			Settings::currentOption--;
		}
		if (onThis && GetAsyncKeyState(downKey)) {
			Settings::currentOption++;
		}
		if (onThis && GetAsyncKeyState(numUpKey)) {
			Settings::currentOption--;
		}
		if (onThis && GetAsyncKeyState(numDownKey)) {
			Settings::currentOption++;
		}
	}
	return false;
}

bool GUI::Option(const char * option, std::function<void()> function)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	return false;
}

bool GUI::MenuOption(const char * option, SubMenus newSub)
{
	Option(option);

	bool onThis = Settings::currentOption == Settings::optionCount ? true : false;
	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(">>", onThis ? Settings::SelectedText : Settings::optionText, { Settings::menuX + 0.090f, Settings::optionCount * 0.035f + 0.128f }, { 0.32f, 0.32f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(">>", onThis ? Settings::SelectedText : Settings::optionText, { Settings::menuX + 0.090f, (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.12f }, { 0.32f, 0.32f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		MenuLevelHandler::MoveMenu(newSub);
		return true;
	}
	return false;
}

bool GUI::MenuOption(const char * option, SubMenus newSub, std::function<void()> function)
{
	MenuOption(option, newSub);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	return false;
}

bool GUI::Toggle(const char * option, bool & b00l)
{
	Option(option);
	if (b00l)
	{//on
		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Drawing::Spriter("commonmenu", "shop_tick_icon", Settings::menuX + 0.090f, (Settings::optionCount * 0.035f + 0.141f), 0.02f, 0.03f, 0, 0, 255, 0, 255); // 0.35 // 0.125 // 0.45
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			Drawing::Spriter("commonmenu", "shop_tick_icon", Settings::menuX + 0.090f, ((Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.141f), 0.02f, 0.03f, 0, 0, 255, 0, 255);
	}
	else
	{//off
		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Drawing::Spriter("commonmenu", "shop_lock", Settings::menuX + 0.090f, (Settings::optionCount * 0.035f + 0.141f), 0.02f, 0.03f, 0, 255, 0, 0, 255);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			Drawing::Spriter("commonmenu", "shop_lock", Settings::menuX + 0.090f, ((Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.141f), 0.02f, 0.03f, 0, 255, 0, 0, 255);
	}
	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		b00l ^= 1;
		return true;
	}
	return false;
}
bool GUI::Toggle(const char* options, bool & b00l, char* text)
{
	Toggle(options, b00l);
	if (Settings::optionCount == Settings::currentOption)
	{
		GUI::textbelowmenu(text);
		return true;
	}
	return false;
}
bool GUI::Toggle(const char * option, bool & b00l, std::function<void()> function)
{
	Toggle(option, b00l);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	return false;
}

bool GUI::Int(const char * option, int & _int, int min, int max)
{
	Option(option);
	bool onThis = Settings::currentOption == Settings::optionCount ? true : false;
	if (Settings::optionCount == Settings::currentOption) {
		if (Settings::leftPressed) {
			_int < max ? _int++ : _int = min;
		}
		if (Settings::rightPressed) {
			_int >= min ? _int-- : _int = max;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Tools::StringToChar("[ " + std::to_string(_int) + " ]"), onThis ? Settings::integre2 : Settings::integre, { Settings::menuX + 0.090f, Settings::optionCount * 0.035f + 0.128f }, { 0.32f, 0.32f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Tools::StringToChar("[ " + std::to_string(_int) + " ]"), onThis ? Settings::integre2 : Settings::integre, { Settings::menuX + 0.090f, (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.12f }, { 0.32f, 0.32f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}
bool GUI::Int(const char * option, int & _int, int min, int max, int step)
{
	Option(option);
	bool onThis = Settings::currentOption == Settings::optionCount ? true : false;
	if (Settings::optionCount == Settings::currentOption) {
		if (Settings::leftPressed) {
			_int < max ? _int += step : _int = min;
		}
		if (Settings::rightPressed) {
			_int >= min ? _int -= step : _int = max;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Tools::StringToChar("[ " + std::to_string(_int) + " ]"), onThis ? Settings::integre2 : Settings::integre, { Settings::menuX + 0.090f, Settings::optionCount * 0.035f + 0.125f }, { 0.32f, 0.32f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Tools::StringToChar("[ " + std::to_string(_int) + " ]"), onThis ? Settings::integre2 : Settings::integre, { Settings::menuX + 0.090f, (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.12f }, { 0.32f, 0.32f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}
bool GUI::Int(const char * option, int & _int, int min, int max, std::function<void()> function)
{
	Int(option, _int, min, max);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) {
		function();
		return true;
	}
	return false;
}
bool GUI::Int(const char * option, int & _int, int min, int max, int step, std::function<void()> function)
{
	Int(option, _int, min, max, step);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) {
		function();
		return true;
	}
	return false;
}
bool GUI::ToggleInt(const char* option, bool&b00l, int&_int, int min, int max)
{
	Option(option);
	bool onThis = Settings::currentOption == Settings::optionCount ? true : false;
	if (Settings::optionCount == Settings::currentOption) {
		if (Settings::leftPressed) {
			_int < max ? _int++ : _int = min;
		}
		if (Settings::rightPressed) {
			_int >= min ? _int-- : _int = max;
		}
	}
	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
	{
		Drawing::Text(Tools::StringToChar("[" + std::to_string(_int) + "]"), onThis ? Settings::integre2 : Settings::integre, { Settings::menuX + 0.090f,Settings::optionCount*0.035f + 0.128f }, { 0.32f, 0.32f }, true);
		Drawing::Spriter("commonmenu", "shop_box_tick", Settings::menuX + 0.095f, (Settings::optionCount * 0.035f + 0.141f), 0.02f, 0.03f, 0, 255, 255, 255, 255);
	}
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
	{
		Drawing::Text(Tools::StringToChar("[ " + std::to_string(_int) + " ]"), onThis ? Settings::integre2 : Settings::integre, { Settings::menuX + 0.090f, Settings::optionCount*0.035f + 0.128f }, { 0.32f, 0.32f }, true);
		Drawing::Spriter("commonmenu", "shop_box_tick", Settings::menuX + 0.095f, (Settings::optionCount * 0.035f + 0.141f), 0.02f, 0.03f, 0, 255, 255, 255, 255);
	}
	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		b00l ^= 1;
		return true;
	}
	return false;
}
bool GUI::ToggleInt(const char* option, bool&b00l, int&_int, int min, int max, char* text, int step)
{
	Option(option);
	GUI::textbelowmenu(text);
	bool onThis = Settings::currentOption == Settings::optionCount ? true : false;
	if (Settings::optionCount == Settings::currentOption) {
		if (Settings::leftPressed) {
			_int < max ? _int += step : _int = min;
		}
		if (Settings::rightPressed) {
			_int >= min ? _int -= step : _int = max;
		}
	}
	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
	{
		Drawing::Text(Tools::StringToChar("[" + std::to_string(_int) + "]"), onThis ? Settings::integre2 : Settings::integre, { Settings::menuX + 0.090f,Settings::optionCount*0.035f + 0.128f }, { 0.32f, 0.32f }, true);
		Drawing::Spriter("commonmenu", b00l ? "shop_box_tick" : "shop_box_blank", (Settings::menuX + 0.096f), (Settings::optionCount * 0.035f + 0.177f), 0.03f, 0.05f, 0, 255, 255, 255, 255);
	}
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
	{
		Drawing::Text(Tools::StringToChar("[ " + std::to_string(_int) + " ]"), onThis ? Settings::integre2 : Settings::integre, { Settings::menuX + 0.090f, Settings::optionCount*0.035f + 0.128f }, { 0.32f, 0.32f }, true);
		Drawing::Spriter("commonmenu", b00l ? "shop_box_tick" : "shop_box_blank", (Settings::menuX + 0.096f), (Settings::optionCount * 0.035f + 0.177f), 0.03f, 0.05f, 0, 255, 255, 255, 255);
	}
	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		b00l ^= 1;
		return true;
	}
}
bool GUI::ToggleInt(const char* option, bool&b00l, int&_int, int min, int max, char* text, int step, std::function<void()> function)
{
	ToggleInt(option, b00l, _int, min, max, text, step);
	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) {
		function();
		return true;
	}
	return false;
}

bool GUI::Float(const char * option, float & _float, int min, int max)
{
	Option(option);
	bool onThis = Settings::currentOption == Settings::optionCount ? true : false;
	stringstream stream;
	if (Settings::optionCount == Settings::currentOption) {
		if (Settings::leftPressed) {
			_float < max ? _float++ : _float = min;
		}
		if (Settings::rightPressed) {
			_float >= min ? _float-- : _float = max;
		}
	}

	stream << fixed << setprecision(0) << _float;
	string value = stream.str();

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Tools::StringToChar("[ " + value + " ]"), onThis ? Settings::integre2 : Settings::integre, { Settings::menuX + 0.090f, Settings::optionCount * 0.035f + 0.128f }, { 0.32f, 0.32f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Tools::StringToChar("[ " + value + " ]"), onThis ? Settings::integre2 : Settings::integre, { Settings::menuX + 0.090f, (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.12f }, { 0.32f, 0.32f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}

bool GUI::Float(const char * option, float & _float, float min, float max, float step)
{
	Option(option);
	bool onThis = Settings::currentOption == Settings::optionCount ? true : false;
	stringstream stream;
	if (Settings::optionCount == Settings::currentOption) {
		if (Settings::leftPressed) {
			_float < max ? _float += step : _float = min;
		}
		if (Settings::rightPressed) {
			_float >= min ? _float -= step : _float = max;
		}
	}

	stream << fixed << setprecision(0) << _float;
	string value = stream.str();

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Tools::StringToChar("[ " + value + " ]"), onThis ? Settings::integre2 : Settings::integre, { Settings::menuX + 0.090f, Settings::optionCount * 0.035f + 0.125f }, { 0.32f, 0.32f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Tools::StringToChar("[ " + value + " ]"), onThis ? Settings::integre2 : Settings::integre, { Settings::menuX + 0.090f, (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.12f }, { 0.32f, 0.32f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}

bool GUI::MenuPlayer(const char * option, SubMenus newSub, int player)
{
	Option(option);
	bool onThis = Settings::currentOption == Settings::optionCount ? true : false;
	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions) {
		Drawing::Text("", Settings::optionText, { Settings::menuX + 0.090f, Settings::optionCount * 0.035f + 0.160f }, { 0.4f, 0.4f }, true);
		if (onThis) {
			Features::LoadPlayerInfo(PLAYER::GET_PLAYER_NAME(player), player);
		}
	}
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption) {
		Drawing::Text("", Settings::optionText, { Settings::menuX + 0.090f, (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.160f }, { 0.4f, 0.4f }, true);
		if (onThis) {
			Features::LoadPlayerInfo(PLAYER::GET_PLAYER_NAME(player), player);
		}
	}

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		MenuLevelHandler::MoveMenu(newSub);
		return true;
	}
	return false;
}

bool GUI::MenuPlayer(const char * option, SubMenus newSub, int player, std::function<void()> function)
{
	MenuPlayer(option, newSub, player);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	return false;
}

#pragma warning(disable: 4267)
bool GUI::IntVector(const char * option, std::vector<int> Vector, int & position)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		int max = Vector.size() - 1;
		int min = 0;
		if (Settings::leftPressed) {
			position >= 1 ? position-- : position = max;
		}
		if (Settings::rightPressed) {
			position < max ? position++ : position = min;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Tools::StringToChar(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Tools::StringToChar(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.12f }, { 0.5f, 0.5f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}

bool GUI::IntVector(const char * option, std::vector<int> Vector, int & position, std::function<void()> function)
{
	IntVector(option, Vector, position);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) {
		function();
		return true;
	}
	return false;
}

bool GUI::FloatVector(const char * option, std::vector<float> Vector, int & position)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		size_t max = Vector.size() - 1;
		int min = 0;
		if (Settings::leftPressed) {
			position >= 1 ? position-- : position = max;
		}
		if (Settings::rightPressed) {
			position < max ? position++ : position = min;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Tools::StringToChar(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Tools::StringToChar(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.12f }, { 0.5f, 0.5f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}

bool GUI::FloatVector(const char * option, std::vector<float> Vector, int & position, std::function<void()> function)
{
	FloatVector(option, Vector, position);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) {
		function();
		return true;
	}
	return false;
}

bool GUI::StringVector(const char * option, std::vector<std::string> Vector, int & position)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		size_t max = Vector.size() - 1;
		int min = 0;
		if (Settings::leftPressed) {
			position >= 1 ? position-- : position = max;
		}
		if (Settings::rightPressed) {
			position < max ? position++ : position = min;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Tools::StringToChar((Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Tools::StringToChar((Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.12f }, { 0.5f, 0.5f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}

bool GUI::StringVector(const char * option, std::vector<std::string> Vector, int & position, std::function<void()> function)
{
	StringVector(option, Vector, position);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) {
		function();
		return true;
	}
	return false;
}

bool GUI::StringVector(const char * option, std::vector<char*> Vector, int & position)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		size_t max = Vector.size() - 1;
		int min = 0;
		if (Settings::leftPressed) {
			position >= 1 ? position-- : position = max;
		}
		if (Settings::rightPressed) {
			position < max ? position++ : position = min;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(((Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(((Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.12f }, { 0.5f, 0.5f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}

bool GUI::StringVector(const char * option, std::vector<char*> Vector, int & position, std::function<void()> function)
{
	StringVector(option, Vector, position);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) {
		function();
		return true;
	}
	return false;
}


void GUI::info(const char * info)
{
	if (Settings::currentOption <= 1 && Settings::optionCount <= 1)
	{
		Drawing::Text(info, Settings::optionText, { Settings::menuX - 0.100f, 11 * 0.035f + 0.1600f }, { 0.25f, 0.25f }, false), Drawing::Rect(Settings::optionRect, { Settings::menuX, 1 * 0.035f + 0.1820f }, { 0.21f, 0.045f });
	}
	else if (Settings::optionCount > (Settings::currentOption - 1) && Settings::optionCount <= Settings::currentOption)
	{
		Drawing::Text(info, Settings::optionText, { Settings::menuX - 0.100f, (Settings::optionCount - (Settings::currentOption - 10))*0.035f + 0.1300f }, { 0.25f, 0.25f }, false), Drawing::Rect(Settings::optionRect, { Settings::menuX, (Settings::optionCount + 1) * 0.035f + 0.1820f }, { 0.21f, 0.045f });
	}
}
bool GUI::textbelowmenu(const char * Text)
{
	if (Settings::optionCount <= Settings::currentOption)
	{
		//Drawing::Text(Text, Settings::optionText, { Settings::menuX - 0.078f, (Settings::optionCount+1) * 0.010f + 0.56f }, { 0.35f,0.38f }, true);
		//Drawing::Rect(Settings::background, { Settings::menuX, (Settings::optionCount+1) * 0.010f + 0.59f }, { 0.21f, 0.035f });
		Drawing::Text(Text, Settings::optionText, { Settings::menuX - 0.100f, (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.1300f }, { 0.25f, 0.25f }, false), Drawing::Rect(Settings::optionRect, { Settings::menuX, (Settings::optionCount + 1) * 0.035f + 0.1820f }, { 0.21f, 0.045f });
	}
	return true;
}
void GUI::End()
{
	int opcount = Settings::optionCount;
	int currop = Settings::currentOption;

	char* rank;

	if (Features::menu_version == 2)
	{
		rank = "  Rank: ~g~VIP+";
	}
	if (Features::menu_version == 1)
	{
		rank = " Rank: ~g~VIP";
	}

	if (opcount >= 16) {
		Drawing::Text(rank, Settings::optionText2, { Settings::menuX - 0.078f, 17 * 0.035f + 0.130f }, { 0.32f, 0.32f }, true);
		Drawing::Text(version, Settings::optionText2, { Settings::menuX + 0.088f, 17 * 0.035f + 0.130f }, { 0.32f, 0.32f }, true);
		Drawing::Text(Tools::StringToChar(std::to_string(currop) + "/" + std::to_string(opcount)), Settings::count, { Settings::menuX + 0.088f, 0.128f }, { 0.32f, 0.32f }, true);
		Drawing::Rect(Settings::Footer, { Settings::menuX, 17 * 0.035f + 0.1415f }, { 0.21f, 0.035f });
		Drawing::Spriter("commonmenu", "shop_arrows_upanddown", Settings::menuX, ((16 + 1) * 0.035f + 0.140f), 0.020f, 0.035f, 180, Settings::line.r, Settings::line.g, Settings::line.b, Settings::line.a);

	}
	else if (opcount > 0) {
		Drawing::Text(rank, Settings::optionText2, { Settings::menuX - 0.078f, (Settings::optionCount + 1) * 0.035f + 0.130f }, { 0.32f, 0.32f }, true);
		Drawing::Text(version, Settings::optionText2, { Settings::menuX + 0.088f, (Settings::optionCount + 1) * 0.035f + 0.130f }, { 0.32f, 0.32f }, true);
		Drawing::Text(Tools::StringToChar(std::to_string(currop) + "/" + std::to_string(opcount)), Settings::count, { Settings::menuX + 0.088f, 0.128f }, { 0.32f, 0.32f }, true);
		Drawing::Rect(Settings::Footer, { Settings::menuX, (Settings::optionCount + 1) * 0.035f + 0.1415f }, { 0.21f, 0.035f });
		Drawing::Spriter("commonmenu", "shop_arrows_upanddown", Settings::menuX, ((Settings::optionCount + 1) * 0.035f + 0.140f), 0.020f, 0.035f, 180, Settings::line.r, Settings::line.g, Settings::line.b, Settings::line.a);
	}
}

int IconNotification(char *text, char *text2, char *Subject)
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	//UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG("CHAR_GANGAPP", "CHAR_GANGAPP", false, 7, text2, Subject, 1.0, "___Menu");
	return UI::_DRAW_NOTIFICATION(1, 1);
}
//char * text = "Logged in";
void PlaySoundFrontend_default(char* sound_name)
{
	AUDIO::PLAY_SOUND_FRONTEND(-1, sound_name, "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
}
void PlaySoundFrontend_default2(char* sound_name)
{
	AUDIO::PLAY_SOUND_FRONTEND(-1, sound_name, "DLC_HEIST_BIOLAB_PREP_HACKING_SOUNDS", 0);
}
char * GUI::Tools::StringToChar(std::string string)
{
	return _strdup(string.c_str());
}

int GUI::Settings::keyPressDelay = 200;
int GUI::Settings::keyPressPreviousTick = GetTickCount();
int GUI::Settings::keyPressDelay2 = 150;
int GUI::Settings::keyPressPreviousTick2 = GetTickCount();
int GUI::Settings::keyPressDelay3 = 140;
int GUI::Settings::keyPressPreviousTick3 = GetTickCount();
int GUI::Settings::openKey = VK_MULTIPLY;
int GUI::Settings::backKey = VK_NUMPAD0;
int GUI::Settings::upKey = VK_NUMPAD8;
int GUI::Settings::downKey = VK_NUMPAD2;
int GUI::Settings::leftKey = VK_NUMPAD4;
int GUI::Settings::rightKey = VK_NUMPAD6;
int GUI::Settings::selectKey = VK_NUMPAD5;
int GUI::Settings::arrowupKey = VK_UP;
int GUI::Settings::arrowdownKey = VK_DOWN;
int GUI::Settings::arrowleftKey = VK_LEFT;
int GUI::Settings::arrowrightKey = VK_RIGHT;
int GUI::Settings::enterKey = VK_RETURN;
int GUI::Settings::deleteKey = VK_BACK;

bool isGtaRunning()
{
	return GetForegroundWindow() == FindWindowA(NULL, "Grand Theft Auto V");
}

#pragma warning(disable: 4018)
//bool firstopen = true;
bool GUI::Settings::controllerinput = true;
void GUI::Checks::Keys()
{
	Settings::selectPressed = false;
	Settings::leftPressed = false;
	Settings::rightPressed = false;
	if (GetTickCount() - Settings::keyPressPreviousTick > Settings::keyPressDelay) {
		if (GetTickCount() - Settings::keyPressPreviousTick2 > Settings::keyPressDelay2) {
			if (GetTickCount() - Settings::keyPressPreviousTick3 > Settings::keyPressDelay3) {
				if ((Features::menu_version == 1) || (Features::menu_version == 2)) {
					if (IsKeyPressed(VK_F4) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlScriptRB) && CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneRight) && Settings::controllerinput) {
						Settings::menuLevel == 0 ? MenuLevelHandler::MoveMenu(SubMenus::mainmenu) : Settings::menuLevel == 1 ? MenuLevelHandler::BackMenu() : NULL;
						if (firstopen) {
							PlaySoundFrontend_default2("Hack_Success");
							firstopen = false;
						}

						Settings::keyPressPreviousTick = GetTickCount();
					}
					else if (IsKeyPressed(VK_NUMPAD0) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendCancel) && Settings::controllerinput) {
						Settings::menuLevel > 0 ? MenuLevelHandler::BackMenu() : NULL;
						if (Settings::menuLevel > 0)
							PlaySoundFrontend_default("BACK");

						Settings::keyPressPreviousTick = GetTickCount();
					}
					else if (IsKeyPressed(VK_NUMPAD8) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendUp) && Settings::controllerinput) {
						Settings::currentOption > 1 ? Settings::currentOption-- : Settings::currentOption = Settings::optionCount;
						if (Settings::menuLevel > 0)
							PlaySoundFrontend_default("NAV_UP_DOWN");

						Settings::keyPressPreviousTick3 = GetTickCount();
					}
					else if (IsKeyPressed(VK_NUMPAD2) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendDown) && Settings::controllerinput) {
						Settings::currentOption < Settings::optionCount ? Settings::currentOption++ : Settings::currentOption = 1;
						if (Settings::menuLevel > 0)
							PlaySoundFrontend_default("NAV_UP_DOWN");

						Settings::keyPressPreviousTick2 = GetTickCount();
					}
					else if (IsKeyPressed(VK_NUMPAD6) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneRight) && Settings::controllerinput) {
						Settings::leftPressed = true;
						if (Settings::menuLevel > 0)
							PlaySoundFrontend_default("NAV_UP_DOWN");

						Settings::keyPressPreviousTick3 = GetTickCount();
					}
					else if (IsKeyPressed(VK_NUMPAD4) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneLeft) && Settings::controllerinput) {
						Settings::rightPressed = true;
						if (Settings::menuLevel > 0)
							PlaySoundFrontend_default("NAV_UP_DOWN");

						Settings::keyPressPreviousTick3 = GetTickCount();
					}
					else if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept) && Settings::controllerinput) {
						Settings::selectPressed = true;
						if (Settings::menuLevel > 0)
							PlaySoundFrontend_default("SELECT");

						Settings::keyPressPreviousTick = GetTickCount();
					}

					//Teleport to waypoint.
					//if (isGtaRunning() && KeyJustUp(VK_F5))
					//{
					//	Features::teleportToWaypoint();
					//}
				}
				else if (Features::menu_version = 0) {

					UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
					UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Project");
					UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", false, 7, "~r~Authentication Failed", "You can purchase the menu on Project.com", 1.0, "___ARSC");
					UI::_DRAW_NOTIFICATION(5000, 1);
				}
				else if (Features::menu_version = 3) {
					UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Project");
					UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", false, 7, "~r~Authentication Failed", "Your HWID does not match our records", 1.0, "___ARSC");
					UI::_DRAW_NOTIFICATION(5000, 1);
				}
				else {
					UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Project");
					UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", false, 7, "~r~Authentication Failed", "Please enter a valid username & password", 1.0, "___ARSC");
					UI::_DRAW_NOTIFICATION(5000, 1);
				}
			}
		}
	}
	Settings::optionCount = 0;
}

#pragma warning(default : 4018)

void GUI::MenuLevelHandler::MoveMenu(SubMenus menu)
{
	Settings::menusArray[Settings::menuLevel] = Settings::currentMenu;
	Settings::optionsArray[Settings::menuLevel] = Settings::currentOption;
	Settings::menuLevel++;
	Settings::currentMenu = menu;
	Settings::currentOption = 1;
}

void GUI::MenuLevelHandler::BackMenu()
{
	Settings::menuLevel--;
	Settings::currentMenu = Settings::menusArray[Settings::menuLevel];
	Settings::currentOption = Settings::optionsArray[Settings::menuLevel];
}

void GUI::Files::WriteStringToIni(std::string string, std::string file, std::string app, std::string key)
{
	WritePrivateProfileStringA(app.c_str(), key.c_str(), string.c_str(), file.c_str());
}
std::string GUI::Files::ReadStringFromIni(std::string file, std::string app, std::string key)
{
	char buf[100];
	GetPrivateProfileStringA(app.c_str(), key.c_str(), "NULL", buf, 100, file.c_str());
	return (std::string)buf;
}

void GUI::Files::WriteIntToIni(int intValue, std::string file, std::string app, std::string key)
{
	WriteStringToIni(std::to_string(intValue), file, app, key);
}

int GUI::Files::ReadIntFromIni(std::string file, std::string app, std::string key)
{
	return std::stoi(ReadStringFromIni(file, app, key));
}

void GUI::Files::WriteFloatToIni(float floatValue, std::string file, std::string app, std::string key)
{
	WriteStringToIni((std::to_string(floatValue)), file, app, key);
}

float GUI::Files::ReadFloatFromIni(std::string file, std::string app, std::string key)
{
	return std::stof(ReadStringFromIni(file, app, key));
}

void GUI::Files::WriteBoolToIni(bool b00l, std::string file, std::string app, std::string key)
{
	WriteStringToIni(b00l ? "true" : "false", file, app, key);
}

bool GUI::Files::ReadBoolFromIni(std::string file, std::string app, std::string key)
{
	return ReadStringFromIni(file, app, key) == "true" ? true : false;
}
//------Colorbox----------------
void GUI::Colorbox2(std::string texture1, std::string texture2, int r, int g, int b, int a)
{
	if (GUI::Settings::menuX < 0.78f)
	{
		if (GUI::Settings::optionCount == GUI::Settings::currentOption) { GUI::Drawing::Spriter(texture1, texture2, GUI::Settings::menuX + 0.24f, 0.2f, 0.11f, 0.11f, 0, r, g, b, a); }
	}
	else { if (GUI::Settings::optionCount == GUI::Settings::currentOption) { GUI::Drawing::Spriter(texture1, texture2, GUI::Settings::menuX - 0.24f, 0.2f, 0.11f, 0.11f, 0, r, g, b, a); } }
}
void GUI::Colorbox(std::string texture1, std::string texture2, RGBA rgba)
{
	if (GUI::Settings::menuX < 0.78f)
	{
		if (GUI::Settings::optionCount == GUI::Settings::currentOption) { GUI::Drawing::Spriter(texture1, texture2, GUI::Settings::menuX + 0.24f, 0.2f, 0.11f, 0.11f, 0, rgba.r, rgba.g, rgba.b, rgba.a); }
	}
	else { if (GUI::Settings::optionCount == GUI::Settings::currentOption) { GUI::Drawing::Spriter(texture1, texture2, GUI::Settings::menuX - 0.24f, 0.2f, 0.11f, 0.11f, 0, rgba.r, rgba.g, rgba.b, rgba.a); } }
}
//---------Vehicle----------------
void GUI::Vehicle(std::string texture1, std::string texture2)
{
	if (GUI::Settings::menuX < 0.78f)
	{
		if (GUI::Settings::optionCount == GUI::Settings::currentOption) { GUI::Drawing::Spriter(texture1, texture2, GUI::Settings::menuX + 0.24f, 0.2f, 0.11f, 0.11f, 0, 255, 255, 255, 255); }
	}
	else { if (GUI::Settings::optionCount == GUI::Settings::currentOption) { GUI::Drawing::Spriter(texture1, texture2, GUI::Settings::menuX - 0.24f, 0.2f, 0.11f, 0.11f, 0, 255, 255, 255, 255); } }
}
void GUI::Vehicle2(std::string texture1, std::string texture2)
{
	if (GUI::Settings::optionCount == GUI::Settings::currentOption) { GUI::Drawing::Spriter(texture1, texture2, GUI::Settings::menuX - 0.24f, 0.362f, 0.15f, 0.18f, 0, 255, 255, 255, 255); }
}
//-----------Player Info-----------

void GUI::PlayerInfoTitle(char* text)
{
	Drawing::Rect(Settings::titleRect, { Settings::menuX - 0.230f,  0.1250f }, { 0.165f, 0.045f });
	Drawing::Spriter("shopui_title_clubhousemod", "shopui_title_clubhousemod", Settings::menuX + 0.175f, 0.1175f - 0.019f, 0.115f, 0.045f, 180, Settings::titleRect.r, Settings::titleRect.g, Settings::titleRect.b, 255);
}


void GUI::PlayerInfoLine(char* text, short line)
{
	if (line == 1) {
		Drawing::Rect(Settings::optionRect, { Settings::menuX - 0.230f, 0.3335f }, { 0.165f, 13 * 0.045f + -0.213f });
		//Drawing::Rect(Settings::optionRect, { Settings::menuX + 0.1385f, 0.2520f }, { 0.019f, 0.085f });
	}
	Drawing::Text(text, Settings::optionText, { Settings::menuX - 0.230f, (line * 0.030f) + 0.155f }, { 0.35f, 0.35f }, true);
}

void GUI::AddSmallTitle(char* text)
{
	if (GUI::Settings::menuX < 0.78f)
	{
		Drawing::Text(text, Settings::titleText, { Settings::menuX + 0.175f, 0.090f }, { 0.425f, 0.425f }, true);
		Drawing::Spriter("CommonMenu", "", Settings::menuX + 0.175f, 0.1175f - 0.019f, 0.115f, 0.045f, 180, Settings::titleEnd.r, Settings::titleEnd.g, Settings::titleEnd.b, Settings::titleEnd.a);
	}
	else
	{
		Drawing::Text(text, Settings::titleText, { Settings::menuX - 0.175f, 0.090f }, { 0.425f, 0.425f }, true);
		Drawing::Spriter("CommonMenu", "", Settings::menuX - 0.175f, 0.1175f - 0.019f, 0.115f, 0.045f, 180, Settings::titleEnd.r, Settings::titleEnd.g, Settings::titleEnd.b, Settings::titleEnd.a);
	}
}
void GUI::AddSmallInfo(char* text, short line)
{
	if (GUI::Settings::menuX < 0.78f)
	{
		if (line == 1) {
			Drawing::Rect(Settings::optionRect, { Settings::menuX + 0.175f, ((17 * 0.035f) / 2.0f) + 0.163f - 0.135f }, { 0.115f, 17 * 0.035f + -0.193f });
		}
		Drawing::Text(text, Settings::count1, { Settings::menuX + 0.120f, (line * 0.020f) + 0.123f }, { 0.3f, 0.3f }, false);
	}
	else
	{
		if (line == 1) {
			Drawing::Rect(Settings::optionRect, { Settings::menuX - 0.175f, ((17 * 0.035f) / 2.0f) + 0.163f - 0.135f }, { 0.115f, 17 * 0.035f + -0.193f });
		}
		Drawing::Text(text, Settings::count1, { Settings::menuX - 0.228f, (line * 0.020f) + 0.123f }, { 0.3f, 0.3f }, false);
	}
}
void GUI::AddSmallTitle2(char* text)
{
	if (GUI::Settings::menuX < 0.78f)
	{
		Drawing::Text(text, Settings::titleText, { Settings::menuX + 0.175f, 0.090f }, { 0.425f, 0.425f }, true);
		Drawing::Spriter("CommonMenu", "", Settings::menuX + 0.175f, 0.1175f - 0.019f, 0.115f, 0.045f, 180, Settings::titleRect.r, Settings::titleRect.g, Settings::titleRect.b, Settings::titleRect.a);
	}
	else
	{
		Drawing::Text(text, Settings::titleText, { Settings::menuX - 0.175f, 0.090f }, { 0.425f, 0.425f }, true);
		Drawing::Spriter("CommonMenu", "", Settings::menuX - 0.175f, 0.1175f - 0.019f, 0.115f, 0.045f, 180, Settings::titleRect.r, Settings::titleRect.g, Settings::titleRect.b, Settings::titleRect.a);
	}
}

void GUI::AddSmallInfo2(char* text, short line)
{
	if (GUI::Settings::menuX < 0.78f)
	{
		if (line == 1) {
			Drawing::Rect(Settings::optionRect, { Settings::menuX + 0.175f, ((13 * 0.035f) / 2.0f) + 0.159f - 0.135f }, { 0.115f, 13 * 0.035f + -0.193f });
		}
		Drawing::Text(text, Settings::count, { Settings::menuX + 0.120f, (line * 0.020f) + 0.123f }, { 0.375f, 0.375f }, false);
	}
	else
	{
		if (line == 1) {
			Drawing::Rect(Settings::optionRect, { Settings::menuX - 0.175f, ((13 * 0.035f) / 2.0f) + 0.159f - 0.135f }, { 0.115f, 13 * 0.035f + -0.193f });
		}
		Drawing::Text(text, Settings::count, { Settings::menuX - 0.228f, (line * 0.020f) + 0.123f }, { 0.375f, 0.375f }, false);
	}
}

void GUI::AddSmallTitle3(char* text)
{
	if (GUI::Settings::menuX < 0.78f)
	{
		Drawing::Text(text, Settings::titleText, { Settings::menuX + 0.175f, 0.090f }, { 0.425f, 0.425f }, true);
		Drawing::Spriter("CommonMenu", "", Settings::menuX + 0.175f, 0.1175f - 0.019f, 0.115f, 0.045f, 180, Settings::titleRect.r, Settings::titleRect.g, Settings::titleRect.b, Settings::titleRect.a);
	}
	else
	{
		Drawing::Text(text, Settings::titleText, { Settings::menuX - 0.175f, 0.090f }, { 0.425f, 0.425f }, true);
		Drawing::Spriter("CommonMenu", "", Settings::menuX - 0.175f, 0.1175f - 0.019f, 0.115f, 0.045f, 180, Settings::titleRect.r, Settings::titleRect.g, Settings::titleRect.b, Settings::titleRect.a);
	}
}

void GUI::AddSmallInfo3(char* text, short line)
{
	if (GUI::Settings::menuX < 0.78f)
	{
		if (line == 1) {
			Drawing::Rect(Settings::optionRect, { Settings::menuX + 0.175f, ((11 * 0.035f) / 2.0f) + 0.159f - 0.135f }, { 0.115f, 11 * 0.035f + -0.193f });
		}
		Drawing::Text(text, Settings::count, { Settings::menuX + 0.120f, (line * 0.020f) + 0.123f }, { 0.375f, 0.375f }, false);
	}
	else
	{
		if (line == 1) {
			Drawing::Rect(Settings::optionRect, { Settings::menuX - 0.175f, ((11 * 0.035f) / 2.0f) + 0.159f - 0.135f }, { 0.115f, 11 * 0.035f + -0.193f });
		}
		Drawing::Text(text, Settings::count, { Settings::menuX - 0.228f, (line * 0.020f) + 0.123f }, { 0.375f, 0.375f }, false);
	}
}

void GUI::VehPix(char* _where, char* called, char* vehname)
{
	if (GUI::Settings::menuX < 0.78f)
	{
		Drawing::Text(vehname, Settings::titleText, { Settings::menuX + 0.175f, 0.090f }, { 0.425f, 0.425f }, true);
		Drawing::Spriter("CommonMenu", "", Settings::menuX + 0.175f, 0.1175f - 0.019f, 0.115f, 0.045f, 180, Settings::titleEnd.r, Settings::titleEnd.g, Settings::titleEnd.b, Settings::titleEnd.a);
		Drawing::Rect(Settings::optionRect, { Settings::menuX + 0.175f, ((17 * 0.035f) / 2.0f) + 0.159f - 0.135f }, { 0.115f, 17 * 0.035f + -0.193f });
		Drawing::Spriter(_where, called, 0.4f, 0.28f, 0.15f, 0.15f, 0, 255, 255, 255, 255);
	}
	else
	{
		Drawing::Text(vehname, Settings::titleText, { Settings::menuX - 0.175f, 0.090f }, { 0.425f, 0.425f }, true);
		Drawing::Spriter("CommonMenu", "", Settings::menuX - 0.175f, 0.1175f - 0.019f, 0.115f, 0.045f, 180, Settings::titleEnd.r, Settings::titleEnd.g, Settings::titleEnd.b, Settings::titleEnd.a);
		Drawing::Rect(Settings::optionRect, { Settings::menuX - 0.175f, ((17 * 0.035f) / 2.0f) + 0.159f - 0.135f }, { 0.115f, 17 * 0.035f + -0.193f });
		Drawing::Spriter(_where, called, 0.4f, 0.28f, 0.15f, 0.15f, 0, 255, 255, 255, 255);
	}
}

//bool Cursor::cursorOn = false;
//The main function of the cursor
//void Cursor::cursor() {
//	if (cursorOn) {
//		//Disable controls
//		CONTROLS::DISABLE_ALL_CONTROL_ACTIONS(0);
//		CONTROLS::DISABLE_ALL_CONTROL_ACTIONS(1);
//		CONTROLS::DISABLE_ALL_CONTROL_ACTIONS(2);
//		//Show the cursor
//		UI::_SET_CURSOR_SPRITE(5);
//		UI::_SHOW_CURSOR_THIS_FRAME();
//		if (Cursor::insideMenu()) {
//			Cursor::moveScroller();
//			//If you click on an option
//			if (GetAsyncKeyState(VK_LBUTTON)) {
//				GUI::Settings::selectPressed = true;
//			}
//			else {
//				GUI::Settings::selectPressed = false;
//			}
//		}
//	}
//	else {
//		CONTROLS::ENABLE_ALL_CONTROL_ACTIONS(0);
//		CONTROLS::ENABLE_ALL_CONTROL_ACTIONS(1);
//		CONTROLS::ENABLE_ALL_CONTROL_ACTIONS(2);
//	}
//}
//
////Get the position of the cursor
//POINT Cursor::cursorPos() {
//	POINT pt;
//	if (GetCursorPos(&pt) && Cursor::cursorOn) {
//		return pt;
//	}
//	else {
//		POINT fail = { 0, 0 };
//		return fail;
//	}
//}
//
////Checks if the cursor is inside the menu
//bool Cursor::insideMenu() {
//	if (Cursor::cursorOn) {
//		float cx = (float)Cursor::cursorPos().x;
//		float cy = (float)Cursor::cursorPos().y;
//		//The cursor position gets calculated differently than the menu position
//		//MenuPosition = (CursorPosition / 100) / 15
//		//CursorPosition = (MenuPosition * 100) * 15
//		float m1 = ((GUI::Settings::menuX * 100) * 15) - 155;
//		float m2 = ((GUI::Settings::menuX * 100) * 15) + 180;
//		//m1 = left menu border, m2 = right menu border
//		if (cx > m1 && cx < m2 && cy > Cursor::getMenuTop()) {
//			return true;
//		}
//		else {
//			return false;
//		}
//	}
//}
//
////The Y-coord of the menu top
//float Cursor::getMenuTop() {
//	return 146;
//}
//
////The height of one option
//float Cursor::getOptionHeight() {
//	return 31.193;
//}
//
////Returns the height of n options
//int optionHeight(int op) {
//	return Cursor::getMenuTop() + (Cursor::getOptionHeight() * op);
//}
//
////Returns the number of the option that the cursor is on
//int Cursor::onOption() {
//	float cy = (float)Cursor::cursorPos().y;
//	int count = GUI::Settings::optionCount;
//	if (Cursor::insideMenu()) {
//		for (int i = 0; i < 16; i++) {
//			if (cy > optionHeight(i) && cy < optionHeight(i + 1)) {
//				return i + 1;
//			}
//		}
//	}
//	else {
//		return -1;
//	}
//}
//
////Gets the options that are currently onscreen
//void Cursor::getOnscreenOptions(int &start, int &end) {
//	int count = GUI::Settings::optionCount;
//	int current = GUI::Settings::currentOption;
//	if (count < 17) {
//		start = 1;
//		end = count;
//	}
//	else {
//		if (current < 17) {
//			start = 1;
//			end = 16;
//		}
//		else {
//			start = current - 15;
//			end = current;
//		}
//	}
//}
//
////Moves the scroller
//void Cursor::moveScroller() {
//	//Saves the options that are onscreen in an array
//	int onscreen[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
//	int unused;
//	Cursor::getOnscreenOptions(onscreen[0], unused);
//	for (int i = 1; i < 16; i++) {
//		onscreen[i] = onscreen[i - 1] + 1;
//	}
//	//Breaks if an option-check is applied? if (onscreen[15] < GUI::Settings::optionCount)
//	//Sets the scroller to the specific option
//	//Cursor::onOption() ranges from 1 to 16; selects the index of the onscreen options
//	GUI::Settings::currentOption = onscreen[Cursor::onOption() - 1];
//}