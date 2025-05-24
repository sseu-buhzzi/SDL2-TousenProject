#ifndef FUNC_DEFINATION_DATA_HPP
#define FUNC_DEFINATION_DATA_HPP

#include "./FuncSource.hpp"

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
	double cubic_smooth(double x, double deriv_0) {
		return x * (x * (x * (deriv_0 * 2 - 2) - deriv_0 * 3 + 3) + deriv_0);
	}
	void null_updater(void *) { }
	template<typename T> void eventer_set_something(::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
		*static_cast<T *>(lparam_map->at(::LparamUsage::LU_TARGET).p) = static_cast<T>(lparam_map->at(::LparamUsage::LU_APPENDAGE).ull);
	}
}

// 標題畫面
namespace FuncSource::MainActivity {
	void updater_smooth(void *param) {
		::QuadDisplayer *updater{static_cast<::QuadDisplayer *>(param)};
		::MainActivity *activity(::Sseu::top_activity<::MainActivity>());
		const unsigned int duration{activity->timer.duration_from_base - updater->setting_duration};
		if (duration < 1024) {
			const double process{1 - (duration * 1e-3 - 1) * (duration * 1e-3 - 1)};
			updater->x = updater->lparam_map[::LparamUsage::LU_SETX].d + process * updater->lparam_map[::LparamUsage::LU_DX].d;
			updater->y = updater->lparam_map[::LparamUsage::LU_SETY].d + process * updater->lparam_map[::LparamUsage::LU_DY].d;
		} else {
			activity->has_animation_completed = true;
			updater->x = updater->lparam_map[::LparamUsage::LU_SETX].d + updater->lparam_map[::LparamUsage::LU_DX].d;
			updater->y = updater->lparam_map[::LparamUsage::LU_SETY].d + updater->lparam_map[::LparamUsage::LU_DY].d;
			updater->update_func = &::FuncSource::General::null_updater;
		}
	}
	void updater_zzingxua(void *param) {
		::RotatedQuadDisplayer *updater{static_cast<::RotatedQuadDisplayer *>(param)};
		::MainActivity *activity{::Sseu::top_activity<::MainActivity>()};
		const unsigned int duration{activity->timer.duration_from_prev};
		updater->x += updater->lparam_map[::LparamUsage::LU_DX].d * duration;
		updater->y += updater->lparam_map[::LparamUsage::LU_DY].d * duration;
		updater->lparam_map[::LparamUsage::LU_THETA].d -= updater->lparam_map[::LparamUsage::LU_DX].d * duration * 16e-3;
		updater->lparam_map[::LparamUsage::LU_DX].d += duration * 64e-6;
	}
}

// 角色們
namespace FuncSource::Characters {
	void updater_tzuihczi(void *param) {
		::MirroredQuadDisplayer *updater{static_cast<::MirroredQuadDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		::std::vector<::RotatedQuadDisplayer *> *tzoiczi_list{static_cast<::std::vector<::RotatedQuadDisplayer *> *>(updater->lparam_map[::LparamUsage::LU_APPENDAGE].p)};
		const bool is_slow{updater->lparam_map[::LparamUsage::LU_IS_SLOW].b};
		const unsigned int tzoiczi_count{activity->info_displayer.power / 100};
		int *tzoiczi_offset_list{static_cast<int **>(updater->lparam_map[::LparamUsage::LU_LIST].p)[tzoiczi_count]};
		bool should_replace_tzoiczi{false};
		::std::vector<::RotatedQuadDisplayer *> prev_tzoiczi_list;
		double rate{activity->timer.duration_from_prev * 0.25};
		if (is_slow) {
			rate *= 0.5;
			tzoiczi_offset_list += 30;
		}
		updater->x += updater->lparam_map[::LparamUsage::LU_DX].d * rate;
		updater->y += updater->lparam_map[::LparamUsage::LU_DY].d * rate;
		if (updater->x < 0) {
			updater->x = 0;
		}
		if (updater->x > ::Sseu::vp_width) {
			updater->x = ::Sseu::vp_width;
		}
		if (updater->y < 0) {
			updater->y = 0;
		}
		if (updater->y > ::Sseu::vp_height) {
			updater->y = ::Sseu::vp_height;
		}
		activity->tzuihczi_shoot_and_break();
		if (tzoiczi_list->empty()) {
			should_replace_tzoiczi = tzoiczi_count;
		} else if (tzoiczi_count == 0 || tzoiczi_list->front()->lparam_map[::LparamUsage::LU_APPENDAGE].p != tzoiczi_offset_list) {
			prev_tzoiczi_list = ::std::move(*tzoiczi_list);
			should_replace_tzoiczi = true;
		}
		if (should_replace_tzoiczi) {
			for (unsigned int i{0U}; i != tzoiczi_count; ++i) {
				double set_x, set_y;
				if (i < prev_tzoiczi_list.size()) {
					set_x = prev_tzoiczi_list[i]->x;
					set_y = prev_tzoiczi_list[i]->y;
				} else {
					set_x = updater->x;
					set_y = updater->y;
				}
				::RotatedQuadDisplayer *tzoiczi{new ::RotatedQuadDisplayer(activity->timer.duration_from_base, &::FuncSource::Characters::updater_tzoiczi, ::TexSource::tex_ids["vagner"], set_x, set_y, 8.0, 8.0, M_PI_2, 0.0)};
				tzoiczi->lparam_map[::LparamUsage::LU_TARGET].p = updater;
				tzoiczi->lparam_map[::LparamUsage::LU_APPENDAGE].p = tzoiczi_offset_list + i * 2;
				tzoiczi_list->push_back(tzoiczi);
			}
			for (::RotatedQuadDisplayer *tzoiczi : prev_tzoiczi_list) {
				delete tzoiczi;
			}
		}
	}
	void updater_boss(void *param) {
		::MirroredQuadDisplayer *updater{static_cast<::MirroredQuadDisplayer *>(param)};
		updater->y = 128.0;
	}
	void updater_tzuihdann(void *param) {
		::QuadDisplayer *updater{static_cast<::QuadDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		updater->x += activity->timer.duration_from_prev * updater->lparam_map[::LparamUsage::LU_DX].d;
		updater->y += activity->timer.duration_from_prev * updater->lparam_map[::LparamUsage::LU_DY].d;
	}
	void updater_tzoiczi(void *param) {
		::RotatedQuadDisplayer *updater{static_cast<::RotatedQuadDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const unsigned int duration{activity->timer.duration_from_prev};
		double const process{duration * 0.015625};
		::MirroredQuadDisplayer *tzuihczi{static_cast<::MirroredQuadDisplayer *>(updater->lparam_map[::LparamUsage::LU_TARGET].p)};
		int *offset{static_cast<int *>(updater->lparam_map[::LparamUsage::LU_APPENDAGE].p)};
		updater->x += (tzuihczi->x + offset[0] - updater->x) * process;
		updater->y += (tzuihczi->y + offset[1] - updater->y) * process;
		updater->lparam_map[::LparamUsage::LU_THETA].d += process * 0.5;
	}
	void updater_tzoidann(void *param) {
		::RotatedQuadDisplayer *updater{static_cast<::RotatedQuadDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const unsigned int duration{activity->timer.duration_from_prev};
		double *theta{&updater->lparam_map[::LparamUsage::LU_THETA].d};
		::QuadDisplayer *diqczi{static_cast<::QuadDisplayer *>(updater->lparam_map[::LparamUsage::LU_TARGET].p)};
		double const direction{diqczi != nullptr && activity->updater_status[diqczi] ? ::atan2(diqczi->x - updater->x, diqczi->y - updater->y) : -*theta};
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
	void updater_tzuihczi_recover(void *param) {
		::MirroredQuadDisplayer *updater{static_cast<::MirroredQuadDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const unsigned int duration{activity->timer.duration_from_prev};
		double const process{duration * 64e-3};
		updater->y += process;
		if (updater->y >= 64.0) {
			updater->y = 64.0;
			updater->update_func = &::FuncSource::Characters::updater_tzuihczi;
		}
		// if (updater->lparam_map[::LparamUsage::LU_IS_SHOOTING].b && !updater->lparam_map[::LparamUsage::LU_IS_IN_SHOOTING_BREAK].b) {
		//     updater->lparam_map[::LparamUsage::LU_IS_IN_SHOOTING_BREAK].b = true;
		//     ::std::thread([updater]() -> void {
		//         ::std::this_thread::sleep_for(::std::chrono::milliseconds(64));
		//         updater->lparam_map[::LparamUsage::LU_IS_IN_SHOOTING_BREAK].b = false;
		//     }).detach();
		//     activity->tzuihczi_shoot();
		// }
		activity->tzuihczi_shoot_and_break();
	}
	void eventer_tzuihczi_shooting_break_recover(::std::unordered_map<::LparamUsage, ::Lparam> *) {
		::Sseu::top_activity<::GameActivity>()->tzuihczi.lparam_map[::LparamUsage::LU_IS_IN_SHOOTING_BREAK].b = false;
	}
	void eventer_tzuihczi_injury_free_quit(::std::unordered_map<::LparamUsage, ::Lparam> *) {
		::Sseu::top_activity<::GameActivity>()->tzuihczi.lparam_map[::LparamUsage::LU_IS_INJURY_FREE].b = false;
	}
}

// 小東西
namespace FuncSource::Stuffs {
	void updater_daycziuh_explode(void *param) {
		::QuadDisplayer *updater{static_cast<::QuadDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const unsigned int duration{activity->timer.duration_from_base - updater->setting_duration};
		double const process{1 - ::pow(duration * 1e-3 - 1, 2.0)};
		if (duration < 1e3) {
			updater->x = updater->lparam_map[::LparamUsage::LU_SETX].d + process * updater->lparam_map[::LparamUsage::LU_DX].d;
			updater->y = updater->lparam_map[::LparamUsage::LU_SETY].d + process * updater->lparam_map[::LparamUsage::LU_DY].d;
		} else {
			updater->update_func = &::FuncSource::Stuffs::updater_daycziuh_fall;
		}
	}
	void updater_daycziuh_fall(void *param) {
		// ::QuadDisplayer *updater{static_cast<::QuadDisplayer *>(param)};
		// ::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		// updater->y -= activity->timer.duration_from_prev * 128e-3;
		// 這種寫法能接受嗎
		static_cast<::QuadDisplayer *>(param)->y -= ::Sseu::top_activity<::GameActivity>()->timer.duration_from_prev * 128e-3;
	}
	void updater_daycziuh_catch(void *param) {
		::QuadDisplayer *updater{static_cast<::QuadDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const double theta{::atan2(activity->tzuihczi.y - updater->y, activity->tzuihczi.x - updater->x)};
		updater->x += activity->timer.duration_from_prev * ::cos(theta);
		updater->y += activity->timer.duration_from_prev * ::sin(theta);
	}
	void updater_ssiaygoo_graze(void *param) {
		::QuadDisplayer *updater{static_cast<::QuadDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const unsigned int duration{activity->timer.duration_from_base - updater->setting_duration};
		double const process{1 - ::pow(duration * 1e-3 - 1, 2.0)};
		if (duration < 1024) {
			updater->x = updater->lparam_map[::LparamUsage::LU_SETX].d + process * updater->lparam_map[::LparamUsage::LU_DX].d;
			updater->y = updater->lparam_map[::LparamUsage::LU_SETY].d + process * updater->lparam_map[::LparamUsage::LU_DY].d;
			updater->half_width = updater->half_height = (1 - process) * 8;
		} else {
			updater->lparam_map[::LparamUsage::LU_EXISTENCE].b = false;
			updater->update_func = &::FuncSource::General::null_updater;
		}
	}
	// 爲啥叫recover？
	void eventer_cziguang_recover(::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
		::RectDisplayer *updater{static_cast<::RectDisplayer *>(lparam_map->at(::LparamUsage::LU_TARGET).p)};
		updater->lparam_map[::LparamUsage::LU_IS_GRAZED].b = false;
	}
	void eventer_bomb(::std::unordered_map<::LparamUsage, ::Lparam> *) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		for (unsigned int i{0U}; i != 8; ++i) {
			activity->timer.prepare(::TimedEvent(activity->timer.duration_from_base + ::rand() % 1024, &::FuncSource::Stuffs::eventer_bomb_single));
		}
		activity->tzuihczi.lparam_map[::LparamUsage::LU_IS_INJURY_FREE].b = true;
		activity->timer.prepare(::TimedEvent(activity->timer.duration_from_base + 8192, &::FuncSource::Characters::eventer_tzuihczi_injury_free_quit));
		// ::TimedEvent event(activity->timer.duration_from_base, &::FuncSource::Stuffs::eventer_bomb_single);
		// // event.lparam_map[::LparamUsage]
		// activity->timer.prepare(event);
	}
	void eventer_bomb_single(::std::unordered_map<::LparamUsage, ::Lparam> *) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		::QuadDisplayer *ssiaygoo{new ::QuadDisplayer(activity->timer.duration_from_base, &::FuncSource::Stuffs::updater_bomb, ::TexSource::tex_ids["bubble"], activity->tzuihczi.x, activity->tzuihczi.y, 32.0, 32.0)};
		const double theta{::rand() * M_PI * 2 / RAND_MAX};
		ssiaygoo->lparam_map[::LparamUsage::LU_DX].d = ::cos(theta) * 64;
		ssiaygoo->lparam_map[::LparamUsage::LU_DY].d = ::sin(theta) * 64;
		ssiaygoo->lparam_map[::LparamUsage::LU_TARGET].p = activity->diqczi_list.empty() ? nullptr : activity->diqczi_list[::rand() % activity->diqczi_list.size()];
		ssiaygoo->lparam_map[::LparamUsage::LU_EXISTENCE].b = true;
		activity->ssiaygoo_list.push_back(ssiaygoo);
	}
	void updater_bomb(void *param) {
		::QuadDisplayer *updater{static_cast<::QuadDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		::QuadDisplayer *diqczi{static_cast<::QuadDisplayer *>(updater->lparam_map[::LparamUsage::LU_TARGET].p)};
		double target_x, target_y;
		if (diqczi == nullptr) {
			target_x = updater->x;
			target_y = 1024;
		} else {
			target_x = diqczi->x;
			target_y = diqczi->y;
		}
		const unsigned int duration{activity->timer.duration_from_prev};
		const double theta{::atan2(target_y - updater->y, target_x - updater->x)};
		double *dx{&updater->lparam_map[::LparamUsage::LU_DX].d};
		double *dy{&updater->lparam_map[::LparamUsage::LU_DY].d};
		*dx += ::cos(theta) * duration * 0.125;
		*dy += ::sin(theta) * duration * 0.125;
		updater->x += *dx * duration * 0.015625;
		updater->y += *dy * duration * 0.015625;
		updater->half_width = updater->half_height = ::FuncSource::General::calc_norm(*dx, *dy);
		if (activity->timer.duration_from_base > updater->setting_duration + 4096 || ::FuncSource::General::calc_norm(target_x - updater->x, target_y - updater->y) < 128) {
			updater->lparam_map[::LparamUsage::LU_EXISTENCE].b = false;
		}
	}
}

// 第一波敵機(diqczi_0)
namespace FuncSource::Gungczi_0 {
	void eventer_init(::std::unordered_map<::LparamUsage, ::Lparam> *) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		for (unsigned int i{0U}; i < 10U; ++i) {
			::TimedEvent event(activity->timer.duration_from_base + ::rand() % 4096, &::FuncSource::Gungczi_0::eventer_diqczi);
			event.lparam_map[::LparamUsage::LU_CHOICE].ull = i;
			activity->timer.prepare(event);
		}
		activity->event_updater = new ::Updater(activity->timer.duration_from_base, &::FuncSource::Gungczi_0::updater_init);
		activity->updater_status[activity->event_updater] = true;
	}
	void updater_init(void *param) {
		::Updater *updater{static_cast<::Updater *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		if (activity->updater_status[updater]) {
			const unsigned int duration{activity->timer.duration_from_base - updater->setting_duration};
			if (duration >= 1024 && activity->diqczi_list.empty()) {
				activity->updater_status[updater] = false;
				delete updater;
				activity->event_updater = nullptr;
				::TimedEvent event(4096, &::FuncSource::Gungczi_1::eventer_init);
				event.lparam_map[::LparamUsage::LU_CHOICE].ull = 0ULL;
				activity->timer.prepare(event);
			}
		}
	}
	void eventer_diqczi(::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		::QuadDisplayer *diqczi{new ::QuadDisplayer(activity->timer.duration_from_base, &::FuncSource::Gungczi_0::updater_diqczi, ::TexSource::tex_ids["stepan_bandera"], 0.0, 0.0, 16.0, 16.0)};
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
		for (unsigned int i{256U}; i < 16384; i += 4096) {
			::TimedEvent event(activity->timer.duration_from_base + i, &::FuncSource::Gungczi_0::eventer_diqdann);
			event.lparam_map[::LparamUsage::LU_TARGET].p = diqczi;
			for (unsigned int j{0U}; j < 8; ++j) {
				event.duration += 128;
				activity->timer.prepare(event);
			}
		}
		::TimedEvent event(activity->timer.duration_from_base + 16384, &::FuncSource::Gungczi_0::eventer_quit);
		event.lparam_map[::LparamUsage::LU_TARGET].p = diqczi;
		activity->timer.prepare(event);
	}
	void updater_diqczi(void *param) {
		::QuadDisplayer *updater{static_cast<::QuadDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const unsigned int duration{activity->timer.duration_from_base - updater->setting_duration};
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
	void eventer_diqdann(::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		::QuadDisplayer *diqczi{static_cast<::QuadDisplayer *>(lparam_map->at(::LparamUsage::LU_TARGET).p)};
		if (activity->updater_status[diqczi]) {
			double const theta{::atan2(activity->tzuihczi.y - diqczi->y, activity->tzuihczi.x - diqczi->x)};
			::QuadDisplayer *diqdann{new ::QuadDisplayer(activity->timer.duration_from_base, &::FuncSource::Gungczi_0::updater_diqdann, ::TexSource::tex_ids["dahzziuh_blue"], diqczi->x, diqczi->y, 16.0, 16.0)};
			diqdann->lparam_map[::LparamUsage::LU_SETX].d = diqdann->x;
			diqdann->lparam_map[::LparamUsage::LU_SETY].d = diqdann->y;
			diqdann->lparam_map[::LparamUsage::LU_DX].d = ::cos(theta);
			diqdann->lparam_map[::LparamUsage::LU_DY].d = ::sin(theta);
			activity->diqdann_list.emplace_back(diqdann);
			activity->updater_status[diqdann] = true;
		}
	}
	void updater_diqdann(void *param) {
		::QuadDisplayer *updater{static_cast<::QuadDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const unsigned int duration{activity->timer.duration_from_base - updater->setting_duration};
		double const process{duration * 512e-3};
		updater->x = updater->lparam_map[::LparamUsage::LU_SETX].d + process * updater->lparam_map[::LparamUsage::LU_DX].d;
		updater->y = updater->lparam_map[::LparamUsage::LU_SETY].d + process * updater->lparam_map[::LparamUsage::LU_DY].d;
	}
	void eventer_quit(::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		::QuadDisplayer *diqczi{static_cast<::QuadDisplayer *>(lparam_map->at(::LparamUsage::LU_TARGET).p)};
		if (activity->updater_status[diqczi]) {
			diqczi->lparam_map[::LparamUsage::LU_SETX].d = diqczi->x;
			diqczi->lparam_map[::LparamUsage::LU_SETY].d = diqczi->y;
			diqczi->lparam_map[::LparamUsage::LU_DX].d = 0.0;
			diqczi->lparam_map[::LparamUsage::LU_DY].d = 512.0;
			diqczi->setting_duration = activity->timer.duration_from_base;
			diqczi->update_func = &::FuncSource::Gungczi_0::updater_diqczi;
		}
	}
}

// 第二波敵機(diqczi_1)
namespace FuncSource::Gungczi_1 {
	void eventer_init(::std::unordered_map<::LparamUsage, ::Lparam> *) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		::TimedEvent event(activity->timer.duration_from_base, &::FuncSource::Gungczi_1::eventer_diqczi);
		event.lparam_map[::LparamUsage::LU_CHOICE].ull = 0ULL;
		activity->timer.prepare(event);
		event.duration += 4096;
		++event.lparam_map[::LparamUsage::LU_CHOICE].ull;
		activity->timer.prepare(event);
		++event.lparam_map[::LparamUsage::LU_CHOICE].ull;
		activity->timer.prepare(event);
		event.duration += 4096;
		event.lparam_map[::LparamUsage::LU_CHOICE].ull = 0ULL;
		activity->timer.prepare(event);
		event.duration += 4096;
		++event.lparam_map[::LparamUsage::LU_CHOICE].ull;
		activity->timer.prepare(event);
		++event.lparam_map[::LparamUsage::LU_CHOICE].ull;
		activity->timer.prepare(event);
		event = ::TimedEvent(::TimedEvent(activity->timer.duration_from_base + 16384, &::FuncSource::Gungczi_2::eventer_init));
		activity->timer.prepare(event);
	}
	void eventer_diqczi(::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		::QuadDisplayer *diqczi{new ::QuadDisplayer(activity->timer.duration_from_base, &::FuncSource::Gungczi_1::updater_diqczi, ::TexSource::tex_ids["stepan_bandera"], 0.0, 0.0, 24.0, 24.0)};
		diqczi->lparam_map[::LparamUsage::LU_HEAL].ll = 128LL;
		switch (lparam_map->at(::LparamUsage::LU_CHOICE).ull) {
			case 0ULL: {
				diqczi->lparam_map[::LparamUsage::LU_SETX].d = diqczi->x = 256.0;
				diqczi->lparam_map[::LparamUsage::LU_SETY].d = diqczi->y = 640.0;
				diqczi->lparam_map[::LparamUsage::LU_DX].d = 0.0;
				diqczi->lparam_map[::LparamUsage::LU_DY].d = -1024.0;
				break;
			}
			case 1ULL: {
				diqczi->lparam_map[::LparamUsage::LU_SETX].d = diqczi->x = 64.0;
				diqczi->lparam_map[::LparamUsage::LU_SETY].d = diqczi->y = 640.0;
				diqczi->lparam_map[::LparamUsage::LU_DX].d = 0.0;
				diqczi->lparam_map[::LparamUsage::LU_DY].d = -1024.0;
				break;
			}
			case 2ULL: {
				diqczi->lparam_map[::LparamUsage::LU_SETX].d = diqczi->x = 448.0;
				diqczi->lparam_map[::LparamUsage::LU_SETY].d = diqczi->y = 640.0;
				diqczi->lparam_map[::LparamUsage::LU_DX].d = 0.0;
				diqczi->lparam_map[::LparamUsage::LU_DY].d = -1024.0;
				break;
			}
		}
		activity->diqczi_list.emplace_back(diqczi);
		activity->updater_status[diqczi] = true;
		for (unsigned int i{0U}; i < 16384U; i += 2048U) {
			::TimedEvent event(activity->timer.duration_from_base + i, &::FuncSource::Gungczi_1::eventer_diqdann);
			event.lparam_map[::LparamUsage::LU_TARGET].p = diqczi;
			activity->timer.prepare(event);
			event.duration += 128;
			activity->timer.prepare(event);
			event.duration += 128;
			activity->timer.prepare(event);
		}
	}
	void updater_diqczi(void *param) {
		::QuadDisplayer *updater{static_cast<::QuadDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const unsigned int duration{activity->timer.duration_from_base - updater->setting_duration};
		double const process{duration * 0.125e-3};
		if (process < 1.0) {
			updater->x = updater->lparam_map[::LparamUsage::LU_SETX].d + process * updater->lparam_map[::LparamUsage::LU_DX].d;
			updater->y = updater->lparam_map[::LparamUsage::LU_SETY].d + process * updater->lparam_map[::LparamUsage::LU_DY].d;
		} else {
			updater->update_func = &::FuncSource::General::null_updater;
		}
	}
	void eventer_diqdann(::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		::QuadDisplayer *diqczi{static_cast<::QuadDisplayer *>(lparam_map->at(::LparamUsage::LU_TARGET).p)};
		const unsigned int tex_ids[6]{::TexSource::tex_ids["diamond_bullet_red"], ::TexSource::tex_ids["diamond_bullet_yellow"], ::TexSource::tex_ids["diamond_bullet_green"], ::TexSource::tex_ids["diamond_bullet_cyan"], ::TexSource::tex_ids["diamond_bullet_blue"], ::TexSource::tex_ids["diamond_bullet_purple"]};
		const unsigned int *tex_id{tex_ids};
		if (activity->updater_status[diqczi]) {
			double const theta{::atan2(activity->tzuihczi.y - diqczi->y, activity->tzuihczi.x - diqczi->x) - M_PI_2};
			for (double offset_theta{0.0}; offset_theta < M_PI * 2; offset_theta += M_PI * 0.0625) {
				::RotatedQuadDisplayer *diqdann{new ::RotatedQuadDisplayer(activity->timer.duration_from_base, &::FuncSource::Gungczi_1::updater_diqdann, *tex_id, diqczi->x, diqczi->y, 8.0, 8.0, M_PI_2, theta + offset_theta)};
				activity->diqdann_list.emplace_back(diqdann);
				activity->updater_status[diqdann] = true;
				if (++tex_id >= tex_ids + 6) {
					tex_id = tex_ids;
				}
			}
		}
	}
	void updater_diqdann(void *param) {
		::RotatedQuadDisplayer *updater{static_cast<::RotatedQuadDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const unsigned int duration{activity->timer.duration_from_prev};
		double const process{duration * 128e-3};
		double const theta{updater->lparam_map[::LparamUsage::LU_THETA].d};
		updater->x -= ::sin(theta) * process;
		updater->y += ::cos(theta) * process;
	}
}

// 第三波敵機(diqczi_2)
namespace FuncSource::Gungczi_2 {
	void eventer_init(::std::unordered_map<::LparamUsage, ::Lparam> *) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		::QuadDisplayer *diqczi{new ::QuadDisplayer(activity->timer.duration_from_base, &::FuncSource::Gungczi_2::updater_diqczi, ::TexSource::tex_ids["stepan_bandera"], 256.0, 640.0, 32.0, 32.0)};
		diqczi->lparam_map[::LparamUsage::LU_HEAL].ll = 256LL;
		activity->diqczi_list.emplace_back(diqczi);
		activity->updater_status[diqczi] = true;
		for (unsigned int i{0U}; i < 4096; i += 256) {
			::TimedEvent event(activity->timer.duration_from_base + i, &::FuncSource::Gungczi_2::eventer_diqdann);
			event.lparam_map[::LparamUsage::LU_TARGET].p = diqczi;
			event.lparam_map[::LparamUsage::LU_THETA].d = i * M_PI_2 / 4096 + M_PI_2;
			activity->timer.prepare(event);
		}
		activity->timer.prepare(::TimedEvent(activity->timer.duration_from_base + 8192, &::FuncSource::Gungczi_230925_0::eventer_init));
	}
	void updater_diqczi(void *param) {
		::QuadDisplayer *updater{static_cast<::QuadDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const unsigned int duration{activity->timer.duration_from_prev};
		double const process{duration * 64e-3};
		updater->y -= process;
	}
	void eventer_diqdann(::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		::QuadDisplayer *diqczi{static_cast<::QuadDisplayer *>(lparam_map->at(::LparamUsage::LU_TARGET).p)};
		for (int distance{64}; activity->updater_status[diqczi] && distance < 512; distance += 16) {
			double theta{lparam_map->at(::LparamUsage::LU_THETA).d};
			::RotatedQuadDisplayer *diqdann{new ::RotatedQuadDisplayer(activity->timer.duration_from_base, &::FuncSource::Gungczi_2::updater_diqdann_0, ::TexSource::tex_ids["dart_bullet_blue"], diqczi->x, diqczi->y, 8.0, 8.0, M_PI_2, theta)};
			diqdann->lparam_map[::LparamUsage::LU_SETX].d = diqdann->x;
			diqdann->lparam_map[::LparamUsage::LU_SETY].d = diqdann->y;
			diqdann->lparam_map[::LparamUsage::LU_DX].d = -::sin(theta) * distance;
			diqdann->lparam_map[::LparamUsage::LU_DY].d = ::cos(theta) * distance;
			activity->diqdann_list.emplace_back(diqdann);
			theta = -theta;
			diqdann = new ::RotatedQuadDisplayer(activity->timer.duration_from_base, &::FuncSource::Gungczi_2::updater_diqdann_0, ::TexSource::tex_ids["dart_bullet_blue"], diqczi->x, diqczi->y, 8.0, 8.0, M_PI_2, theta);
			diqdann->lparam_map[::LparamUsage::LU_SETX].d = diqdann->x;
			diqdann->lparam_map[::LparamUsage::LU_SETY].d = diqdann->y;
			diqdann->lparam_map[::LparamUsage::LU_DX].d = -::sin(theta) * distance;
			diqdann->lparam_map[::LparamUsage::LU_DY].d = ::cos(theta) * distance;
			activity->diqdann_list.emplace_back(diqdann);
		}
	}
	void updater_diqdann_0(void *param) {
		::RotatedQuadDisplayer *updater{static_cast<::RotatedQuadDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const unsigned int duration{activity->timer.duration_from_base - updater->setting_duration};
		double const process{::log(duration * 1e-3 + 1)};
		if (duration < 1e3) {
			updater->x = updater->lparam_map[::LparamUsage::LU_SETX].d + process * updater->lparam_map[::LparamUsage::LU_DX].d;
			updater->y = updater->lparam_map[::LparamUsage::LU_SETY].d + process * updater->lparam_map[::LparamUsage::LU_DY].d;
		} else {
			double const theta{::atan2(activity->tzuihczi.y - updater->y, activity->tzuihczi.x - updater->x)};
			updater->lparam_map[::LparamUsage::LU_THETA].d = theta - M_PI_2;
			updater->lparam_map[::LparamUsage::LU_DX].d = ::cos(theta);
			updater->lparam_map[::LparamUsage::LU_DY].d = ::sin(theta);
			updater->update_func = &::FuncSource::Gungczi_2::updater_diqdann_1;
		}
	}
	void updater_diqdann_1(void *param) {
		::RotatedQuadDisplayer *updater{static_cast<::RotatedQuadDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const unsigned int duration{activity->timer.duration_from_prev};
		double const process{duration * 256e-3};
		updater->x += process * updater->lparam_map[::LparamUsage::LU_DX].d;
		updater->y += process * updater->lparam_map[::LparamUsage::LU_DY].d;
	}
}

// 230925插入的，不描述了
namespace FuncSource::Gungczi_230925_0 {
	void eventer_init(::std::unordered_map<::LparamUsage, ::Lparam> *) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		::TimedEvent event(activity->timer.duration_from_base, &::FuncSource::Gungczi_230925_0::eventer_diqczi);
		event.lparam_map[::LparamUsage::LU_SETX].d = 128.0;
		event.lparam_map[::LparamUsage::LU_SETY].d = 640.0;
		activity->timer.prepare(event);
		event.duration += 4096;
		event.lparam_map[::LparamUsage::LU_SETX].d = 384.0;
		activity->timer.prepare(event);
		event.duration += 4096;
		event.lparam_map[::LparamUsage::LU_SETX].d = 192.0;
		activity->timer.prepare(event);
		event.duration += 4096;
		event.lparam_map[::LparamUsage::LU_SETX].d = 256.0;
		activity->timer.prepare(event);
		event.duration += 4096;
		event.event_func = &::FuncSource::Gungczi_3::eventer_init;
		activity->timer.prepare(event);
	}
	void eventer_diqczi(::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		// 加入敵機
		::QuadDisplayer *diqczi{new ::QuadDisplayer(activity->timer.duration_from_base, ::FuncSource::Gungczi_230925_0::updater_diqczi, ::TexSource::tex_ids["druangczea_niqluh"], lparam_map->at(::LparamUsage::LU_SETX).d, lparam_map->at(::LparamUsage::LU_SETY).d, 16.0, 16.0)};
		diqczi->lparam_map[::LparamUsage::LU_SETX].d = diqczi->x;
		diqczi->lparam_map[::LparamUsage::LU_SETY].d = diqczi->y;
		diqczi->lparam_map[::LparamUsage::LU_DX].d = 0.0;
		diqczi->lparam_map[::LparamUsage::LU_DY].d = -128.0;
		diqczi->lparam_map[::LparamUsage::LU_HEAL].ll = 256LL;
		activity->diqczi_list.push_back(diqczi);
		activity->updater_status[diqczi] = true;
		// 設置敵機射擊的定時事件
		for (unsigned int i{0U}; i < 64; ++i) {
			::TimedEvent event(activity->timer.duration_from_base + i * 64, &::FuncSource::Gungczi_230925_0::eventer_diqdann);
			for (unsigned int j{0U}; j < 16; ++j) {
				event.lparam_map[::LparamUsage::LU_THETA].d = j * M_PI * 0.125;
				event.lparam_map[::LparamUsage::LU_TARGET].p = diqczi;
				activity->timer.prepare(event);
			}
			event.lparam_map.erase(::LparamUsage::LU_THETA);
			event.event_func = &::FuncSource::Gungczi_230925_0::eventer_ssiaygoo;
			activity->timer.prepare(event);
		}
	}
	void updater_diqczi(void *param) {
		::QuadDisplayer *updater{static_cast<::QuadDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const unsigned int duration{activity->timer.duration_from_base - updater->setting_duration};
		if (duration < 500) {
			const double process{::FuncSource::General::cubic_smooth(duration * 1e-3 + 0.5, 0.0) * 2 - 1};
			updater->x = process * updater->lparam_map[::LparamUsage::LU_DX].d + updater->lparam_map[::LparamUsage::LU_SETX].d;
			updater->y = process * updater->lparam_map[::LparamUsage::LU_DY].d + updater->lparam_map[::LparamUsage::LU_SETY].d;
		} else if (duration < 4000) {
			updater->x = updater->lparam_map[::LparamUsage::LU_SETX].d + updater->lparam_map[::LparamUsage::LU_DX].d;
			updater->y = updater->lparam_map[::LparamUsage::LU_SETY].d + updater->lparam_map[::LparamUsage::LU_DY].d;
		} else {
			updater->setting_duration = activity->timer.duration_from_base;
			updater->update_func = &::FuncSource::Gungczi_230925_0::updater_diqczi_quit;
			updater->lparam_map[::LparamUsage::LU_SETX].d += updater->lparam_map[::LparamUsage::LU_DX].d;
			updater->lparam_map[::LparamUsage::LU_SETY].d += updater->lparam_map[::LparamUsage::LU_DY].d;
			updater->lparam_map[::LparamUsage::LU_DX].d = 0.0;
			updater->lparam_map[::LparamUsage::LU_DY].d = 512.0;
		}
	}
	void updater_diqczi_quit(void *param) {
		::QuadDisplayer *updater{static_cast<::QuadDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const unsigned int duration{activity->timer.duration_from_base - updater->setting_duration};
		if (duration < 500) {
			const double process{::FuncSource::General::cubic_smooth(duration * 1e-3, 0.0) * 2};
			updater->x = process * updater->lparam_map[::LparamUsage::LU_DX].d + updater->lparam_map[::LparamUsage::LU_SETX].d;
			updater->y = process * updater->lparam_map[::LparamUsage::LU_DY].d + updater->lparam_map[::LparamUsage::LU_SETY].d;
		} else {
			updater->update_func = &::FuncSource::General::null_updater;
		}
	}
	void eventer_diqdann(::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		::QuadDisplayer *diqczi{static_cast<::QuadDisplayer *>(lparam_map->at(::LparamUsage::LU_TARGET).p)};
		if (activity->updater_status[diqczi]) {
			const double theta{lparam_map->at(::LparamUsage::LU_THETA).d};
			::RotatedQuadDisplayer *diqdann{new ::RotatedQuadDisplayer(activity->timer.duration_from_base, ::FuncSource::Gungczi_230925_0::updater_diqdann, ::TexSource::tex_ids["dart_bullet_blue"], diqczi->x, diqczi->y, 8.0, 8.0, M_PI_2, theta)};
			diqdann->lparam_map[::LparamUsage::LU_DX].d = -::sin(theta);
			diqdann->lparam_map[::LparamUsage::LU_DY].d = ::cos(theta);
			activity->diqdann_list.push_back(diqdann);
		}
	}
	void updater_diqdann(void *param) {
		::RotatedQuadDisplayer *updater{static_cast<::RotatedQuadDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const unsigned int duration{activity->timer.duration_from_prev};
		const double rate{duration * 256e-3};
		updater->x += rate * updater->lparam_map[::LparamUsage::LU_DX].d;
		updater->y += rate * updater->lparam_map[::LparamUsage::LU_DY].d;
	}
	void eventer_ssiaygoo(::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		::QuadDisplayer *diqczi{static_cast<::QuadDisplayer *>(lparam_map->at(::LparamUsage::LU_TARGET).p)};
		if (activity->updater_status[diqczi]) {
			::QuadDisplayer *ssiaygoo{new ::QuadDisplayer(activity->timer.duration_from_base, ::FuncSource::Gungczi_230925_0::updater_ssiaygoo, ::TexSource::tex_ids["bubble"], diqczi->x, diqczi->y, 32.0, 32.0)};
			ssiaygoo->lparam_map[::LparamUsage::LU_EXISTENCE].b = true;
			ssiaygoo->lparam_map[::LparamUsage::LU_DURATION].ull = 64ULL;
			activity->ssiaygoo_list.push_back(ssiaygoo);
		}
	}
	void updater_ssiaygoo(void *param) {
		::QuadDisplayer *updater{static_cast<::QuadDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const unsigned int duration{activity->timer.duration_from_base - updater->setting_duration};
		const unsigned int max_duration(updater->lparam_map[::LparamUsage::LU_DURATION].ull);
		if (duration < max_duration) {
			const double process{1 - ::pow(duration * 2.0 / max_duration - 1, 2)};
			updater->half_width = updater->half_height = process * 32 + 32;
		} else {
			updater->lparam_map[::LparamUsage::LU_EXISTENCE].b = false;
		}
	}
}

// 第四波敵機(boss_3)
namespace FuncSource::Gungczi_3 {
	void eventer_init(::std::unordered_map<::LparamUsage, ::Lparam> *) {
		double const theta{M_PI / 6};
		double const cos_theta{::cos(theta)};
		double const sin_theta{::sin(theta)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		activity->gamearea.alpha = 0x10;
		// 左右移動的字符
		for (int i {-8}; i < 20; ++i) {
			int const text_length{i & 1 ? 128 : 256};
			for (int j{0}; j < 8; ++j) {
				::RotatedQuadDisplayer *ssiaygoo_name{new ::RotatedQuadDisplayer(activity->timer.duration_from_base, &::FuncSource::Gungczi_3::updater_ssiaygoo_name_showup, ::TexSource::tex_ids[i & 1 ? "zelensikij_name" : "slava_ukrajni"], j * cos_theta * text_length - i * sin_theta * 32, i * cos_theta * 32 + j * sin_theta * text_length, 64, 16, M_PI_2, theta)};
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
		::RotatedQuadDisplayer *ssiaygoo_boss{new ::RotatedQuadDisplayer(activity->timer.duration_from_base, &::FuncSource::Gungczi_3::updater_ssiaygoo_boss_showup, ::TexSource::tex_ids["zelensikij"], 512.0, 512.0, 512.0, 512.0, M_PI_2, theta)};
		ssiaygoo_boss->lparam_map[::LparamUsage::LU_SETX].d = ssiaygoo_boss->x;
		ssiaygoo_boss->lparam_map[::LparamUsage::LU_SETY].d = ssiaygoo_boss->y;
		ssiaygoo_boss->lparam_map[::LparamUsage::LU_DX].d = -cos_theta * 512;
		ssiaygoo_boss->lparam_map[::LparamUsage::LU_DY].d = -sin_theta * 512;
		ssiaygoo_boss->lparam_map[::LparamUsage::LU_EXISTENCE].b = true;
		activity->ssiaygoo_list.emplace_back(ssiaygoo_boss);
		// 游戲畫面中的boss
		activity->boss = new ::MirroredQuadDisplayer(activity->timer.duration_from_base, &::FuncSource::Gungczi_3::updater_boss, ::TexSource::tex_ids["zelensikij"], 256.0, 768.0, 128.0, 128.0, false, false);
		activity->boss->lparam_map[::LparamUsage::LU_SETX].d = activity->boss->x;
		activity->boss->lparam_map[::LparamUsage::LU_SETY].d = activity->boss->y;
		activity->boss->lparam_map[::LparamUsage::LU_DX].d = 0.0;
		activity->boss->lparam_map[::LparamUsage::LU_DY].d = -256.0;
		activity->boss->lparam_map[::LparamUsage::LU_HEAL].ll = 4096LL;
		activity->diqczi_list.emplace_back(activity->boss);
		activity->updater_status[activity->boss] = true;
		// 血條
		::QuadDisplayer *ssiaygoo_heal{new ::QuadDisplayer(activity->timer.duration_from_base, &::FuncSource::Gungczi_3::updater_ssiaygoo_heal, ::TexSource::tex_ids["heal_bar"], 256.0, 636.0, 256.0, 4.0)};\
		ssiaygoo_heal->lparam_map[::LparamUsage::LU_EXISTENCE].b = true;
		activity->ssiaygoo_list.push_back(ssiaygoo_heal);
		// boss背後的六芒星
		::RotatedQuadDisplayer *ssiaygoo_hexagram{new ::RotatedQuadDisplayer(activity->timer.duration_from_base, &::FuncSource::Gungczi_3::updater_ssiaygoo_0, ::TexSource::tex_ids["hexagram_blue"], 256.0, 768.0, 128.0, 128.0, M_PI_2, 0.0)};
		ssiaygoo_hexagram->lparam_map[::LparamUsage::LU_EXISTENCE].b = true;
		activity->back_ssiaygoo_list.emplace_back(ssiaygoo_hexagram);
		for (unsigned int i{4U}; i < 56; ++i) {
			::TimedEvent event(activity->timer.duration_from_base + i * 512, &::FuncSource::Gungczi_3::eventer_diqdann_0);
			event.lparam_map[::LparamUsage::LU_CHOICE].ull = i;
			activity->timer.prepare(event);
		}
		::TimedEvent event(activity->timer.duration_from_base + 4096, &::FuncSource::Gungczi_3::eventer_cziguang_1);
		event.lparam_map[::LparamUsage::LU_CHOICE].b = false;
		activity->timer.prepare(event);
		event.duration += 8192;
		activity->timer.prepare(event);
		event.duration += 8192;
		activity->timer.prepare(event);
		event.duration = activity->timer.duration_from_base + 4096;
		event.lparam_map[::LparamUsage::LU_CHOICE].b = true;
		activity->timer.prepare(event);
		event.duration += 8192;
		activity->timer.prepare(event);
		event.duration += 8192;
		activity->timer.prepare(event);
		// 下一波攻擊
		event.duration += 8192;
		// event.duration = activity->timer.duration_from_base; // 取消延時，立即進入第五波攻擊
		event.event_func = &::FuncSource::Gungczi_4::eventer_init;
		activity->timer.prepare(event);
	}
	void updater_ssiaygoo_boss_showup(void *param) {
		::RotatedQuadDisplayer *updater{static_cast<::RotatedQuadDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const unsigned int duration{activity->timer.duration_from_base - updater->setting_duration};
		double const process{duration * 1e-3 * (duration * 1e-3 * (duration * 2e-3 - 3) + 2)};
		updater->x = updater->lparam_map[::LparamUsage::LU_SETX].d + process * updater->lparam_map[::LparamUsage::LU_DX].d;
		updater->y = updater->lparam_map[::LparamUsage::LU_SETY].d + process * updater->lparam_map[::LparamUsage::LU_DY].d;
	}
	void updater_ssiaygoo_name_showup(void *param) {
		::RotatedQuadDisplayer *updater{static_cast<::RotatedQuadDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		if (activity->timer.duration_from_base < updater->setting_duration + 1024) {
			const unsigned int duration{activity->timer.duration_from_prev};
			double const process{duration * 256e-3};
			updater->x += process * updater->lparam_map[::LparamUsage::LU_DX].d;
			updater->y += process * updater->lparam_map[::LparamUsage::LU_DY].d;
		} else {
			updater->lparam_map[::LparamUsage::LU_EXISTENCE].b = false;
		}
	}
	void updater_boss(void *param) {
		::MirroredQuadDisplayer *updater{static_cast<::MirroredQuadDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const unsigned int duration{activity->timer.duration_from_base - updater->setting_duration};
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
	void updater_ssiaygoo_0(void *param) {
		::RotatedQuadDisplayer *updater{static_cast<::RotatedQuadDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		if (activity->updater_status[activity->boss]) {
			const unsigned int duration{activity->timer.duration_from_base - updater->setting_duration};
			double const process{duration * 4e-3};
			updater->x = activity->boss->x;
			updater->y = activity->boss->y;
			updater->lparam_map[::LparamUsage::LU_THETA].d = process;
		} else {
			updater->lparam_map[::LparamUsage::LU_EXISTENCE].b = false;
		}
	}
	void eventer_diqdann_0(::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		if (activity->updater_status[activity->boss]) {
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
				::RotatedQuadDisplayer *diqdann{new ::RotatedQuadDisplayer(activity->timer.duration_from_base, &::FuncSource::Gungczi_3::updater_diqdann_0, tex_id, set_x, 512.0, 8.0, 8.0, M_PI_2, theta)};
				diqdann->lparam_map[::LparamUsage::LU_DX].d = -::sin(theta);
				diqdann->lparam_map[::LparamUsage::LU_DY].d = ::cos(theta);
				activity->diqdann_list.emplace_back(diqdann);
			}
		}
	}
	void updater_diqdann_0(void *param) {
		::RotatedQuadDisplayer *updater{static_cast<::RotatedQuadDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const unsigned int duration{activity->timer.duration_from_prev};
		double const process{duration * 256e-3};
		updater->x += process * updater->lparam_map[::LparamUsage::LU_DX].d;
		updater->y += process * updater->lparam_map[::LparamUsage::LU_DY].d;
	}
	void eventer_cziguang_1(::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		::RectDisplayer *cziguang{new ::RectDisplayer(activity->timer.duration_from_base, &::FuncSource::Gungczi_3::updater_cziguang_1, ::TexSource::tex_ids["laser_blue"], 256.0, 512.0, 0.0, 1024.0, lparam_map->at(::LparamUsage::LU_CHOICE).b ? M_PI * 0.625 : M_PI * 1.375)};
		::QuadDisplayer *ssiaygoo{new ::QuadDisplayer(activity->timer.duration_from_base, &::FuncSource::General::null_updater, ::TexSource::tex_ids["dahzziuh_blue"], cziguang->x, cziguang->y, 32.0, 32.0)};
		cziguang->lparam_map[::LparamUsage::LU_APPENDAGE].p = ssiaygoo;
		cziguang->lparam_map[::LparamUsage::LU_EXISTENCE].b = true;
		activity->cziguang_list.emplace_back(cziguang);
		ssiaygoo->lparam_map[::LparamUsage::LU_EXISTENCE].b = true;
		activity->ssiaygoo_list.emplace_back(ssiaygoo);
	}
	void updater_cziguang_1(void *param) {
		::RectDisplayer *updater{static_cast<::RectDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const unsigned int duration{activity->timer.duration_from_base - updater->setting_duration};
		bool existence{activity->updater_status[activity->boss]};
		if (duration < 1e3) {
			double const process{duration * 1e-3};
			updater->half_width = process * 16.0;
		} else if (duration < 2e3) { } else if (duration < 4e3) {
			double const process{duration * 0.5e-3 - 1};
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
			static_cast<::QuadDisplayer *>(updater->lparam_map[::LparamUsage::LU_APPENDAGE].p)->lparam_map[::LparamUsage::LU_EXISTENCE].b = false;
		}
	}
	void updater_ssiaygoo_heal(void *param) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		if (activity->updater_status[activity->boss]) {
			::QuadDisplayer *updater{static_cast<::QuadDisplayer *>(param)};
			updater->x = updater->half_width = activity->boss->lparam_map[::LparamUsage::LU_HEAL].ll / 16.0;
		}
	}
}

// 第五波敵機(diqczi_4)
namespace FuncSource::Gungczi_4 {
	void eventer_init(::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		// 四散的彈幕
		for (unsigned int i{0U}; i < 8; ++i) {
			::TimedEvent event(activity->timer.duration_from_base + i * 4096, &::FuncSource::Gungczi_4::eventer_diqdann);
			event.lparam_map[::LparamUsage::LU_IS_HMIRRORED].b = i & 0x1;
			activity->timer.prepare(event);
		}
		// 網格狀激光
		::TimedEvent event(activity->timer.duration_from_base + 8192, &::FuncSource::Gungczi_4::eventer_cziguang_wave);
		event.lparam_map[::LparamUsage::LU_SETX].d = 0.0;
		event.lparam_map[::LparamUsage::LU_SETY].d = 640.0;
		event.lparam_map[::LparamUsage::LU_DX].d = 64.0;
		event.lparam_map[::LparamUsage::LU_DY].d = -64.0;
		activity->timer.prepare(event);
		event.duration += 8192;
		event.lparam_map[::LparamUsage::LU_SETX].d = 512.0;
		event.lparam_map[::LparamUsage::LU_DX].d = -64.0;
		activity->timer.prepare(event);
		event.duration += 8192;
		event.lparam_map[::LparamUsage::LU_SETY].d = 0.0;
		event.lparam_map[::LparamUsage::LU_DY].d = 64.0;
		activity->timer.prepare(event);
		event.duration += 8192;
		event.lparam_map[::LparamUsage::LU_SETX].d = 0.0;
		event.lparam_map[::LparamUsage::LU_DX].d = 64.0;
		activity->timer.prepare(event);
		// 下一波攻擊
		event.duration += 8192;
		event.event_func = &::FuncSource::Gungczi_230926_0::eventer_init;
		event.lparam_map.clear();
		activity->timer.prepare(event);
	}
	void eventer_diqdann(::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const bool is_hmirrored{lparam_map->at(::LparamUsage::LU_IS_HMIRRORED).b};
		for (unsigned int i{0U}; i < 8; ++i) {
			::TimedEvent event(activity->timer.duration_from_base + i * 64, &::FuncSource::Gungczi_4::eventer_diqdann_circle);
			event.lparam_map[::LparamUsage::LU_DX].d = (i + 1) << 5;
			event.lparam_map[::LparamUsage::LU_IS_HMIRRORED].b = is_hmirrored;
			activity->timer.prepare(event);
		}
	}
	void eventer_diqdann_circle(::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		if (activity->updater_status[activity->boss]) {
			const double tzuihczi_theta{::atan2(activity->tzuihczi.y - activity->boss->y, activity->tzuihczi.x - activity->boss->x)};
			const double focal_dist{lparam_map->at(::LparamUsage::LU_DX).d};
			const bool is_hmirrored{lparam_map->at(::LparamUsage::LU_IS_HMIRRORED).b};
			const unsigned int tex_id{::TexSource::tex_ids[is_hmirrored ? "diamond_bullet_blue" : "diamond_bullet_red"]};
			for (double theta{0.0}; theta < M_PI * 2; theta += M_PI * 0.125) {
				const double set_theta{theta + tzuihczi_theta - focal_dist * M_PI / 1024};
				const double x{focal_dist * ::cos(set_theta) + activity->boss->x};
				const double y{focal_dist * ::sin(set_theta) + activity->boss->y};
				::RotatedQuadDisplayer *diqdann{new ::RotatedQuadDisplayer(activity->timer.duration_from_base, &::FuncSource::Gungczi_4::updater_diqdann, tex_id, x, y, 8.0, 8.0, M_PI_2, set_theta - M_PI_2)};
				diqdann->lparam_map[::LparamUsage::LU_DISTANCE].d = focal_dist;
				diqdann->lparam_map[::LparamUsage::LU_DTHETA].d = set_theta;
				diqdann->lparam_map[::LparamUsage::LU_IS_HMIRRORED].b = is_hmirrored;
				activity->diqdann_list.push_back(diqdann);
				::QuadDisplayer *ssiaygoo{new ::QuadDisplayer(activity->timer.duration_from_base, &::FuncSource::Gungczi_4::updater_ssiaygoo, ::TexSource::tex_ids["bubble"], x, y, 8.0, 8.0)};
				ssiaygoo->lparam_map[::LparamUsage::LU_EXISTENCE].b = true;
				ssiaygoo->lparam_map[::LparamUsage::LU_DURATION].ull = 512ULL;
				ssiaygoo->lparam_map[::LparamUsage::LU_TARGET].p = diqdann;
				activity->ssiaygoo_list.push_back(ssiaygoo);
			}
		}
	}
	void updater_diqdann(void *param) {
		::RotatedQuadDisplayer *updater{static_cast<::RotatedQuadDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const unsigned int duration{activity->timer.duration_from_base - updater->setting_duration};
		const double f{updater->lparam_map[::LparamUsage::LU_DISTANCE].d};
		const double rate{f * 0.25 + 16};
		double theta{(1 - rate / (duration * 8e-3 + rate)) * M_PI * 2};
		const double tan_theta{::tan(theta)};
		const double delta{f * ::sqrt(tan_theta * tan_theta + 1)};
		const double x_squre{::pow((theta < M_PI_2 ? delta : -delta) - f * tan_theta, 2.0)};
		const double f_squre{f * f};
		const double rho{::sqrt(x_squre * (x_squre * 0.5 / f_squre + 1) * 0.5 + f_squre * 0.25)};
		if (rho < 1024) {
			theta += updater->lparam_map[::LparamUsage::LU_DTHETA].d;
			updater->x = rho * ::cos(theta) + 256.0;
			updater->y = rho * ::sin(theta) + 512.0;
			updater->lparam_map[::LparamUsage::LU_THETA].d = theta - M_PI_4;
			if (updater->lparam_map[::LparamUsage::LU_IS_HMIRRORED].b) {
				updater->x = 512 - updater->x;
				updater->lparam_map[::LparamUsage::LU_THETA].d = -updater->lparam_map[::LparamUsage::LU_THETA].d;
			}
		}
	}
	void eventer_cziguang_wave(::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		if (activity->updater_status[activity->boss]) {
			const double set_x{lparam_map->at(::LparamUsage::LU_SETX).d};
			const double set_y{lparam_map->at(::LparamUsage::LU_SETY).d};
			const double dx{lparam_map->at(::LparamUsage::LU_DX).d};
			const double dy{lparam_map->at(::LparamUsage::LU_DY).d};
			for (unsigned int i{0U}; i != 9; ++i) {
				::TimedEvent event(activity->timer.duration_from_base + (i << 8), &::FuncSource::Gungczi_4::eventer_cziguang);
				event.lparam_map[::LparamUsage::LU_SETX].d = i * dx + set_x;
				event.lparam_map[::LparamUsage::LU_SETY].d = set_y;
				event.lparam_map[::LparamUsage::LU_THETA].d = ::atan2(dy, 0.0) - M_PI_2;
				activity->timer.prepare(event);
			}
			for (unsigned int i{0U}; i != 11; ++i) {
				::TimedEvent event(activity->timer.duration_from_base + (i << 8), &::FuncSource::Gungczi_4::eventer_cziguang);
				event.lparam_map[::LparamUsage::LU_SETX].d = set_x;
				event.lparam_map[::LparamUsage::LU_SETY].d = i * dy + set_y;
				event.lparam_map[::LparamUsage::LU_THETA].d = ::atan2(0.0, dx) - M_PI_2;
				activity->timer.prepare(event);
			}
		}
	}
	void eventer_cziguang(::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const double theta{lparam_map->at(::LparamUsage::LU_THETA).d};
		::RectDisplayer *cziguang{new ::RectDisplayer(activity->timer.duration_from_base, &::FuncSource::Gungczi_4::updater_cziguang, ::TexSource::tex_ids["laser_spark_purple"], lparam_map->at(::LparamUsage::LU_SETX).d + ::sin(theta) * 256, lparam_map->at(::LparamUsage::LU_SETY).d - ::cos(theta) * 256, 8.0, 256.0, theta)};
		cziguang->lparam_map[::LparamUsage::LU_EXISTENCE].b = true;
		activity->cziguang_list.push_back(cziguang);
	}
	void updater_cziguang(void *param) {
		::RectDisplayer *updater{static_cast<::RectDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const unsigned int duration{activity->timer.duration_from_prev};
		const double rate{duration * 256e-3};
		updater->x -= rate * ::sin(updater->rotation);
		updater->y += rate * ::cos(updater->rotation);
	}
	void updater_ssiaygoo(void *param) {
		::QuadDisplayer *updater{static_cast<::QuadDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const unsigned int duration{activity->timer.duration_from_base - updater->setting_duration};
		const unsigned int max_duration(updater->lparam_map[::LparamUsage::LU_DURATION].ull);
		if (duration < max_duration) {
			::RotatedQuadDisplayer *diqdann{static_cast<::RotatedQuadDisplayer *>(updater->lparam_map[::LparamUsage::LU_TARGET].p)};
			const double process{1 - ::pow(duration * 2.0 / max_duration - 1, 2)};
			updater->x = diqdann->x;
			updater->y = diqdann->y;
			updater->half_width = updater->half_height = process * 16;
		} else {
			updater->lparam_map[::LparamUsage::LU_EXISTENCE].b = false;
		}
	}
}

namespace FuncSource::Gungczi_230926_0 {
	void eventer_init(::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		::TimedEvent event(activity->timer.duration_from_base, &::FuncSource::Gungczi_230926_0::eventer_diqdann_root);
		activity->timer.prepare(event);
		event.duration += 2048;
		activity->timer.prepare(event);
		event.duration += 4096;
		activity->timer.prepare(event);
		event.duration += 2048;
		activity->timer.prepare(event);
		event.duration += 4096;
		activity->timer.prepare(event);
		event.duration += 1024;
		activity->timer.prepare(event);
		event.duration += 1024;
		activity->timer.prepare(event);
		event.duration += 4096;
		event.event_func = &::FuncSource::Gungczi_230927_0::eventer_init;
		activity->timer.prepare(event);
	}
	void eventer_diqdann_root(::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		for (unsigned i{0U}; i < 8; ++i) {
			const double theta{(i + 0.5) * M_PI_4};
			::RectDisplayer *diqdann_root{new ::RectDisplayer(activity->timer.duration_from_base, &::FuncSource::Gungczi_230926_0::updater_diqdann_root, ::TexSource::tex_ids["dahzziuh_red"], activity->boss->x, activity->boss->y, 8.0, 16.0, theta)};
			diqdann_root->lparam_map[::LparamUsage::LU_SETX].d = diqdann_root->x;
			diqdann_root->lparam_map[::LparamUsage::LU_SETY].d = diqdann_root->y;
			diqdann_root->lparam_map[::LparamUsage::LU_DX].d = -::sin(theta) * 128;
			diqdann_root->lparam_map[::LparamUsage::LU_DY].d = ::cos(theta) * 128;
			diqdann_root->lparam_map[::LparamUsage::LU_EXISTENCE].b = true;
			activity->cziguang_list.push_back(diqdann_root);
		}
	}
	void eventer_diqdann_cluster(::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		::RectDisplayer *diqdann_root{static_cast<::RectDisplayer *>(lparam_map->at(::LparamUsage::LU_TARGET).p)};
		const double tzuihczi_theta{lparam_map->at(::LparamUsage::LU_THETA).d};
		const double distance{lparam_map->at(::LparamUsage::LU_DISTANCE).d};
		const double rate{1 - distance * 1e-3};
		const unsigned int tex_id(lparam_map->at(::LparamUsage::LU_CHOICE).ull);
		for (unsigned i{0U}; i < 32; ++i) {
			const double theta{i * M_PI_2 * 0.125 + tzuihczi_theta};
			const double cos_theta{::cos(theta)};
			const double sin_theta{::sin(theta)};
			::RotatedQuadDisplayer *diqdann_cluster{new ::RotatedQuadDisplayer(activity->timer.duration_from_base, &::FuncSource::Gungczi_230926_0::updater_diqdann_cluster, tex_id, diqdann_root->x - distance * sin_theta, diqdann_root->y + distance * cos_theta, 8.0, 8.0, M_PI_2, theta)};
			diqdann_cluster->lparam_map[::LparamUsage::LU_DX].d = -rate * sin_theta;
			diqdann_cluster->lparam_map[::LparamUsage::LU_DY].d = rate * cos_theta;
			activity->diqdann_list.push_back(diqdann_cluster);
		}
	}
	void updater_diqdann_root(void *param) {
		::RectDisplayer *updater{static_cast<::RectDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const unsigned int duration{activity->timer.duration_from_base - updater->setting_duration};
		if (duration < 1e3) {
			const double process{::FuncSource::General::cubic_smooth(duration * 500e-6 + 0.5, 0) * 2 - 1};
			updater->x = process * updater->lparam_map[::LparamUsage::LU_DX].d + updater->lparam_map[::LparamUsage::LU_SETX].d;
			updater->y = process * updater->lparam_map[::LparamUsage::LU_DY].d + updater->lparam_map[::LparamUsage::LU_SETY].d;
		} else {
			const unsigned int tex_ids[6]{::TexSource::tex_ids["diamond_bullet_red"], ::TexSource::tex_ids["diamond_bullet_yellow"], ::TexSource::tex_ids["diamond_bullet_green"], ::TexSource::tex_ids["diamond_bullet_cyan"], ::TexSource::tex_ids["diamond_bullet_blue"], ::TexSource::tex_ids["diamond_bullet_purple"]};
			updater->lparam_map[::LparamUsage::LU_EXISTENCE].b = false;
			for (unsigned i{0U}; i < 6; ++i) {
				::TimedEvent event(activity->timer.duration_from_base + (i << 7), &::FuncSource::Gungczi_230926_0::eventer_diqdann_cluster);
				event.lparam_map[::LparamUsage::LU_THETA].d = ::atan2(activity->tzuihczi.y - updater->y, activity->tzuihczi.x - updater->x);
				event.lparam_map[::LparamUsage::LU_DISTANCE].d = (i + 4) << 4;
				event.lparam_map[::LparamUsage::LU_TARGET].p = updater;
				event.lparam_map[::LparamUsage::LU_CHOICE].ull = tex_ids[i];
				activity->timer.prepare(event);
			}
		}
	}
	void updater_diqdann_cluster(void *param) {
		::RotatedQuadDisplayer *updater{static_cast<::RotatedQuadDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const unsigned int duration{activity->timer.duration_from_prev};
		const double rate{duration * 256e-3};
		updater->x += rate * updater->lparam_map[::LparamUsage::LU_DX].d;
		updater->y += rate * updater->lparam_map[::LparamUsage::LU_DY].d;
	}
}

namespace FuncSource::Gungczi_230927_0 {
	void eventer_init(::std::unordered_map<::LparamUsage, ::Lparam> *) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		if (activity->updater_status[activity->boss]) {
			// activity->boss->setting_duration = activity->timer.duration_from_base;
			// activity->boss->update_func = &::FuncSource::Gungczi_3::updater_boss;
			// activity->boss->lparam_map[::LparamUsage::LU_SETX].d = activity->boss->x;
			// activity->boss->lparam_map[::LparamUsage::LU_SETY].d = activity->boss->y;
			// activity->boss->lparam_map[::LparamUsage::LU_DX].d = 0.0;
			// activity->boss->lparam_map[::LparamUsage::LU_DY].d = -128.0;
			::TimedEvent event(activity->timer.duration_from_base + 2048, &::FuncSource::Gungczi_230927_0::eventer_diqdann_cluster);
			event.lparam_map[::LparamUsage::LU_IS_HMIRRORED].b = false;
			activity->timer.prepare(event);
			for (unsigned int i{0U}; i < 256; ++i) {
				event.duration += 8192;
				event.lparam_map[::LparamUsage::LU_IS_HMIRRORED].b = true;
				activity->timer.prepare(event);
				event.duration += 8192;
				event.lparam_map[::LparamUsage::LU_IS_HMIRRORED].b = false;
				activity->timer.prepare(event);
			}
			activity->event_updater = new ::Updater(activity->timer.duration_from_base, &::FuncSource::Gungczi_230927_0::updater_gamearea_alpha);
			activity->updater_status[activity->event_updater] = true;
		}
	}
	void eventer_diqdann_cluster(::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
// ::std::cout << __LINE__ << '\t' << '\n';
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		if (activity->updater_status[activity->boss]) {
			const bool is_hmirrored{lparam_map->at(::LparamUsage::LU_IS_HMIRRORED).b};
			const unsigned int tex_ids[4]{::TexSource::tex_ids["diamond_bullet_red"], ::TexSource::tex_ids["diamond_bullet_green"], ::TexSource::tex_ids["diamond_bullet_blue"], ::TexSource::tex_ids["diamond_bullet_yellow"]};
			for (unsigned int i{0U}; i < 16; ++i) {
				const double rho{i * 16.0};
				const double theta{i * M_PI * 0.125};
				::TimedEvent event(activity->timer.duration_from_base + (i << 7), &::FuncSource::Gungczi_230927_0::eventer_diqdann);
				if (is_hmirrored) {
					event.lparam_map[::LparamUsage::LU_SETX].d = activity->boss->x + rho * ::cos(theta);
				} else {
					event.lparam_map[::LparamUsage::LU_SETX].d = activity->boss->x - rho * ::cos(theta);
				}
				event.lparam_map[::LparamUsage::LU_SETY].d = activity->boss->y + rho * ::sin(theta);
				event.lparam_map[::LparamUsage::LU_CHOICE].ull = tex_ids[i & 0x3];
				activity->timer.prepare(event);
			}
		}
	}
	void eventer_diqdann(::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const unsigned int tex_id(lparam_map->at(::LparamUsage::LU_CHOICE).ull);
		const double set_x{lparam_map->at(::LparamUsage::LU_SETX).d};
		const double set_y{lparam_map->at(::LparamUsage::LU_SETY).d};
		for (unsigned int i{0U}; i < 32; ++i) {
			const double theta{i * M_PI * 0.0625};
			::RotatedQuadDisplayer *diqdann{new ::RotatedQuadDisplayer(activity->timer.duration_from_base, &::FuncSource::Gungczi_230927_0::updater_diqdann, tex_id, set_x, set_y, 8.0, 8.0, M_PI_2, theta)};
			diqdann->lparam_map[::LparamUsage::LU_DX].d = -::sin(theta);
			diqdann->lparam_map[::LparamUsage::LU_DY].d = ::cos(theta);
			activity->diqdann_list.push_back(diqdann);
		}
	}
	void updater_diqdann(void *param) {
		::RotatedQuadDisplayer *updater{static_cast<::RotatedQuadDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const double rate{activity->timer.duration_from_prev * 64e-3};
		updater->x += rate * updater->lparam_map[::LparamUsage::LU_DX].d;
		updater->y += rate * updater->lparam_map[::LparamUsage::LU_DY].d;
	}
	void updater_gamearea_alpha(void *param) {
		::Updater *updater{static_cast<::Updater *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const unsigned int duration{activity->timer.duration_from_base - updater->setting_duration};
		if (duration < 1000) {
			const double process{duration * 1e-3};
			activity->gamearea.alpha = process * 112 + 16;
		} else {
			delete activity->event_updater;
			activity->updater_status[activity->event_updater] = false;
			activity->event_updater = nullptr;
		}
	}
}

// TEST
namespace FuncSource::Gungczi_Test {
	void eventer_init(::std::unordered_map<::LparamUsage, ::Lparam> *) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		::QuadDisplayer *diqczi{new ::QuadDisplayer(activity->timer.duration_from_base, &::FuncSource::General::null_updater, ::TexSource::tex_ids["kung"], 256.0, 512.0, 64.0, 64.0)};
		diqczi->lparam_map[::LparamUsage::LU_HEAL].ll = 256LL;
		activity->diqczi_list.emplace_back(diqczi);
		activity->updater_status[diqczi] = true;
		for (unsigned long long i{0ULL}; i < 65536ULL; i += 64ULL) {
			::TimedEvent event(activity->timer.duration_from_base + i, &::FuncSource::Gungczi_Test::eventer_diqdann);
			event.lparam_map[::LparamUsage::LU_TARGET].p = diqczi;
			activity->timer.prepare(event);
		}
	}
	void eventer_diqdann(::std::unordered_map<::LparamUsage, ::Lparam> *lparam_map) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		::QuadDisplayer *diqczi{static_cast<::QuadDisplayer *>(lparam_map->at(::LparamUsage::LU_TARGET).p)};
		if (activity->updater_status[diqczi]) {
			activity->diqdann_list.emplace_back(new ::QuadDisplayer(activity->timer.duration_from_base, &::FuncSource::Gungczi_Test::updater_diqdann, ::TexSource::tex_ids["dahzziuh_green"], diqczi->x, diqczi->y, 16.0, 16.0));
		}
	}
	void updater_diqdann(void *param) {
		::QuadDisplayer *updater{static_cast<::QuadDisplayer *>(param)};
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		const unsigned int duration{activity->timer.duration_from_prev};
		double const process{duration * 256e-3};
		updater->y -= process;
	}
}

namespace FuncSource::Gungczi_Test_1 {
	void eventer_init(::std::unordered_map<::LparamUsage, ::Lparam> *) {
		::GameActivity *activity{::Sseu::top_activity<::GameActivity>()};
		::RectDisplayer *cziguang{new ::RectDisplayer(activity->timer.duration_from_base, &::FuncSource::General::null_updater, ::TexSource::tex_ids["laser_spark_blue"], 256.0, 384.0, 8.0, 256.0, 0.25)};
		cziguang->lparam_map[::LparamUsage::LU_EXISTENCE].b = true;
		activity->cziguang_list.emplace_back(cziguang);
	}
}

#endif
