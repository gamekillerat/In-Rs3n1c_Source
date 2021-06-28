#pragma once
#include "stdafx.h"

extern std::string username, password;
extern std::string authFile;

extern bool isCredsValid;

bool isAuthValid(std::string username, std::string password);

