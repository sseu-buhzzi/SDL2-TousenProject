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

struct Updater;
struct QuadDisplayer;
struct MirroredQuadDisplayer;
struct TzuihcziDisplayer;
struct OrientedQuadDisplayer;
struct RotatedQuadDisplayer;
struct TrackingQuadDisplayer;
struct TzoicziDisplayer;
struct LocatedQuadDisplayer;
struct DiqcziDisplayer;
struct LineDisplayer;
struct GameareaDisplayer;
struct FpsDisplayer;

template<typename> struct UpdaterList;

struct TimedEvent;
struct Timer;

struct MainActivity;
struct GameActivity;

struct Updater{
    ::std::chrono::system_clock::time_point setting_time;
    void (*update_func)(void *, unsigned long long);
    inline Updater(void (*)(void *, unsigned long long));
    inline void update(unsigned long long);
    inline virtual void display() { }
};
struct QuadDisplayer : Updater{
    // static ::std::unordered_map<void *, bool> displayer_status;
    // bool is_exsisting;
    // ::std::chrono::system_clock::time_point basetime;
    unsigned int tex_id;
    double x, y, half_width, half_height;
    ::std::vector<double> param_list;
    inline QuadDisplayer(void (*)(void *, unsigned long long), unsigned int, double, double, double, double);
    inline ~QuadDisplayer();
    inline virtual void display() override;
};

struct MirroredQuadDisplayer : QuadDisplayer{
    bool is_mirrored;
    inline MirroredQuadDisplayer(void (*)(void *, unsigned long long), unsigned int, double, double, double, double, bool);
    inline virtual void display() override;
};

struct TzuihcziDisplayer : MirroredQuadDisplayer{
    double dx, dy;
    bool is_shifting, is_shooting, is_injury_free;
    ::std::thread shooting_thr;
    inline TzuihcziDisplayer(void (*)(void *, unsigned long long), unsigned int, double, double, double, double, bool);
    inline void display_judge_point();
};

struct OrientedQuadDisplayer : QuadDisplayer{
    double set_x, set_y, dx, dy;
    inline OrientedQuadDisplayer(void (*)(void *, unsigned long long), unsigned int, double, double, double, double, double);
};

struct RotatedQuadDisplayer : QuadDisplayer{
    double phi, theta;
    inline RotatedQuadDisplayer(void (*)(void *, unsigned long long), unsigned int, double, double, double, double, double, double);
    inline virtual void display() override;
};

struct TrackingQuadDisplayer : RotatedQuadDisplayer{
    ::QuadDisplayer *target_displayer;
    inline TrackingQuadDisplayer(void (*)(void *, unsigned long long), unsigned int, double, double, double, double, double, double, ::QuadDisplayer *);
};

struct TzoicziDisplayer : RotatedQuadDisplayer{
    ::TzuihcziDisplayer *tzuihczi;
    double offset_x, offset_y;
    inline TzoicziDisplayer(void (*)(void *, unsigned long long), unsigned int, double, double, double, double, ::TzuihcziDisplayer *, double, double);
};

struct LocatedQuadDisplayer : QuadDisplayer{
    ::std::vector<double> located_x, located_y;
    using ::QuadDisplayer::QuadDisplayer;
};

struct DiqcziDisplayer : LocatedQuadDisplayer{
    double heal;
    ::std::vector<unsigned long long> event_id_list;
    inline DiqcziDisplayer(void (*)(void *, unsigned long long), unsigned int, double, double, double, double, double);
};

struct LineDisplayer{};

struct GameareaDisplayer{
    double process;
    inline GameareaDisplayer();
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

template<typename T> struct UpdaterList : ::std::vector<T>, ::std::mutex{
    // // static ::std::unordered_map<::QuadDisplayer *, bool> displayer_status;
    // inline void emplace_displayer(::QuadDisplayer *, ::std::unordered_map<::Updater *, bool> *);
    // // template<typename T> inline typename ::std::vector<T *>::iterator erase_displayer(typename ::std::vector<T *>::iterator);
    // inline ::std::vector<::QuadDisplayer *>::iterator erase_displayer(::std::vector<::QuadDisplayer *>::iterator, ::std::unordered_map<::Updater *, bool> *);
};

struct TimedEvent{
    // static unsigned long long event_count;
    // unsigned long long event_id;
    double time;
    void (*event_func)(void *, unsigned long long);
    unsigned long long lparam;
    inline TimedEvent(double, void (*)(void *, unsigned long long), unsigned long long);
};

struct Timer{
    bool should_refresh;
    ::std::chrono::system_clock::time_point base_time, latest_time, second_latest_time;
    ::std::vector<::TimedEvent> timed_event_list, prepared_event_list;
    // ::std::vector<unsigned long long> removed_event_id_list;
    inline Timer();
    inline double duration_from_base();
    inline double duration_from_latest();
    inline void prepare(::TimedEvent);
    inline void procedure(void *);
    // inline void remove(unsigned long long);
    inline void set_base_time();
    inline void set_latest_time();
};

struct MainActivity : Sseu::ActivityBase{
    ::Timer timer;
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
    ::Timer timer;
    bool is_exsisting, is_suspending;
    // ::std::vector<::std::thread> thr_list;
    // long long timestamp;
    ::std::unordered_map<::Updater *, bool> updater_status;
    ::Updater *event_updater;
    ::GameareaDisplayer gamearea;
    ::FpsDisplayer fps_displayer;
    ::QuadDisplayer logo_displayer;
    ::TzuihcziDisplayer tzuihczi;
    ::std::vector<::TzoicziDisplayer> tzoiczi_list;
    ::MirroredQuadDisplayer boss;
    ::UpdaterList<::DiqcziDisplayer *> diqczi_list;
    ::UpdaterList<::QuadDisplayer *> tzuihdann_list, diqdann_list;
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
