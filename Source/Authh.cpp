#pragma once
#include "stdafx.h"
using std::string;

#define URL L"https://ars3n1c.com/Auth/"
int Features::menu_version;

bool isCredsValid = false;

std::string authFile = ".\\Project\\auth.ini";
std::string username = GUI::Files::ReadStringFromIni(authFile, "Login", "Username");
std::string password = GUI::Files::ReadStringFromIni(authFile, "Login", "Password");

bool isAuthValid(std::string username, std::string password)
{
	char hwid[4096];
	// total physical memory
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);
	sprintf_s(hwid, "%I64i", statex.ullTotalPhys / 1024);

	// volume information
	TCHAR volumename[MAX_PATH + 1] = { 0 };
	TCHAR filesystemname[MAX_PATH + 1] = { 0 };
	DWORD serialnumber = 0, maxcomponentlen = 0, filesystemflags = 0;
	GetVolumeInformation(_T("C:\\"), volumename, ARRAYSIZE(volumename), &serialnumber, &maxcomponentlen, &filesystemflags, filesystemname, ARRAYSIZE(filesystemname));
	sprintf_s(hwid, "%s%li%ws%li", hwid, serialnumber, filesystemname, maxcomponentlen);

	// computer name
	TCHAR computerName[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD size = sizeof(computerName) / sizeof(computerName[0]);
	GetComputerName(computerName, &size);
	sprintf_s(hwid, "%s%ws", hwid, computerName);

	net::requests m_request(L"galaxy-five", false);
	std::wstring answer = m_request.Post(false, URL, "username=%s&password=%s&hwid=%s", username.c_str(), password.c_str(), (sw::sha512::calculate(hwid)).c_str());
	if (answer == L"Try again") {
		answer = m_request.Post(false, URL, "username=%s&password=%s&hwid=%s", username.c_str(), password.c_str(), (sw::sha512::calculate(hwid)).c_str());
	}

	if (answer == L"WRONG LOGIN") {
		return false;
	}
	else if (answer == L"VIP+") {
		Features::menu_version = 2;
		Log::Msg("VIP+ Access Granted.");
		return true; //VIP
	}
	else if (answer == L"VIP") {
		Features::menu_version = 1;
		Log::Msg("VIP Access Granted.");
		return true; // VIP
	}
	else if (answer == L"MEMBER") {
		Features::menu_version = 0;
		Log::Fatal("Access Denied.");
		return false; // Account, Not Paid.
	}
	else if (answer == L"NO RESULTS") {
		return false;
	}
	else if (answer == L"WRONG HWID") {
		Features::menu_version = 3;
		Log::Fatal("Your HWID does not match our records. Contact a staff.");
		return false;
	}
	else
		return false;
}