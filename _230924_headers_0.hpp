#ifndef HEADERS_HPP
#define HEADERS_HPP

#include <fstream>
#include <functional>
#include <mutex>
#include <random>
#include <thread>
#include <unordered_map>
#include "include\Sseu.hpp"
#include "include\FontSource.hpp"
#include ".\AudioSource.hpp"

#include <iostream>
#include <random>

union Lparam{
    bool b;
    long long int ll;
    unsigned long long int ull;
    double d;
    void *p;
    // Lparam() {}
    // ::std::vector<::Lparam> v;
};

enum LparamUsage{
    LU_IS_GRAZED,
    LU_IS_INJURY_FREE,
    LU_IS_IN_SHOOTING_BREAK,
    LU_IS_SHOOTING,
    LU_IS_SLOW,
    LU_SETX,
    LU_SETY,
    LU_DX,
    LU_DY,
    LU_PHI,
    LU_THETA,
    LU_IS_HMIRRORED,
    LU_IS_VMIRRORED,
    LU_TARGET, // 用於表示發起者等
    LU_HEAL,
    LU_EFFECT, // 這是用於表示獲取道具後的效果
    LU_EXISTENCE,
    LU_CHOICE,
    LU_APPENDAGE, // 用於表示附帶的一些物件
    LU_AUDIO_PLAYER,
    LU_DTHETA,
    LU_DPHI
};

struct Updater;
struct QuadDisplayer;
struct MirroredQuadDisplayer;
struct RotatedQuadDisplayer;
struct RectDisplayer;
struct GameareaDisplayeer;
struct InfoDisplayer;
struct FpsDisplayer;

// template<typename> struct UpdaterList;

struct TimedEvent;
struct Timer;

struct MainActivity;
struct GameActivity;

struct Updater{
    unsigned int setting_duration;
    void (*update_func)(void *, ::Lparam);
    ::std::unordered_map<::LparamUsage, ::Lparam> lparam_map;
    inline Updater(unsigned int, void (*)(void *, ::Lparam));
    inline virtual ~Updater() = default;
    inline void update(::Lparam);
    inline virtual void display() { }
};

struct QuadDisplayer : Updater{
    // static ::std::unordered_map<void *, bool> displayer_status;
    // bool is_exsisting;
    // ::std::chrono::system_clock::time_point basetime;
    unsigned int tex_id;
    double x, y, half_width, half_height;
    // ::std::vector<unsigned long long int> lparam_list;
    inline QuadDisplayer(unsigned int, void (*)(void *, ::Lparam), unsigned int, double, double, double, double);
    inline virtual ~QuadDisplayer() override = default;
    inline virtual void display() override;
};

struct MirroredQuadDisplayer : QuadDisplayer{
    inline MirroredQuadDisplayer(unsigned int, void (*)(void *, ::Lparam), unsigned int, double, double, double, double, bool, bool);
    inline virtual ~MirroredQuadDisplayer() override =  default;
    inline virtual void display() override;
};

struct RotatedQuadDisplayer : QuadDisplayer{
    inline RotatedQuadDisplayer(unsigned int, void (*)(void *, ::Lparam), unsigned int, double, double, double, double, double, double);
    // RotatedQuadDisplayer(const ::RotatedQuadDisplayer &) = delete;
    inline virtual ~RotatedQuadDisplayer() override = default;
    inline virtual void display() override;
};

struct RectDisplayer : Updater{
    unsigned int tex_id;
    double x, y, half_width, half_height, rotation;
    inline RectDisplayer(unsigned int, void (*)(void *, ::Lparam), unsigned int, double, double, double, double, double);
    inline virtual ~RectDisplayer() override = default;
    inline virtual void display() override;
};

struct SelectionDisplayer : Updater{
    unsigned int selected;
    double x, y;
    inline SelectionDisplayer(unsigned int, void (*)(void *, ::Lparam));
    inline void display() override;
};

struct GameareaDisplayer{
    double process;
    unsigned char alpha;
    inline GameareaDisplayer();
    inline void display();
    inline void update(const unsigned int);
};

struct InfoDisplayer{
    unsigned int hi_score, score, player, power, graze;
    unsigned int target_score, target_power;
    inline InfoDisplayer();
    inline void display();
    inline void update();
    inline void get_padded_score(unsigned long long int, char[]);
    // inline void displayer_player_stars();
};

struct FpsDisplayer{
    bool is_counting;
    ::std::thread counting_thr;
    unsigned int frame_count;
    ::std::string fps_text;
    inline FpsDisplayer();
    inline void display();
    inline void start_counting();
    inline void stop_counting();
};

// template<typename T> struct UpdaterList : ::std::vector<T>, ::std::mutex{
//     // // static ::std::unordered_map<::QuadDisplayer *, bool> displayer_status;
//     // inline void emplace_displayer(::QuadDisplayer *, ::std::unordered_map<::Updater *, bool> *);
//     // // template<typename T> inline typename ::std::vector<T *>::iterator erase_displayer(typename ::std::vector<T *>::iterator);
//     // inline ::std::vector<::QuadDisplayer *>::iterator erase_displayer(::std::vector<::QuadDisplayer *>::iterator, ::std::unordered_map<::Updater *, bool> *);
// };

struct TimedEvent{
    // static unsigned long long int event_count;
    // unsigned long long int event_id;
    unsigned int time;
    void (*event_func)(void *, ::std::unordered_map<::LparamUsage, ::Lparam> *);
    ::std::unordered_map<::LparamUsage, ::Lparam> lparam_map;
    inline TimedEvent(const unsigned int, void (*)(void *, ::std::unordered_map<::LparamUsage, ::Lparam> *));
    // inline TimedEvent(::TimedEvent const &);
};

struct Timer{
    // bool should_refresh;
    ::std::chrono::system_clock::time_point base_time, curr_time, prev_time, susp_time;
    ::std::vector<::TimedEvent> timed_event_list, prepared_event_list;
    // ::std::vector<unsigned long long int> removed_event_id_list;
    unsigned int duration_from_base, duration_from_prev, duration_suspending, duration_suspending_prev;
    inline Timer();
    // inline double duration_from_base();
    // inline double duration_from_prev();
    inline void prepare(::TimedEvent);
    inline void procedure(void *);
    // inline void remove(unsigned long long int);
    // inline void set_base_time();
    inline void update();
    inline void pause();
    inline void resume();
};

struct MainActivity : Sseu::ActivityBase{
    ::Timer timer;
    bool is_selection_hiden, has_animation_completed;
    ::QuadDisplayer logo_displayer;
    ::SelectionDisplayer selection_displayer;
    ::FpsDisplayer fps_displayer;
    ::std::vector<::RotatedQuadDisplayer *> zzingxua_list;
    ::AudioSource::AudioPlayer bgm_player;
    ::std::vector<::AudioSource::AudioPlayer *> audio_player_list;
    inline MainActivity();
    inline ~MainActivity();
    inline void init() override;
    inline void quit() override;
    inline void update() override;
    inline void procedure(::SDL_Event const) override;
    // inline void display_selections();
    inline void generate_zzingxua();
};

struct GameActivity : Sseu::ActivityBase{
    ::Timer timer;
    bool is_suspending;
    // ::std::vector<::std::thread> thr_list;
    // long long timestamp;
    ::std::unordered_map<::Updater *, bool> updater_status;
    ::Updater *event_updater;
    ::GameareaDisplayer gamearea;
    ::InfoDisplayer info_displayer;
    ::QuadDisplayer logo_displayer;
    ::FpsDisplayer fps_displayer;
    ::MirroredQuadDisplayer tzuihczi, boss;
    ::std::vector<::RotatedQuadDisplayer> tzoiczi_list;
    ::std::vector<::QuadDisplayer *> back_ssiaygoo_list, diqczi_list, tzuihdann_list, diqdann_list, daycziuh_list, ssiaygoo_list;
    ::std::vector<::RectDisplayer *> cziguang_list;
    ::std::vector<::Updater *> removed_updater_list;
    // unsigned int graze_per_128_milliseconds;
    // ::std::vector<::QuadDisplayer *> bullet_list;
    // ::std::mutex bullet_list_mutex;
    ::AudioSource::AudioPlayer *bgm_player, shooting_sound_player;
    ::std::vector<::AudioSource::AudioPlayer *> audio_player_list;
    unsigned int selected;
    ::std::unordered_map<::SDL_Keycode, bool> key_state;
    // , key_down, key_up;
    inline GameActivity();
    inline ~GameActivity();
    inline void init() override;
    inline void quit() override;
    inline void update() override;
    inline void procedure(::SDL_Event const) override;
    inline void display_background();
    inline void display_gamearea_background();
    inline void display_gamearea_box();
    inline void display_judge_point();
    inline void display_suspending_curtain();
    inline void tzuihczi_graze(double const, double const);
    inline void tzuihczi_miss();
    inline void tzuihczi_shoot();
    // inline void graze_quad_displayer(::QuadDisplayer *);
    // inline void graze_line_displayer(::RectDisplayer *);
};

#endif
