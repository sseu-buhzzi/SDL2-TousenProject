#ifndef FUNC_SOURCE_HPP
#define FUNC_SOURCE_HPP

#include ".\AudioSource.hpp"

namespace FuncSource {
    inline double calc_norm(double, double);
    inline double calc_signed_angle(double);
    inline double calc_unsigned_angle(double);
    // inline double duration_to_now(::std::chrono::system_clock::time_point);
    inline void null_updater(void *, ::Lparam);

    // inline void main_activity_logo_updater(void *);
    inline void game_activity_tzuihczi_updater(void *, ::Lparam);
    inline void game_activity_boss_updater(void *, ::Lparam);
    inline void game_activity_tzuihdann_updater(void *, ::Lparam);
    // inline void game_activity_diqdann_updater(void *);
    // inline void game_activity_diqdann_updater_1(void *);
    inline void game_activity_tzoiczi_updater(void *, ::Lparam);
    inline void game_activity_tzoidann_updater(void *, ::Lparam);
    inline void game_activity_tzuihczi_updater_recover(void *, ::Lparam);

    inline void game_activity_daycziuh_updater_appear(void *, ::Lparam);
    inline void game_activity_daycziuh_updater_fall(void *, ::Lparam);
    inline void game_activity_ssiaygoo_updater_graze(void *, ::Lparam);

    inline void game_activity_diqczi_eventer_0_init(void *, ::Lparam);
    inline void game_activity_diqczi_updater_0_init(void *, ::Lparam);
    inline void game_activity_diqczi_eventer_0(void *, ::Lparam);
    inline void game_activity_diqczi_updater_0(void *, ::Lparam);
    inline void game_activity_diqdann_eventer_0(void *, ::Lparam);
    inline void game_activity_diqdann_updater_0(void *, ::Lparam);
    inline void game_activity_diqczi_eventer_0_quit(void *, ::Lparam);

    inline void game_activity_diqczi_eventer_1_init(void *, ::Lparam);
    inline void game_activity_diqczi_eventer_1(void *, ::Lparam);
    inline void game_activity_diqczi_updater_1(void *, ::Lparam);
    inline void game_activity_diqdann_eventer_1(void *, ::Lparam);
    inline void game_activity_diqdann_updater_1(void *, ::Lparam);

    inline void game_activity_diqczi_eventer_test_init(void *, ::Lparam);
    inline void game_activity_diqdann_eventer_test(void *, ::Lparam);
    inline void game_activity_diqdann_updater_test(void *, ::Lparam);
}

// 通用
namespace FuncSource {
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
    void null_updater(void *, ::Lparam) { }
    // void main_activity_logo_updater(void *param) {
    //     ::QuadDisplayer *updater{reinterpret_cast<::QuadDisplayer *>(param)};
    //     updater->y = 128.0;
    // }
}

// 角色們
namespace FuncSource {
    void game_activity_tzuihczi_updater(void *param, ::Lparam lparam) {
        ::MirroredQuadDisplayer *updater{reinterpret_cast<::MirroredQuadDisplayer *>(param)};
        ::GameActivity *activity(reinterpret_cast<::GameActivity *>(lparam.p));
        double duration{activity->timer.duration_from_latest()};
        if (updater->lparam_map[::UpdaterLparamType::ULT_IS_SLOW].b) {
            duration *= 0.25;
        }
        updater->x += updater->lparam_map[::UpdaterLparamType::ULT_DX].d * duration;
        updater->y += updater->lparam_map[::UpdaterLparamType::ULT_DY].d * duration;
        if (updater->lparam_map[::UpdaterLparamType::ULT_IS_SHOOTING].b && !updater->lparam_map[::UpdaterLparamType::ULT_IS_IN_SHOOTING_BREAK].b) {
            updater->lparam_map[::UpdaterLparamType::ULT_IS_IN_SHOOTING_BREAK].b = true;
            ::std::thread([updater]() -> void {
                ::std::this_thread::sleep_for(::std::chrono::milliseconds(64));
                updater->lparam_map[::UpdaterLparamType::ULT_IS_IN_SHOOTING_BREAK].b = false;
            }).detach();
            ::QuadDisplayer *tzuihdann;
            if (updater->lparam_map[::UpdaterLparamType::ULT_IS_HMIRRORED].b) {
                activity->tzuihdann_list.emplace_back(tzuihdann = new ::QuadDisplayer(&::FuncSource::game_activity_tzuihdann_updater, ::TexSource::tex_ids["shoigu"], activity->tzuihczi.x - 16, activity->tzuihczi.y, 16.0, 16.0));
                tzuihdann->lparam_map[::UpdaterLparamType::ULT_SETX].d = tzuihdann->x;
                tzuihdann->lparam_map[::UpdaterLparamType::ULT_SETY].d = tzuihdann->y;
                tzuihdann->lparam_map[::UpdaterLparamType::ULT_DX].d = 0.0;
                tzuihdann->lparam_map[::UpdaterLparamType::ULT_DY].d = 1.0;
                activity->updater_status[tzuihdann] = true;
                activity->tzuihdann_list.emplace_back(tzuihdann = new ::QuadDisplayer(&::FuncSource::game_activity_tzuihdann_updater, ::TexSource::tex_ids["gerasimov"], activity->tzuihczi.x + 16, activity->tzuihczi.y, 16.0, 16.0));
                tzuihdann->lparam_map[::UpdaterLparamType::ULT_SETX].d = tzuihdann->x;
                tzuihdann->lparam_map[::UpdaterLparamType::ULT_SETY].d = tzuihdann->y;
                tzuihdann->lparam_map[::UpdaterLparamType::ULT_DX].d = 0.0;
                tzuihdann->lparam_map[::UpdaterLparamType::ULT_DY].d = 1.0;
                activity->updater_status[tzuihdann] = true;
            } else {
                activity->tzuihdann_list.emplace_back(tzuihdann = new ::QuadDisplayer(&::FuncSource::game_activity_tzuihdann_updater, ::TexSource::tex_ids["gerasimov"], activity->tzuihczi.x - 16, activity->tzuihczi.y, 16.0, 16.0));
                tzuihdann->lparam_map[::UpdaterLparamType::ULT_SETX].d = tzuihdann->x;
                tzuihdann->lparam_map[::UpdaterLparamType::ULT_SETY].d = tzuihdann->y;
                tzuihdann->lparam_map[::UpdaterLparamType::ULT_DX].d = 0.0;
                tzuihdann->lparam_map[::UpdaterLparamType::ULT_DY].d = 1.0;
                activity->updater_status[tzuihdann] = true;
                activity->tzuihdann_list.emplace_back(tzuihdann = new ::QuadDisplayer(&::FuncSource::game_activity_tzuihdann_updater, ::TexSource::tex_ids["shoigu"], activity->tzuihczi.x + 16, activity->tzuihczi.y, 16.0, 16.0));
                tzuihdann->lparam_map[::UpdaterLparamType::ULT_SETX].d = tzuihdann->x;
                tzuihdann->lparam_map[::UpdaterLparamType::ULT_SETY].d = tzuihdann->y;
                tzuihdann->lparam_map[::UpdaterLparamType::ULT_DX].d = 0.0;
                tzuihdann->lparam_map[::UpdaterLparamType::ULT_DY].d = 1.0;
                activity->updater_status[tzuihdann] = true;
            }
            for (::std::vector<::RotatedQuadDisplayer>::iterator tzoiczi(activity->tzoiczi_list.begin()); tzoiczi != activity->tzoiczi_list.end(); ++tzoiczi) {
                // double theta{(0.875 - (tzoiczi - activity->tzoiczi_list.begin()) * 0.25) * M_PI};
                ::RotatedQuadDisplayer *tzoidann{new ::RotatedQuadDisplayer(&::FuncSource::game_activity_tzoidann_updater, ::TexSource::tex_ids["tracking_bullet"], tzoiczi->x, tzoiczi->y, 8.0, 8.0, M_PI_2, (0.375 - (tzoiczi - activity->tzoiczi_list.begin()) * 0.25) * M_PI)};
                tzoidann->lparam_map[::UpdaterLparamType::ULT_TARGET].p = activity->diqczi_list.empty() ? nullptr : activity->diqczi_list[::rand() % activity->diqczi_list.size()];
                activity->tzuihdann_list.emplace_back(tzoidann);
                activity->updater_status[tzoidann] = true;
            }
        }
    }
    void game_activity_boss_updater(void *param, ::Lparam) {
        ::MirroredQuadDisplayer *updater{reinterpret_cast<::MirroredQuadDisplayer *>(param)};
        updater->y = 128.0;
    }
    void game_activity_tzuihdann_updater(void *param, ::Lparam) {
        ::QuadDisplayer *updater{reinterpret_cast<::QuadDisplayer *>(param)};
        // ::GameActivity *activity{reinterpret_cast<::GameActivity *>(lparam.p)};
        // double const duration{::FuncSource::duration_to_now(updater->basetime)};
        double const duration{(::std::chrono::system_clock::now() - updater->setting_time).count() - 1e-6};
// 實際上每個自彈都有自己的進程，所以統一用這個activity->timer是否合適呢？
        // double const duration{(::std::chrono::system_clock::now().time_since_epoch().count() - updater->exsist_time) * 1024e-9};
        double const process{duration * 1e-6};
        updater->x = updater->lparam_map[::UpdaterLparamType::ULT_SETX].d + process * updater->lparam_map[::UpdaterLparamType::ULT_DX].d;
        updater->y = updater->lparam_map[::UpdaterLparamType::ULT_SETY].d + process * updater->lparam_map[::UpdaterLparamType::ULT_DY].d;
    }
    // void game_activity_diqdann_updater(void *param) {
    //     ::OrientedQuadDisplayer *updater{reinterpret_cast<::OrientedQuadDisplayer *>(param)};
    //     double const duration{::FuncSource::duration_to_now(updater->exsist_time)};
    //     // double const duration{(::std::chrono::system_clock::now().time_since_epoch().count() - updater->exsist_time) * 1e-9};
    //     double const process{(duration * 0.5 - ::exp(-duration * 4) + 1) * 256};
    //     updater->x = updater->set_x + process * updater->dx;
    //     updater->y = updater->set_y + process * updater->dy;
    // }
    // void game_activity_diqdann_updater_1(void *param) {
    //     ::OrientedQuadDisplayer *updater{reinterpret_cast<::OrientedQuadDisplayer *>(param)};
    //     double const duration{::FuncSource::duration_to_now(updater->exsist_time)};
    //     // double const duration{(::std::chrono::system_clock::now().time_since_epoch().count() - updater->exsist_time) * 64e-9};
    //     double const process{duration * 64};
    //     updater->x = updater->set_x + process * updater->dx;
    //     updater->y = updater->set_y + process * updater->dy;
    // }
    void game_activity_tzoiczi_updater(void *param, ::Lparam lparam) {
        ::RotatedQuadDisplayer *updater{reinterpret_cast<::RotatedQuadDisplayer *>(param)};
// ::std::cout << __LINE__ << '\t' << updater->tzuihczi << '\n';
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(lparam.p)};
        double const duration{activity->timer.duration_from_latest()};
        double const process{duration * 16e-3};
        ::MirroredQuadDisplayer *tzuihczi{reinterpret_cast<::MirroredQuadDisplayer *>(updater->lparam_map[::UpdaterLparamType::ULT_TARGET].p)};
        updater->x += (tzuihczi->x + updater->lparam_map[::UpdaterLparamType::ULT_DX].d - updater->x) * process;
        updater->y += (tzuihczi->y + updater->lparam_map[::UpdaterLparamType::ULT_DY].d - updater->y) * process;
        updater->lparam_map[::UpdaterLparamType::ULT_THETA].d += process * 0.5;
// ::std::cout << __LINE__ << '\t' << activity->timer.latest_time.time_since_epoch().count() - activity->timer.second_latest_time.time_since_epoch().count() << '\t' << updater->theta << '\n';
// ::std::cout << __LINE__ << '\t' << activity->timer.duration_from_latest() << '\n';
    }
    void game_activity_tzoidann_updater(void *param, ::Lparam lparam) {
        ::RotatedQuadDisplayer *updater{reinterpret_cast<::RotatedQuadDisplayer *>(param)};
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(lparam.p)};
        double const duration{activity->timer.duration_from_latest()};
        double const process{duration};
        double *theta{&updater->lparam_map[::UpdaterLparamType::ULT_THETA].d};
        ::QuadDisplayer *diqczi{reinterpret_cast<::QuadDisplayer *>(updater->lparam_map[::UpdaterLparamType::ULT_TARGET].p)};
        double const direction{diqczi != nullptr && activity->updater_status[diqczi] ? ::atan2(diqczi->x - updater->x, diqczi->y - updater->y) : -*theta};
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
        *theta -= ::FuncSource::calc_signed_angle(direction + *theta) * 0.03125;
// static double th{0.0};
// *theta = M_PI_2;
        updater->x -= ::sin(*theta) * process;
        updater->y += ::cos(*theta) * process;
    }
    void game_activity_tzuihczi_updater_recover(void *param, ::Lparam lparam) {
        ::MirroredQuadDisplayer *updater{reinterpret_cast<::MirroredQuadDisplayer *>(param)};
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(lparam.p)};
        double const duration{activity->timer.duration_from_latest()};
        double const process{duration * 64e-3};
        updater->y += process;
        if (updater->y >= 64.0) {
            updater->y = 64.0;
            updater->update_func = &::FuncSource::game_activity_tzuihczi_updater;
        }
    }
}

// 小東西
namespace FuncSource {
    void game_activity_daycziuh_updater_appear(void *param, ::Lparam) {
        ::QuadDisplayer *updater{reinterpret_cast<::QuadDisplayer *>(param)};
        double const duration{(::std::chrono::system_clock::now() - updater->setting_time).count() * 1e-6};
        double const process{1 - ::pow(duration * 1e-3 - 1, 2.0)};
// ::std::cout << duration << '\n';
        if (duration < 1e3) {
            updater->x = updater->lparam_map[::UpdaterLparamType::ULT_SETX].d + process * updater->lparam_map[::UpdaterLparamType::ULT_DX].d;
            updater->y = updater->lparam_map[::UpdaterLparamType::ULT_SETY].d + process * updater->lparam_map[::UpdaterLparamType::ULT_DY].d;
        } else {
            updater->update_func = &::FuncSource::game_activity_daycziuh_updater_fall;
        }
    }
    void game_activity_daycziuh_updater_fall(void *param, ::Lparam lparam) {
        ::QuadDisplayer *updater{reinterpret_cast<::QuadDisplayer *>(param)};
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(lparam.p)};
        double const duration{activity->timer.duration_from_latest()};
        double const process{duration * 128e-3};
        updater->y -= process;
    }
    void game_activity_ssiaygoo_updater_graze(void *param, ::Lparam) {
        ::QuadDisplayer *updater{reinterpret_cast<::QuadDisplayer *>(param)};
        double const duration{(::std::chrono::system_clock::now() - updater->setting_time).count() * 1e-6};
        double const process{1 - ::pow(duration * 1e-3 - 1, 2.0)};
        if (duration < 1e3) {
            updater->x = updater->lparam_map[::UpdaterLparamType::ULT_SETX].d + process * updater->lparam_map[::UpdaterLparamType::ULT_DX].d;
            updater->y = updater->lparam_map[::UpdaterLparamType::ULT_SETY].d + process * updater->lparam_map[::UpdaterLparamType::ULT_DY].d;
            updater->half_width = updater->half_height = (1 - process) * 8;
        } else {
            updater->half_width = updater->half_height = 0.0;
            updater->update_func = &::FuncSource::null_updater;
        }
    }
}

// 第一波敵機(diqczi_0)
namespace FuncSource {
    void game_activity_diqczi_eventer_0_init(void *param, ::Lparam) {
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        for (unsigned int i{0U}; i < 10U; ++i) {
            activity->timer.prepare(::TimedEvent(activity->timer.duration_from_base() + ::rand() % 1024, &::FuncSource::game_activity_diqczi_eventer_0, ::Lparam{.ull = i}));
        }
        activity->event_updater = new ::Updater(&::FuncSource::game_activity_diqczi_updater_0_init);
        activity->updater_status[activity->event_updater] = true;
    }
    void game_activity_diqczi_updater_0_init(void *param, ::Lparam lparam) {
        ::Updater *updater{reinterpret_cast<::Updater *>(param)};
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(lparam.p)};
        if (activity->updater_status[updater]) {
            double const duration{(::std::chrono::system_clock::now() - updater->setting_time).count() * 1e-6};
            if (duration >= 1024 && activity->diqczi_list.empty()) {
                // ::std::cout << "next event\n";
                activity->updater_status[updater] = false;
// ::std::cout << __LINE__ << '\t' << updater << '\n';
                delete updater;
                activity->event_updater = nullptr;
// ::std::cout << __LINE__ << '\t' << updater << '\n';
                activity->timer.prepare(::TimedEvent(4096, &::FuncSource::game_activity_diqczi_eventer_1_init, ::Lparam{.ull = 0ULL}));
            }
        }
    }
    void game_activity_diqczi_eventer_0(void *param, ::Lparam lparam) {
// ::std::cout << "__LINE__: " << __LINE__ << '\n';
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        ::QuadDisplayer *diqczi{new ::QuadDisplayer(&::FuncSource::game_activity_diqczi_updater_0, ::TexSource::tex_ids["druangczea_niqluh"], 0.0, 0.0, 16.0, 16.0)};
        diqczi->lparam_map[::UpdaterLparamType::ULT_HEAL].ll = 16LL;
        switch (lparam.ull) {
            case 0ULL: {
                diqczi->lparam_map[::UpdaterLparamType::ULT_SETX].d = diqczi->x = 0.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_SETY].d = diqczi->y = 0.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_DX].d = 64.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_DY].d = 528.0;
                // diqczi->located_x = {0.0, 64.0};
                // diqczi->located_y = {0.0, 528.0};
                break;
            }
            case 1ULL: {
                diqczi->lparam_map[::UpdaterLparamType::ULT_SETX].d = diqczi->x = 0.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_SETY].d = diqczi->y = 0.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_DX].d = 96.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_DY].d = 520.0;
                // diqczi->located_x = {0.0, 96.0};
                // diqczi->located_y = {0.0, 520.0};
                break;
            }
            case 2ULL: {
                diqczi->lparam_map[::UpdaterLparamType::ULT_SETX].d = diqczi->x = 0.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_SETY].d = diqczi->y = 0.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_DX].d = 128.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_DY].d = 512.0;
                // diqczi->located_x = {0.0, 128.0};
                // diqczi->located_y = {0.0, 512.0};
                break;
            }
            case 3ULL: {
                diqczi->lparam_map[::UpdaterLparamType::ULT_SETX].d = diqczi->x = 0.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_SETY].d = diqczi->y = 0.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_DX].d = 160.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_DY].d = 504.0;
                // diqczi->located_x = {0.0, 160.0};
                // diqczi->located_y = {0.0, 504.0};
                break;
            }
            case 4ULL: {
                diqczi->lparam_map[::UpdaterLparamType::ULT_SETX].d = diqczi->x = 0.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_SETY].d = diqczi->y = 0.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_DX].d = 192.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_DY].d = 496.0;
                // diqczi->located_x = {0.0, 192.0};
                // diqczi->located_y = {0.0, 496.0};
                break;
            }
            case 5ULL: {
                diqczi->lparam_map[::UpdaterLparamType::ULT_SETX].d = diqczi->x = 512.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_SETY].d = diqczi->y = 0.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_DX].d = -64.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_DY].d = 528.0;
                // diqczi->located_x = {512.0, 448.0};
                // diqczi->located_y = {0.0, 528.0};
                break;
            }
            case 6ULL: {
                diqczi->lparam_map[::UpdaterLparamType::ULT_SETX].d = diqczi->x = 512.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_SETY].d = diqczi->y = 0.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_DX].d = -96.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_DY].d = 520.0;
                // diqczi->located_x = {512.0, 416.0};
                // diqczi->located_y = {0.0, 520.0};
                break;
            }
            case 7ULL: {
                diqczi->lparam_map[::UpdaterLparamType::ULT_SETX].d = diqczi->x = 512.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_SETY].d = diqczi->y = 0.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_DX].d = -128.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_DY].d = 512.0;
                // diqczi->located_x = {512.0, 384.0};
                // diqczi->located_y = {0.0, 512.0};
                break;
            }
            case 8ULL: {
                diqczi->lparam_map[::UpdaterLparamType::ULT_SETX].d = diqczi->x = 512.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_SETY].d = diqczi->y = 0.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_DX].d = -160.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_DY].d = 504.0;
                // diqczi->located_x = {512.0, 352.0};
                // diqczi->located_y = {0.0, 504.0};
                break;
            }
            case 9ULL: {
                diqczi->lparam_map[::UpdaterLparamType::ULT_SETX].d = diqczi->x = 512.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_SETY].d = diqczi->y = 0.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_DX].d = -192.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_DY].d = 496.0;
                // diqczi->located_x = {512.0, 320.0};
                // diqczi->located_y = {0.0, 496.0};
                break;
            }
        }
        activity->diqczi_list.emplace_back(diqczi);
        activity->updater_status[diqczi] = true;
        for (unsigned int i{2048}; i < 16384; i += 1024) {
            // ::TimedEvent event(activity->timer.duration_from_base() + i, &::FuncSource::game_activity_diqdann_eventer_0, ::Lparam{.p = diqczi});
            activity->timer.prepare(::TimedEvent(activity->timer.duration_from_base() + i, &::FuncSource::game_activity_diqdann_eventer_0, ::Lparam{.p = diqczi}));
            // diqczi->event_id_list.emplace_back(event.event_id);
// ::std::cout << "__LINE__: " << __LINE__ << '\n';
        }
// ::std::cout << "__LINE__: " << __LINE__ << '\n';
        activity->timer.prepare(::TimedEvent(activity->timer.duration_from_base() + 16384, &::FuncSource::game_activity_diqczi_eventer_0_quit, ::Lparam{.p = diqczi}));
    }
    void game_activity_diqczi_updater_0(void *param, ::Lparam) {
        ::QuadDisplayer *updater{reinterpret_cast<::QuadDisplayer *>(param)};
        double const duration{(::std::chrono::system_clock::now() - updater->setting_time).count() * 1e-6};
        double const process{::log(duration * 4e-3 + 1)};
// ::std::cout << "basetime:" << updater->basetime << "\tduration:" << duration << "\tprocess:" << process << '\n';
        if (process < 1.0) {
            updater->x = updater->lparam_map[::UpdaterLparamType::ULT_SETX].d + process * updater->lparam_map[::UpdaterLparamType::ULT_DX].d;
            updater->y = updater->lparam_map[::UpdaterLparamType::ULT_SETY].d + process * updater->lparam_map[::UpdaterLparamType::ULT_DY].d;
            // updater->x = (1 - process) * updater->located_x[0] + process * updater->located_x[1];
            // updater->y = (1 - process) * updater->located_y[0] + process * updater->located_y[1];
        } else {
// ::std::cout << "reached\n";
            updater->x = updater->lparam_map[::UpdaterLparamType::ULT_SETX].d + updater->lparam_map[::UpdaterLparamType::ULT_DX].d;
            updater->y = updater->lparam_map[::UpdaterLparamType::ULT_SETY].d + updater->lparam_map[::UpdaterLparamType::ULT_DY].d;
            updater->update_func = &::FuncSource::null_updater;
        }
    }
    void game_activity_diqdann_eventer_0(void *param, ::Lparam lparam) {
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        ::QuadDisplayer *diqczi{reinterpret_cast<::QuadDisplayer *>(lparam.p)};
        // ::std::cout << diqczi->is_exsisting << '\n';
        if (activity->updater_status[diqczi]) {
            double const theta{::atan2(activity->tzuihczi.y - diqczi->y, activity->tzuihczi.x - diqczi->x)};
            ::QuadDisplayer *diqdann{new ::QuadDisplayer(&::FuncSource::game_activity_diqdann_updater_0, ::TexSource::tex_ids["dahzziuh_blue"], diqczi->x, diqczi->y, 16.0, 16.0)};
            diqdann->lparam_map[::UpdaterLparamType::ULT_SETX].d = diqdann->x;
            diqdann->lparam_map[::UpdaterLparamType::ULT_SETY].d = diqdann->y;
            diqdann->lparam_map[::UpdaterLparamType::ULT_DX].d = ::cos(theta);
            diqdann->lparam_map[::UpdaterLparamType::ULT_DY].d = ::sin(theta);
            activity->diqdann_list.emplace_back(diqdann);
            activity->updater_status[diqdann] = true;
        }
    }
    void game_activity_diqdann_updater_0(void *param, ::Lparam) {
        ::QuadDisplayer *updater{reinterpret_cast<::QuadDisplayer *>(param)};
        double const duration{(::std::chrono::system_clock::now() - updater->setting_time).count() * 1e-6};
        double const process{duration * 512e-3};
        updater->x = updater->lparam_map[::UpdaterLparamType::ULT_SETX].d + process * updater->lparam_map[::UpdaterLparamType::ULT_DX].d;
        updater->y = updater->lparam_map[::UpdaterLparamType::ULT_SETY].d + process * updater->lparam_map[::UpdaterLparamType::ULT_DY].d;
        // updater->x = updater->set_x + process * updater->dx;
        // updater->y = updater->set_y + process * updater->dy;
    }
    void game_activity_diqczi_eventer_0_quit(void *param, ::Lparam lparam) {
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        ::QuadDisplayer *diqczi{reinterpret_cast<::QuadDisplayer *>(lparam.p)};
        if (activity->updater_status[diqczi]) {
            diqczi->lparam_map[::UpdaterLparamType::ULT_SETX].d = diqczi->x;
            diqczi->lparam_map[::UpdaterLparamType::ULT_SETY].d = diqczi->y;
            diqczi->lparam_map[::UpdaterLparamType::ULT_DX].d = 0.0;
            diqczi->lparam_map[::UpdaterLparamType::ULT_DY].d = 512.0;
            // diqczi->located_x = {diqczi->x, diqczi->x};
            // diqczi->located_y = {diqczi->y, 1024.0};
            diqczi->setting_time = ::std::chrono::system_clock::now();
            // diqczi->setting_time = activity->timer.base_time + ::std::chrono::milliseconds(int(activity->timer.duration_from_base()));
            diqczi->update_func = &::FuncSource::game_activity_diqczi_updater_0;
    // ::std::cout << diqczi << "\tshould quit\n";
        }
    }
}

// 第二波敵機(diqczi_1)
namespace FuncSource {
    void game_activity_diqczi_eventer_1_init(void *param, ::Lparam) {
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        ::std::cout << "Second Event\n";
        activity->timer.should_refresh = true;
        // activity->timer.timed_event_list.clear();
        activity->timer.prepare(::TimedEvent(activity->timer.duration_from_base(), &::FuncSource::game_activity_diqczi_eventer_1, ::Lparam{.ull = 0ULL}));
        activity->timer.prepare(::TimedEvent(activity->timer.duration_from_base() + 4096, &::FuncSource::game_activity_diqczi_eventer_1, ::Lparam{.ull = 1ULL}));
        activity->timer.prepare(::TimedEvent(activity->timer.duration_from_base() + 4096, &::FuncSource::game_activity_diqczi_eventer_1, ::Lparam{.ull = 2ULL}));
        activity->timer.prepare(::TimedEvent(activity->timer.duration_from_base() + 8192, &::FuncSource::game_activity_diqczi_eventer_1, ::Lparam{.ull = 0ULL}));
        activity->timer.prepare(::TimedEvent(activity->timer.duration_from_base() + 12288, &::FuncSource::game_activity_diqczi_eventer_1, ::Lparam{.ull = 1ULL}));
        activity->timer.prepare(::TimedEvent(activity->timer.duration_from_base() + 12288, &::FuncSource::game_activity_diqczi_eventer_1, ::Lparam{.ull = 2ULL}));
        activity->timer.prepare(::TimedEvent(activity->timer.duration_from_base() + 16384, &::FuncSource::game_activity_diqczi_eventer_0_init, {}));
    }
    void game_activity_diqczi_eventer_1(void *param, ::Lparam lparam) {
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        ::QuadDisplayer *diqczi{new ::QuadDisplayer(&::FuncSource::game_activity_diqczi_updater_1, ::TexSource::tex_ids["druangczea_niqluh"], 0.0, 0.0, 24.0, 24.0)};
        diqczi->lparam_map[::UpdaterLparamType::ULT_HEAL].ll = 128LL;
        switch (lparam.ull) {
            case 0ULL: {
                diqczi->lparam_map[::UpdaterLparamType::ULT_SETX].d = diqczi->x = 256.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_SETY].d = diqczi->y = 640.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_DX].d = 0.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_DY].d = -768.0;
                // diqczi->located_x = {256.0, 256.0};
                // diqczi->located_y = {640.0, -256.0};
                break;
            }
            case 1ULL: {
                diqczi->lparam_map[::UpdaterLparamType::ULT_SETX].d = diqczi->x = 64.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_SETY].d = diqczi->y = 640.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_DX].d = 0.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_DY].d = -768.0;
                // diqczi->located_x = {64.0, 64.0};
                // diqczi->located_y = {640.0, -256.0};
                break;
            }
            case 2ULL: {
                diqczi->lparam_map[::UpdaterLparamType::ULT_SETX].d = diqczi->x = 448.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_SETY].d = diqczi->y = 640.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_DX].d = 0.0;
                diqczi->lparam_map[::UpdaterLparamType::ULT_DY].d = -768.0;
                // diqczi->located_x = {448.0, 448.0};
                // diqczi->located_y = {640.0, -256.0};
                break;
            }
        }
        // diqczi->x = diqczi->located_x[0];
        // diqczi->y = diqczi->located_y[0];
        activity->diqczi_list.emplace_back(diqczi);
        activity->updater_status[diqczi] = true;
// ::std::cout << __LINE__ << '\t' << diqczi << '\t' << lparam.ull << '\t' << (diqczi->setting_time - activity->timer.base_time).count() *  1e-6 << '\n';
        for (unsigned int i{0U}; i < 16384U; i += 2048U) {
            activity->timer.prepare(::TimedEvent(activity->timer.duration_from_base() + i, &::FuncSource::game_activity_diqdann_eventer_1, ::Lparam{.p = diqczi}));
            activity->timer.prepare(::TimedEvent(activity->timer.duration_from_base() + i + 128, &::FuncSource::game_activity_diqdann_eventer_1, ::Lparam{.p = diqczi}));
            activity->timer.prepare(::TimedEvent(activity->timer.duration_from_base() + i + 256, &::FuncSource::game_activity_diqdann_eventer_1, ::Lparam{.p = diqczi}));
// break;
        }
    }
    void game_activity_diqczi_updater_1(void *param, ::Lparam) {
        ::QuadDisplayer *updater{reinterpret_cast<::QuadDisplayer *>(param)};
        double const duration{(::std::chrono::system_clock::now() - updater->setting_time).count() * 1e-6};
        double const process{duration * 0.125e-3};
        if (process < 1.0) {
            updater->x = updater->lparam_map[::UpdaterLparamType::ULT_SETX].d + process * updater->lparam_map[::UpdaterLparamType::ULT_DX].d;
            updater->y = updater->lparam_map[::UpdaterLparamType::ULT_SETY].d + process * updater->lparam_map[::UpdaterLparamType::ULT_DY].d;
            // updater->x = (1 - process) * updater->located_x[0] + process * updater->located_x[1];
            // updater->y = (1 - process) * updater->located_y[0] + process * updater->located_y[1];
        } else {
            updater->update_func = &::FuncSource::null_updater;
        }
    }
    void game_activity_diqdann_eventer_1(void *param, ::Lparam lparam) {
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        ::QuadDisplayer *diqczi{reinterpret_cast<::QuadDisplayer *>(lparam.p)};
// ::std::cout << diqczi << '\n'; 
        if (activity->updater_status[diqczi]) {
            double const theta{::atan2(activity->tzuihczi.y - diqczi->y, activity->tzuihczi.x - diqczi->x) - M_PI_2};
            for (double offset_theta{0.0}; offset_theta < M_PI * 2; offset_theta += M_PI * 0.0625) {
                ::RotatedQuadDisplayer *diqdann{new ::RotatedQuadDisplayer(&::FuncSource::game_activity_diqdann_updater_1, ::TexSource::tex_ids["diamond_bullet_blue"], diqczi->x, diqczi->y, 8.0, 8.0, M_PI_2, theta + offset_theta)};
                // diqdann->lparam_list = {M_PI_2, theta + offset_theta};
    // ::std::cout << __LINE__ << '\t' << diqdann->x << '\t' << diqdann->y << '\n';
                activity->diqdann_list.emplace_back(diqdann);
                activity->updater_status[diqdann] = true;
            }
        }
    }
    void game_activity_diqdann_updater_1(void *param, ::Lparam lparam) {
        ::RotatedQuadDisplayer *updater{reinterpret_cast<::RotatedQuadDisplayer *>(param)};
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(lparam.p)};
        // double const duration{(::std::chrono::system_clock::now() - updater->setting_time).count() * 1e-6};
        // double const process{duration * 64e-3};
        double const duration{activity->timer.duration_from_latest()};
        double const process{duration * 128e-3};
        double const theta{updater->lparam_map[::UpdaterLparamType::ULT_THETA].d};
// ::std::cout << __LINE__ << '\t' << updater->x << '\t' << updater->y << '\n';
        updater->x -= ::sin(theta) * process;
        updater->y += ::cos(theta) * process;
// ::std::cout << __LINE__ << '\t' << updater->x << '\t' << updater->y << '\t' << activity->diqdann_list.size() << '\n';
        // updater->x = updater->set_x + process * updater->dx;
        // updater->y = updater->set_y + process * updater->dy;
    }
}

// TEST
namespace FuncSource {
    void game_activity_diqczi_eventer_test_init(void *param, ::Lparam) {
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        ::QuadDisplayer *diqczi{new ::QuadDisplayer(&::FuncSource::null_updater, ::TexSource::tex_ids["druangczea_niqluh"], 256.0, 512.0, 64.0, 64.0)};
        diqczi->lparam_map[::UpdaterLparamType::ULT_HEAL].ll = 256LL;
        activity->diqczi_list.emplace_back(diqczi);
        activity->updater_status[diqczi] = true;
        for (unsigned long long i{0ULL}; i < 65536ULL; i += 2048ULL) {
            activity->timer.prepare(::TimedEvent(activity->timer.duration_from_base() + i, &::FuncSource::game_activity_diqdann_eventer_test, ::Lparam{.p = diqczi}));
        }
    }
    void game_activity_diqdann_eventer_test(void *param, ::Lparam lparam) {
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        ::QuadDisplayer *diqczi{reinterpret_cast<::QuadDisplayer *>(lparam.p)};
        if (activity->updater_status[diqczi]) {
            activity->diqdann_list.emplace_back(new ::QuadDisplayer(&::FuncSource::game_activity_diqdann_updater_test, ::TexSource::tex_ids["dahzziuh_green"], diqczi->x, diqczi->y, 16.0, 16.0));
        }
    }
    void game_activity_diqdann_updater_test(void *param, ::Lparam lparam) {
        ::QuadDisplayer *updater{reinterpret_cast<::QuadDisplayer *>(param)};
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(lparam.p)};
        double const duration{activity->timer.duration_from_latest()};
        double const process{duration * 256e-3};
        updater->y -= process;
    }
}

#endif
