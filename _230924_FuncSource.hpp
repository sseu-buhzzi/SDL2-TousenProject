#ifndef FUNC_SOURCE_HPP
#define FUNC_SOURCE_HPP

#include ".\headers.hpp"

namespace FuncSource::General {
    inline double calc_norm(double, double);
    inline double calc_signed_angle(double);
    inline double calc_unsigned_angle(double);
    inline void null_updater(void *, ::Lparam);
}

namespace FuncSource::Characters {
    inline void updater_tzuihczi(void *, ::Lparam);
    inline void updater_boss(void *, ::Lparam);
    inline void updater_tzuihdann(void *, ::Lparam);
    inline void updater_tzoiczi(void *, ::Lparam);
    inline void updater_tzoidann(void *, ::Lparam);
    inline void updater_tzuihczi_recover(void *, ::Lparam);
}

namespace FuncSource::MainActivity {
    inline void updater_smooth(void *, ::Lparam);
    inline void updater_zzingxua(void *, ::Lparam);
}

namespace FuncSource::Stuffs {
    inline void updater_daycziuh_explode(void *, ::Lparam);
    inline void updater_daycziuh_fall(void *, ::Lparam);
    inline void updater_ssiaygoo_graze(void *, ::Lparam);
    inline void eventer_cziguang_recover(void *, ::std::unordered_map<::LparamUsage, ::Lparam> *);
    // inline void graze_per_256_milliseconds_eventer(void *, ::std::unordered_map<::LparamUsage, ::Lparam> *);
}

namespace FuncSource::Diqczi_0 {
    inline void eventer_init(void *, ::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void updater_init(void *, ::Lparam);
    inline void eventer_diqczi(void *, ::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void updater_diqczi(void *, ::Lparam);
    inline void eventer_diqdann(void *, ::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void updater_diqdann(void *, ::Lparam);
    inline void eventer_quit(void *, ::std::unordered_map<::LparamUsage, ::Lparam> *);
}

namespace FuncSource::Diqczi_1 {
    inline void eventer_init(void *, ::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void eventer_diqczi(void *, ::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void updater_diqczi(void *, ::Lparam);
    inline void eventer_diqdann(void *, ::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void updater_diqdann(void *, ::Lparam);
}

namespace FuncSource::Diqczi_2 {
    inline void eventer_init(void *, ::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void updater_diqczi(void *, ::Lparam);
    inline void eventer_diqdann(void *, ::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void updater_diqdann_0(void *, ::Lparam);
    inline void updater_diqdann_1(void *, ::Lparam);
}

namespace FuncSource::Diqczi_3 {
    inline void eventer_init(void *, ::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void updater_ssiaygoo_boss_showup(void *, ::Lparam);
    inline void updater_ssiaygoo_name_showup(void *, ::Lparam);
    inline void updater_boss(void *, ::Lparam);
    inline void updater_ssiaygoo_0(void *, ::Lparam);
    inline void eventer_diqdann_0(void *, ::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void updater_diqdann_0(void *, ::Lparam);
    inline void eventer_cziguang_1(void *, ::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void updater_cziguang_1(void *, ::Lparam);
}

namespace FuncSource::Diqczi_Test {
    inline void eventer_init(void *, ::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void eventer_diqdann(void *, ::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void updater_diqdann(void *, ::Lparam);
}

namespace FuncSource::Diqczi_Test_1 {
    inline void eventer_init(void *, ::std::unordered_map<::LparamUsage, ::Lparam> *);
}

// 通用
namespace FuncSource::General {
    double calc_norm(double x, double y) {
        return ::sqrt(x * x + y * y);
    }
    double calc_signed_angle(double a) {
        return (a = ::fmod(a, M_PI * 2)) < -M_PI ? a + M_PI * 2 : a >= M_PI ? a - M_PI * 2 : a;
    }
    double calc_unsigned_angle(double a) {
        return (a = ::fmod(a, M_PI * 2)) < 0 ? a + M_PI * 2 : a;
    }
    void null_updater(void *, ::Lparam) { }
}

// 標題畫面
namespace FuncSource::MainActivity {
    void updater_smooth(void *param, ::Lparam lparam) {
        ::QuadDisplayer *updater{reinterpret_cast<::QuadDisplayer *>(param)};
        const unsigned int duration{(unsigned int)((::std::chrono::system_clock::now() - updater->setting_time).count()) >> 20};
// ::std::cout <<__LINE__ << '\t' << duration << "\n";
        if (duration < 1024) {
            const double process{1 - (duration * 1e-3 - 1) * (duration * 1e-3 - 1)};
            updater->x = updater->lparam_map[::LparamUsage::LU_SETX].d + process * updater->lparam_map[::LparamUsage::LU_DX].d;
            updater->y = updater->lparam_map[::LparamUsage::LU_SETY].d + process * updater->lparam_map[::LparamUsage::LU_DY].d;
        } else {
            ::MainActivity *activity(reinterpret_cast<::MainActivity *>(lparam.p));
            activity->has_animation_completed = true;
            updater->x = updater->lparam_map[::LparamUsage::LU_SETX].d + updater->lparam_map[::LparamUsage::LU_DX].d;
            updater->y = updater->lparam_map[::LparamUsage::LU_SETY].d + updater->lparam_map[::LparamUsage::LU_DY].d;
            updater->update_func = &::FuncSource::General::null_updater;
        }
    }
    void updater_zzingxua(void *param, ::Lparam lparam) {
        ::RotatedQuadDisplayer *updater{reinterpret_cast<::RotatedQuadDisplayer *>(param)};
        ::MainActivity *activity{reinterpret_cast<::MainActivity *>(lparam.p)};
        const unsigned int duration{activity->timer.duration_from_latest};
        // const double process{duration};
// ::std::cout << updater->lparam_map[::LparamUsage::LU_DX].d << '\t' << updater->lparam_map[::LparamUsage::LU_DY].d << '\n';
        updater->x += updater->lparam_map[::LparamUsage::LU_DX].d * duration;
        updater->y += updater->lparam_map[::LparamUsage::LU_DY].d * duration;
        updater->lparam_map[::LparamUsage::LU_THETA].d -= updater->lparam_map[::LparamUsage::LU_DX].d * duration * 0.0625;
        updater->lparam_map[::LparamUsage::LU_DX].d += duration * 64e-6;
// updater->half_width = updater->half_height = 16.0;
    }
}

// 角色們
namespace FuncSource::Characters {
    void updater_tzuihczi(void *param, ::Lparam lparam) {
        ::MirroredQuadDisplayer *updater{reinterpret_cast<::MirroredQuadDisplayer *>(param)};
        ::GameActivity *activity(reinterpret_cast<::GameActivity *>(lparam.p));
        unsigned int duration{activity->timer.duration_from_latest};
        if (updater->lparam_map[::LparamUsage::LU_IS_SLOW].b) {
            duration *= 0.25;
        }
        updater->x += updater->lparam_map[::LparamUsage::LU_DX].d * duration;
        updater->y += updater->lparam_map[::LparamUsage::LU_DY].d * duration;
        if (updater->lparam_map[::LparamUsage::LU_IS_SHOOTING].b && !updater->lparam_map[::LparamUsage::LU_IS_IN_SHOOTING_BREAK].b) {
            updater->lparam_map[::LparamUsage::LU_IS_IN_SHOOTING_BREAK].b = true;
            ::std::thread([updater]() -> void {
                ::std::this_thread::sleep_for(::std::chrono::milliseconds(64));
                updater->lparam_map[::LparamUsage::LU_IS_IN_SHOOTING_BREAK].b = false;
            }).detach();
//             ::QuadDisplayer *tzuihdann;
//             unsigned int tex_id_left, tex_id_right;
//             if (updater->lparam_map[::LparamUsage::LU_IS_HMIRRORED].b) {
//                 tex_id_left = ::TexSource::tex_ids["shoigu"];
//                 tex_id_right = ::TexSource::tex_ids["gerasimov"];
//             } else {
//                 tex_id_left = ::TexSource::tex_ids["gerasimov"];
//                 tex_id_right = ::TexSource::tex_ids["shoigu"];
//             }
//             activity->tzuihdann_list.emplace_back(tzuihdann = new ::QuadDisplayer(&::FuncSource::Characters::updater_tzuihdann, tex_id_left, activity->tzuihczi.x - 16, activity->tzuihczi.y, 16.0, 16.0));
//             tzuihdann->lparam_map[::LparamUsage::LU_SETX].d = tzuihdann->x;
//             tzuihdann->lparam_map[::LparamUsage::LU_SETY].d = tzuihdann->y;
//             tzuihdann->lparam_map[::LparamUsage::LU_DX].d = 0.0;
//             tzuihdann->lparam_map[::LparamUsage::LU_DY].d = 1.0;
//             activity->updater_status[tzuihdann] = true;
//             activity->tzuihdann_list.emplace_back(tzuihdann = new ::QuadDisplayer(&::FuncSource::Characters::updater_tzuihdann, tex_id_right, activity->tzuihczi.x + 16, activity->tzuihczi.y, 16.0, 16.0));
//             tzuihdann->lparam_map[::LparamUsage::LU_SETX].d = tzuihdann->x;
//             tzuihdann->lparam_map[::LparamUsage::LU_SETY].d = tzuihdann->y;
//             tzuihdann->lparam_map[::LparamUsage::LU_DX].d = 0.0;
//             tzuihdann->lparam_map[::LparamUsage::LU_DY].d = 1.0;
//             activity->updater_status[tzuihdann] = true;
//             // if (updater->lparam_map[::LparamUsage::LU_IS_HMIRRORED].b) {
//             //     activity->tzuihdann_list.emplace_back(tzuihdann = new ::QuadDisplayer(&::FuncSource::Characters::updater_tzuihdann, ::TexSource::tex_ids["shoigu"], activity->tzuihczi.x - 16, activity->tzuihczi.y, 16.0, 16.0));
//             //     tzuihdann->lparam_map[::LparamUsage::LU_SETX].d = tzuihdann->x;
//             //     tzuihdann->lparam_map[::LparamUsage::LU_SETY].d = tzuihdann->y;
//             //     tzuihdann->lparam_map[::LparamUsage::LU_DX].d = 0.0;
//             //     tzuihdann->lparam_map[::LparamUsage::LU_DY].d = 1.0;
//             //     activity->updater_status[tzuihdann] = true;
//             //     activity->tzuihdann_list.emplace_back(tzuihdann = new ::QuadDisplayer(&::FuncSource::Characters::updater_tzuihdann, ::TexSource::tex_ids["gerasimov"], activity->tzuihczi.x + 16, activity->tzuihczi.y, 16.0, 16.0));
//             //     tzuihdann->lparam_map[::LparamUsage::LU_SETX].d = tzuihdann->x;
//             //     tzuihdann->lparam_map[::LparamUsage::LU_SETY].d = tzuihdann->y;
//             //     tzuihdann->lparam_map[::LparamUsage::LU_DX].d = 0.0;
//             //     tzuihdann->lparam_map[::LparamUsage::LU_DY].d = 1.0;
//             //     activity->updater_status[tzuihdann] = true;
//             // } else {
//             //     activity->tzuihdann_list.emplace_back(tzuihdann = new ::QuadDisplayer(&::FuncSource::Characters::updater_tzuihdann, ::TexSource::tex_ids["gerasimov"], activity->tzuihczi.x - 16, activity->tzuihczi.y, 16.0, 16.0));
//             //     tzuihdann->lparam_map[::LparamUsage::LU_SETX].d = tzuihdann->x;
//             //     tzuihdann->lparam_map[::LparamUsage::LU_SETY].d = tzuihdann->y;
//             //     tzuihdann->lparam_map[::LparamUsage::LU_DX].d = 0.0;
//             //     tzuihdann->lparam_map[::LparamUsage::LU_DY].d = 1.0;
//             //     activity->updater_status[tzuihdann] = true;
//             //     activity->tzuihdann_list.emplace_back(tzuihdann = new ::QuadDisplayer(&::FuncSource::Characters::updater_tzuihdann, ::TexSource::tex_ids["shoigu"], activity->tzuihczi.x + 16, activity->tzuihczi.y, 16.0, 16.0));
//             //     tzuihdann->lparam_map[::LparamUsage::LU_SETX].d = tzuihdann->x;
//             //     tzuihdann->lparam_map[::LparamUsage::LU_SETY].d = tzuihdann->y;
//             //     tzuihdann->lparam_map[::LparamUsage::LU_DX].d = 0.0;
//             //     tzuihdann->lparam_map[::LparamUsage::LU_DY].d = 1.0;
//             //     activity->updater_status[tzuihdann] = true;
//             // }
//             for (::std::vector<::RotatedQuadDisplayer>::iterator tzoiczi(activity->tzoiczi_list.begin()); tzoiczi != activity->tzoiczi_list.end(); ++tzoiczi) {
//                 // double theta{(0.875 - (tzoiczi - activity->tzoiczi_list.begin()) * 0.25) * M_PI};
//                 ::RotatedQuadDisplayer *tzoidann{new ::RotatedQuadDisplayer(&::FuncSource::Characters::updater_tzoidann, ::TexSource::tex_ids["tracking_bullet"], tzoiczi->x, tzoiczi->y, 8.0, 8.0, M_PI_2, (0.375 - (tzoiczi - activity->tzoiczi_list.begin()) * 0.25) * M_PI)};
//                 tzoidann->lparam_map[::LparamUsage::LU_TARGET].p = activity->diqczi_list.empty() ? nullptr : activity->diqczi_list[::rand() % activity->diqczi_list.size()];
// // ::std::cout << tzoidann->lparam_map[::LparamUsage::LU_TARGET].p << '\t' << activity->diqczi_list.front() << '\n';
//                 activity->tzuihdann_list.emplace_back(tzoidann);
//                 activity->updater_status[tzoidann] = true;
//             }
            activity->tzuihczi_shoot();
        }
    }
    void updater_boss(void *param, ::Lparam) {
        ::MirroredQuadDisplayer *updater{reinterpret_cast<::MirroredQuadDisplayer *>(param)};
        updater->y = 128.0;
    }
    void updater_tzuihdann(void *param, ::Lparam lparam) {
        ::QuadDisplayer *updater{reinterpret_cast<::QuadDisplayer *>(param)};
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(lparam.p)};
        // const unsigned int duration{::FuncSource::duration_to_now(updater->basetime)};
        const unsigned int duration{activity->timer.duration_from_latest};
// 實際上每個自彈都有自己的進程，所以統一用這個activity->timer是否合適呢？
        // const unsigned int duration{(::std::chrono::system_clock::now().time_since_epoch().count() - updater->exsist_time) * 1024e-9};
        // double const process{duration * 1e-6};
        updater->x += duration * updater->lparam_map[::LparamUsage::LU_DX].d;
        updater->y += duration * updater->lparam_map[::LparamUsage::LU_DY].d;
    }
    void updater_tzoiczi(void *param, ::Lparam lparam) {
        ::RotatedQuadDisplayer *updater{reinterpret_cast<::RotatedQuadDisplayer *>(param)};
// ::std::cout << __LINE__ << '\t' << updater->tzuihczi << '\n';
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(lparam.p)};
        const unsigned int duration{activity->timer.duration_from_latest};
        double const process{duration * 16e-3};
        ::MirroredQuadDisplayer *tzuihczi{reinterpret_cast<::MirroredQuadDisplayer *>(updater->lparam_map[::LparamUsage::LU_TARGET].p)};
        updater->x += (tzuihczi->x + updater->lparam_map[::LparamUsage::LU_DX].d - updater->x) * process;
        updater->y += (tzuihczi->y + updater->lparam_map[::LparamUsage::LU_DY].d - updater->y) * process;
        updater->lparam_map[::LparamUsage::LU_THETA].d += process * 0.5;
// ::std::cout << __LINE__ << '\t' << activity->timer.latest_time.time_since_epoch().count() - activity->timer.second_latest_time.time_since_epoch().count() << '\t' << updater->theta << '\n';
// ::std::cout << __LINE__ << '\t' << activity->timer.duration_from_latest << '\n';
    }
    void updater_tzoidann(void *param, ::Lparam lparam) {
        ::RotatedQuadDisplayer *updater{reinterpret_cast<::RotatedQuadDisplayer *>(param)};
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(lparam.p)};
        const unsigned int duration{activity->timer.duration_from_latest};
        double *theta{&updater->lparam_map[::LparamUsage::LU_THETA].d};
        ::QuadDisplayer *diqczi{reinterpret_cast<::QuadDisplayer *>(updater->lparam_map[::LparamUsage::LU_TARGET].p)};
// ::std::cout << diqczi->x << '\t' << diqczi->y << '\n';
        double const direction{diqczi != nullptr && activity->updater_status[diqczi] ? ::atan2(diqczi->x - updater->x, diqczi->y - updater->y) : -*theta};
// direction = 0.0;
// ::std::cout << direction * M_1_PI * 180 << '\n';
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
        *theta -= ::FuncSource::General::calc_signed_angle(direction + *theta) * duration * 64e-3;
        updater->x -= ::sin(*theta) * duration;
        updater->y += ::cos(*theta) * duration;
    }
    void updater_tzuihczi_recover(void *param, ::Lparam lparam) {
        ::MirroredQuadDisplayer *updater{reinterpret_cast<::MirroredQuadDisplayer *>(param)};
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(lparam.p)};
        const unsigned int duration{activity->timer.duration_from_latest};
        double const process{duration * 64e-3};
        updater->y += process;
        if (updater->y >= 64.0) {
            updater->y = 64.0;
            updater->update_func = &::FuncSource::Characters::updater_tzuihczi;
        }
        if (updater->lparam_map[::LparamUsage::LU_IS_SHOOTING].b && !updater->lparam_map[::LparamUsage::LU_IS_IN_SHOOTING_BREAK].b) {
            updater->lparam_map[::LparamUsage::LU_IS_IN_SHOOTING_BREAK].b = true;
            ::std::thread([updater]() -> void {
                ::std::this_thread::sleep_for(::std::chrono::milliseconds(64));
                updater->lparam_map[::LparamUsage::LU_IS_IN_SHOOTING_BREAK].b = false;
            }).detach();
            activity->tzuihczi_shoot();
        }
    }
}

// 小東西
namespace FuncSource::Stuffs {
    void updater_daycziuh_explode(void *param, ::Lparam) {
        ::QuadDisplayer *updater{reinterpret_cast<::QuadDisplayer *>(param)};
        const unsigned int duration{(unsigned int)((::std::chrono::system_clock::now() - updater->setting_time).count()) >> 20};
        double const process{1 - ::pow(duration * 1e-3 - 1, 2.0)};
        if (duration < 1e3) {
            updater->x = updater->lparam_map[::LparamUsage::LU_SETX].d + process * updater->lparam_map[::LparamUsage::LU_DX].d;
            updater->y = updater->lparam_map[::LparamUsage::LU_SETY].d + process * updater->lparam_map[::LparamUsage::LU_DY].d;
        } else {
            updater->update_func = &::FuncSource::Stuffs::updater_daycziuh_fall;
        }
    }
    void updater_daycziuh_fall(void *param, ::Lparam lparam) {
        ::QuadDisplayer *updater{reinterpret_cast<::QuadDisplayer *>(param)};
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(lparam.p)};
        const unsigned int duration{activity->timer.duration_from_latest};
        double const process{duration * 128e-3};
        updater->y -= process;
    }
    void updater_ssiaygoo_graze(void *param, ::Lparam) {
        ::QuadDisplayer *updater{reinterpret_cast<::QuadDisplayer *>(param)};
        const unsigned int duration{(unsigned int)((::std::chrono::system_clock::now() - updater->setting_time).count()) >> 20};
        double const process{1 - ::pow(duration * 1e-3 - 1, 2.0)};
        if (duration < 1e3) {
            updater->x = updater->lparam_map[::LparamUsage::LU_SETX].d + process * updater->lparam_map[::LparamUsage::LU_DX].d;
            updater->y = updater->lparam_map[::LparamUsage::LU_SETY].d + process * updater->lparam_map[::LparamUsage::LU_DY].d;
            updater->half_width = updater->half_height = (1 - process) * 8;
        } else {
            updater->lparam_map[::LparamUsage::LU_EXISTENCE].b = false;
            updater->update_func = &::FuncSource::General::null_updater;
        }
    }
    // 爲啥叫recover？
    void eventer_cziguang_recover(void *, ::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
        ::LineDisplayer *updater{reinterpret_cast<::LineDisplayer *>(lparam_map->at(::LparamUsage::LU_TARGET).p)};
        updater->lparam_map[::LparamUsage::LU_IS_GRAZED].b = false;
    }
    // void graze_per_256_milliseconds_eventer(void *param, ::std::unordered_map<::LparamUsage, ::Lparam> *) {
    //     ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
    //     activity->graze_per_128_milliseconds = 0U;
    //     activity->timer.prepare(::TimedEvent(activity->timer.duration_from_base + 128, &::FuncSource::Stuffs::graze_per_256_milliseconds_eventer));
    // }
}

// 第一波敵機(diqczi_0)
namespace FuncSource::Diqczi_0 {
    void eventer_init(void *param, ::std::unordered_map<::LparamUsage, ::Lparam> *) {
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        for (unsigned int i{0U}; i < 10U; ++i) {
// ::std::cout << __LINE__ << '\t' << '\n';
            ::TimedEvent event(activity->timer.duration_from_base + ::rand() % 1024, &::FuncSource::Diqczi_0::eventer_diqczi);
            event.lparam_map[::LparamUsage::LU_CHOICE].ull = i;
// ::std::cout << __LINE__ << '\t' << '\n';
            activity->timer.prepare(event);
// ::std::cout << __LINE__ << '\t' << '\n';
        }
        activity->event_updater = new ::Updater(&::FuncSource::Diqczi_0::updater_init);
        activity->updater_status[activity->event_updater] = true;
// ::std::cout << __LINE__ << '\t' << '\n';
    }
    void updater_init(void *param, ::Lparam lparam) {
        ::Updater *updater{reinterpret_cast<::Updater *>(param)};
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(lparam.p)};
        if (activity->updater_status[updater]) {
            const unsigned int duration{(unsigned int)((::std::chrono::system_clock::now() - updater->setting_time).count()) >> 20};
            if (duration >= 1024 && activity->diqczi_list.empty()) {
                activity->updater_status[updater] = false;
                delete updater;
                activity->event_updater = nullptr;
                ::TimedEvent event(4096, &::FuncSource::Diqczi_1::eventer_init);
                event.lparam_map[::LparamUsage::LU_CHOICE].ull = 0ULL;
                activity->timer.prepare(event);
            }
        }
    }
    void eventer_diqczi(void *param, ::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        ::QuadDisplayer *diqczi{new ::QuadDisplayer(&::FuncSource::Diqczi_0::updater_diqczi, ::TexSource::tex_ids["druangczea_niqluh"], 0.0, 0.0, 16.0, 16.0)};
        diqczi->lparam_map[::LparamUsage::LU_HEAL].ll = 16LL;
        switch (lparam_map->at(::LparamUsage::LU_CHOICE).ull) {
            case 0ULL: {
                diqczi->lparam_map[::LparamUsage::LU_SETX].d = diqczi->x = 0.0;
                diqczi->lparam_map[::LparamUsage::LU_SETY].d = diqczi->y = 0.0;
                diqczi->lparam_map[::LparamUsage::LU_DX].d = 64.0;
                diqczi->lparam_map[::LparamUsage::LU_DY].d = 528.0;
                break;
            }
            case 1ULL: {
                diqczi->lparam_map[::LparamUsage::LU_SETX].d = diqczi->x = 0.0;
                diqczi->lparam_map[::LparamUsage::LU_SETY].d = diqczi->y = 0.0;
                diqczi->lparam_map[::LparamUsage::LU_DX].d = 96.0;
                diqczi->lparam_map[::LparamUsage::LU_DY].d = 520.0;
                break;
            }
            case 2ULL: {
                diqczi->lparam_map[::LparamUsage::LU_SETX].d = diqczi->x = 0.0;
                diqczi->lparam_map[::LparamUsage::LU_SETY].d = diqczi->y = 0.0;
                diqczi->lparam_map[::LparamUsage::LU_DX].d = 128.0;
                diqczi->lparam_map[::LparamUsage::LU_DY].d = 512.0;
                break;
            }
            case 3ULL: {
                diqczi->lparam_map[::LparamUsage::LU_SETX].d = diqczi->x = 0.0;
                diqczi->lparam_map[::LparamUsage::LU_SETY].d = diqczi->y = 0.0;
                diqczi->lparam_map[::LparamUsage::LU_DX].d = 160.0;
                diqczi->lparam_map[::LparamUsage::LU_DY].d = 504.0;
                break;
            }
            case 4ULL: {
                diqczi->lparam_map[::LparamUsage::LU_SETX].d = diqczi->x = 0.0;
                diqczi->lparam_map[::LparamUsage::LU_SETY].d = diqczi->y = 0.0;
                diqczi->lparam_map[::LparamUsage::LU_DX].d = 192.0;
                diqczi->lparam_map[::LparamUsage::LU_DY].d = 496.0;
                break;
            }
            case 5ULL: {
                diqczi->lparam_map[::LparamUsage::LU_SETX].d = diqczi->x = 512.0;
                diqczi->lparam_map[::LparamUsage::LU_SETY].d = diqczi->y = 0.0;
                diqczi->lparam_map[::LparamUsage::LU_DX].d = -64.0;
                diqczi->lparam_map[::LparamUsage::LU_DY].d = 528.0;
                break;
            }
            case 6ULL: {
                diqczi->lparam_map[::LparamUsage::LU_SETX].d = diqczi->x = 512.0;
                diqczi->lparam_map[::LparamUsage::LU_SETY].d = diqczi->y = 0.0;
                diqczi->lparam_map[::LparamUsage::LU_DX].d = -96.0;
                diqczi->lparam_map[::LparamUsage::LU_DY].d = 520.0;
                break;
            }
            case 7ULL: {
                diqczi->lparam_map[::LparamUsage::LU_SETX].d = diqczi->x = 512.0;
                diqczi->lparam_map[::LparamUsage::LU_SETY].d = diqczi->y = 0.0;
                diqczi->lparam_map[::LparamUsage::LU_DX].d = -128.0;
                diqczi->lparam_map[::LparamUsage::LU_DY].d = 512.0;
                break;
            }
            case 8ULL: {
                diqczi->lparam_map[::LparamUsage::LU_SETX].d = diqczi->x = 512.0;
                diqczi->lparam_map[::LparamUsage::LU_SETY].d = diqczi->y = 0.0;
                diqczi->lparam_map[::LparamUsage::LU_DX].d = -160.0;
                diqczi->lparam_map[::LparamUsage::LU_DY].d = 504.0;
                break;
            }
            case 9ULL: {
                diqczi->lparam_map[::LparamUsage::LU_SETX].d = diqczi->x = 512.0;
                diqczi->lparam_map[::LparamUsage::LU_SETY].d = diqczi->y = 0.0;
                diqczi->lparam_map[::LparamUsage::LU_DX].d = -192.0;
                diqczi->lparam_map[::LparamUsage::LU_DY].d = 496.0;
                break;
            }
        }
        activity->diqczi_list.emplace_back(diqczi);
        activity->updater_status[diqczi] = true;
// ::std::cout << __LINE__ << '\t' << '\n';
        for (unsigned int i{2048}; i < 16384; i += 1024) {
            ::TimedEvent event(activity->timer.duration_from_base + i, &::FuncSource::Diqczi_0::eventer_diqdann);
            event.lparam_map[::LparamUsage::LU_TARGET].p = diqczi;
            activity->timer.prepare(event);
        }
        ::TimedEvent event(activity->timer.duration_from_base + 16384, &::FuncSource::Diqczi_0::eventer_quit);
        event.lparam_map[::LparamUsage::LU_TARGET].p = diqczi;
        activity->timer.prepare(event);
    }
    void updater_diqczi(void *param, ::Lparam) {
        ::QuadDisplayer *updater{reinterpret_cast<::QuadDisplayer *>(param)};
        const unsigned int duration{(unsigned int)((::std::chrono::system_clock::now() - updater->setting_time).count()) >> 20};
        double const process{::log(duration * 4e-3 + 1)};
        if (process < 1.0) {
            updater->x = updater->lparam_map[::LparamUsage::LU_SETX].d + process * updater->lparam_map[::LparamUsage::LU_DX].d;
            updater->y = updater->lparam_map[::LparamUsage::LU_SETY].d + process * updater->lparam_map[::LparamUsage::LU_DY].d;
        } else {
            updater->x = updater->lparam_map[::LparamUsage::LU_SETX].d + updater->lparam_map[::LparamUsage::LU_DX].d;
            updater->y = updater->lparam_map[::LparamUsage::LU_SETY].d + updater->lparam_map[::LparamUsage::LU_DY].d;
            updater->update_func = &::FuncSource::General::null_updater;
        }
    }
    void eventer_diqdann(void *param, ::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        ::QuadDisplayer *diqczi{reinterpret_cast<::QuadDisplayer *>(lparam_map->at(::LparamUsage::LU_TARGET).p)};
        if (activity->updater_status[diqczi]) {
            double const theta{::atan2(activity->tzuihczi.y - diqczi->y, activity->tzuihczi.x - diqczi->x)};
            ::QuadDisplayer *diqdann{new ::QuadDisplayer(&::FuncSource::Diqczi_0::updater_diqdann, ::TexSource::tex_ids["dahzziuh_blue"], diqczi->x, diqczi->y, 16.0, 16.0)};
            diqdann->lparam_map[::LparamUsage::LU_SETX].d = diqdann->x;
            diqdann->lparam_map[::LparamUsage::LU_SETY].d = diqdann->y;
            diqdann->lparam_map[::LparamUsage::LU_DX].d = ::cos(theta);
            diqdann->lparam_map[::LparamUsage::LU_DY].d = ::sin(theta);
            activity->diqdann_list.emplace_back(diqdann);
            activity->updater_status[diqdann] = true;
        }
    }
    void updater_diqdann(void *param, ::Lparam) {
        ::QuadDisplayer *updater{reinterpret_cast<::QuadDisplayer *>(param)};
        const unsigned int duration{(unsigned int)((::std::chrono::system_clock::now() - updater->setting_time).count()) >> 20};
        double const process{duration * 512e-3};
        updater->x = updater->lparam_map[::LparamUsage::LU_SETX].d + process * updater->lparam_map[::LparamUsage::LU_DX].d;
        updater->y = updater->lparam_map[::LparamUsage::LU_SETY].d + process * updater->lparam_map[::LparamUsage::LU_DY].d;
    }
    void eventer_quit(void *param, ::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        ::QuadDisplayer *diqczi{reinterpret_cast<::QuadDisplayer *>(lparam_map->at(::LparamUsage::LU_TARGET).p)};
        if (activity->updater_status[diqczi]) {
            diqczi->lparam_map[::LparamUsage::LU_SETX].d = diqczi->x;
            diqczi->lparam_map[::LparamUsage::LU_SETY].d = diqczi->y;
            diqczi->lparam_map[::LparamUsage::LU_DX].d = 0.0;
            diqczi->lparam_map[::LparamUsage::LU_DY].d = 512.0;
            diqczi->setting_time = ::std::chrono::system_clock::now();
            diqczi->update_func = &::FuncSource::Diqczi_0::updater_diqczi;
        }
    }
}

// 第二波敵機(diqczi_1)
namespace FuncSource::Diqczi_1 {
    void eventer_init(void *param, ::std::unordered_map<::LparamUsage, ::Lparam> *) {
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        ::std::cout << "Second Event\n";
        // activity->timer.should_refresh = true;
        ::TimedEvent event(activity->timer.duration_from_base, &::FuncSource::Diqczi_1::eventer_diqczi);
        event.lparam_map[::LparamUsage::LU_CHOICE].ull = 0ULL;
        activity->timer.prepare(event);
        event.time += 4096;
        ++event.lparam_map[::LparamUsage::LU_CHOICE].ull;
        activity->timer.prepare(event);
        ++event.lparam_map[::LparamUsage::LU_CHOICE].ull;
        activity->timer.prepare(event);
        event.time += 4096;
        event.lparam_map[::LparamUsage::LU_CHOICE].ull = 0ULL;
        activity->timer.prepare(event);
        event.time += 4096;
        ++event.lparam_map[::LparamUsage::LU_CHOICE].ull;
        activity->timer.prepare(event);
        ++event.lparam_map[::LparamUsage::LU_CHOICE].ull;
        activity->timer.prepare(event);
        event = ::TimedEvent(::TimedEvent(activity->timer.duration_from_base + 16384, &::FuncSource::Diqczi_2::eventer_init));
        activity->timer.prepare(event);
    }
    void eventer_diqczi(void *param, ::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        ::QuadDisplayer *diqczi{new ::QuadDisplayer(&::FuncSource::Diqczi_1::updater_diqczi, ::TexSource::tex_ids["druangczea_niqluh"], 0.0, 0.0, 24.0, 24.0)};
        diqczi->lparam_map[::LparamUsage::LU_HEAL].ll = 128LL;
        switch (lparam_map->at(::LparamUsage::LU_CHOICE).ull) {
            case 0ULL: {
                diqczi->lparam_map[::LparamUsage::LU_SETX].d = diqczi->x = 256.0;
                diqczi->lparam_map[::LparamUsage::LU_SETY].d = diqczi->y = 640.0;
                diqczi->lparam_map[::LparamUsage::LU_DX].d = 0.0;
                diqczi->lparam_map[::LparamUsage::LU_DY].d = -768.0;
                break;
            }
            case 1ULL: {
                diqczi->lparam_map[::LparamUsage::LU_SETX].d = diqczi->x = 64.0;
                diqczi->lparam_map[::LparamUsage::LU_SETY].d = diqczi->y = 640.0;
                diqczi->lparam_map[::LparamUsage::LU_DX].d = 0.0;
                diqczi->lparam_map[::LparamUsage::LU_DY].d = -768.0;
                break;
            }
            case 2ULL: {
                diqczi->lparam_map[::LparamUsage::LU_SETX].d = diqczi->x = 448.0;
                diqczi->lparam_map[::LparamUsage::LU_SETY].d = diqczi->y = 640.0;
                diqczi->lparam_map[::LparamUsage::LU_DX].d = 0.0;
                diqczi->lparam_map[::LparamUsage::LU_DY].d = -768.0;
                break;
            }
        }
        activity->diqczi_list.emplace_back(diqczi);
        activity->updater_status[diqczi] = true;
        for (unsigned int i{0U}; i < 16384U; i += 2048U) {
            ::TimedEvent event(activity->timer.duration_from_base + i, &::FuncSource::Diqczi_1::eventer_diqdann);
            event.lparam_map[::LparamUsage::LU_TARGET].p = diqczi;
            activity->timer.prepare(event);
            event.time += 128;
            activity->timer.prepare(event);
            event.time += 128;
            activity->timer.prepare(event);
        }
    }
    void updater_diqczi(void *param, ::Lparam) {
        ::QuadDisplayer *updater{reinterpret_cast<::QuadDisplayer *>(param)};
        const unsigned int duration{(unsigned int)((::std::chrono::system_clock::now() - updater->setting_time).count()) >> 20};
        double const process{duration * 0.125e-3};
        if (process < 1.0) {
            updater->x = updater->lparam_map[::LparamUsage::LU_SETX].d + process * updater->lparam_map[::LparamUsage::LU_DX].d;
            updater->y = updater->lparam_map[::LparamUsage::LU_SETY].d + process * updater->lparam_map[::LparamUsage::LU_DY].d;
        } else {
            updater->update_func = &::FuncSource::General::null_updater;
        }
    }
    void eventer_diqdann(void *param, ::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        ::QuadDisplayer *diqczi{reinterpret_cast<::QuadDisplayer *>(lparam_map->at(::LparamUsage::LU_TARGET).p)};
        const unsigned int tex_ids[6]{::TexSource::tex_ids["diamond_bullet_red"], ::TexSource::tex_ids["diamond_bullet_yellow"], ::TexSource::tex_ids["diamond_bullet_green"], ::TexSource::tex_ids["diamond_bullet_cyan"], ::TexSource::tex_ids["diamond_bullet_blue"], ::TexSource::tex_ids["diamond_bullet_purple"]};
        const unsigned int *tex_id{tex_ids};
        if (activity->updater_status[diqczi]) {
            double const theta{::atan2(activity->tzuihczi.y - diqczi->y, activity->tzuihczi.x - diqczi->x) - M_PI_2};
            for (double offset_theta{0.0}; offset_theta < M_PI * 2; offset_theta += M_PI * 0.0625) {
                ::RotatedQuadDisplayer *diqdann{new ::RotatedQuadDisplayer(&::FuncSource::Diqczi_1::updater_diqdann, *tex_id, diqczi->x, diqczi->y, 8.0, 8.0, M_PI_2, theta + offset_theta)};
                activity->diqdann_list.emplace_back(diqdann);
                activity->updater_status[diqdann] = true;
                if (++tex_id >= tex_ids + 6) {
                    tex_id = tex_ids;
                }
            }
        }
    }
    void updater_diqdann(void *param, ::Lparam lparam) {
        ::RotatedQuadDisplayer *updater{reinterpret_cast<::RotatedQuadDisplayer *>(param)};
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(lparam.p)};
        const unsigned int duration{activity->timer.duration_from_latest};
        double const process{duration * 128e-3};
        double const theta{updater->lparam_map[::LparamUsage::LU_THETA].d};
        updater->x -= ::sin(theta) * process;
        updater->y += ::cos(theta) * process;
    }
}

// 第三波敵機(diqczi_2)
namespace FuncSource::Diqczi_2 {
    void eventer_init(void *param, ::std::unordered_map<::LparamUsage, ::Lparam> *) {
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        ::QuadDisplayer *diqczi{new ::QuadDisplayer(&::FuncSource::Diqczi_2::updater_diqczi, ::TexSource::tex_ids["druangczea_niqluh"], 256.0, 640.0, 32.0, 32.0)};
        diqczi->lparam_map[::LparamUsage::LU_HEAL].ll = 256LL;
        activity->diqczi_list.emplace_back(diqczi);
        activity->updater_status[diqczi] = true;
        for (unsigned int i{0U}; i < 4096U; i += 512U) {
            ::TimedEvent event(activity->timer.duration_from_base + i, &::FuncSource::Diqczi_2::eventer_diqdann);
            event.lparam_map[::LparamUsage::LU_TARGET].p = diqczi;
            activity->timer.prepare(event);
        }
        activity->timer.prepare(::TimedEvent(activity->timer.duration_from_base + 8192, &::FuncSource::Diqczi_3::eventer_init));
    }
    // void game_activity_diqczi_eventer_2(void *, ::std::unordered_map<::LparamUsage, ::Lparam> *) { }
    void updater_diqczi(void *param, ::Lparam lparam) {
        ::QuadDisplayer *updater{reinterpret_cast<::QuadDisplayer *>(param)};
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(lparam.p)};
        const unsigned int duration{activity->timer.duration_from_latest};
        double const process{duration * 64e-3};
        updater->y -= process;
    }
    void eventer_diqdann(void *param, ::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        ::QuadDisplayer *diqczi{reinterpret_cast<::QuadDisplayer *>(lparam_map->at(::LparamUsage::LU_TARGET).p)};
        for (int distance{64}; activity->updater_status[diqczi] && distance < 128; distance += 8) {
            double theta{-M_PI * 0.625};
            ::RotatedQuadDisplayer *diqdann{new ::RotatedQuadDisplayer(&::FuncSource::Diqczi_2::updater_diqdann_0, ::TexSource::tex_ids["dart_bullet_blue"], diqczi->x, diqczi->y, 8.0, 8.0, M_PI_2, theta)};
            diqdann->lparam_map[::LparamUsage::LU_SETX].d = diqdann->x;
            diqdann->lparam_map[::LparamUsage::LU_SETY].d = diqdann->y;
            diqdann->lparam_map[::LparamUsage::LU_DX].d = -::sin(theta) * distance;
            diqdann->lparam_map[::LparamUsage::LU_DY].d = ::cos(theta) * distance;
            activity->diqdann_list.emplace_back(diqdann);
            theta = M_PI * 0.625;
            diqdann = new ::RotatedQuadDisplayer(&::FuncSource::Diqczi_2::updater_diqdann_0, ::TexSource::tex_ids["dart_bullet_blue"], diqczi->x, diqczi->y, 8.0, 8.0, M_PI_2, theta);
            diqdann->lparam_map[::LparamUsage::LU_SETX].d = diqdann->x;
            diqdann->lparam_map[::LparamUsage::LU_SETY].d = diqdann->y;
            diqdann->lparam_map[::LparamUsage::LU_DX].d = -::sin(theta) * distance;
            diqdann->lparam_map[::LparamUsage::LU_DY].d = ::cos(theta) * distance;
            activity->diqdann_list.emplace_back(diqdann);
        }
    }
    void updater_diqdann_0(void *param, ::Lparam lparam) {
        ::RotatedQuadDisplayer *updater{reinterpret_cast<::RotatedQuadDisplayer *>(param)};
        const unsigned int duration{(unsigned int)((::std::chrono::system_clock::now() - updater->setting_time).count()) >> 20};
        double const process{::log(duration * 1e-3 + 1)};
        if (duration < 4e3) {
            updater->x = updater->lparam_map[::LparamUsage::LU_SETX].d + process * updater->lparam_map[::LparamUsage::LU_DX].d;
            updater->y = updater->lparam_map[::LparamUsage::LU_SETY].d + process * updater->lparam_map[::LparamUsage::LU_DY].d;
        } else {
            ::GameActivity *activity{reinterpret_cast<::GameActivity *>(lparam.p)};
            double const theta{::atan2(activity->tzuihczi.y - updater->y, activity->tzuihczi.x - updater->x)};
            updater->lparam_map[::LparamUsage::LU_THETA].d = theta - M_PI_2;
            updater->lparam_map[::LparamUsage::LU_DX].d = ::cos(theta);
            updater->lparam_map[::LparamUsage::LU_DY].d = ::sin(theta);
            updater->update_func = &::FuncSource::Diqczi_2::updater_diqdann_1;
        }
    }
    void updater_diqdann_1(void *param, ::Lparam lparam) {
        ::RotatedQuadDisplayer *updater{reinterpret_cast<::RotatedQuadDisplayer *>(param)};
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(lparam.p)};
        const unsigned int duration{activity->timer.duration_from_latest};
        double const process{duration * 256e-3};
        updater->x += process * updater->lparam_map[::LparamUsage::LU_DX].d;
        updater->y += process * updater->lparam_map[::LparamUsage::LU_DY].d;
    }
}

// 第四波敵機(boss_3)
namespace FuncSource::Diqczi_3 {
    void eventer_init(void *param, ::std::unordered_map<::LparamUsage, ::Lparam> *) {
        double const theta{M_PI / 6};
        double const cos_theta{::cos(theta)};
        double const sin_theta{::sin(theta)};
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        activity->gamearea.alpha = 0x10;
        // ::AudioSource::pause_audio(::AudioSource::audio_ids["harudomanno_youkai_shoujo"]);
        // ::AudioSource::rewind_audio(::AudioSource::audio_ids["sluziti_rossii"]);
        // ::AudioSource::play_audio(::AudioSource::audio_ids["sluziti_rossii"]);
        // 左右移動的字符
        for (int i {-8}; i < 20; ++i) {
            int const text_length{i & 1 ? 128 : 256};
            for (int j{0}; j < 8; ++j) {
                ::RotatedQuadDisplayer *ssiaygoo_name{new ::RotatedQuadDisplayer(&::FuncSource::Diqczi_3::updater_ssiaygoo_name_showup, ::TexSource::tex_ids[i & 1 ? "zelensikij_name" : "slava_ukrajni"], j * cos_theta * text_length - i * sin_theta * 32, i * cos_theta * 32 + j * sin_theta * text_length, 64, 16, M_PI_2, theta)};
                if (i & 1) {
                    ssiaygoo_name->lparam_map[::LparamUsage::LU_DX].d = -cos_theta;
                    ssiaygoo_name->lparam_map[::LparamUsage::LU_DY].d = -sin_theta;
                } else {
                    ssiaygoo_name->lparam_map[::LparamUsage::LU_DX].d = cos_theta;
                    ssiaygoo_name->lparam_map[::LparamUsage::LU_DY].d = sin_theta;
                }
                ssiaygoo_name->lparam_map[::LparamUsage::LU_EXISTENCE].b = true;
                activity->ssiaygoo_list.emplace_back(ssiaygoo_name);
            }
        }
        // boss的立繪（其實并不是）
        ::RotatedQuadDisplayer *ssiaygoo_boss{new ::RotatedQuadDisplayer(&::FuncSource::Diqczi_3::updater_ssiaygoo_boss_showup, ::TexSource::tex_ids["zelensikij"], 512.0, 512.0, 512.0, 256.0, M_PI_2, theta)};
        ssiaygoo_boss->lparam_map[::LparamUsage::LU_SETX].d = ssiaygoo_boss->x;
        ssiaygoo_boss->lparam_map[::LparamUsage::LU_SETY].d = ssiaygoo_boss->y;
        ssiaygoo_boss->lparam_map[::LparamUsage::LU_DX].d = -cos_theta * 512;
        ssiaygoo_boss->lparam_map[::LparamUsage::LU_DY].d = -sin_theta * 512;
        ssiaygoo_boss->lparam_map[::LparamUsage::LU_EXISTENCE].b = true;
        activity->ssiaygoo_list.emplace_back(ssiaygoo_boss);
        // delete ssiaygoo_boss;
        // 游戲畫面中的boss
        ::MirroredQuadDisplayer *boss{new ::MirroredQuadDisplayer(&::FuncSource::Diqczi_3::updater_boss, ::TexSource::tex_ids["zelensikij"], 256.0, 768.0, 128.0, 64.0, false, false)};
        boss->lparam_map[::LparamUsage::LU_SETX].d = boss->x;
        boss->lparam_map[::LparamUsage::LU_SETY].d = boss->y;
        boss->lparam_map[::LparamUsage::LU_DX].d = 0.0;
        boss->lparam_map[::LparamUsage::LU_DY].d = -256.0;
        boss->lparam_map[::LparamUsage::LU_HEAL].ll = 4096LL;
        activity->diqczi_list.emplace_back(boss);
        activity->updater_status[boss] = true;
        // return;
        // boss背後的六芒星
        ::RotatedQuadDisplayer *ssiaygoo_hexagram{new ::RotatedQuadDisplayer(&::FuncSource::Diqczi_3::updater_ssiaygoo_0, ::TexSource::tex_ids["hexagram_blue"], 256.0, 768.0, 128.0, 128.0, M_PI_2, 0.0)};
        ssiaygoo_hexagram->lparam_map[::LparamUsage::LU_TARGET].p = boss;
        ssiaygoo_hexagram->lparam_map[::LparamUsage::LU_EXISTENCE].b = true;
        activity->back_ssiaygoo_list.emplace_back(ssiaygoo_hexagram);
        for (unsigned int i{4U}; i < 256; ++i) {
            ::TimedEvent event(activity->timer.duration_from_base + i * 512, &::FuncSource::Diqczi_3::eventer_diqdann_0);
            event.lparam_map[::LparamUsage::LU_TARGET].p = boss;
            event.lparam_map[::LparamUsage::LU_CHOICE].ull = i;
            activity->timer.prepare(event);
        }
        ::TimedEvent event(activity->timer.duration_from_base + 4096, &::FuncSource::Diqczi_3::eventer_cziguang_1);
        event.lparam_map[::LparamUsage::LU_TARGET].p = boss;
        event.lparam_map[::LparamUsage::LU_CHOICE].b = false;
        activity->timer.prepare(event);
        event.time += 8192;
        activity->timer.prepare(event);
        event.time += 8192;
        activity->timer.prepare(event);
        event.time = activity->timer.duration_from_base + 4096;
        event.lparam_map[::LparamUsage::LU_CHOICE].b = true;
        activity->timer.prepare(event);
        event.time += 8192;
        activity->timer.prepare(event);
        event.time += 8192;
        activity->timer.prepare(event);
    }
    void updater_ssiaygoo_boss_showup(void *param, ::Lparam) {
        ::RotatedQuadDisplayer *updater{reinterpret_cast<::RotatedQuadDisplayer *>(param)};
        const unsigned int duration{(unsigned int)((::std::chrono::system_clock::now() - updater->setting_time).count()) >> 6};
        double const process{duration * 1e-3 * (duration * 1e-3 * (duration * 2e-3 - 3) + 2)};
// ::std::cout << updater->x << '\t' << updater->y << '\n';
        updater->x = updater->lparam_map[::LparamUsage::LU_SETX].d + process * updater->lparam_map[::LparamUsage::LU_DX].d;
        updater->y = updater->lparam_map[::LparamUsage::LU_SETY].d + process * updater->lparam_map[::LparamUsage::LU_DY].d;
    }
    void updater_ssiaygoo_name_showup(void *param, ::Lparam lparam) {
        ::RotatedQuadDisplayer *updater{reinterpret_cast<::RotatedQuadDisplayer *>(param)};
        if (::std::chrono::system_clock::now() < updater->setting_time + ::std::chrono::milliseconds(1024)) {
            ::GameActivity *activity{reinterpret_cast<::GameActivity *>(lparam.p)};
            const unsigned int duration{activity->timer.duration_from_latest};
            double const process{duration * 256e-3};
            updater->x += process * updater->lparam_map[::LparamUsage::LU_DX].d;
            updater->y += process * updater->lparam_map[::LparamUsage::LU_DY].d;
        } else {
            updater->lparam_map[::LparamUsage::LU_EXISTENCE].b = false;
        }
    }
    void updater_boss(void *param, ::Lparam) {
        ::MirroredQuadDisplayer *updater{reinterpret_cast<::MirroredQuadDisplayer *>(param)};
        const unsigned int duration{(unsigned int)((::std::chrono::system_clock::now() - updater->setting_time).count()) >> 20};
        double const process{duration * 1e-3};
        if (process < 1.0) {
            updater->x = updater->lparam_map[::LparamUsage::LU_SETX].d + process * updater->lparam_map[::LparamUsage::LU_DX].d;
            updater->y = updater->lparam_map[::LparamUsage::LU_SETY].d + process * updater->lparam_map[::LparamUsage::LU_DY].d;
        } else {
            updater->x = updater->lparam_map[::LparamUsage::LU_SETX].d + updater->lparam_map[::LparamUsage::LU_DX].d;
            updater->y = updater->lparam_map[::LparamUsage::LU_SETY].d + updater->lparam_map[::LparamUsage::LU_DY].d;
            updater->update_func = &::FuncSource::General::null_updater;
        }
    }
    void updater_ssiaygoo_0(void *param, ::Lparam lparam) {
        ::RotatedQuadDisplayer *updater{reinterpret_cast<::RotatedQuadDisplayer *>(param)};
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(lparam.p)};
        ::MirroredQuadDisplayer *boss{reinterpret_cast<::MirroredQuadDisplayer *>(updater->lparam_map[::LparamUsage::LU_TARGET].p)};
        if (activity->updater_status[boss]) {
            const unsigned int duration{(unsigned int)((::std::chrono::system_clock::now() - updater->setting_time).count()) >> 20};
            double const process{duration * 4e-3};
            updater->x = boss->x;
            updater->y = boss->y;
// ::std::cout << process << '\n';
            // updater->lparam_map[::LparamUsage::LU_PHI].d = M_PI_2 + M_PI * ::sin(process * 0.25) * 0.0625;
            updater->lparam_map[::LparamUsage::LU_THETA].d = process;
        } else {
            updater->lparam_map[::LparamUsage::LU_EXISTENCE].b = false;
        }
    }
    void eventer_diqdann_0(void *param, ::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        ::MirroredQuadDisplayer *boss{reinterpret_cast<::MirroredQuadDisplayer *>(lparam_map->at(::LparamUsage::LU_TARGET).p)};
        if (activity->updater_status[boss]) {
            double const set_x{lparam_map->at(::LparamUsage::LU_CHOICE).ull & 0x1 ? 128.0 : 384.0};
            unsigned int tex_id;
            switch (lparam_map->at(::LparamUsage::LU_CHOICE).ull % 3) {
                case 0ULL: {
                    tex_id = ::TexSource::tex_ids["ball_lightning_red"];
                    break;
                }
                case 1ULL: {
                    tex_id = ::TexSource::tex_ids["ball_lightning_green"];
                    break;
                }
                case 2ULL: {
                    tex_id = ::TexSource::tex_ids["ball_lightning_blue"];
                    break;
                }
            }
            for (double theta{::rand() * M_PI_4 / RAND_MAX}; theta < M_PI * 2; theta += M_PI * 0.0625) {
                ::RotatedQuadDisplayer *diqdann{new ::RotatedQuadDisplayer(&::FuncSource::Diqczi_3::updater_diqdann_0, tex_id, set_x, 512.0, 8.0, 8.0, M_PI_2, theta)};
                diqdann->lparam_map[::LparamUsage::LU_DX].d = -::sin(theta);
                diqdann->lparam_map[::LparamUsage::LU_DY].d = ::cos(theta);
                activity->diqdann_list.emplace_back(diqdann);
            }
        }
    }
    void updater_diqdann_0(void *param, ::Lparam lparam) {
        ::RotatedQuadDisplayer *updater{reinterpret_cast<::RotatedQuadDisplayer *>(param)};
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(lparam.p)};
        const unsigned int duration{activity->timer.duration_from_latest};
        double const process{duration * 256e-3};
        updater->x += process * updater->lparam_map[::LparamUsage::LU_DX].d;
        updater->y += process * updater->lparam_map[::LparamUsage::LU_DY].d;
    }
    void eventer_cziguang_1(void *param, ::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        ::LineDisplayer *cziguang{new ::LineDisplayer(&::FuncSource::Diqczi_3::updater_cziguang_1, ::TexSource::tex_ids["laser_blue"], 256.0, 512.0, 0.0, lparam_map->at(::LparamUsage::LU_CHOICE).b ? M_PI * 0.625 : M_PI * 1.375)};
        ::QuadDisplayer *ssiaygoo{new ::QuadDisplayer(&::FuncSource::General::null_updater, ::TexSource::tex_ids["dahzziuh_blue"], cziguang->x, cziguang->y, 32.0, 32.0)};
        cziguang->lparam_map[::LparamUsage::LU_TARGET].p = lparam_map->at(::LparamUsage::LU_TARGET).p;
        cziguang->lparam_map[::LparamUsage::LU_APPENDAGE].p = ssiaygoo;
        cziguang->lparam_map[::LparamUsage::LU_EXISTENCE].b = true;
        activity->cziguang_list.emplace_back(cziguang);
        ssiaygoo->lparam_map[::LparamUsage::LU_EXISTENCE].b = true;
        activity->ssiaygoo_list.emplace_back(ssiaygoo);
    }
    void updater_cziguang_1(void *param, ::Lparam lparam) {
        ::LineDisplayer *updater{reinterpret_cast<::LineDisplayer *>(param)};
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(lparam.p)};
        const unsigned int duration{(unsigned int)((::std::chrono::system_clock::now() - updater->setting_time).count()) >> 20};
        bool existence{activity->updater_status[reinterpret_cast<::Updater *>(updater->lparam_map[::LparamUsage::LU_TARGET].p)]};
        if (duration < 1e3) {
            double const process{duration * 1e-3};
            updater->half_width = process * 16.0;
        } else if (duration < 2e3) { } else if (duration < 4e3) {
            double const process{duration * 0.5e-3 - 1};
// ::std::cout << process << '\n';
            if (updater->rotation < M_PI) {
                updater->rotation = M_PI * (0.625 + process * 0.3125);
            } else {
                updater->rotation = M_PI * (1.375 - process * 0.3125);
            }
        } else {
            existence = false;
        }
        if (!existence) {
            updater->lparam_map[::LparamUsage::LU_EXISTENCE].b = false;
            reinterpret_cast<::QuadDisplayer *>(updater->lparam_map[::LparamUsage::LU_APPENDAGE].p)->lparam_map[::LparamUsage::LU_EXISTENCE].b = false;
        }
    }
}

// TEST
namespace FuncSource::Diqczi_Test {
    void eventer_init(void *param, ::std::unordered_map<::LparamUsage, ::Lparam> *) {
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        ::QuadDisplayer *diqczi{new ::QuadDisplayer(&::FuncSource::General::null_updater, ::TexSource::tex_ids["druangczea_niqluh"], 256.0, 512.0, 64.0, 64.0)};
        diqczi->lparam_map[::LparamUsage::LU_HEAL].ll = 256LL;
        activity->diqczi_list.emplace_back(diqczi);
        activity->updater_status[diqczi] = true;
        for (unsigned long long i{0ULL}; i < 65536ULL; i += 64ULL) {
            ::TimedEvent event(activity->timer.duration_from_base + i, &::FuncSource::Diqczi_Test::eventer_diqdann);
            event.lparam_map[::LparamUsage::LU_TARGET].p = diqczi;
            activity->timer.prepare(event);
        }
    }
    void eventer_diqdann(void *param, ::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        ::QuadDisplayer *diqczi{reinterpret_cast<::QuadDisplayer *>(lparam_map->at(::LparamUsage::LU_TARGET).p)};
        if (activity->updater_status[diqczi]) {
            activity->diqdann_list.emplace_back(new ::QuadDisplayer(&::FuncSource::Diqczi_Test::updater_diqdann, ::TexSource::tex_ids["dahzziuh_green"], diqczi->x, diqczi->y, 16.0, 16.0));
        }
    }
    void updater_diqdann(void *param, ::Lparam lparam) {
        ::QuadDisplayer *updater{reinterpret_cast<::QuadDisplayer *>(param)};
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(lparam.p)};
        const unsigned int duration{activity->timer.duration_from_latest};
        double const process{duration * 256e-3};
        updater->y -= process;
    }
}

namespace FuncSource::Diqczi_Test_1 {
    void eventer_init(void *param, ::std::unordered_map<::LparamUsage, ::Lparam> *) {
        ::GameActivity *activity{reinterpret_cast<::GameActivity *>(param)};
        ::LineDisplayer *cziguang{new ::LineDisplayer(&::FuncSource::General::null_updater, ::TexSource::tex_ids["laser_blue"], 256.0, 512.0, 8.0, M_PI * 0.75)};
        cziguang->lparam_map[::LparamUsage::LU_EXISTENCE].b = true;
        activity->cziguang_list.emplace_back(cziguang);
    }
}

#endif
