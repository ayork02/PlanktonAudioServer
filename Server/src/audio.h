#pragma once

#pragma warning(disable : 4244)

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <portaudio.h>
#include <sndfile.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <csignal>


static char* hms = new char[100];

class Audio
{
protected:
	double duration; // duration in seconds
	PaStreamParameters outputParams;
	PaError paError;
	SNDFILE *sndFile;
	SF_INFO sfInfo;

	Audio(const char* file); // opens audio device
	~Audio();
	virtual void play(unsigned short pos = 0);
	virtual void printSpecs();
	void printDuration();
};

inline PaSampleFormat get_sample_format(int sf_format);

inline char* seconds_to_time(float time);