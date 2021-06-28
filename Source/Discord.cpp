#include "stdafx.h"
#include "discord.h"
#include "Discord/include/discord_register.h"
#include "Discord/include/discord_rpc.h"

#pragma comment(lib, "Discord/lib/discord-rpc.lib")


DiscordRichPresence discordPresence;
const char* token = "pGIybFuM1R4B461JhsQLhN5G5YLSom3Q"; // Discord RPC Token

void UpdatePresence()
{
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.state = "Menu Version : 1.1.0";
	discordPresence.details = "Playing GTA V With Project";
	discordPresence.largeImageKey = "webp_net-resizeimage";
	discordPresence.largeImageText = "Project.com";
	discordPresence.smallImageKey = "webp_net-resizeimage";
	discordPresence.smallImageText = "Version 1.1.0";
	discordPresence.instance = 1;
	Discord_UpdatePresence(&discordPresence);
}

void Initialize()
{
	DiscordEventHandlers handlers;
	memset(&handlers, 0, sizeof(handlers));
	Discord_Initialize("token", &handlers, TRUE, nullptr);
}

void Shutdown() {
	Discord_Shutdown(); // Stop RPC
}

void DiscordMain() {
	Initialize();
	UpdatePresence();
}