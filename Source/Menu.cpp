#pragma once
#include "discord.h"
#include "stdafx.h"
#include "shellapi.h"
#include "Authh.h"
#include "Hashes.h"
#include <iostream>

#define PROP_MONEY_BAG_01 0x113FD533
#define PICKUP_MONEY_CASE 0xCE6FDD6B

#pragma warning (push)
#pragma warning (disable: 4305)
bool wallDrive = 0, Rainb = 0, Drift = 0, Gravity = 0, AirStrike = 0, forceog = 0, Rneon = 0, Rwheels = 0, ShootR = 0, NameESP = 0, Trigger = 0, Superr = 0,
UltraJ = 0, ShootT = 0, ShootTankR = 0, ShootBall = 0, ShootMini = 0, ShootWeaponT = 0, ShootHydra = 0, ShootDump = 0, ShootBuz = 0;
bool vehjump = 0, freezespawned = 0, numbersChanged = 0, playerGodMode = 0, cargodmodebool = 0, carlowerbool = 0, para = 0, savenewdrop21 = 0;
bool invis = 0;
bool Invisablecar = 0;
bool bulletTime = 0;
bool loop_SuperGrip = 0;
bool SuperGrip = 0, Analogo = 0;
bool stream = false;
bool Features::isSPBypass = true;
bool ak = false;
bool gg = false;
bool gg2 = false;
bool noRemoveWeps;
bool noGiveWeps;
bool AntiKick2;

float MoveX = 0.5f;
float MoveZ = 0.5f;


float runint = 1;


int Face_;
int tpgun;
int timeer;
int Armor_;
int intor;
int Glasses_;
int Ears_;
int Mask_;
int Hair_;
int Torso_;
int Legs_;
int Hands_;
int Shoes_;
int Watches_;
int Special1_;
int Special2_;
int Special3_;
int Texture_;
int Torso2_;
int primary, secondary;
int paint1, paint2;//pearl topcoat, wheel color
int ppaint1, ppaint2, ppaint3;

int playerAlpha = 250;
int speedRun = 1;
int headfont = 2;

long in = 0;
long out = 0;



Object latestObj;

ostringstream playerName;

Vehicle latestedveh;
Vehicle selectedveh;

Player playerId = PLAYER::PLAYER_ID();

std::string newName = "";
std::string namech;

vector<int> MapModObjs;

void welcome() {
	Player playerId = PLAYER::PLAYER_ID();
	playerName << "Logged in as: ~g~" << Hooking::get_player_name(playerId);
	notifyInfo((char*)playerName.str().c_str(), "Deny", "~g~v1.1.1");

	notifyInfo("Press F4 to Open Menu.", "Deny", "");

	GUI::Settings::titleText.f = 1;
	DiscordMain();
}

bool validateLogin() {

	if (!isCredsValid) {

		GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(1, "Username", "", "", "", "", "", 24);
		notifyInfo("~g~Enter your username", "Project", "Login");
		while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0) WAIT(0);
		if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()) return false;
		{
			username = GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
			GUI::Files::WriteStringToIni(username, authFile, "Login", "Username");
		}
		GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(1, "Password", "", "", "", "", "", 24);
		notifyInfo("~g~Enter your password", "Project", "Login");
		while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0) WAIT(0);
		if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()) return false;
		{
			password = GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
			GUI::Files::WriteStringToIni(password, authFile, "Login", "Password");
		}
		if (!isAuthValid(username, password)) {
			GUI::Files::WriteStringToIni("", authFile, "Login", "Username");
			GUI::Files::WriteStringToIni("", authFile, "Login", "Password");
			return false;
		}
		else {
			DiscordMain();
			welcome();
			return true;
		}
	}
	else {
		DiscordMain();
		welcome();
		return true;
	}
}

void isDead() {

	if (PLAYER::IS_PLAYER_DEAD(PLAYER::PLAYER_ID()))
	{

		GUI::MenuLevelHandler::MoveMenu(SubMenus::mainmenu);

	}
	
}

void main() {

	if (!validateLogin()) {
		notifyMap("~r~Invalid Credentials.\nMenu Unloaded.");
		Hooking::isRunning = false;
	}

	DiscordMain();

	while (true) {
		GUI::Checks::Keys();
		Features::UpdateLoop();
		//isDead();

		DiscordMain();

		switch (GUI::Settings::currentMenu) {

		case mainmenu:
		{
			GUI::Title("");
			GUI::Subtitle("Main Menu");
			GUI::MenuOption("Self", player);
			GUI::MenuOption("Network", network);
			GUI::MenuOption("Weapons", weapon);
			GUI::MenuOption("Vehicle Spawner", vehspawner);
			GUI::MenuOption("Vehicle Options", vehicle);
			GUI::MenuOption("Teleport", teleport);
			GUI::MenuOption("Recovery", recovery);
			GUI::MenuOption("Miscellaneous", misc);
			GUI::MenuOption("Protections", protections);
			GUI::MenuOption("Name Changer", name_changer);
			GUI::MenuOption("Settings", settings);

		}
		break;

#pragma region Player
		case player:
		{
			GUI::Title("");
			GUI::Subtitle("Self Options");
			GUI::MenuOption("Player Options", player_optionss);
			GUI::MenuOption("Player Movement", player_movement);
			GUI::MenuOption("Animation and Effects", animation_effects);
			GUI::MenuOption("Player Body Guards", bodyguard);
			GUI::MenuOption("Outfits", outfits);
			GUI::MenuOption("Model Changer", modelchanger);
			GUI::Break("Should Fix Black Screen For Now");
			GUI::Toggle("Semi God", Features::semigodself, [] { Features::SemiGodSelf(); });
		}
		break;

		case player_optionss:
		{
			GUI::Title("");
			GUI::Subtitle("Player Options");
			GUI::Toggle("God Mode", Features::playerGodMode, [] { Features::GodMode(Features::playerGodMode); });
			//GUI::Toggle("ForceField [NEW]", Features::playerForceField, [] { Features::ForceField(Features::playerForceField); });
			GUI::Toggle("Auto Regen Health", Features::isAutoRegHealth, [] { Features::AutoRegHealth(Features::isAutoRegHealth); });
			GUI::Toggle("Auto Regen Armour", Features::isAutoRegArmour, [] { Features::AutoRegArmour(Features::isAutoRegArmour); });
			GUI::Toggle("Auto Clean", Features::isAutoCleanPlayer, [] { Features::AutoCleanPlayer(Features::isAutoCleanPlayer); });
			GUI::Toggle("Never Wanted", Features::Neverwanted, [] { Features::NeverGetWanted(Features::Neverwanted); });
			GUI::Int("Wanted Level", Features::playerWantedLevel, 0, 5, [] { Features::ChangeWanted(Features::playerWantedLevel); });
			GUI::Toggle("Cops Turn Blind Eye", Features::Neverwanted2, [] { Features::NeverGetWanted(Features::Neverwanted2); });
			GUI::Toggle("Off the Radar [Lester]", Features::orbool, [] { Features::OffRadar(Features::orbool); });
			GUI::Toggle("Off the Radar [Fake-Death]", Features::DeathOffRadar);
			if (GUI::Option("Clean Player")) { Features::cleanSelf(); }
			if (GUI::Option("Heal Player")) { Features::healSelf(); }
			if (GUI::Option("Refresh Armour")) { Features::addArmour(); }
			GUI::Toggle("Tiny Player", Features::betiny, [] { Features::TinyPlayer(Features::betiny); });
			GUI::Toggle("Invisibility", Features::playerinvisibility, [] { Features::Invisibility(Features::playerinvisibility); });
			if (GUI::Int("Player Alpha", playerAlpha, 0, 250, 50)) {
				Entity ped = PLAYER::PLAYER_PED_ID();
				ENTITY::SET_ENTITY_ALPHA(ped, playerAlpha, 0);
			}
			if (GUI::Option("Commit Suicide")) { Features::suicide(); }
		}
		break;

		case player_movement:
		{
			GUI::Title("");
			GUI::Subtitle("Player Movement");
			GUI::Toggle("Super Jump", Features::playersuperjump, [] { Features::SuperJump(); });
			GUI::Toggle("Fast Run X2", Features::fastrun, [] { Features::RunFast(Features::fastrun); });
			if (GUI::Float("Fast Run Multiplier", Features::runint, 1, 10)) 
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Features::runint = Features::NumberKeyboard();
				}
				if (IsKeyPressed(VK_RETURN) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Features::runint = Features::NumberKeyboard();
				}
			}
			GUI::Toggle("Flash Run", Features::isFlashRun, [] { Features::flashRun(); });
			GUI::Toggle("Superman Mode", Features::supermanmode, [] { Features::Superman(Features::supermanmode); });
			GUI::Toggle("Walking No-Clip", Features::isWalkingNoClip, [] { Features::walkingNoClip(); });
			GUI::Toggle("No-Clip", Features::isNoClip, [] { Features::noClip(); });
			GUI::Toggle("No Ragdoll", Features::playernoragdoll, [] { Features::NoRagdoll(Features::playernoragdoll); });
			GUI::Toggle("Fast Swim", Features::fastswim, [] { Features::SwimFast(Features::fastswim); });
			if (GUI::Float("Fast Swim Multiplier", Features::swimint, 1, 10)) 
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Features::swimint = Features::NumberKeyboard();
				}
				if (IsKeyPressed(VK_RETURN) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Features::swimint = Features::NumberKeyboard();
				}
			}
		}
		break;

		case animation_effects:
		{
			GUI::Title("");
			GUI::Subtitle("Player Modifications");
			GUI::MenuOption("Self Animations", animations);
			GUI::MenuOption("Walking Animations", walkings);
			GUI::MenuOption("Particle Effects", ptfx);
			GUI::MenuOption("Visions", visions);
		}
		break;

#pragma endregion

#pragma region Weapons

		case weapon:
		{
			GUI::Title("Weapon Options");
			GUI::Subtitle("Weapon Options");
			GUI::MenuOption("Weapon Stash", weapon_stash);
			GUI::MenuOption("Ammo Modifiers", ammo_mods);
			GUI::MenuOption("Gun Modifiers", gun_mods);
			GUI::Toggle("Infinite Ammo", Features::infammo, [] { Features::noreloadv(Features::infammo); });
			//if (Features::menu_version == 2) {
			//	GUI::Toggle("Trigger Bot", Features::Trigger, [] { Features::TriggerAim(Features::Trigger); }); //VIP
			//}
			GUI::Toggle("Auto-Fire Weapon", Features::isAutoFire, [] { Features::autoFire(); });
			GUI::Toggle("Breathe Fire", Features::isBreatheFire, [] { Features::breatheFire(); });
			GUI::Toggle("Explosive Punch", Features::expmeel, [] {Features::Expmeels(); });
		}
		break;

#pragma endregion 

#pragma region Vehicle

		case vehicle:
		{
			GUI::Title("Vehicle Options");
			GUI::Subtitle("Vehicle Options");
			//GUI::MenuOption("Vehicle Spawner", vehspawner);
			GUI::MenuOption("Vehicle Aesthetics", vehicle_aesthetics);
			GUI::MenuOption("Vehicle Health", vehicle_health);
			GUI::MenuOption("Vehicle Multipliers", vehmult);
			GUI::MenuOption("Vehicle Movement", vehicle_movements);
			GUI::MenuOption("Vehicle Weapons", VehWeapon);
			/*GUI::MenuOption("Vehicle Manager", vehiclemanager);*/
			GUI::Break("Other Options");
			GUI::Toggle("Seatbelt", Features::seatbelt, [] { Features::seatBelt(Features::seatbelt); });
			if (GUI::Option("Delete Current Vehicle"))
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), true);
				VEHICLE::DELETE_VEHICLE(&veh);
			}
		}
		break;

#pragma endregion

#pragma region Teleports

		case teleport:
		{
			GUI::Title("Teleport Options");
			GUI::Subtitle("Teleport Options");
			if (GUI::Option("Teleport to Waypoint")) {
				Features::teleportToWaypoint();
			}
			if (GUI::Option("Teleport to Objective")) {
				Features::teleportToObjective();
			}
			if (GUI::Option("Teleport Forward")) {
				Features::teleportForward();
			}
			if (GUI::Option("Teleport to Nearby Vehicle")) {
				Features::teleportToNearbyCar();
			}
			GUI::Break("Teleport Locations");
			GUI::MenuOption("Bunkers", tpbunkers);
			GUI::MenuOption("High Places", tphigh);
			GUI::MenuOption("Indoors", tpindoors);
			GUI::MenuOption("IPLs", tpipls);
			GUI::MenuOption("Landmarks", tplandmarks);
			GUI::MenuOption("Safehouses", tpsafehouses);
			GUI::MenuOption("Under Water", tpunderwater);
		}
		break;

#pragma endregion

#pragma region Network

		case network:
		{
			GUI::Title("");
			GUI::Subtitle("Network Options");
			GUI::MenuOption("All Players", troll_all_players);
			GUI::MenuOption("Player List", onlinemenu_playerlist);
			//GUI::MenuOption("Online Protections", protections);
			//GUI::MenuOption("Name Changer", name_changer);
			GUI::MenuOption("Online Mods", session_mods);
			//GUI::Toggle("Airport Drop", Features::moneydropL1);
			
		}
		break;

#pragma endregion

#pragma region Recovery

		case recovery:
		{
			GUI::Title("");
			GUI::Subtitle("Recovery Options");
			GUI::MenuOption("Cash", stealth);
			GUI::MenuOption("Rank", rp);
			GUI::MenuOption("Unlocks", unlocks);
			GUI::MenuOption("Stats Editor", statsEdit);
			GUI::Break("-----------------------");
			if (GUI::Option("Combat Roll + Recoil")) {
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SHOOTING_ABILITY"), 150, 0);
				notifyInfo("Modded Combat Rolls + No Recoil Set", "", "");
			}
			if (GUI::Option("Clear Reports")) {
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_REPORT_STRENGTH"), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_COMMEND_STRENGTH"), 100, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_FRIENDLY"), 100, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_HELPFUL"), 100, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_GRIEFING"), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_VC_ANNOYINGME"), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_VC_HATE"), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_OFFENSIVE_LANGUAGE"), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_OFFENSIVE_TAGPLATE"), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_OFFENSIVE_UGC"), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_NAME"), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_MOTTO"), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_STATUS"), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_EMBLEM"), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_GAME_EXPLOITS"), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_EXPLOITS"), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_ISPUNISHED"), 0, 1);
				notifyInfo("Clear Reports Done Enjoy", "", "");
			}
			if (GUI::Option("Remove Bad Sport")) {
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_BAD_SPORT_BITSET"), 0, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_WAS_I_BAD_SPORT"), 0, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_OVERALL_BADSPORT"), 0, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_CHAR_IS_BADSPORT"), 0, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_BECAME_BADSPORT_NUM"), 0, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_DESTROYED_PVEHICLES"), 0, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_REPORT_STRENGTH"), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_COMMEND_STRENGTH"), 100, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_FRIENDLY"), 100, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_HELPFUL"), 100, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_GRIEFING"), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_VC_ANNOYINGME"), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_VC_HATE"), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_OFFENSIVE_LANGUAGE"), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_OFFENSIVE_TAGPLATE"), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_OFFENSIVE_UGC"), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_NAME"), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_MOTTO"), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_STATUS"), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_EMBLEM"), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_GAME_EXPLOITS"), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_EXPLOITS"), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_ISPUNISHED"), 0, 1);
				notifyInfo("Removed Bad Sport!", "", "");
			}
		}
		break;

#pragma endregion

#pragma region Miscellaneous

		case misc:
		{
			GUI::Title("");
			GUI::Subtitle("Miscellaneous Options");
			GUI::MenuOption("Map Mods", mapmods);
			GUI::MenuOption("Time [Local]", time_mods);
			GUI::MenuOption("Weathers [Local]", weatheroptions);
			GUI::MenuOption("Nearby Entities", nearby_entities);
			//GUI::MenuOption("Object Spawner", object_spawner);
			GUI::Toggle("Blackout [Local]", Features::isBlackout, [] { Features::blackOut(); });
			GUI::Toggle("Mobile Radio", Features::mobileRadio, [] { Features::mobilevoid(Features::mobileRadio); });
			GUI::Toggle("Rain Rockets", Features::isRainRockets, [] { Features::rainRockets(Features::isRainRockets); });
			GUI::Toggle("Meteor Shower", Features::AsteroidShower, [] { Features::AsteroidShowerToggle(Features::AsteroidShower); });
			//GUI::Toggle("Heli Bomber", Features::bomber, [] { Features::bomber_mode(Features::bomber); }); //VIP
			GUI::Toggle("Freecam", Features::free_cam, [] { Features::freecam(Features::free_cam); });
		}
		break;

#pragma endregion

#pragma region Settings

		case settings:
		{
			GUI::Title("");
			GUI::Subtitle("Settings");
			GUI::Float("Menu Position", GUI::Settings::menuX, 0.15f, 0.85f, 0.05f);
			if (GUI::Int("Scroll Delay", GUI::Settings::keyPressDelay2, 1, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::keyPressDelay2 = Features::NumberKeyboard();
				}
			}
			if (GUI::Int("Int Delay", GUI::Settings::keyPressDelay3, 1, 200))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::keyPressDelay3 = Features::NumberKeyboard();
				}
			}
			if (Features::menu_version == 2) {
				GUI::MenuOption("UI Customization", guicustm); //VIP
			}
			GUI::Toggle("Display FPS", Features::DisplayFPS, [] { Features::featureDisplayFPS(Features::DisplayFPS); });
			GUI::Toggle("Display Lobby Info", Features::DisplayShowinfo, [] { Features::FeatureDisplayShowInfo(Features::DisplayShowinfo); });
			GUI::MenuOption("Credits", creds);
			GUI::MenuOption("Exit Game", exitgta);
			/*if (GUI::Option("Unload Project (Buggy)"))
			{
				notifyMap("Unloading...");
				Hooking::isRunning = false;
				notifyMap("~r~Menu Unloaded");
			}*/
		}
		break;

		case creds:
		{
			GUI::Title("");
			GUI::Subtitle("Project Credits");

			if (GUI::Option("Neger")) 
			{
				notifyInfo("Good Guy!", "", "");
			}
			if (GUI::Option("Schlampe"))
			{
				notifyInfo("Not Owner!", "", "");
			}
		}
		break;

		case guicustm:
		{
			GUI::Title("");
			GUI::Subtitle("GUI Customizer");
			GUI::MenuOption("Header Stuff", headerctm);
			GUI::MenuOption("Colors", settingstheme);
			//GUI::MenuOption("Text Font", font);
		}
		break;

		case headerctm:
		{
			GUI::Title("");
			GUI::Subtitle("Header");
			if (GUI::Option("Normal Banner"))
			{
			    Features::spacetheme = true;
				Features::Rainbowmenu2 = false;
				Features::customtheme = false;
			}
			if (GUI::Option("Rainbow Banner"))
			{
				Features::spacetheme = false;
				Features::Rainbowmenu2 = true;
				Features::customtheme = false;
			}
			if (GUI::Option("Custom"))
			{
				Features::spacetheme = false;
				Features::Rainbowmenu2 = false;
				Features::customtheme = true;
			}
			GUI::MenuOption("Custom header", cstmhead);
			GUI::Toggle("Globe", Features::globe);
		}
		break;


		case cstmhead:
		{
			GUI::Title("");
			GUI::Subtitle("Custom Header");
			if (GUI::Int("Header Text Font", headfont, 0, 7, 1)) {
				GUI::Settings::titleText.f = headfont;
			}
			GUI::Break("Header Text Color");
			if (GUI::Int("Red", GUI::Settings::titleText.r, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::titleRect.r = Features::NumberKeyboard();
				}
				if (IsKeyPressed(VK_RETURN) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::titleRect.r = Features::NumberKeyboard();
				}
			}
			if (GUI::Int("Green", GUI::Settings::titleText.g, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::titleRect.g = Features::NumberKeyboard();
				}
				if (IsKeyPressed(VK_RETURN) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::titleRect.g = Features::NumberKeyboard();
				}
			}
			if (GUI::Int("Blue", GUI::Settings::titleText.b, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::titleRect.b = Features::NumberKeyboard();
				}
				if (IsKeyPressed(VK_RETURN) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::titleRect.b = Features::NumberKeyboard();
				}
			}
			GUI::Break("Header Background Color");
			if (GUI::Int("Red", GUI::Settings::titleRect.r, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::titleRect.r = Features::NumberKeyboard();
				}
				if (IsKeyPressed(VK_RETURN) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::titleRect.r = Features::NumberKeyboard();
				}
			}
			if (GUI::Int("Green", GUI::Settings::titleRect.g, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::titleRect.g = Features::NumberKeyboard();
				}
				if (IsKeyPressed(VK_RETURN) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::titleRect.g = Features::NumberKeyboard();
				}
			}
			if (GUI::Int("Blue", GUI::Settings::titleRect.b, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::titleRect.b = Features::NumberKeyboard();
				}
				if (IsKeyPressed(VK_RETURN) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::titleRect.b = Features::NumberKeyboard();
				}
			}
			if (GUI::Int("Opacity", GUI::Settings::titleRect.a, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::titleRect.a = Features::NumberKeyboard();
				}
				if (IsKeyPressed(VK_RETURN) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::titleRect.a = Features::NumberKeyboard();
				}
			}
		}
		break;

		case exitgta:
		{
			GUI::Title("Exit GTA V");
			GUI::Subtitle("Exit GTA V");
			if (GUI::Option("Yes")) exit(0);
			if (GUI::Option("No")) GUI::MenuLevelHandler::BackMenu();
		}
		break;

		case settingstheme:
		{
			GUI::Title("Colors");
			GUI::Subtitle("Colors");
			//GUI::MenuOption("Theme Loader", themeloader);
			GUI::MenuOption("Selected Item Color", settingsscroller);
			GUI::MenuOption("Option Text Color", settingsoptiontext);
			GUI::MenuOption("Selected Text Color", settingsoptiontext2);
			GUI::MenuOption("Break Text Color", settingsbreaktext);
			//GUI::Toggle("Rainbow Menu", Features::rainbowmenu, [] { Features::Rainbowmenu(Features::rainbowmenu); });
		}
		break;

#pragma endregion

// ------------------------------ Sub Menus --------------------------------- //

#pragma region Player SubMenus

#pragma region Model Changer
		case modelchanger:
		{
			GUI::Title("Model Changer");
			GUI::Subtitle("Model Changer");
			GUI::MenuOption("Normal Models", animalsped);
			GUI::MenuOption("Animal Models", modelsped);
		}
		break;

		case animalsped:
		{
			GUI::Title("Animal Models");
			GUI::Subtitle("Animal Models");
			for (int i = 0; i < ARRAYSIZE(Hashes::animalsModels); i++)
			{
				if (GUI::Option(Hashes::animalsModels[i]))
				{
					DWORD model = GAMEPLAY::GET_HASH_KEY(Hashes::animalsModels[i]);
					STREAMING::REQUEST_MODEL(model);
					while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
					PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), model);
					PED::SET_PED_DEFAULT_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID());
					WAIT(10);
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
					WAIT(10);
				}
			}
		}
		break;

		case modelsped:
		{
			GUI::Title("Normal Models");
			GUI::Subtitle("Normal Models");
			for (int i = 0; i < ARRAYSIZE(Hashes::pedModels); i++)
			{
				if (GUI::Option(Hashes::pedModels[i]))
				{
					DWORD model = GAMEPLAY::GET_HASH_KEY(Hashes::pedModels[i]);
					STREAMING::REQUEST_MODEL(model);
					while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
					PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), model);
					PED::SET_PED_DEFAULT_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID());
					WAIT(10);
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
					WAIT(10);
				}
			}
		}
		break;
#pragma endregion

#pragma region Self Animations
		case animations:
		{
			GUI::Title("Player Animations");
			GUI::Subtitle("Player Animations");
			GUI::MenuOption("Scenarios", scenarios);
			if (GUI::Option("Clear Animation")) { Features::clearanim(); }
			if (GUI::Option("S** Receiver")) { Features::doAnimation("rcmpaparazzo_2", "shag_loop_poppy"); }
			if (GUI::Option("S** Giver")) { Features::doAnimation("rcmpaparazzo_2", "shag_loop_a"); }
			if (GUI::Option("Stripper Dance")) { Features::doAnimation("mini@strip_club@private_dance@part1", "priv_dance_p1"); }
			if (GUI::Option("Pole Dance")) { Features::doAnimation("mini@strip_club@pole_dance@pole_dance1", "pd_dance_01"); }
			if (GUI::Option("Push Ups")) { Features::doAnimation("amb@world_human_push_ups@male@base", "base"); }
			if (GUI::Option("Sit Ups")) { Features::doAnimation("amb@world_human_sit_ups@male@base", "base"); }
			if (GUI::Option("Celebrate")) { Features::doAnimation("rcmfanatic1celebrate", "celebrate"); }
			if (GUI::Option("Electrocution")) { Features::doAnimation("ragdoll@human", "electrocute"); }
			if (GUI::Option("Suicide")) { Features::doAnimation("mp_suicide", "pistol"); }
			if (GUI::Option("Showering")) { Features::doAnimation("mp_safehouseshower@male@", "male_shower_idle_b"); }
		}
		break;
#pragma endregion

#pragma region Walking Animations

		case walkings:
		{
			Ped ped = PLAYER::PLAYER_PED_ID();

			GUI::Title("");
			GUI::Subtitle("Walking Animations");
			if (GUI::Option("Reset Walk Style")) {
				PED::RESET_PED_MOVEMENT_CLIPSET(ped, 0);
			}
			if (GUI::Option("Male Default")) { Features::setPlayerWalkingStyle("move_m@generic"); }
			if (GUI::Option("Female Default")) { Features::setPlayerWalkingStyle("move_f@generic"); }
			if (GUI::Option("Fat Fuck")) { Features::setPlayerWalkingStyle("move_m@fat@a"); }
			if (GUI::Option("Drunk")) { Features::setPlayerWalkingStyle("move_m@drunk@verydrunk"); }
			if (GUI::Option("Gangster")) { Features::setPlayerWalkingStyle("move_m@gangster@var_e"); }
			if (GUI::Option("Injured")) { Features::setPlayerWalkingStyle("move_m@injured"); }
			if (GUI::Option("Business Man")) { Features::setPlayerWalkingStyle("move_m@business@a"); }
			if (GUI::Option("Hiker")) { Features::setPlayerWalkingStyle("move_m@hiking"); }
			if (GUI::Option("Running")) { Features::setPlayerWalkingStyle("move_f@film_reel"); }
		}
		break;

#pragma endregion

#pragma region Scenarios
		case scenarios:
		{
			GUI::Title("Player Scenarios");
			GUI::Subtitle("Player Scenarios");
			if (GUI::Option("Kill Animation")) AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
			if (GUI::Option("Paparazzi")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_PAPARAZZI", 0, true);
			if (GUI::Option("Drug Dealer")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_DRUG_DEALER_HARD", 0, true);
			if (GUI::Option("Drinking Coffee")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_AA_COFFEE", 0, true);
			if (GUI::Option("Playing Instruments")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_MUSICIAN", 0, true);
			if (GUI::Option("Flexing")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_MUSCLE_FLEX", 0, true);
			if (GUI::Option("Jogging")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_JOG_STANDING", 0, true);
			if (GUI::Option("Binoculars")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_BINOCULARS", 0, true);
			if (GUI::Option("Clipboard")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_CLIPBOARD", 0, true);
			if (GUI::Option("Bench Press")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_MUSCLE_BENCH_PRESS", 0, true);
			if (GUI::Option("Chin Ups")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_MUSCLE_CHIN_UPS", 0, true);
			if (GUI::Option("BBQ")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_BBQ", 0, true);
			if (GUI::Option("Superhero")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SUPERHERO", 0, true);
			if (GUI::Option("Fishing")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_STAND_FISHING", 0, true);
			if (GUI::Option("Security")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SECURITY_SHINE_TORCH", 0, true);
			if (GUI::Option("Leaf Blower")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_GARDENER_LEAF_BLOWER", 0, true);
			if (GUI::Option("Film Shocking")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_MOBILE_FILM_SHOCKING", 0, true);
			if (GUI::Option("Idle Cop")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_COP_IDLES", 0, true);
			if (GUI::Option("Drinking")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_DRINKING", 0, true);
			if (GUI::Option("Golf Player")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_GOLF_PLAYER", 0, true);
			if (GUI::Option("Welding")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_WELDING", 0, true);
			if (GUI::Option("Smoking Pot")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SMOKING_POT", 0, true);
			if (GUI::Option("Hammering")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_HAMMERING", 0, true);
			if (GUI::Option("Tennis")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_TENNIS_PLAYER", 0, true);
			if (GUI::Option("Drilling")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_CONST_DRILL", 0, true);
		}
		break;
#pragma endregion

#pragma region Effects

		case ptfx:
		{
			GUI::Title("Player Effects");
			GUI::Subtitle("Player Effects");
			GUI::Toggle("Clown 1", Features::isClownEffect);
			GUI::Toggle("Clown 2", Features::isClown2Effect);
			GUI::Toggle("Firework", Features::isFireworkEffect);
			GUI::Toggle("Alien 1", Features::isAlienEffect);
			GUI::Toggle("Alien 2", Features::isAlien2Effect);
			GUI::Toggle("Electric Smoke", Features::isElectricEffect);
			GUI::Toggle("Lightning", Features::isElectric2Effect);
			GUI::Toggle("Water Splash", Features::isWaterEffect);
			GUI::Toggle("Smoke", Features::isSmokeEffect);
		}
		break;

#pragma endregion

#pragma region Visions
		case visions:
			GUI::Title("");
			GUI::Subtitle("Vision Menu");
			if (GUI::Option("Default")) { GRAPHICS::SET_TIMECYCLE_MODIFIER("DEFAULT"); }
			if (GUI::Option("Drunk")) { GRAPHICS::SET_TIMECYCLE_MODIFIER("Drunk"); }
			if (GUI::Option("Stoned")) { GRAPHICS::SET_TIMECYCLE_MODIFIER("stoned"); }
			if (GUI::Option("Orange")) { GRAPHICS::SET_TIMECYCLE_MODIFIER("REDMIST"); }
			if (GUI::Option("Death")) { GRAPHICS::SET_TIMECYCLE_MODIFIER("DEATH"); }
			if (GUI::Option("Drugs")) { GRAPHICS::SET_TIMECYCLE_MODIFIER("drug_flying_base"); }
			if (GUI::Option("Huffin Gas")) { GRAPHICS::SET_TIMECYCLE_MODIFIER("DRUG_gas_huffin"); }
			if (GUI::Option("Tipsy")) { GRAPHICS::SET_TIMECYCLE_MODIFIER("drug_wobbly"); }
			if (GUI::Option("Heaven")) { GRAPHICS::SET_TIMECYCLE_MODIFIER("Bloom"); }
			if (GUI::Option("Fancy")) { GRAPHICS::SET_TIMECYCLE_MODIFIER("PlayerSwitchPulse"); }
			if (GUI::Option("Hallucinations")) { GRAPHICS::SET_TIMECYCLE_MODIFIER("player_transition"); }
			if (GUI::Option("Killstreak")) { GRAPHICS::SET_TIMECYCLE_MODIFIER("MP_Killstreak"); }
			if (GUI::Option("Low Quality")) { GRAPHICS::SET_TIMECYCLE_MODIFIER("cinema_001"); }
			if (GUI::Option("Blurry")) { GRAPHICS::SET_TIMECYCLE_MODIFIER("CHOP"); }
			if (GUI::Option("Blinding")) { GRAPHICS::SET_TIMECYCLE_MODIFIER("BarryFadeOut"); }

			break;
#pragma endregion

#pragma region Body Guards
		case bodyguard:
		{
			GUI::Title("");
			GUI::Subtitle("Body Guards");
			int clone[1000];
			int gcount = 1;
			if (GUI::Option("Spawn Jesus w/ Assault Rifle")) {
				Ped selectedplayer = PLAYER::PLAYER_PED_ID();
				if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
				Hash rifle = GAMEPLAY::GET_HASH_KEY("WEAPON_ASSAULTRIFLE");
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
				Hash pedm = GAMEPLAY::GET_HASH_KEY("u_m_m_jesus_01");
				STREAMING::REQUEST_MODEL(pedm);
				while (!STREAMING::HAS_MODEL_LOADED(pedm))
					WAIT(0);
				int my_group = PLAYER::GET_PLAYER_GROUP(selectedplayer);
				clone[gcount] = PED::CREATE_PED(26, pedm, pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 1, 0, 1, 1);
				PED::SET_PED_AS_GROUP_LEADER(selectedplayer, my_group);
				PED::SET_PED_AS_GROUP_MEMBER(clone[gcount], my_group);
				PED::SET_PED_NEVER_LEAVES_GROUP(clone[gcount], my_group);
				PED::SET_PED_COMBAT_ABILITY(clone[gcount], 100);
				WEAPON::GIVE_WEAPON_TO_PED(clone[gcount], rifle, rifle, 9999, 9999);
				PED::SET_PED_CAN_SWITCH_WEAPON(clone[gcount], true);
				PED::SET_GROUP_FORMATION(my_group, 3);
				PED::SET_PED_MAX_HEALTH(clone[gcount], 5000);
				gcount++;
			}
			if (GUI::Option("Spawn Alien w/ Railgun")) {
				Ped selectedplayer = PLAYER::PLAYER_PED_ID();
				if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
				Hash railgun = GAMEPLAY::GET_HASH_KEY("WEAPON_RAILGUN");
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
				Hash pedm = GAMEPLAY::GET_HASH_KEY("s_m_m_movalien_01");
				STREAMING::REQUEST_MODEL(pedm);
				while (!STREAMING::HAS_MODEL_LOADED(pedm))
					WAIT(0);
				int my_group = PLAYER::GET_PLAYER_GROUP(selectedplayer);
				clone[gcount] = PED::CREATE_PED(26, pedm, pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 1, 0, 1, 1);
				PED::SET_PED_AS_GROUP_LEADER(selectedplayer, my_group);
				PED::SET_PED_AS_GROUP_MEMBER(clone[gcount], my_group);
				PED::SET_PED_NEVER_LEAVES_GROUP(clone[gcount], my_group);
				PED::SET_PED_COMBAT_ABILITY(clone[gcount], 100);
				WEAPON::GIVE_WEAPON_TO_PED(clone[gcount], railgun, railgun, 9999, 9999);
				PED::SET_PED_CAN_SWITCH_WEAPON(clone[gcount], true);
				PED::SET_GROUP_FORMATION(my_group, 3);
				PED::SET_PED_MAX_HEALTH(clone[gcount], 5000);
				gcount++;
			}
			if (GUI::Option("Spawn Marine w/ Combat MG")) {
				Ped selectedplayer = PLAYER::PLAYER_PED_ID();
				if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
				Hash combatmg = GAMEPLAY::GET_HASH_KEY("WEAPON_COMBATMG");
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
				Hash pedm = GAMEPLAY::GET_HASH_KEY("s_m_m_marine_02");
				STREAMING::REQUEST_MODEL(pedm);
				while (!STREAMING::HAS_MODEL_LOADED(pedm))
					WAIT(0);
				int my_group = PLAYER::GET_PLAYER_GROUP(selectedplayer);
				clone[gcount] = PED::CREATE_PED(26, pedm, pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 1, 0, 1, 1);
				PED::SET_PED_AS_GROUP_LEADER(selectedplayer, my_group);
				PED::SET_PED_AS_GROUP_MEMBER(clone[gcount], my_group);
				PED::SET_PED_NEVER_LEAVES_GROUP(clone[gcount], my_group);				
				PED::SET_PED_COMBAT_ABILITY(clone[gcount], 100);
				WEAPON::GIVE_WEAPON_TO_PED(clone[gcount], combatmg, combatmg, 9999, 9999);
				PED::SET_PED_CAN_SWITCH_WEAPON(clone[gcount], true);
				PED::SET_GROUP_FORMATION(my_group, 3);
				PED::SET_PED_MAX_HEALTH(clone[gcount], 5000);
				gcount++;
			}
			if (GUI::Option("Spawn Stripper w/ Heavy Sniper")) {
				Ped selectedplayer = PLAYER::PLAYER_PED_ID();
				if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
				Hash heavysniper = GAMEPLAY::GET_HASH_KEY("WEAPON_HEAVYSNIPER");
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
				Hash pedm = GAMEPLAY::GET_HASH_KEY("csb_stripper_01");
				STREAMING::REQUEST_MODEL(pedm);
				while (!STREAMING::HAS_MODEL_LOADED(pedm))
					WAIT(0);
				int my_group = PLAYER::GET_PLAYER_GROUP(selectedplayer);
				clone[gcount] = PED::CREATE_PED(26, pedm, pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 1, 0, 1, 1);
				PED::SET_PED_AS_GROUP_LEADER(selectedplayer, my_group);
				PED::SET_PED_AS_GROUP_MEMBER(clone[gcount], my_group);
				PED::SET_PED_NEVER_LEAVES_GROUP(clone[gcount], my_group);
				PED::SET_PED_COMBAT_ABILITY(clone[gcount], 100);
				WEAPON::GIVE_WEAPON_TO_PED(clone[gcount], heavysniper, heavysniper, 9999, 9999);
				PED::SET_PED_CAN_SWITCH_WEAPON(clone[gcount], true);
				PED::SET_GROUP_FORMATION(my_group, 3);
				PED::SET_PED_MAX_HEALTH(clone[gcount], 5000);
				gcount++;
			}
			if (GUI::Option("Spawn Merry Weather w/ Mini Gun")) {
				Ped selectedplayer = PLAYER::PLAYER_PED_ID();
				if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
				Hash minigun = GAMEPLAY::GET_HASH_KEY("WEAPON_MINIGUN");
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
				Hash pedm = GAMEPLAY::GET_HASH_KEY("csb_mweather");
				STREAMING::REQUEST_MODEL(pedm);
				while (!STREAMING::HAS_MODEL_LOADED(pedm))
					WAIT(0);
				int my_group = PLAYER::GET_PLAYER_GROUP(selectedplayer);
				clone[gcount] = PED::CREATE_PED(26, pedm, pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 1, 0, 1, 1);
				PED::SET_PED_AS_GROUP_LEADER(selectedplayer, my_group);
				PED::SET_PED_AS_GROUP_MEMBER(clone[gcount], my_group);
				PED::SET_PED_NEVER_LEAVES_GROUP(clone[gcount], my_group);
				PED::SET_PED_COMBAT_ABILITY(clone[gcount], 100);
				WEAPON::GIVE_WEAPON_TO_PED(clone[gcount], minigun, minigun, 9999, 9999);
				PED::SET_PED_CAN_SWITCH_WEAPON(clone[gcount], true);
				PED::SET_GROUP_FORMATION(my_group, 3);
				PED::SET_PED_MAX_HEALTH(clone[gcount], 5000);
				gcount++;
			}
			if (GUI::Option("Spawn FIB Agent w/ RPG")) {
				Ped selectedplayer = PLAYER::PLAYER_PED_ID();
				if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
				Hash rpg = GAMEPLAY::GET_HASH_KEY("WEAPON_RPG");
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
				Hash pedm = GAMEPLAY::GET_HASH_KEY("s_m_m_fiboffice_01");
				STREAMING::REQUEST_MODEL(pedm);
				while (!STREAMING::HAS_MODEL_LOADED(pedm))
					WAIT(0);
				int my_group = PLAYER::GET_PLAYER_GROUP(selectedplayer);
				clone[gcount] = PED::CREATE_PED(26, pedm, pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 1, 0, 1, 1);
				PED::SET_PED_AS_GROUP_LEADER(selectedplayer, my_group);
				PED::SET_PED_AS_GROUP_MEMBER(clone[gcount], my_group);
				PED::SET_PED_NEVER_LEAVES_GROUP(clone[gcount], my_group);
				PED::SET_PED_COMBAT_ABILITY(clone[gcount], 100);
				WEAPON::GIVE_WEAPON_TO_PED(clone[gcount], rpg, rpg, 9999, 9999);
				PED::SET_PED_CAN_SWITCH_WEAPON(clone[gcount], true);
				PED::SET_GROUP_FORMATION(my_group, 3);
				PED::SET_PED_MAX_HEALTH(clone[gcount], 5000);
				gcount++;
			}
		}
		break;
#pragma endregion

#pragma region Outfits
		case outfits:
		{
			GUI::Title("Outfit Creator");
			GUI::Subtitle("Outfit Creator");
			GUI::Int("Hats", Face_, 0, 55); { PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 0, Face_, 0, 1); }
			GUI::Int("Glasses", Glasses_, 0, 23); { PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 1, Glasses_, 0, 1); }
			GUI::Int("Ears", Ears_, 0, 3); { PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 2, Ears_, 0, 1); }
			GUI::Int("Torso invisible", Torso_, 0, 50); { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 3, Torso_, 0, 1); }
			GUI::Int("Torso", Torso2_, 0, 50); { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 11, Torso2_, 0, 1); }
			GUI::Int("Legs", Legs_, 0, 50); { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 4, Legs_, 0, 1); }
			GUI::Int("Hands", Hands_, 0, 50); { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 5, Hands_, 0, 1); }
			GUI::Int("Watches", Watches_, 0, 50); { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 6, Watches_, 0, 1); }
			GUI::Int("Special 1", Special1_, 0, 50); { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 7, Special1_, 0, 1); }
			GUI::Int("Special 2", Special2_, 0, 50); { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 8, Special2_, 0, 1); }
			GUI::Int("Special 3", Special3_, 0, 50); { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 9, Special3_, 0, 1); }
			GUI::Int("Texture", Texture_, 0, 50); { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 10, Texture_, 0, 1); }
			GUI::Break("Pre-Made Outfits");
			if (GUI::Option("Police Officer")) {
				Swat();
			}
		}
			break;
#pragma endregion

#pragma region Weapon Stash
		case weapon_stash:
		{
			GUI::Title("");
			GUI::Subtitle("Weapon Stash");
			GUI::MenuOption("MK2 Options", custom_mk2);
			if (GUI::Option("Give All Weapons")) {
				std::vector<uint> Weapons{
					0x92A27487, 0x958A4A8F, 0xF9E6AA4B, 0x84BD7BFD, 0xA2719263, 0x8BB05FD7, 0x440E4788, 0x4E875F73, 0xF9DCBF2D, 0xD8DF3C3C, 0x99B507EA, 0xDD5DF8D9, 0xDFE37640, 0x678B81B1, 0x19044EE0, 0xCD274149, 0x94117305, 0x3813FC08, // Melee
					0x1B06D571, 0xBFE256D4, 0x5EF9FEC4, 0x22D8FE39, 0x3656C8C1, 0x99AEEB3B, 0xBFD21232, 0x88374054, 0xD205520E, 0x83839C4, 0x47757124, 0xDC4DB296, 0xC1B3C3D1, 0xCB96392F, 0x97EA20B8, // Handguns
					0x13532244, 0x2BE6766B, 0x2BE6766B, 0xEFE7E2DF, 0x0A3D4D34, 0xDB1AA450, 0xBD248B55, // Submachine Guns
					0x1D073A89, 0x555AF99A, 0x7846A318, 0xE284C527, 0x9D61E50F, 0xA89CB99E, 0x3AABBBAA, 0xEF951FBB, 0x12E82D3D, // Shotguns
					0xBFEFFF6D, 0x394F415C, 0x83BF0278, 0xFAD1F1C9, 0xAF113F99, 0xC0A3098D, 0x969C3D67, 0x7F229F94, 0x84D6FAFD, 0x624FE830, // Assault Rifles
					0x9D07F764, 0x7FD62962, 0xDBBD7280, 0x61012683, // Light Machine Guns
					0x05FC3C11, 0x0C472FE2, 0xA914799, 0xC734385A, 0x6A6C02E0, // Sniper Rifles
					0xB1CA77B1, 0xA284510B, 0x4DD2DC56, 0x42BF8A85, 0x7F7497E5, 0x6D544C99, 0x63AB0442, 0x0781FE4A, // Heavy Weapons
					0x93E220BD, 0xA0973D5E, 0x24B17070, 0x2C3731D9, 0xAB564B93, 0x787F0BB, 0xBA45E8B8, 0x23C9F95C, 0xFDBC8A50, 0x497FACC3, // Throwables
					0x34A67B97, 0xFBAB5776, 0x060EC506, // Miscellaneous
					0x476BF155, 0xAF3696A1, 0xB62D1F67 // Arena Wars
				};

				for (Hash hash : Weapons)
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), hash, 9999, 0);
			}
			if (GUI::Option("Give All MK1 Weapons")) {
				std::vector<uint> Weapons{
					0x99B507EA, 0x678B81B1, 0x4E875F73, 0x958A4A8F, 0x3813FC08, 0x440E4788, 0x84BD7BFD, 0x1B06D571, 0x5EF9FEC4,
					0x22D8FE39, 0x99AEEB3B, 0x13532244, 0x2BE6766B, 0xEFE7E2DF, 0xBFEFFF6D, 0x83BF0278, 0xAF113F99, 0x9D07F764,
					0x7FD62962, 0x1D073A89, 0x7846A318, 0xE284C527, 0x9D61E50F, 0x3656C8C1, 0x05FC3C11, 0x0C472FE2, 0x33058E22,
					0xA284510B, 0x4DD2DC56, 0xB1CA77B1, 0x687652CE, 0x42BF8A85, 0x93E220BD, 0x2C3731D9, 0xFDBC8A50, 0x24B17070,
					0x060EC506, 0x34A67B97, 0xFDBADCED, 0x23C9F95C, 0x497FACC3, 0xF9E6AA4B, 0x61012683, 0xC0A3098D, 0xD205520E,
					0xBFD21232, 0x7F229F94, 0x92A27487, 0x083839C4, 0x7F7497E5, 0xA89CB99E, 0x3AABBBAA, 0xC734385A, 0x787F0BB,
					0x47757124, 0xD04C944D, 0x3813FC08
				};

				for (Hash hash : Weapons)
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), hash, 9999, 0);
			}
			if (GUI::Option("Give All MK2 Weapons")) {
				std::vector<Hash> WeaponHash{
					0xBFE256D4, 0x78A97CD0, 0xDBBD7280, 0x394F415C, 0xFAD1F1C9, 0xA914799
				};

				for (Hash hash : WeaponHash)
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), hash, 9999, 0);
			}
			if (GUI::Option("Remove All Weapons")) {
				WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()), true);
			}
			if (GUI::Option("Remove All MK2 Weapons")) {
				std::vector<Hash> WeaponHash{
					0xBFE256D4, 0x78A97CD0, 0xDBBD7280, 0x394F415C, 0xFAD1F1C9, 0xA914799
				};

				for (Hash hash : WeaponHash)
					WEAPON::REMOVE_WEAPON_FROM_PED(PLAYER::PLAYER_PED_ID(), hash);
			}
		}
		break;
#pragma endregion

#pragma region MK2 Weapons
		case custom_mk2:
		{
			GUI::Title("");
			GUI::Subtitle("MK2 Options");
			if (GUI::Option("Give All MK2 Upgrades")) {
				std::vector<Hash> pistolMk2{
					1329061674, 2396306288, 1140676955, 1709866683, 568543123, 2467084625
				};
				std::vector<Hash> smgMk2{
					190476639, 2076495324, 2681951826, 3842157419, 1038927834, 1303784126, 2774849419, 966612367
				};
				std::vector<Hash> assltRifleMk2{
					1675665560, 2640679034, 2076495324, 1108334355, 77277509, 3328927042, 2805810788, 1303784126, 1447477866, 3115408816
				};
				std::vector<Hash> carbineRifleMk2{
					1141059345, 2640679034, 2076495324, 1108334355, 77277509, 3328927042, 2205435306, 1303784126, 2335983627, 3663056191
				};
				std::vector<Hash> combatMgMk2{
					1475288264, 2640679034, 1108334355, 1060929921, 3328927042, 1303784126, 3051509595, 3607349581
				};
				std::vector<Hash> heavySniperMk2{
					2313935527, 2193687427, 3159677559, 3061846192, 776198721, 2890063729, 1764221345, 277524638, 1815270123
				};
				std::vector<Hash> WeaponHash{
					0xBFE256D4, 0x78A97CD0, 0xDBBD7280, 0x394F415C, 0xFAD1F1C9, 0xA914799
				};

				for (Hash hash : pistolMk2)
					WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("WEAPON_PISTOL_MK2"), hash);

				for (Hash hash : smgMk2)
					WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("WEAPON_SMG_MK2"), hash);

				for (Hash hash : assltRifleMk2)
					WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("WEAPON_ASSAULTRIFLE_MK2"), hash);

				for (Hash hash : carbineRifleMk2)
					WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("WEAPON_CARBINERIFLE_MK2"), hash);

				for (Hash hash : combatMgMk2)
					WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("WEAPON_COMBATMG_MK2"), hash);

				for (Hash hash : heavySniperMk2)
					WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("WEAPON_HEAVYSNIPER_MK2"), hash);

				for (Hash hash : WeaponHash)
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), hash, 9999, 0);
			}

			if (GUI::Option("Remove All MK2 Upgrades")) {
				std::vector<Hash> pistolMk2{
					1329061674, 2396306288, 1140676955, 1709866683, 568543123, 2467084625
				};
				std::vector<Hash> smgMk2{
					190476639, 2076495324, 2681951826, 3842157419, 1038927834, 1303784126, 2774849419, 966612367
				};
				std::vector<Hash> assltRifleMk2{
					1675665560, 2640679034, 2076495324, 1108334355, 77277509, 3328927042, 2805810788, 1303784126, 1447477866, 3115408816
				};
				std::vector<Hash> carbineRifleMk2{
					1141059345, 2640679034, 2076495324, 1108334355, 77277509, 3328927042, 2205435306, 1303784126, 2335983627, 3663056191
				};
				std::vector<Hash> combatMgMk2{
					1475288264, 2640679034, 1108334355, 1060929921, 3328927042, 1303784126, 3051509595, 3607349581
				};
				std::vector<Hash> heavySniperMk2{
					2313935527, 2193687427, 3159677559, 3061846192, 776198721, 2890063729, 1764221345, 277524638, 1815270123
				};

				for (Hash hash : pistolMk2)
					WEAPON::REMOVE_WEAPON_COMPONENT_FROM_PED(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("WEAPON_PISTOL_MK2"), hash);

				for (Hash hash : smgMk2)
					WEAPON::REMOVE_WEAPON_COMPONENT_FROM_PED(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("WEAPON_SMG_MK2"), hash);

				for (Hash hash : assltRifleMk2)
					WEAPON::REMOVE_WEAPON_COMPONENT_FROM_PED(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("WEAPON_ASSAULTRIFLE_MK2"), hash);

				for (Hash hash : carbineRifleMk2)
					WEAPON::REMOVE_WEAPON_COMPONENT_FROM_PED(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("WEAPON_CARBINERIFLE_MK2"), hash);

				for (Hash hash : combatMgMk2)
					WEAPON::REMOVE_WEAPON_COMPONENT_FROM_PED(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("WEAPON_COMBATMG_MK2"), hash);

				for (Hash hash : heavySniperMk2)
					WEAPON::REMOVE_WEAPON_COMPONENT_FROM_PED(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("WEAPON_HEAVYSNIPER_MK2"), hash);
			}
			GUI::Int("MK2 Tints", Features::tintCount, 1, 32, [] { Features::changeMk2Tint(); });
		}
		break;
#pragma endregion

#pragma region Ammo Mods
		case ammo_mods:
		{
			GUI::Title("");
			GUI::Subtitle("Ammo Modifications");
			GUI::Toggle("Explosive Ammo", Features::expammo, [] {Features::Expammos(); });
			GUI::Toggle("Flame Ammo", Features::fireammo, [] {Features::Fireammos(); });
			GUI::Toggle("One Shot Ammo", Features::osk, [] { Features::OSKR(Features::osk); });
			GUI::Toggle("Shoot Military Tank", Features::ShootWeaponT, [] { Features::ShootWeaponTank(Features::ShootWeaponT); });
			GUI::Toggle("Shoot Jet Hydra", Features::ShootHydra, [] { Features::Shootthehydra(Features::ShootHydra); });
			GUI::Toggle("Shoot Truck", Features::ShootDump, [] { Features::ShootDumpTruck(Features::ShootDump); });
			GUI::Toggle("Shoot Chopper", Features::ShootBuz, [] { Features::ShootBuzzard(Features::ShootBuz); });
			GUI::Toggle("Shoot Adder", Features::Shootadd, [] { Features::Shootadder(Features::Shootadd); });
		}
		break;
#pragma endregion

#pragma region Gun Mods

		case gun_mods:
		{
			GUI::Title("");
			GUI::Subtitle("Gun Modifiers");
			GUI::Toggle("No Recoil", Features::isNoRecoil, [] { Features::recoil(Features::isNoRecoil); });
			GUI::Toggle("Rapid Fire", Features::rapidfirer);
			GUI::Toggle("Airstrike Gun", Features::isAirStrikeGun, [] {Features::airStrikeGun(); });
			if (Features::menu_version == 2) {
				GUI::Toggle("Gravity Gun", Features::Gravity, [] { Features::GravityGun(Features::Gravity); }); //VIP
			}
			GUI::Toggle("Drive-It Gun", Features::isDriveItGun, [] { Features::driveItGun(); });
			GUI::Toggle("Teleport Gun", Features::isTeleportGun, [] {Features::teleportGun(Features::isTeleportGun); });
			GUI::Toggle("Rainbow Gun", Features::rbgun, [] { Features::RBGuner(Features::rbgun); });
			GUI::Toggle("Money Gun", Features::isMoneyGun, [] { Features::moneyGun(); });
			//GUI::Toggle("Guided Missile", Features::VALKYIREROCKET, [] { Features::valkyirerocket(Features::VALKYIREROCKET); }); //VIP
		}
		break;

#pragma endregion

#pragma endregion

#pragma region Vehicle SubMenus

#pragma region Vehicle Spawner
		case vehspawner: {
			GUI::Title("Vehicle Spawner");
			GUI::Subtitle("Vehicle Spawner");
			GUI::Toggle("Spawn in Car", Features::spawnincar);
			GUI::Toggle("Spawn Maxed", Features::spawnmaxed);
			GUI::Toggle("DLC Vehicles to SP", Features::isSPBypass);
			if (GUI::Option("Input Vehicle Name"))
			{
				GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(true, "Vehicle Spawner", "", "", "", "", "", 12);
				while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0) WAIT(0);
				Hash model = GAMEPLAY::GET_HASH_KEY((char*)_strdup(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()));
				if (STREAMING::IS_MODEL_VALID(model))
				{
					STREAMING::REQUEST_MODEL(model);
					while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
					Vector3 ourCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
					float forward = 5.f;
					float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
					float xVector = forward * sin(degToRad(heading)) * -1.f;
					float yVector = forward * cos(degToRad(heading));
					Vehicle veh = VEHICLE::CREATE_VEHICLE(model, ourCoords.x + xVector, ourCoords.y + yVector, ourCoords.z, heading, true, true);
					RequestControlOfEnt(veh);
					VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true, true);
					VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
					DECORATOR::DECOR_SET_INT(veh, "MPBitset", 0);
					auto networkId = NETWORK::VEH_TO_NET(veh);
					ENTITY::_SET_ENTITY_SOMETHING(veh, true);
					if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(veh))
						NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
					if (Features::spawnincar)
					{
						PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
					}
					if (Features::spawnmaxed)
					{
						VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
						for (int i = 0; i < 50; i++)
						{
							VEHICLE::SET_VEHICLE_MOD(veh, i, VEHICLE::GET_NUM_VEHICLE_MODS(veh, i) - 1, false);
						}
						VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, "Project");
					}
					WAIT(150);
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
				}
				else 
				{
					notifyMap("~r~Invalid Input!");
				}
			}
			//GUI::MenuOption("Modded Vehicles", modcars);
			GUI::MenuOption("Arena Wars", ArenaWars);
			GUI::MenuOption("After Hours", AfterHours);
			GUI::MenuOption("Southern San Andreas", san);
			GUI::MenuOption("Smugglers Run", SmuglerRun1);
			GUI::MenuOption("Gun Running", GunRunning1);
			GUI::MenuOption("Cunning Stunts", CunningStunts1);
			GUI::MenuOption("Import/Export", ImportEx1);
			GUI::MenuOption("Doomsday", Doomsday);
			GUI::MenuOption("Super", Supers);
			GUI::MenuOption("Sports", Sports);
			GUI::MenuOption("Sport Classic", SportClassic);
			GUI::MenuOption("Offroad", Offroad);
			GUI::MenuOption("Sedans", Sedans);
			GUI::MenuOption("Coupes", Coupes);
			GUI::MenuOption("Muscle", Muscle);
			GUI::MenuOption("Boats", Boats);
			GUI::MenuOption("Commercial", Commercial);
			GUI::MenuOption("Compacts", Compacts);
			GUI::MenuOption("Cycles", Cycles);
			GUI::MenuOption("Emergency", Emergency);
			GUI::MenuOption("Helicopters", Helicopters);
			GUI::MenuOption("Industrial", Industrial);
			GUI::MenuOption("Military", Military);
			GUI::MenuOption("Motorcycles", Motorcycles);
			GUI::MenuOption("Planes", Planes);
			GUI::MenuOption("Service", Service);
			GUI::MenuOption("SUV", SUV);
			GUI::MenuOption("Trailer", Trailer);
			GUI::MenuOption("Trains", Trains);
			GUI::MenuOption("Utility", Utility);
			GUI::MenuOption("Vans", Vans);

			break;

		case ArenaWars:
			GUI::Title("");
			GUI::Subtitle("Arena Wars");
			for (auto car : Hashes::ArenaWars) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		case AfterHours:
			GUI::Title("");
			GUI::Subtitle("After Hours");
			for (auto car : Hashes::AFTERHOURS) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		case ImportEx1:
			GUI::Title("Import/Export");
			GUI::Subtitle("Import/Export");
			for (auto car : Hashes::IMPORTEXPORT1) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		case CunningStunts1:
			GUI::Title("Cunning Stunts");
			GUI::Subtitle("Cunning Stunts");
			for (auto car : Hashes::CUNNINGSTUNTS1) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		case GunRunning1:
			GUI::Title("Gun Running");
			GUI::Subtitle("Gun Running");
			for (auto car : Hashes::SMUGLERSRUN1) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		case SmuglerRun1:
			GUI::Title("Smuglers Run");
			GUI::Subtitle("Smuglers Run");
			for (auto car : Hashes::GUNRUNNING1) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		case Doomsday:
			GUI::Title("Doomsday");
			GUI::Subtitle("Doomsday");
			for (auto car : Hashes::Doomsday1) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		case san:
			GUI::Title("Southern San Andreas");
			GUI::Subtitle("Southern San Andreas");
			for (auto car : Hashes::SOUTHERNSAN) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		case Supers:
			GUI::Title("Super");
			GUI::Subtitle("Super");
			for (auto car : Hashes::Super1) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		case Sports:
			GUI::Title("Sports");
			GUI::Subtitle("Sports");
			for (auto car : Hashes::Sports1) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		case SportClassic:
			GUI::Title("Sports Classic");
			GUI::Subtitle("Sports Classic");
			for (auto car : Hashes::SportsClassics1) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		case Offroad:
			GUI::Title("Offroad");
			GUI::Subtitle("Offroad");
			for (auto car : Hashes::OffRoad1) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		case Sedans:
			GUI::Title("Sedans");
			GUI::Subtitle("Sedans");
			for (auto car : Hashes::Sedans1) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		case Coupes:
			GUI::Title("Coupes");
			GUI::Subtitle("Coupes");
			for (auto car : Hashes::Coupes1) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		case Muscle:
			GUI::Title("Muscle");
			GUI::Subtitle("Muscle");
			for (auto car : Hashes::Muscle1) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		case Boats:
			GUI::Title("Boats");
			GUI::Subtitle("Boats");
			for (auto car : Hashes::Boats1) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		case Commercial:
			GUI::Title("Commercial");
			GUI::Subtitle("Commercial");
			for (auto car : Hashes::Commercial1) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		case Compacts:
			GUI::Title("Compacts");
			GUI::Subtitle("Compacts");
			for (auto car : Hashes::Compacts1) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		case Cycles:
			GUI::Title("Cycles");
			GUI::Subtitle("Cycles");
			for (auto car : Hashes::Cycles1) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		case Emergency:
			GUI::Title("Emergency");
			GUI::Subtitle("Emergency");
			for (auto car : Hashes::Emergency1) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		case Helicopters:
			GUI::Title("Helicopters");
			GUI::Subtitle("Helicopters");
			for (auto car : Hashes::Helicopters1) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		case Industrial:
			GUI::Title("Industrial");
			GUI::Subtitle("Industrial");
			for (auto car : Hashes::Industrial1) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		case Military:
			GUI::Title("Military");
			GUI::Subtitle("Military");
			for (auto car : Hashes::Military1) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		case Motorcycles:
			GUI::Title("Motorcycles");
			GUI::Subtitle("Motorcycles");
			for (auto car : Hashes::Motorcycles1) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		case Planes:
			GUI::Title("Planes");
			GUI::Subtitle("Planes");
			for (auto car : Hashes::Planes1) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		case Service:
			GUI::Title("Service");
			GUI::Subtitle("Service");
			for (auto car : Hashes::Service1) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		case SUV:
			GUI::Title("SUV");
			GUI::Subtitle("SUV");
			for (auto car : Hashes::SUVs1) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		case Trailer:
			GUI::Title("Trailer");
			GUI::Subtitle("Trailer");
			for (auto car : Hashes::Trailer1) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		case Trains:
			GUI::Title("Trains");
			GUI::Subtitle("Trains");
			for (auto car : Hashes::Trains1) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		case Utility:
			GUI::Title("Utility");
			GUI::Subtitle("Utility");
			for (auto car : Hashes::Utility1) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		case Vans:
			GUI::Title("Vans");
			GUI::Subtitle("Vans");
			for (auto car : Hashes::Vans1) { GUI::Option(car, [car] { Features::spawn_vehicle(car); }); }
			break;
		}
						 break;

		/*case modcars:
		{
			GUI::Title("");
			GUI::Subtitle("Modded Cars");
			if (GUI::Option("Trolley")) {

				uint Handle = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Vector3 null; null.x = 0, null.y = 0; null.z = 0;
				Vector3 a; a.x = 0, a.y = 0, a.z = 0;
				Vector3 b; b.x = 0, b.y = 2, b.z = 0;
				int hash = GAMEPLAY::GET_HASH_KEY("carbonrs");
				int hash2 = GAMEPLAY::GET_HASH_KEY("prop_rub_trolley01a");
				STREAMING::REQUEST_MODEL(hash);
				STREAMING::REQUEST_MODEL(hash2);
				if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
				{
					int Object = OBJECT::CREATE_OBJECT(hash2, null.x, null.y, null.z, 1, 1, 1);
					if (ENTITY::DOES_ENTITY_EXIST(Object))
					{
						int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
						if (ENTITY::DOES_ENTITY_EXIST(Vehicle))
						{
							PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
							STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
							ENTITY::SET_ENTITY_VISIBLE(Vehicle, false, false);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
							notifyMap("Spawned: ~b~Trolley~HUD_COLOUR_WHITE~!");
							ENTITY::SET_ENTITY_VISIBLE(Handle, true, true);

						}

					}

				}

			}
			if (GUI::Option("6x6 War RC")) {
				int Handle = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Vector3 null; null.x = 0, null.y = 0; null.z = 0;
				Vector3 a; a.x = 0, a.y = 0, a.z = 0.03f;
				Vector3 b; b.x = 0, b.y = 0, b.z = 0;
				int hash = GAMEPLAY::GET_HASH_KEY("dune2");
				int hash2 = GAMEPLAY::GET_HASH_KEY("t20");
				int hash3 = GAMEPLAY::GET_HASH_KEY("dune2");
				int hash4 = GAMEPLAY::GET_HASH_KEY("dune2");
				int hash5 = GAMEPLAY::GET_HASH_KEY("monster");
				int hash6 = GAMEPLAY::GET_HASH_KEY("monster");


				STREAMING::REQUEST_MODEL(hash);
				STREAMING::REQUEST_MODEL(hash2);
				STREAMING::REQUEST_MODEL(hash3);
				STREAMING::REQUEST_MODEL(hash4);
				STREAMING::REQUEST_MODEL(hash5);
				STREAMING::REQUEST_MODEL(hash6);


				if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2) && STREAMING::HAS_MODEL_LOADED(hash3) && STREAMING::HAS_MODEL_LOADED(hash4) && STREAMING::HAS_MODEL_LOADED(hash5) && STREAMING::HAS_MODEL_LOADED(hash6))
				{
					int Object1 = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
					int Object2 = VEHICLE::CREATE_VEHICLE(hash3, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
					int Object3 = VEHICLE::CREATE_VEHICLE(hash4, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
					int Object4 = VEHICLE::CREATE_VEHICLE(hash5, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
					int Object5 = VEHICLE::CREATE_VEHICLE(hash6, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);



					if (ENTITY::DOES_ENTITY_EXIST(Object1) && ENTITY::DOES_ENTITY_EXIST(Object2) && ENTITY::DOES_ENTITY_EXIST(Object3) && ENTITY::DOES_ENTITY_EXIST(Object4) && ENTITY::DOES_ENTITY_EXIST(Object5))
					{
						int Vehicle = VEHICLE::CREATE_VEHICLE(hash2, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
						if (ENTITY::DOES_ENTITY_EXIST(Vehicle))
						{
							PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);

							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object1, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object2, Vehicle, 0, a.x - 0.1f, a.y, a.z, b.x, b.y + 41.1f, b.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object3, Vehicle, 0, a.x + 0.1f, a.y, a.z, b.x, b.y - 41.4f, b.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object4, Vehicle, 0, a.x + 1.41f, a.y, a.z - 0.2f, b.x - 179.99f, b.y, b.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object5, Vehicle, 0, a.x - 1.41f, a.y, a.z - 0.2f, b.x - 179.99f, b.y, b.z, 0, 1, 0, 0, 2, 1);

							VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle, 255, 255, 255);
							VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle, 255, 255, 255);
							VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object1, 255, 255, 255);
							VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object1, 255, 255, 255);
							VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object4, 255, 255, 255);
							VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object4, 255, 255, 255);
							VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object5, 255, 255, 255);
							VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object5, 255, 255, 255);
						}

					}

				}
			}
			if (GUI::Option("Speeder Prototype")) {
				int Handle = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Vector3 null; null.x = 0, null.y = 0; null.z = 0;
				Vector3 a; a.x = 0, a.y = 0, a.z = 0.03f;
				Vector3 b; b.x = 0, b.y = 0, b.z = 0;
				int hash = GAMEPLAY::GET_HASH_KEY("seashark");
				int hash1 = GAMEPLAY::GET_HASH_KEY("seashark");
				int hash2 = GAMEPLAY::GET_HASH_KEY("turismor");
				STREAMING::REQUEST_MODEL(hash);
				STREAMING::REQUEST_MODEL(hash1);
				STREAMING::REQUEST_MODEL(hash2);
				if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash1) && STREAMING::HAS_MODEL_LOADED(hash2))
				{
					int Object = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
					int Object1 = VEHICLE::CREATE_VEHICLE(hash1, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(Object))
					{
						int Vehicle = VEHICLE::CREATE_VEHICLE(hash2, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
						if (ENTITY::DOES_ENTITY_EXIST(Vehicle))
						{
							VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle, 255, 0, 0);
							VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle, 255, 0, 0);
							VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object, 255, 0, 0);
							VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object, 255, 0, 0);
							VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object1, 255, 0, 0);
							VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object1, 255, 0, 0);
							PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y + 1.37f, a.z + 0.59f, b.x - 14.33f, b.y + 541.20f, b.z - 1.42f, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object1, Vehicle, 0, a.x, a.y - 0.79f, a.z + 0.83f, b.x + 9.72f, b.y + 539.03f, b.z - 0.16f, 0, 1, 0, 0, 2, 1);
						}
					}
				}
			}
			if (GUI::Option("Snow Scooter")) {
				int Handle = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Vector3 null; null.x = 0, null.y = 0; null.z = 0;
				Vector3 a; a.x = 0, a.y = 0, a.z = 0.03f;
				Vector3 b; b.x = 0, b.y = 0, b.z = 0;
				int hash = GAMEPLAY::GET_HASH_KEY("seashark");
				int hash2 = GAMEPLAY::GET_HASH_KEY("sanchez");
				STREAMING::REQUEST_MODEL(hash);
				STREAMING::REQUEST_MODEL(hash2);
				if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
				{
					int Object = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(Object))
					{
						int Vehicle = VEHICLE::CREATE_VEHICLE(hash2, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
						if (ENTITY::DOES_ENTITY_EXIST(Vehicle))
						{
							VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle, 255, 0, 0);
							VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle, 255, 0, 0);
							VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object, 255, 0, 0);
							VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object, 255, 0, 0);
							PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);

							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x - 0.02f, a.y - 0.08f, a.z - 0.36f, b.x - 0.21f, b.y + 1.83f, b.z - 0.21f, 0, 1, 0, 0, 2, 1);

						}
					}
				}
			}
			if (GUI::Option("Military Flightsquad")) {
				int Handle = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Vector3 null; null.x = 0, null.y = 0; null.z = 0;
				Vector3 a; a.x = 0, a.y = 0, a.z = 0.03f;
				Vector3 b; b.x = 0, b.y = 0, b.z = 0;
				int hash = GAMEPLAY::GET_HASH_KEY("hydra");
				int hash1 = GAMEPLAY::GET_HASH_KEY("hydra");
				int hash2 = GAMEPLAY::GET_HASH_KEY("hydra");
				int hash3 = GAMEPLAY::GET_HASH_KEY("hydra");
				int hash4 = GAMEPLAY::GET_HASH_KEY("hydra");
				int hash5 = GAMEPLAY::GET_HASH_KEY("hydra");
				int hash6 = GAMEPLAY::GET_HASH_KEY("hydra");
				int hash7 = GAMEPLAY::GET_HASH_KEY("hydra");
				int hash8 = GAMEPLAY::GET_HASH_KEY("hydra");

				STREAMING::REQUEST_MODEL(hash);
				STREAMING::REQUEST_MODEL(hash2);
				STREAMING::REQUEST_MODEL(hash1);
				STREAMING::REQUEST_MODEL(hash3);
				STREAMING::REQUEST_MODEL(hash4);
				STREAMING::REQUEST_MODEL(hash5);
				STREAMING::REQUEST_MODEL(hash6);
				STREAMING::REQUEST_MODEL(hash7);
				STREAMING::REQUEST_MODEL(hash8);
				if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2) && STREAMING::HAS_MODEL_LOADED(hash1) && STREAMING::HAS_MODEL_LOADED(hash3) && STREAMING::HAS_MODEL_LOADED(hash4) && STREAMING::HAS_MODEL_LOADED(hash5) && STREAMING::HAS_MODEL_LOADED(hash6) && STREAMING::HAS_MODEL_LOADED(hash7) && STREAMING::HAS_MODEL_LOADED(hash8))
				{
					int Object = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
					int Object1 = VEHICLE::CREATE_VEHICLE(hash1, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
					int Object2 = VEHICLE::CREATE_VEHICLE(hash3, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
					int Object3 = VEHICLE::CREATE_VEHICLE(hash4, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
					int Object4 = VEHICLE::CREATE_VEHICLE(hash5, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
					int Object5 = VEHICLE::CREATE_VEHICLE(hash6, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
					int Object6 = VEHICLE::CREATE_VEHICLE(hash7, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
					int Object7 = VEHICLE::CREATE_VEHICLE(hash8, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(Object))
					{
						int Vehicle = VEHICLE::CREATE_VEHICLE(hash2, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
						if (ENTITY::DOES_ENTITY_EXIST(Vehicle))
						{

							PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);


							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y + 15.541162f, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object1, Vehicle, 0, a.x, a.y + 30.541162f, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object2, Vehicle, 0, a.x - 15.0f, a.y + 15.541162f, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object3, Vehicle, 0, a.x + 15.0f, a.y + 15.541162f, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object4, Vehicle, 0, a.x + 15.0f, a.y, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object5, Vehicle, 0, a.x + 30.0f, a.y, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object6, Vehicle, 0, a.x - 15.0f, a.y, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object7, Vehicle, 0, a.x - 30.0f, a.y, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);

						}
					}
				}
			}
			if (GUI::Option("Bike Robot")) {
				int Handle = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Vector3 null; null.x = 0, null.y = 0; null.z = 0;
				Vector3 a; a.x = 0, a.y = 0, a.z = 0.03f;
				Vector3 b; b.x = 0, b.y = 0, b.z = 0;
				int hash = GAMEPLAY::GET_HASH_KEY("bati");
				int hash1 = GAMEPLAY::GET_HASH_KEY("bati");
				int hash2 = GAMEPLAY::GET_HASH_KEY("bati");
				int hash3 = GAMEPLAY::GET_HASH_KEY("bati");
				int hash4 = GAMEPLAY::GET_HASH_KEY("bati");
				int hash5 = GAMEPLAY::GET_HASH_KEY("bati");
				int hash6 = GAMEPLAY::GET_HASH_KEY("bati");
				int hash7 = GAMEPLAY::GET_HASH_KEY("bati");
				int hash8 = GAMEPLAY::GET_HASH_KEY("bati");
				int hash9 = GAMEPLAY::GET_HASH_KEY("bati");
				int hash10 = GAMEPLAY::GET_HASH_KEY("bati");
				int hash11 = GAMEPLAY::GET_HASH_KEY("bati");
				int hash12 = GAMEPLAY::GET_HASH_KEY("bati");
				STREAMING::REQUEST_MODEL(hash);
				STREAMING::REQUEST_MODEL(hash1);
				STREAMING::REQUEST_MODEL(hash2);
				STREAMING::REQUEST_MODEL(hash2);
				STREAMING::REQUEST_MODEL(hash3);
				STREAMING::REQUEST_MODEL(hash4);
				STREAMING::REQUEST_MODEL(hash5);
				STREAMING::REQUEST_MODEL(hash6);
				STREAMING::REQUEST_MODEL(hash7);
				STREAMING::REQUEST_MODEL(hash8);
				STREAMING::REQUEST_MODEL(hash9);
				STREAMING::REQUEST_MODEL(hash10);
				STREAMING::REQUEST_MODEL(hash11);
				STREAMING::REQUEST_MODEL(hash12);
				if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2) && STREAMING::HAS_MODEL_LOADED(hash1) && STREAMING::HAS_MODEL_LOADED(hash3) && STREAMING::HAS_MODEL_LOADED(hash4) && STREAMING::HAS_MODEL_LOADED(hash5) && STREAMING::HAS_MODEL_LOADED(hash6) && STREAMING::HAS_MODEL_LOADED(hash7) && STREAMING::HAS_MODEL_LOADED(hash8) && STREAMING::HAS_MODEL_LOADED(hash9) && STREAMING::HAS_MODEL_LOADED(hash10) && STREAMING::HAS_MODEL_LOADED(hash11))
				{
					int Object = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
					int Object1 = VEHICLE::CREATE_VEHICLE(hash1, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
					int Object2 = VEHICLE::CREATE_VEHICLE(hash3, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
					int Object3 = VEHICLE::CREATE_VEHICLE(hash4, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
					int Object4 = VEHICLE::CREATE_VEHICLE(hash5, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
					int Object5 = VEHICLE::CREATE_VEHICLE(hash6, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
					int Object6 = VEHICLE::CREATE_VEHICLE(hash7, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
					int Object7 = VEHICLE::CREATE_VEHICLE(hash8, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
					int Object8 = VEHICLE::CREATE_VEHICLE(hash9, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
					int Object9 = VEHICLE::CREATE_VEHICLE(hash10, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
					int Object10 = VEHICLE::CREATE_VEHICLE(hash11, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
					int Object11 = VEHICLE::CREATE_VEHICLE(hash12, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(Object))
					{
						int Vehicle = VEHICLE::CREATE_VEHICLE(hash2, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
						if (ENTITY::DOES_ENTITY_EXIST(Vehicle))
						{
							PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);

							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z + 1.16f, b.x + 62.0f, b.y, b.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object1, Vehicle, 0, a.x + 2.5f, a.y, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object3, Vehicle, 0, a.x + 2.5f, a.y, a.z + 1.16f, b.x + 62.0f, b.y, b.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object4, Vehicle, 0, a.x + 0.5f, a.y + 0.5f, a.z + 2.27f, b.x + 50.0f, b.y - 70.0f, b.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object5, Vehicle, 0, a.x + 1.95f, a.y + 0.5f, a.z + 2.27f, b.x + 50.0f, b.y + 70.0f, b.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object6, Vehicle, 0, a.x + 1.24f, a.y + 0.8f, a.z + 5.0f, b.x + 90.0f, b.y, b.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object7, Vehicle, 0, a.x + 1.24f, a.y + 0.8f, a.z + 3.5f, b.x + 90.0f, b.y, b.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object8, Vehicle, 0, a.x + 1.24f, a.y + 0.8f, a.z + 6.0f, b.x - 15.0f, b.y, b.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object9, Vehicle, 0, a.x + 2.0f, a.y + 0.8f, a.z + 4.43f, b.x - 30.0f, b.y - 50.0f, b.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object10, Vehicle, 0, a.x + 0.6f, a.y + 0.8f, a.z + 4.43f, b.x - 30.0f, b.y + 50.0f, b.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object2, Vehicle, 0, a.x, a.y + 2.1f, a.z + 3.7f, b.x - 10.0f, b.y + 12.8f, b.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object11, Vehicle, 0, a.x + 2.8f, a.y + 1.9f, a.z + 3.7f, b.x - 10.0f, b.y - 13.6f, b.z, 0, 1, 0, 0, 2, 1);
						}
					}
				}
			}
			if (GUI::Option("Bumper Buggy")) {
				uint Handle = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Vector3 null; null.x = 0.0f, null.y = 0.0f; null.z = 0.0f;
				Vector3 a; a.x = -0.34f, a.y = 0.32f, a.z = -0.25;
				Vector3 b; b.x = 0.0f, b.y = 0.0f, b.z = 180;
				Vector3 Tire; Tire.x = 0.0f, Tire.y = 0.0; Tire.z = 0.0;//Right Front(inner tire)
				Vector3 TireA; TireA.x = 0.40f, TireA.y = 1.0f, TireA.z = -0.51f;//X Coord - Y Coord - Z Coord
				Vector3 TireB; TireB.x = 0.0f, TireB.y = 0.0f, TireB.z = 88.0;//Pitch - Roll - Yaw
				Vector3 Tire01; Tire01.x = 0.0f, Tire01.y = 0.0; Tire01.z = 0.0f;//Right Front(outter tire)
				Vector3 TireC; TireC.x = 0.59f, TireC.y = 1.0f, TireC.z = -0.51f;//X Coord - Y Coord - Z Coord
				Vector3 TireD; TireD.x = 0.0f, TireD.y = 0.0f, TireD.z = -90.0;//Pitch - Roll - Yaw
				Vector3 Tire02; Tire02.x = 0.0f, Tire02.y = 0.0; Tire02.z = 0.0;//Left Front(inner tire)
				Vector3 TireE; TireE.x = -1.09f, TireE.y = 1.0f, TireE.z = -0.50;//X Coord - Y Coord - Z Coord
				Vector3 TireF; TireF.x = 0.0f, TireF.y = 0.0f, TireF.z = -88.0;//Pitch - Roll - Yaw
				Vector3 Tire03; Tire03.x = 0.0f, Tire03.y = 0.0; Tire03.z = 0.0;//Left Front(outter tire)
				Vector3 TireG; TireG.x = -1.264f, TireG.y = 1.0f, TireG.z = -0.50;//X Coord - Y Coord - Z Coord
				Vector3 TireH; TireH.x = 0.0f, TireH.y = 0.0f, TireH.z = 92.0;//Pitch - Roll - Yaw
				Vector3 Engine1; Engine1.x = 0.0f, Engine1.y = 0.0; Engine1.z = 0.0;//Engine
				Vector3 EngineA; EngineA.x = -0.39f, EngineA.y = -1.60f, EngineA.z = -0.70f;//X Coord - Y Coord - Z Coord
				Vector3 EngineB; EngineB.x = 0.0f, EngineB.y = 0.0f, EngineB.z = 0.0;//Pitch - Roll - Yaw
				Vector3 Tire04; Tire04.x = 0.0f, Tire04.y = 0.0; Tire04.z = 0.0;//Right Rear(inner tire)
				Vector3 TireI; TireI.x = 0.22f, TireI.y = -1.40f, TireI.z = -0.50;//X Coord - Y Coord - Z Coord
				Vector3 TireJ; TireJ.x = 0.0f, TireJ.y = 0.0f, TireJ.z = -88.0;//Pitch - Roll - Yaw
				Vector3 Tire05; Tire05.x = 0.0f, Tire05.y = 0.0; Tire05.z = 0.0;//Right Rear(middle tire)
				Vector3 TireK; TireK.x = 0.42f, TireK.y = -1.40f, TireK.z = -0.50;//X Coord - Y Coord - Z Coord
				Vector3 TireL; TireL.x = 0.0f, TireL.y = 0.0f, TireL.z = 90.0;//Pitch - Roll - Yaw
				Vector3 Tire06; Tire06.x = 0.0f, Tire06.y = 0.0; Tire06.z = 0.0;//Right Rear(outter tire)
				Vector3 TireM; TireM.x = 0.593f, TireM.y = -1.40f, TireM.z = -0.50;//X Coord - Y Coord - Z Coord
				Vector3 TireN; TireN.x = 0.0f, TireN.y = 0.0f, TireN.z = -89.0;//Pitch - Roll - Yaw
				Vector3 Tire07; Tire07.x = 0.0f, Tire07.y = 0.0; Tire07.z = 0.0;//Left Rear(inner tire)
				Vector3 TireO; TireO.x = -0.81f, TireO.y = -1.40f, TireO.z = -0.50;//X Coord - Y Coord - Z Coord
				Vector3 TireP; TireP.x = 0.0f, TireP.y = 0.0f, TireP.z = 88.0;//Pitch - Roll - Yaw
				Vector3 Tire08; Tire08.x = 0.0f, Tire08.y = 0.0; Tire08.z = 0.0;//Left Rear(middle tire)
				Vector3 TireQ; TireQ.x = -1.01f, TireQ.y = -1.40f, TireQ.z = -0.50;//X Coord - Y Coord - Z Coord
				Vector3 TireR; TireR.x = 0.0f, TireR.y = 0.0f, TireR.z = -91.0;//Pitch - Roll - Yaw
				Vector3 Tire09; Tire09.x = 0.0f, Tire09.y = 0.0; Tire09.z = 0.0;//Left Rear(outter tire)
				Vector3 TireSs; TireSs.x = -1.184f, TireSs.y = -1.40f, TireSs.z = -0.50f;//X Coord - Y Coord - Z Coord
				Vector3 TireT; TireT.x = 0.0f, TireT.y = 0.0f, TireT.z = 88.0f;//Pitch - Roll - Yaw
				Vector3 Hood1; Hood1.x = 0.0f, Hood1.y = 0; Hood1.z = 0.0f;//Hood
				Vector3 HoodA; HoodA.x = -0.34f, HoodA.y = 1.2f, HoodA.z = -0.40f;//X Coord - Y Coord - Z Coord
				Vector3 HoodB; HoodB.x = -24.0f, HoodB.y = 0.0f, HoodB.z = 0.0;//Pitch - Roll - Yaw
				Vector3 Battery1; Battery1.x = 0.0f, Battery1.y = 0.0; Battery1.z = 0.0;//Battery
				Vector3 BatteryA; BatteryA.x = -0.34f, BatteryA.y = 1.06f, BatteryA.z = -0.06f;//X Coord - Y Coord - Z Coord
				Vector3 BatteryB; BatteryB.x = -24.0f, BatteryB.y = 0.0f, BatteryB.z = 0.0;//Pitch - Roll - Yaw
				int hash = GAMEPLAY::GET_HASH_KEY("blista");
				int hash2 = GAMEPLAY::GET_HASH_KEY("prop_bumper_car_01");
				int Tires = GAMEPLAY::GET_HASH_KEY("prop_wheel_01");
				int Engine = GAMEPLAY::GET_HASH_KEY("prop_car_engine_01");
				int Hood = GAMEPLAY::GET_HASH_KEY("hei_prop_heist_emp");
				int Battery = GAMEPLAY::GET_HASH_KEY("prop_power_cell");
				STREAMING::REQUEST_MODEL(hash);
				STREAMING::REQUEST_MODEL(hash2);
				STREAMING::REQUEST_MODEL(Tires);
				STREAMING::REQUEST_MODEL(Engine);
				STREAMING::REQUEST_MODEL(Hood);
				STREAMING::REQUEST_MODEL(Battery);
				if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2) && STREAMING::HAS_MODEL_LOADED(Tires) && STREAMING::HAS_MODEL_LOADED(Engine) && STREAMING::HAS_MODEL_LOADED(Hood) && STREAMING::HAS_MODEL_LOADED(Battery))
				{
					int Object = OBJECT::CREATE_OBJECT(hash2, null.x, null.y, null.z, 1, 0, 1);
					int Tire1 = OBJECT::CREATE_OBJECT(Tires, Tire.x, Tire.y, Tire.z, 1, 0, 1);//Right Front(inner tire)
					int Tire2 = OBJECT::CREATE_OBJECT(Tires, Tire01.x, Tire01.y, Tire01.z, 1, 0, 1);//right Front(outter tire)
					int Tire3 = OBJECT::CREATE_OBJECT(Tires, Tire02.x, Tire02.y, Tire02.z, 1, 0, 1);//Left Front(inner tire)
					int Tire4 = OBJECT::CREATE_OBJECT(Tires, Tire03.x, Tire03.y, Tire03.z, 1, 0, 1);//Left Front(outter tire)
					int Engine01 = OBJECT::CREATE_OBJECT(Engine, Engine1.x, Engine1.y, Engine1.z, 1, 0, 1);//Engine
					int Tire5 = OBJECT::CREATE_OBJECT(Tires, Tire04.x, Tire04.y, Tire04.z, 1, 0, 1);//Right Rear(inner tire)
					int Tire6 = OBJECT::CREATE_OBJECT(Tires, Tire05.x, Tire05.y, Tire05.z, 1, 0, 1);//Right Rear(middle tire)
					int Tire7 = OBJECT::CREATE_OBJECT(Tires, Tire06.x, Tire06.y, Tire06.z, 1, 0, 1);//Right Rear(outter tire)
					int Tire8 = OBJECT::CREATE_OBJECT(Tires, Tire07.x, Tire07.y, Tire07.z, 1, 0, 1);//Left Rear(inner tire)
					int Tire9 = OBJECT::CREATE_OBJECT(Tires, Tire08.x, Tire08.y, Tire08.z, 1, 0, 1);//Left Rear(middle tire)
					int Tire10 = OBJECT::CREATE_OBJECT(Tires, Tire09.x, Tire09.y, Tire09.z, 1, 0, 1);//Left Rear(outter tire)
					int Hood01 = OBJECT::CREATE_OBJECT(Hood, Hood1.x, Hood1.y, Hood1.z, 1, 0, 1);//Hood
					int Battery01 = OBJECT::CREATE_OBJECT(Battery, Battery1.x, Battery1.y, Battery1.z, 1, 0, 1);//Battery
					if (ENTITY::DOES_ENTITY_EXIST(Object) && ENTITY::DOES_ENTITY_EXIST(Tire1) && ENTITY::DOES_ENTITY_EXIST(Tire2) && ENTITY::DOES_ENTITY_EXIST(Tire3) && ENTITY::DOES_ENTITY_EXIST(Tire4) && ENTITY::DOES_ENTITY_EXIST(Engine01) && ENTITY::DOES_ENTITY_EXIST(Tire5) && ENTITY::DOES_ENTITY_EXIST(Tire6) && ENTITY::DOES_ENTITY_EXIST(Tire7) && ENTITY::DOES_ENTITY_EXIST(Tire8) && ENTITY::DOES_ENTITY_EXIST(Tire9) && ENTITY::DOES_ENTITY_EXIST(Tire10) && ENTITY::DOES_ENTITY_EXIST(Hood01) && ENTITY::DOES_ENTITY_EXIST(Battery01))
					{
						int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
						if (ENTITY::DOES_ENTITY_EXIST(Vehicle))
						{
							PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
							STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
							ENTITY::SET_ENTITY_VISIBLE(Vehicle, false, false);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Tire1, Vehicle, 0, TireA.x, TireA.y, TireA.z, TireB.x, TireB.y, TireB.z, 0, 1, 0, 0, 2, 1);//Right Front(inner tire)
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Tire2, Vehicle, 0, TireC.x, TireC.y, TireC.z, TireD.x, TireD.y, TireD.z, 0, 1, 0, 0, 2, 1);//right Front(outter tire)
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Tire3, Vehicle, 0, TireE.x, TireE.y, TireE.z, TireF.x, TireF.y, TireF.z, 0, 1, 0, 0, 2, 1);//Left Front(inner tire)
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Tire4, Vehicle, 0, TireG.x, TireG.y, TireG.z, TireH.x, TireH.y, TireH.z, 0, 1, 0, 0, 2, 1);//Left Front(outter tire)
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Engine01, Vehicle, 0, EngineA.x, EngineA.y, EngineA.z, EngineB.x, EngineB.y, EngineB.z, 0, 1, 0, 0, 2, 1);//Engine
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Tire5, Vehicle, 0, TireI.x, TireI.y, TireI.z, TireJ.x, TireJ.y, TireJ.z, 0, 1, 0, 0, 2, 1);//Right Rear(inner tire)
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Tire6, Vehicle, 0, TireK.x, TireK.y, TireK.z, TireL.x, TireL.y, TireL.z, 0, 1, 0, 0, 2, 1);//Right Rear(middle tire)
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Tire7, Vehicle, 0, TireM.x, TireM.y, TireM.z, TireN.x, TireN.y, TireN.z, 0, 1, 0, 0, 2, 1);//Right Rear(outter tire)
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Tire8, Vehicle, 0, TireO.x, TireO.y, TireO.z, TireP.x, TireP.y, TireP.z, 0, 1, 0, 0, 2, 1);//Left Rear(inner tire)
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Tire9, Vehicle, 0, TireQ.x, TireQ.y, TireQ.z, TireR.x, TireR.y, TireR.z, 0, 1, 0, 0, 2, 1);//Left Rear(middle tire)
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Tire10, Vehicle, 0, TireSs.x, TireSs.y, TireSs.z, TireT.x, TireT.y, TireT.z, 0, 1, 0, 0, 2, 1);//Left Rear(outter tire)
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Hood01, Vehicle, 0, HoodA.x, HoodA.y, HoodA.z, HoodB.x, HoodB.y, HoodB.z, 0, 1, 0, 0, 2, 1);//Hood
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Battery01, Vehicle, 0, BatteryA.x, BatteryA.y, BatteryA.z, BatteryB.x, BatteryB.y, BatteryB.z, 0, 1, 0, 0, 2, 1);//Battery
							ENTITY::SET_ENTITY_VISIBLE(Handle, true, false);

						}

					}

				}

			}
			if (GUI::Option("Modded Carbon RS")) {
				uint Handle = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				//hash2_EMP
				Vector3 null; null.x = 0.0, null.y = 0.0; null.z = 0.0;
				Vector3 a; a.x = 0.0, a.y = 1.61, a.z = -0.12;//X Coord - Y Coord - Z Coord
				Vector3 b; b.x = -12.0, b.y = 0.0, b.z = 0.0;//Pitch - Roll - Yaw
																//hash3_MiniGun
				Vector3 null1; null1.x = 0.0, null1.y = 0.0; null1.z = 0.0;
				Vector3 a1; a1.x = -0.60, a1.y = 1.60, a1.z = 0.20;
				Vector3 b1; b1.x = 0.0, b1.y = 0.0, b1.z = 88.0;
				//hash3_MiniGun2
				Vector3 null0; null0.x = 0.0, null0.y = 0.0; null0.z = 0.0;
				Vector3 a0; a0.x = 0.60, a0.y = 1.60, a0.z = 0.20;
				Vector3 b0; b0.x = 0.0, b0.y = 0.0, b0.z = 88.0;
				//hash4_FLWheel1
				Vector3 null2; null2.x = 0.0, null2.y = 0.0; null2.z = 0.0;
				Vector3 a2; a2.x = -0.94, a2.y = 1.32, a2.z = -0.25;
				Vector3 b2; b2.x = 9.0, b2.y = -28.0, b2.z = 87.0;
				//hash4_RLWheel1
				Vector3 null3; null3.x = 0.0, null3.y = 0.0; null3.z = 0.0;
				Vector3 a3; a3.x = -0.95, a3.y = -1.34, a3.z = -0.25f;
				Vector3 b3; b3.x = 9.0, b3.y = 38.0, b3.z = 87.0;
				//hash4_RFWheel1
				Vector3 null4; null4.x = 0.0, null4.y = 0.0; null4.z = 0.0;
				Vector3 a4; a4.x = 0.95, a4.y = 1.33, a4.z = -0.23;
				Vector3 b4; b4.x = 11.0, b4.y = 26.0, b4.z = -89.0;
				//hash4_RRWheel1
				Vector3 null5; null5.x = 0.0, null5.y = 0.0; null5.z = 0.0;
				Vector3 a5; a5.x = 0.96, a5.y = -1.31, a5.z = -0.23;
				Vector3 b5; b5.x = 10.0, b5.y = 20.0, b5.z = -92.0;

				int hash_T20 = GAMEPLAY::GET_HASH_KEY("t20");
				int hash2_EMP = GAMEPLAY::GET_HASH_KEY("hei_prop_heist_emp");
				int hash3_MiniGun = GAMEPLAY::GET_HASH_KEY("prop_minigun_01");
				int hash4_Wheel = GAMEPLAY::GET_HASH_KEY("prop_wheel_01");

				STREAMING::REQUEST_MODEL(hash_T20);
				STREAMING::REQUEST_MODEL(hash2_EMP);
				STREAMING::REQUEST_MODEL(hash3_MiniGun);
				STREAMING::REQUEST_MODEL(hash4_Wheel);

				if (STREAMING::HAS_MODEL_LOADED(hash_T20) && STREAMING::HAS_MODEL_LOADED(hash2_EMP) && STREAMING::HAS_MODEL_LOADED(hash3_MiniGun) && STREAMING::HAS_MODEL_LOADED(hash4_Wheel))
				{
					int EMP = OBJECT::CREATE_OBJECT(hash2_EMP, null.x, null.y, null.z, 1, 0, 1);
					int MiniGun = OBJECT::CREATE_OBJECT(hash3_MiniGun, null1.x, null1.y, null1.z, 1, 0, 1);
					int MiniGun2 = OBJECT::CREATE_OBJECT(hash3_MiniGun, null0.x, null0.y, null0.z, 1, 0, 1);
					int FLWheel1 = OBJECT::CREATE_OBJECT(hash4_Wheel, null2.x, null2.y, null2.z, 1, 0, 1);
					int RLWheel1 = OBJECT::CREATE_OBJECT(hash4_Wheel, null3.x, null3.y, null3.z, 1, 0, 1);
					int RFWheel1 = OBJECT::CREATE_OBJECT(hash4_Wheel, null4.x, null4.y, null4.z, 1, 0, 1);
					int RRWheel1 = OBJECT::CREATE_OBJECT(hash4_Wheel, null5.x, null5.y, null5.z, 1, 0, 1);

					if (ENTITY::DOES_ENTITY_EXIST(EMP) && ENTITY::DOES_ENTITY_EXIST(MiniGun) && ENTITY::DOES_ENTITY_EXIST(MiniGun2) && ENTITY::DOES_ENTITY_EXIST(FLWheel1) && ENTITY::DOES_ENTITY_EXIST(RLWheel1) && ENTITY::DOES_ENTITY_EXIST(RFWheel1) && ENTITY::DOES_ENTITY_EXIST(RRWheel1))
					{
						int Vehicle = VEHICLE::CREATE_VEHICLE(hash_T20, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);

						if (ENTITY::DOES_ENTITY_EXIST(Vehicle))
						{
							PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
							STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash_T20);
							ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, true);
							ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true, true);

							ENTITY::ATTACH_ENTITY_TO_ENTITY(EMP, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(MiniGun, Vehicle, 0, a1.x, a1.y, a1.z, b1.x, b1.y, b1.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(MiniGun2, Vehicle, 0, a0.x, a0.y, a0.z, b0.x, b0.y, b0.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(FLWheel1, Vehicle, 0, a2.x, a2.y, a2.z, b2.x, b2.y, b2.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(RLWheel1, Vehicle, 0, a3.x, a3.y, a3.z, b3.x, b3.y, b3.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(RFWheel1, Vehicle, 0, a4.x, a4.y, a4.z, b4.x, b4.y, b4.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(RRWheel1, Vehicle, 0, a5.x, a5.y, a5.z, b5.x, b5.y, b5.z, 0, 1, 0, 0, 2, 1);

						}

					}

				}

			}
			if (GUI::Option("Modded T20")) {
				uint Handle = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				//hash2_EMP
				Vector3 null; null.x = 0.0, null.y = 0.0; null.z = 0.0;
				Vector3 a; a.x = 0.0, a.y = 1.61, a.z = -0.12;//X Coord - Y Coord - Z Coord
				Vector3 b; b.x = -12.0, b.y = 0.0, b.z = 0.0;//Pitch - Roll - Yaw
																//hash3_MiniGun
				Vector3 null1; null1.x = 0.0, null1.y = 0.0; null1.z = 0.0;
				Vector3 a1; a1.x = -0.60, a1.y = 1.60, a1.z = 0.20;
				Vector3 b1; b1.x = 0.0, b1.y = 0.0, b1.z = 88.0;
				//hash3_MiniGun2
				Vector3 null0; null0.x = 0.0, null0.y = 0.0; null0.z = 0.0;
				Vector3 a0; a0.x = 0.60, a0.y = 1.60, a0.z = 0.20;
				Vector3 b0; b0.x = 0.0, b0.y = 0.0, b0.z = 88.0;
				//hash4_FLWheel1
				Vector3 null2; null2.x = 0.0, null2.y = 0.0; null2.z = 0.0;
				Vector3 a2; a2.x = -0.94, a2.y = 1.32, a2.z = -0.25;
				Vector3 b2; b2.x = 9.0, b2.y = -28.0, b2.z = 87.0;
				//hash4_RLWheel1
				Vector3 null3; null3.x = 0.0, null3.y = 0.0; null3.z = 0.0;
				Vector3 a3; a3.x = -0.95, a3.y = -1.34, a3.z = -0.25f;
				Vector3 b3; b3.x = 9.0, b3.y = 38.0, b3.z = 87.0;
				//hash4_RFWheel1
				Vector3 null4; null4.x = 0.0, null4.y = 0.0; null4.z = 0.0;
				Vector3 a4; a4.x = 0.95, a4.y = 1.33, a4.z = -0.23;
				Vector3 b4; b4.x = 11.0, b4.y = 26.0, b4.z = -89.0;
				//hash4_RRWheel1
				Vector3 null5; null5.x = 0.0, null5.y = 0.0; null5.z = 0.0;
				Vector3 a5; a5.x = 0.96, a5.y = -1.31, a5.z = -0.23;
				Vector3 b5; b5.x = 10.0, b5.y = 20.0, b5.z = -92.0;

				int hash_T20 = GAMEPLAY::GET_HASH_KEY("t20");
				int hash2_EMP = GAMEPLAY::GET_HASH_KEY("hei_prop_heist_emp");
				int hash3_MiniGun = GAMEPLAY::GET_HASH_KEY("prop_minigun_01");
				int hash4_Wheel = GAMEPLAY::GET_HASH_KEY("prop_wheel_01");

				STREAMING::REQUEST_MODEL(hash_T20);
				STREAMING::REQUEST_MODEL(hash2_EMP);
				STREAMING::REQUEST_MODEL(hash3_MiniGun);
				STREAMING::REQUEST_MODEL(hash4_Wheel);

				if (STREAMING::HAS_MODEL_LOADED(hash_T20) && STREAMING::HAS_MODEL_LOADED(hash2_EMP) && STREAMING::HAS_MODEL_LOADED(hash3_MiniGun) && STREAMING::HAS_MODEL_LOADED(hash4_Wheel))
				{
					int EMP = OBJECT::CREATE_OBJECT(hash2_EMP, null.x, null.y, null.z, 1, 0, 1);
					int MiniGun = OBJECT::CREATE_OBJECT(hash3_MiniGun, null1.x, null1.y, null1.z, 1, 0, 1);
					int MiniGun2 = OBJECT::CREATE_OBJECT(hash3_MiniGun, null0.x, null0.y, null0.z, 1, 0, 1);
					int FLWheel1 = OBJECT::CREATE_OBJECT(hash4_Wheel, null2.x, null2.y, null2.z, 1, 0, 1);
					int RLWheel1 = OBJECT::CREATE_OBJECT(hash4_Wheel, null3.x, null3.y, null3.z, 1, 0, 1);
					int RFWheel1 = OBJECT::CREATE_OBJECT(hash4_Wheel, null4.x, null4.y, null4.z, 1, 0, 1);
					int RRWheel1 = OBJECT::CREATE_OBJECT(hash4_Wheel, null5.x, null5.y, null5.z, 1, 0, 1);

					if (ENTITY::DOES_ENTITY_EXIST(EMP) && ENTITY::DOES_ENTITY_EXIST(MiniGun) && ENTITY::DOES_ENTITY_EXIST(MiniGun2) && ENTITY::DOES_ENTITY_EXIST(FLWheel1) && ENTITY::DOES_ENTITY_EXIST(RLWheel1) && ENTITY::DOES_ENTITY_EXIST(RFWheel1) && ENTITY::DOES_ENTITY_EXIST(RRWheel1))
					{
						int Vehicle = VEHICLE::CREATE_VEHICLE(hash_T20, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);

						if (ENTITY::DOES_ENTITY_EXIST(Vehicle))
						{
							PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
							STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash_T20);
							ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, true);
							ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true, true);

							ENTITY::ATTACH_ENTITY_TO_ENTITY(EMP, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(MiniGun, Vehicle, 0, a1.x, a1.y, a1.z, b1.x, b1.y, b1.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(MiniGun2, Vehicle, 0, a0.x, a0.y, a0.z, b0.x, b0.y, b0.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(FLWheel1, Vehicle, 0, a2.x, a2.y, a2.z, b2.x, b2.y, b2.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(RLWheel1, Vehicle, 0, a3.x, a3.y, a3.z, b3.x, b3.y, b3.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(RFWheel1, Vehicle, 0, a4.x, a4.y, a4.z, b4.x, b4.y, b4.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(RRWheel1, Vehicle, 0, a5.x, a5.y, a5.z, b5.x, b5.y, b5.z, 0, 1, 0, 0, 2, 1);

						}

					}

				}

			}
			if (GUI::Option("Roller Coaster Car")) {
				uint Handle = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				//hash2_RollerCar
				Vector3 null; null.x = 0.0, null.y = 0.0; null.z = 0.0;
				Vector3 a; a.x = 0.0, a.y = 0.0, a.z = -0.5;//X Coord - Y Coord - Z Coord
				Vector3 b; b.x = 0.0, b.y = 0.0, b.z = 180.0;//Pitch - Roll - Yaw
																//hash3_Seats
				Vector3 null1; null1.x = 0.0, null1.y = 0.0; null1.z = 0.0;
				Vector3 a1; a1.x = 0.0, a1.y = 0.0, a1.z = 0.0;
				Vector3 b1; b1.x = 0.0, b1.y = 0.0, b1.z = 0.0;
				//hash3_FLWheel1
				Vector3 null2; null2.x = 0.0, null2.y = 0.0; null2.z = 0.0;
				Vector3 a2; a2.x = -0.97, a2.y = 1.0, a2.z = -0.25;
				Vector3 b2; b2.x = 0.0, b2.y = 0.0, b2.z = -89.0;
				//hash3_RLWheel1
				Vector3 null3; null3.x = 0.0, null3.y = 0.0; null3.z = 0.0;
				Vector3 a3; a3.x = -1.00, a3.y = -1.10, a3.z = -0.24;
				Vector3 b3; b3.x = 0.0, b3.y = 0.0, b3.z = -89.0;
				//hash3_RFWheel1
				Vector3 null4; null4.x = 0.0, null4.y = 0.0; null4.z = 0.0;
				Vector3 a4; a4.x = 0.97, a4.y = 1.00, a4.z = -0.24;
				Vector3 b4; b4.x = 0.0, b4.y = 0.0, b4.z = 89.0;
				//hash3_RRWheel1
				Vector3 null5; null5.x = 0.0, null5.y = 0.0; null5.z = 0.0;
				Vector3 a5; a5.x = 1.00, a5.y = -1.10, a5.z = -0.24;
				Vector3 b5; b5.x = 0.0, b5.y = 0.0, b5.z = 89.0;
				int hash_T20 = GAMEPLAY::GET_HASH_KEY("t20");
				int hash2_RollerCar = GAMEPLAY::GET_HASH_KEY("ind_prop_dlc_roller_car");
				int hash3_Seats = GAMEPLAY::GET_HASH_KEY("prop_hd_seats_01");
				int hash4_Wheel = GAMEPLAY::GET_HASH_KEY("prop_wheel_01");
				STREAMING::REQUEST_MODEL(hash_T20);
				STREAMING::REQUEST_MODEL(hash2_RollerCar);
				STREAMING::REQUEST_MODEL(hash3_Seats);
				STREAMING::REQUEST_MODEL(hash4_Wheel);
				if (STREAMING::HAS_MODEL_LOADED(hash_T20) && STREAMING::HAS_MODEL_LOADED(hash2_RollerCar) && STREAMING::HAS_MODEL_LOADED(hash3_Seats) && STREAMING::HAS_MODEL_LOADED(hash4_Wheel))
				{
					int RollerCar = OBJECT::CREATE_OBJECT(hash2_RollerCar, null.x, null.y, null.z, 1, 0, 1);
					int Seats = OBJECT::CREATE_OBJECT(hash3_Seats, null1.x, null1.y, null1.z, 1, 0, 1);
					int FLWheel1 = OBJECT::CREATE_OBJECT(hash4_Wheel, null2.x, null2.y, null2.z, 1, 0, 1);
					int RLWheel1 = OBJECT::CREATE_OBJECT(hash4_Wheel, null3.x, null3.y, null3.z, 1, 0, 1);
					int RFWheel1 = OBJECT::CREATE_OBJECT(hash4_Wheel, null4.x, null4.y, null4.z, 1, 0, 1);
					int RRWheel1 = OBJECT::CREATE_OBJECT(hash4_Wheel, null5.x, null5.y, null5.z, 1, 0, 1);
					if (ENTITY::DOES_ENTITY_EXIST(RollerCar) && ENTITY::DOES_ENTITY_EXIST(Seats) && ENTITY::DOES_ENTITY_EXIST(FLWheel1) && ENTITY::DOES_ENTITY_EXIST(RLWheel1) && ENTITY::DOES_ENTITY_EXIST(RFWheel1) && ENTITY::DOES_ENTITY_EXIST(RRWheel1))
					{
						int Vehicle = VEHICLE::CREATE_VEHICLE(hash_T20, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
						if (ENTITY::DOES_ENTITY_EXIST(Vehicle))
						{
							PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
							STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash_T20);
							ENTITY::SET_ENTITY_VISIBLE(Vehicle, false, false);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(RollerCar, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Seats, Vehicle, 0, a1.x, a1.y, a1.z, b1.x, b1.y, b1.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(FLWheel1, Vehicle, 0, a2.x, a2.y, a2.z, b2.x, b2.y, b2.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(RLWheel1, Vehicle, 0, a3.x, a3.y, a3.z, b3.x, b3.y, b3.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(RFWheel1, Vehicle, 0, a4.x, a4.y, a4.z, b4.x, b4.y, b4.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(RRWheel1, Vehicle, 0, a5.x, a5.y, a5.z, b5.x, b5.y, b5.z, 0, 1, 0, 0, 2, 1);
							ENTITY::SET_ENTITY_VISIBLE(Handle, true, true);

						}

					}

				}

			}
			if (GUI::Option("Boat And Trailer")) {
				uint Me = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Vector3 null; null.x = 0, null.y = 0; null.z = 0;
				Vector3 a; a.x = 0, a.y = -0.61, a.z = 0.28;
				Vector3 b; b.x = 0, b.y = 0, b.z = 0;
				int hash = GAMEPLAY::GET_HASH_KEY("boattrailer");
				int hash2 = GAMEPLAY::GET_HASH_KEY("suntrap");
				STREAMING::REQUEST_MODEL(hash);
				STREAMING::REQUEST_MODEL(hash2);
				if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
				{
					int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					int Object = VEHICLE::CREATE_VEHICLE(hash2, null.x, null.y, null.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object))
					{
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
						ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, false);
						ENTITY::SET_ENTITY_COLLISION(Object, 1, 0);

					}

				}

			}
			if (GUI::Option("Flat Bed And T20")) {
				uint Me = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Vector3 null; null.x = 0, null.y = 0; null.z = 0;
				Vector3 a; a.x = 0, a.y = -2.0, a.z = 1.1;
				Vector3 b; b.x = 0, b.y = 0, b.z = 0;
				Vector3 null1; null1.x = 0, null1.y = 0; null1.z = 0;
				Vector3 a1; a1.x = -1.06, a1.y = -0.1, a1.z = 0.46;
				Vector3 b1; b1.x = 91.0, b1.y = 0, b1.z = 0;
				Vector3 null2; null2.x = 0, null2.y = 0; null2.z = 0;
				Vector3 a2; a2.x = -0.9, a2.y = 0.61, a2.z = 0.62;
				Vector3 b2; b2.x = 0.0, b2.y = 100.0, b2.z = 0;
				Vector3 null3; null3.x = 0, null3.y = 0; null3.z = 0;
				Vector3 a3; a3.x = 0.9, a3.y = 0.8, a3.z = 0.41;
				Vector3 b3; b3.x = -25.0, b3.y = 0, b3.z = 0;
				int hash = GAMEPLAY::GET_HASH_KEY("flatbed");
				int hash2 = GAMEPLAY::GET_HASH_KEY("t20");
				int hash3 = GAMEPLAY::GET_HASH_KEY("prop_tool_broom");
				int hash4 = GAMEPLAY::GET_HASH_KEY("prop_roadcone01a");
				int hash5 = GAMEPLAY::GET_HASH_KEY("prop_tool_box_02");
				STREAMING::REQUEST_MODEL(hash);
				STREAMING::REQUEST_MODEL(hash2);
				STREAMING::REQUEST_MODEL(hash3);
				STREAMING::REQUEST_MODEL(hash4);
				STREAMING::REQUEST_MODEL(hash5);
				if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2) && STREAMING::HAS_MODEL_LOADED(hash3) && STREAMING::HAS_MODEL_LOADED(hash4) && STREAMING::HAS_MODEL_LOADED(hash5))
				{
					int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					int Object = VEHICLE::CREATE_VEHICLE(hash2, null.x, null.y, null.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					int Broom = OBJECT::CREATE_OBJECT(hash3, null1.x, null1.y, null1.z, 1, 0, 1);
					int Cone = OBJECT::CREATE_OBJECT(hash4, null2.x, null2.y, null2.z, 1, 0, 1);
					int Tool = OBJECT::CREATE_OBJECT(hash5, null3.x, null3.y, null3.z, 1, 0, 1);
					if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object) && ENTITY::DOES_ENTITY_EXIST(Broom) && ENTITY::DOES_ENTITY_EXIST(Cone) && ENTITY::DOES_ENTITY_EXIST(Tool))
					{
						PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
						VEHICLE::SET_VEHICLE_MOD_KIT(Object, 0);
						VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(Object, "Project");
						VEHICLE::SET_VEHICLE_WINDOW_TINT(Object, 5);
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
						ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, false);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Broom, Vehicle, 0, a1.x, a1.y, a1.z, b1.x, b1.y, b1.z, 0, false, 0, 0, 2, true);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Cone, Vehicle, 0, a2.x, a2.y, a2.z, b2.x, b2.y, b2.z, 0, false, 0, 0, 2, true);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Tool, Vehicle, 0, a3.x, a3.y, a3.z, b3.x, b3.y, b3.z, 0, false, 0, 0, 2, true);
						ENTITY::SET_ENTITY_COLLISION(Object, 1, 0);

					}

				}

			}
			if (GUI::Option("JetSki And Trailer")) {
				uint Me = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Vector3 null; null.x = 0, null.y = 0; null.z = 0.;
				Vector3 a; a.x = -0.625, a.y = -1.9, a.z = -0.09;
				Vector3 b; b.x = 0, b.y = 0, b.z = 0;
				Vector3 a1; a1.x = 0.625, a1.y = -1.9, a1.z = -0.09;
				Vector3 b1; b1.x = 0, b1.y = 0, b1.z = 0;

				Vector3 a2; a2.x = 0.0, a2.y = 0.9, a2.z = -0.45;
				Vector3 b2; b2.x = 0, b2.y = 0, b2.z = 180.0;

				int hash = GAMEPLAY::GET_HASH_KEY("boattrailer");
				int hash2 = GAMEPLAY::GET_HASH_KEY("seashark");
				int hash3 = GAMEPLAY::GET_HASH_KEY("prop_tool_box_05");
				STREAMING::REQUEST_MODEL(hash);
				STREAMING::REQUEST_MODEL(hash2);
				STREAMING::REQUEST_MODEL(hash3);

				if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2) && STREAMING::HAS_MODEL_LOADED(hash3))
				{
					int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					int Object = VEHICLE::CREATE_VEHICLE(hash2, null.x, null.y, null.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					int Object1 = VEHICLE::CREATE_VEHICLE(hash2, null.x, null.y, null.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					int Object2 = OBJECT::CREATE_OBJECT(hash3, null.x, null.y, null.z, 1, 0, 1);
					if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object) && ENTITY::DOES_ENTITY_EXIST(Object1) && ENTITY::DOES_ENTITY_EXIST(Object2))
					{
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
						ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, false);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Object1, Vehicle, 0, a1.x, a1.y, a1.z, b1.x, b1.y, b1.z, 0, false, 0, 0, 2, true);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Object2, Vehicle, 0, a2.x, a2.y, a2.z, b2.x, b2.y, b2.z, 0, false, 0, 0, 2, true);
						ENTITY::SET_ENTITY_COLLISION(Object, 1, 0);
						ENTITY::SET_ENTITY_COLLISION(Object1, 1, 0);

					}

				}

			}
			if (GUI::Option("Ramp Truck")) {
				uint Me = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Vector3 null; null.x = 0, null.y = 0; null.z = 0;
				Vector3 a; a.x = 0, a.y = 10.0, a.z = -0.3;
				Vector3 b; b.x = 0, b.y = -147.0, b.z = 90.0;
				int hash = GAMEPLAY::GET_HASH_KEY("phantom");
				int hash2 = GAMEPLAY::GET_HASH_KEY("prop_lev_des_barge_01");
				STREAMING::REQUEST_MODEL(hash);
				STREAMING::REQUEST_MODEL(hash2);
				if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
				{
					int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					int Object = OBJECT::CREATE_OBJECT(hash2, null.x, null.y, null.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object))
					{
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
						PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
						ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, false);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);
						ENTITY::SET_ENTITY_COLLISION(Object, 1, 0);

					}

				}

			}
			if (GUI::Option("Monster Swat")) {
				uint Me = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Vector3 null; null.x = 0, null.y = 0; null.z = 0;
				Vector3 a; a.x = 0, a.y = 0, a.z = 0;
				Vector3 b; b.x = 0, b.y = 0, b.z = 0;
				int hash = GAMEPLAY::GET_HASH_KEY("monster");
				int hash2 = GAMEPLAY::GET_HASH_KEY("riot");
				STREAMING::REQUEST_MODEL(hash);
				STREAMING::REQUEST_MODEL(hash2);
				if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
				{
					int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					int Object = VEHICLE::CREATE_VEHICLE(hash2, null.x, null.y, null.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object))
					{
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
						PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
						ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, false);
						VEHICLE::SET_VEHICLE_MOD_KIT(Object, 0);
						VEHICLE::SET_VEHICLE_WINDOW_TINT(Object, 5);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);

					}

				}

			}
			if (GUI::Option("Buffulo Police")) {
				uint Me = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Vector3 null; null.x = 0, null.y = 0; null.z = 0;
				Vector3 a; a.x = 0, a.y = 0, a.z = 0;
				Vector3 b; b.x = 0, b.y = 0, b.z = 0;
				int hash = GAMEPLAY::GET_HASH_KEY("police2");
				int hash2 = GAMEPLAY::GET_HASH_KEY("buffalo2");
				STREAMING::REQUEST_MODEL(hash);
				STREAMING::REQUEST_MODEL(hash2);
				if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
				{
					int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					int Object = VEHICLE::CREATE_VEHICLE(hash2, null.x, null.y, null.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object))
					{
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
						PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
						ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, false);
						VEHICLE::SET_VEHICLE_MOD_KIT(Object, 0);
						VEHICLE::SET_VEHICLE_WINDOW_TINT(Object, 5);
						VEHICLE::SET_VEHICLE_WINDOW_TINT(Vehicle, 5);
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object, 0, 0, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object, 0, 0, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle, 0, 0, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle, 0, 0, 0);
						VEHICLE::SET_VEHICLE_EXTRA_COLOURS(Object, 0, 0);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);

					}

				}

			}
			if (GUI::Option("Insurgent 3")) {
				uint Me = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Vector3 null; null.x = 0, null.y = 0; null.z = 0;
				Vector3 a; a.x = 0, a.y = 0, a.z = 0;
				Vector3 b; b.x = 0, b.y = 0, b.z = 0;
				int hash = GAMEPLAY::GET_HASH_KEY("insurgent");
				int hash2 = GAMEPLAY::GET_HASH_KEY("insurgent2");
				STREAMING::REQUEST_MODEL(hash);
				STREAMING::REQUEST_MODEL(hash2);
				if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
				{
					int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					int Object = VEHICLE::CREATE_VEHICLE(hash2, null.x, null.y, null.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object))
					{
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
						PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
						ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, false);
						VEHICLE::SET_VEHICLE_MOD_KIT(Object, 0);
						VEHICLE::SET_VEHICLE_WINDOW_TINT(Object, 5);
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object, 0, 0, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object, 0, 0, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle, 0, 0, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle, 0, 0, 0);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);

					}

				}

			}
			if (GUI::Option("Super 1")) {
				uint Me = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Vector3 null; null.x = 0, null.y = 0; null.z = 0;
				Vector3 a; a.x = 0, a.y = 0, a.z = -0.25;
				Vector3 b; b.x = 0, b.y = 0, b.z = 0;
				int hash = GAMEPLAY::GET_HASH_KEY("t20");
				int hash2 = GAMEPLAY::GET_HASH_KEY("cheetah");
				STREAMING::REQUEST_MODEL(hash);
				STREAMING::REQUEST_MODEL(hash2);
				if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
				{
					int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					int Object = VEHICLE::CREATE_VEHICLE(hash2, null.x, null.y, null.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object))
					{
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
						PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
						ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, false);
						VEHICLE::SET_VEHICLE_MOD_KIT(Object, 0);
						VEHICLE::SET_VEHICLE_WINDOW_TINT(Object, 5);
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object, 0, 0, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object, 0, 0, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle, 0, 0, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle, 0, 0, 0);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);

					}

				}

			}
			if (GUI::Option("Super 2")) {
				uint Me = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Vector3 null; null.x = 0, null.y = 0; null.z = 0;
				Vector3 a; a.x = 0, a.y = 0, a.z = 0;
				Vector3 b; b.x = 0, b.y = 0, b.z = 0;
				int hash = GAMEPLAY::GET_HASH_KEY("feltzer2");
				int hash2 = GAMEPLAY::GET_HASH_KEY("rapidgt");
				STREAMING::REQUEST_MODEL(hash);
				STREAMING::REQUEST_MODEL(hash2);
				if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
				{
					int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					int Object = VEHICLE::CREATE_VEHICLE(hash2, null.x, null.y, null.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object))
					{
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
						PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
						ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, false);
						VEHICLE::SET_VEHICLE_MOD_KIT(Object, 0);
						VEHICLE::SET_VEHICLE_WINDOW_TINT(Object, 5);
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object, 0, 0, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object, 0, 0, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle, 0, 0, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle, 0, 0, 0);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);

					}

				}

			}
			if (GUI::Option("Muscle 1")) {
				uint Me = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Vector3 null; null.x = 0.0f, null.y = 0.0f; null.z = 0.0f;
				Vector3 a; a.x = 0.0f, a.y = 0.0f, a.z = -0.2f;
				Vector3 b; b.x = 0.0f, b.y = 0.0f, b.z = 0.0f;
				int hash = GAMEPLAY::GET_HASH_KEY("hotknife");
				int hash2 = GAMEPLAY::GET_HASH_KEY("jb700");
				STREAMING::REQUEST_MODEL(hash);
				STREAMING::REQUEST_MODEL(hash2);
				if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
				{
					int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					int Object = VEHICLE::CREATE_VEHICLE(hash2, null.x, null.y, null.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object))
					{
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
						PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
						ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, false);
						VEHICLE::SET_VEHICLE_MOD_KIT(Object, 0);
						VEHICLE::SET_VEHICLE_WINDOW_TINT(Object, 5);
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object, 0, 0, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object, 0, 0, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle, 0, 0, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle, 0, 0, 0);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);

					}

				}

			}
			if (GUI::Option("Muscle 2")) {
				uint Me = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Vector3 null; null.x = 0.0f, null.y = 0.0f; null.z = 0.0f;
				Vector3 a; a.x = 0.0f, a.y = 0.0f, a.z = 2.0f;
				Vector3 b; b.x = 0.0f, b.y = 0.0f, b.z = 0.0f;
				int hash = GAMEPLAY::GET_HASH_KEY("coquette2");
				int hash2 = GAMEPLAY::GET_HASH_KEY("hotknife");
				STREAMING::REQUEST_MODEL(hash);
				STREAMING::REQUEST_MODEL(hash2);
				if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
				{
					int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					int Object = VEHICLE::CREATE_VEHICLE(hash2, null.x, null.y, null.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object))
					{
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
						PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
						ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, false);
						VEHICLE::SET_VEHICLE_MOD_KIT(Object, 0);
						VEHICLE::SET_VEHICLE_WINDOW_TINT(Object, 5);
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object, 0, 0, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object, 0, 0, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle, 0, 0, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle, 0, 0, 0);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);

					}

				}

			}
			if (GUI::Option("Special")) {
				uint Me = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Vector3 null; null.x = 0.0f, null.y = 0.0f; null.z = 0.0f;
				Vector3 a; a.x = 0.0f, a.y = 0.0f, a.z = 0.0f;
				Vector3 b; b.x = 0.0f, b.y = 0.0f, b.z = 0.0f;
				int hash = GAMEPLAY::GET_HASH_KEY("zentorno");
				int hash2 = GAMEPLAY::GET_HASH_KEY("kuruma2");
				STREAMING::REQUEST_MODEL(hash);
				STREAMING::REQUEST_MODEL(hash2);
				if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
				{
					int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					int Object = VEHICLE::CREATE_VEHICLE(hash2, null.x, null.y, null.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object))
					{
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
						PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
						ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, false);
						VEHICLE::SET_VEHICLE_MOD_KIT(Object, 0);
						VEHICLE::SET_VEHICLE_WINDOW_TINT(Object, 5);
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object, 0, 0, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object, 0, 0, 0);
						VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(Object, "Project");
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle, 0, 0, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle, 0, 0, 0);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);

					}

				}

			}
			if (GUI::Option("Sub Copter")) {
				uint Me = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Vector3 null; null.x = 0, null.y = 0; null.z = 0;
				Vector3 a; a.x = 0.0f, a.y = 1.0f, a.z = 0.8f;
				Vector3 b; b.x = 0.0f, b.y = 0.0f, b.z = 0.0f;
				int hash = GAMEPLAY::GET_HASH_KEY("buzzard");
				int hash2 = GAMEPLAY::GET_HASH_KEY("submersible");
				STREAMING::REQUEST_MODEL(hash);
				STREAMING::REQUEST_MODEL(hash2);
				if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
				{
					int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					int Object = VEHICLE::CREATE_VEHICLE(hash2, null.x, null.y, null.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object))
					{
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
						PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
						ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, false);
						VEHICLE::SET_VEHICLE_MOD_KIT(Object, 0);
						VEHICLE::SET_VEHICLE_WINDOW_TINT(Object, 5);
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object, 0, 0, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object, 0, 0, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle, 255, 149, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle, 0, 0, 0);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);

					}

				}

			}
			if (GUI::Option("Slam Van")) {
				uint Me = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Vector3 null; null.x = 0, null.y = 0; null.z = 0;
				Vector3 a; a.x = 0, a.y = -2.0, a.z = 1.1;
				Vector3 b; b.x = 0, b.y = 0, b.z = 0;
				Vector3 null1; null1.x = 0, null1.y = 0; null1.z = 0;
				Vector3 a1; a1.x = -1.06, a1.y = -0.1, a1.z = 0.46;
				Vector3 b1; b1.x = 91.0, b1.y = 0, b1.z = 0;
				Vector3 null2; null2.x = 0, null2.y = 0; null2.z = 0;
				Vector3 a2; a2.x = -0.9, a2.y = 0.61, a2.z = 0.62;
				Vector3 b2; b2.x = 0.0, b2.y = 100.0, b2.z = 0;
				Vector3 null3; null3.x = 0, null3.y = 0; null3.z = 0;
				Vector3 a3; a3.x = 0.9, a3.y = 0.8, a3.z = 0.41;
				Vector3 b3; b3.x = -25.0, b3.y = 0, b3.z = 0;
				int hash = GAMEPLAY::GET_HASH_KEY("flatbed");
				int hash2 = GAMEPLAY::GET_HASH_KEY("slamvan2");
				int hash3 = GAMEPLAY::GET_HASH_KEY("prop_tool_broom");
				int hash4 = GAMEPLAY::GET_HASH_KEY("prop_roadcone01a");
				int hash5 = GAMEPLAY::GET_HASH_KEY("prop_tool_box_02");
				STREAMING::REQUEST_MODEL(hash);
				STREAMING::REQUEST_MODEL(hash2);
				STREAMING::REQUEST_MODEL(hash3);
				STREAMING::REQUEST_MODEL(hash4);
				STREAMING::REQUEST_MODEL(hash5);
				if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2) && STREAMING::HAS_MODEL_LOADED(hash3) && STREAMING::HAS_MODEL_LOADED(hash4) && STREAMING::HAS_MODEL_LOADED(hash5))
				{
					int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					int Object = VEHICLE::CREATE_VEHICLE(hash2, null.x, null.y, null.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					int Broom = OBJECT::CREATE_OBJECT(hash3, null1.x, null1.y, null1.z, 1, 0, 1);
					int Cone = OBJECT::CREATE_OBJECT(hash4, null2.x, null2.y, null2.z, 1, 0, 1);
					int Tool = OBJECT::CREATE_OBJECT(hash5, null3.x, null3.y, null3.z, 1, 0, 1);
					if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object) && ENTITY::DOES_ENTITY_EXIST(Broom) && ENTITY::DOES_ENTITY_EXIST(Cone) && ENTITY::DOES_ENTITY_EXIST(Tool))
					{
						PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
						VEHICLE::SET_VEHICLE_MOD_KIT(Object, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object, 8, 17, 30);
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object, 0, 30, 1);
						VEHICLE::SET_VEHICLE_EXTRA_COLOURS(Object, 92, 0);
						VEHICLE::SET_VEHICLE_COLOURS(Object, 12, 53);
						VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(Object, "Project");
						VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(Object, 1);
						VEHICLE::TOGGLE_VEHICLE_MOD(Object, 18, 1);
						VEHICLE::TOGGLE_VEHICLE_MOD(Object, 22, 1);
						VEHICLE::SET_VEHICLE_MOD(Object, 11, 3, 0);
						VEHICLE::SET_VEHICLE_MOD(Object, 14, 14, 0);
						VEHICLE::SET_VEHICLE_MOD(Object, 15, 3, 0);
						VEHICLE::SET_VEHICLE_MOD(Object, 13, 2, 0);
						VEHICLE::SET_VEHICLE_WHEEL_TYPE(Object, 6);
						VEHICLE::SET_VEHICLE_WINDOW_TINT(Object, 5);
						VEHICLE::SET_VEHICLE_MOD(Object, 23, 18, 1);
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
						ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, false);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Broom, Vehicle, 0, a1.x, a1.y, a1.z, b1.x, b1.y, b1.z, 0, false, 0, 0, 2, true);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Cone, Vehicle, 0, a2.x, a2.y, a2.z, b2.x, b2.y, b2.z, 0, false, 0, 0, 2, true);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Tool, Vehicle, 0, a3.x, a3.y, a3.z, b3.x, b3.y, b3.z, 0, false, 0, 0, 2, true);

					}

				}

			}
			if (GUI::Option("Flying 5 Seater")) {
				uint Me = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Vector3 null; null.x = 0, null.y = 0; null.z = 0.;

				Vector3 a; a.x = 0.0, a.y = 0.0, a.z = 0.6;		// seashark 1 - 0.7 worked just hard to get on .. infront and behind wings only way to get on the sharks ...
				Vector3 b; b.x = 0, b.y = 0, b.z = 0;

				Vector3 a1; a1.x = 0.0, a1.y = -4.0, a1.z = 0.6;  // seashark 2
				Vector3 b1; b1.x = 0, b1.y = 0, b1.z = 0;


				Vector3 a2; a2.x = 0.0, a2.y = 0.9, a2.z = -0.45;
				Vector3 b2; b2.x = 0, b2.y = 0, b2.z = 180.0;

				int hash = GAMEPLAY::GET_HASH_KEY("hydra");
				int hash2 = GAMEPLAY::GET_HASH_KEY("seashark");
				int hash3 = GAMEPLAY::GET_HASH_KEY("prop_tool_box_05"); // turn this into something usefull maybe another sea shark ...
				STREAMING::REQUEST_MODEL(hash);
				STREAMING::REQUEST_MODEL(hash2);
				STREAMING::REQUEST_MODEL(hash3);

				if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2) && STREAMING::HAS_MODEL_LOADED(hash3))
				{
					int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					int Object = VEHICLE::CREATE_VEHICLE(hash2, null.x, null.y, null.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					int Object1 = VEHICLE::CREATE_VEHICLE(hash2, null.x, null.y, null.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					int Object2 = OBJECT::CREATE_OBJECT(hash3, null.x, null.y, null.z, 1, 0, 1);
					if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object) && ENTITY::DOES_ENTITY_EXIST(Object1) && ENTITY::DOES_ENTITY_EXIST(Object2))
					{
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
						ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, false);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Object1, Vehicle, 0, a1.x, a1.y, a1.z, b1.x, b1.y, b1.z, 0, false, 0, 0, 2, true);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Object2, Vehicle, 0, a2.x, a2.y, a2.z, b2.x, b2.y, b2.z, 0, false, 0, 0, 2, true);
						ENTITY::SET_ENTITY_COLLISION(Object, 1, 0);
						ENTITY::SET_ENTITY_COLLISION(Object1, 1, 0);

					}

				}

			}
			if (GUI::Option("Panto/HotKnife")) {
				uint Handle = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				//hash2_PANTO
				Vector3 null; null.x = 0.0, null.y = 0.0; null.z = 0.0;
				Vector3 a; a.x = 0.0, a.y = 0.0, a.z = -0.2;//X Coord - Y Coord - Z Coord
				Vector3 b; b.x = 0.0, b.y = 0.0, b.z = 0.0;//Pitch - Roll - Yaw
															//hash3_MiniGun
				Vector3 null1; null1.x = 0.0, null1.y = 0.0; null1.z = 0.0;
				Vector3 a1; a1.x = -0.60, a1.y = 1.60, a1.z = 0.20;
				Vector3 b1; b1.x = 0.0, b1.y = 0.0, b1.z = 88.0;
				//hash3_MiniGun2
				Vector3 null0; null0.x = 0.0, null0.y = 0.0; null0.z = 0.0;
				Vector3 a0; a0.x = 0.60, a0.y = 1.60, a0.z = 0.20;
				Vector3 b0; b0.x = 0.0, b0.y = 0.0, b0.z = 88.0;
				//hash4_WindScreen _ VANISHED NEEDS FIXING
				Vector3 null2; null2.x = 0.0, null2.y = 0.0; null2.z = 0.0;
				Vector3 a2; a2.x = 0.3, a2.y = 0.41, a2.z = 0.50;
				Vector3 b2; b2.x = -45.3, b2.y = 0.0, b2.z = -179.0;//87
																	//hash4_RLWheel1
				Vector3 null3; null3.x = 0.0, null3.y = 0.0; null3.z = 0.0;
				Vector3 a3; a3.x = -0.90, a3.y = -1.2, a3.z = 0.0; // -0.23
				Vector3 b3; b3.x = 0.0, b3.y = 0.0, b3.z = 86.0;
				//hash4_RFWindScreen 
				Vector3 null4; null4.x = 0.0, null4.y = 0.0; null4.z = 0.0;
				Vector3 a4; a4.x = -0.3, a4.y = 0.41, a4.z = 0.5;
				Vector3 b4; b4.x = -45.3, b4.y = 0.0, b4.z = -179.0;
				//hash4_RRWheel1
				Vector3 null5; null5.x = 0.0, null5.y = 0.0; null5.z = 0.0;
				Vector3 a5; a5.x = 0.92, a5.y = -1.2, a5.z = 0.01;
				Vector3 b5; b5.x = 0.0, b5.y = 0.0, b5.z = -92.0;
				//PUNTO -- FUCK UP NEEDS FIXING 
				Vector3 null6; null6.x = 0, null6.y = 0; null6.z = 0;
				Vector3 a6; a6.x = 0.0, a6.y = 0.0, a6.z = -0.2;
				Vector3 b6; b6.x = 0.0, b6.y = 0.0, b6.z = 0.0;
				//SIDES LEFT
				Vector3 null7; null7.x = 0, null7.y = 0; null7.z = 0;
				Vector3 a7; a7.x = -0.75, a7.y = 0.7, a7.z = -0.3;
				Vector3 b7; b7.x = 90.0, b7.y = 0.0, b7.z = 0.0;
				//SIDES RIGHT
				Vector3 null8; null8.x = 0, null8.y = 0; null8.z = 0;
				Vector3 a8; a8.x = 0.75, a8.y = 0.7, a8.z = -0.3;
				Vector3 b8; b8.x = 90.0, b8.y = 0.0, b8.z = 0.0;

				int hash = GAMEPLAY::GET_HASH_KEY("hotknife");
				int hash2_EMP = GAMEPLAY::GET_HASH_KEY("hei_prop_heist_emp");
				int hash3_MiniGun = GAMEPLAY::GET_HASH_KEY("prop_minigun_01");
				int hash4_Wheel = GAMEPLAY::GET_HASH_KEY("prop_wheel_01");
				int hash2 = GAMEPLAY::GET_HASH_KEY("panto");
				int hashWindow = GAMEPLAY::GET_HASH_KEY("prop_ballistic_shield");
				int hashSides = GAMEPLAY::GET_HASH_KEY("prop_cons_plank");




				STREAMING::REQUEST_MODEL(hashWindow);// WINDOW
				STREAMING::REQUEST_MODEL(hash2_EMP); // PANTO
				STREAMING::REQUEST_MODEL(hash3_MiniGun); // GUNS
				STREAMING::REQUEST_MODEL(hash4_Wheel); // back wheels
				STREAMING::REQUEST_MODEL(hash);
				STREAMING::REQUEST_MODEL(hash2);
				STREAMING::REQUEST_MODEL(hashSides); // SIDE SKIRTS

				if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hashSides) && STREAMING::HAS_MODEL_LOADED(hashWindow) && STREAMING::HAS_MODEL_LOADED(hash2_EMP) && STREAMING::HAS_MODEL_LOADED(hash3_MiniGun) && STREAMING::HAS_MODEL_LOADED(hash2) && STREAMING::HAS_MODEL_LOADED(hash4_Wheel))
				{
					int EMP = OBJECT::CREATE_OBJECT(hash2_EMP, null.x, null.y, null.z, 1, 0, 1);
					int MiniGun = OBJECT::CREATE_OBJECT(hash3_MiniGun, null1.x, null1.y, null1.z, 1, 0, 1);
					int MiniGun2 = OBJECT::CREATE_OBJECT(hash3_MiniGun, null0.x, null0.y, null0.z, 1, 0, 1);
					int WINDOW_1 = OBJECT::CREATE_OBJECT(hashWindow, null2.x, null2.y, null2.z, 1, 0, 1);
					int RLWheel1 = OBJECT::CREATE_OBJECT(hash4_Wheel, null3.x, null3.y, null3.z, 1, 0, 1);
					int WINDOW_2 = OBJECT::CREATE_OBJECT(hashWindow, null4.x, null4.y, null4.z, 1, 0, 1);
					int RRWheel1 = OBJECT::CREATE_OBJECT(hash4_Wheel, null5.x, null5.y, null5.z, 1, 0, 1);
					int Object = VEHICLE::CREATE_VEHICLE(hash2, null.x, null.y, null.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
					int LeftSide = OBJECT::CREATE_OBJECT(hashSides, null7.x, null7.y, null7.z, 1, 0, 1);
					int RightSide = OBJECT::CREATE_OBJECT(hashSides, null8.x, null8.y, null8.z, 1, 0, 1);


					if (ENTITY::DOES_ENTITY_EXIST(EMP) && ENTITY::DOES_ENTITY_EXIST(LeftSide) && ENTITY::DOES_ENTITY_EXIST(RightSide) && ENTITY::DOES_ENTITY_EXIST(MiniGun) && ENTITY::DOES_ENTITY_EXIST(MiniGun2) && ENTITY::DOES_ENTITY_EXIST(WINDOW_1) && ENTITY::DOES_ENTITY_EXIST(RLWheel1) && ENTITY::DOES_ENTITY_EXIST(WINDOW_2) && ENTITY::DOES_ENTITY_EXIST(RRWheel1))
					{
						int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);

						if (ENTITY::DOES_ENTITY_EXIST(Vehicle))
						{
							PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
							STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
							ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, false);
							ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true, false);
							STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
							PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
							ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, false);
							VEHICLE::SET_VEHICLE_MOD_KIT(Object, 0);
							VEHICLE::SET_VEHICLE_WINDOW_TINT(Object, 5);
							VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object, 0, 0, 0);
							VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object, 0, 0, 0);
							VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle, 0, 0, 0);
							VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle, 0, 0, 0);
							VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(Vehicle, "sm");
							VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(Object, "sm");
							VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(Vehicle, 1);
							VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(Object, 1);

							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(EMP, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(MiniGun, Vehicle, 0, a1.x, a1.y, a1.z, b1.x, b1.y, b1.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(MiniGun2, Vehicle, 0, a0.x, a0.y, a0.z, b0.x, b0.y, b0.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(WINDOW_1, Vehicle, 0, a2.x, a2.y, a2.z, b2.x, b2.y, b2.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(RLWheel1, Vehicle, 0, a3.x, a3.y, a3.z, b3.x, b3.y, b3.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(WINDOW_2, Vehicle, 0, a4.x, a4.y, a4.z, b4.x, b4.y, b4.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(RRWheel1, Vehicle, 0, a5.x, a5.y, a5.z, b5.x, b5.y, b5.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(LeftSide, Vehicle, 0, a7.x, a7.y, a7.z, b7.x, b7.y, b7.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(RightSide, Vehicle, 0, a8.x, a8.y, a8.z, b8.x, b8.y, b8.z, 0, 1, 0, 0, 2, 1);


						}

					}

				}

			}
			if (GUI::Option("Monster Digger")) {
				uint Handle = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				//hash2_Dozer
				Vector3 null; null.x = 0.0, null.y = 0.0; null.z = 0.0;
				Vector3 a; a.x = 0.0, a.y = 0.0, a.z = -0.4;   //X Coord - Y Coord - Z Coord
				Vector3 b; b.x = 0.0, b.y = 0.0, b.z = 0.0;   //Pitch - Roll - Yaw
																//hash3_MiniGun LEFT
				Vector3 null1; null1.x = 0.0, null1.y = 0.0; null1.z = 0.0;
				Vector3 a1; a1.x = -0.70, a1.y = 1.80, a1.z = 0.98;
				Vector3 b1; b1.x = 0.0, b1.y = 0.0, b1.z = 88.0;
				//hash3_MiniGun2 RIGHT
				Vector3 null0; null0.x = 0.0, null0.y = 0.0; null0.z = 0.0;
				Vector3 a0; a0.x = 0.70, a0.y = 1.80, a0.z = 0.98;
				Vector3 b0; b0.x = 0.0, b0.y = 0.0, b0.z = 88.0;
				//hash4_Left BLUE left
				Vector3 null2; null2.x = 0.0, null2.y = 0.0; null2.z = 0.0;
				Vector3 a2; a2.x = -0.31, a2.y = 2.51, a2.z = 0.55;
				Vector3 b2; b2.x = 0.0, b2.y = 0.0, b2.z = -175.0;//87 - 179
																	//hash4_NIONS LEFT/back
				Vector3 null3; null3.x = 0.0, null3.y = 0.0; null3.z = 0.0;
				Vector3 a3; a3.x = 0.5, a3.y = -3.0, a3.z = -0.36; // -0.23
				Vector3 b3; b3.x = 0.0, b3.y = 0.0, b3.z = 86.0;
				//hash4_Right BLUE LIGHT
				Vector3 null4; null4.x = 0.0, null4.y = 0.0; null4.z = 0.0;
				Vector3 a4; a4.x = 0.31, a4.y = 2.51, a4.z = 0.55;
				Vector3 b4; b4.x = 0.0, b4.y = 0.0, b4.z = -175.0;
				//hash4_NIONS RIGHT
				Vector3 null5; null5.x = 0.0, null5.y = 0.0; null5.z = 0.0;
				Vector3 a5; a5.x = 0.92, a5.y = -2.0, a5.z = 0.01;
				Vector3 b5; b5.x = 0.0, b5.y = 0.0, b5.z = 89.0;
				//ENGINE
				Vector3 null6; null6.x = 0, null6.y = 0; null6.z = 0;
				Vector3 a6; a6.x = 0.0, a6.y = 1.76, a6.z = 0.86;
				Vector3 b6; b6.x = -0.0, b6.y = 0.0, b6.z = 0.0;
				//SIDES LEFT EMP
				Vector3 null7; null7.x = 0, null7.y = 0; null7.z = 0;
				Vector3 a7; a7.x = -0.88, a7.y = -1.8, a7.z = 1.0;
				Vector3 b7; b7.x = 0.0, b7.y = -51.9, b7.z = 0.0;
				//SIDES RIGHT EMP
				Vector3 null8; null8.x = 0, null8.y = 0; null8.z = 0;
				Vector3 a8; a8.x = 0.88, a8.y = -1.8, a8.z = 1.0;
				Vector3 b8; b8.x = 0.0, b8.y = 51.9, b8.z = 0.0;
				//BEAR
				Vector3 null9; null9.x = 0, null9.y = 0; null9.z = 0;
				Vector3 a9; a9.x = -1.0, a9.y = 2.7, a9.z = -0.4;
				Vector3 b9; b9.x = 0.0, b9.y = 0.0, b9.z = 156.5;
				//SPIKES
				Vector3 null10; null10.x = 0, null10.y = 0; null10.z = 0;
				Vector3 a10; a10.x = -0.12, a10.y = 0.59, a10.z = 1.9;
				Vector3 b10; b10.x = 0.0, b10.y = 0.0, b10.z = 0.0;

				int hash = GAMEPLAY::GET_HASH_KEY("monster");				// Monster Truck
				int hash1 = GAMEPLAY::GET_HASH_KEY("prop_car_engine_01");	// Car Engine
				int hash2 = GAMEPLAY::GET_HASH_KEY("bulldozer");			// Dozer
																			//int hash3 = GAMEPLAY::GET_HASH_KEY("prop_minigun_01");		// Mini GUn 
																			//int hash4 = GAMEPLAY::GET_HASH_KEY("v_ilev_uvcheetah");		// Nion Lights <-- needs changing
																			//int hash5 = GAMEPLAY::GET_HASH_KEY("prop_air_lights_05a");	// Blue Lights	
																			//int hash6 = GAMEPLAY::GET_HASH_KEY("hei_prop_heist_emp");	// Emp Lights	
																			//int hash7 = GAMEPLAY::GET_HASH_KEY("prop_mem_teddy_02");	// Large Teddy	
																			//int hash8 = GAMEPLAY::GET_HASH_KEY("p_stinger_04");			// Stinger Spikes

				STREAMING::REQUEST_MODEL(hash); 	// MONSTER
				STREAMING::REQUEST_MODEL(hash1); 	// Car Engine
				STREAMING::REQUEST_MODEL(hash2); 	// DOZER
													//STREAMING::REQUEST_MODEL(hash3); 	// GUNS
													//STREAMING::REQUEST_MODEL(hash4); 	// Nion Lights
													//STREAMING::REQUEST_MODEL(hash5);	// Blue Lights
													//STREAMING::REQUEST_MODEL(hash6); 	// Emp Lights
													//STREAMING::REQUEST_MODEL(hash7); 	// Large Teddy
													//STREAMING::REQUEST_MODEL(hash8); 	// SPIKES

				if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash1) && STREAMING::HAS_MODEL_LOADED(hash2))
				{
					int Object = VEHICLE::CREATE_VEHICLE(hash2, null.x, null.y, null.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
					int Ebox = OBJECT::CREATE_OBJECT(hash1, null.x, null.y, null.z, 1, 0, 1);

					if (ENTITY::DOES_ENTITY_EXIST(Ebox) && ENTITY::DOES_ENTITY_EXIST(Object))
					{
						int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);

						if (ENTITY::DOES_ENTITY_EXIST(Vehicle))
						{
							PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
							STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
							ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, false);
							ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true, false);
							VEHICLE::SET_VEHICLE_MOD_KIT(Vehicle, 5);
							VEHICLE::SET_VEHICLE_WINDOW_TINT(Vehicle, 5);
							VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle, 0, 0, 0);
							VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle, 0, 0, 0);
							VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object, 0, 0, 0);
							VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object, 0, 0, 0);

							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Ebox, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
						}

					}

				}

			}
			if (GUI::Option("Train")) {
				uint Me = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Vector3 null; null.x = 0, null.y = 0; null.z = 0;
				Vector3 a; a.x = 0, a.y = 0, a.z = 0;
				Vector3 b; b.x = 0, b.y = 0, b.z = 0;
				int hash = GAMEPLAY::GET_HASH_KEY("massacro2");
				int hash2 = GAMEPLAY::GET_HASH_KEY("freight");
				STREAMING::REQUEST_MODEL(hash);
				STREAMING::REQUEST_MODEL(hash2);
				if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
				{
					int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					int Object = VEHICLE::CREATE_VEHICLE(hash2, null.x, null.y, null.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object))
					{
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
						PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
						ENTITY::SET_ENTITY_VISIBLE(Object, true, false);
						VEHICLE::SET_VEHICLE_MOD_KIT(Object, 0);
						VEHICLE::SET_VEHICLE_WINDOW_TINT(Object, 5);
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object, 0, 0, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object, 0, 0, 0);
						VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(Object, "sm");
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle, 0, 0, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle, 0, 0, 0);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);

					}

				}

			}
			if (GUI::Option("Classic Car Mix")) {
				uint Me = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Vector3 null; null.x = 0, null.y = 0; null.z = 0;
				Vector3 a; a.x = 0, a.y = 0, a.z = 0;
				Vector3 b; b.x = 0, b.y = 0, b.z = 0;
				int hash = GAMEPLAY::GET_HASH_KEY("ztype");
				int hash2 = GAMEPLAY::GET_HASH_KEY("btype");
				STREAMING::REQUEST_MODEL(hash);
				STREAMING::REQUEST_MODEL(hash2);
				if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
				{
					int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					int Object = VEHICLE::CREATE_VEHICLE(hash2, null.x, null.y, null.z, ENTITY::GET_ENTITY_HEADING(Me), 1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object))
					{
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
						PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
						ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, false);
						VEHICLE::SET_VEHICLE_MOD_KIT(Object, 0);
						VEHICLE::SET_VEHICLE_WINDOW_TINT(Object, 5);
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object, 0, 0, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object, 0, 0, 0);
						VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(Vehicle, "Project");
						VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(Object, "Project");
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle, 0, 0, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle, 0, 0, 0);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);

					}

				}

			}
			if (GUI::Option("Cup Car")) {
				int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				Vector3 Ocoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Handle, 0.0, 5.0, 0.0);
				Vehicle zentorno = Features::SpawnVehicle("SURANO", Ocoords, 0, 0.0f);
				ENTITY::SET_ENTITY_VISIBLE(zentorno, false, false);
				ENTITY::SET_ENTITY_ALPHA(zentorno, 0, 1);
				VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(zentorno, 1);
				Object model = SpawnObject("PROP_CUP_SAUCER_01", Ocoords);
				if (freezespawned) {
					ENTITY::FREEZE_ENTITY_POSITION(model, true);
				}
				DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
				AttachThingToThing(model, zentorno, -0.4f, -0.5f, -0.4f, 0.0f, 0.0f, 180.0f);
			}
			if (GUI::Option("Fly UFO")) {
				int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				Vector3 Ocoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Handle, 0.0, 5.0, 0.0);
				Vehicle zentorno = Features::SpawnVehicle("HYDRA", Ocoords, 0, 0.0f);
				ENTITY::SET_ENTITY_VISIBLE(zentorno, false, false);
				ENTITY::SET_ENTITY_ALPHA(zentorno, 0, 1);
				VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(zentorno, 1);
				Object model = SpawnObject("p_spinning_anus_s", Ocoords);
				if (freezespawned) {
					ENTITY::FREEZE_ENTITY_POSITION(model, true);
				}
				DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
				AttachThingToThing(model, zentorno, -0.4f, -0.5f, -0.4f, 0.0f, 0.0f, 180.0f);
			}
			if (GUI::Option("Poop Car")) {
				int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				Vector3 Ocoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Handle, 0.0, 5.0, 0.0);
				Vehicle zentorno = Features::SpawnVehicle("SURANO", Ocoords, 0, 0.0f);
				ENTITY::SET_ENTITY_VISIBLE(zentorno, false, false);
				ENTITY::SET_ENTITY_ALPHA(zentorno, 0, 1);
				VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(zentorno, 1);
				Object model = SpawnObject("prop_ld_toilet_01", Ocoords);
				if (freezespawned) {
					ENTITY::FREEZE_ENTITY_POSITION(model, true);
				}
				DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
				AttachThingToThing(model, zentorno, -0.5f, -0.8f, -0.4f, 0.0f, 0.0f, 180.0f);
			}
			if (GUI::Option("Coyote on Crack")) {
				int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				Vector3 Ocoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Handle, 0.0, 5.0, 0.0);
				Vehicle zentorno = Features::SpawnVehicle("SPEEDO2", Ocoords, 0, 0.0f);
				ENTITY::SET_ENTITY_VISIBLE(zentorno, false, false);
				ENTITY::SET_ENTITY_ALPHA(zentorno, 0, 1);
				VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(zentorno, 1);
				Object model = SpawnObject("a_c_coyote", Ocoords);
				if (freezespawned) {
					ENTITY::FREEZE_ENTITY_POSITION(model, true);
				}
				DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
				AttachThingToThing(model, zentorno, -0.5f, -0.8f, -0.4f, 0.0f, 0.0f, 180.0f);
			}
			if (GUI::Option("Shark on Crack")) {
				int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				Vector3 Ocoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Handle, 0.0, 5.0, 0.0);
				Vehicle zentorno = Features::SpawnVehicle("SPEEDO2", Ocoords, 0, 0.0f);
				ENTITY::SET_ENTITY_VISIBLE(zentorno, false, false);
				ENTITY::SET_ENTITY_ALPHA(zentorno, 0, 1);
				VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(zentorno, 1);
				Object model = SpawnObject("a_c_sharktiger", Ocoords);
				if (freezespawned) {
					ENTITY::FREEZE_ENTITY_POSITION(model, true);
				}
				DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
				AttachThingToThing(model, zentorno, -0.5f, -0.8f, -0.4f, 0.0f, 0.0f, 180.0f);
			}
			if (GUI::Option("Bumper Cart")) {
				int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				Vector3 Ocoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Handle, 0.0, 5.0, 0.0);
				Vehicle zentorno = Features::SpawnVehicle("SURANO", Ocoords, 0, 0.0f);
				ENTITY::SET_ENTITY_VISIBLE(zentorno, false, false);
				ENTITY::SET_ENTITY_ALPHA(zentorno, 0, 1);
				VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(zentorno, 1);
				Object model = SpawnObject("PROP_BUMPER_CAR_01", Ocoords);
				if (freezespawned) {
					ENTITY::FREEZE_ENTITY_POSITION(model, true);
				}
				DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
				AttachThingToThing(model, zentorno, -0.5f, -0.8f, -0.4f, 0.0f, 0.0f, 180.0f);
			}
			if (GUI::Option("Sofa Car")) {
				int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				Vector3 Ocoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Handle, 0.0, 5.0, 0.0);
				Vehicle zentorno = Features::SpawnVehicle("SURANO", Ocoords, 0, 0.0f);
				ENTITY::SET_ENTITY_VISIBLE(zentorno, false, false);
				ENTITY::SET_ENTITY_ALPHA(zentorno, 0, 1);
				VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(zentorno, 1);
				Object model = SpawnObject("PROP_YACHT_SEAT_01", Ocoords);
				if (freezespawned) {
					ENTITY::FREEZE_ENTITY_POSITION(model, true);
				}
				DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
				AttachThingToThing(model, zentorno, -0.5f, -0.8f, -0.4f, 0.0f, 0.0f, 180.0f);
			}
			if (GUI::Option("Roller Car")) {
				int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				Vector3 Ocoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Handle, 0.0, 5.0, 0.0);
				Vehicle zentorno = Features::SpawnVehicle("SURANO", Ocoords, 0, 0.0f);
				ENTITY::SET_ENTITY_VISIBLE(zentorno, false, false);
				ENTITY::SET_ENTITY_ALPHA(zentorno, 0, 1);
				VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(zentorno, 1);
				Object model = SpawnObject("prop_roller_car_02", Ocoords);
				if (freezespawned) {
					ENTITY::FREEZE_ENTITY_POSITION(model, true);
				}
				DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
				AttachThingToThing(model, zentorno, -0.5f, -0.8f, -0.4f, 0.0f, 0.0f, 180.0f);
			}
			if (GUI::Option("Deer on Crack")) {
				int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				Vector3 Ocoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Handle, 0.0, 5.0, 0.0);
				Vehicle zentorno = Features::SpawnVehicle("SPEEDO2", Ocoords, 0, 0.0f);
				ENTITY::SET_ENTITY_VISIBLE(zentorno, false, false);
				ENTITY::SET_ENTITY_ALPHA(zentorno, 0, 1);
				VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(zentorno, 1);
				Object model = SpawnObject("a_c_deer", Ocoords);
				if (freezespawned) {
					ENTITY::FREEZE_ENTITY_POSITION(model, true);
				}
				DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
				AttachThingToThing(model, zentorno, -0.5f, -0.8f, -0.4f, 0.0f, 0.0f, 180.0f);
			}
			if (GUI::Option("Cow on Crack")) {
				int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				Vector3 Ocoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Handle, 0.0, 5.0, 0.0);
				Vehicle zentorno = Features::SpawnVehicle("SPEEDO2", Ocoords, 0, 0.0f);
				ENTITY::SET_ENTITY_VISIBLE(zentorno, false, false);
				ENTITY::SET_ENTITY_ALPHA(zentorno, 0, 1);
				VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(zentorno, 1);
				Object model = SpawnObject("a_c_cow", Ocoords);
				if (freezespawned) {
					ENTITY::FREEZE_ENTITY_POSITION(model, true);
				}
				DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
				AttachThingToThing(model, zentorno, -0.5f, -0.8f, -0.4f, 0.0f, 0.0f, 180.0f);
			}
		}
		break;*/

#pragma endregion

#pragma region Vehicle Colors

		case vehicle_colors:
		{
			GUI::Title("");
			GUI::Subtitle("Vehicle Colors");
			GUI::MenuOption("Primary Color", primary_paints);
			GUI::MenuOption("Secondary Color", secondary_paints);
			GUI::MenuOption("Pearl Topcoat", pearl_topcoat);
			GUI::MenuOption("Wheel Color", wheel_paints);
		}
		break;

#pragma endregion

#pragma region LS Customs
		case lsc:
		{
			GUI::Title("");
			GUI::Subtitle("Los Santos Customs");
			if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), true)) {
				GUI::Option("You need to be in any vehicle.");
			}
			else {
				GUI::MenuOption("Spoiler", spoiler);
				GUI::MenuOption("Front Bumper", front_bumper);
				GUI::MenuOption("Rear Bumper", rear_bumper);
				GUI::MenuOption("Side Skirt", side_skirt);
				GUI::MenuOption("Exhaust", exhaust);
				GUI::MenuOption("Grille", grille);
				GUI::MenuOption("Chassis", chassis);
				GUI::MenuOption("Hood", hood);
				GUI::MenuOption("Fender", fender);
				GUI::MenuOption("Right Fender", right_fender);
				GUI::MenuOption("Roof", roof);
				GUI::MenuOption("Engine", engine);
				GUI::MenuOption("Brakes", brakes);
				GUI::MenuOption("Transmission", transmission);
				GUI::MenuOption("Horns", horns);
				GUI::MenuOption("Suspension", suspension);
				GUI::MenuOption("Armor", armor);
				GUI::MenuOption("Wheels", wheels);
				GUI::MenuOption("Windows", windows);
			}
		}
		break;

		case primary_paints:
		{
			GUI::Title("");
			GUI::Subtitle("Primary Color");
			GUI::MenuOption("Normal", normal);
			GUI::MenuOption("Metallic", metallic);
			GUI::MenuOption("Matte", matte);
			GUI::MenuOption("Metal", metal);
			if (GUI::Option("Chrome")) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
				VEHICLE::SET_VEHICLE_COLOURS(veh, 120, secondary);
			}
		}
		break;

		case normal:
		{
			GUI::Title("");
			GUI::Subtitle("Normal");
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			for (auto paint : Hashes::PAINTS_NORMAL) {
				if (GUI::Option(paint.name)) {
					VEHICLE::GET_VEHICLE_COLOURS(veh, &primary, &secondary);
					VEHICLE::SET_VEHICLE_MOD_COLOR_1(veh, 0, 0, 0);
					VEHICLE::SET_VEHICLE_COLOURS(veh, paint.mainValue, secondary);
				}
			}
		}
		break;

		case metallic:
		{
			GUI::Title("");
			GUI::Subtitle("Metallic");
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			for (auto paint : Hashes::PAINTS_METALLIC) {
				if (GUI::Option(paint.name)) {
					VEHICLE::GET_VEHICLE_COLOURS(veh, &primary, &secondary);
					VEHICLE::SET_VEHICLE_MOD_COLOR_1(veh, 0, 0, 0);
					VEHICLE::SET_VEHICLE_COLOURS(veh, paint.mainValue, secondary);
				}
			}
		}
		break;

		case matte:
		{
			GUI::Title("");
			GUI::Subtitle("Matte");
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			for (auto paint : Hashes::PAINTS_MATTE) {
				if (GUI::Option(paint.name)) {
					VEHICLE::GET_VEHICLE_COLOURS(veh, &primary, &secondary);
					VEHICLE::SET_VEHICLE_MOD_COLOR_1(veh, 0, 0, 0);
					VEHICLE::SET_VEHICLE_COLOURS(veh, paint.mainValue, secondary);
				}
			}
		}
		break;

		case metal:
		{
			GUI::Title("");
			GUI::Subtitle("Metal");
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			for (auto paint : Hashes::PAINTS_METAL) {
				if (GUI::Option(paint.name)) {
					VEHICLE::GET_VEHICLE_COLOURS(veh, &primary, &secondary);
					VEHICLE::SET_VEHICLE_MOD_COLOR_1(veh, 0, 0, 0);
					VEHICLE::SET_VEHICLE_COLOURS(veh, paint.mainValue, secondary);
				}
			}
		}
		break;

		case pearl_topcoat:
		{
			GUI::Title("");
			GUI::Subtitle("Pearl Topcoat");
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			for (auto paint : Hashes::PAINTS_PEARL) {
				if (GUI::Option(paint.name)) {
					VEHICLE::GET_VEHICLE_MOD_COLOR_1(veh, &ppaint1, &ppaint2, &ppaint3);
					VEHICLE::SET_VEHICLE_MOD_COLOR_1(veh, 0, primary + 1, primary + 1);
					VEHICLE::SET_VEHICLE_COLOURS(veh, primary, secondary);
					if (paint.pearlAddition != -1) {
						VEHICLE::GET_VEHICLE_EXTRA_COLOURS(veh, &paint1, &paint2);
						VEHICLE::SET_VEHICLE_EXTRA_COLOURS(veh, paint.pearlAddition, paint2);
					}
				}
			}
		}
		break;
		
		case wheel_paints:
		{
			GUI::Title("");
			GUI::Subtitle("Wheel Colors");
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			for (auto paint : Hashes::PAINTS_WHEELS) {
				if (GUI::Option(paint.name)) {
					VEHICLE::GET_VEHICLE_EXTRA_COLOURS(veh, &paint1, &paint2);
					VEHICLE::SET_VEHICLE_EXTRA_COLOURS(veh, paint1, paint.mainValue);
				}
			}
		}
		break;

		case secondary_paints:
		{
			GUI::Title("");
			GUI::Subtitle("Secondary Color");
			GUI::MenuOption("Normal", normal2);
			GUI::MenuOption("Metallic", metallic2);
			GUI::MenuOption("Matte", matte2);
			GUI::MenuOption("Metal", metal2);
			if (GUI::Option("Chrome")) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
				VEHICLE::SET_VEHICLE_COLOURS(veh, primary, 120);
			}
		}
		break;

		case normal2:
		{
			GUI::Title("");
			GUI::Subtitle("Normal");
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			for (auto paint : Hashes::PAINTS_NORMAL) {
				if (GUI::Option(paint.name)) {
					VEHICLE::GET_VEHICLE_COLOURS(veh, &primary, &secondary);
					VEHICLE::SET_VEHICLE_MOD_COLOR_2(veh, 0, 0);
					VEHICLE::SET_VEHICLE_COLOURS(veh, primary, paint.mainValue);
				}
			}
		}
		break;

		case metallic2:
		{
			GUI::Title("");
			GUI::Subtitle("Metallic");
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			for (auto paint : Hashes::PAINTS_METALLIC) {
				if (GUI::Option(paint.name)) {
					VEHICLE::GET_VEHICLE_COLOURS(veh, &primary, &secondary);
					VEHICLE::SET_VEHICLE_MOD_COLOR_2(veh, 0, 0);
					VEHICLE::SET_VEHICLE_COLOURS(veh, primary, paint.mainValue);
				}
			}
		}
		break;

		case matte2:
		{
			GUI::Title("");
			GUI::Subtitle("Matte");
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			for (auto paint : Hashes::PAINTS_MATTE) {
				if (GUI::Option(paint.name)) {
					VEHICLE::GET_VEHICLE_COLOURS(veh, &primary, &secondary);
					VEHICLE::SET_VEHICLE_MOD_COLOR_2(veh, 0, 0);
					VEHICLE::SET_VEHICLE_COLOURS(veh, primary, paint.mainValue);
				}
			}
		}
		break;

		case metal2:
		{
			GUI::Title("");
			GUI::Subtitle("Metal");
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			for (auto paint : Hashes::PAINTS_METAL) {
				if (GUI::Option(paint.name)) {
					VEHICLE::GET_VEHICLE_COLOURS(veh, &primary, &secondary);
					VEHICLE::SET_VEHICLE_MOD_COLOR_2(veh, 0, 0);
					VEHICLE::SET_VEHICLE_COLOURS(veh, primary, paint.mainValue);
				}
			}
		}
		break;

		// --------- LSC Mods --------- //

		case spoiler:
		{
			GUI::Title("");
			GUI::Subtitle("Spoiler");
			char modName[30];
			char* modLabel;
			int modType = MOD_SPOILER;
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			for (int i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(veh, modType); ++i) {
				modLabel = UI::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(veh, modType, i));
				snprintf(modName, sizeof(modName), "%s", modLabel);
				if (GUI::Option(i == -1 ? "None" : modName)) {
					VEHICLE::SET_VEHICLE_MOD(veh, modType, i, false);
				}
			}
		}
		break;

		case front_bumper:
		{
			GUI::Title("");
			GUI::Subtitle("Front Bumper");
			char modName[30];
			char* modLabel;
			int modType = MOD_FRONTBUMPER;
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			for (int i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(veh, modType); ++i) {
				modLabel = UI::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(veh, modType, i));
				snprintf(modName, sizeof(modName), "%s", modLabel);
				if (GUI::Option(i == -1 ? "None" : modName)) {
					VEHICLE::SET_VEHICLE_MOD(veh, modType, i, false);
				}
			}
		}
		break;

		case rear_bumper:
		{
			GUI::Title("");
			GUI::Subtitle("Rear Bumper");
			char modName[30];
			char* modLabel;
			int modType = MOD_REARBUMPER;
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			for (int i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(veh, modType); ++i) {
				modLabel = UI::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(veh, modType, i));
				snprintf(modName, sizeof(modName), "%s", modLabel);
				if (GUI::Option(i == -1 ? "None" : modName)) {
					VEHICLE::SET_VEHICLE_MOD(veh, modType, i, false);
				}
			}
		}
		break;

		case side_skirt:
		{
			GUI::Title("");
			GUI::Subtitle("Side Skirt");
			char modName[30];
			char* modLabel;
			int modType = MOD_SIDESKIRT;
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			for (int i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(veh, modType); ++i) {
				modLabel = UI::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(veh, modType, i));
				snprintf(modName, sizeof(modName), "%s", modLabel);
				if (GUI::Option(i == -1 ? "None" : modName)) {
					VEHICLE::SET_VEHICLE_MOD(veh, modType, i, false);
				}
			}
		}
		break;

		case exhaust:
		{
			GUI::Title("");
			GUI::Subtitle("Exhaust");
			char modName[30];
			char* modLabel;
			int modType = MOD_EXHAUST;
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			for (int i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(veh, modType); ++i) {
				modLabel = UI::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(veh, modType, i));
				snprintf(modName, sizeof(modName), "%s", modLabel);
				if (GUI::Option(i == -1 ? "None" : modName)) {
					VEHICLE::SET_VEHICLE_MOD(veh, modType, i, false);
				}
			}
		}
		break;

		case grille:
		{
			GUI::Title("");
			GUI::Subtitle("Grille");
			char modName[30];
			char* modLabel;
			int modType = MOD_GRILLE;
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			for (int i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(veh, modType); ++i) {
				modLabel = UI::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(veh, modType, i));
				snprintf(modName, sizeof(modName), "%s", modLabel);
				if (GUI::Option(i == -1 ? "None" : modName)) {
					VEHICLE::SET_VEHICLE_MOD(veh, modType, i, false);
				}
			}
		}
		break;

		case chassis:
		{
			GUI::Title("");
			GUI::Subtitle("Chassis");
			char modName[30];
			char* modLabel;
			int modType = MOD_CHASSIS;
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			for (int i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(veh, modType); ++i) {
				modLabel = UI::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(veh, modType, i));
				snprintf(modName, sizeof(modName), "%s", modLabel);
				if (GUI::Option(i == -1 ? "None" : modName)) {
					VEHICLE::SET_VEHICLE_MOD(veh, modType, i, false);
				}
			}
		}
		break;

		case hood:
		{
			GUI::Title("");
			GUI::Subtitle("Hood");
			char modName[30];
			char* modLabel;
			int modType = MOD_HOOD;
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			for (int i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(veh, modType); ++i) {
				modLabel = UI::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(veh, modType, i));
				snprintf(modName, sizeof(modName), "%s", modLabel);
				if (GUI::Option(i == -1 ? "None" : modName)) {
					VEHICLE::SET_VEHICLE_MOD(veh, modType, i, false);
				}
			}
		}
		break;

		case fender:
		{
			GUI::Title("");
			GUI::Subtitle("Fender");
			char modName[30];
			char* modLabel;
			int modType = MOD_FENDER;
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			for (int i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(veh, modType); ++i) {
				modLabel = UI::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(veh, modType, i));
				snprintf(modName, sizeof(modName), "%s", modLabel);
				if (GUI::Option(i == -1 ? "None" : modName)) {
					VEHICLE::SET_VEHICLE_MOD(veh, modType, i, false);
				}
			}
		}
		break;

		case right_fender:
		{
			GUI::Title("");
			GUI::Subtitle("Right Fender");
			char modName[30];
			char* modLabel;
			int modType = MOD_RIGHTFENDER;
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			for (int i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(veh, modType); ++i) {
				modLabel = UI::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(veh, modType, i));
				snprintf(modName, sizeof(modName), "%s", modLabel);
				if (GUI::Option(i == -1 ? "None" : modName)) {
					VEHICLE::SET_VEHICLE_MOD(veh, modType, i, false);
				}
			}
		}
		break;

		case roof:
		{
			GUI::Title("");
			GUI::Subtitle("Roof");
			char modName[30];
			char* modLabel;
			int modType = MOD_ROOF;
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			for (int i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(veh, modType); ++i) {
				modLabel = UI::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(veh, modType, i));
				snprintf(modName, sizeof(modName), "%s", modLabel);
				if (GUI::Option(i == -1 ? "None" : modName)) {
					VEHICLE::SET_VEHICLE_MOD(veh, modType, i, false);
				}
			}
		}
		break;

		case engine:
		{
			GUI::Title("");
			GUI::Subtitle("Engine");
			int modType = MOD_ENGINE;
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			if (GUI::Option("Stock")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, -1, false);
			}
			if (GUI::Option("EMS Upgrade, Level 1")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 0, false);
			}
			if (GUI::Option("EMS Upgrade, Level 2")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 1, false);
			}
			if (GUI::Option("EMS Upgrade, Level 3")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 2, false);
			}
			if (GUI::Option("EMS Upgrade, Level 4")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 3, false);
			}
		}
		break;

		case brakes:
		{
			GUI::Title("");
			GUI::Subtitle("Brakes");
			int modType = MOD_BRAKES;
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			if (GUI::Option("Stock")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, -1, false);
			}
			if (GUI::Option("Street Brakes")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 0, false);
			}
			if (GUI::Option("Sport Brakes")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 1, false);
			}
			if (GUI::Option("Race Brakes")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 2, false);
			}
		}
		break;

		case transmission:
		{
			GUI::Title("");
			GUI::Subtitle("Transmission");
			int modType = MOD_TRANSMISSION;
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			if (GUI::Option("Stock")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, -1, false);
			}
			if (GUI::Option("Street Transmission")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 0, false);
			}
			if (GUI::Option("Sport Transmission")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 1, false);
			}
			if (GUI::Option("Race Transmission")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 2, false);
			}
		}
		break;

		case horns:
		{
			GUI::Title("");
			GUI::Subtitle("Horns");
			GUI::MenuOption("Standard", standard_horns);
			GUI::MenuOption("Musical", musical_horns);
			GUI::MenuOption("Looped", looped_horns);
		}
		break;

		case standard_horns:
		{
			GUI::Title("");
			GUI::Subtitle("Standard Horns");
			int modType = MOD_HORNS;
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
			if (GUI::Option("Stock")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, -1, false);
			}
			if (GUI::Option("Truck Horn")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 0, false);
			}
			if (GUI::Option("Cop Horn")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 1, false);
			}
			if (GUI::Option("Clown Horn")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 2, false);
			}
		}
		break;

		case musical_horns:
		{
			GUI::Title("");
			GUI::Subtitle("Musical Horns");
			int modType = MOD_HORNS;
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
			if (GUI::Option("Musical Horn 1")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 3, false);
			}
			if (GUI::Option("Musical Horn 2")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 4, false);
			}
			if (GUI::Option("Musical Horn 3")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 5, false);
			}
			if (GUI::Option("Musical Horn 4")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 6, false);
			}
			if (GUI::Option("Musical Horn 5")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 7, false);
			}
			if (GUI::Option("Sad Trombone")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 8, false);
			}
			if (GUI::Option("Classical Horn 1")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 9, false);
			}
			if (GUI::Option("Classical Horn 2")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 10, false);
			}
			if (GUI::Option("Classical Horn 3")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 11, false);
			}
			if (GUI::Option("Classical Horn 4")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 12, false);
			}
			if (GUI::Option("Classical Horn 5")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 13, false);
			}
			if (GUI::Option("Classical Horn 6")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 14, false);
			}
			if (GUI::Option("Classical Horn 7")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 15, false);
			}
			if (GUI::Option("Classical Horn 8")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 33, false);
			}
			if (GUI::Option("Scale - Do")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 16, false);
			}
			if (GUI::Option("Scale - Re")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 17, false);
			}
			if (GUI::Option("Scale - Mi")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 18, false);
			}
			if (GUI::Option("Scale - Fa")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 19, false);
			}
			if (GUI::Option("Scale - So")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 20, false);
			}
			if (GUI::Option("Scale - La")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 21, false);
			}
			if (GUI::Option("Scale - Ti")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 22, false);
			}
			if (GUI::Option("Scale - Do (High)")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 23, false);
			}
			if (GUI::Option("Jazz Horn 1")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 24, false);
			}
			if (GUI::Option("Jazz Horn 2")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 25, false);
			}
			if (GUI::Option("Jazz Horn 3")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 26, false);
			}
			if (GUI::Option("Star Spangled Banner 1")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 28, false);
			}
			if (GUI::Option("Star Spangled Banner 2")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 29, false);
			}
			if (GUI::Option("Star Spangled Banner 3")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 30, false);
			}
			if (GUI::Option("Star Spangled Banner 4")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 31, false);
			}
		}
		break;

		case looped_horns:
		{
			GUI::Title("");
			GUI::Subtitle("Looped Horns");
			int modType = MOD_HORNS;
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			if (GUI::Option("Jazz Horn")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 27, false);
			}
			if (GUI::Option("Classical Horn Loop 1")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 32, false);
			}
			if (GUI::Option("Classical Horn Loop 2")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 34, false);
			}
		}
		break;

		case suspension:
		{
			GUI::Title("");
			GUI::Subtitle("Suspensions");
			int modType = MOD_SUSPENSION;
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			if (GUI::Option("Stock")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, -1, false);
			}
			if (GUI::Option("Street Suspension")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 0, false);
			}
			if (GUI::Option("Sport Suspension")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 1, false);
			}
			if (GUI::Option("Race Suspension")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 2, false);
			}
		}
		break;

		case armor:
		{
			GUI::Title("");
			GUI::Subtitle("Vehicle Armor");
			int modType = MOD_ARMOR;
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			if (GUI::Option("Stock")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, -1, false);
			}
			if (GUI::Option("Armor Upgrade 20%")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 0, false);
			}
			if (GUI::Option("Armor Upgrade 40%")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 1, false);
			}
			if (GUI::Option("Armor Upgrade 60%")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 2, false);
			}
			if (GUI::Option("Armor Upgrade 80%")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 3, false);
			}
			if (GUI::Option("Armor Upgrade 100%")) {
				VEHICLE::SET_VEHICLE_MOD(veh, modType, 4, false);
			}
		}
		break;

		case wheels:
		{
			GUI::Title("");
			GUI::Subtitle("Wheels");
			char modName[30];
			char* modLabel;
			int modType = MOD_FRONTWHEELS;
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			for (int i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(veh, modType); ++i) {
				modLabel = UI::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(veh, modType, i));
				snprintf(modName, sizeof(modName), "%s", modLabel);
				if (GUI::Option(i == -1 ? "Default" : modName)) {
					VEHICLE::SET_VEHICLE_MOD(veh, modType, i, false);
				}
			}
		}
		break;

		case windows:
		{
			GUI::Title("");
			GUI::Subtitle("Windows");
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			if (GUI::Option("Stock")) {
				VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, 0);
			}
			if (GUI::Option("Limo")) {
				VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, 1);
			}
			if (GUI::Option("Dark Smoke")) {
				VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, 2);
			}
			if (GUI::Option("Light Smoke")) {
				VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, 3);
			}
			if (GUI::Option("None")) {
				VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, 4);
			}
			if (GUI::Option("Green")) {
				VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, 5);
			}
		}
		break;

#pragma endregion

#pragma region Paints
		case paint:
		{
			GUI::Title("Paint Menu");
			GUI::Subtitle("Paint Menu");
			if (GUI::Option("Random")) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, rand() % 255, rand() % 255, rand() % 255);
				if (VEHICLE::GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(veh))
					VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, rand() % 255, rand() % 255, rand() % 255);
			}
			if (GUI::Option("Chrome")) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 120, 120);
			}
			if (GUI::Option("Black")) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 0, 0, 0);
			}
			if (GUI::Option("White")) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 255, 255, 255);
			}
			if (GUI::Option("Red")) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 255, 0, 0);
			}
			if (GUI::Option("Green")) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 0, 255, 0);
			}
			if (GUI::Option("Blue")) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 0, 0, 255);
			}
			if (GUI::Option("Orange")) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 255, 128, 0);
			}
			if (GUI::Option("Yellow")) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 255, 255, 0);
			}
			if (GUI::Option("Purple")) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 204, 0, 204);
			}
			if (GUI::Option("Grey")) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 96, 96, 96);
			}
			if (GUI::Option("Brown")) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 165, 42, 42);
			}
			if (GUI::Option("Pink")) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 255, 51, 255);
			}
			if (GUI::Option("Cool Green")) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 0, 255, 196);
			}
			if (GUI::Option("Hot Pink")) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 255, 0, 145);
			}
			if (GUI::Option("Lime")) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 128, 255, 0);
			}
			if (GUI::Option("Lava Red")) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 255, 60, 0);
			}
			if (GUI::Option("Mint Green")) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 0, 255, 119);
			}
			if (GUI::Option("Neon Green")) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 187, 255, 0);
			}
		}
		break;
#pragma endregion

#pragma region Vehicle Weapons
		case VehWeapon:
		{
			GUI::Title("Vehicle Weapons");
			GUI::Subtitle("Vehicle Weapons");
			GUI::Toggle("Shoot Rockets", Features::ShootR, [] { Features::ShootRocket(Features::ShootR); });
			GUI::Toggle("Shoot FireWorks", Features::ShootT, [] { Features::ShootTanks(Features::ShootT); });
			GUI::Toggle("Shoot Tank Rounds", Features::ShootTankR, [] { Features::ShootTankRounds(Features::ShootTankR); });
			GUI::Toggle("Shoot Balls", Features::ShootBall, [] { Features::ShootBalls(Features::ShootBall); });
			GUI::Toggle("Shoot Mini Gun", Features::ShootMini, [] { Features::ShootMiniGun(Features::ShootMini); });
			GUI::Break("Press + key to use");
		}
		break;

#pragma endregion

#pragma region Plates
		case plateoptions:
		{
			GUI::Title("");
			GUI::Subtitle("Plate Options");
			GUI::MenuOption("Plate Style", platecolor);
			if (GUI::Option("Custom Plate Text")) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				RequestControlOfEnt(veh);
				VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, Features::CharKeyboard());

			}
			if (GUI::Option("Project Plate")) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				RequestControlOfEnt(veh);
				VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, "Project");
			}
		}
		break;
#pragma endregion

#pragma region Plate Colors
		case platecolor:
		{
			GUI::Title("");
			GUI::Subtitle("Plate Style");
			if (GUI::Option("Blue On White Plate")) {
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), true))
				{
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 0);

				}
			}
			if (GUI::Option("Yellow On Black Plate")) {
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), true))
				{
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 1);

				}
			}
			if (GUI::Option("Yellow On Blue Plate")) {
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), true))
				{
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 2);

				}
			}
			if (GUI::Option("Blue On White 2 Plate")) {
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), true))
				{
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 3);

				}
			}
			if (GUI::Option("Blue On White 3 Plate")) {
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), true))
				{
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 4);

				}
			}
			if (GUI::Option("Yankton Plate")) {
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), true))
				{
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 5);

				}
			}

		}
		break;

#pragma endregion

#pragma region Vehicle Options

		case vehicle_aesthetics:
		{
			GUI::Title("");
			GUI::Subtitle("Vehicle Aesthetics");
			GUI::MenuOption("Los Santos Customs", lsc);
			GUI::MenuOption("Vehicle Colors", vehicle_colors);
			GUI::MenuOption("Plate Style", plateoptions);
			GUI::Toggle("Rainbow Car", Features::rlbool, [] { Features::HasPaintLoop(Features::rlbool); });
			GUI::Toggle("Smooth Rainbow Car", Features::rainbowcar, [] { Features::RainbowCar(Features::rainbowcar); });
			GUI::Toggle("Rainbow Tire Smoke", Features::rainbowsmokecar, [] { Features::RainbowSmokeCar(Features::rainbowsmokecar); });
			GUI::Toggle("Rainbow Neons", Features::Rneon, [] { Features::RainbowNeon(Features::Rneon); });
			//GUI::Toggle("Rainbow Wheels", Features::rainbowwheelscar, [] { Features::RainbowWheelsCar(Features::rainbowwheelscar); });
			//GUI::Toggle("Rainbow Interior", Features::rainbowinteriorcar, [] { Features::RainbowInteriorCar(Features::rainbowinteriorcar); });
			if (GUI::Option("Roll Down Windows"))
			{
				VEHICLE::ROLL_DOWN_WINDOWS(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()));
			}
			if (GUI::Option("Roll Up Windows"))
			{
				for (int i = 0; i < 7; i++)
				{
					VEHICLE::ROLL_UP_WINDOW(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), i);
				}
			}
			if (GUI::Option("Open Doors")) {
				VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0, true, false);
				VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 1, true, false);
				VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 2, true, false);
				VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 3, true, false);
				VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 4, true, false);
				VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 5, true, false);
				VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 6, true, false);
				VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 7, true, false);
			}
			if (GUI::Option("Close Doors")) {
				VEHICLE::SET_VEHICLE_DOORS_SHUT(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), true);
			}
			if (GUI::Option("Max Upgrade")) {
				Features::maxvehicle();
			}
		}
		break;

		case vehicle_health:
		{
			GUI::Title("");
			GUI::Subtitle("Vehicle Health");
			GUI::Toggle("Car Godmode", Features::cargodmodebool, [] { Features::cargodmode(Features::cargodmodebool); });
			GUI::Toggle("Repair Loop", Features::isRepairLoop, [] { Features::repairLoop(); });
			if (GUI::Option("Fix Car & Wash")) {
				uint Vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()));
				VEHICLE::SET_VEHICLE_FIXED(Vehicle);
				VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(Vehicle);
				VEHICLE::SET_VEHICLE_DIRT_LEVEL(Vehicle, 0);
			}
		}
		break;

		case vehicle_movements:
		{
			GUI::Title("");
			GUI::Subtitle("Vehicle Movements");
			//GUI::Toggle("Speedo (MPH)", Features::speedmetorbool, [] { Features::speedmetor(Features::speedmetorbool); });
			GUI::Toggle("Horn Boost", Features::isHornBoost, [] { Features::hornBoost(); });
			GUI::Toggle("Drift Mode", Features::Drift, [] { Features::DriftMode(Features::Drift); });
			GUI::Toggle("Engine Always On", Features::enginealwaysonbool, [] { Features::enginealwayson(Features::enginealwaysonbool); });
			GUI::Toggle("Instant Brake", Features::isInstantBrake, [] { Features::instantBrake(); });
			GUI::Toggle("Wall Drive", Features::isWallDrive, [] { Features::wallDrive(); });
			GUI::Toggle("Lower Car", Features::carlowerbool, [] { Features::carlower(Features::carlowerbool); });
			GUI::Toggle("Drive on Water", Features::dowbool, [] { Features::DriveOnWater(Features::dowbool); });
			GUI::Toggle("Infnite Rocket Boost", Features::isInfBoost, [] { Features::InfiniteBoost(Features::isInfBoost); });

			//GUI::Toggle("Car Jump", Features::carjump, [] { Features::carjumpon(); });
			if (GUI::Option("Flip Car")) 
			{
				Features::flipup();
			}
			if (GUI::Option("Vehicle Jump")) 
			{
				if ((VK_SPACE) && PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
					ENTITY::APPLY_FORCE_TO_ENTITY(veh, 1, 0 + ENTITY::GET_ENTITY_FORWARD_X(veh), 0 + ENTITY::GET_ENTITY_FORWARD_Y(veh), 7, 0, 0, 0, 1, 0, 1, 1, 1, 1);
				}
			}
		}
		break;

		case vehmult:
		{
			GUI::Title("");
			GUI::Subtitle("Vehicle Multipliers");
			if (GUI::Float("Torque Multiplier", Features::Torqueint, 1, 1000)) {
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Features::Torqueint = Features::NumberKeyboard();
				}
				if (IsKeyPressed(VK_RETURN) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Features::Torqueint = Features::NumberKeyboard();
				}
			}
			if (GUI::Float("Power Multiplier", Features::Powerint, 1, 1000)) {
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Features::Powerint = Features::NumberKeyboard();
				}
				if (IsKeyPressed(VK_RETURN) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Features::Powerint = Features::NumberKeyboard();
				}
			}
			if (GUI::Float("Light Multiplier", Features::Lightint, 1, 1000)) {
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Features::Lightint = Features::NumberKeyboard();
				}
				if (IsKeyPressed(VK_RETURN) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Features::Lightint = Features::NumberKeyboard();
				}
			}
			if (GUI::Float("Break Multiplier", Features::Breakfloat, 1, 100)) {
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Features::Breakfloat = Features::NumberKeyboard();
				}
				if (IsKeyPressed(VK_RETURN) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Features::Breakfloat = Features::NumberKeyboard();
				}
			}
		}
		break;

#pragma endregion

#pragma region Vehicle Manager
		case vehiclemanager:
			GUI::Title("Vehicle Manager");
			GUI::Subtitle("Vehicle Manager");
			for (int i = 0; i < Features::spawnvehl; i++) {
				if (ENTITY::DOES_ENTITY_EXIST(Features::spawnedVeh[i])) {
					if (GUI::MenuOption(Features::spawnedvehnames[i], editveh)) {
						latestedveh = Features::spawnedVeh[i];
						selectedveh = i;
					}
				}
			}
			break;
#pragma endregion

#pragma region Vehicle Editor
		case editveh:
			GUI::Title("Edit Vehicle");
			GUI::Subtitle("Edit Vehicle");
			//done just add the options you want in here :)
			break;
#pragma endregion

#pragma endregion

#pragma region Teleport SubMenus

#pragma region Locations
		//Teleports Bunkers
		case tpbunkers:
		{
			GUI::Title("");
			GUI::Subtitle("Bunkers");
			if (GUI::Option("Zancudo")) {
				Vector3 Coords;
				Coords.x = -3058.714f; Coords.y = 3329.19f; Coords.z = 12.5844f;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Route 68")) {
				Vector3 Coords;
				Coords.x = 24.43542f; Coords.y = 2959.705f; Coords.z = 58.35517f;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Oil Fields")) {
				Vector3 Coords;
				Coords.x = 481.0465f; Coords.y = 2995.135f; Coords.z = 43.96672f;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Desert")) {
				Vector3 Coords;
				Coords.x = 848.6175f; Coords.y = 2996.567f; Coords.z = 45.81612f;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Smoke Tree")) {
				Vector3 Coords;
				Coords.x = 2126.785f; Coords.y = 3335.04f; Coords.z = 48.21422f;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Scrapyard")) {
				Vector3 Coords;
				Coords.x = 2493.654f; Coords.y = 3140.399f; Coords.z = 51.28789f;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Grape Seed")) {
				Vector3 Coords;
				Coords.x = 1823.961f; Coords.y = 4708.14f; Coords.z = 42.4991f;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Palleto Bay")) {
				Vector3 Coords;
				Coords.x = -783.0755f; Coords.y = 5934.686f; Coords.z = 24.31475f;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Route 1")) {
				Vector3 Coords;
				Coords.x = -3180.466f; Coords.y = 1374.192f; Coords.z = 19.9597f;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Farm House")) {
				Vector3 Coords;
				Coords.x = 1570.372f; Coords.y = 2254.549f; Coords.z = 78.89397f;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Raton Canyon")) {
				Vector3 Coords;
				Coords.x = -391.3216f; Coords.y = 4363.728f; Coords.z = 58.65862f;
				Features::teleportToLocation(Coords);
			}
		}
		break;

		//Teleport Indoors
		case tpindoors:
		{
			GUI::Title("");
			GUI::Subtitle("Indoors");
			if (GUI::Option("10 Car Garage Back Room")) {
				Vector3 Coords;
				Coords.x = 223.193f; Coords.y = -967.322f; Coords.z = 99.000f;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("10 Car Garage Bay")) {
				Vector3 Coords;
				Coords.x = 228.135; Coords.y = -995.350; Coords.z = -99.000;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Ammunation Gun Range")) {
				Vector3 Coords;
				Coords.x = 22.153; Coords.y = -1072.854; Coords.z = 29.797;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Ammunation Office")) {
				Vector3 Coords;
				Coords.x = 247.3652; Coords.y = -45.8777; Coords.z = 69.9411;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Bahama Mamas West")) {
				Vector3 Coords;
				Coords.x = -1387.08; Coords.y = -588.4; Coords.z = 30.3195;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Blaine County Bank")) {
				Vector3 Coords;
				Coords.x = -109.299; Coords.y = 6464.035; Coords.z = 31.627;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Burnt FIB Building")) {
				Vector3 Coords;
				Coords.x = 160.868; Coords.y = -745.831; Coords.z = 250.063;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Control Office")) {
				Vector3 Coords;
				Coords.x = 1080.97; Coords.y = -1976.0; Coords.z = 31.4721;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Devin's Garage")) {
				Vector3 Coords;
				Coords.x = 482.027; Coords.y = -1317.96; Coords.z = 29.2021;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Eclipse Apartment 5")) {
				Vector3 Coords;
				Coords.x = -762.762; Coords.y = 322.634; Coords.z = 175.401;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Eclipse Apartment 9")) {
				Vector3 Coords;
				Coords.x = -790.673; Coords.y = 334.468; Coords.z = 158.599;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Eclipse Apartment 31")) {
				Vector3 Coords;
				Coords.x = -762.762; Coords.y = 322.634; Coords.z = 221.855;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Eclipse Apartment 40")) {
				Vector3 Coords;
				Coords.x = -790.673; Coords.y = 334.468; Coords.z = 206.218;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Floyd's Apartment")) {
				Vector3 Coords;
				Coords.x = -1150.703; Coords.y = -1520.713; Coords.z = 10.633;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Garment Factory")) {
				Vector3 Coords;
				Coords.x = 717.397; Coords.y = -965.572; Coords.z = 30.3955;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Humane Labs Lower Level")) {
				Vector3 Coords;
				Coords.x = 3617.231f; Coords.y = 3739.871f; Coords.z = 28.6901f;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Humane Labs Upper Level")) {
				Vector3 Coords;
				Coords.x = 3617.231f; Coords.y = 3739.871f; Coords.z = 28.6901f;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("IAA Office")) {
				Vector3 Coords;
				Coords.x = 117.220; Coords.y = -620.938; Coords.z = 206.047;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Ice Planet Jewelery")) {
				Vector3 Coords;
				Coords.x = 243.516; Coords.y = 364.099; Coords.z = 105.738;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Janitor's Apartment")) {
				Vector3 Coords;
				Coords.x = -110.721; Coords.y = -8.22095; Coords.z = 70.5197;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Lester's House")) {
				Vector3 Coords;
				Coords.x = 1273.898; Coords.y = -1719.304; Coords.z = 54.771;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Pacific Standard Bank Vault")) {
				Vector3 Coords;
				Coords.x = 255.851; Coords.y = 217.030; Coords.z = 101.683;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Paleto Bay Sheriff")) {
				Vector3 Coords;
				Coords.x = -446.135; Coords.y = 6012.91; Coords.z = 31.7164;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Police Station")) {
				Vector3 Coords;
				Coords.x = 436.491; Coords.y = -982.172; Coords.z = 30.699;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Raven Slaughterhouse")) {
				Vector3 Coords;
				Coords.x = 967.357; Coords.y = -2184.71; Coords.z = 30.0613;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Rogers Salvage & Scrap")) {
				Vector3 Coords;
				Coords.x = -609.962; Coords.y = -1612.49; Coords.z = 27.0105;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Sandy Shores Sheriff")) {
				Vector3 Coords;
				Coords.x = 1853.18; Coords.y = 3686.63; Coords.z = 34.2671;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Simeon's Dealership")) {
				Vector3 Coords;
				Coords.x = -56.4951; Coords.y = -1095.8; Coords.z = 26.4224;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Split Sides West Comedy Club")) {
				Vector3 Coords;
				Coords.x = -564.261; Coords.y = 278.232; Coords.z = 83.1364;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Strip Club DJ Booth")) {
				Vector3 Coords;
				Coords.x = 126.135; Coords.y = -1278.583; Coords.z = 29.270;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Torture Room")) {
				Vector3 Coords;
				Coords.x = 147.170; Coords.y = -2201.804; Coords.z = 4.688;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Zancudo Entrance")) {
				Vector3 Coords;
				Coords.x = -2344.373; Coords.y = 3267.498; Coords.z = 32.811;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Zancudo Tower")) {
				Vector3 Coords;
				Coords.x = -2356.0940; Coords.y = 3248.645; Coords.z = 101.4505;
				Features::teleportToLocation(Coords);
			}
		}
		break;

		//Teleports IPLs
		case tpipls:
		{
			GUI::Title("");
			GUI::Subtitle("IPLs");
			if (GUI::Option("North Yankton")) {
				STREAMING::REQUEST_IPL("prologue01");
				STREAMING::REQUEST_IPL("Prologue01c");
				STREAMING::REQUEST_IPL("Prologue01d");
				STREAMING::REQUEST_IPL("Prologue01e");
				STREAMING::REQUEST_IPL("Prologue01f");
				STREAMING::REQUEST_IPL("Prologue01g");
				STREAMING::REQUEST_IPL("prologue01h");
				STREAMING::REQUEST_IPL("prologue01i");
				STREAMING::REQUEST_IPL("prologue01j");
				STREAMING::REQUEST_IPL("prologue01k");
				STREAMING::REQUEST_IPL("prologue01z");
				STREAMING::REQUEST_IPL("prologue02");
				STREAMING::REQUEST_IPL("prologue03");
				STREAMING::REQUEST_IPL("prologue03b");
				STREAMING::REQUEST_IPL("prologue03_grv_cov");
				STREAMING::REQUEST_IPL("prologue03_grv_dug");
				STREAMING::REQUEST_IPL("prologue03_grv_fun");
				STREAMING::REQUEST_IPL("prologue04");
				STREAMING::REQUEST_IPL("prologue04b");
				STREAMING::REQUEST_IPL("prologue04_cover");
				STREAMING::REQUEST_IPL("prologue05");
				STREAMING::REQUEST_IPL("prologue05b");
				STREAMING::REQUEST_IPL("prologue06");
				STREAMING::REQUEST_IPL("prologue06b");
				STREAMING::REQUEST_IPL("prologue06_int");
				STREAMING::REQUEST_IPL("prologuerd");
				STREAMING::REQUEST_IPL("prologuerdb");
				STREAMING::REQUEST_IPL("prologue_DistantLights");
				STREAMING::REQUEST_IPL("prologue_grv_torch");
				STREAMING::REQUEST_IPL("prologue_m2_door");
				STREAMING::REQUEST_IPL("prologue_LODLights");
				STREAMING::REQUEST_IPL("DES_ProTree_start");
				Vector3 Coords;
				Coords.x = 3595.39673f; Coords.y = -4893.727f; Coords.z = 115.838394f;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Porn Yacht")) {
				STREAMING::REQUEST_IPL("smboat");
				Vector3 Coords;
				Coords.x = -2045.8f; Coords.y = -1031.2f; Coords.z = 11.9f;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Aircraft Carrier")) {
				STREAMING::REQUEST_IPL("hei_carrier");
				STREAMING::REQUEST_IPL("hei_carrier_DistantLights");
				STREAMING::REQUEST_IPL("hei_Carrier_int1");
				STREAMING::REQUEST_IPL("hei_Carrier_int2");
				STREAMING::REQUEST_IPL("hei_Carrier_int3");
				STREAMING::REQUEST_IPL("hei_Carrier_int4");
				STREAMING::REQUEST_IPL("hei_Carrier_int5");
				STREAMING::REQUEST_IPL("hei_Carrier_int6");
				STREAMING::REQUEST_IPL("hei_carrier_LODLights");
				Vector3 Coords;
				Coords.x = 3069.330f; Coords.y = -4632.4f; Coords.z = 15.043f;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Sunken Cargoship")) {
				STREAMING::REQUEST_IPL("sunkcargoship");
				Vector3 Coords;
				Coords.x = -162.8918f; Coords.y = -2365.769f; Coords.z = 0.0f;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Hospital")) {
				STREAMING::REQUEST_IPL("RC12B_HospitalInterior");
				STREAMING::REQUEST_IPL("RC12B_Destroyed");
				Vector3 Coords;
				Coords.x = 356.8f; Coords.y = -590.1f; Coords.z = 43.3f;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Oneil Farm")) {
				STREAMING::REMOVE_IPL("farm_burnt");
				STREAMING::REMOVE_IPL("farm_burnt_props");
				STREAMING::REQUEST_IPL("farm");
				STREAMING::REQUEST_IPL("farm_props");
				STREAMING::REQUEST_IPL("farmint");
				STREAMING::REQUEST_IPL("farmint_cap");
				Vector3 Coords;
				Coords.x = 2441.2f; Coords.y = 4968.5f; Coords.z = 51.7f;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Life Invader Office")) {
				STREAMING::REQUEST_IPL("facelobby");
				STREAMING::REQUEST_IPL("facelobbyfake");
				Vector3 Coords;
				Coords.x = -1047.9f; Coords.y = -233.0f; Coords.z = 39.0f;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Cargoship")) {
				STREAMING::REQUEST_IPL("cargoship");
				Vector3 Coords;
				Coords.x = -162.8918f; Coords.y = -2365.769f; Coords.z = 9.3192f;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Jewelry Store")) {
				STREAMING::REQUEST_IPL("jewel2fake");
				STREAMING::REQUEST_IPL("post_hiest_unload");
				STREAMING::REQUEST_IPL("bh1_16_refurb");
				Vector3 Coords;
				Coords.x = -630.4f; Coords.y = -236.7f; Coords.z = 40.0f;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Morgue")) {
				STREAMING::REQUEST_IPL("Coroner_Int_on");
				Vector3 Coords;
				Coords.x = 244.9f; Coords.y = -1374.7f; Coords.z = 39.5f;
				Features::teleportToLocation(Coords);
			}
		}
		break;

		//Teleport Underwater
		case tpunderwater:
		{
			GUI::Title("");
			GUI::Subtitle("Underwater");
			if (GUI::Option("Dead Sea Monster")) {
				Vector3 Coords;
				Coords.x = -3373.726; Coords.y = 504.714; Coords.z = -24.656;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Underwater Hatch")) {
				Vector3 Coords;
				Coords.x = 4273.950; Coords.y = 2975.714; Coords.z = -170.746;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Underwater UFO")) {
				Vector3 Coords;
				Coords.x = 762.426; Coords.y = 7380.371; Coords.z = -111.377;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Underwater WW2 Tank")) {
				Vector3 Coords;
				Coords.x = 4201.633; Coords.y = 3643.821; Coords.z = -39.016;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Sunken Body")) {
				Vector3 Coords;
				Coords.x = -3161.078; Coords.y = 3001.998; Coords.z = -37.974;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Sunken Cargo Ship")) {
				Vector3 Coords;
				Coords.x = 3199.748; Coords.y = -379.018; Coords.z = -22.500;
				Features::teleportToLocation(Coords);
			}
		}
		break;

		//Teleport High
		case tphigh:
		{
			GUI::Title("");
			GUI::Subtitle("High Places");
			if (GUI::Option("Airplane Graveyard Airplane Tail")) {
				Vector3 Coords;
				Coords.x = 2395.096; Coords.y = 3049.616; Coords.z = 60.053;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("FIB Top Floor")) {
				Vector3 Coords;
				Coords.x = 135.733; Coords.y = -749.216; Coords.z = 258.152;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Galileo Observatory Roof")) {
				Vector3 Coords;
				Coords.x = -438.804; Coords.y = 1076.097; Coords.z = 352.411;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("IAA Building Roof")) {
				Vector3 Coords;
				Coords.x = 134.085; Coords.y = -637.859; Coords.z = 262.851;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Maze Bank Arena Roof")) {
				Vector3 Coords;
				Coords.x = -324.300; Coords.y = -1968.545; Coords.z = 67.002;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Maze Bank")) {
				Vector3 Coords;
				Coords.x = -74.94243f; Coords.y = -818.63446f; Coords.z = 326.174347f;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Mount Chiliad")) {
				Vector3 Coords;
				Coords.x = 496.75; Coords.y = 5591.17; Coords.z = 795.03;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Palmer-Taylor Power Station Chimney")) {
				Vector3 Coords;
				Coords.x = 2732.931; Coords.y = 1577.540; Coords.z = 83.671;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Rebel Radio")) {
				Vector3 Coords;
				Coords.x = 736.153; Coords.y = 2583.143; Coords.z = 79.634;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Sandy Shores Building Site Crane")) {
				Vector3 Coords;
				Coords.x = 1051.209; Coords.y = 2280.452; Coords.z = 89.727;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Satellite Dish Antenna")) {
				Vector3 Coords;
				Coords.x = 2034.988; Coords.y = 2953.105; Coords.z = 74.602;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Stab City")) {
				Vector3 Coords;
				Coords.x = 126.975; Coords.y = 3714.419; Coords.z = 46.827;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Very High Up")) {
				Vector3 Coords;
				Coords.x = -129.964; Coords.y = 8130.873; Coords.z = 6705.307;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Windmill Top")) {
				Vector3 Coords;
				Coords.x = 2026.677; Coords.y = 1842.684; Coords.z = 133.313;
				Features::teleportToLocation(Coords);
			}
		}
		break;

		//Teleport Landmarks
		case tplandmarks:
		{
			GUI::Title("");
			GUI::Subtitle("Landmarks");
			if (GUI::Option("Airport Entrance")) {
				Vector3 Coords;
				Coords.x = -1034.6; Coords.y = -2733.6; Coords.z = 13.8;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Airport Field")) {
				Vector3 Coords;
				Coords.x = -1102.2910; Coords.y = -2894.5160; Coords.z = 13.9467;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Altruist Cult Camp")) {
				Vector3 Coords;
				Coords.x = -1170.841; Coords.y = 4926.646; Coords.z = 224.295;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Calafia Train Bridge")) {
				Vector3 Coords;
				Coords.x = -517.869; Coords.y = 4425.284; Coords.z = 89.795;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Cargo Ship")) {
				Vector3 Coords;
				Coords.x = 899.678; Coords.y = -2882.191; Coords.z = 19.013;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Chumash")) {
				Vector3 Coords;
				Coords.x = -3192.6; Coords.y = 1100.0; Coords.z = 20.2;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Chumash Historic Family Pier")) {
				Vector3 Coords;
				Coords.x = -3426.683; Coords.y = 967.738; Coords.z = 8.347;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Clothes Store")) {
				Vector3 Coords;
				Coords.x = -718.91; Coords.y = -158.16; Coords.z = 37.00;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Del Perro Pier")) {
				Vector3 Coords;
				Coords.x = -1850.127; Coords.y = -1231.751; Coords.z = 13.017;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Devin Weston's House")) {
				Vector3 Coords;
				Coords.x = -2639.872; Coords.y = 1866.812; Coords.z = 160.135;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("El Burro Heights")) {
				Vector3 Coords;
				Coords.x = 1384.0; Coords.y = -2057.1; Coords.z = 52.0;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Elysian Island")) {
				Vector3 Coords;
				Coords.x = 338.2; Coords.y = -2715.9; Coords.z = 38.5;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Far North San Andreas")) {
				Vector3 Coords;
				Coords.x = 24.775; Coords.y = 7644.102; Coords.z = 19.055;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Ferris Wheel")) {
				Vector3 Coords;
				Coords.x = -1670.7; Coords.y = -1125.0; Coords.z = 13.0;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Fort Zancudo")) {
				Vector3 Coords;
				Coords.x = -2047.4; Coords.y = 3132.1; Coords.z = 32.8;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("God's Thumb")) {
				Vector3 Coords;
				Coords.x = -1006.402; Coords.y = 6272.383; Coords.z = 1.503;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Hippy Camp")) {
				Vector3 Coords;
				Coords.x = 2476.712; Coords.y = 3789.645; Coords.z = 41.226;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Jetsam")) {
				Vector3 Coords;
				Coords.x = 760.4; Coords.y = -2943.2; Coords.z = 5.8;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Jolene Cranley-Evans Ghost")) {
				Vector3 Coords;
				Coords.x = 3059.620; Coords.y = 5564.246; Coords.z = 197.091;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Kortz Center")) {
				Vector3 Coords;
				Coords.x = -2243.810; Coords.y = 264.048; Coords.z = 174.615;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Los Santos Customs")) {
				Vector3 Coords;
				Coords.x = -373.01; Coords.y = -124.91; Coords.z = 38.31;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Marlowe Vineyards")) {
				Vector3 Coords;
				Coords.x = -1868.971; Coords.y = 2095.674; Coords.z = 139.115;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Mask Shop")) {
				Vector3 Coords;
				Coords.x = -1338.16; Coords.y = -1278.11; Coords.z = 4.87;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("McKenzie Airfield")) {
				Vector3 Coords;
				Coords.x = 2121.7; Coords.y = 4796.3; Coords.z = 41.1;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Merryweather Dock")) {
				Vector3 Coords;
				Coords.x = 486.417; Coords.y = -3339.692; Coords.z = 6.070;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Mineshaft")) {
				Vector3 Coords;
				Coords.x = -595.342; Coords.y = 2086.008; Coords.z = 131.412;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Mors Mutual Insurance")) {
				Vector3 Coords;
				Coords.x = -222.1977; Coords.y = -1185.8500; Coords.z = 23.0294;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Mt. Chiliad")) {
				Vector3 Coords;
				Coords.x = 425.4; Coords.y = 5614.3; Coords.z = 766.5;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("NOOSE Headquarters")) {
				Vector3 Coords;
				Coords.x = 2535.243; Coords.y = -383.799; Coords.z = 92.993;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Pacific Standard Bank")) {
				Vector3 Coords;
				Coords.x = 235.046; Coords.y = 216.434; Coords.z = 106.287;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Paleto Bay Pier")) {
				Vector3 Coords;
				Coords.x = -275.522; Coords.y = 6635.835; Coords.z = 7.425;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Playboy Mansion")) {
				Vector3 Coords;
				Coords.x = -1475.234; Coords.y = 167.088; Coords.z = 55.841;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Quarry")) {
				Vector3 Coords;
				Coords.x = 2954.196; Coords.y = 2783.410; Coords.z = 41.004;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Sandy Shores Airfield")) {
				Vector3 Coords;
				Coords.x = 1741.4960; Coords.y = 3269.2570; Coords.z = 41.6014;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Satellite Dishes")) {
				Vector3 Coords;
				Coords.x = 2062.123; Coords.y = 2942.055; Coords.z = 47.431;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Sisyphus Theater Stage")) {
				Vector3 Coords;
				Coords.x = 686.245; Coords.y = 577.950; Coords.z = 130.461;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Trevor's Meth Lab")) {
				Vector3 Coords;
				Coords.x = 1391.773; Coords.y = 3608.716; Coords.z = 38.942;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Waterfall")) {
				Vector3 Coords;
				Coords.x = -597.9525f; Coords.y = 4475.2910f; Coords.z = 25.6890f;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Weed Farm")) {
				Vector3 Coords;
				Coords.x = 2208.777; Coords.y = 5578.235; Coords.z = 53.735;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Wind Farm")) {
				Vector3 Coords;
				Coords.x = 2354.0; Coords.y = 1830.3; Coords.z = 101.1;
				Features::teleportToLocation(Coords);
			}

		}
		break;

		case tpsafehouses:
		{
			GUI::Title("");
			GUI::Subtitle("Safehouses");
			if (GUI::Option("Franklin's Safehouse")) {
				Vector3 Coords;
				Coords.x = -18.0355; Coords.y = -1456.94; Coords.z = 30.4548;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Franklin's Safehouse Inside")) {
				Vector3 Coords;
				Coords.x = -14.3803; Coords.y = -1438.51; Coords.z = 31.1073;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Franklin's Safehouse 2")) {
				Vector3 Coords;
				Coords.x = 10.8766; Coords.y = 545.654; Coords.z = 175.419;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Franklin's Safehouse 2 Inside")) {
				Vector3 Coords;
				Coords.x = 7.11903; Coords.y = 536.615; Coords.z = 176.028;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Michael's Safehouse")) {
				Vector3 Coords;
				Coords.x = -827.138; Coords.y = 176.368; Coords.z = 70.4999;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Michael's Safehouse Inside")) {
				Vector3 Coords;
				Coords.x = -813.603; Coords.y = 179.474; Coords.z = 72.1548;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Trevor's Safehouse")) {
				Vector3 Coords;
				Coords.x = 1982.13; Coords.y = 3829.44; Coords.z = 32.3662;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Trevor's Safehouse 2")) {
				Vector3 Coords;
				Coords.x = -1157.05; Coords.y = -1512.73; Coords.z = 4.2127;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Trevor's Safehouse 3")) {
				Vector3 Coords;
				Coords.x = 91.1407; Coords.y = -1280.65; Coords.z = 29.1353;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Trevor's Safehouse Inside")) {
				Vector3 Coords;
				Coords.x = 1972.61; Coords.y = 3817.04; Coords.z = 33.4278;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Trevor's Safehouse 2 Inside")) {
				Vector3 Coords;
				Coords.x = -1151.77f; Coords.y = -1518.14f; Coords.z = 10.6327f;
				Features::teleportToLocation(Coords);
			}
			if (GUI::Option("Trevor's Safehouse 3 Inside")) {
				Vector3 Coords;
				Coords.x = 96.1536f; Coords.y = -1290.73f; Coords.z = 29.2664f;
				Features::teleportToLocation(Coords);
			}
		}
		break;
#pragma endregion

#pragma endregion

#pragma region Network SubMenus

#pragma region Online Protections

		case protections:
		{
			GUI::Title("");
			GUI::Subtitle("Online Protections");
				GUI::Toggle("Anti-Idle Kick", Features::isAntiAFK, [] { Features::antiAFK(Features::isAntiAFK); });
				if (Features::menu_version == 2) {
				GUI::Toggle("Anti Vote Kick", ak, [] { Hooking::defuseEvent(eRockstarEvent::KICK_VOTES_EVENT, ak); });
				}
				GUI::Toggle("CEO Ban", Features::isCEOBanProtex);
				GUI::Toggle("CEO Kick", Features::isCEOKickProtex);
				GUI::Toggle("Non-Host Kick [New Session]", Features::isKickToFMProtex);
				GUI::Toggle("Non-Host Kick [Story Mode]", Features::isKickToSPProtex);
				GUI::Toggle("Send to Mission", Features::isSendToJobProtex);
				GUI::Toggle("Sound Spam & Invite Spam", Features::isSoundSpamProtex);
				GUI::Toggle("Teleportation & Infinite Invite Screen", Features::isTeleportProtex);
				if (Features::menu_version == 2) {
					GUI::Toggle("Online Crash", Features::isCrashProtex, [] { Features::antiCrash(Features::isCrashProtex); }); //VIP
					GUI::Toggle("Banner", Features::isGTABannerProtex); //VIP
					GUI::Toggle("Transaction Errors", Features::isTransactionErrorProtex); //VIP
				}
				GUI::Break("Defuse Events / Events Disabler");
				GUI::Toggle("Change Time", Features::isChangeTime, [] { Features::antiChangeTime(); });
				GUI::Toggle("Change Weather", Features::isChangeWeather, [] { Features::antiChangeWeather(); });
				GUI::Toggle("Explosions", Features::isAntiExplosion, [] { Features::antiExplosion(); });
				GUI::Toggle("Fire/Water", Features::isAntiFire, [] { Features::antiFire(); });
				GUI::Toggle("Freeze", Features::isClearTasks, [] { Features::antiClearPedTasks(); });
				GUI::Toggle("Give Weapon", Features::isGiveWeapon, [] { Features::antiGiveWeapons(); });
				GUI::Toggle("Particle Effects", Features::isAntiPTFX, [] { Features::antiPTFX(); });
				GUI::Toggle("Ragdoll", Features::isAntiRagdoll, [] { Features::antiRagdoll(); });
				GUI::Toggle("Request Control", Features::isRequestControl, [] { Features::antiRequestControl(); });
				GUI::Toggle("Remove Weapon", Features::isRemoveWeapon, [] { Features::antiRemoveWeapons(); });
				//GUI::Toggle("Anti Car Horn (NEW)", Features::isHornProtection, [] { Features::antiHornProtection(); });
				GUI::Toggle("Vehicle Control", Features::isAntiVehControl, [] { Features::antiVehControl(); });
		}
		break;

#pragma endregion

#pragma region Online Menu

		case onlinemenu_playerlist:
		{
			GUI::Title("");
			GUI::Subtitle("Player List");
			if (!NETWORK::NETWORK_IS_IN_SESSION() && !NETWORK::NETWORK_IS_PLAYER_CONNECTED(PLAYER::PLAYER_PED_ID())) {
				GUI::Option("You need to be online to use this.");
			}
			else
			{
				for (int i = 0; i < 32; i++)
				{
					if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))) {
						Player player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
						bool is_friend = false;
						bool handle_valid = Features::isPlayerFriend(i, is_friend);
						std::string playerTag = Hooking::get_player_name(i);

						if (Hooking::network_is_session_started()) {
							if (NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0) == i) {
								playerTag += " ~r~[HOST]";
							}
							if (globalHandle(2423801).At(i, 413).At(200).As<int>()) {
								playerTag += " ~o~[OTR]";
							}
							if (player == PLAYER::PLAYER_PED_ID()) {
								playerTag += " ~b~[SELF]";
							}
							if (handle_valid && is_friend) {
								playerTag += " ~g~[FRIEND]";
							}

							GUI::MenuPlayer((char*)playerTag.c_str(), onlinemenu_selected, i) ? Features::Online::selectedPlayer = i : NULL;
						}
						else
						{
							GUI::MenuPlayer((char*)playerTag.c_str(), onlinemenu_selected, i) ? Features::Online::selectedPlayer = i : NULL;
							break;
						}
					}
				}
			}
		}
		break;

		case onlinemenu_selected:
		{
			GUI::Title("");
			GUI::Subtitle(Hooking::get_player_name(Features::Online::selectedPlayer));
			Features::LoadPlayerInfo(Hooking::get_player_name(Features::Online::selectedPlayer), Features::Online::selectedPlayer);
			if (!NETWORK::NETWORK_IS_IN_SESSION() && !NETWORK::NETWORK_IS_PLAYER_CONNECTED(PLAYER::PLAYER_PED_ID())) {
				GUI::Option("You need to be online to use this.");
			}
			else 
			{
				GUI::MenuOption("Drop Items", dropoptions);
				GUI::MenuOption("Weapon Options", weaponss_options);
				GUI::MenuOption("Griefing Options", troll_options);
				GUI::MenuOption("Teleport Options", tpother);
				GUI::MenuOption("Vehicle Options", vehicle_options);
				GUI::MenuOption("Spawn Body Guards", bodyoptions);
				if (Features::Online::selectedPlayer != PLAYER::PLAYER_ID()) { GUI::Toggle("Draw Waypoint", Features::isMarkRoutePlayer, [] { Features::markRoutePlayer(); }); }
				//if (Features::Online::selectedPlayer != PLAYER::PLAYER_ID()) { GUI::Toggle("Mark as Enemy", Features::isMarkPlayerEnemy, [] { Features::markPlayerEnemy(); }); }
				//if (Features::Online::selectedPlayer != PLAYER::PLAYER_ID()) { GUI::Toggle("Mark as Friendly", Features::isMarkPlayerFriendly, [] { Features::markPlayerFriendly(); }); }
				if (Features::Online::selectedPlayer != PLAYER::PLAYER_ID()) { GUI::Toggle("Spectate", Features::isSpectatePlayer, [] { Features::spectatePlayer(Features::isSpectatePlayer); }); }
			}

			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), false);
			GRAPHICS::DRAW_MARKER(2, coords.x, coords.y, coords.z + 1.3f, 0.0f, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f, 0.3f, 0.3f, 0.3f, 65, 244, 89, 200, 1, 1, 1, 0, 0, 0, 0);

			//GUI::MenuOption("~w~Effects ~w~->", onlineftp);
			//GUI::MenuOption("~w~Attach to Player", attachtp);
			//GUI::MenuOption("~w~Vehicle Weapons", vehweapplay);
			//GUI::MenuOption("Pickup Drop Options", dropOnlinepick);
			//GUI::MenuOption("Custom Outfit Changer Player", cocplll);
			//GUI::MenuOption("Vehicle Spawner to Player", vehspawneralone);
		}
		break;

#pragma endregion

#pragma region All Players
		case troll_all_players:
		{
			GUI::Title("All Players");
			GUI::Subtitle("All Players");
			if (!NETWORK::NETWORK_IS_IN_SESSION() && !NETWORK::NETWORK_IS_PLAYER_CONNECTED(PLAYER::PLAYER_PED_ID())) {
				GUI::Option("You need to be online to use this.");
			}
			else {
				GUI::MenuOption("Change Lobby Weather", lobby_weather);
				GUI::MenuOption("Teleport All to Apartments", teleport_all_apartments);
				GUI::Toggle("Show Talking Players", Features::ShowTalking, [] { Features::ShowTalkingbool(Features::ShowTalking); });
				GUI::Break("Griefing");
				if (GUI::Option("Alien Invasion")) {
					for (int i = 0; i <= 32; i++)
					{
						WAIT(0);
						if (i == PLAYER::PLAYER_ID())continue;
						int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
						AI::CLEAR_PED_TASKS_IMMEDIATELY(Handle);
						Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(Handle, 0);
						Hash oball = GAMEPLAY::GET_HASH_KEY("p_spinning_anus_s");
						STREAMING::REQUEST_MODEL(oball);
						while (!STREAMING::HAS_MODEL_LOADED(oball))
							WAIT(0);
						//	int orangeball = CREATE_OBJECT(oball, pCoords.x, pCoords.y, pCoords.z, true, 1, 0);
						//	ATTACH_ENTITY_TO_ENTITY(orangeball, Handle, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 2, 1);
						AI::CLEAR_PED_TASKS_IMMEDIATELY(Handle);
						int createdObject = NETWORK::OBJ_TO_NET(OBJECT::CREATE_OBJECT_NO_OFFSET(oball, pCoords.x, pCoords.y, pCoords.z, 1, 0, 0));

						{
							if (i == 32)
							{
								break;
							}

						}
					}
				}
				if (GUI::Option("Give All Weapons")) {
					std::vector<uint> Weapons{
					0x92A27487, 0x958A4A8F, 0xF9E6AA4B, 0x84BD7BFD, 0xA2719263, 0x8BB05FD7, 0x440E4788, 0x4E875F73, 0xF9DCBF2D, 0xD8DF3C3C, 0x99B507EA, 0xDD5DF8D9, 0xDFE37640, 0x678B81B1, 0x19044EE0, 0xCD274149, 0x94117305, 0x3813FC08, // Melee
					0x1B06D571, 0xBFE256D4, 0x5EF9FEC4, 0x22D8FE39, 0x3656C8C1, 0x99AEEB3B, 0xBFD21232, 0x88374054, 0xD205520E, 0x83839C4, 0x47757124, 0xDC4DB296, 0xC1B3C3D1, 0xCB96392F, 0x97EA20B8, // Handguns
					0x13532244, 0x2BE6766B, 0x2BE6766B, 0xEFE7E2DF, 0x0A3D4D34, 0xDB1AA450, 0xBD248B55, // Submachine Guns
					0x1D073A89, 0x555AF99A, 0x7846A318, 0xE284C527, 0x9D61E50F, 0xA89CB99E, 0x3AABBBAA, 0xEF951FBB, 0x12E82D3D, // Shotguns
					0xBFEFFF6D, 0x394F415C, 0x83BF0278, 0xFAD1F1C9, 0xAF113F99, 0xC0A3098D, 0x969C3D67, 0x7F229F94, 0x84D6FAFD, 0x624FE830, // Assault Rifles
					0x9D07F764, 0x7FD62962, 0xDBBD7280, 0x61012683, // Light Machine Guns
					0x05FC3C11, 0x0C472FE2, 0xA914799, 0xC734385A, 0x6A6C02E0, // Sniper Rifles
					0xB1CA77B1, 0xA284510B, 0x4DD2DC56, 0x42BF8A85, 0x7F7497E5, 0x6D544C99, 0x63AB0442, 0x0781FE4A, // Heavy Weapons
					0x93E220BD, 0xA0973D5E, 0x24B17070, 0x2C3731D9, 0xAB564B93, 0x787F0BB, 0xBA45E8B8, 0x23C9F95C, 0xFDBC8A50, 0x497FACC3, // Throwables
					0x34A67B97, 0xFBAB5776, 0x060EC506, // Miscellaneous
					0x476BF155, 0xAF3696A1, 0xB62D1F67 // Arena Wars
					};

					for (int i = 0; i <= 32; i++)
					{
						WAIT(0);
						if (i == PLAYER::PLAYER_ID())continue;
						int players = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);

						for (Hash hash : Weapons) {
							WEAPON::GIVE_DELAYED_WEAPON_TO_PED(players, hash, 9999, 0);
							{
								if (i == 32)
								{
									break;
								}
							}
						}
					}
				}
				if (GUI::Option("Take All Weapons")) {
					for (int i = 0; i <= 32; i++)
					{
						WAIT(0);
						if (i == PLAYER::PLAYER_ID())continue;
						int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
						WEAPON::REMOVE_ALL_PED_WEAPONS(Handle, 1);
						{
							if (i == 32)
							{
								break;
							}

						}
					}
				}
				if (GUI::Option("Give All Railguns")) {
					for (int i = 0; i <= 32; i++)
					{
						WAIT(0);
						if (i == PLAYER::PLAYER_ID())continue;
						int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
						Hash railgun = GAMEPLAY::GET_HASH_KEY("WEAPON_RAILGUN");
						WEAPON::GIVE_WEAPON_TO_PED(Handle, railgun, railgun, 9999, 9999);
						{
							if (i == 32)
							{
								break;
							}

						}
					}
				}
				if (GUI::Option("Give All Taser")) {
					for (int i = 0; i <= 32; i++)
					{
						WAIT(0);
						if (i == PLAYER::PLAYER_ID())continue;
						int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
						Hash railgun = GAMEPLAY::GET_HASH_KEY("WEAPON_STUNGUN");
						WEAPON::GIVE_WEAPON_TO_PED(Handle, railgun, railgun, 9999, 9999);
						{
							if (i == 32)
							{
								break;
							}

						}
					}
				}
				if (GUI::Option("Give All snowballs")) {
					for (int i = 0; i <= 32; i++)
					{
						WAIT(0);
						if (i == PLAYER::PLAYER_ID())continue;
						int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
						Hash railgun = GAMEPLAY::GET_HASH_KEY("WEAPON_SNOWBALL");
						WEAPON::GIVE_WEAPON_TO_PED(Handle, railgun, railgun, 9999, 9999);
						{
							if (i == 32)
							{
								break;
							}

						}
					}
				}
				if (GUI::Option("Shake Lobby")) {
					Ped playerPedID = PLAYER::PLAYER_PED_ID();
					Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(playerPedID, 0);
					for (int i = 0; i <= 32; i++)
					{
						WAIT(0);
						if (i == PLAYER::PLAYER_ID())continue;
						int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
						Vector3 pos = ENTITY::GET_ENTITY_COORDS(Handle, 1);
						if (!ENTITY::DOES_ENTITY_EXIST(Handle)) continue;
						FIRE::ADD_EXPLOSION(pos.x, pos.y, pos.z + 15, 29, 999999.5f, false, true, 1.0f, true);
						{
							if (i == 32)

							{
								break;
							}

						}
					}
				}
				if (GUI::Option("Attach BeachFire to All")) {
					for (int i = 0; i <= 32; i++)
					{
						WAIT(0);
						if (i == PLAYER::PLAYER_ID())continue;
						int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
						Hash oball = GAMEPLAY::GET_HASH_KEY("prop_beach_fire");
						STREAMING::REQUEST_MODEL(oball);
						while (!STREAMING::HAS_MODEL_LOADED(oball))
							WAIT(0);
						int orangeball = OBJECT::CREATE_OBJECT(oball, 0, 0, 0, true, 1, 0);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(orangeball, Handle, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 2, 1);
						{
							if (i == 32)
							{
								break;
							}
							notifyMap("~p~BeachFire attached to all players..");

						}
					}
				}
				if (GUI::Option("Trap All In Cage")) {
					for (int i = 0; i <= 32; i++)
					{
						WAIT(0);
						if (i == PLAYER::PLAYER_ID())continue;
						int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
						Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(Handle, 0);
						Hash oball = GAMEPLAY::GET_HASH_KEY("prop_gold_cont_01");
						STREAMING::REQUEST_MODEL(oball);
						while (!STREAMING::HAS_MODEL_LOADED(oball))
							WAIT(0);
						//	int orangeball = CREATE_OBJECT(oball, pCoords.x, pCoords.y, pCoords.z, true, 1, 0);
						//	ATTACH_ENTITY_TO_ENTITY(orangeball, Handle, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 2, 1);
						AI::CLEAR_PED_TASKS_IMMEDIATELY(Handle);
						NETWORK::OBJ_TO_NET(OBJECT::CREATE_OBJECT_NO_OFFSET(oball, pCoords.x, pCoords.y, pCoords.z, 1, 0, 0));
						{
							if (i == 32)
							{
								break;
							}

						}
					}
				}
				if (GUI::Option("Attach Toilet to All")) {
					for (int i = 0; i <= 32; i++)
					{
						WAIT(0);
						if (i == PLAYER::PLAYER_ID())continue;
						int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
						Hash oball = GAMEPLAY::GET_HASH_KEY("prop_ld_toilet_01");
						STREAMING::REQUEST_MODEL(oball);
						while (!STREAMING::HAS_MODEL_LOADED(oball))
							WAIT(0);
						int orangeball = OBJECT::CREATE_OBJECT(oball, 0, 0, 0, true, 1, 0);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(orangeball, Handle, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 2, 1);
						{
							if (i == 32)
							{
								break;
							}

						}
					}
				}
				if (GUI::Option("Explode Bitches")) {
					for (int i = 0; i < 33; i++)
					{
						if (PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i) == PLAYER::PLAYER_PED_ID()) continue;
						{
							Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), false);
							FIRE::ADD_EXPLOSION(coords.x, coords.y, coords.z, 29, 1000.f, true, false, 100.f, false);
						}
					}
				}
				if (GUI::Option("Kick All from Vehicle")) {
					for (int i = 0; i < 32; i++)
					{
						if (i != PLAYER::PLAYER_ID())
						{
							RequestControlOfEnt(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
							AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
							AI::CLEAR_PED_TASKS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
							AI::CLEAR_PED_SECONDARY_TASK(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
						}
					}
				}
			}
		}
		break;

		case lobby_weather:
		{
			GUI::Title("");
			GUI::Subtitle("Change Lobby Weather");
			int weatherType = 1;
			if (!NETWORK::NETWORK_IS_IN_SESSION() && !NETWORK::NETWORK_IS_PLAYER_CONNECTED(PLAYER::PLAYER_PED_ID())) {
				GUI::Option("You need to be online to use this.");
			}
			else {
				if (GUI::Option("Extra Sunny")) {
					weatherType = 0;
					Hooking::set_lobby_weather(1, weatherType, 76, 0);
				}
				if (GUI::Option("Clear")) {
					weatherType = 1;
					Hooking::set_lobby_weather(1, weatherType, 76, 0);
				}
				if (GUI::Option("Clouds")) {
					weatherType = 2;
					Hooking::set_lobby_weather(1, weatherType, 76, 0);
				}
				if (GUI::Option("Smog")) {
					weatherType = 3;
					Hooking::set_lobby_weather(1, weatherType, 76, 0);
				}
				if (GUI::Option("Foggy")) {
					weatherType = 4;
					Hooking::set_lobby_weather(1, weatherType, 76, 0);
				}
				if (GUI::Option("Overcast")) {
					weatherType = 5;
					Hooking::set_lobby_weather(1, weatherType, 76, 0);
				}
				if (GUI::Option("Rain")) {
					weatherType = 6;
					Hooking::set_lobby_weather(1, weatherType, 76, 0);
				}
				if (GUI::Option("Thunder")) {
					weatherType = 7;
					Hooking::set_lobby_weather(1, weatherType, 76, 0);
				}
				if (GUI::Option("Light Rain")) {
					weatherType = 8;
					Hooking::set_lobby_weather(1, weatherType, 76, 0);
				}
				if (GUI::Option("Smoggy Light Rain")) {
					weatherType = 9;
					Hooking::set_lobby_weather(1, weatherType, 76, 0);
				}
				if (GUI::Option("Very Light Snow")) {
					weatherType = 10;
					Hooking::set_lobby_weather(1, weatherType, 76, 0);
				}
				if (GUI::Option("Windy Light Snow")) {
					weatherType = 11;
					Hooking::set_lobby_weather(1, weatherType, 76, 0);
				}
				if (GUI::Option("Light Snow")) {
					weatherType = 12;
					Hooking::set_lobby_weather(1, weatherType, 76, 0);
				}
				if (GUI::Option("Christmas")) {
					weatherType = 13;
					Hooking::set_lobby_weather(1, weatherType, 76, 0);
				}
				if (GUI::Option("Halloween")) {
					weatherType = 14;
					Hooking::set_lobby_weather(1, weatherType, 76, 0);
				}
				if (GUI::Option("Blackout")) {
					weatherType = 15;
					Hooking::set_lobby_weather(1, weatherType, 76, 0);
				}
			}
		}
		break;

		case teleport_all_apartments:
		{
			GUI::Title("");
			GUI::Subtitle("Teleport All to Apartments");
			if (GUI::Option("Eclipse Towers")) {
				Features::RemoteTeleportAll(1);
			}
			if (GUI::Option("Alta Street")) {
				Features::RemoteTeleportAll(5);
			}
			if (GUI::Option("Del Perro Heights")) {
				Features::RemoteTeleportAll(7);
			}
			if (GUI::Option("Power Street")) {
				Features::RemoteTeleportAll(8);
			}
			if (GUI::Option("Spanish Avenue")) {
				Features::RemoteTeleportAll(9);
			}
			if (GUI::Option("Las Lagunas Blvd")) {
				Features::RemoteTeleportAll(10);
			}
			if (GUI::Option("Milton Road")) {
				Features::RemoteTeleportAll(11);
			}
			if (GUI::Option("The Royale")) {
				Features::RemoteTeleportAll(12);
			}
			if (GUI::Option("Milton Drive")) {
				Features::RemoteTeleportAll(13);
			}
			if (GUI::Option("Bay City Avenue")) {
				Features::RemoteTeleportAll(14);
			}
			if (GUI::Option("South Rockford Drive")) {
				Features::RemoteTeleportAll(15);
			}
			if (GUI::Option("Dream Tower")) {
				Features::RemoteTeleportAll(16);
			}
			if (GUI::Option("San Vitas Street")) {
				Features::RemoteTeleportAll(18);
			}
			if (GUI::Option("Vespucci Blvd")) {
				Features::RemoteTeleportAll(20);
			}
			if (GUI::Option("Cougar Avenue")) {
				Features::RemoteTeleportAll(21);
			}
			if (GUI::Option("Prosperity Street")) {
				Features::RemoteTeleportAll(22);
			}
		}
		break;

#pragma endregion

#pragma region Remote Options
#       pragma warning(push)
#       pragma warning ( disable: 4838 4334)
		case remote_options:
		{
			Features::LoadPlayerInfo(Hooking::get_player_name(Features::Online::selectedPlayer), Features::Online::selectedPlayer);
			GUI::Title("Remote Options");
			GUI::Subtitle("Remote Options");
			if (!NETWORK::NETWORK_IS_IN_SESSION() && !NETWORK::NETWORK_IS_PLAYER_CONNECTED(PLAYER::PLAYER_PED_ID())) {
				GUI::Option("You need to be online to use this.");
			}
			else {
				GUI::MenuOption("Teleport to Apartments", troll_apartments);
				GUI::MenuOption("Spam Invites", troll_invites);
				if (Features::menu_version == 2) {
					GUI::Toggle("Off the Radar", Features::RemoteOTRBool[Features::Online::selectedPlayer], [] { Features::RemoteOTR(Features::RemoteOTRBool[Features::Online::selectedPlayer]); }); //VIP
					GUI::Toggle("Never Wanted", Features::isRemoteNeverWanted[Features::Online::selectedPlayer], [] { Features::RemoteNeverWanted(Features::isRemoteNeverWanted[Features::Online::selectedPlayer]); }); //VIP
				}
				GUI::Toggle("Sound Spam", Features::Spam[Features::Online::selectedPlayer], [] { Features::DoSoundSpam(Features::Spam[Features::Online::selectedPlayer]); });
				if (GUI::Option("Non-host Kick [New Session]")) {
					DWORD64 args[4] = { 769347061, Features::Online::selectedPlayer, 0, 0 };
					Hooking::trigger_script_event(1, args, 4, 1 << Features::Online::selectedPlayer);
				}
				if (GUI::Option("CEO Ban")) {
					DWORD64 args[3] = { 360381720, Features::Online::selectedPlayer, 1 };
					Hooking::trigger_script_event(1, args, 3, 1 << Features::Online::selectedPlayer);
				}
				if (GUI::Option("CEO Kick")) {
					DWORD64 args[4] = { -1190833098, Features::Online::selectedPlayer, 0, 0 };
					Hooking::trigger_script_event(1, args, 4, 1 << Features::Online::selectedPlayer);
				}
				if (GUI::Option("CEO Kick with Notification")) {
					DWORD64 args[4] = { -1190833098, Features::Online::selectedPlayer, 1, 5 };
					Hooking::trigger_script_event(1, args, 4, 1 << Features::Online::selectedPlayer);
				}
				if (GUI::Option("CEO Ban with Notification")) {
					DWORD64 args[4] = { 360381720, Features::Online::selectedPlayer, 1, 5 };
					Hooking::trigger_script_event(1, args, 4, 1 << Features::Online::selectedPlayer);
				}
				if (GUI::Option("Infinite Loading Screen")) {
					DWORD64 args[9] = { 1000837481, Features::Online::selectedPlayer, 1, -1, 1, 0, 0, 0, 0 };
					Hooking::trigger_script_event(1, args, 9, 1 << Features::Online::selectedPlayer);
				}
				if (Features::menu_version == 2) {
					if (GUI::Option("Send 9K Bounty")) {
						int handle1 = globalHandle(1643357).At(9).As<int>();
						int handle2 = globalHandle(1643357).At(10).As<int>();
						DWORD64 args[22] = { -679747935, Features::Online::selectedPlayer, 0, 1, 9000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, handle1, handle2 };
						Hooking::trigger_script_event(1, args, 22, 1 << Features::Online::selectedPlayer);
					}
					if (GUI::Option("Send Insurance Message")) {
						DWORD64 args[3] = { 380155193, Features::Online::selectedPlayer, 1584303804 };
						Hooking::trigger_script_event(1, args, 3, 1 << Features::Online::selectedPlayer);
					}
					if (GUI::Option("Send Removed Money Message")) {
						DWORD64 args[14] = { 713068249, Features::Online::selectedPlayer, 2110027654, 15000000 };
						Hooking::trigger_script_event(1, args, 14, 1 << Features::Online::selectedPlayer);
					}
				}	
				if (GUI::Option("Send Spectating Message")) {
					DWORD64 args[3] = { 713068249, Features::Online::selectedPlayer, 1583919327 };
					Hooking::trigger_script_event(1, args, 3, 1 << Features::Online::selectedPlayer);
				}
				if (GUI::Option("Send to Job")) {
					DWORD64 args[4] = { -15432926, Features::Online::selectedPlayer, 0, 0 };
					Hooking::trigger_script_event(1, args, 4, 1 << Features::Online::selectedPlayer);
				}
				if (Features::menu_version == 2) {
					if (GUI::Option("Send Transaction Error")) { //VIP
						auto var0 = globalHandle(1625435 + 1 + Features::Online::selectedPlayer * 560 + 491).As<std::uint64_t>();
						auto var1 = globalHandle(1643357 + 9).As<std::uint64_t>();
						uint64_t args[8] = { -1920290846, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), 10000, 0, 0, var0, var1, var1 };
						Hooking::trigger_script_event(1, args, 8, 1 << Features::Online::selectedPlayer);
					}
					if (GUI::Option("Show Banner")) { //VIP
						DWORD64 args[14] = { 713068249, Features::Online::selectedPlayer, 1009196241 };
						Hooking::trigger_script_event(1, args, 14, 1 << Features::Online::selectedPlayer);
					}
				}
			}
		}
		break;
#       pragma warning ( pop )

		case troll_apartments:
		{
			Features::LoadPlayerInfo(Hooking::get_player_name(Features::Online::selectedPlayer), Features::Online::selectedPlayer);
			GUI::Title("");
			GUI::Subtitle("Teleport to Apartments");
			if (GUI::Option("Prosperity Street")) {
				Features::RemoteTeleport(22);
			}
			if (GUI::Option("Eclipse Towers")) {
				Features::RemoteTeleport(1);
			}
			if (GUI::Option("Bay City Avenue")) {
				Features::RemoteTeleport(14);
			}
			if (GUI::Option("South Rockford Drive")) {
				Features::RemoteTeleport(15);
			}
			if (GUI::Option("Dream Tower")) {
				Features::RemoteTeleport(16);
			}
			if (GUI::Option("San Vitas Street")) {
				Features::RemoteTeleport(18);
			}
			if (GUI::Option("Alta Street")) {
				Features::RemoteTeleport(5);
			}
			if (GUI::Option("Del Perro Heights")) {
				Features::RemoteTeleport(7);
			}
			if (GUI::Option("Power Street")) {
				Features::RemoteTeleport(8);
			}
			if (GUI::Option("Vespucci Blvd")) {
				Features::RemoteTeleport(20);
			}
			if (GUI::Option("Cougar Avenue")) {
				Features::RemoteTeleport(21);
			}
			if (GUI::Option("Spanish Avenue")) {
				Features::RemoteTeleport(9);
			}
			if (GUI::Option("Milton Road")) {
				Features::RemoteTeleport(11);
			}
			if (GUI::Option("Las Lagunas Blvd")) {
				Features::RemoteTeleport(10);
			}
			if (GUI::Option("The Royale")) {
				Features::RemoteTeleport(12);
			}
			if (GUI::Option("Milton Drive")) {
				Features::RemoteTeleport(13);
			}
		}
		break;

		case troll_invites:
		{
			Features::LoadPlayerInfo(Hooking::get_player_name(Features::Online::selectedPlayer), Features::Online::selectedPlayer);
			GUI::Title("");
			GUI::Subtitle("Send Invites");
			if (GUI::Option("Apartment")) {
				Features::sendInvite(0);
			}
			if (GUI::Option("Yacht")) {
				Features::sendInvite(1);
			}
			if (GUI::Option("Office")) {
				Features::sendInvite(2);
			}
			if (GUI::Option("Clubhouse")) {
				Features::sendInvite(3);
			}
			if (GUI::Option("Office Garage")) {
				Features::sendInvite(6);
			}
			if (GUI::Option("Custom Auto Shop")) {
				Features::sendInvite(7);
			}
		}
		break;

#pragma endregion

#pragma region Attach Options
		case attachoptions:
		{
			GUI::Title("Attach Options");
			GUI::Subtitle("Attach Options");
			if (!NETWORK::NETWORK_IS_IN_SESSION() && !NETWORK::NETWORK_IS_PLAYER_CONNECTED(PLAYER::PLAYER_PED_ID())) {
				GUI::Option("You need to be online to use this.");
			}
			else {
				if (GUI::Option("Delete All Objects")) {
					for (int i = 0; i < 5; i++) {
						Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), 1);
						GAMEPLAY::CLEAR_AREA_OF_PEDS(coords.x, coords.y, coords.z, 2, 0);
						GAMEPLAY::CLEAR_AREA_OF_OBJECTS(coords.x, coords.y, coords.z, 2, 0);
						GAMEPLAY::CLEAR_AREA_OF_VEHICLES(coords.x, coords.y, coords.z, 2, 0, 0, 0, 0, 0);
						for (int i = 0; i < 136; i++) {
							Object obj = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(coords.x, coords.y, coords.z, 4.0, GAMEPLAY::GET_HASH_KEY(Hashes::objects[i]), 0, 0, 1);

							if (ENTITY::DOES_ENTITY_EXIST(obj) && ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(obj, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer))) {
								RequestControlOfEnt(obj);
								int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(obj);
								NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, 1);
								Features::RequestControlOfid(netID);
								ENTITY::DETACH_ENTITY(obj, 1, 1);
								if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(obj)) {
									ENTITY::SET_ENTITY_AS_MISSION_ENTITY(obj, 1, 1);
									ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&obj);
									ENTITY::DELETE_ENTITY(&obj);
								}
							}
						}
					}
				}
				if (GUI::Option("Plate")) { Features::attachobjects2("p_oil_slick_01"); }
				if (GUI::Option("EMP")) { Features::attachobjects2("hei_prop_heist_emp"); }
				if (GUI::Option("Orange Ball")) { Features::attachobjects2("prop_juicestand"); }
				if (GUI::Option("Weed")) { Features::attachobjects2("prop_weed_01"); }
				if (GUI::Option("Safe")) { Features::attachobjects2("p_v_43_safe_s"); }
				if (GUI::Option("Ufo")) { Features::attachobjects2("p_spinning_anus_s"); }
				if (GUI::Option("Toilet")) { Features::attachobjects2("prop_ld_toilet_01"); }
				if (GUI::Option("Christmas Tree")) { Features::attachobjects2("prop_xmas_tree_int"); }
				if (GUI::Option("Windmill")) { Features::attachobjects2("prop_windmill_01"); }
				if (GUI::Option("Radar")) { Features::attachobjects2("prop_air_bigradar"); }
				if (GUI::Option("Alien Egg")) { Features::attachobjects2("prop_alien_egg_01"); }
				if (GUI::Option("Beggers Sign")) { Features::attachobjects2("prop_beggers_sign_01"); }
				if (GUI::Option("Tramp Sign")) { Features::attachobjects2("prop_beggers_sign_02"); }
				if (GUI::Option("Egg Clock")) { Features::attachobjects2("prop_egg_clock_01"); }
				if (GUI::Option("Guitar")) { Features::attachobjects2("prop_acc_guitar_01_d1"); }
				if (GUI::Option("Duffel")) { Features::attachobjects2("prop_cs_duffel_01b"); }
				if (GUI::Option("Vending Dispenser")) { Features::attachobjects2("prop_juice_dispenser"); }
				if (GUI::Option("Boxing")) { Features::attachobjects2("prop_boxing_glove_01"); }
				if (GUI::Option("Dingy")) { Features::attachobjects2("prop_byard_dingy"); }
				if (GUI::Option("Dildo")) { Features::attachobjects2("prop_cs_dildo_01"); }
				if (GUI::Option("Dumpster")) { Features::attachobjects2("prop_cs_dumpster_01a"); }
				if (GUI::Option("DJ")) { Features::attachobjects2("prop_dj_deck_02"); }
				if (GUI::Option("Plane")) { Features::attachobjects2("prop_dummy_plane"); }
				if (GUI::Option("Ramp")) { Features::attachobjects2("PROP_MP_RAMP_03"); }
				if (GUI::Option("Ramp2")) { Features::attachobjects2("PROP_MP_RAMP_02"); }
				if (GUI::Option("Ramp3")) { Features::attachobjects2("PROP_MP_RAMP_01"); }
				if (GUI::Option("Skip")) { Features::attachobjects2("PROP_SKIP_08A"); }
				if (GUI::Option("Number 1")) { Features::attachobjects2("PROP_MP_NUM_1"); }
				if (GUI::Option("Number 2")) { Features::attachobjects2("PROP_MP_NUM_2"); }
				if (GUI::Option("Number 3")) { Features::attachobjects2("PROP_MP_NUM_3"); }
				if (GUI::Option("Number 4")) { Features::attachobjects2("PROP_MP_NUM_4"); }
				if (GUI::Option("Number 5")) { Features::attachobjects2("PROP_MP_NUM_5"); }
				if (GUI::Option("Number 6")) { Features::attachobjects2("PROP_MP_NUM_6"); }
				if (GUI::Option("Number 7")) { Features::attachobjects2("PROP_MP_NUM_7"); }
				if (GUI::Option("Number 8")) { Features::attachobjects2("PROP_MP_NUM_8"); }
				if (GUI::Option("Number 9")) { Features::attachobjects2("PROP_MP_NUM_9"); }
				if (GUI::Option("Beer Neon")) { Features::attachobjects2("prop_beer_neon_01"); }
				if (GUI::Option("Dummy Plane")) { Features::attachobjects2("prop_dummy_plane"); }
				if (GUI::Option("Cash Pile")) { Features::attachobjects2("prop_anim_cash_pile_02"); }
				if (GUI::Option("Asteroid")) { Features::attachobjects2("prop_asteroid_01"); }
				if (GUI::Option("Weed Palet")) { Features::attachobjects2("prop_weed_pallet"); }
				if (GUI::Option("Ferris Wheel")) { Features::attachobjects2("prop_Ld_ferris_wheel"); }
				if (GUI::Option("Donut")) { Features::attachobjects2("prop_amb_donut"); }
				if (GUI::Option("Basejump")) { Features::attachobjects2("prop_basejump_target_01"); }
				if (GUI::Option("Handbag")) { Features::attachobjects2("prop_amb_handbag_01"); }
				if (GUI::Option("Cargo")) { Features::attachobjects2("prop_air_cargo_01a"); }
				if (GUI::Option("Stunt Ramp BIG")) { Features::attachobjects2("stt_prop_ramp_multi_loop_rb"); }
				if (GUI::Option("Crashed Heli")) { Features::attachobjects2("prop_crashed_heli"); }
				if (GUI::Option("Crashed Heli 2")) { Features::attachobjects2("prop_crashed_heli_s"); }
				if (GUI::Option("Train")) { Features::attachobjects2("prop_rail_boxcar3"); }
				if (GUI::Option("Roller")) { Features::attachobjects2("prop_roller_car_02"); }
				if (GUI::Option("Para")) { Features::attachobjects2("p_cargo_chute_s"); }
			}
		}
		break;
#pragma endregion

#pragma region Name Changer

		case name_changer:
		{
			GUI::Title("");
			GUI::Subtitle("Name Changer");
			for (auto color : Hashes::COLOR_CODES) {
				if (GUI::Option(color.name)) {
					Features::NameChanger(color.value);
				}
			}
		}
		break;

#pragma endregion

#pragma region Online PTFX
		case PTFXO:
		{
			GUI::Title("Online Effects");
			GUI::Subtitle("Online Effects");
			if (!NETWORK::NETWORK_IS_IN_SESSION() && !NETWORK::NETWORK_IS_PLAYER_CONNECTED(PLAYER::PLAYER_PED_ID())) {
				GUI::Option("You need to be online to use this.");
			}
			else {
				GUI::Toggle("Looped", Features::PTLoopedO[Features::Online::selectedPlayer]);
				if (GUI::Option("Clown Appears"))Features::PTFXCALLO("scr_rcbarry2", "scr_rcbarry2", "scr_clown_appears", Features::Online::selectedPlayer);
				if (GUI::Option("Firework 1"))Features::PTFXCALLO("scr_indep_fireworks", "scr_indep_fireworks", "scr_indep_firework_trailburst", Features::Online::selectedPlayer);
				if (GUI::Option("Firework 2"))Features::PTFXCALLO("proj_xmas_firework", "proj_xmas_firework", "scr_firework_xmas_burst_rgw", Features::Online::selectedPlayer);
				if (GUI::Option("Firework 3"))Features::PTFXCALLO("proj_xmas_firework", "proj_xmas_firework", "scr_firework_xmas_spiral_burst_rgw", Features::Online::selectedPlayer);
				if (GUI::Option("Banknotes"))Features::PTFXCALLO("scr_ornate_heist", "scr_ornate_heist", "scr_heist_ornate_banknotes", Features::Online::selectedPlayer);
				if (GUI::Option("Truck Crash"))Features::PTFXCALLO("scr_fbi4", "scr_fbi4", "scr_fbi4_trucks_crash", Features::Online::selectedPlayer);
				if (GUI::Option("Ped Sliced"))Features::PTFXCALLO("scr_michael2", "scr_michael2", "scr_abattoir_ped_sliced", Features::Online::selectedPlayer);
				if (GUI::Option("Camera"))Features::PTFXCALLO("scr_rcpaparazzo1", "scr_rcpaparazzo1", "scr_rcpap1_camera", Features::Online::selectedPlayer);
				if (GUI::Option("Alien 1"))Features::PTFXCALLO("scr_rcbarry1", "scr_rcbarry1", "scr_alien_disintegrate", Features::Online::selectedPlayer);
				if (GUI::Option("Alien 2"))Features::PTFXCALLO("scr_rcbarry1", "scr_rcbarry1", "scr_alien_teleport", Features::Online::selectedPlayer);
				if (GUI::Option("Electric Box"))Features::PTFXCALLO("scr_agencyheistb", "scr_agencyheistb", "scr_agency3b_elec_box", Features::Online::selectedPlayer);
				if (GUI::Option("Water Splash"))Features::PTFXCALLO("scr_fbi5a", "scr_fbi5a", "scr_fbi5_ped_water_splash", Features::Online::selectedPlayer);
				if (GUI::Option("Bubbles"))Features::PTFXCALLO("scr_fbi5a", "scr_fbi5a", "water_splash_ped_bubbles", Features::Online::selectedPlayer);
				if (GUI::Option("Blood Entry"))Features::PTFXCALLO("scr_finalec2", "scr_finalec2", "scr_finale2_blood_entry", Features::Online::selectedPlayer);
				if (GUI::Option("Sniper Impact"))Features::PTFXCALLO("scr_martin1", "scr_martin1", "scr_sol1_sniper_impact", Features::Online::selectedPlayer);
				if (GUI::Option("Dirt Throw"))Features::PTFXCALLO("core_snow", "core_snow", "cs_mich1_spade_dirt_throw", Features::Online::selectedPlayer);
				if (GUI::Option("Blood Stab"))Features::PTFXCALLO("scr_michael2", "scr_michael2", "scr_mich2_blood_stab", Features::Online::selectedPlayer);
				if (GUI::Option("Meth Smoke"))Features::PTFXCALLO("scr_familyscenem", "scr_familyscenem", "scr_meth_pipe_smoke", Features::Online::selectedPlayer);
				if (GUI::Option("Burial Dirt"))Features::PTFXCALLO("scr_reburials", "scr_reburials", "scr_burial_dirt", Features::Online::selectedPlayer);
			}
		}
		break;
#pragma endregion

#pragma region Teleport Options
		case tpother:
		{
			GUI::Title("Teleport Options");
			GUI::Subtitle("Teleport Options");
			GUI::Option("Teleport To Player", [] {Features::Online::TeleportToPlayer(Features::Online::selectedPlayer); });
			if (GUI::Option("Teleport Into Car")) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), false);
				for (int i = -1; i < 16; i++)
				{
					if (VEHICLE::IS_VEHICLE_SEAT_FREE(veh, i))
					{
						PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, i);
					}
				}
			}
		}
		break;
#pragma endregion

#pragma region Vehicle Options
		case vehicle_options:
		{
			GUI::Title("Vehicle Options");
			GUI::Subtitle("Vehicle Options");
			if (GUI::Option("Give Player T20"))
			{
				int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				AI::CLEAR_PED_TASKS_IMMEDIATELY(Handle);
				Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(Handle, 0);
				Vector3 Ocoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Handle, 0.0, 5.0, 0.0);
				Vehicle zentorno = Features::SpawnVehicle("t20", Ocoords, 0, 0.0f);
				ENTITY::SET_ENTITY_INVINCIBLE(zentorno, 0);
			}
			if (GUI::Option("Give Player Monster Truck"))
			{
				int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				AI::CLEAR_PED_TASKS_IMMEDIATELY(Handle);
				Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(Handle, 0);
				Vector3 Ocoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Handle, 0.0, 5.0, 0.0);
				Vehicle zentorno = Features::SpawnVehicle("MONSTER", Ocoords, 0, 0.0f);
				ENTITY::SET_ENTITY_INVINCIBLE(zentorno, 0);
			}
			if (GUI::Option("Give Player Rhino Tank"))
			{
				int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				AI::CLEAR_PED_TASKS_IMMEDIATELY(Handle);
				Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(Handle, 0);
				Vector3 Ocoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Handle, 0.0, 5.0, 0.0);
				Vehicle zentorno = Features::SpawnVehicle("RHINO", Ocoords, 0, 0.0f);
				ENTITY::SET_ENTITY_INVINCIBLE(zentorno, 0);
			}
			if (GUI::Option("Give Player Space Docker"))
			{
				int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				AI::CLEAR_PED_TASKS_IMMEDIATELY(Handle);
				Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(Handle, 0);
				Vector3 Ocoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Handle, 0.0, 5.0, 0.0);
				Vehicle zentorno = Features::SpawnVehicle("DUNE2", Ocoords, 0, 0.0f);
				ENTITY::SET_ENTITY_INVINCIBLE(zentorno, 0);
			}
		}
		break;
#pragma endregion

#pragma region Griefing Options

		case troll_options:
		{
			GUI::Title("Griefing Options");
			GUI::Subtitle("Griefing Options");
			GUI::MenuOption("Attach Objects", attachoptions);
			if (Features::menu_version == 2) {
				GUI::MenuOption("Blame Player Selective", blame_single); //VIP
			}
			GUI::MenuOption("Effects", PTFXO);
			GUI::MenuOption("Ram Options", troll_ram);
			GUI::MenuOption("Remote Options", remote_options);
			GUI::MenuOption("Spawn Assassins", spawn_assassins);
			GUI::MenuOption("Vehicle Options", troll_vehicle);
			GUI::Toggle("Air Strike", Features::AirStrike, [] { Features::AirStrike1(Features::AirStrike); });
			GUI::Toggle("Fire Loop", Features::playerfireloop[Features::Online::selectedPlayer], [] { Features::FireLoop(Features::playerfireloop[Features::Online::selectedPlayer]); });
			GUI::Toggle("Freeze", Features::freezed[Features::Online::selectedPlayer], [] { Features::Freezer(Features::freezed[Features::Online::selectedPlayer]); });
			GUI::Toggle("Shake Cam", Features::camshaker[Features::Online::selectedPlayer], [] { Features::shakecam(Features::camshaker[Features::Online::selectedPlayer]); });
			GUI::Toggle("Water Loop", Features::playerwaterloop[Features::Online::selectedPlayer], [] { Features::WaterLoop(Features::playerwaterloop[Features::Online::selectedPlayer]); });
			GUI::Toggle("Explosion Loop", Features::exploder[Features::Online::selectedPlayer], [] { Features::explodeloop(Features::exploder[Features::Online::selectedPlayer]); });
			if (Features::menu_version == 2) {
				if (GUI::Option("Blame Player")) { //VIP
					Features::BlamePlayer();
				}
				if (GUI::Option("Force Suicide")) { //VIP
					Features::forceSuicide();
				}
			}
			if (GUI::Option("Explode Player")) {
				Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
				FIRE::ADD_EXPLOSION(pos.x, pos.y, pos.z, 29, 0.5f, true, false, 5.0f, false);
			}
			if (GUI::Option("Host Kick")) {
				if (NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0) == PLAYER::PLAYER_PED_ID()) {
					NETWORK::NETWORK_SESSION_KICK_PLAYER(Features::Online::selectedPlayer);
				}
			}
			if (GUI::Option("Kill Player")) {
				Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), false);
				FIRE::ADD_EXPLOSION(coords.x, coords.y, coords.z, 4, 1000.f, true, false, 1000.f, false);
			}
			if (GUI::Option("Attach to Player")) {
				if (playerId != PLAYER::PLAYER_PED_ID())
				{
					ENTITY::ATTACH_ENTITY_TO_ENTITY(PLAYER::PLAYER_PED_ID(), PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), 0, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, true, true, false, true, 2, true);
				}
			}
			if (GUI::Option("Detach to Player")) {
				ENTITY::DETACH_ENTITY(PLAYER::PLAYER_PED_ID(), true, true);
			}
			if (GUI::Option("Cage Player")) {
				Features::trapcage(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer));
			}
			if (GUI::Option("Clone Player"))
			{
				PED::CLONE_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), 1, 1, 1);
			}
			if (GUI::Option("Copy Player's Outfit")) CopyOutfit(Features::Online::selectedPlayer);
			if (GUI::Option("Ram Player")) {
				float offset;
				Hash vehmodel = GAMEPLAY::GET_HASH_KEY("SANDKING");
				STREAMING::REQUEST_MODEL(vehmodel);

				while (!STREAMING::HAS_MODEL_LOADED(vehmodel)) WAIT(0);
				Vector3 pCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), 0.0, -10.0, 0.0);

				if (STREAMING::IS_MODEL_IN_CDIMAGE(vehmodel) && STREAMING::IS_MODEL_A_VEHICLE(vehmodel))
				{
					Vector3 dim1, dim2;
					GAMEPLAY::GET_MODEL_DIMENSIONS(vehmodel, &dim1, &dim2);

					offset = dim2.y * 1.6f;

					Vector3 dir = ENTITY::GET_ENTITY_FORWARD_VECTOR(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer));
					float rot = (ENTITY::GET_ENTITY_ROTATION(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), 0)).z;

					Vehicle veh = VEHICLE::CREATE_VEHICLE(vehmodel, pCoords.x + (dir.x * offset), pCoords.y + (dir.y * offset), pCoords.z, rot, 1, 1);
					Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);

					VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
					ENTITY::SET_ENTITY_VISIBLE(veh, true, 0);
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 700.0);
				}

			}
			if (GUI::Option("Valkyrie Cannon")) {
				Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
				FIRE::ADD_EXPLOSION(pos.x, pos.y, pos.z - 1, 38, 0.5f, true, false, 0.0f, false);
			}
			if (GUI::Option("Join Player's Crew")) JoinCrew(Features::Online::selectedPlayer);
		}
		break;

		case blame_single:
		{
			Features::LoadPlayerInfo(PLAYER::GET_PLAYER_NAME(Features::Online::selectedPlayer), Features::Online::selectedPlayer);
			GUI::Title("");
			GUI::Subtitle("Blame Player Single");
			for (int i = 0; i < 32; ++i) {
				if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))) {
					if (i != Features::Online::selectedPlayer && i != PLAYER::PLAYER_PED_ID()) {
						if (GUI::Option(Hooking::get_player_name(i))) {
							Features::blamesingle_player = i;
							Features::BlamePlayerSelective();
						}
					}
				}
			}
		}
		break;
		
#pragma endregion

#pragma region Ram w/ Vehicles
		case troll_ram:
		{
			Features::LoadPlayerInfo(Hooking::get_player_name(Features::Online::selectedPlayer), Features::Online::selectedPlayer);
			GUI::Title("");
			GUI::Subtitle("Ram w/ Vehicles");
			if (GUI::Option("Ram with Sandking")) {

				float offset;
				Hash vehmodel = GAMEPLAY::GET_HASH_KEY("SANDKING");
				STREAMING::REQUEST_MODEL(vehmodel);

				while (!STREAMING::HAS_MODEL_LOADED(vehmodel)) WAIT(0);
				Vector3 pCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), 0.0, -10.0, 0.0);

				if (STREAMING::IS_MODEL_IN_CDIMAGE(vehmodel) && STREAMING::IS_MODEL_A_VEHICLE(vehmodel))
				{
					Vector3 dim1, dim2;
					GAMEPLAY::GET_MODEL_DIMENSIONS(vehmodel, &dim1, &dim2);

					offset = dim2.y * 1.6f;

					Vector3 dir = ENTITY::GET_ENTITY_FORWARD_VECTOR(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer));
					float rot = (ENTITY::GET_ENTITY_ROTATION(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), 0)).z;

					Vehicle veh = VEHICLE::CREATE_VEHICLE(vehmodel, pCoords.x + (dir.x * offset), pCoords.y + (dir.y * offset), pCoords.z, rot, 1, 1);

					VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
					ENTITY::SET_ENTITY_VISIBLE(veh, true, 0);
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 700.0);
				}

			}
			if (GUI::Option("Ram with Bus")) {

				float offset;
				Hash vehmodel = GAMEPLAY::GET_HASH_KEY("BUS");
				STREAMING::REQUEST_MODEL(vehmodel);

				while (!STREAMING::HAS_MODEL_LOADED(vehmodel)) WAIT(0);
				Vector3 pCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), 0.0, -10.0, 0.0);

				if (STREAMING::IS_MODEL_IN_CDIMAGE(vehmodel) && STREAMING::IS_MODEL_A_VEHICLE(vehmodel))
				{
					Vector3 dim1, dim2;
					GAMEPLAY::GET_MODEL_DIMENSIONS(vehmodel, &dim1, &dim2);

					offset = dim2.y * 1.6f;

					Vector3 dir = ENTITY::GET_ENTITY_FORWARD_VECTOR(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer));
					float rot = (ENTITY::GET_ENTITY_ROTATION(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), 0)).z;

					Vehicle veh = VEHICLE::CREATE_VEHICLE(vehmodel, pCoords.x + (dir.x * offset), pCoords.y + (dir.y * offset), pCoords.z, rot, 1, 1);

					VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
					ENTITY::SET_ENTITY_VISIBLE(veh, true, 0);
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 700.0);
				}
			}
			if (GUI::Option("Ram with Freight")) {

				float offset;
				Hash vehmodel = GAMEPLAY::GET_HASH_KEY("FREIGHT");
				STREAMING::REQUEST_MODEL(vehmodel);

				while (!STREAMING::HAS_MODEL_LOADED(vehmodel)) WAIT(0);
				Vector3 pCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), 0.0, -10.0, 0.0);

				if (STREAMING::IS_MODEL_IN_CDIMAGE(vehmodel) && STREAMING::IS_MODEL_A_VEHICLE(vehmodel))
				{
					Vector3 dim1, dim2;
					GAMEPLAY::GET_MODEL_DIMENSIONS(vehmodel, &dim1, &dim2);

					offset = dim2.y * 1.6f;

					Vector3 dir = ENTITY::GET_ENTITY_FORWARD_VECTOR(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer));
					float rot = (ENTITY::GET_ENTITY_ROTATION(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), 0)).z;

					Vehicle veh = VEHICLE::CREATE_VEHICLE(vehmodel, pCoords.x + (dir.x * offset), pCoords.y + (dir.y * offset), pCoords.z, rot, 1, 1);

					VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
					ENTITY::SET_ENTITY_VISIBLE(veh, true, 0);
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 700.0);
				}
			}
			if (GUI::Option("Ram with Freight Car")) {

				float offset;
				Hash vehmodel = GAMEPLAY::GET_HASH_KEY("FREIGHTCAR");
				STREAMING::REQUEST_MODEL(vehmodel);

				while (!STREAMING::HAS_MODEL_LOADED(vehmodel)) WAIT(0);
				Vector3 pCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), 0.0, -10.0, 0.0);

				if (STREAMING::IS_MODEL_IN_CDIMAGE(vehmodel) && STREAMING::IS_MODEL_A_VEHICLE(vehmodel))
				{
					Vector3 dim1, dim2;
					GAMEPLAY::GET_MODEL_DIMENSIONS(vehmodel, &dim1, &dim2);

					offset = dim2.y * 1.6f;

					Vector3 dir = ENTITY::GET_ENTITY_FORWARD_VECTOR(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer));
					float rot = (ENTITY::GET_ENTITY_ROTATION(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), 0)).z;

					Vehicle veh = VEHICLE::CREATE_VEHICLE(vehmodel, pCoords.x + (dir.x * offset), pCoords.y + (dir.y * offset), pCoords.z, rot, 1, 1);

					VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
					ENTITY::SET_ENTITY_VISIBLE(veh, true, 0);
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 700.0);
				}
			}
		}
		break;

#pragma endregion

#pragma region Troll Vehicle
		case troll_vehicle:
		{
			GUI::Title("Vehicle Options");
			GUI::Subtitle("Vehicle Options");
			GUI::Toggle("Fuck Handling", Features::fuckedhandling[Features::Online::selectedPlayer], [] { Features::fuckhandling(Features::fuckedhandling[Features::Online::selectedPlayer]); });
			if (GUI::Option("Slingshot Car")) {
				if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), true)))
				{
					ENTITY::APPLY_FORCE_TO_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), true), 1, 0, 0, 20, 0, 0, 0, 1, false, true, true, true, true);
				}
			}
			if (GUI::Option("Kick him out of Car")) {
				Ped playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				RequestControlOfEnt(playerPed);
				AI::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
				AI::CLEAR_PED_TASKS(playerPed);
				AI::CLEAR_PED_SECONDARY_TASK(playerPed);
			}
			if (GUI::Option("Explode Vehicle")) {
				Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
				FIRE::ADD_EXPLOSION(pos.x, pos.y, pos.z, 29, 0.5f, true, false, 5.0f, false);
			}
			if (GUI::Option("Launch Vehicle")) {
				Player playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(playerPed, 0);
				{
					RequestControlOfEnt(veh);
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 300.0);
				}
			}
			if (GUI::Option("Push Vehicle")) {
				Player playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(playerPed, 0);
				{
					RequestControlOfEnt(veh);
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 120.0);

				}
			}
			if (GUI::Option("Pop Tires")) {
				Vehicle selectedlPlayerveh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), false);
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), false))
				{
					RequestControlOfEnt(selectedlPlayerveh);
					VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(selectedlPlayerveh, true);
					for (int i = 5; i--;)
						VEHICLE::SET_VEHICLE_TYRE_BURST(selectedlPlayerveh, i, true, 1000.f);
				}
			}
		}
		break;

#pragma endregion

#pragma region Drop Options

		case dropoptions:
		{
			GUI::Title("Drop Options");
			GUI::Subtitle("Drop Options");
			GUI::Toggle("Money Drop [Standard]", Features::savenewdrop21[Features::Online::selectedPlayer]);
			GUI::Toggle("Money Drop [Ground]", Features::CashDropRemotev2[Features::Online::selectedPlayer], [] {Features::CashDropv2(Features::CashDropRemotev2[Features::Online::selectedPlayer]); });
			if (GUI::Option("Drop Armor")) {
				Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
				OBJECT::CREATE_AMBIENT_PICKUP(1274757841, pos.x, pos.y, pos.z + 1.5f, 0, 100000, 1, 0, 1);
			}
			if (GUI::Option("Drop Parachute")) {
				Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
				OBJECT::CREATE_AMBIENT_PICKUP(1735599485, pos.x, pos.y, pos.z + 1.5f, 0, 100000, 1, 0, 1);
			}
			if (GUI::Option("Drop Snack")) {
				Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
				OBJECT::CREATE_AMBIENT_PICKUP(483577702, pos.x, pos.y, pos.z + 1.5f, 0, 100000, 1, 0, 1);
			}
		}
		break;

#pragma endregion

#pragma region Weapon Options

		case weaponss_options:
		{
		GUI::Title("Weapon Options");
		GUI::Subtitle("Weapon Options");
		if (GUI::Option("Give All Weapons")) {
			std::vector<uint> Weapons{
			0x92A27487, 0x958A4A8F, 0xF9E6AA4B, 0x84BD7BFD, 0xA2719263, 0x8BB05FD7, 0x440E4788, 0x4E875F73, 0xF9DCBF2D, 0xD8DF3C3C, 0x99B507EA, 0xDD5DF8D9, 0xDFE37640, 0x678B81B1, 0x19044EE0, 0xCD274149, 0x94117305, 0x3813FC08, // Melee
			0x1B06D571, 0xBFE256D4, 0x5EF9FEC4, 0x22D8FE39, 0x3656C8C1, 0x99AEEB3B, 0xBFD21232, 0x88374054, 0xD205520E, 0x83839C4, 0x47757124, 0xDC4DB296, 0xC1B3C3D1, 0xCB96392F, 0x97EA20B8, // Handguns
			0x13532244, 0x2BE6766B, 0x2BE6766B, 0xEFE7E2DF, 0x0A3D4D34, 0xDB1AA450, 0xBD248B55, // Submachine Guns
			0x1D073A89, 0x555AF99A, 0x7846A318, 0xE284C527, 0x9D61E50F, 0xA89CB99E, 0x3AABBBAA, 0xEF951FBB, 0x12E82D3D, // Shotguns
			0xBFEFFF6D, 0x394F415C, 0x83BF0278, 0xFAD1F1C9, 0xAF113F99, 0xC0A3098D, 0x969C3D67, 0x7F229F94, 0x84D6FAFD, 0x624FE830, // Assault Rifles
			0x9D07F764, 0x7FD62962, 0xDBBD7280, 0x61012683, // Light Machine Guns
			0x05FC3C11, 0x0C472FE2, 0xA914799, 0xC734385A, 0x6A6C02E0, // Sniper Rifles
			0xB1CA77B1, 0xA284510B, 0x4DD2DC56, 0x42BF8A85, 0x7F7497E5, 0x6D544C99, 0x63AB0442, 0x0781FE4A, // Heavy Weapons
			0x93E220BD, 0xA0973D5E, 0x24B17070, 0x2C3731D9, 0xAB564B93, 0x787F0BB, 0xBA45E8B8, 0x23C9F95C, 0xFDBC8A50, 0x497FACC3, // Throwables
			0x34A67B97, 0xFBAB5776, 0x060EC506, // Miscellaneous
			0x476BF155, 0xAF3696A1, 0xB62D1F67, // Arena Wars
			0xBFE256D4, 0x78A97CD0, 0xDBBD7280, 0x394F415C, 0xFAD1F1C9, 0xA914799 // MK2 Weapons
			};

			for (Hash hash : Weapons)
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), hash, 9999, 0);
		}
		if (GUI::Option("Give All MK1 Weapons")) {
			std::vector<uint> Weapons{
			0x99B507EA, 0x678B81B1, 0x4E875F73, 0x958A4A8F, 0x3813FC08, 0x440E4788, 0x84BD7BFD, 0x1B06D571, 0x5EF9FEC4,
			0x22D8FE39, 0x99AEEB3B, 0x13532244, 0x2BE6766B, 0xEFE7E2DF, 0xBFEFFF6D, 0x83BF0278, 0xAF113F99, 0x9D07F764,
			0x7FD62962, 0x1D073A89, 0x7846A318, 0xE284C527, 0x9D61E50F, 0x3656C8C1, 0x05FC3C11, 0x0C472FE2, 0x33058E22,
			0xA284510B, 0x4DD2DC56, 0xB1CA77B1, 0x687652CE, 0x42BF8A85, 0x93E220BD, 0x2C3731D9, 0xFDBC8A50, 0x24B17070,
			0x060EC506, 0x34A67B97, 0xFDBADCED, 0x23C9F95C, 0x497FACC3, 0xF9E6AA4B, 0x61012683, 0xC0A3098D, 0xD205520E,
			0xBFD21232, 0x7F229F94, 0x92A27487, 0x083839C4, 0x7F7497E5, 0xA89CB99E, 0x3AABBBAA, 0xC734385A, 0x787F0BB,
			0x47757124, 0xD04C944D, 0x3813FC08 // MK1
			};

			for (Hash hash : Weapons)
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), hash, 9999, 0);
		}
		if (GUI::Option("Give All MK2 Weapons")) {
			std::vector<uint> Weapons{
			0xBFE256D4, 0x78A97CD0, 0xDBBD7280, 0x394F415C, 0xFAD1F1C9, 0xA914799 // MK2 Weapons
			};

			for (Hash hash : Weapons)
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), hash, 9999, 0);
		}
		if (GUI::Option("Remove All Weapons")) {
			std::vector<uint> Weapons{
			0x92A27487, 0x958A4A8F, 0xF9E6AA4B, 0x84BD7BFD, 0xA2719263, 0x8BB05FD7, 0x440E4788, 0x4E875F73, 0xF9DCBF2D, 0xD8DF3C3C, 0x99B507EA, 0xDD5DF8D9, 0xDFE37640, 0x678B81B1, 0x19044EE0, 0xCD274149, 0x94117305, 0x3813FC08, // Melee
			0x1B06D571, 0xBFE256D4, 0x5EF9FEC4, 0x22D8FE39, 0x3656C8C1, 0x99AEEB3B, 0xBFD21232, 0x88374054, 0xD205520E, 0x83839C4, 0x47757124, 0xDC4DB296, 0xC1B3C3D1, 0xCB96392F, 0x97EA20B8, // Handguns
			0x13532244, 0x2BE6766B, 0x2BE6766B, 0xEFE7E2DF, 0x0A3D4D34, 0xDB1AA450, 0xBD248B55, // Submachine Guns
			0x1D073A89, 0x555AF99A, 0x7846A318, 0xE284C527, 0x9D61E50F, 0xA89CB99E, 0x3AABBBAA, 0xEF951FBB, 0x12E82D3D, // Shotguns
			0xBFEFFF6D, 0x394F415C, 0x83BF0278, 0xFAD1F1C9, 0xAF113F99, 0xC0A3098D, 0x969C3D67, 0x7F229F94, 0x84D6FAFD, 0x624FE830, // Assault Rifles
			0x9D07F764, 0x7FD62962, 0xDBBD7280, 0x61012683, // Light Machine Guns
			0x05FC3C11, 0x0C472FE2, 0xA914799, 0xC734385A, 0x6A6C02E0, // Sniper Rifles
			0xB1CA77B1, 0xA284510B, 0x4DD2DC56, 0x42BF8A85, 0x7F7497E5, 0x6D544C99, 0x63AB0442, 0x0781FE4A, // Heavy Weapons
			0x93E220BD, 0xA0973D5E, 0x24B17070, 0x2C3731D9, 0xAB564B93, 0x787F0BB, 0xBA45E8B8, 0x23C9F95C, 0xFDBC8A50, 0x497FACC3, // Throwables
			0x34A67B97, 0xFBAB5776, 0x060EC506, // Miscellaneous
			0x476BF155, 0xAF3696A1, 0xB62D1F67, // Arena Wars
			0xBFE256D4, 0x78A97CD0, 0xDBBD7280, 0x394F415C, 0xFAD1F1C9, 0xA914799 // MK2 Weapons
			};

			for (Hash hash : Weapons)
			WEAPON::REMOVE_WEAPON_FROM_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), hash);
		}
		if (GUI::Option("Remove All MK2 Weapons")) {
			std::vector<Hash> WeaponHash{
				0xBFE256D4, 0x78A97CD0, 0xDBBD7280, 0x394F415C, 0xFAD1F1C9, 0xA914799
			};

			for (Hash hash : WeaponHash)
				WEAPON::REMOVE_WEAPON_FROM_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), hash);
		}
	}
	break;
#pragma endregion

#pragma region Spawn Assassins
		case spawn_assassins:
		{
			Features::LoadPlayerInfo(Hooking::get_player_name(Features::Online::selectedPlayer), Features::Online::selectedPlayer);
			GUI::Title("");
			GUI::Subtitle("Spawn Assassins");
			int eclone[1000];
			int egcount = 1;
			if (GUI::Option("Spawn Jesus w/ Assault Rifle")) {
				Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
				Hash rifle = GAMEPLAY::GET_HASH_KEY("WEAPON_ASSAULTRIFLE");
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
				Hash pedm = GAMEPLAY::GET_HASH_KEY("u_m_m_jesus_01");
				STREAMING::REQUEST_MODEL(pedm);
				while (!STREAMING::HAS_MODEL_LOADED(pedm))
					WAIT(0);
				eclone[egcount] = PED::CREATE_PED(26, pedm, pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 1, 0, 1, 1);
				ENTITY::SET_ENTITY_INVINCIBLE(eclone[egcount], false);
				PED::SET_PED_COMBAT_ABILITY(eclone[egcount], 100);
				WEAPON::GIVE_WEAPON_TO_PED(eclone[egcount], rifle, rifle, 9999, 9999);
				PED::SET_PED_CAN_SWITCH_WEAPON(eclone[egcount], true);
				AI::TASK_COMBAT_PED(eclone[egcount], selectedplayer, 1, 1);
				PED::SET_PED_ALERTNESS(eclone[egcount], 1000);
				PED::SET_PED_COMBAT_RANGE(eclone[egcount], 1000);
				egcount++;
			}
			if (GUI::Option("Spawn Alien w/ Railgun")) {
				Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
				Hash railgun = GAMEPLAY::GET_HASH_KEY("WEAPON_RAILGUN");
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
				Hash pedm = GAMEPLAY::GET_HASH_KEY("s_m_m_movalien_01");
				STREAMING::REQUEST_MODEL(pedm);
				while (!STREAMING::HAS_MODEL_LOADED(pedm))
					WAIT(0);
				eclone[egcount] = PED::CREATE_PED(26, pedm, pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 1, 0, 1, 1);
				ENTITY::SET_ENTITY_INVINCIBLE(eclone[egcount], false);
				PED::SET_PED_COMBAT_ABILITY(eclone[egcount], 100);
				WEAPON::GIVE_WEAPON_TO_PED(eclone[egcount], railgun, railgun, 9999, 9999);
				PED::SET_PED_CAN_SWITCH_WEAPON(eclone[egcount], true);
				AI::TASK_COMBAT_PED(eclone[egcount], selectedplayer, 1, 1);
				PED::SET_PED_ALERTNESS(eclone[egcount], 1000);
				PED::SET_PED_COMBAT_RANGE(eclone[egcount], 1000);
				egcount++;
			}
			if (GUI::Option("Spawn Marine w/ Combat MG")) {
				Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
				Hash combatmg = GAMEPLAY::GET_HASH_KEY("WEAPON_COMBATMG");
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
				Hash pedm = GAMEPLAY::GET_HASH_KEY("s_m_m_marine_02");
				STREAMING::REQUEST_MODEL(pedm);
				while (!STREAMING::HAS_MODEL_LOADED(pedm))
					WAIT(0);
				eclone[egcount] = PED::CREATE_PED(26, pedm, pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 1, 0, 1, 1);
				ENTITY::SET_ENTITY_INVINCIBLE(eclone[egcount], false);
				PED::SET_PED_COMBAT_ABILITY(eclone[egcount], 100);
				WEAPON::GIVE_WEAPON_TO_PED(eclone[egcount], combatmg, combatmg, 9999, 9999);
				PED::SET_PED_CAN_SWITCH_WEAPON(eclone[egcount], true);
				AI::TASK_COMBAT_PED(eclone[egcount], selectedplayer, 1, 1);
				PED::SET_PED_ALERTNESS(eclone[egcount], 1000);
				PED::SET_PED_COMBAT_RANGE(eclone[egcount], 1000);
				egcount++;
			}
			if (GUI::Option("Spawn Stripper w/ Heavy Sniper")) {
				Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
				Hash heavysniper = GAMEPLAY::GET_HASH_KEY("WEAPON_HEAVYSNIPER");
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
				Hash pedm = GAMEPLAY::GET_HASH_KEY("csb_stripper_01");
				STREAMING::REQUEST_MODEL(pedm);
				while (!STREAMING::HAS_MODEL_LOADED(pedm))
					WAIT(0);
				eclone[egcount] = PED::CREATE_PED(26, pedm, pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 1, 0, 1, 1);
				ENTITY::SET_ENTITY_INVINCIBLE(eclone[egcount], false);
				PED::SET_PED_COMBAT_ABILITY(eclone[egcount], 100);
				WEAPON::GIVE_WEAPON_TO_PED(eclone[egcount], heavysniper, heavysniper, 9999, 9999);
				PED::SET_PED_CAN_SWITCH_WEAPON(eclone[egcount], true);
				AI::TASK_COMBAT_PED(eclone[egcount], selectedplayer, 1, 1);
				PED::SET_PED_ALERTNESS(eclone[egcount], 1000);
				PED::SET_PED_COMBAT_RANGE(eclone[egcount], 1000);
				egcount++;
			}
			if (GUI::Option("Spawn Merry Weather w/ Mini Gun")) {
				Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
				Hash minigun = GAMEPLAY::GET_HASH_KEY("WEAPON_MINIGUN");
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
				Hash pedm = GAMEPLAY::GET_HASH_KEY("csb_mweather");
				STREAMING::REQUEST_MODEL(pedm);
				while (!STREAMING::HAS_MODEL_LOADED(pedm))
					WAIT(0);
				eclone[egcount] = PED::CREATE_PED(26, pedm, pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 1, 0, 1, 1);
				ENTITY::SET_ENTITY_INVINCIBLE(eclone[egcount], false);
				PED::SET_PED_COMBAT_ABILITY(eclone[egcount], 100);
				WEAPON::GIVE_WEAPON_TO_PED(eclone[egcount], minigun, minigun, 9999, 9999);
				PED::SET_PED_CAN_SWITCH_WEAPON(eclone[egcount], true);
				AI::TASK_COMBAT_PED(eclone[egcount], selectedplayer, 1, 1);
				PED::SET_PED_ALERTNESS(eclone[egcount], 1000);
				PED::SET_PED_COMBAT_RANGE(eclone[egcount], 1000);
				egcount++;
			}
			if (GUI::Option("Spawn FIB Agent w/ RPG")) {
				Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
				Hash rpg = GAMEPLAY::GET_HASH_KEY("WEAPON_RPG");
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
				Hash pedm = GAMEPLAY::GET_HASH_KEY("s_m_m_fiboffice_01");
				STREAMING::REQUEST_MODEL(pedm);
				while (!STREAMING::HAS_MODEL_LOADED(pedm))
					WAIT(0);
				eclone[egcount] = PED::CREATE_PED(26, pedm, pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 1, 0, 1, 1);
				ENTITY::SET_ENTITY_INVINCIBLE(eclone[egcount], false);
				PED::SET_PED_COMBAT_ABILITY(eclone[egcount], 100);
				WEAPON::GIVE_WEAPON_TO_PED(eclone[egcount], rpg, rpg, 9999, 9999);
				PED::SET_PED_CAN_SWITCH_WEAPON(eclone[egcount], true);
				AI::TASK_COMBAT_PED(eclone[egcount], selectedplayer, 1, 1);
				PED::SET_PED_ALERTNESS(eclone[egcount], 1000);
				PED::SET_PED_COMBAT_RANGE(eclone[egcount], 1000);
				egcount++;
			}
		}
		break;

#pragma endregion

#pragma region Spawn Body Guards
		case bodyoptions:
		{
			GUI::Title("Spawn Body Guards");
			GUI::Subtitle("Spawn Body Guards");
			Features::LoadPlayerInfo(Hooking::get_player_name(Features::Online::selectedPlayer), Features::Online::selectedPlayer);
			int clone[1000];
			int gcount = 1;
			if (GUI::Option("Spawn Jesus w/ Assault Rifle")) {
				Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
				Hash rifle = GAMEPLAY::GET_HASH_KEY("WEAPON_ASSAULTRIFLE");
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
				Hash pedm = GAMEPLAY::GET_HASH_KEY("u_m_m_jesus_01");
				STREAMING::REQUEST_MODEL(pedm);
				while (!STREAMING::HAS_MODEL_LOADED(pedm))
					WAIT(0);
				int my_group = PLAYER::GET_PLAYER_GROUP(selectedplayer);
				clone[gcount] = PED::CREATE_PED(26, pedm, pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 1, 0, 1, 1);
				PED::SET_PED_AS_GROUP_LEADER(selectedplayer, my_group);
				PED::SET_PED_AS_GROUP_MEMBER(clone[gcount], my_group);
				PED::SET_PED_NEVER_LEAVES_GROUP(clone[gcount], my_group);
				ENTITY::SET_ENTITY_INVINCIBLE(clone[gcount], false);
				PED::SET_PED_COMBAT_ABILITY(clone[gcount], 100);
				WEAPON::GIVE_WEAPON_TO_PED(clone[gcount], rifle, rifle, 9999, 9999);
				PED::SET_PED_CAN_SWITCH_WEAPON(clone[gcount], true);
				PED::SET_GROUP_FORMATION(my_group, 3);
				PED::SET_PED_MAX_HEALTH(clone[gcount], 5000);
				gcount++;
			}
			if (GUI::Option("Spawn Alien w/ Railgun")) {
				Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
				Hash railgun = GAMEPLAY::GET_HASH_KEY("WEAPON_RAILGUN");
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
				Hash pedm = GAMEPLAY::GET_HASH_KEY("s_m_m_movalien_01");
				STREAMING::REQUEST_MODEL(pedm);
				while (!STREAMING::HAS_MODEL_LOADED(pedm))
					WAIT(0);
				int my_group = PLAYER::GET_PLAYER_GROUP(selectedplayer);
				clone[gcount] = PED::CREATE_PED(26, pedm, pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 1, 0, 1, 1);
				PED::SET_PED_AS_GROUP_LEADER(selectedplayer, my_group);
				PED::SET_PED_AS_GROUP_MEMBER(clone[gcount], my_group);
				PED::SET_PED_NEVER_LEAVES_GROUP(clone[gcount], my_group);
				ENTITY::SET_ENTITY_INVINCIBLE(clone[gcount], false);
				PED::SET_PED_COMBAT_ABILITY(clone[gcount], 100);
				WEAPON::GIVE_WEAPON_TO_PED(clone[gcount], railgun, railgun, 9999, 9999);
				PED::SET_PED_CAN_SWITCH_WEAPON(clone[gcount], true);
				PED::SET_GROUP_FORMATION(my_group, 3);
				PED::SET_PED_MAX_HEALTH(clone[gcount], 5000);
				gcount++;
			}
			if (GUI::Option("Spawn Marine w/ Combat MG")) {
				Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
				Hash combatmg = GAMEPLAY::GET_HASH_KEY("WEAPON_COMBATMG");
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
				Hash pedm = GAMEPLAY::GET_HASH_KEY("s_m_m_marine_02");
				STREAMING::REQUEST_MODEL(pedm);
				while (!STREAMING::HAS_MODEL_LOADED(pedm))
					WAIT(0);
				int my_group = PLAYER::GET_PLAYER_GROUP(selectedplayer);
				clone[gcount] = PED::CREATE_PED(26, pedm, pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 1, 0, 1, 1);
				PED::SET_PED_AS_GROUP_LEADER(selectedplayer, my_group);
				PED::SET_PED_AS_GROUP_MEMBER(clone[gcount], my_group);
				PED::SET_PED_NEVER_LEAVES_GROUP(clone[gcount], my_group);
				ENTITY::SET_ENTITY_INVINCIBLE(clone[gcount], false);
				PED::SET_PED_COMBAT_ABILITY(clone[gcount], 100);
				WEAPON::GIVE_WEAPON_TO_PED(clone[gcount], combatmg, combatmg, 9999, 9999);
				PED::SET_PED_CAN_SWITCH_WEAPON(clone[gcount], true);
				PED::SET_GROUP_FORMATION(my_group, 3);
				PED::SET_PED_MAX_HEALTH(clone[gcount], 5000);
				gcount++;
			}
			if (GUI::Option("Spawn Stripper w/ Heavy Sniper")) {
				Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
				Hash heavysniper = GAMEPLAY::GET_HASH_KEY("WEAPON_HEAVYSNIPER");
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
				Hash pedm = GAMEPLAY::GET_HASH_KEY("csb_stripper_01");
				STREAMING::REQUEST_MODEL(pedm);
				while (!STREAMING::HAS_MODEL_LOADED(pedm))
					WAIT(0);
				int my_group = PLAYER::GET_PLAYER_GROUP(selectedplayer);
				clone[gcount] = PED::CREATE_PED(26, pedm, pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 1, 0, 1, 1);
				PED::SET_PED_AS_GROUP_LEADER(selectedplayer, my_group);
				PED::SET_PED_AS_GROUP_MEMBER(clone[gcount], my_group);
				PED::SET_PED_NEVER_LEAVES_GROUP(clone[gcount], my_group);
				ENTITY::SET_ENTITY_INVINCIBLE(clone[gcount], false);
				PED::SET_PED_COMBAT_ABILITY(clone[gcount], 100);
				WEAPON::GIVE_WEAPON_TO_PED(clone[gcount], heavysniper, heavysniper, 9999, 9999);
				PED::SET_PED_CAN_SWITCH_WEAPON(clone[gcount], true);
				PED::SET_GROUP_FORMATION(my_group, 3);
				PED::SET_PED_MAX_HEALTH(clone[gcount], 5000);
				gcount++;
			}
			if (GUI::Option("Spawn Merry Weather w/ Mini Gun")) {
				Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
				Hash minigun = GAMEPLAY::GET_HASH_KEY("WEAPON_MINIGUN");
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
				Hash pedm = GAMEPLAY::GET_HASH_KEY("csb_mweather");
				STREAMING::REQUEST_MODEL(pedm);
				while (!STREAMING::HAS_MODEL_LOADED(pedm))
					WAIT(0);
				int my_group = PLAYER::GET_PLAYER_GROUP(selectedplayer);
				clone[gcount] = PED::CREATE_PED(26, pedm, pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 1, 0, 1, 1);
				PED::SET_PED_AS_GROUP_LEADER(selectedplayer, my_group);
				PED::SET_PED_AS_GROUP_MEMBER(clone[gcount], my_group);
				PED::SET_PED_NEVER_LEAVES_GROUP(clone[gcount], my_group);
				ENTITY::SET_ENTITY_INVINCIBLE(clone[gcount], false);
				PED::SET_PED_COMBAT_ABILITY(clone[gcount], 100);
				WEAPON::GIVE_WEAPON_TO_PED(clone[gcount], minigun, minigun, 9999, 9999);
				PED::SET_PED_CAN_SWITCH_WEAPON(clone[gcount], true);
				PED::SET_GROUP_FORMATION(my_group, 3);
				PED::SET_PED_MAX_HEALTH(clone[gcount], 5000);
				gcount++;
			}
			if (GUI::Option("Spawn FIB Agent w/ RPG")) {
				Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
				if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
				Hash rpg = GAMEPLAY::GET_HASH_KEY("WEAPON_RPG");
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
				Hash pedm = GAMEPLAY::GET_HASH_KEY("s_m_m_fiboffice_01");
				STREAMING::REQUEST_MODEL(pedm);
				while (!STREAMING::HAS_MODEL_LOADED(pedm))
					WAIT(0);
				int my_group = PLAYER::GET_PLAYER_GROUP(selectedplayer);
				clone[gcount] = PED::CREATE_PED(26, pedm, pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 1, 0, 1, 1);
				PED::SET_PED_AS_GROUP_LEADER(selectedplayer, my_group);
				PED::SET_PED_AS_GROUP_MEMBER(clone[gcount], my_group);
				PED::SET_PED_NEVER_LEAVES_GROUP(clone[gcount], my_group);
				ENTITY::SET_ENTITY_INVINCIBLE(clone[gcount], false);
				PED::SET_PED_COMBAT_ABILITY(clone[gcount], 100);
				WEAPON::GIVE_WEAPON_TO_PED(clone[gcount], rpg, rpg, 9999, 9999);
				PED::SET_PED_CAN_SWITCH_WEAPON(clone[gcount], true);
				PED::SET_GROUP_FORMATION(my_group, 3);
				PED::SET_PED_MAX_HEALTH(clone[gcount], 5000);
				gcount++;
			}
		}
		break;
#pragma endregion

#pragma region ESP
		case espmenu:
		{
			GUI::Title("ESP");
			GUI::Subtitle("ESP");
			if (!NETWORK::NETWORK_IS_IN_SESSION() && !NETWORK::NETWORK_IS_PLAYER_CONNECTED(PLAYER::PLAYER_PED_ID())) {
				GUI::Option("You need to be online to use this.");
			}
			else {
				GUI::Toggle("Name Tag ESP", Features::NameESP, [] { Features::NameTagESP(Features::NameESP); });
				GUI::Toggle("ESP", Features::esper, [] {});
			}
		}
		break;
#pragma endregion

#pragma region MerryWeather Requests
		case merryweather:
		{
			GUI::Title("");
			GUI::Subtitle("Merryweather Requests");
			if (!NETWORK::NETWORK_IS_IN_SESSION() && !NETWORK::NETWORK_IS_PLAYER_CONNECTED(PLAYER::PLAYER_PED_ID())) {
				GUI::Option("You need to be online to use this.");
			}
			else {
				if (GUI::Option("Airstrike w/ Flares")) {
					globalHandle(2524719).At(4377).As<int>() = 1;
				}
				if (GUI::Option("Ammo Drop")) {
					globalHandle(2524719).At(822).As<int>() = 1;
				}
				if (GUI::Option("Ammo Drop v2")) {
					globalHandle(2524719).At(832).As<int>() = 1;
				}
				if (GUI::Option("Boat Pickup")) {
					globalHandle(2524719).At(823).As<int>() = 1;
				}
				if (GUI::Option("Bullshark Testosterone Drop")) {
					globalHandle(2437022).At(3876).As<int>() = 1;
				}
				if (GUI::Option("Heli Backup")) {
					globalHandle(2524719).At(4376).As<int>() = 1;
				}
				if (GUI::Option("Heli Pickup")) {
					globalHandle(2524719).At(824).As<int>() = 1;
				}
			}
		}
		break;
#pragma endregion

#pragma region Session Options

		case session_mods:
		{
			GUI::Title("");
			GUI::Subtitle("Session Options");
			if (!NETWORK::NETWORK_IS_IN_SESSION() && !NETWORK::NETWORK_IS_PLAYER_CONNECTED(PLAYER::PLAYER_PED_ID())) 
			{
				GUI::Option("You need to be online to use this.");
			}
			else {
				GUI::MenuOption("ESP", espmenu);
				GUI::MenuOption("Merryweather Requests", merryweather);
				if (GUI::Option("Bypass LSC Vehicle Sell Time")) {
					STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_VEHICLE_SELL_TIME"), 0, 1);
				}
				if (Features::menu_version == 2) {
					if (GUI::Option("Remove Orbital Cooldown")) { //VIP
						STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ORBITAL_CANNON_COOLDOWN"), 0, 0);
						STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_ORBITAL_CANNON_COOLDOWN"), 0, 0);
					}
					GUI::Toggle("Unlimited Orbital Cannon Shots", Features::unliorbital, [] { Features::UnliOrbital(); }); //VIP
				}
				GUI::Toggle("Unlimited Vehicle Sell Time", Features::bypasssell, [] { Features::BypassSell(); });
				GUI::Toggle("Reveal Off-Radar Players", Features::isRevealPlayers, [] { Features::revealPlayers(); });
				//int rank;
				//if (GUI::Int("Spoof Rank", rank, -9999, 9999)) {
				//	globalHandle(1589747).At(PLAYER::PLAYER_ID(), 790).At(211).At(6).As<int>() = rank;
				//}
			}
		}
		break;

#pragma endregion

#pragma endregion

#pragma region Recovery SubMenus

#pragma region Unlocks
		case unlocks:
		{
			GUI::Title("Recovery Options");
			GUI::Subtitle("Recovery Options");
			if (!NETWORK::NETWORK_IS_IN_SESSION() && !NETWORK::NETWORK_IS_PLAYER_CONNECTED(PLAYER::PLAYER_PED_ID())) {
				GUI::Option("You need to be online to use this.");
			}
			else {
				if (GUI::Option("Max Character Skills")) {
					Features::MaxStats();
				}
				if (GUI::Option("Unlock All Tattoos")) {
					Features::UnlockTattoos();
				}
				if (GUI::Option("Unlimited Snacks")) {
					Features::UnliSnacks();
				}
				if (GUI::Option("Unlock Weapon Colors")) {
					Features::UnlockWpnColors();
				}
				if (GUI::Option("Unlock All Clothing")) {
					Features::UnlockClothings();
				}
				if (GUI::Option("Unlock Vehicle Mods (NEW)")) {
					Features::Unlockcars();
				}
			}
		}
		break;
#pragma endregion

#pragma region Stealth Money

		case stealth:
		{
			GUI::Title("");
			GUI::Subtitle("Money Options");
			if (!NETWORK::NETWORK_IS_IN_SESSION() && !NETWORK::NETWORK_IS_PLAYER_CONNECTED(PLAYER::PLAYER_PED_ID())) {
				GUI::Option("You need to be online to use this.");
			}
			else {
				GUI::MenuOption("ATM", atm);
				GUI::MenuOption("Stealth Job Money", stealthadd);
				GUI::MenuOption("Stealth Remove Money", stealthremove);
				GUI::Break("Drop Cash");
				GUI::Toggle("Drop Money Bags [Above]", Features::CashDropSelfBoolv1, [] {Features::CashDropSelfv1(Features::CashDropSelfBoolv1); });
				GUI::Toggle("Drop Money Bags [Below]", Features::CashDropSelfBoolv2, [] {Features::CashDropSelfv2(Features::CashDropSelfBoolv2); });
				GUI::Toggle("Money Rain", Features::moneyrain2k, [] { Features::RainMoney(Features::moneyrain2k); });
			}
		}
		break;

		case atm:
		{
			GUI::Title("");
			GUI::Subtitle("ATM");
			GUI::Break("Withdraw Money");
			if (GUI::Option("Withdraw 5 Mil")) {
				Features::withdraw(5000000);
			}
			if (GUI::Option("Withdraw 10 Mil")) {
				Features::withdraw(10000000);
			}
			if (GUI::Option("Withdraw 20 Mil")) {
				Features::withdraw(20000000);
			}
			if (GUI::Option("Withdraw 100 Mil")) {
				Features::withdraw(100000000);
			}

			GUI::Break("Deposit Money");
			if (GUI::Option("Deposit 5 Mil")) {
				Features::deposit(5000000);
			}
			if (GUI::Option("Deposit 10 Mil")) {
				Features::deposit(10000000);
			}
			if (GUI::Option("Deposit 20 Mil")) {
				Features::deposit(20000000);
			}
			if (GUI::Option("Deposit 100 Mil")) {
				Features::deposit(100000000);
			}
		}
		break;

		case stealthadd:
		{
			GUI::Title("");
			GUI::Subtitle("Stealth Job");
			GUI::Break("Method 1");
			GUI::Int("Value", Features::stealth1Value, 1000000, 10000000, 1000000);
			GUI::Toggle("Stealth Toggle", Features::isStealthLoop1);
			GUI::Break("Method 2");
			GUI::Int("Value", Features::stealth2Value, 1000000, 15000000, 1000000);
			GUI::Toggle("Stealth Toggle", Features::isStealthLoop2);
			GUI::Toggle("Send to Bank [Method 2]", Features::isStealthBanked);
			if (GUI::Option("10Mil Stealth Job [Method 1]")) {
				Features::stealthSingle(10000000);
			}
			if (GUI::Option("10Mil Stealth Job [Method 2]")) {
				Features::stealthSingle2(10000000);
			}
		}
		break;

		case stealthremove:
		{
			GUI::Title("");
			GUI::Subtitle("Remove Money");
			GUI::Int("Value", Features::removeValue, 0, 10000000, 1000000);
			GUI::Toggle("Remove Toggle", Features::isRemoveMoney);
			if (GUI::Option("Remove 10mil from bank")) {
				Features::removeBankMoney(10000000);
			}
			if (GUI::Option("Remove 10mil from cash")) {
				Features::removeCashMoney(10000000);
			}
		}
		break;

#pragma endregion

#pragma region Ranks
		case rp:
		{
			GUI::Title("");
			GUI::Subtitle("Rank Options");
			if (!NETWORK::NETWORK_IS_IN_SESSION() && !NETWORK::NETWORK_IS_PLAYER_CONNECTED(PLAYER::PLAYER_PED_ID())) {
				GUI::Option("You need to be online to use this.");
			}
			else {
				GUI::Toggle("RP Loop", Features::RPLoop, [] { Features::rpLoop(); });
				if (GUI::Option("RP Correction")) {
					int temp1 = 0;
					temp1 = Features::RankKeyboard();

					if (temp1 != 0) {
						Features::RPCorrect(temp1);
						break;
					}
					else {
						notifyMap("~r~Invalid Input!");
					}

				}
				if (GUI::Option("Set Rank")) {
					int temp1 = 0;
					temp1 = Features::RankKeyboard();

					if (temp1 != 0) {
						Features::SetRank(temp1);
						break;
					}
					else {
						notifyMap("~r~Invalid Input!");
					}
				}
				GUI::Break("Instant Rank");
				if (GUI::Option("Rank Set 50")) {
					Features::SetRank(50);
				}
				if (GUI::Option("Rank Set 75")) {
					Features::SetRank(75);
				}
				if (GUI::Option("Rank Set 100")) {
					Features::SetRank(100);
				}
				if (GUI::Option("Rank Set 150")) {
					Features::SetRank(150);
				}
				if (GUI::Option("Rank Set 200")) {
					Features::SetRank(200);
				}
				if (GUI::Option("Rank Set 250")) {
					Features::SetRank(250);
				}
				if (GUI::Option("Rank Set 300")) {
					Features::SetRank(300);
				}
				if (GUI::Option("Rank Set 350")) {
					Features::SetRank(350);
				}
				if (GUI::Option("Rank Set 400")) {
					Features::SetRank(400);
				}
				if (GUI::Option("Rank Set 450")) {
					Features::SetRank(450);
				}
				if (GUI::Option("Rank Set 500")) {
					Features::SetRank(500);
				}
				if (GUI::Option("Rank Set 550")) {
					Features::SetRank(550);
				}
				if (GUI::Option("Rank Set 600")) {
					Features::SetRank(600);
				}
				if (GUI::Option("Rank Set 650")) {
					Features::SetRank(650);
				}
				if (GUI::Option("Rank Set 700")) {
					Features::SetRank(700);
				}
				if (GUI::Option("Rank Set 750")) {
					Features::SetRank(750);
				}
				if (GUI::Option("Rank Set 800")) {
					Features::SetRank(800);
				}
				if (GUI::Option("Rank Set 850")) {
					Features::SetRank(850);
				}
				if (GUI::Option("Rank Set 900")) {
					Features::SetRank(900);
				}
				if (GUI::Option("Rank Set 950")) {
					Features::SetRank(950);
				}
				if (GUI::Option("Rank Set 1000")) {
					Features::SetRank(1000);
				}
			}
		}
		break;
#pragma endregion

#pragma region Stats Editor
		case statsEdit:
		{
			GUI::Title("");
			GUI::Subtitle("Stats Editor");
			if (!NETWORK::NETWORK_IS_IN_SESSION() && !NETWORK::NETWORK_IS_PLAYER_CONNECTED(PLAYER::PLAYER_PED_ID())) {
				GUI::Option("You need to be online to use this.");
			}
			else {
				GUI::Drawing::Spriter("Textures", "stat", GUI::Settings::menuX, 0.0800f, 0.21f, 0.090f, 0, GUI::Settings::titleRect.r, GUI::Settings::titleRect.g, GUI::Settings::titleRect.b, GUI::Settings::titleRect.a);

				if (GUI::Option("Set Money Earned In Jobs")) {
					int val = Features::NumberKeyboard();
					Hooking::stat_set_int($("MPPLY_TOTAL_EVC"), val, 1);

					UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
					UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Please change session to take effect.");
					UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "Project", "Stats Editor", 1, "", 9, 0);
					UI::_DRAW_NOTIFICATION(FALSE, FALSE);
				}
				if (GUI::Option("Set Total Money Earned")) {
					int temp1 = 0;
					temp1 = Features::NumberKeyboard();
					Hooking::stat_set_int($("MPPLY_TOTAL_EVC"), temp1, 1);

					UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
					UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Please change session to take effect.");
					UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "Project", "Stats Editor", 1, "", 9, 0);
					UI::_DRAW_NOTIFICATION(FALSE, FALSE);
				}
				if (GUI::Option("Set Report Strength")) {
					int val = Features::NumberKeyboard();
					Hooking::stat_set_int($("MPPLY_REPORT_STRENGTH"), val, 1);

					UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
					UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Please change session to take effect.");
					UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "Project", "Stats Editor", 1, "", 9, 0);
					UI::_DRAW_NOTIFICATION(FALSE, FALSE);
				}
				if (GUI::Option("Custom Deaths")) {
					int val = Features::NumberKeyboard();
					Hooking::stat_set_int($("MPPLY_DEATHS_PLAYER"), val, 1);

					UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
					UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Please change session to take effect.");
					UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "Project", "Stats Editor", 1, "", 9, 0);
					UI::_DRAW_NOTIFICATION(FALSE, FALSE);
				}
				if (GUI::Option("Set Commend Strength")) {
					int val = Features::NumberKeyboard();
					Hooking::stat_set_int($("MPPLY_COMMEND_STRENGTH"), val, 1);

					UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
					UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Please change session to take effect.");
					UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "Project", "Stats Editor", 1, "", 9, 0);
					UI::_DRAW_NOTIFICATION(FALSE, FALSE);
				}
				if (GUI::Option("Set Friendly Stuff")) {
					int val = Features::NumberKeyboard();
					Hooking::stat_set_int($("MPPLY_FRIENDLY"), val, 1);

					UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
					UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Please change session to take effect.");
					UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "Project", "Stats Editor", 1, "", 9, 0);
					UI::_DRAW_NOTIFICATION(FALSE, FALSE);
				}
				if (GUI::Option("Set Helpfull Stuff")) {
					int val = Features::NumberKeyboard();
					Hooking::stat_set_int($("MPPLY_HELPFUL"), val, 1);

					UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
					UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Please change session to take effect.");
					UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "Project", "Stats Editor", 1, "", 9, 0);
					UI::_DRAW_NOTIFICATION(FALSE, FALSE);
				}
				if (GUI::Option("Set Griefing")) {
					int val = Features::NumberKeyboard();
					Hooking::stat_set_int($("MPPLY_GRIEFING"), val, 1);

					UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
					UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Please change session to take effect.");
					UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "Project", "Stats Editor", 1, "", 9, 0);
					UI::_DRAW_NOTIFICATION(FALSE, FALSE);
				}
				if (GUI::Option("Set Offensive Language")) {
					int val = Features::NumberKeyboard();
					Hooking::stat_set_int($("MPPLY_OFFENSIVE_LANGUAGE"), val, 1);

					UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
					UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Please change session to take effect.");
					UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "Project", "Stats Editor", 1, "", 9, 0);
					UI::_DRAW_NOTIFICATION(FALSE, FALSE);
				}
				if (GUI::Option("Set Offensive UGC")) {
					int val = Features::NumberKeyboard();
					Hooking::stat_set_int($("MPPLY_OFFENSIVE_UGC"), val, 1);

					UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
					UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Please change session to take effect.");
					UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "Project", "Stats Editor", 1, "", 9, 0);
					UI::_DRAW_NOTIFICATION(FALSE, FALSE);
				}
				if (GUI::Option("Set VC Hate")) {
					int val = Features::NumberKeyboard();
					Hooking::stat_set_int($("MPPLY_VC_HATE"), val, 1);

					UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
					UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Please change session to take effect.");
					UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "Project", "Stats Editor", 1, "", 9, 0);
					UI::_DRAW_NOTIFICATION(FALSE, FALSE);
				}
				if (GUI::Option("Set Gameplay Exploits")) {
					int val = Features::NumberKeyboard();
					Hooking::stat_set_int($("MPPLY_GAME_EXPLOITS"), val, 1);

					UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
					UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Please change session to take effect.");
					UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "Project", "Stats Editor", 1, "", 9, 0);
					UI::_DRAW_NOTIFICATION(FALSE, FALSE);
				}
				if (GUI::Option("Set Inspunished")) {
					int val = Features::NumberKeyboard();
					Hooking::stat_set_int($("MPPLY_ISPUNISHED"), val, 1);

					UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
					UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Please change session to take effect.");
					UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "Project", "Stats Editor", 1, "", 9, 0);
					UI::_DRAW_NOTIFICATION(FALSE, FALSE);
				}
				if (GUI::Option("Set Badsports")) {
					int val = Features::NumberKeyboard();
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_1ST_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_2ND_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_3RD_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_4TH_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_5TH_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_6TH_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_7TH_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_8TH_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_9TH_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_10TH_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_1ST_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_2ND_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_3RD_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_4TH_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_5TH_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_6TH_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_7TH_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_8TH_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_9TH_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_11TH_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_1ST_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_2ND_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_3RD_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_4TH_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_5TH_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_6TH_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_7TH_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_8TH_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_9TH_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_11TH_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_1ST_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_2ND_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_3RD_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_4TH_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_5TH_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_6TH_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_7TH_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_8TH_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_9TH_OFFENCE"), val, 1);
					Hooking::stat_set_int($("BADSPORT_NUMDAYS_11TH_OFFENCE"), val, 1);
					Hooking::stat_set_int($("MPPLY_BECAME_BADSPORT_NUM"), val, 1);
					Hooking::stat_set_int($("BAD_SPORT_BITSET"), val, 1);
					Hooking::stat_set_int($("CHEAT_BITSET"), val, 1);

					UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
					UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Please change session to take effect.");
					UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "Project", "Stats Editor", 1, "", 9, 0);
					UI::_DRAW_NOTIFICATION(FALSE, FALSE);

				}
				if (GUI::Option("Set Kills")) {
					int val = Features::NumberKeyboard();
					Hooking::stat_set_int($("MPPLY_KILLS_PLAYERS"), val, 1);

					UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
					UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Please change session to take effect.");
					UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "Project", "Stats Editor", 1, "", 9, 0);
					UI::_DRAW_NOTIFICATION(FALSE, FALSE);
				}
				if (GUI::Option("Set Won Races")) {
					int val = Features::NumberKeyboard();
					Hooking::stat_set_int($("AWD_RACES_WON"), val, 1);
					Hooking::stat_set_int($("AWD_FM_GTA_RACES_WON"), val, 1);

					UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
					UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Please change session to take effect.");
					UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "Project", "Stats Editor", 1, "", 9, 0);
					UI::_DRAW_NOTIFICATION(FALSE, FALSE);
				}
				if (GUI::Option("Set Armwrestling Wins")) {
					int val = Features::NumberKeyboard();
					Hooking::stat_set_int($("AWD_NO_ARMWRESTLING_WINS"), val, 1);

					UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
					UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Please change session to take effect.");
					UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "Project", "Stats Editor", 1, "", 9, 0);
					UI::_DRAW_NOTIFICATION(FALSE, FALSE);
				}
				if (GUI::Option("Set Deathmatch Wins")) {
					int val = Features::NumberKeyboard();
					Hooking::stat_set_int($("AWD_FM_DM_WINS"), val, 1);
					Hooking::stat_set_int($("AWD_FM_DM_WINS"), val, 1);
					Hooking::stat_set_int($("AWD_FM_TDM_WINS"), val, 1);

					UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
					UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Please change session to take effect.");
					UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "Project", "Stats Editor", 1, "", 9, 0);
					UI::_DRAW_NOTIFICATION(FALSE, FALSE);
				}
				if (GUI::Option("Set Deathmatch Losses")) {
					int val = Features::NumberKeyboard();
					Hooking::stat_set_int($("MPPLY_TOTAL_DEATHMATCH_LOST"), val, 1);

					UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
					UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Please change session to take effect.");
					UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "Project", "Stats Editor", 1, "", 9, 0);
					UI::_DRAW_NOTIFICATION(FALSE, FALSE);
				}
				if (GUI::Option("Set Death Match Kills")) {
					int val = Features::NumberKeyboard();
					Hooking::stat_set_int($("AWD_FM_DM_TOTALKILLS"), val, 1);

					UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
					UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Please change session to take effect.");
					UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "Project", "Stats Editor", 1, "", 9, 0);
					UI::_DRAW_NOTIFICATION(FALSE, FALSE);
				}
				if (GUI::Option("Set Death Match Deaths")) {
					int val = Features::NumberKeyboard();
					Hooking::stat_set_int($("MPPLY_DM_TOTAL_DEATHS"), val, 1);

					UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
					UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Please change session to take effect.");
					UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "Project", "Stats Editor", 1, "", 9, 0);
					UI::_DRAW_NOTIFICATION(FALSE, FALSE);
				}
				if (GUI::Option("Set Golf Wins")) {
					int val = Features::NumberKeyboard();
					Hooking::stat_set_int($("AWD_FM_GOLF_WON"), val, 1);

					UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
					UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Please change session to take effect.");
					UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "Project", "Stats Editor", 1, "", 9, 0);
					UI::_DRAW_NOTIFICATION(FALSE, FALSE);
				}
				if (GUI::Option("Set Shooting Range Wins")) {
					int val = Features::NumberKeyboard();
					Hooking::stat_set_int($("AWD_FM_SHOOTRANG_TG_WON"), val, 1);
					Hooking::stat_set_int($("AWD_FM_SHOOTRANG_RT_WON"), val, 1);
					Hooking::stat_set_int($("AWD_FM_SHOOTRANG_CT_WON"), val, 1);
					Hooking::stat_set_int($("AWD_FM_SHOOTRANG_GRAN_WON"), val, 1);

					UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
					UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Please change session to take effect.");
					UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "Project", "Stats Editor", 1, "", 9, 0);
					UI::_DRAW_NOTIFICATION(FALSE, FALSE);
				}
				if (GUI::Option("Set Tennis Wins")) {
					int val = Features::NumberKeyboard();
					Hooking::stat_set_int($("AWD_FM_TENNIS_WON"), val, 1);
					Hooking::stat_set_int($("MPPLY_TENNIS_MATCHES_WON"), val, 1);

					UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
					UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Please change session to take effect.");
					UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "Project", "Stats Editor", 1, "", 9, 0);
					UI::_DRAW_NOTIFICATION(FALSE, FALSE);
				}
				if (GUI::Option("Weapons")) {
					int val = Features::NumberKeyboard();

					Hooking::stat_set_int($("MOLOTOV_ENEMY_KILLS"), val, 1);
					Hooking::stat_set_int($("CMBTPISTOL_ENEMY_KILLS"), val, 1);
					Hooking::stat_set_int($("PISTOL50_ENEMY_KILLS"), val, 1);
					Hooking::stat_set_int($("APPISTOL_ENEMY_KILLS"), val, 1);
					Hooking::stat_set_int($("MICROSMG_ENEMY_KILLS"), val, 1);
					Hooking::stat_set_int($("SMG_ENEMY_KILLS"), val, 1);
					Hooking::stat_set_int($("ASLTSMG_ENEMY_KILLS"), val, 1);
					Hooking::stat_set_int($("ASLTRIFLE_ENEMY_KILLS"), val, 1);
					Hooking::stat_set_int($("CRBNRIFLE_ENEMY_KILLS"), val, 1);
					Hooking::stat_set_int($("ADVRIFLE_ENEMY_KILLS"), val, 1);
					Hooking::stat_set_int($("MG_ENEMY_KILLS"), val, 1);
					Hooking::stat_set_int($("CMBTMG_ENEMY_KILLS"), val, 1);
					Hooking::stat_set_int($("ASLTMG_ENEMY_KILLS"), val, 1);
					Hooking::stat_set_int($("PUMP_ENEMY_KILLS"), val, 1);
					Hooking::stat_set_int($("SAWNOFF_ENEMY_KILLS"), val, 1);
					Hooking::stat_set_int($("BULLPUP_ENEMY_KILLS"), val, 1);
					Hooking::stat_set_int($("ASLTSHTGN_ENEMY_KILLS"), val, 1);
					Hooking::stat_set_int($("SNIPERRFL_ENEMY_KILLS"), val, 1);
					Hooking::stat_set_int($("HVYSNIPER_ENEMY_KILLS"), val, 1);
					Hooking::stat_set_int($("GRNLAUNCH_ENEMY_KILLS"), val, 1);
					Hooking::stat_set_int($("RPG_ENEMY_KILLS"), val, 1);
					Hooking::stat_set_int($("MINIGUNS_ENEMY_KILLS"), val, 1);
					Hooking::stat_set_int($("GRENADE_ENEMY_KILLS"), val, 1);
					Hooking::stat_set_int($("SMKGRENADE_ENEMY_KILLS"), val, 1);
					Hooking::stat_set_int($("STKYBMB_ENEMY_KILLS"), val, 1);
					Hooking::stat_set_int($("MOLOTOV_ENEMY_KILLS"), val, 1);

					UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
					UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Please change session to take effect.");
					UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "Project", "Stats Editor", 1, "", 9, 0);
					UI::_DRAW_NOTIFICATION(FALSE, FALSE);
				}
			}
		}
		break;
#pragma endregion

#pragma endregion

#pragma region World SubMenus

#pragma region Map Mods
		case mapmods:
		{
			GUI::Title("");
			GUI::Subtitle("Map Mods");
			GUI::MenuOption("Maze Bank Small Ramp", ramp1);
			GUI::MenuOption("Maze Bank Roof Ramp", ramp2);
			GUI::MenuOption("Beach Ramp", ramp3);
			GUI::MenuOption("Mount Chilliad Ramp", ramp4);
			GUI::MenuOption("Airport Mini Ramp", ramp5);
			GUI::MenuOption("Airport Gate Ramp", ramp6);
			GUI::MenuOption("Space Tower", ramp7);
			GUI::MenuOption("Quad Ramp", ramp8);
			GUI::MenuOption("Fort", ramp9);
			GUI::MenuOption("Half Pipe", ramp10);
			GUI::MenuOption("Airport Loop Ramp", ramp11);
			GUI::MenuOption("Mega Ramp", ramp12);
		}
		break;
#pragma endregion

#pragma region Mods
		case ramp1:
			GUI::Title("Maze Bank Demolition");
			GUI::Subtitle("Maze Bank Demolition");
			if (GUI::Option("Load")) {
				Features::PlaceObjectByHash(2475986526, -80.9087f, -830.357f, 325.097f, -14.4264f, -8.53774f, 152.209f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -79.2316f, -831.297f, 325.108f, -14.4054f, 4.26887f, 164.271f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -76.7563f, -831.549f, 325.123f, -14.4263f, -0.0f, 171.818f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -74.2595f, -831.691f, 325.09f, -14.2059f, -1.06722f, -176.517f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -71.9478f, -831.257f, 325.113f, -14.4264f, 2.13443f, -166.006f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -69.5981f, -830.542f, 325.066f, -14.5918f, -4.26887f, -155.474f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -67.4174f, -829.035f, 325.097f, -14.4263f, -4.26887f, -140.651f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -65.7121f, -827.409f, 325.068f, -14.3048f, -1.70755f, -130.667f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -64.2717f, -825.422f, 325.112f, -14.4263f, -0.0f, -121.256f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -63.2876f, -823.434f, 325.114f, -14.5345f, -0.0f, -111.446f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -62.4924f, -821.128f, 325.082f, -14.5467f, 2.13443f, -102.385f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -62.233f, -818.528f, 325.065f, -14.6184f, -8.00413f, -88.1861f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -62.8694f, -815.926f, 325.118f, -14.4265f, -6.4033f, -76.5979f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -63.6142f, -813.68f, 325.112f, -14.3655f, 8.53774f, -66.7885f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -64.9883f, -811.439f, 325.107f, -14.4263f, 1.28066f, -52.8494f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -66.5913f, -808.328f, 325.238f, -12.4517f, -0.0f, -40.3246f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -68.2603f, -807.899f, 325.336f, -13.8689f, -0.0f, -33.062f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -71.1526f, -807.598f, 325.153f, -12.0416f, 4.26887f, -28.0523f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -73.2853f, -806.628f, 325.151f, -11.7962f, -0.0f, -19.1717f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -75.2243f, -806.286f, 325.164f, -12.0419f, -0.0f, 1.55726f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -77.5757f, -806.312f, 325.088f, -14.1843f, -0.0f, 12.6263f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -79.8704f, -807.22f, 325.143f, -14.049f, -4.26887f, 21.4769f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -82.0222f, -807.83f, 325.036f, -14.1422f, -4.26887f, 32.7605f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -83.8934f, -809.424f, 325.073f, -14.5264f, -8.53774f, 46.5132f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -85.2523f, -810.983f, 325.043f, -14.859f, -0.0f, 53.5324f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -86.5177f, -813.202f, 325.089f, -14.5267f, 4.26887f, 64.6634f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -87.6645f, -815.707f, 325.059f, -14.8589f, 4.26887f, 73.157f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -87.7973f, -817.987f, 325.119f, -14.8468f, -1.33402f, 89.3982f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -87.5801f, -821.034f, 325.059f, -14.8593f, -0.0f, 95.4435f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -87.2815f, -822.239f, 325.126f, -15.6308f, -4.26887f, 100.311f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -86.7602f, -824.03f, 325.044f, -15.9224f, -0.0f, 116.957f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -85.3743f, -826.099f, 325.136f, -15.7025f, 2.56132f, 124.307f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -83.4737f, -828.611f, 325.076f, -15.0688f, -0.0f, 132.538f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -87.9554f, -832.877f, 325.894f, -14.1563f, 4.26887f, 132.995f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -89.3865f, -831.322f, 325.887f, -14.1562f, -0.0f, 126.154f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -86.4247f, -834.407f, 325.915f, -14.2701f, 4.26887f, 143.277f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -85.1736f, -833.789f, 325.653f, -14.4072f, -4.26887f, 145.777f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -83.8118f, -835.765f, 326.063f, -12.243f, 4.26887f, 151.527f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -80.7015f, -837.145f, 326.059f, -12.3172f, 2.13443f, 162.332f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -77.6428f, -837.649f, 326.163f, -10.8391f, 3.20165f, 171.297f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -75.479f, -837.909f, 326.025f, -12.3172f, -1.06722f, 174.574f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -73.861f, -837.826f, 326.061f, -12.3173f, 5.33609f, -176.632f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -70.4799f, -837.265f, 326.09f, -12.3173f, -0.0f, -166.182f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -67.0415f, -836.185f, 326.018f, -12.3171f, -0.0f, -156.039f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -64.8504f, -834.996f, 325.951f, -11.5263f, -0.0f, -145.834f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -63.5702f, -833.725f, 326.1f, -11.2947f, -0.0f, -140.961f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -60.9992f, -831.419f, 326.075f, -11.5262f, -4.26887f, -130.963f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -58.9923f, -828.729f, 326.116f, -11.5262f, 4.26887f, -121.973f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -57.5045f, -825.626f, 326.114f, -11.5263f, -0.0f, -110.959f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -56.5533f, -822.397f, 326.08f, -11.1311f, -6.4033f, -102.0f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -56.0911f, -820.05f, 326.049f, -11.0325f, 2.13443f, -100.794f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -56.0681f, -818.32f, 326.087f, -11.1312f, -2.66804f, -87.9469f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -56.2989f, -816.237f, 326.048f, -11.0324f, 2.13443f, -83.2139f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -56.8952f, -814.518f, 326.142f, -11.0324f, -2.13443f, -76.5476f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -58.1209f, -811.23f, 326.116f, -10.9697f, -0.0f, -66.7674f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -59.0622f, -809.17f, 326.095f, -11.0574f, 4.26887f, -62.782f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -60.096f, -807.639f, 326.119f, -11.5544f, -0.0f, -52.7596f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -62.081f, -805.317f, 326.116f, -11.1035f, -0.0f, -40.7682f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -64.1466f, -804.55f, 326.283f, -11.1035f, -0.0f, -30.477f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -67.9795f, -798.8f, 326.717f, -10.1561f, -0.0f, -29.3495f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -67.5734f, -802.52f, 326.262f, -10.471f, -8.53774f, -31.2185f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -70.9341f, -800.541f, 326.198f, -10.5317f, -0.0f, -20.0064f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -75.3309f, -801.285f, 325.849f, -10.2407f, -0.0f, 1.58401f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -74.0222f, -799.865f, 326.177f, -10.7327f, -0.0f, -5.98314f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -76.5167f, -797.998f, 326.32f, -12.4969f, -2.66804f, 1.58883f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -79.2787f, -800.531f, 326.011f, -12.9433f, 4.26887f, 13.0054f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -81.6721f, -801.017f, 325.9f, -12.4601f, 2.13443f, 17.3792f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -83.6027f, -801.744f, 325.971f, -12.9433f, -0.0f, 26.3052f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -85.6586f, -802.789f, 325.95f, -12.8791f, 1.28066f, 32.5856f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -87.5086f, -804.25f, 325.978f, -12.9432f, 4.26887f, 42.3279f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -88.9923f, -805.73f, 325.89f, -11.9333f, -4.26887f, 46.0613f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -90.167f, -807.318f, 325.946f, -13.0244f, -0.0f, 53.178f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -93.5987f, -807.353f, 326.343f, -11.5713f, 4.26887f, 60.8753f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -93.5166f, -813.963f, 325.942f, -13.4341f, -4.26887f, 73.0256f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -92.121f, -810.584f, 325.996f, -13.4339f, -4.26887f, 64.9353f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -93.9931f, -815.866f, 325.924f, -13.0519f, -0.0f, 79.5966f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -93.8716f, -817.904f, 325.988f, -13.4339f, -0.0f, 88.8361f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -93.7912f, -821.777f, 325.946f, -13.6946f, -2.66804f, 91.1427f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -93.2951f, -823.554f, 325.966f, -13.157f, -0.0f, 101.424f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -92.5757f, -827.033f, 325.87f, -13.5323f, -0.0f, 104.668f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -91.53f, -828.342f, 325.842f, -14.1563f, 4.26887f, 120.328f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -90.5203f, -829.611f, 325.936f, -14.1563f, -0.0f, 124.573f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -95.5355f, -833.068f, 327.049f, -9.63525f, 1.70755f, 124.512f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -94.2445f, -835.1f, 326.976f, -9.27617f, -1.28066f, 128.396f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -92.513f, -837.087f, 327.008f, -9.63523f, -4.26887f, 132.871f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -90.07f, -839.341f, 327.025f, -9.63574f, 4.26887f, 143.545f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -86.7336f, -841.135f, 327.284f, -9.63566f, -0.0f, 150.983f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -84.8343f, -842.167f, 327.254f, -9.36742f, -4.26887f, 152.377f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -90.0883f, -842.661f, 327.589f, -7.98782f, -8.53774f, 146.409f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -82.595f, -843.001f, 327.277f, -9.6352f, -0.0f, 161.654f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -80.8027f, -843.618f, 327.263f, -9.36755f, -2.13443f, 165.215f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -78.5619f, -843.703f, 327.458f, -9.63545f, -2.13443f, 171.015f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -76.2479f, -844.026f, 327.261f, -9.36765f, 1.06722f, 175.986f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -73.5382f, -843.999f, 327.285f, -9.6355f, -0.0f, -177.212f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -71.2047f, -843.988f, 327.3f, -9.36764f, -1.06722f, -172.013f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -69.036f, -843.266f, 327.309f, -9.63525f, 4.26887f, -166.686f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -67.2981f, -840.996f, 326.756f, -9.37509f, -2.13443f, -159.014f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -66.7067f, -842.714f, 327.222f, -9.37501f, 2.13443f, -159.27f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -64.5693f, -841.792f, 327.24f, -9.63515f, 4.26887f, -156.16f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -61.8874f, -840.436f, 327.231f, -9.37483f, 4.26887f, -146.534f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -59.7118f, -838.501f, 327.384f, -9.63533f, -0.0f, -141.372f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -57.9491f, -837.16f, 327.309f, -9.37471f, 4.26887f, -135.839f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -56.3494f, -835.471f, 327.34f, -9.63578f, 4.26887f, -131.675f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -54.9387f, -833.93f, 327.334f, -9.37482f, -0.0f, -127.887f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -53.727f, -832.032f, 327.367f, -9.63521f, -4.26887f, -122.142f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -52.5928f, -830.077f, 327.332f, -9.37496f, -0.0f, -116.843f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -51.7552f, -827.819f, 327.385f, -9.63569f, 6.4033f, -111.077f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -51.0061f, -825.839f, 327.369f, -9.37494f, 4.26887f, -107.054f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -50.5468f, -823.622f, 327.378f, -9.63572f, 4.26887f, -101.598f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -50.0992f, -820.896f, 327.345f, -9.47333f, -1.06722f, -95.7976f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -49.9295f, -818.102f, 327.381f, -9.63531f, -8.00413f, -88.2146f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -50.1895f, -815.816f, 327.358f, -9.4734f, -0.0f, -82.8649f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -50.9164f, -813.132f, 327.442f, -9.63524f, 2.13443f, -76.865f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -51.1585f, -811.568f, 327.373f, -9.58574f, -0.0f, -69.3402f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -52.0622f, -809.533f, 327.354f, -9.63541f, 2.13443f, -65.7624f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -53.4048f, -806.624f, 327.376f, -9.63526f, 2.13443f, -65.3971f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -55.2978f, -803.815f, 327.389f, -9.63524f, 4.26887f, -52.2107f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -56.5179f, -802.266f, 327.366f, -9.51013f, 4.26887f, -50.6537f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -57.9995f, -800.68f, 327.42f, -9.6353f, 1.28066f, -41.7027f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -61.0278f, -799.404f, 327.549f, -9.63516f, 8.53774f, -31.016f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -64.37f, -797.284f, 327.603f, -9.6351f, -0.0f, -31.6732f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -66.3998f, -795.965f, 327.526f, -9.42422f, 8.53773f, -29.018f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -68.8079f, -794.744f, 327.535f, -9.63558f, -2.13443f, -20.0341f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -72.1225f, -793.825f, 327.497f, -9.57894f, -2.13443f, -12.2336f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -75.6415f, -795.169f, 327.2f, -9.63555f, -1.60083f, 2.8097f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -77.9613f, -794.235f, 327.223f, -8.9769f, -5.33608f, 4.53814f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -75.3695f, -789.507f, 328.306f, -8.84722f, -8.33763f, -0.0879073f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -80.6908f, -794.505f, 327.217f, -9.63537f, 4.26887f, 13.0745f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -83.5673f, -795.148f, 327.101f, -9.92985f, 2.13443f, 17.5819f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -86.3087f, -796.203f, 327.177f, -9.63542f, -4.26887f, 25.9296f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -88.9655f, -797.634f, 327.118f, -9.92994f, -4.26887f, 33.0571f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -91.6251f, -799.702f, 327.176f, -9.63539f, -0.0f, 42.2513f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -93.414f, -801.299f, 327.124f, -9.92995f, -0.0f, 48.7085f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -95.1453f, -803.637f, 327.147f, -9.63537f, -8.53774f, 53.6544f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -96.5885f, -805.701f, 327.144f, -9.8947f, -0.0f, 60.5096f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -97.6945f, -807.971f, 327.174f, -9.63569f, 4.26887f, 64.7568f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -98.7075f, -809.885f, 327.026f, -8.13758f, -0.0f, 67.8881f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -99.394f, -812.176f, 327.105f, -9.63525f, -4.26887f, 73.0223f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -100.025f, -814.868f, 327.097f, -9.97277f, 2.13443f, 83.1537f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -100.012f, -817.789f, 327.15f, -9.63535f, -1.33402f, 88.8234f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -100.069f, -819.76f, 327.099f, -9.95297f, -1.33402f, 90.8729f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -99.969f, -821.91f, 327.11f, -9.63541f, -2.66804f, 91.5501f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -99.3358f, -824.801f, 327.138f, -9.63539f, 2.13443f, 101.678f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -98.5443f, -828.598f, 327.033f, -9.63553f, -0.0f, 104.64f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -97.0896f, -831.054f, 326.937f, -10.0741f, 4.26887f, 118.72f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -102.435f, -833.952f, 328.506f, -5.26399f, -0.0f, 118.502f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -103.536f, -831.932f, 328.513f, -5.42142f, 4.26887f, 111.099f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -100.644f, -836.571f, 328.636f, -5.26398f, -0.0f, 124.006f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -99.0448f, -838.912f, 328.589f, -5.26395f, -2.13443f, 128.175f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -96.9401f, -841.184f, 328.589f, -5.26384f, -2.13443f, 132.615f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -95.4409f, -842.718f, 328.551f, -5.01006f, -2.13443f, 136.57f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -93.6584f, -844.231f, 328.606f, -5.26388f, -0.0f, 143.429f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -92.1044f, -845.82f, 328.655f, -5.01307f, -2.13443f, 147.428f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -89.6061f, -846.328f, 328.851f, -5.26389f, -0.0f, 150.62f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -87.5884f, -847.552f, 328.829f, -5.6777f, -0.0f, 153.36f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -84.5215f, -848.802f, 328.867f, -5.26405f, 5.33608f, 161.164f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -81.9779f, -849.605f, 328.821f, -5.67769f, 1.06722f, 166.961f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -79.5282f, -849.717f, 329.046f, -5.26392f, 1.06722f, 170.517f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -76.7555f, -850.113f, 328.885f, -4.93224f, 2.66804f, 175.995f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -73.2336f, -850.06f, 328.883f, -5.26397f, -0.0f, -177.431f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -70.4067f, -849.836f, 328.854f, -4.82287f, -5.33608f, -172.2f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -67.6252f, -849.166f, 328.911f, -5.26394f, -0.0f, -166.741f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -64.6525f, -848.331f, 328.792f, -4.82267f, -2.13443f, -160.74f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -62.1086f, -847.355f, 328.837f, -5.26389f, 2.13443f, -156.346f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -60.2755f, -846.895f, 328.808f, -5.97307f, -2.13443f, -151.031f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -58.5152f, -845.543f, 328.833f, -5.26392f, 1.06722f, -147.129f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -55.9339f, -843.258f, 328.987f, -5.26394f, 2.13443f, -141.8f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -53.6636f, -841.564f, 328.905f, -5.18348f, -0.0f, -136.192f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -51.8013f, -839.526f, 328.926f, -5.26393f, -2.13443f, -131.788f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -49.9112f, -837.51f, 328.916f, -5.18352f, -8.53774f, -125.894f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -48.5833f, -835.261f, 328.968f, -5.26388f, 2.13443f, -122.598f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -47.1369f, -832.806f, 328.936f, -5.18352f, -0.0f, -117.146f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -46.1092f, -830.019f, 328.985f, -5.26389f, -0.0f, -111.097f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -45.2549f, -827.659f, 328.957f, -5.18353f, -1.06722f, -105.915f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -44.5598f, -824.856f, 328.973f, -5.26387f, -0.0f, -101.582f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -44.0346f, -821.522f, 328.953f, -5.26387f, 5.33608f, -95.978f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -43.8673f, -817.92f, 328.98f, -5.26387f, -4.00206f, -88.1556f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -44.1983f, -815.072f, 328.956f, -5.26387f, -0.0f, -82.8806f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -45.0463f, -811.788f, 329.021f, -5.26392f, -0.0f, -77.2513f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -45.6154f, -809.566f, 328.95f, -5.25705f, -2.13443f, -72.2094f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -46.5685f, -807.149f, 328.929f, -5.26395f, -2.13443f, -66.9958f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -47.9752f, -804.122f, 328.959f, -5.26398f, -0.0f, -65.1505f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -49.0785f, -802.078f, 328.914f, -5.31539f, 4.26887f, -57.7224f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -50.5092f, -800.141f, 328.99f, -5.26406f, -0.0f, -52.4683f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -52.041f, -798.134f, 329.001f, -5.31536f, -2.13443f, -49.2493f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -53.8808f, -796.134f, 329.041f, -5.26389f, -0.0f, -42.3308f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -55.4375f, -794.682f, 329.045f, -5.32055f, 2.13443f, -37.3601f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -57.7537f, -794.2f, 329.16f, -5.26393f, 2.13443f, -32.2267f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -61.0299f, -792.042f, 329.172f, -5.26389f, -2.13443f, -32.1174f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -63.5163f, -790.736f, 329.085f, -5.04535f, -4.26887f, -29.2933f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -64.7324f, -789.882f, 329.081f, -4.987f, -2.13443f, -27.7917f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -66.7775f, -788.94f, 329.155f, -5.04558f, 1.06722f, -19.5666f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -68.6555f, -788.272f, 329.103f, -5.30654f, 3.20165f, -16.9146f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -70.8259f, -787.837f, 329.128f, -5.04546f, 1.06722f, -12.2941f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -74.5572f, -787.022f, 329.08f, -4.61724f, 1.06722f, -10.7316f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -75.8754f, -788.646f, 328.671f, -6.78921f, -0.0f, 2.98721f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -78.4f, -788.132f, 328.83f, -5.91899f, 2.66804f, 3.75875f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -80.5351f, -788.179f, 328.782f, -5.80051f, -0.0f, 7.26539f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -82.1189f, -788.558f, 328.793f, -5.9192f, 1.06722f, 12.7168f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -85.4054f, -789.317f, 328.666f, -5.79433f, -0.0f, 17.1877f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -87.4651f, -789.98f, 328.647f, -5.63204f, -0.0f, 20.2315f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -88.9795f, -790.697f, 328.76f, -5.79416f, -0.0f, 25.9501f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -90.9922f, -791.487f, 328.684f, -6.26149f, -0.0f, 27.0819f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -92.3298f, -792.474f, 328.677f, -5.79412f, -0.0f, 33.3113f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -94.2322f, -793.73f, 328.669f, -5.58479f, -2.13443f, 37.4974f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -95.7282f, -795.2f, 328.764f, -5.79431f, -0.0f, 41.8672f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -97.9782f, -797.316f, 328.695f, -5.58488f, -0.0f, 48.9171f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -100.042f, -800.063f, 328.731f, -5.79425f, 2.13443f, 53.7039f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -101.884f, -802.718f, 328.706f, -5.5848f, 2.13443f, 60.3613f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -103.09f, -805.421f, 328.718f, -5.79425f, -0.0f, 64.506f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -104.284f, -807.711f, 328.691f, -5.58488f, -2.13443f, 65.966f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -105.262f, -810.369f, 328.729f, -5.26384f, 1.06722f, 73.2414f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -105.769f, -812.146f, 328.645f, -5.25205f, -1.06722f, 75.8091f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -106.155f, -814.128f, 328.687f, -5.26388f, -1.06722f, 82.8157f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -106.062f, -817.685f, 328.758f, -5.26388f, 2.66804f, 88.7458f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -106.154f, -819.723f, 328.716f, -5.25204f, -0.0f, 90.1628f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -106.082f, -822.072f, 328.729f, -5.26387f, -1.33402f, 91.2972f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -105.911f, -823.815f, 328.7f, -5.52135f, 5.33608f, 99.4393f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -105.28f, -826.029f, 328.734f, -5.26391f, 1.06722f, 101.615f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -105.06f, -827.904f, 328.644f, -5.29978f, 1.06722f, 102.515f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -104.327f, -830.112f, 328.614f, -5.26391f, -2.13443f, 104.719f, -1, 0);
				Features::PlaceObjectByHash(3291218330, -108.551f, -853.416f, 327.387f, 2.94456f, 89.1111f, -166.155f, -1, 0);
				Features::PlaceObjectByHash(3291218330, -80.2509f, -866.418f, 327.301f, 3.7405f, 89.3f, 146.641f, -1, 0);
				Features::PlaceObjectByHash(3291218330, -55.8513f, -863.921f, 327.333f, 6.87468f, 89.6184f, 149.776f, -1, 0);
				Features::PlaceObjectByHash(3291218330, -37.3907f, -848.122f, 327.717f, 2.33633f, 88.8797f, -16.2595f, -1, 0);
				Features::PlaceObjectByHash(3291218330, -26.1908f, -818.332f, 328.76f, 0.490556f, 84.6598f, -18.107f, -1, 0);
				Features::PlaceObjectByHash(3291218330, -37.891f, -789.138f, 328.134f, 1.11673f, 87.6571f, 42.7186f, -1, 0);
				Features::PlaceObjectByHash(3291218330, -63.492f, -772.044f, 327.866f, 3.09962f, 89.1556f, 44.702f, -1, 0);
				Features::PlaceObjectByHash(3291218330, -93.4916f, -774.848f, 327.398f, 2.73771f, 89.0443f, 122.539f, -1, 0);
				Features::PlaceObjectByHash(3291218330, -115.991f, -795.259f, 327.27f, 3.28432f, 89.2033f, 123.086f, -1, 0);
				Features::PlaceObjectByHash(3291218330, -122.551f, -825.074f, 327.213f, 173.37f, 89.6048f, 4.27077f, -1, 0);
				Features::PlaceObjectByHash(118627012, -74.8438f, -819.617f, 323.685f, 0.0f, 0.0f, -3.37511f, -1, 0);
				Features::PlaceObjectByHash(2475986526, -67.6253f, -820.244f, 323.793f, -14.4263f, -8.53774f, -100.02f, -1, 0);
			}
			if (GUI::Option("Teleport")) {
				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -74.94243f, -818.63446f, 326.174347f, 1, 0, 0, 1);
			}
			break;

		case ramp2:
			GUI::Title("Maze Bank Roof Ramp");
			GUI::Subtitle("Maze Bank Roof Ramp");
			if (GUI::Option("Load")) {
				Features::PlaceObjectByHash(1600026313, -78.4864f, -807.943f, 323.202f, 109.364f, -89.9209f, 0.0f, -1, 1);
				Features::PlaceObjectByHash(1600026313, -79.2766f, -805.701f, 323.204f, 109.364f, -89.9209f, 0.0f, -1, 1);
				Features::PlaceObjectByHash(1600026313, -79.8373f, -803.709f, 323.205f, 109.364f, -89.9209f, 0.0f, -1, 1);
				Features::PlaceObjectByHash(1600026313, -80.4295f, -801.947f, 323.207f, 109.364f, -89.9209f, 0.0f, -1, 1);
				Features::PlaceObjectByHash(4143853297, -97.4731f, -778.557f, 308.877f, 0.0f, -0.0f, -159.831f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -84.2429f, -793.182f, 321.08f, -63.5625f, -0.0f, -160.249f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -83.5429f, -795.106f, 322.073f, -63.5625f, -0.0f, -160.249f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -84.9429f, -791.108f, 319.956f, -62.6673f, 8.53774e-007f, -160.249f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -85.8122f, -788.585f, 318.638f, -63.5625f, -0.0f, -160.249f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -89.1589f, -779.487f, 313.336f, -59.5389f, 0.0405551f, -160.567f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -90.7065f, -774.863f, 310.09f, -57.4959f, 0.322988f, -160.758f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -91.4887f, -772.564f, 308.403f, -55.1692f, 0.383369f, -161.049f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -91.7565f, -771.74f, 307.844f, -56.4466f, 0.0442451f, -160.565f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -93.6941f, -766.245f, 302.736f, -45.9996f, 0.0556114f, -160.556f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -94.2969f, -764.648f, 301.067f, -44.7623f, -1.70755e-006f, -159.354f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -94.2969f, -764.648f, 301.067f, -44.7623f, -1.70755e-006f, -159.354f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -94.886f, -762.996f, 298.741f, -36.7051f, -0.0f, -159.354f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -95.4855f, -761.334f, 296.406f, -36.7051f, -0.0f, -159.354f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -95.4855f, -761.334f, 296.406f, -36.7051f, -0.0f, -159.354f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -96.1606f, -759.499f, 294.259f, -42.0766f, -0.0f, -159.354f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -96.0707f, -759.689f, 293.709f, -36.7051f, -0.0f, -159.354f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -96.0707f, -759.689f, 293.709f, -36.7051f, -0.0f, -159.354f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -96.0707f, -759.689f, 293.46f, -36.7051f, -0.0f, -159.354f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -96.8807f, -757.391f, 292.506f, -51.0291f, -8.53774e-007f, -159.354f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -96.8807f, -757.391f, 292.506f, -51.0291f, -8.53774e-007f, -159.354f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -97.3203f, -756.159f, 291.688f, -57.2958f, -0.0f, -159.354f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -97.9597f, -754.358f, 290.78f, -62.6673f, 8.53774e-007f, -160.249f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -97.9597f, -754.358f, 290.78f, -62.6673f, 8.53774e-007f, -160.249f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -98.7192f, -752.356f, 290.042f, -69.9278f, 3.20165e-005f, -160.249f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -99.0244f, -751.684f, 290.499f, -90.0f, -8.46346e-007f, -160.249f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -99.3223f, -750.534f, 290.479f, -90.0f, -8.46346e-007f, -160.249f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -100.348f, -747.881f, 290.452f, -89.5256f, -1.33402e-008f, -159.354f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -100.26f, -748.154f, 290.462f, -76.096f, 4.26887e-007f, 19.6954f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -100.687f, -747.053f, 290.731f, -62.6673f, -8.53774e-007f, 20.5907f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -101.346f, -745.387f, 291.611f, -58.191f, 1.70755e-006f, 19.6954f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -102.234f, -743.119f, 293.091f, -52.2249f, 0.00051141f, 21.3426f, -1, 1);
				Features::PlaceObjectByHash(2475986526, -102.154f, -739.285f, 294.83f, 9.80014f, 0.295618f, 18.7802f, -1, 1);
				Features::PlaceObjectByHash(2475986526, -105.054f, -740.282f, 294.827f, 9.80014f, 0.295618f, 18.7802f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -103.071f, -741.047f, 294.832f, -48.0666f, 0.000519094f, 21.3419f, -1, 1);
				Features::PlaceObjectByHash(1087520462, -103.75f, -739.405f, 296.413f, -45.1472f, 0.000547269f, 21.3416f, -1, 1);
				Features::PlaceObjectByHash(4143853297, -90.3515f, -798.112f, 319.893f, 0.0f, -0.0f, -159.831f, -1, 1);
				Features::PlaceObjectByHash(4143853297, -93.2293f, -790.348f, 317.189f, 0.0f, -0.0f, -159.831f, -1, 1);
				Features::PlaceObjectByHash(4143853297, -95.3479f, -784.483f, 313.696f, 0.0f, -0.0f, -159.831f, -1, 1);
				Features::PlaceObjectByHash(4143853297, -100.01f, -771.31f, 304.367f, 0.0f, -0.0f, -159.831f, -1, 1);
				Features::PlaceObjectByHash(4143853297, -101.829f, -766.277f, 299.666f, 0.0f, -0.0f, -159.831f, -1, 1);
				Features::PlaceObjectByHash(4143853297, -103.318f, -762.175f, 293.966f, 0.0f, -0.0f, -159.831f, -1, 1);
				Features::PlaceObjectByHash(4143853297, -104.948f, -757.681f, 288.866f, 0.0f, -0.0f, -159.831f, -1, 1);
				Features::PlaceObjectByHash(4143853297, -108.146f, -748.798f, 288.866f, 0.0f, -0.0f, -159.831f, -1, 1);
				Features::PlaceObjectByHash(4143853297, -108.146f, -748.798f, 295.608f, 0.0f, -0.0f, -159.831f, -1, 1);
				Features::PlaceObjectByHash(4143853297, -108.225f, -748.694f, 302.608f, 0.0f, -0.0f, -159.831f, -1, 1);
				Features::PlaceObjectByHash(3167053133, -103.451f, -740.541f, 307.317f, -0.900199f, -1.19985f, 20.9076f, -1, 1);
				Features::PlaceObjectByHash(2375650849, -102.454f, -742.6f, 309.309f, 0.0f, 0.0f, 20.9393f, -1, 1);
				Features::PlaceObjectByHash(4143853297, -101.483f, -746.044f, 305.602f, 0.0f, -0.0f, -159.831f, -1, 1);
				Features::PlaceObjectByHash(4143853297, -94.7458f, -743.402f, 295.608f, 0.0f, -0.0f, -159.831f, -1, 1);
				Features::PlaceObjectByHash(4143853297, -94.7566f, -743.406f, 288.866f, 0.0f, -0.0f, -159.831f, -1, 1);
				Features::PlaceObjectByHash(4143853297, -94.7426f, -743.595f, 302.651f, 0.0f, -0.0f, -159.831f, -1, 1);
				Features::PlaceObjectByHash(1157292806, -99.7732f, -750.516f, 309.575f, 0.0f, 0.0f, 24.1761f, -1, 1);
				Features::PlaceObjectByHash(4143853297, -89.9785f, -756.476f, 293.966f, 0.0f, -0.0f, -159.831f, -1, 1);
				Features::PlaceObjectByHash(4143853297, -91.5378f, -752.285f, 288.866f, 0.0f, -0.0f, -159.831f, -1, 1);
				Features::PlaceObjectByHash(4143853297, -87.9094f, -762.07f, 299.666f, 0.0f, -0.0f, -159.831f, -1, 1);
				Features::PlaceObjectByHash(4143853297, -86.2094f, -766.939f, 304.367f, 0.0f, -0.0f, -159.831f, -1, 1);
				Features::PlaceObjectByHash(4143853297, -84.0215f, -772.971f, 309.575f, 0.0f, -0.0f, -159.831f, -1, 1);
				Features::PlaceObjectByHash(4143853297, -81.6733f, -779.348f, 313.696f, 0.0f, -0.0f, -159.831f, -1, 1);
				Features::PlaceObjectByHash(4143853297, -79.5187f, -785.083f, 317.189f, 0.0f, -0.0f, -159.831f, -1, 1);
				Features::PlaceObjectByHash(4143853297, -76.5616f, -793.191f, 319.493f, 0.0f, -0.0f, -159.831f, -1, 1);
				Features::PlaceObjectByHash(1998517203, -81.0993f, -790.139f, 326.57f, 0.0f, 0.0f, -82.6177f, -1, 1);
				Features::PlaceObjectByHash(1998517203, -88.8988f, -792.911f, 326.95f, 0.0f, 0.0f, -82.6177f, -1, 1);
				Features::PlaceObjectByHash(803874239, -88.3376f, -794.173f, 327.042f, 0.0f, 0.0f, 31.5501f, -1, 1);
				Features::PlaceObjectByHash(803874239, -90.0376f, -795.174f, 327.262f, 0.0f, 0.0f, 31.5501f, -1, 1);
				Features::PlaceObjectByHash(803874239, -91.6375f, -796.175f, 327.482f, 0.0f, 0.0f, 31.5501f, -1, 1);
				Features::PlaceObjectByHash(803874239, -79.0283f, -791.31f, 326.763f, 0.0f, -0.0f, 100.953f, -1, 1);
				Features::PlaceObjectByHash(803874239, -76.8377f, -790.87f, 326.823f, 0.0f, -0.0f, 100.953f, -1, 1);
				Features::PlaceObjectByHash(803874239, -81.0088f, -791.22f, 326.713f, 0.0f, -0.0f, 100.953f, -1, 1);
			}
			if (GUI::Option("Teleport")) {
				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -74.94243f, -818.63446f, 326.174347f, 1, 0, 0, 1);
			}
			break;

		case ramp3:
			GUI::Title("Beach Ferris-Ramp");
			GUI::Subtitle("Beach Ferris-Ramp");
			if (GUI::Option("Load")) {
				Features::PlaceObjectByHash(1952396163, -1497.76f, -1113.84f, -3.08f, -90.0f, 6.14715e-007f, 165.792f, -1, 2);
				Features::PlaceObjectByHash(2475986526, -1461.92f, -1216.88f, 2.5836f, -2.3048f, -0.0f, -154.878f, -1, 2);
				Features::PlaceObjectByHash(3291218330, -1465.62f, -1217.64f, 18.0f, 166.516f, -5.12264e-006f, 24.1717f, -1, 2);
				Features::PlaceObjectByHash(3291218330, -1458.89f, -1214.4f, 18.0f, -38.4956f, 8.53774e-007f, -153.982f, -1, 2);
				Features::PlaceObjectByHash(2475986526, -1460.32f, -1219.97f, 4.3801f, 12.6953f, -0.0f, -154.878f, -1, 2);
				Features::PlaceObjectByHash(2475986526, -1457.0f, -1226.67f, 11.8772f, 31.7229f, -0.0f, -154.382f, -1, 2);
				Features::PlaceObjectByHash(2475986526, -1458.4f, -1223.77f, 7.9937f, 23.6001f, -0.0916355f, -154.918f, -1, 2);
				Features::PlaceObjectByHash(2475986526, -1456.4f, -1228.27f, 14.9608f, 48.674f, -0.0f, -153.982f, -1, 2);
				Features::PlaceObjectByHash(2475986526, -1456.0f, -1229.07f, 19.7441f, 68.6628f, -0.0f, -153.982f, -1, 2);
				Features::PlaceObjectByHash(2475986526, -1456.2f, -1228.47f, 24.8276f, 82.6252f, 3.80938f, -152.828f, -1, 2);
				Features::PlaceObjectByHash(2475986526, -1456.9f, -1226.47f, 28.9111f, 108.498f, -8.51368f, -157.244f, -1, 2);
				Features::PlaceObjectByHash(2475986526, -1458.59f, -1223.37f, 31.5945f, 130.616f, -4.72983f, -155.087f, -1, 2);
				Features::PlaceObjectByHash(2475986526, -1460.59f, -1218.38f, 33.5779f, 143.744f, -3.95611f, -152.581f, -1, 2);
				Features::PlaceObjectByHash(2475986526, -1462.79f, -1214.28f, 34.161f, 163.63f, -2.68302f, -155.763f, -1, 2);
				Features::PlaceObjectByHash(2475986526, -1465.3f, -1209.78f, 32.5228f, -172.187f, 4.69576e-006f, -152.192f, -1, 2);
				Features::PlaceObjectByHash(2475986526, -1465.3f, -1209.78f, 32.5228f, -172.187f, 4.69576e-006f, -152.192f, -1, 2);
				Features::PlaceObjectByHash(2475986526, -1466.9f, -1205.68f, 29.0062f, -155.178f, 9.47689e-005f, -153.087f, -1, 2);
				Features::PlaceObjectByHash(2475986526, -1468.3f, -1202.98f, 24.1897f, -131.11f, 6.74481e-005f, -153.088f, -1, 2);
				Features::PlaceObjectByHash(2475986526, -1468.59f, -1202.68f, 19.3732f, -107.429f, 3.07358e-005f, -153.087f, -1, 2);
				Features::PlaceObjectByHash(2475986526, -1467.99f, -1203.88f, 13.5732f, -89.6528f, -0.153235f, -155.853f, -1, 2);
				Features::PlaceObjectByHash(2475986526, -1467.11f, -1205.68f, 10.7072f, -63.5491f, 8.53774e-007f, -156.504f, -1, 2);
				Features::PlaceObjectByHash(4109455646, -1465.05f, -1210.03f, 7.9503f, 9.53319f, 1.38057f, 24.2606f, -1, 2);
				Features::PlaceObjectByHash(2975320548, -1460.95f, -1218.79f, 7.66f, -29.9323f, -0.173323f, 24.7221f, -1, 2);
				Features::PlaceObjectByHash(2975320548, -1463.05f, -1214.19f, 6.7879f, -6.50192f, 1.391f, 24.2651f, -1, 2);
			}
			if (GUI::Option("Teleport")) {
				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -1513.0f, -1192.0f, 1.0f, 1, 0, 0, 1);
			}
			break;

		case ramp4:
			GUI::Title("Mount Chilliad Ramp");
			GUI::Subtitle("Mount Chilliad Ramp");
			if (GUI::Option("Load")) {
				Features::PlaceObjectByHash(1952396163, -1497.76f, -1113.84f, -3.08f, -90.0f, -0.0f, 165.792f, 90.0f, 3);
				Features::PlaceObjectByHash(2475986526, -1461.92f, -1216.88f, 2.5836f, -2.3048f, 0.0f, -154.878f, 205.14f, 3);
				Features::PlaceObjectByHash(3291218330, -1458.89f, -1214.4f, 18.0f, -38.4956f, 0.0f, -153.982f, 211.95f, 3);
				Features::PlaceObjectByHash(2475986526, -1460.32f, -1219.97f, 4.3801f, 12.6953f, 0.0f, -154.878f, 205.672f, 3);
				Features::PlaceObjectByHash(2975320548, -1463.05f, -1214.19f, 6.7879f, -6.5f, -1.391f, 24.2651f, 24.4244f, 3);
				Features::PlaceObjectByHash(3291218330, -1465.62f, -1217.64f, 18.0f, 166.516f, 180.0f, 24.1717f, 155.224f, 3);
				Features::PlaceObjectByHash(4109455646, -1465.05f, -1210.03f, 7.9503f, 9.5304f, -1.3806f, 24.2606f, 24.5148f, 3);
				Features::PlaceObjectByHash(2975320548, -1460.95f, -1218.79f, 7.66f, -29.9322f, 0.1733f, 24.7221f, 27.9617f, 3);
				Features::PlaceObjectByHash(2475986526, -1458.4f, -1223.77f, 7.9937f, 23.6001f, 0.0916f, -154.918f, 207.065f, 3);
				Features::PlaceObjectByHash(2475986526, -1467.11f, -1205.68f, 10.7072f, -63.5491f, 0.0f, -156.505f, 224.303f, 3);
				Features::PlaceObjectByHash(2475986526, -1457.0f, -1226.67f, 11.8772f, 31.7229f, 0.0f, -154.382f, 209.411f, 3);
				Features::PlaceObjectByHash(2475986526, -1456.4f, -1228.27f, 14.9608f, 48.674f, 0.0f, -153.982f, 216.471f, 3);
				Features::PlaceObjectByHash(2475986526, -1456.0f, -1229.07f, 19.7441f, 68.6628f, 0.0f, -153.982f, 233.298f, 3);
				Features::PlaceObjectByHash(2475986526, -1456.2f, -1228.47f, 24.8276f, 81.7043f, -3.8094f, -152.828f, 252.429f, 3);
				Features::PlaceObjectByHash(2475986526, -1456.9f, -1226.47f, 28.9111f, 110.301f, 171.486f, -157.244f, 312.201f, 3);
				Features::PlaceObjectByHash(2475986526, -1458.59f, -1223.37f, 31.5945f, 130.843f, 175.27f, -155.087f, 325.759f, 3);
				Features::PlaceObjectByHash(2475986526, -1460.59f, -1218.38f, 33.5779f, 143.844f, 176.044f, -152.581f, 327.979f, 3);
				Features::PlaceObjectByHash(2475986526, -1462.79f, -1214.28f, 34.161f, 163.648f, 177.317f, -155.763f, 335.024f, 3);
				Features::PlaceObjectByHash(2475986526, -1465.3f, -1209.78f, 32.5228f, -172.187f, -180.0f, -152.192f, 331.971f, 3);
				Features::PlaceObjectByHash(2475986526, -1466.9f, -1205.68f, 29.0062f, -155.178f, -180.0f, -153.087f, 330.783f, 3);
				Features::PlaceObjectByHash(2475986526, -1468.3f, -1202.98f, 24.1897f, -131.11f, -180.0f, -153.088f, 322.332f, 3);
				Features::PlaceObjectByHash(2475986526, -1468.59f, -1202.68f, 19.3732f, -107.429f, -180.0f, -153.087f, 300.544f, 3);
				Features::PlaceObjectByHash(2475986526, -1467.99f, -1203.88f, 13.5732f, -89.6205f, 0.1532f, -155.853f, 269.072f, 3);
				Features::PlaceObjectByHash(3966705493, 509.842f, 5589.24f, 791.066f, 0.141f, 0.0f, 65.3998f, 65.3999f, 3);
				Features::PlaceObjectByHash(3966705493, 520.5f, 5584.38f, 790.503f, 5.441f, 0.0f, 65.3998f, 65.4976f, 3);
				Features::PlaceObjectByHash(3966705493, 531.057f, 5579.54f, 788.691f, 12.441f, 0.0f, 65.3998f, 65.9111f, 3);
				Features::PlaceObjectByHash(3966705493, 568.672f, 5562.32f, 767.428f, 40.7396f, 0.0f, 65.3998f, 70.8685f, 3);
				Features::PlaceObjectByHash(3966705493, 576.972f, 5558.53f, 759.566f, 40.7396f, 0.0f, 65.3998f, 70.8685f, 3);
				Features::PlaceObjectByHash(3966705493, 560.174f, 5566.2f, 774.698f, 35.0403f, 0.0f, 65.3998f, 69.4512f, 3);
				Features::PlaceObjectByHash(3966705493, 541.325f, 5574.84f, 785.49f, 19.4409f, 0.0f, 65.3998f, 66.6484f, 3);
				Features::PlaceObjectByHash(3966705493, 551.066f, 5570.37f, 780.799f, 27.5407f, 0.0f, 65.3998f, 67.9049f, 3);
				Features::PlaceObjectByHash(3966705493, 585.249f, 5554.75f, 751.745f, 40.7396f, 0.0f, 65.3998f, 70.8685f, 3);
				Features::PlaceObjectByHash(3966705493, 618.334f, 5539.62f, 720.386f, 40.7936f, 0.0f, 65.3998f, 70.8829f, 3);
				Features::PlaceObjectByHash(3966705493, 626.602f, 5535.85f, 712.547f, 40.7396f, 0.0f, 65.3998f, 70.8685f, 3);
				Features::PlaceObjectByHash(3966705493, 610.065f, 5543.4f, 728.217f, 40.7396f, 0.0f, 65.3998f, 70.8685f, 3);
				Features::PlaceObjectByHash(3966705493, 601.777f, 5547.19f, 736.076f, 40.7396f, 0.0f, 65.3998f, 70.8685f, 3);
				Features::PlaceObjectByHash(3966705493, 593.507f, 5550.97f, 743.917f, 40.7396f, 0.0f, 65.3998f, 70.8685f, 3);
				Features::PlaceObjectByHash(3966705493, 634.862f, 5532.07f, 704.725f, 40.7396f, 0.0f, 65.3998f, 70.8685f, 3);
				Features::PlaceObjectByHash(3966705493, 643.121f, 5528.29f, 696.894f, 40.7936f, 0.0f, 65.3998f, 70.8829f, 3);
				Features::PlaceObjectByHash(3966705493, 651.391f, 5524.51f, 689.053f, 40.7396f, 0.0f, 65.3998f, 70.8685f, 3);
				Features::PlaceObjectByHash(3966705493, 659.651f, 5520.73f, 681.221f, 40.7396f, 0.0f, 65.3998f, 70.8685f, 3);
				Features::PlaceObjectByHash(3966705493, 667.911f, 5516.94f, 673.389f, 40.7396f, 0.0f, 65.3998f, 70.8685f, 3);
				Features::PlaceObjectByHash(3966705493, 676.171f, 5513.17f, 665.558f, 40.7396f, 0.0f, 65.3998f, 70.8685f, 3);
				Features::PlaceObjectByHash(3966705493, 684.431f, 5509.38f, 657.727f, 40.7396f, 0.0f, 65.3998f, 70.8685f, 3);
				Features::PlaceObjectByHash(3966705493, 692.691f, 5505.61f, 649.905f, 40.7396f, 0.0f, 65.3998f, 70.8685f, 3);
				Features::PlaceObjectByHash(3966705493, 700.95f, 5501.83f, 642.074f, 40.7396f, 0.0f, 65.3998f, 70.8685f, 3);
				Features::PlaceObjectByHash(3966705493, 709.22f, 5498.05f, 634.243f, 40.7396f, 0.0f, 65.3998f, 70.8685f, 3);
				Features::PlaceObjectByHash(3966705493, 717.46f, 5494.28f, 626.431f, 40.7396f, 0.0f, 65.3998f, 70.8685f, 3);
				Features::PlaceObjectByHash(3966705493, 725.72f, 5490.5f, 618.6f, 40.7396f, 0.0f, 65.3998f, 70.8685f, 3);
				Features::PlaceObjectByHash(3966705493, 733.98f, 5486.72f, 610.778f, 40.7396f, 0.0f, 65.3998f, 70.8685f, 3);
				Features::PlaceObjectByHash(3966705493, 742.6f, 5482.78f, 603.167f, 36.9395f, 0.0f, 65.3998f, 69.9005f, 3);
				Features::PlaceObjectByHash(3966705493, 751.83f, 5478.55f, 596.335f, 31.0392f, 0.0f, 65.3998f, 68.5807f, 3);
				Features::PlaceObjectByHash(3966705493, 761.71f, 5474.02f, 590.613f, 24.5989f, 0.0f, 65.3998f, 67.3986f, 3);
				Features::PlaceObjectByHash(3966705493, 772.07f, 5469.28f, 586.08f, 18.9288f, 0.0f, 65.3998f, 66.5835f, 3);
				Features::PlaceObjectByHash(3966705493, 782.84f, 5464.34f, 582.86f, 11.5788f, 0.0f, 65.3998f, 65.8427f, 3);
				Features::PlaceObjectByHash(3966705493, 793.89f, 5459.28f, 581.117f, 5.0787f, 0.0f, 65.3998f, 65.485f, 3);
				Features::PlaceObjectByHash(3966705493, 805.1f, 5454.15f, 580.876f, -2.5212f, 0.0f, 65.3998f, 65.4208f, 3);
				Features::PlaceObjectByHash(3966705493, 816.17f, 5449.08f, 581.975f, -7.6213f, 0.0f, 65.3998f, 65.5917f, 3);
				Features::PlaceObjectByHash(3966705493, 827.191f, 5444.04f, 584.582f, -16.6212f, 0.0f, 65.3998f, 66.3125f, 3);
				Features::PlaceObjectByHash(3966705493, 837.681f, 5439.24f, 588.899f, -24.421f, 0.0f, 65.3998f, 67.3698f, 3);
				Features::PlaceObjectByHash(2580877897, 522.61f, 5584.49f, 779.214f, 79.7153f, -9.2252f, 55.7018f, 77.7612f, 3);
				Features::PlaceObjectByHash(3862788492, 522.445f, 5583.69f, 779.551f, -0.9197f, -69.229f, -167.468f, 184.555f, 3);
			}
			if (GUI::Option("Teleport")) {
				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 500.0f, 5593.0f, 795.0f, 1, 0, 0, 1);
			}

			break;

		case ramp5:
			GUI::Title("Airport Mini Ramp");
			GUI::Subtitle("Airport Mini Ramp");
			if (GUI::Option("Load")) {
				Features::PlaceObjectByHash(2475986526, -1242.08f, -2931.15f, 12.9924f, -0.1046f, -3.33505e-009f, 61.0607f, -1, 4);
				Features::PlaceObjectByHash(2475986526, -1247.11f, -2928.46f, 15.013f, -0.1046f, -3.33505e-009f, 61.0607f, -1, 4);
				Features::PlaceObjectByHash(2475986526, -1251.58f, -2926.05f, 16.7865f, -0.1046f, -3.33505e-009f, 61.0607f, -1, 4);
				Features::PlaceObjectByHash(2475986526, -1254.69f, -2924.35f, 18.25f, -0.1046f, -3.33505e-009f, 61.0607f, -1, 4);
				Features::PlaceObjectByHash(3966705493, -1276.69f, -2912.99f, 23.0019f, 0.0f, 0.05f, 60.9705f, -1, 4);
				Features::PlaceObjectByHash(2475986526, -1258.35f, -2922.28f, 20.2135f, -0.1046f, -3.33505e-009f, 61.0607f, -1, 4);
				Features::PlaceObjectByHash(3966705493, -1270.89f, -2916.22f, 23.0123f, 0.0f, 0.0f, 60.8909f, -1, 4);
				Features::PlaceObjectByHash(3966705493, -1270.25f, -2914.99f, 23.0137f, 0.0f, 0.0f, 60.8909f, -1, 4);
				Features::PlaceObjectByHash(3966705493, -1274.87f, -2909.4f, 23.0049f, 0.0f, 0.05f, 60.9705f, -1, 4);
				Features::PlaceObjectByHash(3966705493, -1269.01f, -2912.64f, 22.9993f, 0.0f, 0.05f, 60.9705f, -1, 4);
				Features::PlaceObjectByHash(3966705493, -1267.87f, -2915.44f, 28.3632f, 0.0f, -0.0f, 147.299f, -1, 4);
				Features::PlaceObjectByHash(3966705493, -1272.13f, -2918.33f, 28.4791f, 0.0f, 0.05f, 60.9705f, -1, 4);
				Features::PlaceObjectByHash(3966705493, -1272.11f, -2918.35f, 25.6708f, -0.48f, 0.0499982f, 60.9701f, -1, 4);
				Features::PlaceObjectByHash(3966705493, -1277.93f, -2915.14f, 25.604f, 0.0f, 0.05f, 60.9705f, -1, 4);
				Features::PlaceObjectByHash(3966705493, -1279.69f, -2909.85f, 25.6358f, 0.0f, -0.0f, -151.239f, -1, 4);
				Features::PlaceObjectByHash(3966705493, -1279.69f, -2909.85f, 28.4844f, 0.0f, -0.0f, -151.239f, -1, 4);
				Features::PlaceObjectByHash(2475986526, -1261.82f, -2920.38f, 21.767f, -0.1046f, -3.33505e-009f, 61.0607f, -1, 4);
				Features::PlaceObjectByHash(3966705493, -1273.65f, -2907.11f, 22.9763f, 0.0f, 0.05f, 60.9705f, -1, 4);
				Features::PlaceObjectByHash(3966705493, -1267.77f, -2910.37f, 22.9978f, 0.0f, 0.05f, 60.9705f, -1, 4);
				Features::PlaceObjectByHash(3966705493, -1266.49f, -2908.08f, 22.9987f, 0.0f, -0.0f, -119.462f, -1, 4);
				Features::PlaceObjectByHash(3966705493, -1265.15f, -2905.8f, 23.0042f, 0.0f, -0.0f, -119.462f, -1, 4);
				Features::PlaceObjectByHash(3966705493, -1266.44f, -2905.21f, 25.6255f, 0.0f, -0.0f, -118.761f, -1, 4);
				Features::PlaceObjectByHash(3966705493, -1265.66f, -2911.99f, 25.6968f, 0.0f, 0.0f, -30.9603f, -1, 4);
				Features::PlaceObjectByHash(3966705493, -1264.88f, -2910.66f, 25.6982f, 0.0f, 0.0f, -30.9603f, -1, 4);
				Features::PlaceObjectByHash(3966705493, -1264.84f, -2905.14f, 25.624f, 0.0f, -0.0f, -118.761f, -1, 4);
				Features::PlaceObjectByHash(3966705493, -1272.37f, -2900.96f, 25.6199f, 0.0f, -0.0f, -118.761f, -1, 4);
				Features::PlaceObjectByHash(3966705493, -1276.35f, -2903.91f, 25.6214f, 0.0f, -0.0f, -151.239f, -1, 4);
				Features::PlaceObjectByHash(3966705493, -1276.35f, -2903.91f, 28.4329f, 0.0f, -0.0f, -151.239f, -1, 4);
				Features::PlaceObjectByHash(3966705493, -1272.37f, -2900.96f, 28.4385f, 0.0f, -0.0f, -118.761f, -1, 4);
				Features::PlaceObjectByHash(3966705493, -1266.44f, -2905.21f, 28.437f, 0.0f, -0.0f, -118.761f, -1, 4);
				Features::PlaceObjectByHash(3966705493, -1265.17f, -2905.14f, 28.3426f, 0.0f, -0.0f, -118.861f, -1, 4);
				Features::PlaceObjectByHash(3966705493, -1271.09f, -2902.58f, 23.0057f, 0.0f, -0.0f, -119.462f, -1, 4);
				Features::PlaceObjectByHash(3966705493, -1272.37f, -2904.83f, 22.9972f, 0.0f, -0.0f, -119.462f, -1, 4);
			}
			if (GUI::Option("Teleport")) {
				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -1208.0f, -2950.0f, 13.0f, 1, 0, 0, 1);
			}

			break;

		case ramp6:
			GUI::Title("Airport Gate Ramp");
			GUI::Subtitle("Airport Gate Ramp");
			if (GUI::Option("Load")) {
				Features::PlaceObjectByHash(2475986526, -1098.36f, -2631.17f, 19.0f, 0.0f, -0.0f, 152.671f, -1, 5);
				Features::PlaceObjectByHash(2475986526, -1100.26f, -2634.64f, 21.1976f, 16.2002f, 0.192059f, 150.427f, -1, 5);
				Features::PlaceObjectByHash(2475986526, -1102.26f, -2638.02f, 25.01f, 26.7003f, 0.178675f, 149.261f, -1, 5);
				Features::PlaceObjectByHash(2475986526, -1103.96f, -2640.91f, 29.04f, 28.3717f, -0.0f, 146.82f, -1, 5);
				Features::PlaceObjectByHash(1952396163, -1119.61f, -2670.96f, -5.125f, 0.0f, -0.0f, 150.514f, -1, 5);
				Features::PlaceObjectByHash(1952396163, -1119.61f, -2670.96f, -5.125f, 0.0f, -0.0f, 150.401f, -1, 5);
				Features::PlaceObjectByHash(3137065507, -1044.69f, -2530.08f, 20.4011f, 94.8962f, 4.26887e-007f, 147.716f, -1, 5);
			}
			if (GUI::Option("Teleport")) {
				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -1046.0f, -2538.0f, 20.0f, 1, 0, 0, 1);
			}

			break;

		case ramp7:
			GUI::Title("UFO Tower");
			GUI::Subtitle("UFO Tower");
			if (GUI::Option("Load")) {
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 654.365f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 646.186f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 638.008f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 629.829f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 621.65f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 613.471f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 605.292f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 597.114f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 588.935f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 580.756f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 572.577f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 564.399f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 556.22f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 662.544f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 548.041f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 539.862f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 531.683f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 523.505f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 515.326f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 507.147f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 498.968f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 490.79f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 482.611f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 474.432f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 466.253f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 458.074f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 449.896f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 441.717f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 433.538f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 425.359f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 417.18f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 409.001f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 400.823f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 392.644f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 384.465f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 376.286f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 368.107f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 359.929f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 351.75f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 343.571f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 335.392f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 327.213f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 319.035f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 310.856f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 302.677f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 294.498f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 286.319f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 278.141f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 269.962f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 261.783f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 253.604f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 245.425f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 237.247f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 229.068f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 220.889f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 212.71f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 204.531f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 196.353f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 188.174f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 179.995f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 171.816f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 163.637f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 155.459f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 147.28f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 139.101f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 130.922f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 122.743f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 114.565f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 106.386f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 98.207f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 90.0282f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 81.8494f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 73.6706f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 65.4918f, 0.660085f, -0.919939f, -109.32f, -1, 6);
				Features::PlaceObjectByHash(3026699584, 70.2592f, -674.044f, 57.313f, 0.660085f, -0.919939f, -109.32f, -1, 6);
			}
			if (GUI::Option("Teleport")) {
				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 70.0f, -674.0f, 680.0f, 1, 0, 0, 1);
			}
			break;

		case ramp8:
			GUI::Title("Maze Bank Quad Ramp");
			GUI::Subtitle("Maze Bank Quad Ramp");
			if (GUI::Option("Load")) {
				Features::PlaceObjectByHash(3522933110, -81.3886f, -814.648f, 325.169f, 0.0f, -0.0f, 180.0f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -81.7456f, -809.064f, 324.799f, 0.500021f, 2.66804f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -86.1333f, -802.279f, 321.92f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -89.7406f, -796.701f, 316.539f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -93.601f, -790.725f, 310.777f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -97.4741f, -784.73f, 304.997f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -101.373f, -778.696f, 299.179f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -105.233f, -772.72f, 293.417f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -109.106f, -766.725f, 287.637f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -112.954f, -760.769f, 281.894f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -116.827f, -754.773f, 276.113f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -120.687f, -748.798f, 270.352f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -124.518f, -742.868f, 264.636f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -128.358f, -736.925f, 258.909f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -132.22f, -730.949f, 253.151f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -136.081f, -724.974f, 247.394f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -139.943f, -718.998f, 241.636f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -143.826f, -712.99f, 235.846f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -147.667f, -707.047f, 230.12f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -151.508f, -701.104f, 224.394f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -155.369f, -695.128f, 218.636f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -159.252f, -689.12f, 212.846f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -163.072f, -683.209f, 207.152f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -166.976f, -677.168f, 201.331f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -170.838f, -671.193f, 195.573f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -174.7f, -665.217f, 189.815f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -178.583f, -659.209f, 184.026f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -182.444f, -653.233f, 178.268f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -186.327f, -647.225f, 172.479f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -190.189f, -641.249f, 166.721f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -194.03f, -635.306f, 160.994f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -197.871f, -629.363f, 155.268f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -201.711f, -623.42f, 149.542f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -205.552f, -617.477f, 143.815f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -209.393f, -611.534f, 138.089f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -213.255f, -605.559f, 132.331f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -217.095f, -599.616f, 126.605f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -220.957f, -593.64f, 120.847f, -38.9999f, -1.45141f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -222.245f, -591.648f, 118.928f, -33.8999f, 1.02453f, 32.8807f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -223.349f, -589.94f, 117.561f, -29.31f, 1.79292f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -224.58f, -588.036f, 116.288f, -26.25f, 5.12264f, 32.8807f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -225.869f, -586.04f, 115.116f, -24.7199f, -1.10991f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -227.127f, -584.095f, 114.05f, -21.6599f, 1.8783f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -228.615f, -581.794f, 112.961f, -19.6199f, 1.02453f, 32.8807f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -230.201f, -579.341f, 111.92f, -17.0699f, -0.0f, 32.8807f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -232.121f, -576.369f, 110.833f, -12.9899f, 4.26887f, 32.8808f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -234.105f, -573.302f, 109.991f, -9.9299f, -2.98821f, 32.8807f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -236.628f, -569.396f, 109.329f, -7.3799f, -4.26887f, 32.8807f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -239.81f, -564.475f, 108.721f, -4.3199f, 1.28066f, 32.8807f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -241.76f, -561.459f, 108.549f, -0.7499f, -1.12058f, 32.8807f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -244.04f, -557.932f, 108.494f, 2.82011f, -2.77476f, 32.8807f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -246.372f, -554.326f, 108.705f, 5.8801f, -2.77476f, 32.8807f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -248.668f, -550.777f, 109.14f, 10.4701f, 8.96462f, 32.8806f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -251.664f, -546.138f, 110.313f, 13.5301f, 1.15259f, 32.8806f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -254.537f, -541.694f, 111.791f, 16.5901f, 4.26887f, 32.8807f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -256.28f, -538.999f, 112.748f, 19.6501f, -1.19528f, 32.8807f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -65.9078f, -814.752f, 326.106f, 19.89f, 4.26887f, -53.8105f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -58.6541f, -809.444f, 327.336f, -4.08004f, -2.13443f, -53.8103f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -52.4476f, -804.909f, 323.715f, -45.3899f, 2.56132f, -53.8101f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -47.2332f, -801.09f, 317.168f, -45.3899f, 2.56132f, -53.8101f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -42.0187f, -797.272f, 310.621f, -45.3899f, 2.56132f, -53.8101f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -36.8326f, -793.474f, 304.109f, -45.3899f, 2.56132f, -53.8101f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -31.5898f, -789.635f, 297.526f, -45.3899f, 2.56132f, -53.8101f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -26.4037f, -785.838f, 291.014f, -45.3899f, 2.56132f, -53.8101f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -21.1893f, -782.019f, 284.467f, -45.3899f, 2.56132f, -53.8101f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -15.9748f, -778.201f, 277.919f, -45.3899f, 2.56132f, -53.8101f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -10.7604f, -774.383f, 271.372f, -45.3899f, 2.56132f, -53.8101f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -5.57426f, -770.585f, 264.86f, -45.3899f, 2.56132f, -53.8101f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -0.359839f, -766.767f, 258.313f, -45.3899f, 2.56132f, -53.8101f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 4.82623f, -762.969f, 251.799f, -45.3899f, 2.56132f, -53.8101f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 10.0123f, -759.171f, 245.285f, -45.3899f, 2.56132f, -53.8101f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 15.2268f, -755.353f, 238.735f, -45.3899f, 2.56132f, -53.8101f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 20.4412f, -751.535f, 232.184f, -45.3899f, 2.56132f, -53.8101f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 25.6273f, -747.737f, 225.67f, -45.3899f, 2.56132f, -53.8101f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 30.8135f, -743.939f, 219.155f, -45.3899f, 2.56132f, -53.8101f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 36.0279f, -740.121f, 212.605f, -45.3899f, 2.56132f, -53.8101f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 41.214f, -736.323f, 206.091f, -45.3899f, 2.56132f, -53.8101f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 46.4285f, -732.505f, 199.54f, -45.3899f, 2.56132f, -53.8101f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 48.4122f, -731.052f, 197.049f, -41.8198f, 1.62217f, -53.8101f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 49.5549f, -730.218f, 195.782f, -38.2499f, 3.24434f, -53.8101f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 51.171f, -729.035f, 194.203f, -36.2098f, 2.39057f, -53.81f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 52.8966f, -727.773f, 192.637f, -33.1499f, -6.83019f, -53.8101f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 54.586f, -726.537f, 191.27f, -30.0898f, 8.70849f, -53.8099f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 56.5413f, -725.105f, 189.866f, -25.4998f, 7.59859f, -53.8099f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 58.8359f, -723.425f, 188.509f, -22.4398f, 4.26887f, -53.81f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 60.738f, -722.033f, 187.536f, -18.3599f, 1.10991f, -53.81f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 63.1509f, -720.268f, 186.544f, -15.8098f, 5.03727f, -53.8099f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 65.131f, -718.821f, 185.849f, -12.7498f, 5.07995f, -53.8099f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 67.1384f, -717.352f, 185.286f, -9.17981f, 4.78113f, -53.81f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 69.2894f, -715.776f, 184.855f, -4.5898f, 4.18349f, -53.8099f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 71.7831f, -713.952f, 184.607f, 0.000193536f, 4.16213f, -53.8099f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 74.0832f, -712.268f, 184.607f, 3.06019f, 3.7566f, -53.81f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 76.0175f, -710.853f, 184.736f, 8.1602f, 4.35424f, -53.81f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 77.7752f, -709.567f, 185.048f, 13.2602f, 5.50684f, -53.81f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 79.6997f, -708.158f, 185.61f, 17.3402f, 3.7566f, -53.8099f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 81.3947f, -706.918f, 186.266f, 21.9302f, 4.26887f, -53.81f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 83.3036f, -705.52f, 187.219f, 26.0102f, 9.39151f, -53.8099f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 85.6244f, -703.821f, 188.622f, 29.0702f, 1.96368f, -53.8099f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 87.3526f, -702.556f, 189.812f, 33.1501f, 2.90283f, -53.8098f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 89.2107f, -701.196f, 191.316f, 37.2301f, 4.86651f, -53.8098f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 90.8492f, -699.998f, 192.859f, 41.82f, -2.56132f, -53.8099f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 92.6236f, -698.701f, 194.826f, 46.41f, 8.2816f, -53.8099f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 94.2096f, -697.539f, 196.89f, 52.0199f, 6.57406f, -53.8098f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 95.6251f, -696.503f, 199.137f, 56.61f, 9.22075f, -53.8097f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 96.9799f, -695.512f, 201.683f, 61.7098f, 8.53774f, -53.8097f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 98.1658f, -694.646f, 204.413f, 65.7899f, 5.03726f, -53.8096f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -69.0186f, -829.452f, 324.775f, 0.0f, -0.0f, -152.398f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -65.276f, -836.288f, 321.491f, -44.8796f, 3.24434f, -152.398f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -62.2554f, -842.061f, 315.0f, -44.8796f, 3.24434f, -152.398f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -59.2515f, -847.802f, 308.544f, -44.8796f, 3.24434f, -152.398f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -56.2313f, -853.574f, 302.053f, -44.8796f, 3.24434f, -152.398f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -53.1945f, -859.378f, 295.526f, -44.8796f, 3.24434f, -152.398f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -50.2071f, -865.088f, 289.106f, -44.8796f, 3.24434f, -152.398f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -47.2032f, -870.829f, 282.65f, -44.8796f, 3.24434f, -152.398f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -44.1829f, -876.602f, 276.159f, -44.8796f, 3.24434f, -152.398f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -41.1626f, -882.374f, 269.667f, -44.8796f, 3.24434f, -152.398f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -38.1751f, -888.084f, 263.247f, -44.8796f, 3.24434f, -152.398f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -35.1713f, -893.825f, 256.791f, -44.8796f, 3.24434f, -152.398f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -32.1674f, -899.566f, 250.335f, -44.8796f, 3.24434f, -152.398f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -29.1635f, -905.307f, 243.879f, -44.8796f, 3.24434f, -152.398f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -26.1432f, -911.079f, 237.388f, -44.8796f, 3.24434f, -152.398f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -23.1393f, -916.821f, 230.932f, -44.8796f, 3.24434f, -152.398f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -20.119f, -922.593f, 224.44f, -44.8796f, 3.24434f, -152.398f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -17.1152f, -928.334f, 217.985f, -44.8796f, 3.24434f, -152.398f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -14.1112f, -934.075f, 211.529f, -44.8796f, 3.24434f, -152.398f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -11.1235f, -939.785f, 205.108f, -44.8796f, 3.24434f, -152.398f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -8.13589f, -945.495f, 198.687f, -44.8796f, 3.24434f, -152.398f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -5.28891f, -951.101f, 192.102f, -47.4298f, -1.79292f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -2.35757f, -956.552f, 185.364f, -47.4298f, -1.79292f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 0.589775f, -962.033f, 178.59f, -47.4298f, -1.79292f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 3.5211f, -967.483f, 171.852f, -47.4298f, -1.79292f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 9.3998f, -978.414f, 158.339f, -47.4298f, -1.79292f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 6.46847f, -972.964f, 165.077f, -47.4298f, -1.79292f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 12.3311f, -983.865f, 151.601f, -47.4298f, -1.79292f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 15.2944f, -989.375f, 144.789f, -47.4298f, -1.79292f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 21.1569f, -1000.28f, 131.313f, -47.4298f, -1.79292f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 18.2417f, -994.856f, 138.014f, -47.4298f, -1.79292f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 24.0722f, -1005.7f, 124.612f, -47.4298f, -1.79292f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 27.0355f, -1011.21f, 117.801f, -47.4298f, -1.79292f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 29.9828f, -1016.69f, 111.026f, -47.4298f, -1.79292f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 35.8294f, -1027.56f, 97.5867f, -47.4298f, -1.79292f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 37.2241f, -1030.15f, 94.4555f, -44.3698f, -1.70754f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 38.7475f, -1032.99f, 91.3086f, -39.7798f, -4.26887f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 39.7483f, -1034.85f, 89.5491f, -36.7197f, 3.4151f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 40.9818f, -1037.14f, 87.6062f, -33.6597f, -2.21981f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 42.1248f, -1039.27f, 85.999f, -30.0898f, -1.96368f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 32.9141f, -1022.14f, 104.288f, -47.4298f, -1.79292f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 43.3132f, -1041.47f, 84.5449f, -26.5197f, -1.79293f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 44.7115f, -1044.08f, 83.0715f, -23.4597f, -2.39056f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 45.9496f, -1046.38f, 81.937f, -20.3997f, -2.47594f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 47.0815f, -1048.48f, 81.0483f, -17.3397f, -2.09174f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 48.302f, -1050.75f, 80.2436f, -14.7897f, -8.96462f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 50.0647f, -1054.03f, 79.2608f, -13.2597f, -2.77476f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 52.0238f, -1057.67f, 78.2861f, -11.7297f, -1.45141f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 53.7395f, -1060.86f, 77.5341f, -9.17973f, -1.1099f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 55.7265f, -1064.56f, 76.8558f, -6.11973f, -6.61674f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 57.3746f, -1067.62f, 76.4825f, -3.56972f, -9.60496f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 59.3125f, -1071.23f, 76.2272f, 0.000276446f, -9.05818f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 61.112f, -1074.58f, 76.2272f, 4.08028f, -8.00412f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 62.529f, -1077.21f, 76.4405f, 7.65027f, -7.04364f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 64.0779f, -1080.1f, 76.8796f, 10.7103f, -1.28066f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 65.9388f, -1083.55f, 77.623f, 14.2802f, -1.70755f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 67.4076f, -1086.29f, 78.4126f, 17.3403f, -1.57948f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, 68.7639f, -1088.81f, 79.3066f, 21.4202f, 1.36604f, -151.734f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -86.0915f, -825.576f, 324.775f, 0.0f, -0.0f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -99.1939f, -833.684f, 315.911f, -39.27f, -2.30519f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -105.248f, -837.511f, 310.056f, -39.27f, -2.30519f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -93.1729f, -829.876f, 321.734f, -39.27f, -2.30519f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -111.268f, -841.319f, 304.233f, -39.27f, -2.30519f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -123.245f, -848.891f, 292.651f, -39.27f, -2.30519f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -147.333f, -864.12f, 269.359f, -39.27f, -2.30519f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -141.278f, -860.292f, 275.213f, -39.27f, -2.30519f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -135.256f, -856.485f, 281.036f, -39.27f, -2.30519f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -129.266f, -852.699f, 286.828f, -39.27f, -2.30519f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -117.224f, -845.084f, 298.474f, -39.27f, -2.30519f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -165.367f, -875.521f, 251.921f, -39.27f, -2.30519f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -213.415f, -905.895f, 205.464f, -39.27f, -2.30519f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -207.426f, -902.108f, 211.255f, -39.27f, -2.30519f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -201.403f, -898.301f, 217.078f, -39.27f, -2.30519f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -195.414f, -894.515f, 222.87f, -39.27f, -2.30519f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -183.434f, -886.942f, 234.452f, -39.27f, -2.30519f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -177.445f, -883.156f, 240.244f, -39.27f, -2.30519f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -171.422f, -879.348f, 246.067f, -39.27f, -2.30519f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -159.378f, -871.734f, 257.713f, -39.27f, -2.30519f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -153.355f, -867.927f, 263.536f, -39.27f, -2.30519f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -189.424f, -890.728f, 228.661f, -39.27f, -2.30519f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -231.449f, -917.296f, 188.027f, -39.27f, -2.30519f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -225.46f, -913.509f, 193.818f, -39.27f, -2.30519f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -219.47f, -909.723f, 199.609f, -39.27f, -2.30519f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -237.439f, -921.082f, 182.235f, -39.27f, -2.30519f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -284.806f, -951.016f, 167.673f, 28.5601f, -7.5132f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -289.048f, -953.697f, 170.578f, 34.1701f, -3.41509f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -290.727f, -954.757f, 171.926f, 37.23f, 3.41509f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -286.998f, -952.399f, 169.084f, 31.62f, -1.36604f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -282.375f, -949.481f, 166.27f, 26.0101f, 3.50047f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -280.014f, -947.991f, 165.174f, 21.4201f, -6.83019f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -277.4f, -946.336f, 164.178f, 17.8501f, -3.15896f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -270.266f, -941.827f, 162.896f, 4.59013f, -1.79292f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -266.683f, -939.562f, 163.103f, -6.11989f, -1.38738f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -259.328f, -934.913f, 165.339f, -17.8499f, -4.69576f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -253.478f, -931.22f, 168.474f, -26.01f, -4.18349f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -248.103f, -927.823f, 172.247f, -33.66f, -5.97642f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -243.429f, -924.868f, 176.444f, -39.27f, -2.30519f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -256.593f, -933.187f, 166.676f, -22.4399f, -5.97641f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -262.183f, -936.72f, 164.252f, -14.2799f, -3.20165f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -268.321f, -940.597f, 162.896f, 0.000125527f, -1.95033f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -272.668f, -943.344f, 163.123f, 8.67012f, -2.86014f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -275.091f, -944.877f, 163.561f, 12.7501f, -5.1226f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -249.757f, -928.867f, 170.944f, -31.11f, -6.0617f, 122.286f, -1, 7);
				Features::PlaceObjectByHash(3681122061, -251.566f, -930.012f, 169.653f, -27.54f, -3.58585f, 122.286f, -1, 7);
			}
			if (GUI::Option("Teleport")) {
				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -74.94243f, -818.63446f, 326.174347f, 1, 0, 0, 1);
			}

			break;

		case ramp9:
			GUI::Title("Fort Zancudo Motorcross");
			GUI::Subtitle("Fort Zancudo Motorcross");
			if (GUI::Option("Load")) {
				Features::PlaceObjectByHash(3213433054, -2661.22f, 3209.43f, 32.7118f, 0.0f, -0.0f, -120.437f, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2657.86f, 3207.56f, 32.7118f, 0.0f, 0.0f, 59.6808f, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2659.52f, 3212.33f, 32.7118f, 0.0f, -0.0f, -120.437f, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2656.2f, 3210.41f, 32.7118f, 0.0f, 0.0f, 59.6808f, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2654.54f, 3213.26f, 32.7118f, 0.0f, 0.0f, 59.6808f, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2657.84f, 3215.18f, 32.7118f, 0.0f, -0.0f, -120.437f, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2615.14f, 3183.0f, 32.8118f, 0.0f, -0.0f, -120.45f, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2611.82f, 3181.02f, 32.8118f, 0.0f, 0.0f, 58.529f, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2613.47f, 3185.85f, 32.8118f, 0.0f, -0.0f, -120.45f, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2610.11f, 3183.91f, 32.8118f, 0.0f, 0.0f, 59.589f, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2611.79f, 3188.7f, 32.8118f, 0.0f, -0.0f, -120.45f, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2608.46f, 3186.71f, 32.8118f, 0.0f, 0.0f, 58.529f, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2550.83f, 3162.65f, 32.7702f, 0.0f, -0.0f, -117.989f, -1, 8);
				Features::PlaceObjectByHash(4109455646, -2547.01f, 3160.66f, 34.9496f, 11.66f, -2.56132e-006f, -118.95f, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2476.76f, 3120.72f, 32.7718f, 0.0f, -0.0f, -119.612f, -1, 8);
				Features::PlaceObjectByHash(4109455646, -2473.51f, 3118.83f, 34.5672f, 8.47412f, -0.0223369f, -120.965f, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2442.43f, 3105.7f, 35.6224f, -7.42001f, -5.12265e-006f, 150.074f, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2443.67f, 3101.83f, 35.8732f, -11.66f, 3.84198e-006f, 59.738f, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2438.8f, 3099.0f, 36.0155f, -11.66f, -6.40331e-006f, 59.7379f, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2434.05f, 3096.22f, 36.6871f, -22.26f, -1.45141e-005f, 59.7379f, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2446.85f, 3098.2f, 35.6088f, -7.42f, 3.20165e-006f, -31.8463f, -1, 8);
				Features::PlaceObjectByHash(2402097066, -2448.77f, 3097.65f, 35.4732f, 0.0f, -0.0f, -120.616f, -1, 8);
				Features::PlaceObjectByHash(2402097066, -2442.95f, 3108.08f, 35.4832f, 0.0f, -0.0f, -117.436f, -1, 8);
				Features::PlaceObjectByHash(2402097066, -2442.95f, 3108.08f, 35.4832f, 0.0f, -0.0f, -117.436f, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2389.55f, 3069.11f, 36.5952f, 179.801f, -3.76861e-006f, -117.806f, -1, 8);
				Features::PlaceObjectByHash(1982829832, -2363.33f, 3056.01f, 31.8257f, 0.0f, -0.0f, -119.219f, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2389.55f, 3069.11f, 36.5952f, 179.801f, -3.76861e-006f, -117.806f, -1, 8);
				Features::PlaceObjectByHash(2609922146, -2358.79f, 3060.59f, 31.8217f, 0.0f, -0.0f, -119.371f, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2325.93f, 3034.99f, 33.3214f, 19.8f, 3.41509e-006f, -120.09f, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2321.78f, 3032.58f, 36.3899f, 25.7399f, -8.62311e-005f, -120.09f, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2317.79f, 3030.29f, 39.6222f, 25.0799f, -6.23256e-005f, -120.09f, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2313.74f, 3027.94f, 42.9228f, 25.7399f, -8.62311e-005f, -120.09f, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2309.83f, 3025.69f, 46.2289f, 27.06f, -8.2816e-005f, -120.09f, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2306.07f, 3023.49f, 49.5919f, 29.0399f, -0.000116113f, -120.09f, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2283.14f, 3009.97f, 44.7284f, 14.12f, -2.04906e-005f, 60.0397f, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2287.5f, 3012.47f, 46.9591f, 13.6f, 0.680011f, 60.0397f, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2302.26f, 3021.28f, 53.174f, 29.6999f, -0.000100745f, -120.09f, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2292.06f, 3015.11f, 49.2546f, 13.6f, 1.53679e-005f, 60.0397f, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2298.56f, 3019.12f, 56.7472f, 30.36f, -8.79386e-005f, -120.09f, -1, 8);
				Features::PlaceObjectByHash(2052512905, -2294.52f, 3015.08f, 58.6366f, 82.6616f, 0.00430302f, -31.2919f, -1, 8);
				Features::PlaceObjectByHash(2052512905, -2293.13f, 3017.4f, 58.6822f, 80.9428f, 0.00560716f, 149.187f, -1, 8);
				Features::PlaceObjectByHash(2787492567, -2293.66f, 3016.58f, 31.8318f, -90.0f, 0.0833042f, 109.919f, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2202.78f, 2963.39f, 32.8003f, 0.0f, -0.0f, -120.04f, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2199.53f, 2961.53f, 34.17f, -40.5599f, -2.56132e-006f, 59.8803f, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2137.1f, 2904.97f, 32.8327f, 16.8f, -1.10991e-005f, -141.061f, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2132.27f, 2897.94f, 34.4465f, 16.8f, -14.0f, -141.061f, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2127.12f, 2890.88f, 36.4432f, 17.92f, -29.68f, -136.581f, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2119.98f, 2885.33f, 38.8379f, 17.92f, -29.68f, -136.581f, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2113.02f, 2880.0f, 41.2705f, 17.92f, -29.68f, -136.581f, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2085.18f, 2857.71f, 49.9177f, 19.04f, -43.12f, -136.581f, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2078.1f, 2852.44f, 51.662f, 19.0399f, -50.4001f, -136.581f, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2092.05f, 2863.54f, 48.2285f, 17.92f, -34.16f, -136.581f, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2098.91f, 2869.18f, 46.2053f, 17.92f, -29.68f, -136.581f, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2105.97f, 2874.59f, 43.7379f, 17.92f, -29.68f, -136.581f, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2070.42f, 2847.69f, 53.5814f, 19.0399f, -50.4001f, -136.581f, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2062.85f, 2843.01f, 55.4739f, 19.0399f, -50.4001f, -136.581f, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2055.32f, 2838.69f, 56.5097f, 17.7868f, -43.8868f, -131.905f, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2047.61f, 2834.88f, 58.9097f, 26.1867f, -43.8868f, -131.905f, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2039.74f, 2832.2f, 62.2769f, 38.5067f, -45.5668f, -131.905f, -1, 8);
				Features::PlaceObjectByHash(3681122061, -1996.98f, 2830.2f, 48.384f, 0.202822f, -14.4337f, -105.503f, -1, 8);
				Features::PlaceObjectByHash(3681122061, -1996.42f, 2832.89f, 59.0601f, -179.433f, 12.3451f, 76.9258f, -1, 8);
				Features::PlaceObjectByHash(3213433054, -1951.86f, 2849.63f, 34.5146f, -47.5199f, -7.59859e-005f, 59.6261f, -1, 8);
				Features::PlaceObjectByHash(3213433054, -1950.16f, 2852.52f, 34.5146f, -47.5199f, -7.59859e-005f, 59.6261f, -1, 8);
				Features::PlaceObjectByHash(3213433054, -1953.57f, 2854.49f, 32.8004f, 0.0f, -0.0f, -120.091f, -1, 8);
				Features::PlaceObjectByHash(3213433054, -1955.25f, 2851.59f, 32.8004f, 0.0f, -0.0f, -120.091f, -1, 8);
				Features::PlaceObjectByHash(4111834409, -1960.72f, 2857.38f, 31.7305f, 0.0f, -0.0f, -118.505f, -1, 8);
				Features::PlaceObjectByHash(4109455646, -2144.0f, 2967.21f, 36.0606f, 9.35852f, -0.00134085f, 59.8371f, -1, 8);
				Features::PlaceObjectByHash(4109455646, -2139.63f, 2964.67f, 33.9985f, 5.84852f, -0.0013321f, 59.8371f, -1, 8);
				Features::PlaceObjectByHash(4109455646, -2135.45f, 2962.3f, 32.4604f, 0.0f, 0.0f, 60.4792f, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2193.23f, 2995.21f, 35.0684f, 11.6996f, -0.00262322f, -119.238f, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2197.74f, 2997.74f, 32.8074f, 15.2099f, 2.04906e-005f, -119.328f, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2246.82f, 3026.19f, 33.0318f, 0.0331696f, 0.0056356f, 58.6423f, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2256.38f, 3032.02f, 35.4343f, 6.5707f, 0.0279573f, 58.7685f, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2265.19f, 3037.37f, 38.408f, 10.1262f, 0.0254109f, 58.7585f, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2273.45f, 3042.38f, 40.214f, 8.95404f, -0.00182451f, 58.7729f, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2281.36f, 3047.19f, 42.7382f, 8.89319f, 0.151422f, 58.8279f, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2289.41f, 3052.05f, 46.2871f, 13.2f, 0.000150264f, 58.7642f, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2397.86f, 3114.2f, 32.8449f, 0.0f, 0.0f, 60.2049f, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2402.38f, 3116.77f, 34.7648f, 0.0f, 0.0f, 60.2049f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2394.65f, 3118.07f, 32.5452f, 0.0f, 0.0f, 56.6241f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2397.73f, 3120.09f, 34.1452f, 2.04f, -1.38738e-006f, 56.6241f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2401.78f, 3122.77f, 36.6227f, 8.16f, 1.28066e-006f, 56.6239f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2405.48f, 3125.2f, 39.5571f, 14.28f, 1.02453e-005f, 56.6239f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2409.12f, 3127.6f, 43.2064f, 20.4f, -2.39057e-005f, 56.6239f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2412.29f, 3129.71f, 46.9494f, 24.4781f, -1.43125f, 56.2632f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2415.18f, 3131.49f, 51.529f, 38.3931f, -3.70399f, 55.299f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2416.96f, 3132.28f, 56.2986f, 54.0331f, -3.70398f, 53.2589f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2417.37f, 3132.16f, 61.6124f, 73.753f, -3.70394f, 53.2588f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2416.48f, 3131.04f, 66.996f, 90.9129f, -3.70395f, 53.2587f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2414.88f, 3129.5f, 70.998f, 104.113f, -3.70383f, 50.6186f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2412.46f, 3127.2f, 74.61f, 116.653f, -3.70392f, 50.6185f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2409.58f, 3124.71f, 77.6119f, 121.273f, -3.70395f, 50.6185f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2406.75f, 3122.18f, 80.0586f, 127.213f, -3.70391f, 50.6184f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2403.38f, 3119.23f, 82.2502f, 135.793f, -3.70396f, 50.6185f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2369.71f, 3092.81f, 68.2807f, -146.327f, -3.7039f, 50.6183f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2367.45f, 3091.4f, 63.3347f, -134.447f, -3.70392f, 50.6182f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2366.0f, 3090.66f, 58.0814f, -123.887f, -3.7039f, 50.6182f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2365.38f, 3090.57f, 53.1623f, -112.007f, -3.70391f, 50.6182f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2365.62f, 3091.18f, 48.0172f, -99.4666f, -3.70393f, 50.6181f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2366.77f, 3092.54f, 43.04f, -86.2661f, -3.70399f, 50.6181f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2368.73f, 3094.52f, 38.5669f, -74.386f, -3.70392f, 50.6181f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2371.25f, 3096.8f, 35.0692f, -59.206f, -3.70384f, 55.2379f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2375.18f, 3099.61f, 32.3997f, -42.0459f, -3.70387f, 57.2179f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2395.69f, 3112.77f, 84.6355f, 152.292f, -3.70389f, 50.6184f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2391.54f, 3109.37f, 84.6603f, 162.192f, -3.70393f, 50.6184f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2387.13f, 3105.84f, 83.6595f, 172.752f, -3.70391f, 50.6184f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2382.97f, 3102.56f, 81.8101f, -179.988f, -3.70391f, 50.6184f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2372.52f, 3094.76f, 72.6855f, -154.907f, -3.70391f, 50.6183f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2379.11f, 3099.59f, 79.371f, -172.728f, -3.70391f, 50.6183f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2375.46f, 3096.85f, 76.1692f, -162.168f, -3.70388f, 50.6182f, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2399.8f, 3116.19f, 83.7512f, 143.712f, -3.70387f, 50.6184f, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2510.73f, 3180.4f, 32.8111f, 0.0f, 0.0f, 59.4291f, -1, 8);
				Features::PlaceObjectByHash(209943352, -2302.92f, 3059.95f, 50.2208f, 76.8397f, -0.679965f, -120.716f, -1, 8);
				Features::PlaceObjectByHash(209943352, -2298.84f, 3057.5f, 48.7042f, 71.3997f, -0.679954f, -120.716f, -1, 8);
				Features::PlaceObjectByHash(209943352, -2290.6f, 3052.58f, 47.3498f, 84.3198f, -0.679946f, -120.716f, -1, 8);
				Features::PlaceObjectByHash(209943352, -2290.6f, 3052.58f, 47.3498f, 84.3198f, -0.679946f, -120.716f, -1, 8);
				Features::PlaceObjectByHash(209943352, -2294.73f, 3055.05f, 47.6692f, 76.8398f, -0.680059f, -120.716f, -1, 8);
				Features::PlaceObjectByHash(209943352, -2533.2f, 3193.91f, 37.3948f, 0.0f, -0.0f, -120.716f, -1, 8);
				Features::PlaceObjectByHash(209943352, -2533.2f, 3193.91f, 37.3948f, 0.0f, -0.0f, -120.716f, -1, 8);
				Features::PlaceObjectByHash(209943352, -2425.58f, 3091.36f, 36.493f, 0.0f, -0.0f, -120.716f, -1, 8);
				Features::PlaceObjectByHash(209943352, -2425.58f, 3091.36f, 36.493f, 0.0f, -0.0f, -120.716f, -1, 8);
				Features::PlaceObjectByHash(209943352, -2293.7f, 3012.65f, 55.3685f, -89.7587f, -0.659716f, -30.2946f, -1, 8);
				Features::PlaceObjectByHash(209943352, -2293.7f, 3012.65f, 55.3685f, -89.7587f, -0.659716f, -30.2946f, -1, 8);
			}
			if (GUI::Option("Teleport")) {
				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -2731, 3259, 32, 1, 0, 0, 1);
			}

			break;

		case ramp10:
			GUI::Title("Halfpipe Fun Track");
			GUI::Subtitle("Halfpipe Fun Track");
			if (GUI::Option("Load")) {
				Features::PlaceObjectByHash(3681122061, -1018.78f, -2937.26f, 12.9646f, 0.0f, 0.0f, -30.3132f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1023.38f, -2945.17f, 12.9646f, 0.0f, 0.0f, -30.3132f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1028.02f, -2953.13f, 12.9646f, 0.0f, 0.0f, -30.3132f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1032.66f, -2961.06f, 12.9646f, 0.0f, 0.0f, -30.3132f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1037.32f, -2969.04f, 12.9646f, 0.0f, 0.0f, -30.3132f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1041.95f, -2976.96f, 12.9646f, 0.0f, 0.0f, -30.3132f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1046.18f, -2984.19f, 12.9646f, 0.0f, 0.0f, -30.3132f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1050.78f, -2992.12f, 12.9646f, 0.0f, 0.0f, -29.8732f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1053.22f, -2998.13f, 12.9646f, 0.0f, 0.0f, -14.2534f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1054.14f, -3005.28f, 12.9646f, 0.0f, 0.0f, -0.613478f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1053.45f, -3012.85f, 12.9646f, 0.0f, 0.0f, 11.4866f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1051.19f, -3020.08f, 12.9646f, 0.0f, 0.0f, 23.3667f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1047.43f, -3026.73f, 12.9646f, 0.0f, 0.0f, 35.2469f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1042.42f, -3032.37f, 12.9646f, 0.0f, 0.0f, 47.7871f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1037.1f, -3038.16f, 12.9646f, 0.0f, 0.0f, 37.2273f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1033.11f, -3044.75f, 12.9646f, 0.0f, 0.0f, 25.5675f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1030.43f, -3052.11f, 12.9646f, 0.0f, 0.0f, 14.5676f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1029.18f, -3059.85f, 12.9646f, 0.0f, 0.0f, 4.00757f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1029.37f, -3067.7f, 12.9646f, 0.0f, 0.0f, -6.55247f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1031.0f, -3075.33f, 12.9646f, 0.0f, 0.0f, -17.5525f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1034.09f, -3082.35f, 12.9646f, 0.0f, 0.0f, -29.6525f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1038.6f, -3088.77f, 12.9646f, 0.0f, 0.0f, -40.2127f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1044.19f, -3094.15f, 12.9646f, 0.0f, 0.0f, -51.653f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1050.65f, -3098.2f, 12.9646f, 0.0f, 0.0f, -63.7531f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1057.89f, -3100.91f, 12.9646f, 0.0f, 0.0f, -75.1935f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1065.18f, -3101.87f, 12.9646f, 0.0f, 0.0f, -89.7139f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1073.03f, -3101.2f, 12.9646f, 0.0f, -0.0f, -100.054f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1080.63f, -3099.11f, 12.9646f, 0.0f, -0.0f, -110.615f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1087.92f, -3095.65f, 12.9646f, 0.0f, -0.0f, -119.855f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1095.95f, -3091.03f, 12.9646f, 0.0f, -0.0f, -119.855f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1104.01f, -3086.4f, 12.9646f, 0.0f, -0.0f, -119.855f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1112.04f, -3081.79f, 12.9646f, 0.0f, -0.0f, -119.855f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1120.04f, -3077.19f, 12.9646f, 0.0f, -0.0f, -119.855f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1128.1f, -3072.56f, 12.9646f, 0.0f, -0.0f, -119.855f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1136.15f, -3067.93f, 12.9646f, 0.0f, -0.0f, -119.855f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1144.2f, -3063.31f, 12.9646f, 0.0f, -0.0f, -119.855f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1152.22f, -3058.7f, 12.9646f, 0.0f, -0.0f, -119.855f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1160.24f, -3054.09f, 12.9646f, 0.0f, -0.0f, -119.855f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1168.22f, -3049.48f, 12.9646f, 0.0f, -0.0f, -120.295f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1176.21f, -3044.8f, 12.9646f, 0.0f, -0.0f, -120.295f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1183.28f, -3040.14f, 12.9646f, 0.0f, -0.0f, -126.455f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1189.23f, -3034.89f, 12.9646f, 0.0f, -0.0f, -136.356f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1193.86f, -3028.84f, 12.9646f, 0.0f, -0.0f, -148.677f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1197.2f, -3021.86f, 12.9646f, 0.0f, -0.0f, -159.898f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1198.78f, -3014.77f, 12.9646f, 0.0f, -0.0f, -174.639f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1198.72f, -3007.04f, 12.9646f, 0.0f, -0.0f, 173.701f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1197.0f, -2999.97f, 12.9646f, 0.0f, -0.0f, 158.962f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1193.5f, -2993.3f, 12.9646f, 0.0f, -0.0f, 145.982f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1188.51f, -2987.1f, 12.9646f, 0.0f, -0.0f, 136.083f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1182.5f, -2981.85f, 12.9646f, 0.0f, -0.0f, 126.183f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1175.98f, -2978.23f, 12.9646f, 0.0f, -0.0f, 112.104f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1168.67f, -2976.15f, 12.9646f, 0.0f, -0.0f, 99.7843f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1160.82f, -2975.53f, 12.9646f, 0.0f, 0.0f, 89.4449f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1152.93f, -2976.29f, 12.9646f, 0.0f, 0.0f, 79.5455f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1145.21f, -2978.39f, 12.9646f, 0.0f, 0.0f, 70.0859f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1138.14f, -2981.75f, 12.9646f, 0.0f, 0.0f, 59.0863f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1130.27f, -2986.43f, 12.9646f, 0.0f, 0.0f, 59.0863f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1122.46f, -2991.09f, 12.9646f, 0.0f, 0.0f, 59.0863f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1115.12f, -2994.75f, 12.9646f, 0.0f, 0.0f, 67.1435f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1107.63f, -2997.13f, 12.9646f, 0.0f, 0.0f, 76.9913f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1099.8f, -2998.14f, 12.9646f, 0.0f, 0.0f, 86.8389f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1091.94f, -2997.76f, 12.9646f, 0.0f, -0.0f, 97.5819f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1084.47f, -2995.95f, 12.9646f, 0.0f, -0.0f, 108.325f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1077.64f, -2992.78f, 12.9646f, 0.0f, -0.0f, 119.963f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1077.64f, -2992.78f, 12.9646f, 0.0f, -0.0f, 119.963f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1071.68f, -2988.3f, 12.9646f, 0.0f, -0.0f, 132.496f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1066.33f, -2982.53f, 12.9646f, 0.0f, -0.0f, 141.449f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1053.01f, -2960.01f, 12.9646f, 0.0f, 0.0f, -28.5532f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1048.58f, -2951.88f, 12.9646f, 0.0f, 0.0f, -28.5532f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1044.16f, -2943.76f, 12.9646f, 0.0f, 0.0f, -28.5532f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1039.74f, -2935.64f, 12.9646f, 0.0f, 0.0f, -28.5532f, -1, 9);
				Features::PlaceObjectByHash(3681122061, -1035.5f, -2927.86f, 12.9646f, 0.0f, 0.0f, -28.5532f, -1, 9);
				Features::PlaceObjectByHash(3608473212, -1063.23f, -2993.67f, 15.3449f, 0.0f, 0.0f, -25.1145f, -1, 9);
				Features::PlaceObjectByHash(3608473212, -1067.37f, -2998.06f, 15.3449f, 0.0f, 0.0f, -25.1145f, -1, 9);
				Features::PlaceObjectByHash(3608473212, -1063.7f, -2994.67f, 15.3449f, 0.0f, 0.0f, -25.1145f, -1, 9);
				Features::PlaceObjectByHash(3608473212, -1064.21f, -2995.73f, 15.3449f, 0.0f, 0.0f, -25.1145f, -1, 9);
				Features::PlaceObjectByHash(3608473212, -1064.71f, -2996.8f, 15.3449f, 0.0f, 0.0f, -25.1145f, -1, 9);
				Features::PlaceObjectByHash(3608473212, -1065.21f, -2997.84f, 15.3449f, 0.0f, 0.0f, -25.1145f, -1, 9);
				Features::PlaceObjectByHash(3608473212, -1067.1f, -2999.45f, 15.3449f, 0.0f, 0.0f, -25.1145f, -1, 9);
				Features::PlaceObjectByHash(3608473212, -1065.43f, -3000.24f, 15.3449f, 0.0f, 0.0f, -25.1145f, -1, 9);
				Features::PlaceObjectByHash(3608473212, -1068.29f, -3000.06f, 15.3449f, 0.0f, 0.0f, -25.1145f, -1, 9);
				Features::PlaceObjectByHash(3608473212, -1065.92f, -3001.18f, 15.3449f, 0.0f, 0.0f, -25.1145f, -1, 9);
				Features::PlaceObjectByHash(3608473212, -1066.44f, -3002.28f, 15.3449f, 0.0f, 0.0f, -25.1145f, -1, 9);
				Features::PlaceObjectByHash(3608473212, -1065.35f, -3002.77f, 15.3449f, 0.0f, 0.0f, -25.1145f, -1, 9);
				Features::PlaceObjectByHash(3608473212, -1065.6f, -3003.96f, 15.3449f, 0.0f, 0.0f, -25.1145f, -1, 9);
				Features::PlaceObjectByHash(3608473212, -1066.11f, -3005.04f, 15.3449f, 0.0f, 0.0f, -25.1145f, -1, 9);
				Features::PlaceObjectByHash(3608473212, -1064.21f, -2999.56f, 15.3449f, 0.0f, 0.0f, -25.1145f, -1, 9);
				Features::PlaceObjectByHash(3608473212, -1069.53f, -3000.82f, 15.3449f, 0.0f, 0.0f, -25.1145f, -1, 9);
				Features::PlaceObjectByHash(3608473212, -1070.75f, -3001.52f, 15.3449f, 0.0f, 0.0f, -25.1145f, -1, 9);
				Features::PlaceObjectByHash(3608473212, -1068.76f, -3002.46f, 15.3449f, 0.0f, 0.0f, -25.1145f, -1, 9);
				Features::PlaceObjectByHash(3608473212, -1069.29f, -3003.54f, 15.3449f, 0.0f, 0.0f, -25.1145f, -1, 9);
				Features::PlaceObjectByHash(3608473212, -1068.44f, -3005.23f, 15.3449f, 0.0f, 0.0f, -25.1145f, -1, 9);
				Features::PlaceObjectByHash(3608473212, -1071.58f, -3003.74f, 15.3449f, 0.0f, 0.0f, -25.1145f, -1, 9);
				Features::PlaceObjectByHash(2475986526, -1072.98f, -3006.81f, 16.0846f, 0.0f, 0.0f, -26.0348f, -1, 9);
				Features::PlaceObjectByHash(3608473212, -1072.44f, -3002.05f, 15.3449f, 0.0f, 0.0f, -25.1145f, -1, 9);
				Features::PlaceObjectByHash(3608473212, -1073.73f, -3002.72f, 15.3449f, 0.0f, 0.0f, -25.1145f, -1, 9);
				Features::PlaceObjectByHash(2475986526, -1076.54f, -3005.07f, 16.0846f, 0.0f, 0.0f, -26.0348f, -1, 9);
				Features::PlaceObjectByHash(2475986526, -1078.92f, -3009.92f, 13.7046f, 0.0f, 0.0f, -26.0348f, -1, 9);
				Features::PlaceObjectByHash(2475986526, -1075.31f, -3011.69f, 13.7046f, 0.0f, 0.0f, -26.0348f, -1, 9);
				Features::PlaceObjectByHash(2475986526, -1069.34f, -3008.59f, 16.0846f, 0.0f, 0.0f, -26.0348f, -1, 9);
				Features::PlaceObjectByHash(2475986526, -1071.71f, -3013.45f, 13.7046f, 0.0f, 0.0f, -26.0348f, -1, 9);
				Features::PlaceObjectByHash(2475986526, -1068.14f, -3015.2f, 13.7046f, 0.0f, 0.0f, -26.0348f, -1, 9);
				Features::PlaceObjectByHash(3608473212, -1065.36f, -3006.66f, 15.3449f, 0.0f, 0.0f, -25.1145f, -1, 9);
				Features::PlaceObjectByHash(2475986526, -1065.75f, -3010.35f, 16.0846f, 0.0f, 0.0f, -26.0348f, -1, 9);
			}
			if (GUI::Option("Teleport")) {
				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -1003.0f, -2916.0f, 14.0f, 1, 0, 0, 1);
			}

			break;

		case ramp11:
			GUI::Title("Airport Loop");
			GUI::Subtitle("Airport Loop");
			if (GUI::Option("Load")) {
				Features::PlaceObjectByHash(3966705493, -1041.89f, -3219.51f, 10.1797f, -2.43331f, 5.32208f, 62.9336f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1037.79f, -3221.47f, 10.3641f, -2.43331f, 5.32208f, 62.9336f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1034.16f, -3223.3f, 10.5366f, -2.43331f, 5.32208f, 62.9336f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1036.76f, -3219.45f, 10.1526f, -2.43331f, 5.32208f, 62.9336f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1033.12f, -3221.28f, 10.3251f, -2.43331f, 5.32208f, 62.9336f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1029.37f, -3225.6f, 11.1956f, -11.6033f, 5.32207f, 62.9335f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1028.33f, -3223.58f, 10.9842f, -11.6033f, 5.32207f, 62.9335f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1024.27f, -3225.54f, 12.1104f, -18.1533f, 5.32205f, 62.9336f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1025.44f, -3227.83f, 12.3497f, -18.1533f, 5.32205f, 62.9336f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1020.36f, -3230.06f, 15.7972f, -40.4234f, 5.32214f, 62.9336f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1019.22f, -3227.83f, 15.5634f, -40.4234f, 5.32214f, 62.9336f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1014.85f, -3229.56f, 20.4393f, -50.9034f, 5.3221f, 62.9337f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1016.07f, -3231.95f, 20.6898f, -50.9034f, 5.3221f, 62.9337f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1012.88f, -3232.96f, 26.0664f, -64.0034f, 5.32209f, 62.9336f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1011.63f, -3230.51f, 25.8104f, -64.0034f, 5.32209f, 62.9336f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1009.27f, -3231.06f, 32.0819f, -73.1735f, 5.32204f, 62.9336f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1010.52f, -3233.51f, 32.3379f, -73.1735f, 5.32214f, 62.9337f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1009.36f, -3233.48f, 38.2311f, -83.6535f, 5.32208f, 62.9336f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1008.09f, -3230.98f, 37.9695f, -83.6535f, 5.32208f, 62.9336f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1007.71f, -3230.43f, 44.185f, -92.8235f, 6.63212f, 62.9336f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1009.05f, -3228.93f, 49.9682f, -119.024f, 6.63217f, 62.9336f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1008.93f, -3232.81f, 44.4969f, -92.8235f, 6.63212f, 62.9336f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1010.27f, -3231.31f, 50.2801f, -119.024f, 6.63217f, 62.9336f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1011.96f, -3226.91f, 54.0691f, -142.604f, 6.6321f, 62.9337f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1013.1f, -3229.14f, 54.3602f, -142.604f, 6.6321f, 62.9337f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1017.49f, -3226.51f, 57.2125f, -159.634f, 6.63211f, 62.9336f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1022.14f, -3223.91f, 58.9186f, -168.804f, 6.63213f, 62.9336f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1035.97f, -3216.05f, 58.7162f, 155.826f, 1.39214f, 60.3137f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1031.37f, -3218.71f, 60.1775f, 176.786f, 6.63213f, 60.3137f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1026.33f, -3221.63f, 59.8766f, -168.804f, 6.63212f, 60.3136f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1020.98f, -3221.63f, 58.6206f, -168.804f, 6.63213f, 62.9336f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1024.97f, -3219.25f, 59.5578f, -168.804f, 6.63212f, 60.3136f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1016.33f, -3224.24f, 56.9145f, -159.634f, 6.63211f, 62.9336f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1029.99f, -3216.28f, 59.8517f, 176.786f, 6.63213f, 60.3137f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1029.99f, -3216.28f, 59.8517f, 176.786f, 6.63213f, 60.3137f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1034.73f, -3213.86f, 58.655f, 155.826f, 1.39214f, 60.3137f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1039.18f, -3211.42f, 55.2255f, 138.796f, 1.39206f, 60.3137f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1039.18f, -3211.42f, 55.2255f, 138.796f, 1.39206f, 60.3137f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1040.42f, -3213.61f, 55.2867f, 138.796f, 1.39206f, 60.3137f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1044.34f, -3211.51f, 50.6082f, 128.316f, 1.39213f, 60.3137f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1043.09f, -3209.33f, 50.547f, 128.316f, 1.39213f, 60.3137f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1046.16f, -3207.74f, 45.1535f, 117.837f, 1.39215f, 60.3137f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1048.17f, -3206.74f, 39.6252f, 104.737f, 1.39214f, 60.3137f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1048.92f, -3206.44f, 33.1586f, 87.6005f, 0.0914728f, 60.6227f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1048.18f, -3206.88f, 26.5446f, 77.3408f, 0.0913896f, 60.6229f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1049.44f, -3209.13f, 26.5487f, 77.3407f, 0.0913427f, 60.6228f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1047.3f, -3210.37f, 21.3947f, 56.6411f, 0.0914017f, 58.823f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1047.3f, -3210.37f, 21.3947f, 56.6411f, 0.0914017f, 58.823f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1045.93f, -3208.12f, 21.3905f, 56.6411f, 0.0914017f, 58.823f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1042.61f, -3210.12f, 16.8766f, 42.1517f, 0.0913785f, 58.8231f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1038.64f, -3212.63f, 13.6141f, 28.2018f, 0.0914187f, 58.8231f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1039.97f, -3214.83f, 13.6182f, 28.2018f, 0.0914187f, 58.8231f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1034.82f, -3217.71f, 11.1985f, 16.4116f, 0.0913871f, 69.303f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1033.53f, -3215.55f, 11.1081f, 16.4117f, 0.0913619f, 66.683f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1043.97f, -3212.37f, 16.8808f, 42.1517f, 0.0913785f, 58.8231f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1050.19f, -3208.69f, 33.1627f, 87.6005f, 0.0914728f, 60.6227f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1049.45f, -3208.98f, 39.6879f, 104.737f, 1.39214f, 60.3137f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1047.44f, -3209.98f, 45.2161f, 117.837f, 1.39215f, 60.3137f, -1, 10);
				Features::PlaceObjectByHash(3966705493, -1047.44f, -3209.98f, 45.2161f, 117.837f, 1.39215f, 60.3137f, -1, 10);
			}
			if (GUI::Option("Teleport")) {
				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -1074.0f, -3201.0f, 13.0f, 1, 0, 0, 1);
			}

			break;

		case ramp12:
			GUI::Title("Maze Bank Ramp");
			GUI::Subtitle("Maze Bank Ramp");
			if (GUI::Option("Load")) {
				Features::PlaceObjectByHash(3681122061, -82.9657f, -818.944f, 325.175f, 0.0f, -0.0f, 91.03f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -91.0941f, -819.089f, 322.355f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -98.36f, -819.224f, 316.632f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -105.626f, -819.358f, 310.91f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -112.892f, -819.492f, 305.187f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -120.158f, -819.626f, 299.464f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -127.424f, -819.761f, 293.741f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -134.69f, -819.895f, 288.018f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -141.956f, -820.029f, 282.296f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -149.222f, -820.163f, 276.573f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -156.487f, -820.298f, 270.85f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -163.753f, -820.432f, 265.127f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -171.019f, -820.566f, 259.404f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -178.285f, -820.701f, 253.682f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -185.551f, -820.835f, 247.959f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -192.817f, -820.969f, 242.236f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -200.083f, -821.103f, 236.513f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -207.349f, -821.238f, 230.79f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -214.615f, -821.372f, 225.068f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -221.881f, -821.506f, 219.345f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -229.147f, -821.641f, 213.622f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -236.413f, -821.775f, 207.899f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -243.679f, -821.909f, 202.176f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -250.945f, -822.043f, 196.453f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -258.21f, -822.178f, 190.731f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -265.476f, -822.312f, 185.008f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -287.274f, -822.715f, 167.839f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -280.008f, -822.58f, 173.562f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -272.742f, -822.446f, 179.285f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -294.54f, -822.849f, 162.117f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -301.806f, -822.983f, 156.394f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -309.072f, -823.118f, 150.671f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -316.338f, -823.252f, 144.948f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -323.604f, -823.386f, 139.225f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -330.87f, -823.52f, 133.503f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -338.136f, -823.655f, 127.78f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -345.402f, -823.789f, 122.057f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -352.668f, -823.923f, 116.334f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -359.934f, -824.057f, 110.611f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -367.199f, -824.192f, 104.889f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -374.465f, -824.326f, 99.1657f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -381.731f, -824.46f, 93.4429f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -388.997f, -824.595f, 87.7201f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -396.263f, -824.729f, 81.9973f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -403.529f, -824.863f, 76.2745f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -411.479f, -825.022f, 68.7971f, -19.78f, -3.43377e-005f, 91.1094f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -410.795f, -824.997f, 70.5517f, -38.2199f, 0.00787841f, 91.0529f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -411.96f, -825.029f, 69.097f, -27.6f, 1.15259e-005f, 91.1095f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -412.719f, -825.046f, 67.8516f, -10.58f, -2.92151e-006f, 91.1095f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -413.903f, -825.068f, 67.2075f, -3.21999f, 5.66959e-007f, 91.1095f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -415.378f, -825.099f, 66.7734f, 3.68002f, -4.58236e-006f, 91.1095f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -416.883f, -825.126f, 66.57f, 9.66002f, -8.44435e-006f, 91.1096f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -418.526f, -825.157f, 66.5571f, 15.64f, -1.80093e-005f, 91.1095f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -419.945f, -825.184f, 66.6727f, 20.7001f, 8.69782e-006f, 91.1094f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -421.727f, -825.218f, 67.0936f, 25.7601f, -2.09975e-005f, 91.1095f, -1, 11);
				Features::PlaceObjectByHash(3681122061, -422.006f, -825.234f, 66.966f, 30.8199f, 0.114757f, 90.6829f, -1,  11);
				Features::PlaceObjectByHash(3681122061, -429.913f, -825.328f, 71.6856f, 30.8199f, 0.114757f, 90.6829f, -1, 11);
			}
			if (GUI::Option("Teleport")) {
				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -74.94243f, -818.63446f, 326.174347f, 1, 0, 0, 1);
			}

			break;
#pragma endregion

#pragma region Time Mods
		case time_mods:
		{
			GUI::Title("");
			GUI::Subtitle("Time Options");
			GUI::Int("Choose Time", timeer, 0, 23);
			if (GUI::Option("Set Time")) {
				if (timeer == -1) {
					timeer = 0;
					TIME::SET_CLOCK_TIME(timeer, 0, 0);
				}
				else {
					TIME::SET_CLOCK_TIME(timeer, 0, 0);
				}
			}
			if (GUI::Option("Sync System Time")) {
				time_t now = time(0);
				tm t;
				localtime_s(&t, &now);
				TIME::SET_CLOCK_TIME(t.tm_hour, t.tm_min, t.tm_sec);
			}
		}
		break;

#pragma endregion

#pragma region Weathers
		case weatheroptions:
		{
			GUI::Title("");
			GUI::Subtitle("Weather Options");
			GUI::Toggle("SP Ground Snow", Features::isSPSnow, [] { Features::spSnow(); });
			if (GUI::Option("Sun")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("Clear"); }
			if (GUI::Option("Rain")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("Clearing"); }
			if (GUI::Option("Snow")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("Snowlight"); }
			if (GUI::Option("Thunder")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("Thunder"); }
			if (GUI::Option("Blizzard")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("Blizzard"); }
			if (GUI::Option("Overcast")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("Overcast"); }
			if (GUI::Option("Foggy")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("Foggy"); }
			if (GUI::Option("Smog")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("Smog"); }
			if (GUI::Option("Clouds")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("Clouds"); }
			if (GUI::Option("Christmas")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("XMAS"); }
			if (GUI::Option("Halloween")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("Halloween"); }
		}
		break;
#pragma endregion

#pragma region Object Spawner
		case object_spawner:
		{
			GUI::Title("Object Options");
			GUI::Option("~y~Not Finished");

		}
		break;
#pragma endregion

#pragma region Nearby Entities
		case nearby_entities:
		{
			GUI::Title("");
			GUI::Subtitle("Nearby Entities");
			if (GUI::Option("Repair Nearby Cars")) {
				Features::repairnearbyvehicles();
			}
			GUI::Toggle("Explode Nearby Peds", Features::explodepedsbool);
			GUI::Toggle("Upgrade Nearby Cars", Features::upgradenearbyvehiclesbool);
			GUI::Toggle("Explode Nearby Cars", Features::explodenearbyvehiclesbool);
			GUI::Toggle("Explode Nearby Tires", Features::explodenearbytiresbool);
			GUI::Toggle("Horn Nearby Cars", Features::hornnearbyvehiclesbool);
			GUI::Toggle("Launch Nearby Cars", Features::launchnearbyvehiclesbool);
			GUI::Toggle("Delete Cars", Features::deletenearbyvehiclesbool);
		}
		break;

#pragma endregion

#pragma endregion

#pragma region Settings SubMenus

#pragma region Settings Mods
		case themeloader:
		{
			GUI::Title("Theme Colors");
			GUI::Subtitle("Theme Colors");
			if (GUI::Option("Red Theme")) {
				GUI::Settings::titleRect = { 100, 0, 0, 255 };
				GUI::Settings::scroller = { 100, 0, 0, 255 };
			}
			if (GUI::Option("Blue Theme")) {
				GUI::Settings::titleRect = { 0, 0, 200, 255 };
				GUI::Settings::scroller = { 0, 0, 200, 255 };
			}
			if (GUI::Option("Green Theme")) {
				GUI::Settings::titleRect = { 0, 180, 0, 255 };
				GUI::Settings::scroller = { 0, 0, 180, 255 };
			}
			if (GUI::Option("Load Default Theme")) {
				GUI::Settings::count = { 255, 255, 255, 255, 6 };
				GUI::Settings::titleText = { 226, 46, 52, 200, 7 };
				GUI::Settings::titleRect = { 37, 35, 35, 255 };
				GUI::Settings::optionText = { 226, 46, 52, 255, 6 };
				GUI::Settings::breakText = { 226, 46, 52, 200, 1 };
				GUI::Settings::arrow = { 255, 255, 255, 255, 3 };
				GUI::Settings::scroller = { 226, 46, 52, 150 };
				GUI::Settings::integre = { 255, 255, 255, 255, 2 };
				GUI::Settings::line = { 255, 255, 255, 255 };
			}
		}
		break;
		case settingstitlerect:
		{
			GUI::Title("Title Rect");
			GUI::Subtitle("Title Rect");
			if (GUI::Int("Red", GUI::Settings::titleRect.r, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::titleRect.r = Features::NumberKeyboard();
				}
			}
			if (GUI::Int("Green", GUI::Settings::titleRect.g, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::titleRect.g = Features::NumberKeyboard();
				}
			}
			if (GUI::Int("Blue", GUI::Settings::titleRect.b, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::titleRect.b = Features::NumberKeyboard();
				}
			}
			if (GUI::Int("Opacity", GUI::Settings::titleRect.a, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::titleRect.a = Features::NumberKeyboard();
				}
			}
		}
		break;
		case settingsoptiontext:
		{
			GUI::Title("Option Text");
			GUI::Subtitle("Option Text");
			if (GUI::Int("Red", GUI::Settings::optionText.r, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::optionText.r = Features::NumberKeyboard();

				}
			}
			if (GUI::Int("Green", GUI::Settings::optionText.g, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::optionText.g = Features::NumberKeyboard();
				}
			}
			if (GUI::Int("Blue", GUI::Settings::optionText.b, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::optionText.b = Features::NumberKeyboard();
				}
			}
			if (GUI::Int("Opacity", GUI::Settings::optionText.a, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::optionText.a = Features::NumberKeyboard();
				}
			}
			GUI::Break("Integer Text");
			if (GUI::Int("Red", GUI::Settings::integre.r, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::integre.r = Features::NumberKeyboard();
				}
			}
			if (GUI::Int("Green", GUI::Settings::integre.g, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::integre.g = Features::NumberKeyboard();
				}
			}
			if (GUI::Int("Blue", GUI::Settings::integre.b, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::integre.b = Features::NumberKeyboard();
				}
			}
			if (GUI::Int("Opacity", GUI::Settings::integre.a, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::integre.a = Features::NumberKeyboard();
				}
			}
			//GUI::MenuOption("Font", font);
		}
		break;
		case settingsoptiontext2:
		{
			GUI::Title("Selected Text");
			GUI::Subtitle("Selected Text");
			if (GUI::Int("Red", GUI::Settings::SelectedText.r, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::SelectedText.r = Features::NumberKeyboard();
				}
			}
			if (GUI::Int("Green", GUI::Settings::SelectedText.g, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::SelectedText.g = Features::NumberKeyboard();
				}
			}
			if (GUI::Int("Blue", GUI::Settings::SelectedText.b, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::SelectedText.b = Features::NumberKeyboard();
				}
			}
			if (GUI::Int("Opacity", GUI::Settings::SelectedText.a, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::SelectedText.a = Features::NumberKeyboard();
				}
			}
			GUI::Break("Integer Text");
			if (GUI::Int("Red", GUI::Settings::integre2.r, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::integre2.r = Features::NumberKeyboard();
				}
			}
			if (GUI::Int("Green", GUI::Settings::integre2.g, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::integre2.g = Features::NumberKeyboard();
				}
			}
			if (GUI::Int("Blue", GUI::Settings::integre2.b, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::integre2.b = Features::NumberKeyboard();
				}
			}
			if (GUI::Int("Opacity", GUI::Settings::integre2.a, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::integre2.a = Features::NumberKeyboard();
				}
			}
			//GUI::MenuOption("Font", font);
		}
		break;

		case settingsbreaktext:
		{
			GUI::Title("Break Text");
			GUI::Subtitle("Break Text");
			if (GUI::Int("Red", GUI::Settings::breakText.r, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::breakText.r = Features::NumberKeyboard();
				}
			}
			if (GUI::Int("Green", GUI::Settings::breakText.g, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::breakText.g = Features::NumberKeyboard();
				}
			}
			if (GUI::Int("Blue", GUI::Settings::breakText.b, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::breakText.b = Features::NumberKeyboard();
				}
			}
			if (GUI::Int("Opacity", GUI::Settings::breakText.a, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::breakText.a = Features::NumberKeyboard();
				}
			}
			GUI::Break("Break Text Here");
			//GUI::MenuOption("Font", font);
		}
		break;

		case font:
		{
			GUI::Title("Font");
			GUI::Subtitle("Font");
			if (GUI::Option("Chalet London")) { GUI::Settings::optionText.f, GUI::Settings::SelectedText.f = 0; }
			if (GUI::Option("House Script")) { GUI::Settings::optionText.f, GUI::Settings::SelectedText.f = 1; }
			if (GUI::Option("Monospace")) { GUI::Settings::optionText.f, GUI::Settings::SelectedText.f = 2; }
			if (GUI::Option("Wing Dings")) { GUI::Settings::optionText.f, GUI::Settings::SelectedText.f = 3; }
			if (GUI::Option("Chalet Comprime Cologne")) { GUI::Settings::optionText.f, GUI::Settings::SelectedText.f = 4; }
			if (GUI::Option("Pricedown")) { GUI::Settings::optionText.f, GUI::Settings::SelectedText.f = 7; }
		}
		break;
		case settingsscroller:
		{
			GUI::Title("Scroller");
			GUI::Subtitle("Scroller");
			if (GUI::Int("Red", GUI::Settings::scroller.r, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::scroller.r = Features::NumberKeyboard();
				}
			}
			if (GUI::Int("Green", GUI::Settings::scroller.g, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::scroller.g = Features::NumberKeyboard();
				}
			}
			if (GUI::Int("Blue", GUI::Settings::scroller.b, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::scroller.b = Features::NumberKeyboard();
				}
			}
			if (GUI::Int("Opacity", GUI::Settings::scroller.a, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					GUI::Settings::scroller.a = Features::NumberKeyboard();
				}
			}
		}
		break;
#pragma endregion

#pragma endregion

		}
		GUI::End();
		WAIT(0);
	}
}

void ScriptMain() {
	srand(GetTickCount());
	Features::TimePD = timeGetTime();
	Features::TimePD2 = timeGetTime();
	Features::TimePD3 = timeGetTime();
	Features::TimePD5 = timeGetTime();
	Features::TimePD6 = timeGetTime();
	Features::TimePD9 = timeGetTime();
	Features::TimePD10 = timeGetTime();
	Features::TimePD11 = timeGetTime();
	main();
}

#pragma warning (pop)