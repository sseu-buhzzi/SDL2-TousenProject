#include ".\include\sdl\SDL2\SDL.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <windows.h>

::std::vector<unsigned char> get_data() {
    ::std::vector<unsigned char> data;
    ::std::ifstream mem("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\src\\SluzitiRossii.mem", ::std::ios::binary);
    unsigned int length;
    mem.read(reinterpret_cast<char *>(&length), 4ULL);
    while (!mem.eof()) {
        data.emplace_back(mem.get());
    }
    mem.close();
    // for (unsigned char d : data) {
    //     ::std::cout << int(d) << ' ';
    // }
    ::std::cout << data.size() << '\n';
    return data;
}

unsigned long long data_offset{0ULL};

void audioCallback(void* userdata, Uint8* stream, int len) {
    unsigned char* audioData = static_cast<unsigned char*>(userdata);

    for (int i = 0; i < len; ++i) {
        *stream++ = audioData[data_offset++];
    }
}

int WINAPI WinMain(::HINSTANCE, ::HINSTANCE, ::LPTSTR, int) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        SDL_Log("SDL initialization failed: %s", SDL_GetError());
        return 1;
    }

    // unsigned char recordedAudio[] = { /* Your recorded audio data here */ };
    ::std::vector<unsigned char> data(::get_data());
    unsigned char *recordedAudio{data.data()};

    SDL_AudioSpec wantedSpec, obtainedSpec;
    wantedSpec.freq = 44100;  // 采样率
    wantedSpec.format = AUDIO_S16SYS;  // 格式：8位无符号整数
    wantedSpec.channels = 1;  // 声道数
    wantedSpec.samples = 0xffff;  // 缓冲区大小
    wantedSpec.callback = audioCallback;
    wantedSpec.userdata = recordedAudio;  // 传递录制好的音频数据

    SDL_AudioDeviceID audioDevice = SDL_OpenAudioDevice(NULL, 0, &wantedSpec, &obtainedSpec, 0);
    if (audioDevice == 0) {
        SDL_Log("Failed to open audio: %s", SDL_GetError());
        return 1;
    }

    SDL_PauseAudioDevice(audioDevice, 0);

    // 在这里等待音频播放完毕
    ::std::cin.get();

    SDL_PauseAudioDevice(audioDevice, 1);
    SDL_CloseAudioDevice(audioDevice);

    SDL_Quit();

    return 0;
}
