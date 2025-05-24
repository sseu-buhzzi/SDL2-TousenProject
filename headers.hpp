#ifndef HEADERS_HPP
#define HEADERS_HPP

#include <fstream>
#include <functional>
#include <mutex>
#include <random>
#include <thread>
#include <unordered_map>
#include "include/Sseu.hpp"
#include "include/FontSource.hpp"
#include "./AudioSource.hpp"

#include <iostream>
#include <random>


#ifndef M_E
#define M_E 2.7182818284590452354
#endif
#ifndef M_LOG2E
#define M_LOG2E 1.4426950408889634074
#endif
#ifndef M_LOG10E
#define M_LOG10E 0.43429448190325182765
#endif
#ifndef M_LN2
#define M_LN2 0.69314718055994530942
#endif
#ifndef M_LN10
#define M_LN10 2.30258509299404568402
#endif
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_PI_2
#define M_PI_2 1.57079632679489661923
#endif
#ifndef M_PI_4
#define M_PI_4 0.78539816339744830962
#endif
#ifndef M_1_PI
#define M_1_PI 0.31830988618379067154
#endif
#ifndef M_2_PI
#define M_2_PI 0.63661977236758134308
#endif
#ifndef M_2_SQRTPI
#define M_2_SQRTPI 1.12837916709551257390
#endif
#ifndef M_SQRT2
#define M_SQRT2 1.41421356237309504880
#endif
#ifndef M_SQRT1_2
#define M_SQRT1_2 0.70710678118654752440
#endif

union Lparam{
    bool b;
    long long int ll;
    unsigned long long int ull;
    double d;
    void *p;
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
    LU_DISTANCE,
    LU_DTHETA,
    LU_DPHI,
    LU_DURATION,
    LU_LIST, // 給子機的偏移量設置的表
    LU_DDX,
    LU_DDY
};

struct Updater;
struct QuadDisplayer;
struct MirroredQuadDisplayer;
struct RotatedQuadDisplayer;
struct RectDisplayer;
struct GameareaDisplayeer;
struct InfoDisplayer;
struct FpsDisplayer;

struct TimedEvent;
struct Timer;

struct LaunchActivity;
struct MainActivity;
struct LoadActivity;
struct GameActivity;

struct Updater{
    unsigned int setting_duration;
    void (*update_func)(void *);
    ::std::unordered_map<::LparamUsage, ::Lparam> lparam_map;
    inline Updater(unsigned int, void (*)(void *));
    inline virtual ~Updater() = default;
    inline void update();
    inline virtual void display() { }
};

struct QuadDisplayer : Updater{
    unsigned int tex_id;
    double x, y, half_width, half_height;
    inline QuadDisplayer(unsigned int, void (*)(void *), unsigned int, double, double, double, double);
    inline virtual ~QuadDisplayer() override = default;
    inline virtual void display() override;
};

struct MirroredQuadDisplayer : QuadDisplayer{
    inline MirroredQuadDisplayer(unsigned int, void (*)(void *), unsigned int, double, double, double, double, bool, bool);
    inline virtual ~MirroredQuadDisplayer() override =  default;
    inline virtual void display() override;
};

struct RotatedQuadDisplayer : QuadDisplayer{
    inline RotatedQuadDisplayer(unsigned int, void (*)(void *), unsigned int, double, double, double, double, double, double);
    inline virtual ~RotatedQuadDisplayer() override = default;
    inline virtual void display() override;
};

struct RectDisplayer : Updater{
    unsigned int tex_id;
    double x, y, half_width, half_height, rotation;
    inline RectDisplayer(unsigned int, void (*)(void *), unsigned int, double, double, double, double, double);
    inline virtual ~RectDisplayer() override = default;
    inline virtual void display() override;
};

struct SelectionDisplayer : Updater{
    unsigned int selected;
    double x, y;
    inline SelectionDisplayer(unsigned int, void (*)(void *));
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

struct TimedEvent{
    unsigned int duration;
    void (*event_func)(::std::unordered_map<::LparamUsage, ::Lparam> *);
    ::std::unordered_map<::LparamUsage, ::Lparam> lparam_map;
    inline TimedEvent(const unsigned int, void (*)(::std::unordered_map<::LparamUsage, ::Lparam> *));
};

struct Timer{
    ::std::chrono::system_clock::time_point base_time, curr_time, prev_time, susp_time;
    ::std::vector<::TimedEvent> timed_event_list, prepared_event_list;
    unsigned int duration_from_base, duration_from_prev, duration_suspending, duration_suspending_prev;
    inline Timer();
    inline void prepare(::TimedEvent);
    inline void procedure();
    inline void update();
    inline void pause();
    inline void resume();
};

struct LaunchActivity : Sseu::ActivityBase{
    ::Timer timer;
    ::QuadDisplayer logo_sseu;
    unsigned char alpha;
    bool should_quit;
    inline LaunchActivity();
    inline ~LaunchActivity() override;
    inline void init() override;
    inline void quit() override;
    inline void update() override;
    inline void procedure(const ::SDL_Event) override;
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
    inline ~MainActivity() override;
    inline void init() override;
    inline void quit() override;
    inline void update() override;
    inline void procedure(::SDL_Event const) override;
    inline void display_background();
    inline void generate_zzingxua();
};

struct LoadActivity : Sseu::ActivityBase{
    
};

struct GameActivity : Sseu::ActivityBase{
    ::Timer timer;
    bool is_suspending;
    ::std::unordered_map<::Updater *, bool> updater_status;
    ::Updater *event_updater;
    ::GameareaDisplayer gamearea;
    ::InfoDisplayer info_displayer;
    ::QuadDisplayer logo_displayer;
    ::FpsDisplayer fps_displayer;
    ::MirroredQuadDisplayer tzuihczi, *boss;
    ::std::vector<::RotatedQuadDisplayer *> tzoiczi_list;
    ::std::vector<::QuadDisplayer *> back_ssiaygoo_list, diqczi_list, tzuihdann_list, diqdann_list, daycziuh_list, ssiaygoo_list;
    ::std::vector<::RectDisplayer *> cziguang_list;
    ::std::vector<::Updater *> removed_updater_list;
    ::AudioSource::AudioPlayer *bgm_player, shooting_sound_player;
    ::std::vector<::AudioSource::AudioPlayer *> audio_player_list;
    unsigned int selected;
    ::std::unordered_map<::SDL_Keycode, bool> key_state;
    inline GameActivity();
    inline ~GameActivity() override;
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
    inline void tzuihczi_shoot_and_break();
};

#endif
