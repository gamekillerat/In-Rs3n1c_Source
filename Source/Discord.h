#pragma once

void UpdatePresence(); // Update Discord RPC
void Initialize(); // Initialise RPC
void Shutdown(); // Shutdown RPC, Call this function in dllmain upon freeing memory!
void DiscordMain(); // Calls Initialise And Update P....