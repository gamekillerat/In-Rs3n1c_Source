//Hooking.cpp
#pragma once
#include "stdafx.h"
#include "enums.h"
#include "Authh.h"
#include <fstream>

using namespace Memory;

ScriptThread*(*GetActiveThread)() = nullptr;
HMODULE _hmoduleDLL;
HANDLE mainFiber;
DWORD wakeAt;

std::vector<LPVOID>				Hooking::m_hooks;
uint64_t*						Hooking::m_frameCount;
fpIsDLCPresent					Hooking::is_DLC_present;
fpCreateAmbientPickup			Hooking::create_ambient_pickup;
fpGetEventData					Hooking::get_event_data;
fpStatSetInt					Hooking::stat_set_int;
fpTriggerScriptEvent			Hooking::trigger_script_event;
fpGetPlayerName					Hooking::get_player_name;
fpSetTime						Hooking::set_time;
fpSpectatePlayer				Hooking::spectate_player;
fpLobbyWeather					Hooking::set_lobby_weather;
fpAddOwnedExplosion				Hooking::add_owned_explosion;
fpNetworkIsSessionStarted		Hooking::network_is_session_started;

static eGameState* 											m_gameState;
static uint64_t												m_worldPtr;
static BlipList*											m_blipList;
static Hooking::NativeRegistrationNew**						m_registrationTable;
static std::unordered_map<uint64_t, Hooking::NativeHandler>	m_handlerCache;
static std::vector<LPVOID>									m_hookedNative;
static __int64**                                            m_globalPtr;
bool Hooking::isRunning = true;

twoBytes* Hooking::m_ownedExplosionBypass;
const int EVENT_COUNT = 84;
static std::vector<void*> EventPtr;
static char EventRestore[EVENT_COUNT] = {};
const char NOP = '\x90';


/* Start Hooking */
void Hooking::Start(HMODULE hmoduleDLL)
{
	_hmoduleDLL = hmoduleDLL;
	Log::Init(hmoduleDLL);
	FindPatterns();
	if (!InitializeHooks()) Cleanup();
}
BOOL Hooking::InitializeHooks()
{
	BOOL returnVal = TRUE;

	if (username == "" || password == "")
	{
		isCredsValid = false;
	}
	else if (!isAuthValid(username, password)) {
		isCredsValid = false;
	}
	else {
		isCredsValid = true;
	}

	if (!iHook.Initialize()) {

		Log::Error("Failed to initialize InputHook");
		returnVal = FALSE;
	}

	if (MH_Initialize() != MH_OK) {
		Log::Error("MinHook failed to initialize");
		returnVal = FALSE;
	}

	if (!HookNatives()) {

		Log::Error("Failed to initialize NativeHooks");
		returnVal = FALSE;
	}

	return returnVal;
}

template <typename T>
bool Native(DWORD64 hash, LPVOID hookFunction, T** trampoline)
{
	if (*reinterpret_cast<LPVOID*>(trampoline) != NULL)
		return true;
	auto originalFunction = Hooking::GetNativeHandler(hash);
	if (originalFunction != 0) {
		MH_STATUS createHookStatus = MH_CreateHook(originalFunction, hookFunction, reinterpret_cast<LPVOID*>(trampoline));
		if (((createHookStatus == MH_OK) || (createHookStatus == MH_ERROR_ALREADY_CREATED)) && (MH_EnableHook(originalFunction) == MH_OK))
		{
			m_hookedNative.push_back((LPVOID)originalFunction);
			Log::Msg("Hooked Native 0x%#p", hash);
			return true;
		}
	}

	return false;
}

uint64_t CMetaData::m_begin = 0;
uint64_t CMetaData::m_end = 0;
DWORD CMetaData::m_size = 0;

uint64_t CMetaData::begin()
{
	return m_begin;
}
uint64_t CMetaData::end()
{
	return m_end;
}
DWORD CMetaData::size()
{
	return m_size;
}

void CMetaData::init()
{
	if (m_begin && m_size)
		return;

	m_begin = (uint64_t)GetModuleHandleA(nullptr);
	const IMAGE_DOS_HEADER*	headerDos = (const IMAGE_DOS_HEADER*)m_begin;
	const IMAGE_NT_HEADERS*	headerNt = (const IMAGE_NT_HEADERS64*)((const BYTE*)headerDos + headerDos->e_lfanew);
	m_size = headerNt->OptionalHeader.SizeOfCode;
	m_end = m_begin + m_size;
	return;
}

bool twoBytes::empty()
{
	bool r = true;
	for (int i = 0; i < 2; ++i)
		if (this->byte[i] != 0)
		{
			r = false;
			break;
		}
	return r;
}

void Hooking::ownedExplosionBypass(bool toggle)
{
	constexpr twoBytes patched = { 0x39, 0xDB };
	constexpr twoBytes restore = { 0x3B, 0xF8 };
	if (Hooking::m_ownedExplosionBypass == nullptr)
		return;
	*Hooking::m_ownedExplosionBypass = toggle ? patched : restore;
}

fpIsDLCPresent OG_IS_DLC_PRESENT = nullptr;
bool HK_IS_DLC_PRESENT(std::uint32_t dlcHash)
{
	static uint64_t	last = 0;
	uint64_t		cur = *Hooking::m_frameCount;
	if (last != cur)
	{
		last = cur;
		Hooking::onTickInit();
	}
	return OG_IS_DLC_PRESENT(dlcHash);
}
Hooking::NativeHandler ORIG_WAIT = NULL;
void* __cdecl MY_WAIT(NativeContext *cxt)
{
	static int lastThread = 0;
	int threadId = SCRIPT::GET_ID_OF_THIS_THREAD();
	if (!lastThread)
	{
		char* name = SCRIPT::_GET_NAME_OF_THREAD(threadId);
		if (strcmp(name, "main_persistent") == 0)
		{
			lastThread = threadId;
			Log::Msg("Hooked Script NAME: %s ID: %i", name, threadId);
		}
	}
	if (threadId == lastThread) Hooking::onTickInit();
	ORIG_WAIT(cxt);
	return cxt;
}

fpGetEventData OG_GET_EVENT_DATA = nullptr;
bool HK_GET_EVENT_DATA(std::int32_t eventGroup, std::int32_t eventIndex, std::int64_t* args, std::uint32_t argCount)
{
	auto handle = static_cast<decltype(&HK_GET_EVENT_DATA)>(OG_GET_EVENT_DATA)(eventGroup, eventIndex, args, argCount);

	if (handle) {

		Player player = args[1];
		const char* sender = Hooking::get_player_name(player);

		if (args[0] == -175474624 && Features::isSoundSpamProtex)
		{
			notifyBlocked("Event: Sound Spam Event\nSender: " + (std::string)sender + "\nStatus: Prevented");
			return false;
		}
		if (args[0] == 1000837481 && Features::isTeleportProtex)
		{
			notifyBlocked("Event: Teleport Event\nSender: " + (std::string)sender + "\nStatus: Prevented");
			return false;
		}
		if (args[0] == -77616667 && Features::isKickToFMProtex)
		{
			notifyBlocked("Event: Kick Event\nSender: " + (std::string)sender + "\nStatus: Prevented");
			return false;
		}
		if (args[0] == 769347061 && Features::isKickToSPProtex)
		{
			notifyBlocked("Event: Kick Event\nSender: " + (std::string)sender + "\nStatus: Prevented");
			return false;
		}
		if (Features::isSendToJobProtex && args[0] == -15432926)
		{
			notifyBlocked("Event: Send to Job Event\nSender: " + (std::string)sender + "\nStatus: Prevented");
			return false;
		}
		if (Features::isCEOKickProtex && args[0] == -1190833098)
		{
			notifyBlocked("Event: CEO Kick Event\nSender: " + (std::string)sender + "\nStatus: Prevented");
			return false;
		}
		if (Features::isCEOBanProtex && args[0] == 360381720)
		{
			notifyBlocked("Event: CEO Ban Event\nSender: " + (std::string)sender + "\nStatus: Prevented");
			return false;
		}
		if (Features::isTransactionErrorProtex && args[0] == -1920290846) //VIP
		{
			notifyBlocked("Event: Transaction Error Event\nSender: " + (std::string)sender + "\nStatus: Prevented");
			return false;
		}
		if (Features::isGTABannerProtex && args[0] == -181444979) //VIP
		{
			notifyBlocked("Event: Banner Event\nSender: " + (std::string)sender + "\nStatus: Prevented");
			return false;
		}
	}

	return handle;
}

bool Hooking::HookNatives()
{
	MH_STATUS status = MH_CreateHook(Hooking::is_DLC_present, HK_IS_DLC_PRESENT, (void**)&OG_IS_DLC_PRESENT);
	if ((status != MH_OK && status != MH_ERROR_ALREADY_CREATED) || MH_EnableHook(Hooking::is_DLC_present) != MH_OK)
		return false;
	Hooking::m_hooks.push_back(Hooking::is_DLC_present);

	MH_STATUS status1 = MH_CreateHook(Hooking::get_event_data, HK_GET_EVENT_DATA, (void**)&OG_GET_EVENT_DATA);
	if (status1 != MH_OK && status1 != MH_ERROR_ALREADY_CREATED || MH_EnableHook(Hooking::get_event_data) != MH_OK) {
		Log::Msg("Failed to hook GET_EVENT_DATA.");
		return false;
	}
	else
	{
		Log::Msg("Hooked GET_EVENT_DATA.");
	}

	Hooking::m_hooks.push_back(Hooking::get_event_data);
	return true;
}

void __stdcall ScriptFunction(LPVOID lpParameter)
{
	try
	{
		ScriptMain();

	}
	catch (...)
	{
		Log::Fatal("Failed scriptFiber");
	}
}

void Hooking::onTickInit()
{
	mainFiber = IsThreadAFiber() ? GetCurrentFiber() : ConvertThreadToFiber(nullptr);

	if (timeGetTime() < wakeAt)
		return;

	static HANDLE scriptFiber;
	if (scriptFiber)
		SwitchToFiber(scriptFiber);
	else
		scriptFiber = CreateFiber(NULL, ScriptFunction, nullptr);
}

void Hooking::FailPatterns(const char* name)
{
	char buf[4096];
	sprintf_s(buf, "finding %s", name);
	Log::Error(buf);
	Cleanup();
}

/*
//CPatternResult
*/

CPatternResult::CPatternResult(void* pVoid) :
	m_pVoid(pVoid)
{}
CPatternResult::CPatternResult(void* pVoid, void* pBegin, void* pEnd) :
	m_pVoid(pVoid),
	m_pBegin(pBegin),
	m_pEnd(pEnd)
{}
CPatternResult::~CPatternResult() {}

/*
//CPattern Public
*/

CPattern::CPattern(char* szByte, char* szMask) :
	m_szByte(szByte),
	m_szMask(szMask),
	m_bSet(false)
{}
CPattern::~CPattern() {}

CPattern&	CPattern::find(int i, uint64_t startAddress)
{
	match(i, startAddress, false);
	if (m_result.size() <= i)
		m_result.push_back(nullptr);
	return *this;
}

CPattern&	CPattern::virtual_find(int i, uint64_t startAddress)
{
	match(i, startAddress, true);
	if (m_result.size() <= i)
		m_result.push_back(nullptr);
	return *this;
}

CPatternResult	CPattern::get(int i)
{
	if (m_result.size() > i)
		return m_result[i];
	return nullptr;
}

/*
//CPattern Private
*/
bool	CPattern::match(int i, uint64_t startAddress, bool virt)
{
	if (m_bSet)
		return false;
	uint64_t	begin = 0;
	uint64_t	end = 0;
	if (!virt)
	{
		CMetaData::init();
		begin = CMetaData::begin() + startAddress;
		end = CMetaData::end();
		if (begin >= end)
			return false;
	}
	int		j = 0;
	do
	{
		if (virt)
			begin = virtual_find_pattern(startAddress, (BYTE*)m_szByte, m_szMask) + 1;
		else
			begin = find_pattern(begin, end, (BYTE*)m_szByte, m_szMask) + 1;
		if (begin == NULL)
			break;
		j++;
	} while (j < i);

	m_bSet = true;
	return true;
}

bool	CPattern::byte_compare(const BYTE* pData, const BYTE* btMask, const char* szMask)
{
	for (; *szMask; ++szMask, ++pData, ++btMask)
		if (*szMask == 'x' && *pData != *btMask)
			break;
	if ((*szMask) != 0)
		return false;
	return true;
}


uint64_t	CPattern::find_pattern(uint64_t address, uint64_t end, BYTE *btMask, char *szMask)
{
	size_t len = strlen(szMask) + 1;
	for (uint64_t i = 0; i < (end - address - len); i++)
	{
		BYTE*	ptr = (BYTE*)(address + i);
		if (byte_compare(ptr, btMask, szMask))
		{
			m_result.push_back(CPatternResult((void*)(address + i)));
			return address + i;
		}
	}
	return NULL;
}

uint64_t	CPattern::virtual_find_pattern(uint64_t address, BYTE *btMask, char *szMask)
{
	MEMORY_BASIC_INFORMATION mbi;
	char*	pStart = nullptr;
	char*	pEnd = nullptr;
	char*	res = nullptr;
	size_t	maskLen = strlen(szMask);

	while (res == nullptr && sizeof(mbi) == VirtualQuery(pEnd, &mbi, sizeof(mbi)))
	{
		pStart = pEnd;
		pEnd += mbi.RegionSize;
		if (mbi.Protect != PAGE_READWRITE || mbi.State != MEM_COMMIT)
			continue;

		for (int i = 0; pStart < pEnd - maskLen && res == nullptr; ++pStart)
		{
			if (byte_compare((BYTE*)pStart, btMask, szMask))
			{
				m_result.push_back(CPatternResult((void*)pStart, mbi.BaseAddress, pEnd));
				res = pStart;
			}
		}

		mbi = {};
	}
	return (uint64_t)res;
}

void	failPat(const char* name)
{
	Log::Fatal("Failed to find %s pattern.", name);
	exit(0);
}

template <typename T>
void	setPat
(
	const char*	name,
	char*		pat,
	char*		mask,
	T**			out,
	bool		rel,
	int			offset = 0,
	int			deref = 0,
	int			skip = 0
)
{
	T*	ptr = nullptr;

	CPattern pattern(pat, mask);
	pattern.find(1 + skip);
	if (rel)
		ptr = pattern.get(skip).get_rel<T>(offset);
	else
		ptr = pattern.get(skip).get<T>(offset);

	while (true)
	{
		if (ptr == nullptr)
			failPat(name);

		if (deref <= 0)
			break;
		ptr = *(T**)ptr;
		--deref;
	}

	*out = ptr;
	return;
}

template <typename T>
void	setFn
(
	const char*	name,
	char*		pat,
	char*		mask,
	T*			out,
	int			skip = 0
)
{
	char*	ptr = nullptr;

	CPattern pattern(pat, mask);
	pattern.find(1 + skip);
	ptr = pattern.get(skip).get<char>(0);

	if (ptr == nullptr)
		failPat(name);

	*out = (T)ptr;
	return;
}

void* Hooking::m_onlineName;

void Hooking::FindPatterns()
{
	HANDLE steam = GetModuleHandleA("steam_api64.dll");

	//auto p_EpicBypass = pattern("74 12 48 8B 10 48 8B C8 FF 52 30 84 C0 74 05 48 8B C3"); //model spawn
	//Memory::nop(p_EpicBypass.count(1).get(0).get<void>(13), 2);

	auto p_activeThread = pattern("E8 ? ? ? ? 48 8B 88 10 01 00 00");
	auto p_blipList = pattern("4C 8D 05 ? ? ? ? 0F B7 C1");
	auto p_fixVector3Result = pattern("83 79 18 00 48 8B D1 74 4A FF 4A 18");
	auto p_gameLegals = pattern("72 1F E8 ? ? ? ? 8B 0D");
	auto p_gameLogos = pattern("70 6C 61 74 66 6F 72 6D 3A");
	auto p_gameState = pattern("83 3D ? ? ? ? ? 8A D9 74 0A");
	auto p_nativeTable = pattern("76 32 48 8B 53 40 48 8D 0D");
	auto p_worldPtr = pattern("48 8B 05 ? ? ? ? 45 ? ? ? ? 48 8B 48 08 48 85 C9 74 07");
	auto p_globalPtr = pattern("4C 8D 05 ? ? ? ? 4D 8B 08 4D 85 C9 74 11");
	auto p_eventHook = pattern("48 83 EC 28 E8 ? ? ? ? 48 8B 0D ? ? ? ? 4C 8D 0D ? ? ? ? 4C 8D 05 ? ? ? ? BA 03");
	auto p_bypass = pattern("3B F8 40 0F 94 C7");
	char* ptr = nullptr;
	ptr = p_bypass.count(1).get(0).get<char>(0);
	ptr == nullptr ? FailPatterns("AddOwnedExplosion") : Hooking::m_ownedExplosionBypass = (twoBytes*)ptr;

	setPat<uint64_t>("frame count",
		"\x8B\x15\x00\x00\x00\x00\x41\xFF\xCF",
		"xx????xxx",
		&Hooking::m_frameCount,
		true,
		2);

	setFn<fpIsDLCPresent>("is_DLC_present",
		"\x48\x89\x5C\x24\x00\x57\x48\x83\xEC\x20\x81\xF9\x00\x00\x00\x00",
		"xxxx?xxxxxxx????",
		&Hooking::is_DLC_present);

	setFn<fpGetEventData>("get_event_data", "\x48\x89\x5C\x24\x00\x57\x48\x83\xEC\x20\x49\x8B\xF8\x4C\x8D\x05\x00\x00\x00\x00", "xxxx?xxxxxxxxxxx????",
		&Hooking::get_event_data);

	setFn<fpStatSetInt>("stat_set_int",
		"\x48\x89\x5C\x24\x00\x48\x89\x74\x24\x00\x89\x54\x24\x10\x55\x57\x41\x57",
		"xxxx?xxxx?xxxxxxxx",
		&Hooking::stat_set_int);

	setFn<fpAddOwnedExplosion>("add_owned_explosion",
		"\x48\x8B\xC4\x48\x89\x58\x08\x48\x89\x70\x10\x48\x89\x78\x18\x4C\x89\x70\x20\x55\x48\x8D\x68\xB9\x48\x81\xEC\x00\x00\x00\x00\x0F\x29\x70\xE8\x41\x8B\xD8",
		"xxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxxxx",
		&Hooking::add_owned_explosion);

	setFn<fpTriggerScriptEvent>("trigger_script_event",
		"\x48\x8B\xC4\x48\x89\x58\x08\x48\x89\x68\x10\x48\x89\x70\x18\x48\x89\x78\x20\x41\x56\x48\x81\xEC\x00\x00\x00\x00\x45\x8B\xF0\x41\x8B\xF9",
		"xxxxxxxxxxxxxxxxxxxxxxxx????xxxxxx",
		&Hooking::trigger_script_event);

	setFn<fpNetworkIsSessionStarted>("network_is_session_started",
		"\x48\x8B\x0D\x00\x00\x00\x00\x33\xC0\x48\x85\xC9\x74\x0E\x83\xB9\x00\x00\x00\x00\x00\x75\x05",
		"xxx????xxxxxxxxx?????xx",
		&Hooking::network_is_session_started);

	char * c_location = nullptr;
	void * v_location = nullptr;

	Hooking::set_lobby_weather = reinterpret_cast<decltype(set_lobby_weather)>(Memory::pattern("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 30 40 8A E9").count(1).get(0).get<char>(0));
	Hooking::set_time = reinterpret_cast<decltype(set_time)>(Memory::pattern("80 3D ? ? ? ? ? 75 37 8B 05 ? ? ? ? C6").count(1).get(0).get<void>(0));
	Hooking::spectate_player = reinterpret_cast<decltype(spectate_player)>(Memory::pattern("48 89 5C 24 ? 57 48 83 EC 20 41 8A F8 84 C9").count(1).get(0).get<void>(0));

	Log::Msg("Getting Game State...");
	c_location = p_gameState.count(1).get(0).get<char>(2);
	c_location == nullptr ? FailPatterns("gameState") : m_gameState = reinterpret_cast<decltype(m_gameState)>(c_location + *(int32_t*)c_location + 5);

	Log::Msg("Fixing Vector3 Result...");
	v_location = p_fixVector3Result.count(1).get(0).get<void>(0);
	if (v_location != nullptr) scrNativeCallContext::SetVectorResults = (void(*)(scrNativeCallContext*))(v_location);

	Log::Msg("Getting Native Registration Table...");
	c_location = p_nativeTable.count(1).get(0).get<char>(9);
	c_location == nullptr ? FailPatterns("native registration table") : m_registrationTable = reinterpret_cast<decltype(m_registrationTable)>(c_location + *(int32_t*)c_location + 4);

	Log::Msg("Getting World Pointer...");
	c_location = p_worldPtr.count(1).get(0).get<char>(0);
	c_location == nullptr ? FailPatterns("world Pointer") : m_worldPtr = reinterpret_cast<uint64_t>(c_location) + *reinterpret_cast<int*>(reinterpret_cast<uint64_t>(c_location) + 3) + 7;

	Log::Msg("Getting Blip List...");
	c_location = p_blipList.count(1).get(0).get<char>(0);
	c_location == nullptr ? FailPatterns("blip List") : m_blipList = (BlipList*)(c_location + *reinterpret_cast<int*>(c_location + 3) + 7);

	//Log::Msg("Bypassing Object restrictions..");
	//CPattern pattern_modelCheck("\x48\x85\xC0\x0F\x84\x00\x00\x00\x00\x8B\x48\x50", "xxxxx????xxx");
	//auto ptr = pattern_modelCheck.find(0).get(0).get<char>(0);
	//ptr == nullptr ? Log::Error("Failed to find modelCheck_pattern") : Memory::nop(ptr, 24);

	//CPattern pattern_modelSpawn("\x48\x8B\xC8\xFF\x52\x30\x84\xC0\x74\x05\x48", "xxxxxxxxxxx");
	//ptr = pattern_modelSpawn.find(0).get(0).get<char>(8);
	//ptr == nullptr ? Log::Error("Failed to find modelSpawn_pattern") : Memory::nop(ptr, 2);

	Log::Msg("Getting Active Script Thread...");
	c_location = p_activeThread.count(1).get(0).get<char>(1);
	c_location == nullptr ? FailPatterns("Active Script Thread") : GetActiveThread = reinterpret_cast<decltype(GetActiveThread)>(c_location + *(int32_t*)c_location + 4);

	Log::Msg("Getting World Pointer...");
	c_location = p_globalPtr.count(1).get(0).get<char>(0);
	__int64 patternAddr = NULL;
	c_location == nullptr ? FailPatterns("globalTable") : patternAddr = reinterpret_cast<decltype(patternAddr)>(c_location);
	m_globalPtr = (__int64**)(patternAddr + *(int*)(patternAddr + 3) + 7);

	Log::Msg("Getting Event Hook...");
	if ((c_location = p_eventHook.count(1).get(0).get<char>(0)))
	{
		int i = 0, j = 0, matches = 0, found = 0;
		char* pattern = "\x4C\x8D\x05";
		while (found != EVENT_COUNT)
		{
			if (c_location[i] == pattern[j])
			{
				if (++matches == 3)
				{
					EventPtr.push_back((void*)(reinterpret_cast<uint64_t>(c_location + i - j) + *reinterpret_cast<int*>(c_location + i + 1) + 7));
					found++;
					j = matches = 0;
				}
				j++;
			}
			else
			{
				matches = j = 0;
			}
			i++;
		}
	}

	Log::Msg("Initializing Natives...");
	CrossMapping::initNativeMap();

	Log::Msg("Checking if Grand Theft Auto V is Ready...");
	while (*m_gameState != GameStatePlaying) {
		Sleep(200);
	}

	if (*m_gameState == GameStatePlaying) {
		Log::Msg("Grand Theft Auto V is ready.");

		setPat<void>("name changer",
			"\x48\x8B\x05\x00\x00\x00\x00\xC3\x8A\xD1",
			"xxx????xxx",
			&Hooking::m_onlineName,
			true,
			3, 1);

		setFn<fpGetPlayerName>("get_player_name",
			"\x40\x53\x48\x83\xEC\x20\x80\x3D\x00\x00\x00\x00\x00\x8B\xD9\x74\x22",
			"xxxxxxxx?????xxxx",
			&Hooking::get_player_name);

		Log::Msg("Hooked GET_PLAYER_NAME.");
	}
}

static Hooking::NativeHandler _Handler(uint64_t origHash)
{
	uint64_t newHash = CrossMapping::MapNative(origHash);
	if (newHash == 0)
	{
		return nullptr;
	}

	Hooking::NativeRegistrationNew * table = m_registrationTable[newHash & 0xFF];

	for (; table; table = table->getNextRegistration())
	{
		for (uint32_t i = 0; i < table->getNumEntries(); i++)
		{
			if (newHash == table->getHash(i))
			{
				return table->handlers[i];
			}
		}
	}
	return nullptr;
}

Hooking::NativeHandler Hooking::GetNativeHandler(uint64_t origHash)
{
	auto& handler = m_handlerCache[origHash];

	if (handler == nullptr)
	{
		handler = _Handler(origHash);
	}

	return handler;
}

eGameState Hooking::GetGameState()
{
	return *m_gameState;
}

BlipList* Hooking::GetBlipList()
{
	return m_blipList;
}

uint64_t Hooking::getWorldPtr()
{
	return m_worldPtr;
}
void WAIT(DWORD ms)
{
	wakeAt = timeGetTime() + ms;
	SwitchToFiber(mainFiber);
}

void Hooking::Cleanup()
{
	Log::Msg("Unhooking Started...");

	/*if (m_object_spawn != nullptr)
		memcpy_s(m_object_spawn, sizeof(object_spawn), object_spawn, sizeof(object_spawn));
	Log::Msg("Object Spawn Bypass Restored.");*/

	iHook.keyboardHandlerUnregister(OnKeyboardMessage);
	iHook.Remove();

	bool b = (MH_DisableHook(&ResetWriteWatch) != MH_OK && MH_RemoveHook(&ResetWriteWatch) != MH_OK);
	b = (MH_DisableHook(Hooking::is_DLC_present) != MH_OK && MH_RemoveHook(Hooking::is_DLC_present) != MH_OK);
	Log::Msg("Main Hook Unloaded.");

	for (int i = 0; i < m_hookedNative.size(); i++)
		b = (MH_DisableHook(m_hookedNative[i]) != MH_OK && MH_RemoveHook(m_hookedNative[i]) != MH_OK);
	Log::Msg("Unloaded All Hooked Natives.");

	MH_Uninitialize();
	Log::Msg("MH_Uninitialize executed.");

	Log::Msg("Unhooking Finished.");
}

void Hooking::defuseEvent(eRockstarEvent e, bool toggle)
{
	static const unsigned char retn = 0xC3;
	char* p = (char*)EventPtr[e];
	if (toggle)
	{
		if (EventRestore[e] == 0)
			EventRestore[e] = p[0];
		*p = retn;
	}
	else
	{
		if (EventRestore[e] != 0)
			*p = EventRestore[e];
	}
}

__int64** Hooking::getGlobalPtr()
{
	return m_globalPtr;
}
__int64 * Hooking::getGlobalPtr1(int index)
{
	return nullptr;
}
__int64 * Hooking::setTunable(int Tunable)
{
	return nullptr;
}
