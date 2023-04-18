#pragma once

#include <stdio.h>

FILE* logOut;

void logOpen(const char* file);

void mlog(const char* format, ...);
