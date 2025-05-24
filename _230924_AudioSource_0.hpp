#ifndef AUDIO_SOURCE_HPP
#define AUDIO_SOURCE_HPP

#include "TexSource.hpp"

// unsigned int shoot_sound_audio_id{0xffffffffU};

namespace AudioSource {
    struct AudioPlayer;

    struct Audio{
        unsigned int length;
        char *data;
        // unsigned long long player_count;
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
        // inline void play_once();
    };
    const unsigned short audio_samples{0x0100U};
    const unsigned char audio_sample_width{0x02U};
    const int audio_freq{44100U};
    const double audio_length_duration_rate{1e3 / ::AudioSource::audio_freq / ::AudioSource::audio_sample_width};
    // ::std::mutex audio_mutex;
    ::std::vector<Audio> audio_list;
    // // 你他媽的我明白了，是他媽我學藝不精，我他媽的忘了::std::vector在擴容時會將原有元素複製到新的地址上，我他媽傻逼了，難怪直接傳地址會導致播放多個音頻就卡退，真你媽神奇。解決方法：將::std::vector<::AudioSource::AudioPlayer>改成::std::vector<::AudioSource::AudioPlayer *>，這樣就好了。
    // ::std::vector<AudioPlayer *> audio_player_list;
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
        "D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\src\\FuuinsaresiKamigami.mem",
        "D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\src\\SluzitiRossii.mem",
        "D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\src\\HarudomannoYoukaiShoujo.mem",
        "D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\src\\Biu.mem",
        "D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\src\\OptionChange.mem",
        "D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\src\\OptionChoose.mem",
        "D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\src\\OptionQuit.mem",
        "D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\src\\ShootingSound.mem",
        "D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\src\\CatchDaycziuh.mem",
        "D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\src\\GrazeSound.mem"
    };
    unsigned int const audio_count{sizeof audio_names / sizeof(::std::string const)};
    ::std::unordered_map<::std::string, unsigned int> audio_ids;
    inline void audio_cbfunc(void *audio_player_ptr, ::Uint8 *audio_stream, int length) {
        ::AudioSource::AudioPlayer *audio_player{reinterpret_cast<::AudioSource::AudioPlayer *>(audio_player_ptr)};
        // ::AudioSource::audio_mutex.lock();
// ::std::cout << __LINE__ << '\t' << audio_player->device_id << '\n';
        if (audio_player->offset + length >= audio_player->audio->length) {
            length = audio_player->audio->length - audio_player->offset;
        }
// ::std::cout << __LINE__ << '\t' << audio_player->device_id << '\n';
        for (unsigned int i{0U}; i < length; ++i) {
            *audio_stream++ = audio_player->audio->data[audio_player->offset++];
        }
// ::std::cout << __LINE__ << '\t' << audio_player->device_id << '\n';
        if (length < ::AudioSource::audio_samples * ::AudioSource::audio_sample_width) {
            audio_player->offset = 0U;
        }
// ::std::cout << __LINE__ << '\t' << audio_player->device_id << '\n';
        // ::AudioSource::audio_mutex.unlock();
        // ::std::this_thread::sleep_for(::std::chrono::milliseconds(256));
// ::std::cout << audio_player << '\n';
        // if (audio_player == ::AudioSource::audio_list.data() + 7) {
        //     ::std::cout << "Shoot sound\n";
        // }
    }
    inline void source_init() {
        for (unsigned int i{0U}; i < ::AudioSource::audio_count; ++i) {
            const unsigned int audio_id(::AudioSource::audio_list.size());
            ::AudioSource::audio_list.emplace_back();
            ::std::ifstream audio_file(::AudioSource::audio_files[i], ::std::ios::binary);
            ::AudioSource::Audio *audio{&::AudioSource::audio_list.back()};
            audio_file.read(reinterpret_cast<char *>(&audio->length), 4ULL);
            audio->data = new char[audio->length];
            audio_file.read(audio->data, audio->length);
            audio_file.close();
            ::AudioSource::audio_ids.emplace(::AudioSource::audio_names[i], audio_id);
        }
                                                                // ::shoot_sound_audio_id = ::AudioSource::audio_ids["shoot_sound"];
    }
    inline void source_quit() {
        for (::std::vector<::AudioSource::Audio>::iterator audio_it(::AudioSource::audio_list.begin()); audio_it != ::AudioSource::audio_list.end(); ++audio_it) {
            delete audio_it->data;
        }
    }
    AudioPlayer::AudioPlayer(unsigned int audio_id): audio{::AudioSource::audio_list.data() + audio_id}, offset{0U} {
        ::SDL_AudioSpec audio_spec{.freq = ::AudioSource::audio_freq, .format = AUDIO_S16SYS, .channels = 1, .samples = ::AudioSource::audio_samples,  .callback = &::AudioSource::audio_cbfunc, .userdata = this};
        this->device_id = ::SDL_OpenAudioDevice(nullptr, 0, &audio_spec, nullptr, 0);
        // ::std::cout << this->device_id << "\topen\n";
    }
    AudioPlayer::~AudioPlayer() {
        ::SDL_CloseAudioDevice(this->device_id);
        // ::std::cout << this->device_id << "\tclose\n";
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
    // void AudioPlayer::play_once() {
    //     this->play();
    //     ::std::thread([this]() -> void {
    //         ::std::this_thread::sleep_for(::std::chrono::milliseconds(int(this->audio->length * ::AudioSource::audio_length_duration_rate)));
    //         if (this->is_playing()) {
    //             this->pause();
    //         }
    //     }).detach();
    // }
    inline void play_audio_once(unsigned int audio_id) {
        ::AudioSource::AudioPlayer *audio_player{new ::AudioSource::AudioPlayer(audio_id)};
        audio_player->play();
        ::std::thread([audio_player]() -> void {
            ::std::this_thread::sleep_for(::std::chrono::milliseconds(int(audio_player->audio->length * ::AudioSource::audio_length_duration_rate)));
// ::std::cout << __LINE__ << '\t' << '\n';
            // if (audio_player != nullptr) {
// ::std::cout << __LINE__ << '\t' << '\n';
            audio_player->pause();
            delete audio_player;
// ::std::cout << __LINE__ << '\t' << '\n';
            // }
// ::std::cout << __LINE__ << '\t' << '\n';
        }).detach();
    }
//     inline ::AudioSource::AudioPlayer *play_audio(unsigned int audio_id) {
//         ::AudioSource::audio_player_list.push_back(new ::AudioSource::AudioPlayer{::AudioSource::audio_list.data() + audio_id});
//         ::AudioSource::AudioPlayer *audio_player{::AudioSource::audio_player_list.back()};
// // long long int lt;
// // if (audio_id == ::AudioSource::audio_ids["graze_sound"]) { long long int ct{::std::chrono::system_clock::now().time_since_epoch().count()}; ::std::cout << ct - lt << '\n'; lt = ct; }
//         ::SDL_AudioSpec audio_spec{};
//         audio_spec.freq = ::AudioSource::audio_freq;
//         audio_spec.format = AUDIO_S16SYS;
//         audio_spec.channels = 1;
//         audio_spec.samples = ::AudioSource::audio_samples;
//         audio_spec.callback = &::AudioSource::audio_cbfunc;
// // if (audio_id == ::AudioSource::audio_ids["graze_sound"]) { long long int ct{::std::chrono::system_clock::now().time_since_epoch().count()}; ::std::cout << ct - lt << '\n'; lt = ct; }
//         audio_spec.userdata = audio_player;
// // if (audio_id == ::AudioSource::audio_ids["graze_sound"]) { long long int ct{::std::chrono::system_clock::now().time_since_epoch().count()}; ::std::cout << ct - lt << '\n'; lt = ct; }
//         audio_player->device_id = ::SDL_OpenAudioDevice(nullptr, 0, &audio_spec, nullptr, 0);
// // if (audio_id == ::AudioSource::audio_ids["graze_sound"]) { long long int ct{::std::chrono::system_clock::now().time_since_epoch().count()}; ::std::cout << ct - lt << '\n'; lt = ct; }
//         ::SDL_PauseAudioDevice(audio_player->device_id, 0);
// // if (audio_id == ::AudioSource::audio_ids["graze_sound"]) { long long int ct{::std::chrono::system_clock::now().time_since_epoch().count()}; ::std::cout << ct - lt << '\n'; lt = ct; ::std::cin.get(); }
//         return audio_player;
//     }
//     inline void pause_audio(::AudioSource::AudioPlayer *audio_player) {
//         // ::SDL_AudioDeviceID audio_device_id{audio_player->device_id};
// // ::std::cout << __LINE__ << '\t' << audio_player->device_id << '\n';
//         ::SDL_PauseAudioDevice(audio_player->device_id, 1);
// // ::std::cout << __LINE__ << '\t' << '\n';
//         ::SDL_CloseAudioDevice(audio_player->device_id);
// // ::std::cout << __LINE__ << '\t' << '\n';
//     }
//     inline void rewind_audio(::AudioSource::AudioPlayer *audio_player) {
//         audio_player->offset = 0U;
//     }
//     inline bool is_audio_playing(::AudioSource::AudioPlayer *audio_player) {
//         return ::SDL_GetAudioDeviceStatus(audio_player->device_id) == SDL_AUDIO_PLAYING;
//     }
//     inline void play_audio_once(unsigned int audio_id) {
// // // if (audio_id == ::AudioSource::audio_ids["graze_sound"]) { ::std::cout << ::std::chrono::system_clock::now().time_since_epoch().count() << '\n'; }
// //         unsigned long long int const audio_player_id{++::AudioSource::audio_list[audio_id].player_count};
// // // ::std::cout << "audio_player_id\t" << audio_player_id << '\n';
// //         if (::AudioSource::is_audio_playing(audio_id)) {
// //             ::AudioSource::pause_audio(audio_id);
// //         }
// // // if (audio_id == ::AudioSource::audio_ids["graze_sound"]) { ::std::cout << ::std::chrono::system_clock::now().time_since_epoch().count() << '\n'; }
// //         ::AudioSource::rewind_audio(audio_id);
// //         ::AudioSource::play_audio(audio_id);
// // // if (audio_id == ::AudioSource::audio_ids["graze_sound"]) { ::std::cout << ::std::chrono::system_clock::now().time_since_epoch().count() << '\n'; }
// // // ::std::cout << ::AudioSource::audio_list[audio_id].length << '\t' << ::AudioSource::audio_list[audio_id].length / (::AudioSource::audio_freq * 2.0) * 1000 << '\n';
// //         ::std::thread([audio_id, audio_player_id]() -> void {
// //             ::std::this_thread::sleep_for(::std::chrono::milliseconds(::AudioSource::audio_list[audio_id].length * 1000 / ::AudioSource::audio_freq / ::AudioSource::audio_sample_width));
// //             if (::AudioSource::audio_list[audio_id].player_count == audio_player_id && ::AudioSource::is_audio_playing(audio_id)) {
// //                 ::AudioSource::pause_audio(audio_id);
// //             }
// //         }).detach();
// // // if (audio_id == ::AudioSource::audio_ids["graze_sound"]) { ::std::cout << ::std::chrono::system_clock::now().time_since_epoch().count() << '\n'; }
// // // if (audio_id == ::AudioSource::audio_ids["graze_sound"]) { ::std::cin.get(); }
//         ::AudioSource::AudioPlayer *audio_player{::AudioSource::play_audio(audio_id)};
//         ::std::thread([audio_player]() -> void {
//             ::std::this_thread::sleep_for(::std::chrono::milliseconds(audio_player->audio->length * 1000 / ::AudioSource::audio_freq / ::AudioSource::audio_sample_width));
// // ::std::cout << __LINE__ << '\t' << '\n';
//             if (::AudioSource::is_audio_playing(audio_player)) {
//                 ::AudioSource::pause_audio(audio_player);
//             }
// // ::std::cout << __LINE__ << '\t' << '\n';
//         }).detach();
//     }
}

#endif
