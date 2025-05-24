#ifndef FUNC_SOURCE_HPP
#define FUNC_SOURCE_HPP

#include "./headers.hpp"

namespace FuncSource::General {
    inline double calc_norm(double, double);
    inline double calc_signed_angle(double);
    inline double calc_unsigned_angle(double);
    inline double cubic_smooth(double, double);
    inline void null_updater(void *);
    template<typename T> inline void eventer_set_something(::std::unordered_map<::LparamUsage, ::Lparam> *);
}

namespace FuncSource::Characters {
    inline void updater_tzuihczi(void *);
    inline void updater_boss(void *);
    inline void updater_tzuihdann(void *);
    inline void updater_tzoiczi(void *);
    inline void updater_tzoidann(void *);
    inline void updater_tzuihczi_recover(void *);
    inline void eventer_tzuihczi_shooting_break_recover(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void eventer_tzuihczi_injury_free_quit(::std::unordered_map<::LparamUsage, ::Lparam> *);
}

namespace FuncSource::MainActivity {
    inline void updater_smooth(void *);
    inline void updater_zzingxua(void *);
}

namespace FuncSource::Stuffs {
    inline void updater_daycziuh_explode(void *);
    inline void updater_daycziuh_fall(void *);
    inline void updater_daycziuh_catch(void *);
    inline void updater_ssiaygoo_graze(void *);
    inline void eventer_cziguang_recover(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void eventer_bomb(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void eventer_bomb_single(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void updater_bomb(void *);
}

namespace FuncSource::Gungczi_0 {
    inline void eventer_init(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void updater_init(void *);
    inline void eventer_diqczi(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void updater_diqczi(void *);
    inline void eventer_diqdann(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void updater_diqdann(void *);
    inline void eventer_quit(::std::unordered_map<::LparamUsage, ::Lparam> *);
}

namespace FuncSource::Gungczi_1 {
    inline void eventer_init(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void eventer_diqczi(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void updater_diqczi(void *);
    inline void eventer_diqdann(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void updater_diqdann(void *);
}

namespace FuncSource::Gungczi_2 {
    inline void eventer_init(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void updater_diqczi(void *);
    inline void eventer_diqdann(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void updater_diqdann_0(void *);
    inline void updater_diqdann_1(void *);
}

namespace FuncSource::Gungczi_230925_0 {
    inline void eventer_init(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void eventer_diqczi(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void updater_diqczi(void *);
    inline void updater_diqczi_quit(void *);
    inline void eventer_diqdann(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void updater_diqdann(void *);
    inline void eventer_ssiaygoo(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void updater_ssiaygoo(void *);
}

namespace FuncSource::Gungczi_3 {
    inline void eventer_init(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void updater_ssiaygoo_boss_showup(void *);
    inline void updater_ssiaygoo_name_showup(void *);
    inline void updater_boss(void *);
    inline void updater_ssiaygoo_0(void *);
    inline void eventer_diqdann_0(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void updater_diqdann_0(void *);
    inline void eventer_cziguang_1(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void updater_cziguang_1(void *);
    inline void updater_ssiaygoo_heal(void *);
}

namespace FuncSource::Gungczi_4 {
    inline void eventer_init(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void eventer_diqdann(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void eventer_diqdann_circle(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void updater_diqdann(void *);
    inline void eventer_cziguang_wave(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void eventer_cziguang(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void updater_cziguang(void *);
    inline void updater_ssiaygoo(void *);
}

namespace FuncSource::Gungczi_230926_0 {
    // 建立六個母彈，設定延時事件，發出多叢，多層，多個子彈
    // 隨便幾個吧，不一定是六個
    inline void eventer_init(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void eventer_diqdann_root(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void eventer_diqdann_cluster(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void updater_diqdann_root(void *);
    inline void updater_diqdann_cluster(void *);
}

namespace FuncSource::Gungczi_230927_0 {
    inline void eventer_init(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void eventer_diqdann_cluster(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void eventer_diqdann(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void updater_diqdann(void *);
    inline void updater_gamearea_alpha(void *);
}

namespace FuncSource::Gungczi_Test {
    inline void eventer_init(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void eventer_diqdann(::std::unordered_map<::LparamUsage, ::Lparam> *);
    inline void updater_diqdann(void *);
}

namespace FuncSource::Gungczi_Test_1 {
    inline void eventer_init(::std::unordered_map<::LparamUsage, ::Lparam> *);
}

#endif
