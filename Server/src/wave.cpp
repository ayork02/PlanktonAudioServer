#include "wave.h"

Wave::Wave(const char* file)
:	Audio(file)
{
	filepath = file;
	if(sfInfo.format & SF_FORMAT_TYPEMASK != SF_FORMAT_WAV)
	{
		std::cerr << "Invalid WAVE File" << std::endl;
		exit(1);
	}
}

Wave::~Wave()
{

}

void Wave::printSpecs()
{
	FILE *file;
	file = fopen(filepath, "rb");
	int read = 0;
	char riff[4];
	read = fread(riff, 4, 1, file);
	unsigned int overallSize; // overall size of file in bytes
	read = fread(reinterpret_cast<char*>(&overallSize), 4, 1, file);
	printf("File Size: %u bytes\n", overallSize);
	char wavChunk[4];
	read = fread(wavChunk, 4, 1, file);
	char fmtChunkMarker[4];
	if(memcmp(fmtChunkMarker, "fmt ", 4) != 0) // it works, don't ask questions
	{
		read = fread(fmtChunkMarker, 4, 1, file);
	}
	unsigned int fmtLength; // length of the format data
	read = fread(reinterpret_cast<char*>(&fmtLength), 4, 1, file);
	unsigned short fmtType; // 1-PCM, 3-IEEE float, 6-8bit A law, 7-8bit mu law
	read = fread(reinterpret_cast<char*>(&fmtType), 2, 1, file);
	std::string fmtName;
	if(fmtType == 1)
		fmtName = "PCM";
	else if(fmtType == 6)
		fmtName = "A-law";
	else if (fmtType == 7)
		fmtName = "Mu-law";
	printf("Format Type: %s\n", fmtName.c_str());
	unsigned short numChannels; // number of channels
	read = fread(reinterpret_cast<char*>(&numChannels), 2, 1, file);
	printf("Channels: %u\n", numChannels);
	unsigned int sampleRate; // blocks per second
	read = fread(reinterpret_cast<char*>(&sampleRate), 4, 1, file);
	printf("Sample Rate: %u\n", sampleRate);
	unsigned int byteRate; // sampleRate * channels * bitsPerSample
	read = fread(reinterpret_cast<char*>(&byteRate), 4, 1, file);
	printf("Byte Rate: %u, Bit Rate: %u\n", byteRate, byteRate * 8);
	unsigned short blockAlign; // channels * bitsPerSample/8
	read = fread(reinterpret_cast<char*>(&blockAlign), 2, 1, file);
	printf("Block Alignment: %u\n", blockAlign);
	unsigned short bitsPerSample; // 8 - 8 bits, 16 - 16 bits etc.
	read = fread(reinterpret_cast<char*>(&bitsPerSample), 2, 1, file);
	printf("Bits per Sample: %u\n", bitsPerSample);
	char dataChunkHeader[4]; // DATA string or FLLr string	
	char subChunkLength;
	while (true) // skip over other subchunks
	{
		fread(dataChunkHeader, 4, 1, file);
		if (memcmp(dataChunkHeader, "data", 4) != 0)
			{
				read = fread(reinterpret_cast<char*>(&subChunkLength), 4, 1, file);
				fseek(file, subChunkLength, SEEK_CUR);
			}
		else
		{
			break;
		}
	}
	unsigned int dataSize; // size of chunk to be read
	read = fread(reinterpret_cast<char*>(&dataSize), 4, 1, file);
	printf("Size of Data Chunk: %u\n", dataSize);
	unsigned int numSamples; // 8 * dataSize / (channels * bitsPerSample)
	numSamples = (8 * dataSize) / (numChannels * bitsPerSample);
	printf("Number of Samples: %u\n", numSamples);
	unsigned int sampleSize; // size of each sample in bytes
	sampleSize = (numChannels * bitsPerSample) / 8;
	printf("Size of Each Sample: %u bytes\n", sampleSize);
	fclose(file);
}

void Wave::play(unsigned short pos)
{
	if(outputParams.sampleFormat == paInt16)
	{
		playPCM16(pos);
	}	
}

void Wave::playPCM16(unsigned short pos)
{
	short* data;
	sf_count_t readCount;
	PaError paError;
	PaStream *stream;
	data = (short*)malloc(sfInfo.frames * sfInfo.channels * sizeof(short));
	paError = Pa_OpenStream(
        &stream, NULL, &outputParams,
        sfInfo.samplerate, 1024, paClipOff,
        NULL, NULL);
    if(paError != paNoError)
	{
		std::cerr << "Error Opening Stream: " << Pa_GetErrorText(paError) << std::endl;
        Pa_Terminate();
		exit(1);
	}
    paError = Pa_StartStream(stream);
    if(paError != paNoError)
	{
		std::cerr << "Error Starting Stream: " << Pa_GetErrorText(paError) << std::endl;
        Pa_Terminate();
		exit(1);
	}

	while((readCount = sf_readf_short(sndFile, data, 1024)))
    {
        paError = Pa_WriteStream(stream, data, 1024);
        if (paError != paNoError)
        {
            std::cerr << "Error Writing to Stream: " << Pa_GetErrorText(paError) << std::endl;
        	Pa_AbortStream(stream);
			exit(1);
        }
    }
	paError = Pa_CloseStream(stream);
	if(paError != paNoError)
	{
		std::cerr << "Error Closing Stream: " << Pa_GetErrorText(paError) << std::endl;
        Pa_Terminate();
		exit(1);
	}
	free(data);
}