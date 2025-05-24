#ifndef AUDIO_SOURCE_HPP
#define AUDIO_SOURCE_HPP

#include "TexSource.hpp"

namespace AudioSource {
    struct Audio{
        unsigned int length;
        char *data;
    };
    struct AudioPlayer{
        ::AudioSource::Audio *audio;
        unsigned int offset;
        ::SDL_AudioDeviceID device_id;
        inline AudioPlayer(unsigned int audio_id);
        inline ~AudioPlayer();
        inline void play();
        inline void pause();
        inline bool is_playing();
    };
    const unsigned short audio_samples{0x0100U};
    const unsigned char audio_sample_width{0x02U};
    const int audio_freq{44100U};
    const double audio_length_duration_rate{1e3 / ::AudioSource::audio_freq / ::AudioSource::audio_sample_width};
    ::std::vector<Audio> audio_list;
    ::std::string const audio_names[]{
        "fuuinsaresi_kamigami",
        "sluziti_rossii",
        "harudomanno_youkai_shoujo",
        "biu",
        "option_change",
        "option_choose",
        "option_quit",
        "shooting_sound",
        "catch_daycziuh",
        "graze_sound"
    };
    ::std::string const audio_files[]{
        "FuuinsaresiKamigami.mem",
        "SluzitiRossii.mem",
        "HarudomannoYoukaiShoujo.mem",
        "Biu.mem",
        "OptionChange.mem",
        "OptionChoose.mem",
        "OptionQuit.mem",
        "ShootingSound.mem",
        "CatchDaycziuh.mem",
        "GrazeSound.mem"
    };
    unsigned int const audio_count{sizeof audio_names / sizeof(::std::string const)};
    ::std::unordered_map<::std::string, unsigned int> audio_ids;
    inline void audio_cbfunc(void *audio_player_ptr, ::Uint8 *audio_stream, int length) {
        ::AudioSource::AudioPlayer *audio_player{reinterpret_cast<::AudioSource::AudioPlayer *>(audio_player_ptr)};
        if (audio_player->offset + length >= audio_player->audio->length) {
            length = audio_player->audio->length - audio_player->offset;
        }
        for (int i{0}; i < length; ++i) {
            *audio_stream++ = audio_player->audio->data[audio_player->offset++];
        }
        if (length < ::AudioSource::audio_samples * ::AudioSource::audio_sample_width) {
            audio_player->offset = 0U;
        }
    }
    inline void source_init(const ::std::string &src_dir) {
        for (unsigned int i{0U}; i < ::AudioSource::audio_count; ++i) {
            const unsigned int audio_id(::AudioSource::audio_list.size());
            ::AudioSource::audio_list.emplace_back();
            ::std::ifstream audio_file(src_dir + ::AudioSource::audio_files[i], ::std::ios::binary);
            ::AudioSource::Audio *audio{&::AudioSource::audio_list.back()};
            audio_file.read(reinterpret_cast<char *>(&audio->length), 4ULL);
            audio->data = new char[audio->length];
            audio_file.read(audio->data, audio->length);
            audio_file.close();
            ::AudioSource::audio_ids.emplace(::AudioSource::audio_names[i], audio_id);
        }
    }
    inline void source_quit() {
        for (::std::vector<::AudioSource::Audio>::iterator audio_it(::AudioSource::audio_list.begin()); audio_it != ::AudioSource::audio_list.end(); ++audio_it) {
            delete audio_it->data;
        }
    }
    AudioPlayer::AudioPlayer(unsigned int audio_id): audio{::AudioSource::audio_list.data() + audio_id}, offset{0U} {
        ::SDL_AudioSpec audio_spec{.freq = ::AudioSource::audio_freq, .format = AUDIO_S16SYS, .channels = 1, .samples = ::AudioSource::audio_samples,  .callback = &::AudioSource::audio_cbfunc, .userdata = this};
        this->device_id = ::SDL_OpenAudioDevice(nullptr, 0, &audio_spec, nullptr, 0);
    }
    AudioPlayer::~AudioPlayer() {
        ::SDL_CloseAudioDevice(this->device_id);
    }
    void AudioPlayer::play() {
        ::SDL_PauseAudioDevice(this->device_id, 0);
    }
    void AudioPlayer::pause() {
        ::SDL_PauseAudioDevice(this->device_id, 1);
    }
    bool AudioPlayer::is_playing() {
        return ::SDL_GetAudioDeviceStatus(this->device_id) == SDL_AUDIO_PLAYING;
    }
    inline void play_audio_once(unsigned int audio_id) {
        ::AudioSource::AudioPlayer *audio_player{new ::AudioSource::AudioPlayer(audio_id)};
        audio_player->play();
        ::std::thread([audio_player]() -> void {
            ::std::this_thread::sleep_for(::std::chrono::milliseconds(int(audio_player->audio->length * ::AudioSource::audio_length_duration_rate)));
            audio_player->pause();
            delete audio_player;
        }).detach();
    }
}

#endif
