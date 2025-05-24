#ifndef FUNC_SOURCE_HPP
#define FUNC_SOURCE_HPP

#include ".\AudioSource.hpp"

namespace Sseu::FuncSource {
    inline double calc_norm(double, double);
    inline double calc_signed_angle(double);
    inline double calc_unsigned_angle(double);
    // inline double duration_to_now(::std::chrono::system_clock::time_point);
    inline void null_updater(void *, unsigned long long);
    // inline void main_activity_logo_updater(void *);
    inline void game_activity_tzuihczi_updater(void *, unsigned long long);
    inline void game_activity_boss_updater(void *, unsigned long long);
    inline void game_activity_tzuihdann_updater(void *, unsigned long long);
    // inline void game_activity_diqdann_updater(void *);
    // inline void game_activity_diqdann_updater_1(void *);
    inline void game_activity_tzoiczi_updater(void *, unsigned long long);
    inline void game_activity_tzoidann_updater(void *, unsigned long long);

    inline void game_activity_diqczi_eventer_0_init(void *, unsigned long long);
    inline void game_activity_diqczi_updater_0_init(void *, unsigned long long);
    inline void game_activity_diqczi_eventer_0(void *, unsigned long long);
    inline void game_activity_diqczi_updater_0(void *, unsigned long long);
    inline void game_activity_diqdann_eventer_0(void *, unsigned long long);
    inline void game_activity_diqdann_updater_0(void *, unsigned long long);
    inline void game_activity_diqczi_eventer_0_quit(void *, unsigned long long);

    inline void game_activity_diqczi_eventer_1_init(void *, unsigned long long);
    inline void game_activity_diqczi_eventer_1(void *, unsigned long long);
    inline void game_activity_diqczi_updater_1(void *, unsigned long long);
    inline void game_activity_diqdann_eventer_1(void *, unsigned long long);
    inline void game_activity_diqdann_updater_1(void *, unsigned long long);
}

namespace Sseu::FuncSource {
    double calc_norm(double x, double y) {
        return ::sqrt(x * x + y * y);
    }
    double calc_signed_angle(double a) {
        return (a = ::fmod(a, M_PI * 2)) < -M_PI ? a + M_PI * 2 : a >= M_PI ? a - M_PI * 2 : a;
    }
    double calc_unsigned_angle(double a) {
        return (a = ::fmod(a, M_PI * 2)) < 0 ? a + M_PI * 2 : a;
    }
    // double duration_to_now(::std::chrono::system_clock::time_point basetime) {
    //     return (::std::chrono::system_clock::now() - basetime).count() * 1e-6;
    // }
    void null_updater(void *, unsigned long long) { }
    // void main_activity_logo_updater(void *param) {
    //     ::QuadDisplayer *updater{reinterpret_cast<::QuadDisplayer *>(param)};
    //     updater->y = 128.0;
    // }
    void game_activity_tzuihczi_updater(void *param, unsigned long long lparam) {
        ::TzuihcziDisplayer *updater{reinterpret_cast<::TzuihcziDisplayer *>(param)};
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(lparam)};
        double duration{activity->timer.duration_from_latest()};
        if (updater->is_shifting) {
            duration *= 0.25;
        }
        updater->x += updater->dx * duration;
        updater->y += updater->dy * duration;
    }
    void game_activity_boss_updater(void *param, unsigned long long) {
        ::MirroredQuadDisplayer *updater{reinterpret_cast<::MirroredQuadDisplayer *>(param)};
        updater->y = 128.0;
    }
    void game_activity_tzuihdann_updater(void *param, unsigned long long) {
        ::OrientedQuadDisplayer *updater{reinterpret_cast<::OrientedQuadDisplayer *>(param)};
        // ::GameActivity *activity{reinterpret_cast<::GameActivity *>(lparam)};
        // double const duration{::Sseu::FuncSource::duration_to_now(updater->basetime)};
        double const duration{(::std::chrono::system_clock::now() - updater->setting_time).count() - 1e-6};
// 實際上每個自彈都有自己的進程，所以統一用這個activity->timer是否合適呢？
        // double const duration{(::std::chrono::system_clock::now().time_since_epoch().count() - updater->exsist_time) * 1024e-9};
        double const process{duration * 1e-6};
        updater->x = updater->set_x + process * updater->dx;
        updater->y = updater->set_y + process * updater->dy;
    }
    // void game_activity_diqdann_updater(void *param) {
    //     ::OrientedQuadDisplayer *updater{reinterpret_cast<::OrientedQuadDisplayer *>(param)};
    //     double const duration{::Sseu::FuncSource::duration_to_now(updater->exsist_time)};
    //     // double const duration{(::std::chrono::system_clock::now().time_since_epoch().count() - updater->exsist_time) * 1e-9};
    //     double const process{(duration * 0.5 - ::exp(-duration * 4) + 1) * 256};
    //     updater->x = updater->set_x + process * updater->dx;
    //     updater->y = updater->set_y + process * updater->dy;
    // }
    // void game_activity_diqdann_updater_1(void *param) {
    //     ::OrientedQuadDisplayer *updater{reinterpret_cast<::OrientedQuadDisplayer *>(param)};
    //     double const duration{::Sseu::FuncSource::duration_to_now(updater->exsist_time)};
    //     // double const duration{(::std::chrono::system_clock::now().time_since_epoch().count() - updater->exsist_time) * 64e-9};
    //     double const process{duration * 64};
    //     updater->x = updater->set_x + process * updater->dx;
    //     updater->y = updater->set_y + process * updater->dy;
    // }
    void game_activity_tzoiczi_updater(void *param, unsigned long long lparam) {
        ::TzoicziDisplayer *updater{reinterpret_cast<::TzoicziDisplayer *>(param)};
// ::std::cout << __LINE__ << '\t' << updater->tzuihczi << '\n';
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(lparam)};
        updater->x += (updater->tzuihczi->x + updater->offset_x - updater->x) * 0.0625;
        updater->y += (updater->tzuihczi->y + updater->offset_y - updater->y) * 0.0625;
        updater->theta += activity->timer.duration_from_latest() * 16e-3;
// ::std::cout << __LINE__ << '\t' << activity->timer.latest_time.time_since_epoch().count() - activity->timer.second_latest_time.time_since_epoch().count() << '\t' << updater->theta << '\n';
// ::std::cout << __LINE__ << '\t' << activity->timer.duration_from_latest() << '\n';
    }
    void game_activity_tzoidann_updater(void *param, unsigned long long lparam) {
        ::TrackingQuadDisplayer *updater{reinterpret_cast<::TrackingQuadDisplayer *>(param)};
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(lparam)};
        double direction{updater->target_displayer != nullptr && activity->updater_status[updater->target_displayer] ? ::atan2(updater->target_displayer->x - updater->x, updater->target_displayer->y - updater->y) : 0.0};
// direction = 0.0;
/*
y
|    /
|   /
|  /
|^/ -> The direction angle
|/
O_______x

y
|   /
|  /
| /
|/ ) -> The theta angle
O________x

direction + M_PI_2 = target_theta
*/
        updater->theta -= ::Sseu::FuncSource::calc_signed_angle(direction + updater->theta) * 0.0625;
// static double th{0.0};
// updater->theta = M_PI_2;
        updater->x -= ::sin(updater->theta);
        updater->y += ::cos(updater->theta);
    }
}

// 第一波敵機(diqczi_0)
namespace Sseu::FuncSource {
    void game_activity_diqczi_eventer_0_init(void *param, unsigned long long) {
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        for (unsigned int i{0U}; i < 10U; ++i) {
            activity->timer.prepare(::TimedEvent(activity->timer.duration_from_base() + ::rand() % 1024, &::Sseu::FuncSource::game_activity_diqczi_eventer_0, i));
        }
        activity->event_updater = new ::Updater(&::Sseu::FuncSource::game_activity_diqczi_updater_0_init);
        activity->updater_status[activity->event_updater] = true;
    }
    void game_activity_diqczi_updater_0_init(void *param, unsigned long long lparam) {
        ::Updater *updater{reinterpret_cast<::Updater *>(param)};
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(lparam)};
        if (activity->updater_status[updater]) {
            double const duration{(::std::chrono::system_clock::now() - updater->setting_time).count() * 1e-6};
            if (duration >= 1024 && activity->diqczi_list.empty()) {
                // ::std::cout << "next event\n";
                activity->updater_status[updater] = false;
// ::std::cout << __LINE__ << '\t' << updater << '\n';
                delete updater;
                activity->event_updater = nullptr;
// ::std::cout << __LINE__ << '\t' << updater << '\n';
                activity->timer.prepare(::TimedEvent(2048, &::Sseu::FuncSource::game_activity_diqczi_eventer_1_init, 0ULL));
            }
        }
    }
    void game_activity_diqczi_eventer_0(void *param, unsigned long long lparam) {
// ::std::cout << "__LINE__: " << __LINE__ << '\n';
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        ::DiqcziDisplayer *diqczi{new ::DiqcziDisplayer(&::Sseu::FuncSource::game_activity_diqczi_updater_0, ::Sseu::TexSource::tex_ids["druangczea_niqluh"], 0.0, 0.0, 16.0, 16.0, 16.0)};
        switch (lparam) {
            case 0ULL: {
                diqczi->located_x = {0.0, 64.0};
                diqczi->located_y = {0.0, 528.0};
                break;
            }
            case 1ULL: {
                diqczi->located_x = {0.0, 96.0};
                diqczi->located_y = {0.0, 520.0};
                break;
            }
            case 2ULL: {
                diqczi->located_x = {0.0, 128.0};
                diqczi->located_y = {0.0, 512.0};
                break;
            }
            case 3ULL: {
                diqczi->located_x = {0.0, 160.0};
                diqczi->located_y = {0.0, 504.0};
                break;
            }
            case 4ULL: {
                diqczi->located_x = {0.0, 192.0};
                diqczi->located_y = {0.0, 496.0};
                break;
            }
            case 5ULL: {
                diqczi->located_x = {512.0, 448.0};
                diqczi->located_y = {0.0, 528.0};
                break;
            }
            case 6ULL: {
                diqczi->located_x = {512.0, 416.0};
                diqczi->located_y = {0.0, 520.0};
                break;
            }
            case 7ULL: {
                diqczi->located_x = {512.0, 384.0};
                diqczi->located_y = {0.0, 512.0};
                break;
            }
            case 8ULL: {
                diqczi->located_x = {512.0, 352.0};
                diqczi->located_y = {0.0, 504.0};
                break;
            }
            case 9ULL: {
                diqczi->located_x = {512.0, 320.0};
                diqczi->located_y = {0.0, 496.0};
                break;
            }
        }
        activity->diqczi_list.emplace_back(diqczi);
        activity->updater_status[diqczi] = true;
        for (unsigned int i{2048}; i < 16384; i += 1024) {
            // ::TimedEvent event(activity->timer.duration_from_base() + i, &::Sseu::FuncSource::game_activity_diqdann_eventer_0, reinterpret_cast<unsigned long long>(diqczi));
            activity->timer.prepare(::TimedEvent(activity->timer.duration_from_base() + i, &::Sseu::FuncSource::game_activity_diqdann_eventer_0, reinterpret_cast<unsigned long long>(diqczi)));
            // diqczi->event_id_list.emplace_back(event.event_id);
// ::std::cout << "__LINE__: " << __LINE__ << '\n';
        }
// ::std::cout << "__LINE__: " << __LINE__ << '\n';
        activity->timer.prepare(::TimedEvent(activity->timer.duration_from_base() + 16384, &::Sseu::FuncSource::game_activity_diqczi_eventer_0_quit, reinterpret_cast<unsigned long long>(diqczi)));
    }
    void game_activity_diqczi_updater_0(void *param, unsigned long long) {
        ::LocatedQuadDisplayer *updater{reinterpret_cast<::LocatedQuadDisplayer *>(param)};
        double const duration{(::std::chrono::system_clock::now() - updater->setting_time).count() * 1e-6};
        double const process{::log(duration * 4e-3 + 1)};
// ::std::cout << "basetime:" << updater->basetime << "\tduration:" << duration << "\tprocess:" << process << '\n';
        if (process < 1.0) {
            updater->x = (1 - process) * updater->located_x[0] + process * updater->located_x[1];
            updater->y = (1 - process) * updater->located_y[0] + process * updater->located_y[1];
        } else {
// ::std::cout << "reached\n";
            updater->update_func = &::Sseu::FuncSource::null_updater;
        }
    }
    void game_activity_diqdann_eventer_0(void *param, unsigned long long lparam) {
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        ::DiqcziDisplayer *diqczi{reinterpret_cast<::DiqcziDisplayer *>(lparam)};
        // ::std::cout << diqczi->is_exsisting << '\n';
        if (activity->updater_status[diqczi]) {
            ::OrientedQuadDisplayer *diqdann{new ::OrientedQuadDisplayer(&::Sseu::FuncSource::game_activity_diqdann_updater_0, ::Sseu::TexSource::tex_ids["dahzziuh_blue"], diqczi->x, diqczi->y, 16.0, 16.0, ::atan2(activity->tzuihczi.y - diqczi->y, activity->tzuihczi.x - diqczi->x))};
            activity->diqdann_list.emplace_back(diqdann);
            activity->updater_status[diqdann] = true;
        }
    }
    void game_activity_diqdann_updater_0(void *param, unsigned long long) {
        ::OrientedQuadDisplayer *updater{reinterpret_cast<::OrientedQuadDisplayer *>(param)};
        double const duration{(::std::chrono::system_clock::now() - updater->setting_time).count() * 1e-6};
        double const process{duration * 512e-3};
        updater->x = updater->set_x + process * updater->dx;
        updater->y = updater->set_y + process * updater->dy;
    }
    void game_activity_diqczi_eventer_0_quit(void *param, unsigned long long lparam) {
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        ::LocatedQuadDisplayer *diqczi{reinterpret_cast<::LocatedQuadDisplayer *>(lparam)};
        if (activity->updater_status[diqczi]) {
            diqczi->located_x = {diqczi->x, diqczi->x};
            diqczi->located_y = {diqczi->y, 1024.0};
            diqczi->setting_time = ::std::chrono::system_clock::now();
            // diqczi->setting_time = activity->timer.base_time + ::std::chrono::milliseconds(int(activity->timer.duration_from_base()));
            diqczi->update_func = &::Sseu::FuncSource::game_activity_diqczi_updater_0;
    // ::std::cout << diqczi << "\tshould quit\n";
        }
    }
}

//第二波敵機(diqczi_1)
namespace Sseu::FuncSource {
    void game_activity_diqczi_eventer_1_init(void *param, unsigned long long) {
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        ::std::cout << "Second Event\n";
        activity->timer.should_refresh = true;
        // activity->timer.timed_event_list.clear();
        activity->timer.prepare(::TimedEvent(activity->timer.duration_from_base() + 1024, &::Sseu::FuncSource::game_activity_diqczi_eventer_1, 0ULL));
        activity->timer.prepare(::TimedEvent(activity->timer.duration_from_base() + 4096, &::Sseu::FuncSource::game_activity_diqczi_eventer_1, 1ULL));
        activity->timer.prepare(::TimedEvent(activity->timer.duration_from_base() + 4096, &::Sseu::FuncSource::game_activity_diqczi_eventer_1, 2ULL));
    }
    void game_activity_diqczi_eventer_1(void *param, unsigned long long lparam) {
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        ::DiqcziDisplayer *diqczi{new ::DiqcziDisplayer(&::Sseu::FuncSource::game_activity_diqczi_updater_1, ::Sseu::TexSource::tex_ids["druangczea_niqluh"], 0.0, 0.0, 24.0, 24.0, 64.0)};
        switch (lparam) {
            case 0ULL: {
                diqczi->located_x = {256.0, 256.0};
                diqczi->located_y = {640.0, 512.0};
                break;
            }
            case 1ULL: {
                diqczi->located_x = {64.0, 64.0};
                diqczi->located_y = {640.0, 512.0};
                break;
            }
            case 2ULL: {
                diqczi->located_x = {448.0, 448.0};
                diqczi->located_y = {640.0, 512.0};
                break;
            }
        }
        activity->diqczi_list.emplace_back(diqczi);
        activity->updater_status[diqczi] = true;
        for (unsigned int i{2048U}; i < 16384U; i += 2048) {
            activity->timer.prepare(::TimedEvent(activity->timer.duration_from_base() + i, &::Sseu::FuncSource::game_activity_diqdann_eventer_1, reinterpret_cast<unsigned long long>(diqczi)));
// break;
        }
    }
    void game_activity_diqczi_updater_1(void *param, unsigned long long) {
        ::LocatedQuadDisplayer *updater{reinterpret_cast<::LocatedQuadDisplayer *>(param)};
        double const duration{(::std::chrono::system_clock::now() - updater->setting_time).count() * 1e-6};
        double const process{::log(duration * 1e-3 + 1)};
        if (process < 1.0) {
            updater->x = (1 - process) * updater->located_x[0] + process * updater->located_x[1];
            updater->y = (1 - process) * updater->located_y[0] + process * updater->located_y[1];
        } else {
            updater->update_func = &::Sseu::FuncSource::null_updater;
        }
    }
    void game_activity_diqdann_eventer_1(void *param, unsigned long long lparam) {
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        ::DiqcziDisplayer *diqczi{reinterpret_cast<::DiqcziDisplayer *>(lparam)};
        if (activity->updater_status[diqczi]) {
            double const theta{::atan2(activity->tzuihczi.y - diqczi->y, activity->tzuihczi.x - diqczi->x) - M_PI_2};
            for (double offset_theta{0.0}; offset_theta < M_PI * 2; offset_theta += M_PI * 0.0625) {
                ::RotatedQuadDisplayer *diqdann{new ::RotatedQuadDisplayer(&::Sseu::FuncSource::game_activity_diqdann_updater_1, ::Sseu::TexSource::tex_ids["diamond_bullet_blue"], diqczi->x, diqczi->y, 8.0, 8.0, 0.0, 0.0)};
                diqdann->param_list = {M_PI_2, theta + offset_theta};
    // ::std::cout << __LINE__ << '\t' << diqdann->x << '\t' << diqdann->y << '\n';
                activity->diqdann_list.emplace_back(diqdann);
                activity->updater_status[diqdann] = true;
            }
        }
    }
    void game_activity_diqdann_updater_1(void *param, unsigned long long lparam) {
        ::RotatedQuadDisplayer *updater{reinterpret_cast<::RotatedQuadDisplayer *>(param)};
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(lparam)};
        // double const duration{(::std::chrono::system_clock::now() - updater->setting_time).count() * 1e-6};
        // double const process{duration * 64e-3};
        double const duration{activity->timer.duration_from_latest()};
        double const process{duration * 256e-3};
// ::std::cout << __LINE__ << '\t' << updater->x << '\t' << updater->y << '\n';
        updater->x -= ::sin(updater->param_list[1]) * process;
        updater->y += ::cos(updater->param_list[1]) * process;
// ::std::cout << __LINE__ << '\t' << updater->x << '\t' << updater->y << '\t' << activity->diqdann_list.size() << '\n';
        // updater->x = updater->set_x + process * updater->dx;
        // updater->y = updater->set_y + process * updater->dy;
    }
}

#endif
