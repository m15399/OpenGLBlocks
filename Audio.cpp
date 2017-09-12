
Audio g_audio;

void PrintAudioSpec(SDL_AudioSpec& spec, const char* name = "(no name)"){
	printf("Audio :: name: %s, freq: %d, channels: %d, isFloat: %d, bits/sample: %d\n",
		name, spec.freq, spec.channels, SDL_AUDIO_ISFLOAT(spec.format), SDL_AUDIO_BITSIZE(spec.format));
}

// Test...
AudioFile af;
AudioClip clip, clip2;
constexpr bool testAudio = false;


void AudioCallback(void *userData, Uint8 *stream, int len){
	if (len == 0)
		return;

	memset(stream, 0, len);


	if(testAudio){
		clip.Mix(stream, len);
		clip2.Mix(stream, len);
	}
}

void Audio::Init(){
	SDL_memset(&want, 0, sizeof(want));
	want.freq = 44100;
	want.format = AUDIO_F32;
	want.channels = 2;
	want.samples = 4096;
	want.callback = AudioCallback;

	SDL_AudioSpec have;
	SDL_AudioDeviceID dev = SDL_OpenAudioDevice(NULL, SDL_FALSE, &want, &have, 0 /*SDL_AUDIO_ALLOW_FORMAT_CHANGE*/);
	printf("Found audio device: %d\n", dev);
	PrintAudioSpec(have, "have");

	if(testAudio){
		af.Init("b.wav");
		clip.Init(&af);
		clip2.Init(&af);
		clip2.SetTime(0, .6);
	}

	SDL_PauseAudioDevice(dev, false);
}


AudioFile::~AudioFile(){
	if(buffer)
		delete buffer;
	buffer = nullptr;
}

void AudioFile::Init(const char* filename){
	SDL_AudioSpec spec;

	Uint8 *tempBuffer;
	Uint32 tempBufferLen;

	if( SDL_LoadWAV(filename, &spec, &tempBuffer, &tempBufferLen) == nullptr ){
		assert(false);
	}
	printf("Loaded audio: %s, buffer: %p, len: %d\n",
		filename, tempBuffer, tempBufferLen);
	PrintAudioSpec(spec, filename);

	// TODO use global desired audio spec
	SDL_AudioCVT cvt;
	SDL_BuildAudioCVT(&cvt, spec.format, spec.channels, spec.freq, AUDIO_F32, 2, 44100);

	cvt.len = tempBufferLen;
	maxBufferLen = cvt.len * cvt.len_mult;
	buffer = new Uint8[maxBufferLen];
	memset(buffer, 0, maxBufferLen);
	memcpy(buffer, tempBuffer, tempBufferLen);
	cvt.buf = buffer;

	SDL_ConvertAudio(&cvt);

	bufferLen = cvt.len_cvt;
	SDL_FreeWAV(tempBuffer);
}




void AudioClip::Init(AudioFile* file){
	// TODO ref count the file
	audioFile = file;
}

void AudioClip::SetTime(int minutes, double seconds){
	seconds += minutes * 60;

	int bytesPerSecond = 44100 * 4 * 2;
	double targetByte = seconds * bytesPerSecond;
	progress = (int) (unsigned long long) targetByte;
}

void AudioClip::Mix(Uint8* stream, int len){
	if(audioFile == nullptr){
		printf("oops...\n");
		return;
	}

	int lenLeft = audioFile->bufferLen - progress;
	int lenToCopy = std::min(len, lenLeft);

	Uint8* audioPos = audioFile->buffer + progress;

	// TODO this is only supposed to be used for mixing 2 sources
	// SDL_memcpy(stream, audioPos, lenToCopy);
	SDL_MixAudioFormat(stream, audioPos, AUDIO_F32, lenToCopy, SDL_MIX_MAXVOLUME / 2);

	// TODO this doesn't loop 'smoothly' - it pauses after being done for the rest of len
	progress += lenToCopy;
	if(looping && progress >= audioFile->bufferLen){
		progress = 0;
	}
}
