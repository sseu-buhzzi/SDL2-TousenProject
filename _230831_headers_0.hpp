#ifndef HEADERS_HPP
#define HEADERS_HPP

#include <fstream>
#include <functional>
#include <mutex>
#include <random>
#include <thread>
#include <unordered_map>
// #include <unordered_set>
#include "include\Sseu.hpp"
#include "include\FontSource.hpp"

#include <iostream>
#include <random>

struct QuadDisplayer;
struct MirroredQuadDisplayer;
struct TzuihcziDisplayer;
struct OrientedQuadDisplayer;
struct RotatedQuadDisplayer;
struct TrackingQuadDisplayer;
struct TzoicziDisplayer;
struct LocatedQuadDisplayer;
struct LineDisplayer;
struct GameareaBackgroundDisplayer;
struct FpsDisplayer;

template<typename> struct DisplayerList;

struct TimedEvent;
struct EventTimer;

struct MainActivity;
struct GameActivity;

struct QuadDisplayer{
    bool is_exsisting;
    long long exsist_time;
    unsigned int tex_id;
    double half_width, half_height;
    void (*updater)(void *);
    double x, y;
    inline QuadDisplayer(unsigned int, double, double, void (*)(void *), double, double);
    inline ~QuadDisplayer();
    inline virtual void display();
    inline void update();
};

struct MirroredQuadDisplayer : QuadDisplayer{
    bool is_mirrored;
    inline MirroredQuadDisplayer(unsigned int, double, double, void (*)(void *), double, double, bool);
    inline virtual void display() override;
};

struct TzuihcziDisplayer : MirroredQuadDisplayer{
    double moving_speed;
    bool is_shooting, is_injury_free;
    ::std::thread shooting_thr;
    inline TzuihcziDisplayer(unsigned int, double, double, void (*)(void *), double, double, bool);
    inline void display_judge_point();
};

struct OrientedQuadDisplayer : QuadDisplayer{
    double set_x, set_y, dx, dy;
    inline OrientedQuadDisplayer(unsigned int, double, double, void (*)(void *), double, double, double);
};

struct RotatedQuadDisplayer : QuadDisplayer{
    double phi, theta;
    inline RotatedQuadDisplayer(unsigned int, double, double, void (*)(void *), double, double, double, double);
    inline virtual void display() override;
};

struct TrackingQuadDisplayer : RotatedQuadDisplayer{
    ::QuadDisplayer *target_displayer;
    inline TrackingQuadDisplayer(unsigned int, double, double, void (*)(void *), double, double, double, double, ::QuadDisplayer *);
};

struct TzoicziDisplayer : RotatedQuadDisplayer{
    double offset_x, offset_y;
    ::TzuihcziDisplayer *tzuihczi;
    inline TzoicziDisplayer(unsigned int, double, double, void (*)(void *), double, double, ::TzuihcziDisplayer *, double, double);
};

struct LocatedQuadDisplayer : QuadDisplayer{
    ::std::vector<double> located_x, located_y;
    using ::QuadDisplayer::QuadDisplayer;
};

struct LineDisplayer{};

struct GameareaBackgroundDisplayer{
    double process;
    inline GameareaBackgroundDisplayer();
    inline void display();
    inline void update();
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

template<typename T> struct DisplayerList : ::std::vector<T>, ::std::mutex{ };

struct TimedEvent{
    double time;
    void (*event_func)(void *, unsigned long long);
    unsigned long long lparam;
    inline TimedEvent(double, void (*)(void *, unsigned long long), unsigned long long);
};

struct EventTimer : ::std::vector<::TimedEvent>{
    void *activity_ptr;
    ::std::chrono::system_clock::time_point basetime;
    double duration;
    ::std::vector<::TimedEvent> prepared_events;
    inline EventTimer(void *);
    inline void prepare(double, void (*)(void *, unsigned long long), unsigned long long);
    inline void procedure();
    inline void set_basetime();
};

struct MainActivity : Sseu::ActivityBase{
    unsigned int selected;
    ::QuadDisplayer logo_displayer;
    ::FpsDisplayer fps_displayer;
    inline MainActivity();
    inline ~MainActivity();
    inline void init() override;
    inline void quit() override;
    inline void update() override;
    inline void procedure(::SDL_Event const) override;
    inline void display_selections();
};

struct GameActivity : Sseu::ActivityBase{
    bool is_exsisting, is_suspending;
    ::std::vector<::std::thread> thr_list;
    long long timestamp;
    ::EventTimer event_timer;
    ::GameareaBackgroundDisplayer gamearea_background;
    ::FpsDisplayer fps_displayer;
    ::QuadDisplayer logo_displayer;
    ::TzuihcziDisplayer tzuihczi;
    ::std::vector<::TzoicziDisplayer> tzoiczi_list;
    ::MirroredQuadDisplayer boss;
    ::DisplayerList<::QuadDisplayer *> diqczi_list, tzuihdann_list, diqdann_list;
    // ::std::vector<::QuadDisplayer *> bullet_list;
    // ::std::mutex bullet_list_mutex;
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
    inline void display_suspending_curtain();
};

#endif
