#pragma once

#include <stdio.h>

FILE* logOut;

void logOpen(const char* file);

void logClose(char* file);

void messageLog(char* format, char* message);