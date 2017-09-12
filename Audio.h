
class Audio {
public:
	SDL_AudioSpec want;

	void Init();
};

extern Audio g_audio;

class AudioFile {
public:
	Uint8 *buffer = nullptr;
	Uint32 bufferLen = 0;
	int maxBufferLen;

	~AudioFile();

	void Init(const char* filename);

};

class AudioClip {
public:

	AudioFile* audioFile = nullptr;
	int progress = 0;
	bool looping = true;

	void Init(AudioFile* audioFile);
	void Mix(Uint8* stream, int len);
	void SetTime(int minutes, double seconds);

};

