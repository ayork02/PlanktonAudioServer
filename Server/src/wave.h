#pragma once

#include "audio.h"

class Wave : protected Audio
{
public:
	Wave(const char* file);
	~Wave();
	void printSpecs();
	void printDuration();
	void play(unsigned short pos = 0);
private:
	const char* filepath;

	void playPCM16(unsigned short pos = 0);
};