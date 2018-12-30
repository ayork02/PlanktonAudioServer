#include "audio.h"

Audio::Audio(const char* file)
{
	sndFile = sf_open(file, SFM_READ, &sfInfo);
	if (!sndFile) // TODO: Add file validation
	{
		std::cerr << "Error Opening File" << std::endl;
		exit(1);
	}
    paError = Pa_Initialize();
	if(paError != paNoError) // TODO: Make inline function
	{
		std::cerr << "Error Initialising PortAudio: " << Pa_GetErrorText(paError) << std::endl;
        Pa_Terminate();
		exit(1);
	}
	if(sfInfo.channels == !(1 || 2))
	{
		std::cerr << "Channel Number Not Supported" << std::endl;
		exit(1);
	}
	outputParams.channelCount = sfInfo.channels;
	outputParams.sampleFormat = get_sample_format(sfInfo.format & SF_FORMAT_SUBMASK);
	outputParams.device = Pa_GetDefaultOutputDevice();
	outputParams.suggestedLatency = Pa_GetDeviceInfo(outputParams.device)->defaultLowOutputLatency;
	outputParams.hostApiSpecificStreamInfo = NULL;
}

Audio::~Audio()
{
    sf_close(sndFile);
	paError = Pa_Terminate();
	if(paError != paNoError)
	{
		std::cerr << "Error Terminating PortAudio: " << Pa_GetErrorText(paError) << std::endl;
		exit(1);
	}
}

void Audio::play(unsigned short pos)
{

}

void Audio::printSpecs()
{

}

void Audio::printDuration()
{
	duration = sfInfo.frames / sfInfo.samplerate;
	printf("Approximate Duration: %s", seconds_to_time(duration));
	delete[] hms;
}

inline PaSampleFormat get_sample_format(int sf_format)
{
	switch(sf_format)
	{
		case SF_FORMAT_PCM_S8 : 
			return paInt8;
		case SF_FORMAT_PCM_16 : 
			return paInt16;
		case SF_FORMAT_PCM_24 : 
			return paInt24;
		case SF_FORMAT_PCM_32 : 
			return paInt32;
		case SF_FORMAT_PCM_U8 : 
			return paUInt8;
		case SF_FORMAT_FLOAT : 
			return paFloat32;
		default :
			std::cerr << "Format Not Supported" << std::endl;
			exit(1);
	}
}

inline char* seconds_to_time(float time)
{
	float seconds = time;
	int hour = seconds / 3600;
	seconds = (int)seconds % 3600;
	int min = seconds / 60;
	int millisec = (seconds - (int)seconds) * 100;
	int sec = (int)seconds % 60;
	sprintf(hms, "%d:%d:%d.%d", hour, min, sec, millisec);
	return hms;
}