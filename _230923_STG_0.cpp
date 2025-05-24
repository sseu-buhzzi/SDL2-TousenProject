// compile command:
// D:\Sseu\Tryingssiuh\MinGW\mingw64\bin\g++.exe -Ofast -o D:\Sseu\Tryingssiuh\Ssianxmuh\_230515_STGs\_230824_STG\_230824_STG.exe D:\Sseu\Tryingssiuh\Ssianxmuh\_230515_STGs\_230824_STG\_230824_STG.cpp -LD:\Sseu\Tryingssiuh\Ssianxmuh\_230515_STGs\_230824_STG\lib -lfreeglut -lglu32 -lopengl32 -lSDL2; D:\Sseu\Tryingssiuh\Ssianxmuh\_230515_STGs\_230824_STG\_230824_STG

#ifndef STG_CPP

#include ".\FuncSource.hpp"

Updater::Updater(void (*update_func)(void *, ::Lparam)): setting_time{::std::chrono::system_clock::now()}, update_func{update_func} { }
void Updater::update(::Lparam lparam) {
// ::std::cout << __LINE__ << '\t' << this << '\t' << reinterpret_cast<::RotatedQuadDisplayer *>(this)->tzuihczi << '\n';
    (*this->update_func)(this, lparam);
}

QuadDisplayer::QuadDisplayer(void (*update_func)(void *, ::Lparam), unsigned int tex_id, double x, double y, double half_width, double half_height): ::Updater::Updater(update_func), tex_id{tex_id}, x{x}, y{y}, half_width{half_width}, half_height{half_height} { }
void QuadDisplayer::display() {
    ::glPushMatrix();
    ::glTranslated(this->x, this->y, 0.0);
    ::glBindTexture(GL_TEXTURE_2D, this->tex_id);
    ::glBegin(GL_QUADS);
    ::glTexCoord2i(0, 1);
    ::glVertex2d(-this->half_width, -this->half_height);
    ::glTexCoord2i(0, 0);
    ::glVertex2d(-this->half_width, this->half_height);
    ::glTexCoord2i(1, 0);
    ::glVertex2d(this->half_width, this->half_height);
    ::glTexCoord2i(1, 1);
    ::glVertex2d(this->half_width, -this->half_height);
    ::glEnd();
    ::glPopMatrix();
}

MirroredQuadDisplayer::MirroredQuadDisplayer(void (*update_func)(void *, ::Lparam), unsigned int tex_id, double x, double y, double half_width, double half_height, bool is_hmirrored, bool is_vmirrored): ::QuadDisplayer::QuadDisplayer(update_func, tex_id, x, y, half_width, half_height) {
    this->lparam_map[::LparamUsage::LU_IS_HMIRRORED].b = is_hmirrored;
    this->lparam_map[::LparamUsage::LU_IS_VMIRRORED].b = is_vmirrored;
}
void MirroredQuadDisplayer::display() {
    ::glPushMatrix();
    ::glTranslated(this->x, this->y, 0.0);
    ::glBindTexture(GL_TEXTURE_2D, this->tex_id);
    ::glBegin(GL_QUADS);
    switch (this->lparam_map[::LparamUsage::LU_IS_HMIRRORED].b << 1 | this->lparam_map[::LparamUsage::LU_IS_VMIRRORED].b) {
        case 0: {
            ::glTexCoord2i(0, 1);
            ::glVertex2d(-this->half_width, -this->half_height);
            ::glTexCoord2i(0, 0);
            ::glVertex2d(-this->half_width, this->half_height);
            ::glTexCoord2i(1, 0);
            ::glVertex2d(this->half_width, this->half_height);
            ::glTexCoord2i(1, 1);
            ::glVertex2d(this->half_width, -this->half_height);
            break;
        }
        case 1: {
            ::glTexCoord2i(0, 0);
            ::glVertex2d(-this->half_width, -this->half_height);
            ::glTexCoord2i(0, 1);
            ::glVertex2d(-this->half_width, this->half_height);
            ::glTexCoord2i(1, 1);
            ::glVertex2d(this->half_width, this->half_height);
            ::glTexCoord2i(1, 0);
            ::glVertex2d(this->half_width, -this->half_height);
            break;
        }
        case 2: {
            ::glTexCoord2i(1, 1);
            ::glVertex2d(-this->half_width, -this->half_height);
            ::glTexCoord2i(1, 0);
            ::glVertex2d(-this->half_width, this->half_height);
            ::glTexCoord2i(0, 0);
            ::glVertex2d(this->half_width, this->half_height);
            ::glTexCoord2i(0, 1);
            ::glVertex2d(this->half_width, -this->half_height);
            break;
        }
        case 3: {
            ::glTexCoord2i(1, 0);
            ::glVertex2d(-this->half_width, -this->half_height);
            ::glTexCoord2i(1, 1);
            ::glVertex2d(-this->half_width, this->half_height);
            ::glTexCoord2i(0, 1);
            ::glVertex2d(this->half_width, this->half_height);
            ::glTexCoord2i(0, 0);
            ::glVertex2d(this->half_width, -this->half_height);
            break;
        }
    }
    ::glEnd();
    ::glPopMatrix();
}

// OrientedQuadDisplayer::OrientedQuadDisplayer(void (*update_func)(void *, ::Lparam), unsigned int tex_id, double x, double y, double half_width, double half_height, double theta): ::QuadDisplayer::QuadDisplayer(update_func, tex_id, x, y, half_width, half_height), set_x{x}, set_y{y}, dx{::cos(theta)}, dy{::sin(theta)} { }

RotatedQuadDisplayer::RotatedQuadDisplayer(void (*update_func)(void *, ::Lparam), unsigned int tex_id, double x, double y, double half_width, double half_height, double phi, double theta): ::QuadDisplayer::QuadDisplayer(update_func, tex_id, x, y, half_width, half_height) {
    this->lparam_map[::LparamUsage::LU_PHI].d = phi;
    this->lparam_map[::LparamUsage::LU_THETA].d = theta;
    // *reinterpret_cast<double *>(&this->lparam_map[::LparamUsage::LU_PHI]) = phi;
    // *reinterpret_cast<double *>(&this->lparam_map[::LparamUsage::LU_THETA]) = theta;
}
void RotatedQuadDisplayer::display() {
//     if (!this->lparam_list.empty()) {
//         this->phi = this->lparam_list[0];
//         this->theta = this->lparam_list[1];
// // ::std::cout << __LINE__ << '\t' << this->x << '\t' << this->y << '\n';
//     }
    // double const phi{*reinterpret_cast<double *>(this->lparam_list.data())};
    // double const theta{*reinterpret_cast<double *>(this->lparam_list.data() + 1)};
    double const vp_half_height{this->half_height * ::sin(this->lparam_map[::LparamUsage::LU_PHI].d)};
    ::glPushMatrix();
    ::glTranslated(this->x, this->y, 0.0);
    ::glRotated(this->lparam_map[::LparamUsage::LU_THETA].d * M_1_PI * 180, 0.0, 0.0, 1.0);
    // ::glRotated((M_PI_2 - this->lparam_map[::LparamUsage::LU_PHI].d) * M_1_PI * 180, 1.0, 0.0, 0.0);
    ::glBindTexture(GL_TEXTURE_2D, this->tex_id);
    ::glBegin(GL_QUADS);
    ::glTexCoord2i(0, 1);
    ::glVertex2d(-this->half_width, -vp_half_height);
    ::glTexCoord2i(0, 0);
    ::glVertex2d(-this->half_width, vp_half_height);
    ::glTexCoord2i(1, 0);
    ::glVertex2d(this->half_width, vp_half_height);
    ::glTexCoord2i(1, 1);
    ::glVertex2d(this->half_width, -vp_half_height);
    ::glEnd();
    ::glPopMatrix();
}

LineDisplayer::LineDisplayer(void (*update_func)(void *, ::Lparam), unsigned int tex_id, double x, double y, double half_width, double rotation): ::Updater::Updater(update_func), tex_id{tex_id}, x{x}, y{y}, half_width{half_width}, rotation{rotation} { }
void LineDisplayer::display() {
    ::glPushMatrix();
    ::glTranslated(this->x, this->y, 0.0);
    ::glRotated(this->rotation * M_1_PI * 180, 0.0, 0.0, 1.0);
    ::glBindTexture(GL_TEXTURE_2D, this->tex_id);
    ::glBegin(GL_QUADS);
    ::glTexCoord2i(0, 1);
    ::glVertex2d(-this->half_width, 0.0);
    ::glTexCoord2i(0, 0);
    ::glVertex2d(-this->half_width, 65536.0);
    ::glTexCoord2i(1, 0);
    ::glVertex2d(this->half_width, 65536.0);
    ::glTexCoord2i(1, 1);
    ::glVertex2d(this->half_width, 0.0);
    ::glEnd();
    ::glPopMatrix();
}

// TrackingQuadDisplayer::TrackingQuadDisplayer(void (*update_func)(void *, ::Lparam), unsigned int tex_id, double x, double y, double half_width, double half_height, double phi, double theta, ::QuadDisplayer *target_displayer): ::RotatedQuadDisplayer::RotatedQuadDisplayer(update_func, tex_id, x, y, half_width, half_height, phi, theta), target_displayer{target_displayer} { }

SelectionDisplayer::SelectionDisplayer(void (*update_func)(void *, ::Lparam)): ::Updater::Updater(update_func), selected{0U} { }
void SelectionDisplayer::display() {
    ::glPushMatrix();
    ::glTranslated(this->x, this->y - 64, 0.0);
    this->selected == 0U ? ::glColor3ub(0xff, 0xff, 0xff) : ::glColor3ub(0x80, 0x80, 0x80);
    ::Sseu::FontSource::draw_text("START", 16.0);
    ::glTranslatef(0.0F, -64.0F, 0.0F);
    this->selected == 1U ? ::glColor3ub(0xff, 0xff, 0xff) : ::glColor3ub(0x80, 0x80, 0x80);
    ::Sseu::FontSource::draw_text("QUIT", 16.0);
    ::glPopMatrix();
}

GameareaDisplayer::GameareaDisplayer(): process{0.0}, alpha{0x80} { }
void GameareaDisplayer::display() {
    double const offset{this->process - int(this->process / 256) * 256};
    double const rotation{::sin(this->process * 0.015625) * 2.5};
    ::glMatrixMode(GL_PROJECTION);
    ::glLoadIdentity();
    ::glFrustum(-1.0, 1.0, -double(::Sseu::vp_height) / ::Sseu::vp_width, double(::Sseu::vp_height) / ::Sseu::vp_width, 1.0, 1024.0);
    ::glPushMatrix();
    ::glRotatef(rotation, 0.0F, 0.0F, 1.0F);
    ::glTranslatef(0.0, 0.0F, -256.0F);
    ::glRotatef(-75.0F, 1.0F, 0.0F, 0.0F);
    ::glRotatef(15.0F, 0.0F, 0.0F, 1.0F);
    ::glColor3ub(0xff, 0xff, 0xff);
    ::glBindTexture(GL_TEXTURE_2D, ::TexSource::tex_ids["wheat_field"]);
    ::glBegin(GL_QUADS);
    for (int i{-2}; i < 8; ++i) {
        for (int j{-4}; j < 8; ++j) {
            ::glTexCoord2i(0, 1);
            ::glVertex2d(j * 256 - offset, i * 128 - offset);
            ::glTexCoord2i(0, 0);
            ::glVertex2d(j * 256 - offset, (i + 1) * 128 - offset);
            ::glTexCoord2i(1, 0);
            ::glVertex2d((j + 1) * 256 - offset, (i + 1) * 128 - offset);
            ::glTexCoord2i(1, 1);
            ::glVertex2d((j + 1) * 256 - offset, i * 128 - offset);
        }
    }
    ::glEnd();
    ::glPopMatrix();
    ::Sseu::set_base_projection();
    ::glBindTexture(GL_TEXTURE_2D, ::TexSource::tex_ids["blue_sky"]);
    ::glPushMatrix();
    // ::glTranslatef(0.0F, 0.0F, -256.0F);
    ::glRotatef(rotation, 0.0F, 0.0F, 1.0F);
    ::glBegin(GL_QUADS);
    ::glTexCoord2i(0, 1);
    ::glVertex2i(-64, 352);
    ::glTexCoord2i(0, 0);
    ::glVertex2i(-64, 992);
    ::glTexCoord2i(1, 0);
    ::glVertex2i(576, 992);
    ::glTexCoord2i(1, 1);
    ::glVertex2i(576, 352);
    ::glEnd();
    ::glPopMatrix();
    ::glDisable(GL_TEXTURE_2D);
    ::glColor4ub(0x00, 0x00, 0x00, 0xff - this->alpha);
    ::glBegin(GL_QUADS);
    ::glVertex2i(0, 0);
    ::glVertex2i(0, ::Sseu::vp_height);
    ::glVertex2i(::Sseu::vp_width, ::Sseu::vp_height);
    ::glVertex2i(::Sseu::vp_width, 0);
    ::glEnd();
    ::glEnable(GL_TEXTURE_2D);
    ::glColor3ub(0xff, 0xff, 0xff);
}
void GameareaDisplayer::update(double const duration) {
    double const process{duration * 16e-3};
    this->process += process;
}

InfoDisplayer::InfoDisplayer(): hi_score{0U}, score{0U}, player{2U}, power{0U}, graze{0U}, target_score{0U}, target_power{400U} { }
void InfoDisplayer::display() {
    char hi_score_text[11]{}, score_text[11]{};
    this->get_padded_score(this->hi_score, hi_score_text);
    this->get_padded_score(this->score, score_text);
    ::glPushMatrix();
    ::glTranslatef(640.0F, 640.0F, 0.0F);
    // ::glBindTexture(GL_TEXTURE_2D, ::TexSource::tex_ids["logo"]);
    // ::glBegin(GL_QUADS);
    // ::glTexCoord2i(0, 1);
    // ::glVertex2i(0, 0);
    // ::glTexCoord2i(0, 0);
    // ::glVertex2i(0, 64);
    // ::glTexCoord2i(1, 0);
    // ::glVertex2i(64, 64);
    // ::glTexCoord2i(1, 1);
    // ::glVertex2i(64, 0);
    // ::glEnd();
    ::Sseu::FontSource::draw_text("HiScore", 12.0);
    ::glTranslatef(0.0F, -32.0F, 0.0F);
    ::Sseu::FontSource::draw_text("  Score", 12.0);
    ::glTranslatef(0.0F, -64.0F, 0.0F);
    ::Sseu::FontSource::draw_text(" Player", 12.0);
    ::glTranslatef(0.0F, -32.0F, 0.0F);
    ::Sseu::FontSource::draw_text("  Power", 12.0);
    ::glTranslatef(0.0F, -32.0F, 0.0F);
    ::Sseu::FontSource::draw_text("  Graze", 12.0);
    ::glTranslatef(128.0F, 156.0F, 0.0F);
    ::Sseu::FontSource::draw_text(hi_score_text, 16.0);
    ::glTranslatef(0.0F, -32.0F, 0.0F);
    ::Sseu::FontSource::draw_text(score_text, 16.0);
    ::glTranslatef(0.0F, -64.0F, 0.0F);
    ::glBindTexture(GL_TEXTURE_2D, ::TexSource::tex_ids["player_star"]);
    ::glBegin(GL_QUADS);
    for (unsigned int i{0U}; i < this->player; ++i) {
        ::glTexCoord2i(0, 1);
        ::glVertex2i(i * 20, 12);
        ::glTexCoord2i(0, 0);
        ::glVertex2i(i * 20, 28);
        ::glTexCoord2i(1, 0);
        ::glVertex2i(i * 20 + 16, 28);
        ::glTexCoord2i(1, 1);
        ::glVertex2i(i * 20 + 16, 12);
    }
    ::glEnd();
    ::glTranslatef(0.0F, -32.0F, 0.0F);
    ::Sseu::FontSource::draw_text(::std::to_string(this->power / 100).c_str(), 16.0);
    ::glTranslatef(16.0F, 4.0F, 0.0F);
    ::Sseu::FontSource::draw_text(('.' + ::std::to_string(this->power % 100 + 100).substr(1ULL)).c_str(), 8.0);
    ::glTranslatef(24.0F, -4.0F, 0.0F);
    ::Sseu::FontSource::draw_text("/5", 16.0);
    ::glTranslatef(32.0F, 4.0F, 0.0F);
    ::Sseu::FontSource::draw_text(".00", 8.0);
    ::glTranslatef(-72.0F, -36.0F, 0.0F);
    ::Sseu::FontSource::draw_text(::std::to_string(this->graze).c_str(), 16.0);
    ::glPopMatrix();
}
void InfoDisplayer::update() {
    if (::abs(int(this->target_score - this->score)) < 256) {
        this->score = this->target_score;
    } else if (this->score < this->target_score) {
        this->score += 256;
    } else if (this->score > this->target_score) {
        this->score -= 256;
    }
    if (this->score > this->hi_score) {
        this->hi_score = this->score;
    }
    if (::abs(int(this->target_power - this->power)) < 16) {
        this->power = this->target_power;
    } else if (this->power < this->target_power) {
        this->power += 16;
    } else if (this->power > this->target_power) {
        this->power -= 16;
    }
}
void InfoDisplayer::get_padded_score(unsigned long long int score, char text[]) {
    for (char *p{text + 9}; p >= text; --p) {
        *p = '0' + score % 10;
        score /= 10;
    }
}

FpsDisplayer::FpsDisplayer(): frame_count{0U} { }
void FpsDisplayer::display() {
    ++this->frame_count;
    ::glPushMatrix();
    ::glTranslatef(1024 - this->fps_text.length() * 16, 0.0F, 0.0F);
    ::glColor3ub(0xff, 0xff, 0xff);
    ::Sseu::FontSource::draw_text(this->fps_text.c_str(), 16.0);
    ::glPopMatrix();
}
void FpsDisplayer::start_counting() {
    this->is_counting = true;
    this->counting_thr = ::std::thread([this]() -> void {
        while (this->is_counting) {
            ::std::this_thread::sleep_for(::std::chrono::seconds(1));
            this->fps_text = ::std::to_string(this->frame_count) + "fps";
            this->frame_count = 0U;
        }
    });
}
void FpsDisplayer::stop_counting() {
    this->is_counting = false;
    this->counting_thr.join();
}

// ::std::unordered_map<::QuadDisplayer *, bool> DisplayerList::displayer_status;
// void DisplayerList::emplace_displayer(::QuadDisplayer *displayer, ::std::unordered_map<::Updater *, bool> *updater_status) {
//     this->emplace_back(displayer);
//     updater_status->operator [](displayer) = true;
//     // ::DisplayerList::displayer_status[displayer] = true;
// }
// ::std::vector<::QuadDisplayer *>::iterator DisplayerList::erase_displayer(::std::vector<::QuadDisplayer *>::iterator displayer, ::std::unordered_map<::Updater *, bool> *updater_status) {
//     updater_status->operator [](*displayer) = false;
//     // ::DisplayerList::displayer_status[*displayer] = false;
//     return this->erase(displayer);
// }

// unsigned long long int TimedEvent::event_count{0ULL};
TimedEvent::TimedEvent(double time, void (*event_func)(void *, ::std::unordered_map<::LparamUsage, ::Lparam> *)): time{time}, event_func{event_func} { }

Timer::Timer(): should_refresh{false}, base_time(::std::chrono::system_clock::now()), latest_time{::std::chrono::system_clock::now()}, second_latest_time{this->latest_time} { }
double Timer::duration_from_base() {
    return (::std::chrono::system_clock::now() - this->base_time).count() * 1e-6;
}
double Timer::duration_from_latest() {
    return (this->latest_time - this->second_latest_time).count() * 1e-6;
}
void Timer::prepare(::TimedEvent event) {
// ::std::cout << __LINE__ << '\t' << (void *)(event.event_func) << '\n';
// ::std::cin.get();
    this->prepared_event_list.emplace_back(event);
}
void Timer::procedure(void *param) {
// ::std::cout << __LINE__ << '\n';
    double const duration{this->duration_from_base()};
// // ::std::cout << __LINE__ << '\t' << this->removed_event_list.size() << '\n';
//     for (unsigned long long int event_id : this->removed_event_id_list) {
//         // ::std::cout << __LINE__ << '\t' << event->time << '\t' << reinterpret_cast<void *>(event->event_func) << '\n';
//         for (::std::vector<::TimedEvent>::iterator event(this->timed_event_list.begin()); event != this->timed_event_list.end(); ) {
//             if (event->event_id == event_id) {
//                 event = this->timed_event_list.erase(event);
//             } else {
//                 ++event;
//             }
//         }
//     }
//     this->removed_event_id_list.clear();
    if (this->should_refresh) {
        this->should_refresh = false;
        this->timed_event_list.clear();
    }
    this->timed_event_list.insert(this->timed_event_list.end(), this->prepared_event_list.begin(), this->prepared_event_list.end());
    this->prepared_event_list.clear();
// ::std::cout << __LINE__ << '\n';
    for (::std::vector<::TimedEvent>::iterator event(this->timed_event_list.begin()); event != this->timed_event_list.end(); ) {
// ::std::cout << __LINE__ << '\t';
        if (duration >= event->time) {
// {
// using namespace ::FuncSource;
// ::std::cout << reinterpret_cast<void *>(&game_activity_diqczi_eventer_0_init)
// << reinterpret_cast<void *>(&game_activity_diqczi_updater_0_init)
// << reinterpret_cast<void *>(&game_activity_diqczi_eventer_0)
// << reinterpret_cast<void *>(&game_activity_diqczi_updater_0)
// << reinterpret_cast<void *>(&game_activity_diqdann_eventer_0)
// << reinterpret_cast<void *>(&game_activity_diqdann_updater_0)
// << reinterpret_cast<void *>(&game_activity_diqczi_eventer_0_quit)
// << '\n';
// }
// ::std::cout << __LINE__ << '\t' << reinterpret_cast<void *>(event->event_func) << '\t';
// ::std::cout << __LINE__ << '\t' << (void *)(event->event_func) << '\t' << (void *)(&::FuncSource::main_activity_quad_eventer_init) << '\n';
            (*event->event_func)(param, &event->lparam_map);
// ::std::cout << __LINE__ << '\t' << (void *)(event->event_func) << ' ' << (void *)(&::FuncSource::game_activity_diqczi_eventer_0_quit) << '\n';
            event = this->timed_event_list.erase(event);
// ::std::cout << __LINE__ << '\n';
        } else {
            ++event;
        }
    }
// ::std::cout << __LINE__ << '\n';
}
// void Timer::remove(unsigned long long int event_id) {
//     this->removed_event_id_list.emplace_back(event_id);
// }
void Timer::set_base_time() {
    this->base_time = ::std::chrono::system_clock::now();
}
void Timer::set_latest_time() {
    this->second_latest_time = this->latest_time;
    this->latest_time = ::std::chrono::system_clock::now();
}

// void __audio_cbfunc(void *audio_player_ptr, ::Uint8 *audio_stream, int length) {
//     ::AudioSource::AudioPlayer *audio_player{reinterpret_cast<::AudioSource::AudioPlayer *>(audio_player_ptr)};
//     if (audio_player->offset + length >= audio_player->audio->length) {
//         length = audio_player->audio->length - audio_player->offset;
//     }
//     for (unsigned int i{0U}; i < length; ++i) {
//         *audio_stream++ = audio_player->audio->data[audio_player->offset++];
//     }
//     if (length < ::AudioSource::audio_samples * ::AudioSource::audio_sample_width) {
//         audio_player->offset = 0U;
//     }
// }
// ::AudioSource::AudioPlayer __audio_player{};

MainActivity::MainActivity(): logo_displayer(&::FuncSource::General::null_updater, ::TexSource::tex_ids["logo"], 512.0, 1024.0, 128.0, 128.0), selection_displayer(&::FuncSource::General::null_updater), bgm_player(::AudioSource::audio_ids["fuuinsaresi_kamigami"]) { }
MainActivity::~MainActivity() { }
void MainActivity::init() {
    this->bgm_player.play();
    // ::std::this_thread::sleep_for(::std::chrono::milliseconds(2048));
    // ::std::cout << "pause\n";
    // this->bgm_player.pause();
    // ::std::this_thread::sleep_for(::std::chrono::milliseconds(2048));
    // ::std::cout << "play again\n";
    // this->bgm_player.pause();
    // this->bgm_player = ::AudioSource::play_audio(::AudioSource::audio_ids["fuuinsaresi_kamigami"]);
    // {
    //     ::AudioSource::audio_player_list.push_back(new ::AudioSource::AudioPlayer{::AudioSource::audio_list.data() + 3});
    //     ::AudioSource::AudioPlayer *audio_player{::AudioSource::audio_player_list.back()};
    //     ::SDL_AudioSpec audio_spec{};
    //     audio_spec.freq = ::AudioSource::audio_freq;
    //     audio_spec.format = AUDIO_S16SYS;
    //     audio_spec.samples = ::AudioSource::audio_samples;
    //     audio_spec.callback = &::AudioSource::audio_cbfunc;
    //     audio_spec.userdata = audio_player;
    //     audio_player->device_id = ::SDL_OpenAudioDevice(nullptr, 0, &audio_spec, nullptr, 0);
    //     ::SDL_PauseAudioDevice(audio_player->device_id, 0);
    // }

    ::glEnable(GL_DEPTH_TEST);
    ::glDepthFunc(GL_LEQUAL);

    ::glEnable(GL_BLEND);
    ::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ::glEnable(GL_SCISSOR_TEST);

    ::glPointSize(4.0F);

    ::Sseu::set_viewport(0, 0, ::Sseu::wnd_width, ::Sseu::wnd_height);
    ::Sseu::set_base_projection();
    ::Sseu::set_base_modelview();

    this->is_selection_hiden = true;
    this->has_animation_completed = false;

    this->logo_displayer.setting_time = ::std::chrono::system_clock::now();
    this->logo_displayer.update_func = &::FuncSource::MainActivity::main_activity_updater_smooth;
    this->logo_displayer.lparam_map[::LparamUsage::LU_SETX].d = 512.0;
    this->logo_displayer.lparam_map[::LparamUsage::LU_SETY].d = 768.0;
    this->logo_displayer.lparam_map[::LparamUsage::LU_DX].d = 0.0;
    this->logo_displayer.lparam_map[::LparamUsage::LU_DY].d = -384.0;

    this->selection_displayer.x = 1024.0;
    this->selection_displayer.y = 512.0;

    this->fps_displayer.start_counting();
}
void MainActivity::quit() {
    this->logo_displayer.update_func = &::FuncSource::General::null_updater;
    this->selection_displayer.update_func = &::FuncSource::General::null_updater;

    this->fps_displayer.stop_counting();

    // if (this->bgm_player != nullptr) {
    //     ::AudioSource::pause_audio(this->bgm_player);
    //     this->bgm_player = nullptr;
    // }
    this->bgm_player.pause();
}
void MainActivity::update() {
    ::Lparam activity_lparam{.p = this};
    this->logo_displayer.update(activity_lparam);
    this->selection_displayer.update(activity_lparam);
    for (::std::vector<::RotatedQuadDisplayer>::iterator zzingxua(this->zzingxua_list.begin()); zzingxua != this->zzingxua_list.end(); ) {
        zzingxua->update(activity_lparam);
        if (zzingxua->x > ::Sseu::vp_width + 128.0 || zzingxua->y < -128.0) {
            zzingxua = zzingxua_list.erase(zzingxua);
        } else {
            ++zzingxua;
        }
    }
    this->generate_zzingxua();

    ::glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
    ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ::glEnable(GL_TEXTURE_2D);
    ::glColor3ub(0xff, 0xff, 0xff);
    this->logo_displayer.display();
    this->selection_displayer.display();
    this->fps_displayer.display();
    // this->display_selections();
    for (::std::vector<::RotatedQuadDisplayer>::iterator zzingxua(this->zzingxua_list.begin()); zzingxua != this->zzingxua_list.end(); ++zzingxua) {
        zzingxua->display();
    }
    ::glDisable(GL_TEXTURE_2D);

    ::SDL_GL_SwapWindow(::Sseu::window);
    // ::std::this_thread::sleep_for(::std::chrono::milliseconds(64));
    this->timer.procedure(this);
    ::std::this_thread::sleep_until(this->timer.latest_time + ::std::chrono::milliseconds(16));
    this->timer.set_latest_time();
}
void MainActivity::procedure(::SDL_Event const event) {
    switch (event.type) {
        case ::SDL_EventType::SDL_KEYDOWN: {
            if (this->is_selection_hiden) {
                if (this->has_animation_completed) {
                    this->is_selection_hiden = false;
                    this->has_animation_completed = false;

                    this->logo_displayer.setting_time = ::std::chrono::system_clock::now();
                    this->logo_displayer.update_func = &::FuncSource::MainActivity::main_activity_updater_smooth;
                    this->logo_displayer.lparam_map[::LparamUsage::LU_SETX].d = 512.0;
                    this->logo_displayer.lparam_map[::LparamUsage::LU_SETY].d = 384.0;
                    this->logo_displayer.lparam_map[::LparamUsage::LU_DX].d = -192.0;
                    this->logo_displayer.lparam_map[::LparamUsage::LU_DY].d = 0.0;

                    this->selection_displayer.setting_time = ::std::chrono::system_clock::now();
                    this->selection_displayer.update_func = &::FuncSource::MainActivity::main_activity_updater_smooth;
                    this->selection_displayer.lparam_map[::LparamUsage::LU_SETX].d = 1024.0;
                    this->selection_displayer.lparam_map[::LparamUsage::LU_SETY].d = 512.0;
                    this->selection_displayer.lparam_map[::LparamUsage::LU_DX].d = -256.0;
                    this->selection_displayer.lparam_map[::LparamUsage::LU_DY].d = 0.0;
                    // 可以設置成，如果按下的是Escape，那麽自動選中QUIT選項
                }
            } else {
                switch (event.key.keysym.sym) {
                    case ::SDL_KeyCode::SDLK_RETURN: case ::SDL_KeyCode::SDLK_z: {
                        switch (this->selection_displayer.selected) {
                            case 0U: {
                                ::AudioSource::play_audio_once(::AudioSource::audio_ids["option_choose"]);
                                // ::AudioSource::play_audio_once(::AudioSource::audio_ids["option_choose"]);
                                ::Sseu::push_activity<::GameActivity>();
                                break;
                            }
                            case 1U: {
                                ::AudioSource::play_audio_once(::AudioSource::audio_ids["option_quit"]);
                                // ::AudioSource::play_audio_once(::AudioSource::audio_ids["option_quit"]);
                                ::Sseu::pop_activity();
                                break;
                            }
                        }
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_ESCAPE: {
                        ::AudioSource::play_audio_once(::AudioSource::audio_ids["option_quit"]);
                        // ::AudioSource::play_audio_once(::AudioSource::audio_ids["option_quit"]);
                        this->selection_displayer.selected = 1U;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_UP: case ::SDL_KeyCode::SDLK_RIGHT: {
                        ::AudioSource::play_audio_once(::AudioSource::audio_ids["option_change"]);
                        // ::AudioSource::play_audio_once(::AudioSource::audio_ids["option_change"]);
                        ++this->selection_displayer.selected %= 2U;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_DOWN: case ::SDL_KeyCode::SDLK_LEFT: {
                        ::AudioSource::play_audio_once(::AudioSource::audio_ids["option_change"]);
                        // ::AudioSource::play_audio_once(::AudioSource::audio_ids["option_change"]);
                        --this->selection_displayer.selected %= 2U;
                        break;
                    }
                                                                // case ::SDL_KeyCode::SDLK_SPACE: {
                                                                //     ::AudioSource::play_audio_once(::AudioSource::audio_ids["option_change"]);
                                                                //     break;
                                                                // }
                }
            }
            break;
        }
    }
}
// void MainActivity::display_selections() {
//     ::glPushMatrix();
//     ::glTranslatef(768.0F, 384.0F, 0.0F);
//     this->selected == 0U ? ::glColor3ub(0xff, 0xff, 0xff) : ::glColor3ub(0x80, 0x80, 0x80);
//     ::Sseu::FontSource::draw_text("START", 16.0);
//     ::glTranslatef(0.0F, -64.0F, 0.0F);
//     this->selected == 1U ? ::glColor3ub(0xff, 0xff, 0xff) : ::glColor3ub(0x80, 0x80, 0x80);
//     ::Sseu::FontSource::draw_text("QUIT", 16.0);
//     ::glPopMatrix();
// }
void MainActivity::generate_zzingxua() {
    if (this->zzingxua_list.size() < 64ULL) {
        const unsigned int tex_id{::TexSource::tex_ids[::rand() * 8 < RAND_MAX ? "ssiauzzian" : "zzingxua"]};
        const double start_x{::rand() * ::Sseu::vp_width * 2.0 / RAND_MAX - ::Sseu::vp_width};
        const double start_y{(start_x / ::Sseu::vp_width + 1.0) * ::Sseu::vp_height};
        const double half_size{::rand() * 6.0 / RAND_MAX + 2.0};
        this->zzingxua_list.emplace_back(&::FuncSource::MainActivity::updater_zzingxua, tex_id, start_x, start_y, half_size, half_size, M_PI_2, 0.0);
        ::RotatedQuadDisplayer *zzingxua{&this->zzingxua_list.back()};
        zzingxua->lparam_map[::LparamUsage::LU_DX].d = ::rand() * 256e-3 / RAND_MAX;
        zzingxua->lparam_map[::LparamUsage::LU_DY].d = -::rand() * 256e-3 / RAND_MAX;
    }
}

GameActivity::GameActivity(): is_exsisting{true}, is_suspending{false}, event_updater{nullptr}, logo_displayer(&::FuncSource::General::null_updater, ::TexSource::tex_ids["logo"], 800.0, 256.0, 128.0, 128.0), tzuihczi(&::FuncSource::Characters::game_activity_tzuihczi_updater, ::TexSource::tex_ids["prigozin_on_plane"], 256.0, 256.0, 32.0, 32.0, false, false), boss(&::FuncSource::Characters::game_activity_boss_updater, ::TexSource::tex_ids["zelensikij"], 256.0, 768.0, 128.0, 64.0, false, false), bgm_player{new ::AudioSource::AudioPlayer(::AudioSource::audio_ids["harudomanno_youkai_shoujo"])}, shooting_sound_player(::AudioSource::audio_ids["shooting_sound"]) {
    this->tzoiczi_list.emplace_back(&::FuncSource::Characters::game_activity_tzoiczi_updater, ::TexSource::tex_ids["vagner"], this->tzuihczi.x, this->tzuihczi.y, 8.0, 8.0, M_PI_2, 0.0);
    this->tzoiczi_list.back().lparam_map[::LparamUsage::LU_TARGET].p = &this->tzuihczi;
    this->tzoiczi_list.back().lparam_map[::LparamUsage::LU_DX].d = -64.0;
    this->tzoiczi_list.back().lparam_map[::LparamUsage::LU_DY].d = 0.0;
    this->tzoiczi_list.emplace_back(&::FuncSource::Characters::game_activity_tzoiczi_updater, ::TexSource::tex_ids["vagner"], this->tzuihczi.x, this->tzuihczi.y, 8.0, 8.0, M_PI_2, 0.0);
    this->tzoiczi_list.back().lparam_map[::LparamUsage::LU_TARGET].p = &this->tzuihczi;
    this->tzoiczi_list.back().lparam_map[::LparamUsage::LU_DX].d = -32.0;
    this->tzoiczi_list.back().lparam_map[::LparamUsage::LU_DY].d = 32.0;
    this->tzoiczi_list.emplace_back(&::FuncSource::Characters::game_activity_tzoiczi_updater, ::TexSource::tex_ids["vagner"], this->tzuihczi.x, this->tzuihczi.y, 8.0, 8.0, M_PI_2, 0.0);
    this->tzoiczi_list.back().lparam_map[::LparamUsage::LU_TARGET].p = &this->tzuihczi;
    this->tzoiczi_list.back().lparam_map[::LparamUsage::LU_DX].d = 32.0;
    this->tzoiczi_list.back().lparam_map[::LparamUsage::LU_DY].d = 32.0;
    this->tzoiczi_list.emplace_back(&::FuncSource::Characters::game_activity_tzoiczi_updater, ::TexSource::tex_ids["vagner"], this->tzuihczi.x, this->tzuihczi.y, 8.0, 8.0, M_PI_2, 0.0);
    this->tzoiczi_list.back().lparam_map[::LparamUsage::LU_TARGET].p = &this->tzuihczi;
    this->tzoiczi_list.back().lparam_map[::LparamUsage::LU_DX].d = 64.0;
    this->tzoiczi_list.back().lparam_map[::LparamUsage::LU_DY].d = 0.0;

// ::RotatedQuadDisplayer tzd(&::FuncSource::game_activity_tzoiczi_updater, ::TexSource::tex_ids["vagner"], 8.0, 8.0, M_PI_2, 0.0, &this->tzuihczi, 64.0, 0.0);
// ::std::cout << __LINE__ << '\t' << &tzd << '\t' << tzd.tzuihczi << '\n';
// (*tzd.update_func)(&tzd, 42ULL);
// tzd.update(42ULL);

    // for (unsigned int i{0U}; i < 10U; ++i) {
    //     this->timer.prepare(1024 + ::rand() % 1024, &::FuncSource::game_activity_diqczi_eventer_0, i);
    // }
    // this->timer.prepare(::TimedEvent(this->timer.duration_from_base(), &::FuncSource::Stuffs::graze_per_256_milliseconds_eventer));
    // this->timer.prepare(::TimedEvent(2048, &::FuncSource::Diqczi_Test_1::eventer_init));
    this->timer.prepare(::TimedEvent(2048, &::FuncSource::Diqczi_0::game_activity_diqczi_eventer_0_init));
    // ::FuncSource::game_activity_diqczi_eventer_test_init(this, nullptr);
}
GameActivity::~GameActivity() {
    this->is_exsisting = false;
// ::std::cout << __LINE__ << '\t' << '\n';
    for (::QuadDisplayer *diqczi : this->diqczi_list) {
        delete diqczi;
    }
// ::std::cout << __LINE__ << '\t' << '\n';
    for (::QuadDisplayer *tzuihdann : this->tzuihdann_list) {
        delete tzuihdann;
    }
// ::std::cout << __LINE__ << '\t' << '\n';
    for (::QuadDisplayer *diqdann : this->diqdann_list) {
        delete diqdann;
    }
    for (::Updater *diqczi : this->removed_updater_list) {
        delete diqczi;
    }
// ::std::cout << __LINE__ << '\t' << '\n';
}
void GameActivity::init() {
    this->bgm_player->play();
    // this->bgm_player = ::AudioSource::play_audio(::AudioSource::audio_ids["harudomanno_youkai_shoujo"]);

    ::glEnable(GL_DEPTH_TEST);
    ::glDepthFunc(GL_LEQUAL);

    ::glEnable(GL_BLEND);
    ::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ::glEnable(GL_SCISSOR_TEST);

    ::glMatrixMode(GL_MODELVIEW);
    ::glLoadIdentity();
    ::gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    ::glPointSize(4.0F);

    this->fps_displayer.start_counting();
}
void GameActivity::quit() {
    this->fps_displayer.stop_counting();

    // unsigned int audio_id{::AudioSource::audio_ids["harudomanno_youkai_shoujo"]};
    // ::AudioSource::pause_audio(this->bgm_player);
    // ::AudioSource::rewind_audio(this->bgm_player);
    this->bgm_player->pause();
    this->bgm_player->offset = 0U;
}
void GameActivity::update() {
// ::std::cout << __LINE__ << '\t' << '\n';
// ::std::cout << __LINE__ << '\n';
    double const duration{this->timer.duration_from_latest()};
    // this->info_displayer.score += (this->info_displayer.target_score - this->info_displayer.score) * duration * 256e-3;
    // this->info_displayer.power += (this->info_displayer.target_power - this->info_displayer.power) * duration * 256e-3;
    // if (this->info_displayer.score > 65536) {
    //     ::std::cout << this->info_displayer.score << '\n';
    // }
    // if (this->graze_per_frame > 1) { ::std::cout << "Total graze\t" << this->graze_per_frame << '\n'; }
    // this->graze_per_frame = 0U;
    this->info_displayer.update();
    if (!this->is_suspending) {
        ::Lparam activity_lparam{.p = this};
        // unsigned long long int activity_ptr{reinterpret_cast<unsigned long long int>(this)};
// ::std::cout << __LINE__ << '\t' << this->event_updater << '\t' << this->updater_status[this->event_updater] << '\n';
        if (this->event_updater != nullptr && this->updater_status[this->event_updater]) {
            this->event_updater->update(activity_lparam);
        }
// ::std::cout << __LINE__ << '\n';
        this->gamearea.update(this->timer.duration_from_latest());
// ::std::cout << __LINE__ << '\n';
        // double tzuihczi_speed{this->tzuihczi.moving_speed * duration};
        // if (this->key_state[::SDL_KeyCode::SDLK_UP]) {
        //     this->tzuihczi.y += tzuihczi_speed;
        // } else if (this->key_state[::SDL_KeyCode::SDLK_DOWN]) {
        //     this->tzuihczi.y -= tzuihczi_speed;
        // }
        // if (this->key_state[::SDL_KeyCode::SDLK_LEFT]) {
        //     this->tzuihczi.is_mirrored = true;
        //     this->tzuihczi.x -= tzuihczi_speed;
        // } else if (this->key_state[::SDL_KeyCode::SDLK_RIGHT]) {
        //     this->tzuihczi.is_mirrored = false;
        //     this->tzuihczi.x += tzuihczi_speed;
        // }
        for (::std::vector<::QuadDisplayer *>::iterator ssiaygoo(this->back_ssiaygoo_list.begin()); ssiaygoo != this->back_ssiaygoo_list.end(); ) {
            (*ssiaygoo)->update(activity_lparam);
            if (!(*ssiaygoo)->lparam_map[::LparamUsage::LU_EXISTENCE].b) {
                delete *ssiaygoo;
                ssiaygoo = this->back_ssiaygoo_list.erase(ssiaygoo);
            } else {
                ++ssiaygoo;
            }
        }
// ::std::cout << __LINE__ << '\n';
        this->tzuihczi.update(activity_lparam);
// ::std::cout << __LINE__ << '\n';
        for (::std::vector<::RotatedQuadDisplayer>::iterator tzoiczi(this->tzoiczi_list.begin()); tzoiczi != this->tzoiczi_list.end(); ++tzoiczi) {
// ::std::cout << __LINE__ << '\t' << tzoiczi.base() << '\t' << tzoiczi->tzuihczi << '\n';
            tzoiczi->update(activity_lparam);
        }
// ::std::cout << __LINE__ << '\n';
        for (::std::vector<::QuadDisplayer *>::iterator diqczi(this->diqczi_list.begin()); diqczi != this->diqczi_list.end(); ) {
            (*diqczi)->update(activity_lparam);
            if ((*diqczi)->lparam_map[::LparamUsage::LU_HEAL].ll <= 0 || (*diqczi)->x < -128.0 || (*diqczi)->x > ::Sseu::vp_width + 128.0 || (*diqczi)->y < -128.0 || (*diqczi)->y > ::Sseu::vp_height + 128.0) {
// ::std::cout << __LINE__ << '\t' << '\n';
                ::QuadDisplayer *daycziuh{new ::QuadDisplayer(&::FuncSource::Stuffs::game_activity_daycziuh_updater_appear, ::TexSource::tex_ids[::rand() * 2 < RAND_MAX ? "power_point" : "dean_point"], (*diqczi)->x, (*diqczi)->y, 8.0, 8.0)};
                double const theta{M_PI * 2 * ::rand() / RAND_MAX};
                double const distance{256.0 * ::rand() / RAND_MAX};
                daycziuh->lparam_map[::LparamUsage::LU_SETX].d = daycziuh->x;
                daycziuh->lparam_map[::LparamUsage::LU_SETY].d = daycziuh->y;
                daycziuh->lparam_map[::LparamUsage::LU_DX].d = ::std::min(::std::max(distance * ::cos(theta), -daycziuh->x), ::Sseu::vp_width - daycziuh->x);
                daycziuh->lparam_map[::LparamUsage::LU_DY].d = ::std::min(::std::max(distance * ::sin(theta), -daycziuh->y), ::Sseu::vp_height - daycziuh->y);
                daycziuh->lparam_map[::LparamUsage::LU_EFFECT].ull = daycziuh->tex_id == ::TexSource::tex_ids["power_point"] ? 0ULL : 1ULL;
                this->daycziuh_list.emplace_back(daycziuh);
                this->updater_status[daycziuh] = true;
// ::std::cout << __LINE__ << '\t' << '\n';
                this->updater_status[*diqczi] = false;
                this->removed_updater_list.emplace_back(*diqczi);
                diqczi = this->diqczi_list.erase(diqczi);
// ::std::cout << __LINE__ << '\t' << '\n';
            } else {
// ::std::cout << __LINE__ << '\t' << '\n';
                ++diqczi;
            }
// ::std::cout << __LINE__ << '\t' << '\n';
        }
// ::std::cout << __LINE__ << '\n';
        // this->tzuihdann_list.lock();
        for (::std::vector<::QuadDisplayer *>::iterator tzuihdann(this->tzuihdann_list.begin()); tzuihdann != this->tzuihdann_list.end(); ) {
            (*tzuihdann)->update(activity_lparam);
            ::std::vector<::QuadDisplayer *>::iterator diqczi(this->diqczi_list.begin());
            while (diqczi != this->diqczi_list.end() && ::FuncSource::General::calc_norm((*tzuihdann)->x - (*diqczi)->x, (*tzuihdann)->y - (*diqczi)->y) >= (*tzuihdann)->half_width + ::std::min((*diqczi)->half_width, (*diqczi)->half_height)) {
                ++diqczi;
            }
            if (diqczi != this->diqczi_list.end()) {
                this->updater_status[*tzuihdann] = false;
                delete *tzuihdann;
                tzuihdann = this->tzuihdann_list.erase(tzuihdann);
                // tzuihdann = this->tzuihdann_list.erase_displayer(tzuihdann, &this->updater_status);
                --(*diqczi)->lparam_map[::LparamUsage::LU_HEAL].ll;
                // ::std::cout << (*diqczi)->lparam_map[::LparamUsage::LU_HEAL].ull << '\n';
                // this->updater_status[*diqczi] = false;
                // delete *diqczi;
                // this->diqczi_list.erase(diqczi);
                // this->diqczi_list.erase_displayer(diqczi, &this->updater_status);
            } else if ((*tzuihdann)->x < -128.0 || (*tzuihdann)->x > ::Sseu::vp_width + 128.0 || (*tzuihdann)->y < -128.0 || (*tzuihdann)->y > ::Sseu::vp_height + 128.0) {
                this->updater_status[*tzuihdann] = false;
                delete *tzuihdann;
                tzuihdann = this->tzuihdann_list.erase(tzuihdann);
                // tzuihdann = this->tzuihdann_list.erase_displayer(tzuihdann, &this->updater_status);
            } else {
                ++tzuihdann;
            }
        }
        // this->tzuihdann_list.unlock();
// ::std::cout << __LINE__ << '\n';
        // this->diqdann_list.lock();
// this->tzuihczi.lparam_map[::LparamUsage::LU_IS_INJURY_FREE].b = true;
        for (::std::vector<::QuadDisplayer *>::iterator diqdann(this->diqdann_list.begin()); diqdann != this->diqdann_list.end(); ) {
            (*diqdann)->update(activity_lparam);
            double const distance{::FuncSource::General::calc_norm((*diqdann)->x - this->tzuihczi.x, (*diqdann)->y - this->tzuihczi.y) - (*diqdann)->half_width};
            if (!(*diqdann)->lparam_map[::LparamUsage::LU_IS_GRAZED].b && distance >= 0 && distance < 16) {
                (*diqdann)->lparam_map[::LparamUsage::LU_IS_GRAZED].b = true;
                this->tzuihczi_graze((*diqdann)->x, (*diqdann)->y);
                // ::QuadDisplayer *ssiaygoo{new ::QuadDisplayer(&::FuncSource::game_activity_ssiaygoo_updater_graze, ::TexSource::tex_ids["graze"], this->tzuihczi.x, this->tzuihczi.y, 8.0, 8.0)};
                // ssiaygoo->lparam_map[::LparamUsage::LU_SETX].d = ssiaygoo->x;
                // ssiaygoo->lparam_map[::LparamUsage::LU_SETY].d = ssiaygoo->y;
                // ssiaygoo->lparam_map[::LparamUsage::LU_DX].d = (this->tzuihczi.x - diqdann->x) * 4;
                // ssiaygoo->lparam_map[::LparamUsage::LU_DY].d = (this->tzuihczi.y - diqdann->y) * 4;
                // ssiaygoo->lparam_map[::LparamUsage::LU_EXISTENCE].b = true;
                // this->ssiaygoo_list.emplace_back(ssiaygoo);
                // // 這裏需要爲效果設置updater_status嗎？我覺得暫時不用，因爲接下來沒有什麽與效果交互的部分。
                // diqdann->lparam_map[::LparamUsage::LU_IS_GRAZED].b = true;
                // ++this->info_displayer.graze;
                // this->info_displayer.target_score += 500;
                // if (this->graze_per_frame < 2U) {
                //     ::AudioSource::play_audio_once(::AudioSource::audio_ids["graze_sound"]);
                //     ++this->graze_per_frame;
                //     ::std::cout << "Graze\t" << this->graze_per_frame << '\n';
                // }
            }
            if (!this->tzuihczi.lparam_map[::LparamUsage::LU_IS_INJURY_FREE].b && distance < 0) {
                this->tzuihczi_miss();
                // this->tzuihczi.lparam_map[::LparamUsage::LU_IS_INJURY_FREE].b = true;
                // ::std::thread([this]() -> void {
                //     ::std::this_thread::sleep_for(::std::chrono::milliseconds(8192));
                //     this->tzuihczi.lparam_map[::LparamUsage::LU_IS_INJURY_FREE].b = false;
                // }).detach();
                // if (this->info_displayer.player > 0U) {
                //     --this->info_displayer.player;
                // } else {
                //     ::std::cout << "Lose!\n";
                // }
                // this->tzuihczi.x = 256.0;
                // this->tzuihczi.y = -64,0;
                // this->tzuihczi.update_func = &::FuncSource::Characters::game_activity_tzuihczi_updater_recover;
                // // ::AudioSource::play_audio(::AudioSource::audio_ids["biu"]);
                // // ::std::thread([]() -> void {
                // //     ::std::this_thread::sleep_for(::std::chrono::milliseconds(1024));
                // //     ::AudioSource::pause_audio(::AudioSource::audio_ids["biu"]);
                // // }).detach();
                // ::AudioSource::play_audio_once(::AudioSource::audio_ids["biu"]);
                diqdann = this->diqdann_list.erase(diqdann);
                // ::std::cout << "Miss!" << *diqdann << '\n';
            } else if ((*diqdann)->x < -128.0 || (*diqdann)->x > ::Sseu::vp_width + 128.0 || (*diqdann)->y < -128.0 || (*diqdann)->y > ::Sseu::vp_height + 128.0) {
                this->updater_status[*diqdann] = false;
                delete *diqdann;
                diqdann = this->diqdann_list.erase(diqdann);
                // diqdann = this->diqdann_list.erase_displayer(diqdann, &this->updater_status);
            } else {
                ++diqdann;
            }
        }
        // this->diqdann_list.unlock();
// ::std::cout << __LINE__ << '\n';
        for (::std::vector<::LineDisplayer *>::iterator cziguang(this->cziguang_list.begin()); cziguang != this->cziguang_list.end(); ) {
// ::std::cout << __LINE__ << '\n';
            (*cziguang)->update(activity_lparam);
// ::std::cout << __LINE__ << '\n';
            const double cos_rotation{::cos((*cziguang)->rotation)};
            const double sin_rotation{::sin((*cziguang)->rotation)};
            const double dx = this->tzuihczi.x - (*cziguang)->x;
            const double dy = this->tzuihczi.y - (*cziguang)->y;
            // const double radical{dy * cos_rotation - dx * sin_rotation};
            // const double vertical{dx * cos_rotation + dy * sin_rotation};
            if (!this->tzuihczi.lparam_map[::LparamUsage::LU_IS_INJURY_FREE].b && dy * cos_rotation - dx * sin_rotation > 0 && ::fabs(dx * cos_rotation + dy * sin_rotation) < (*cziguang)->half_width) {
                this->tzuihczi_miss();
                ::std::cout << "Collide cziguang\n";
            }
            // 這裏補上擦彈判定和碰撞判定，其中下面一句在擦彈中是需要的
            ::TimedEvent event(this->timer.duration_from_base() + 1024, &::FuncSource::Stuffs::game_activity_cziguang_eventer_recover);
            event.lparam_map[::LparamUsage::LU_TARGET].p = *cziguang;
            this->timer.prepare(event);
            if (!(*cziguang)->lparam_map[::LparamUsage::LU_EXISTENCE].b) {
                cziguang = this->cziguang_list.erase(cziguang);
            } else {
                ++cziguang;
            }
// ::std::cout << __LINE__ << '\n';
        }
// ::std::cout << __LINE__ << '\n';
        for (::std::vector<::QuadDisplayer *>::iterator daycziuh(this->daycziuh_list.begin()); daycziuh != this->daycziuh_list.end(); ) {
            (*daycziuh)->update(activity_lparam);
            if (::FuncSource::General::calc_norm((*daycziuh)->x - this->tzuihczi.x, (*daycziuh)->y - this->tzuihczi.y) < (*daycziuh)->half_width + this->tzuihczi.half_width) {
                switch ((*daycziuh)->lparam_map[::LparamUsage::LU_EFFECT].ull) {
                    case 0ULL: {
                        this->info_displayer.target_power = ::std::min(this->info_displayer.power + 5U, 500U);
                        break;
                    }
                    case 1ULL: {
                        this->info_displayer.target_score += this->tzuihczi.y * 256 + 4096;
                        break;
                    }
                }
                ::AudioSource::play_audio_once(::AudioSource::audio_ids["catch_daycziuh"]);
                this->updater_status[*daycziuh] = false;
                delete *daycziuh;
                daycziuh = this->daycziuh_list.erase(daycziuh);
            } else if ((*daycziuh)->x < -128.0 || (*daycziuh)->x > ::Sseu::vp_width + 128.0 || (*daycziuh)->y < -128.0 || (*daycziuh)->y > ::Sseu::vp_height + 128.0) {
                this->updater_status[*daycziuh] = false;
                delete *daycziuh;
                daycziuh = this->daycziuh_list.erase(daycziuh);
            } else {
                ++daycziuh;
            }
        }
        for (::std::vector<::QuadDisplayer *>::iterator ssiaygoo(this->ssiaygoo_list.begin()); ssiaygoo != this->ssiaygoo_list.end(); ) {
            (*ssiaygoo)->update(activity_lparam);
            if (!(*ssiaygoo)->lparam_map[::LparamUsage::LU_EXISTENCE].b) {
                delete *ssiaygoo;
                ssiaygoo = this->ssiaygoo_list.erase(ssiaygoo);
            } else {
                ++ssiaygoo;
            }
        }
    }
// ::std::cout << __LINE__ << '\n';

    // ::glPushMatrix();
    // ::glTranslatef(0.0F, 0.0F, -63.0F);

    ::Sseu::set_viewport(0, 0, ::Sseu::wnd_width, ::Sseu::wnd_height);
    ::Sseu::set_base_projection();
    ::glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
    ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ::glEnable(GL_TEXTURE_2D);
    ::glColor3ub(0xff, 0xff, 0xff);
    this->display_background();
    ::glColor3ub(0xff, 0xff, 0xff);
    this->info_displayer.display();
    this->logo_displayer.display();
    this->fps_displayer.display();
    ::glDisable(GL_TEXTURE_2D);

    ::Sseu::set_viewport(64, 64, 512, 640);
    ::glEnable(GL_TEXTURE_2D);
    ::glClear(GL_DEPTH_BUFFER_BIT);
    this->gamearea.display();

    // ::glPopMatrix();
    // ::glTranslatef(0.0F, 0.0F, 63.0F);

// ::std::cout << __LINE__ << '\n';
    for (::QuadDisplayer *ssiaygoo : this->back_ssiaygoo_list) {
        ssiaygoo->display();
    }
    if (!this->tzuihczi.lparam_map[::LparamUsage::LU_IS_INJURY_FREE].b || ::fmod(this->timer.duration_from_base(), 512.0) >= 256.0) {
        this->tzuihczi.display();
// ::std::cout << this->tzuihczi.x << ' ' << this->tzuihczi.y << '\n';
    }
    for (::std::vector<::RotatedQuadDisplayer>::iterator tzoiczi(this->tzoiczi_list.begin()); tzoiczi != this->tzoiczi_list.end(); ++tzoiczi) {
        tzoiczi->display();
    }
    // this->boss.display();
    for (::QuadDisplayer *diqczi : this->diqczi_list) {
        diqczi->display();
    }
    for (::QuadDisplayer *tzuihdann : this->tzuihdann_list) {
        tzuihdann->display();
    }
    // this->diqdann_list.lock();
    for (::QuadDisplayer *diqdann : this->diqdann_list) {
        diqdann->display();
    }
    // this->diqdann_list.unlock();
// ::std::cout << __LINE__ << '\n';
    for (::LineDisplayer *cziguang : this->cziguang_list) {
        cziguang->display();
    }
// ::std::cout << __LINE__ << '\n';
    for (::QuadDisplayer *daycziuh : this->daycziuh_list) {
        daycziuh->display();
    }
    for (::QuadDisplayer *ssiaygoo : this->ssiaygoo_list) {
        ssiaygoo->display();
    }
    if (this->tzuihczi.lparam_map[::LparamUsage::LU_IS_SLOW].b) {
        this->display_judge_point();
    }
    ::glDisable(GL_TEXTURE_2D);

// ::std::cout << __LINE__ << '\t' << '\n';

    if (this->is_suspending) {
        this->display_suspending_curtain();
    }

    ::SDL_GL_SwapWindow(::Sseu::window);
// ::std::cout << __LINE__ << '\t' << '\n';
// ::std::cout << __LINE__ << '\n';
    this->timer.procedure(this);
// ::std::cout << __LINE__ << '\n';
    ::std::this_thread::sleep_until(this->timer.latest_time + ::std::chrono::milliseconds(16));
    this->timer.set_latest_time();
// ::std::cout << __LINE__ << '\n';
}
void GameActivity::procedure(::SDL_Event const event) {
    switch (event.type) {
        case ::SDL_EventType::SDL_KEYDOWN: {
            this->key_state[event.key.keysym.sym] = true;
            if (this->is_suspending) {
                switch (event.key.keysym.sym) {
                    case ::SDL_KeyCode::SDLK_ESCAPE: {
                        this->is_suspending = false;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_RETURN: case ::SDL_KeyCode::SDLK_z: {
                        switch (this->selected) {
                            case 0U: {
                                this->is_suspending = false;
                                break;
                            }
                            case 1U: {
                                ::Sseu::pop_activity();
                                break;
                            }
                        }
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_UP: {
                        ::AudioSource::play_audio_once(::AudioSource::audio_ids["option_change"]);
                        --this->selected %= 2U;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_DOWN: {
                        ::AudioSource::play_audio_once(::AudioSource::audio_ids["option_change"]);
                        ++this->selected %= 2U;
                        break;
                    }
                }
            } else {
                switch (event.key.keysym.sym) {
                    case ::SDL_KeyCode::SDLK_ESCAPE: {
                        this->is_suspending = true;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_LSHIFT: case ::SDL_KeyCode::SDLK_RSHIFT: {
                        this->tzuihczi.lparam_map[::LparamUsage::LU_IS_SLOW].b = true;
                        this->tzoiczi_list[0].lparam_map[::LparamUsage::LU_DX].d = -32.0;
                        this->tzoiczi_list[0].lparam_map[::LparamUsage::LU_DY].d = 0.0;
                        this->tzoiczi_list[1].lparam_map[::LparamUsage::LU_DX].d = -16.0;
                        this->tzoiczi_list[1].lparam_map[::LparamUsage::LU_DY].d = -16.0;
                        this->tzoiczi_list[2].lparam_map[::LparamUsage::LU_DX].d = 16.0;
                        this->tzoiczi_list[2].lparam_map[::LparamUsage::LU_DY].d = -16.0;
                        this->tzoiczi_list[3].lparam_map[::LparamUsage::LU_DX].d = 32.0;
                        this->tzoiczi_list[3].lparam_map[::LparamUsage::LU_DY].d = 0.0;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_LEFT: {
                        this->tzuihczi.lparam_map[::LparamUsage::LU_IS_HMIRRORED].b = true;
                        this->tzuihczi.lparam_map[::LparamUsage::LU_DX].d = -0.5;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_RIGHT: {
                        this->tzuihczi.lparam_map[::LparamUsage::LU_IS_HMIRRORED].b = false;
                        this->tzuihczi.lparam_map[::LparamUsage::LU_DX].d = 0.5;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_UP: {
                        this->tzuihczi.lparam_map[::LparamUsage::LU_DY].d = 0.5;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_DOWN: {
                        this->tzuihczi.lparam_map[::LparamUsage::LU_DY].d = -0.5;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_z: {
                        // if (!this->tzuihczi.lparam_map[::LparamUsage::LU_IS_SHOOTING].b) {
                        //     this->tzuihczi.lparam_map[::LparamUsage::LU_IS_SHOOTING].b = true;
                        //     this->tzuihczi.shooting_thr = ::std::thread([this]() {
                        //         while (this->tzuihczi.lparam_map[::LparamUsage::LU_IS_SHOOTING].b) {
                        //             double const offset{this->tzuihczi.is_mirrored ? 16.0 : -16.0};
                        //             this->tzuihdann_list.lock();
                                    // ::OrientedQuadDisplayer *tzuihdann;
                                    // this->tzuihdann_list.emplace_back(tzuihdann = new ::OrientedQuadDisplayer(&::FuncSource::game_activity_tzuihdann_updater, ::TexSource::tex_ids["shoigu"], this->tzuihczi.x - offset, this->tzuihczi.y, 16.0, 16.0, M_PI_2));
                                    // this->updater_status[tzuihdann] = true;
                                    // this->tzuihdann_list.emplace_back(tzuihdann = new ::OrientedQuadDisplayer(&::FuncSource::game_activity_tzuihdann_updater, ::TexSource::tex_ids["gerasimov"], this->tzuihczi.x + offset, this->tzuihczi.y, 16.0, 16.0, M_PI_2));
                                    // this->updater_status[tzuihdann] = true;
                                    // for (::std::vector<::RotatedQuadDisplayer>::iterator tzoiczi(this->tzoiczi_list.begin()); tzoiczi != this->tzoiczi_list.end(); ++tzoiczi) {
                                    //     ::TrackingQuadDisplayer *tzoidann{new ::TrackingQuadDisplayer(&::FuncSource::game_activity_tzoidann_updater, ::TexSource::tex_ids["tracking_bullet"], tzoiczi->x, tzoiczi->y, 8.0, 8.0, M_PI_2, 0.0, this->diqczi_list.empty() ? nullptr : this->diqczi_list[::rand() % this->diqczi_list.size()])};
                                    //     this->tzuihdann_list.emplace_back(tzoidann);
                                    //     this->updater_status[tzoidann] = true;
                                    // }
                        //             this->tzuihdann_list.unlock();
                        //             ::std::this_thread::sleep_for(::std::chrono::milliseconds(64));
                        //         }
                        //     });
                        // }
                        if (!this->tzuihczi.lparam_map[::LparamUsage::LU_IS_SHOOTING].b) {
                            // unsigned int const audio_id{::AudioSource::audio_ids["shoot_sound"]};
                            // ::AudioSource::rewind_audio(audio_id);
                            // ::AudioSource::play_audio(audio_id);
                            // this->tzuihczi.lparam_map[::LparamUsage::LU_AUDIO_PLAYER].p = ::AudioSource::play_audio(::AudioSource::audio_ids["shoot_sound"]);
                            this->shooting_sound_player.play();
                        }
                        this->tzuihczi.lparam_map[::LparamUsage::LU_IS_SHOOTING].b = true;
                        break;
                    }
// case ::SDL_KeyCode::SDLK_SPACE: {
//     this->info_displayer.target_score += 1000;
//     break;
// }
                }
            }
            break;
        }
        case ::SDL_EventType::SDL_KEYUP: {
            this->key_state[event.key.keysym.sym] = false;
            if (!this->is_suspending) {
                switch (event.key.keysym.sym) {
                    case ::SDL_KeyCode::SDLK_LSHIFT: case ::SDL_KeyCode::SDLK_RSHIFT: {
                        this->tzuihczi.lparam_map[::LparamUsage::LU_IS_SLOW].b = false;
                        this->tzoiczi_list[0].lparam_map[::LparamUsage::LU_DX].d = -64.0;
                        this->tzoiczi_list[0].lparam_map[::LparamUsage::LU_DY].d = 0.0;
                        this->tzoiczi_list[1].lparam_map[::LparamUsage::LU_DX].d = -32.0;
                        this->tzoiczi_list[1].lparam_map[::LparamUsage::LU_DY].d = 32.0;
                        this->tzoiczi_list[2].lparam_map[::LparamUsage::LU_DX].d = 32.0;
                        this->tzoiczi_list[2].lparam_map[::LparamUsage::LU_DY].d = 32.0;
                        this->tzoiczi_list[3].lparam_map[::LparamUsage::LU_DX].d = 64.0;
                        this->tzoiczi_list[3].lparam_map[::LparamUsage::LU_DY].d = 0.0;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_LEFT: {
                        this->tzuihczi.lparam_map[::LparamUsage::LU_DX].d = this->key_state[::SDL_KeyCode::SDLK_RIGHT] * 0.5;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_RIGHT: {
                        this->tzuihczi.lparam_map[::LparamUsage::LU_DX].d = this->key_state[::SDL_KeyCode::SDLK_LEFT] * -0.5;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_UP: {
                        this->tzuihczi.lparam_map[::LparamUsage::LU_DY].d = this->key_state[::SDL_KeyCode::SDLK_DOWN] * -0.5;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_DOWN: {
                        this->tzuihczi.lparam_map[::LparamUsage::LU_DY].d = this->key_state[::SDL_KeyCode::SDLK_UP] * 0.5;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_z: {
                        // if (this->tzuihczi.lparam_map[::LparamUsage::LU_IS_SHOOTING].b) {
                        //     this->tzuihczi.lparam_map[::LparamUsage::LU_IS_SHOOTING].b = false;
                        //     this->tzuihczi.shooting_thr.join();
                        // }
                        if (this->tzuihczi.lparam_map[::LparamUsage::LU_IS_SHOOTING].b) {
                            // ::AudioSource::pause_audio(::AudioSource::audio_ids["shoot_sound"]);
                            // ::AudioSource::pause_audio(reinterpret_cast<::AudioSource::AudioPlayer *>(this->tzuihczi.lparam_map[::LparamUsage::LU_AUDIO_PLAYER].p));
                            this->shooting_sound_player.pause();
                        }
                        this->tzuihczi.lparam_map[::LparamUsage::LU_IS_SHOOTING].b = false;
                    }
                }
            }
            break;
        }
    }
}
void GameActivity::display_background() {
    ::glBindTexture(GL_TEXTURE_2D, ::TexSource::tex_ids["game_background"]);
    ::glBegin(GL_QUADS);
    ::glTexCoord2i(0, 1);
    ::glVertex2i(0, 0);
    ::glTexCoord2i(0, 0);
    ::glVertex2i(0, ::Sseu::vp_height);
    ::glTexCoord2i(1, 0);
    ::glVertex2i(::Sseu::vp_width, ::Sseu::vp_height);
    ::glTexCoord2i(1, 1);
    ::glVertex2i(::Sseu::vp_width, 0);
    ::glEnd();
    ::glColor4ub(0x00, 0x00, 0x00, 0x80);
    ::glBegin(GL_QUADS);
    ::glVertex2i(0, 0);
    ::glVertex2i(0, ::Sseu::vp_height);
    ::glVertex2i(::Sseu::vp_width, ::Sseu::vp_height);
    ::glVertex2i(::Sseu::vp_width, 0);
    ::glEnd();
}
void GameActivity::display_gamearea_background() {
}
void GameActivity::display_gamearea_box() {
    ::glColor3ub(0x80, 0x80, 0x80);
    ::glLineWidth(2.0F);
    ::glBegin(GL_LINE_STRIP);
    ::glVertex2i(0, 0);
    ::glVertex2i(0, ::Sseu::vp_height - 0);
    ::glVertex2i(::Sseu::vp_width - 0, ::Sseu::vp_height - 0);
    ::glVertex2i(::Sseu::vp_width - 0, 0);
    ::glVertex2i(0, 0);
    ::glEnd();
}
void GameActivity::display_judge_point() {
    ::glPushMatrix();
    ::glTranslated(this->tzuihczi.x, this->tzuihczi.y, 0.0);
    ::glBindTexture(GL_TEXTURE_2D, ::TexSource::tex_ids["judge_point"]);
    ::glBegin(GL_QUADS);
    ::glTexCoord2i(0, 1);
    ::glVertex2d(-6.0, -6.0);
    ::glTexCoord2i(0, 0);
    ::glVertex2d(-6.0, 6.0);
    ::glTexCoord2i(1, 0);
    ::glVertex2d(6.0, 6.0);
    ::glTexCoord2i(1, 1);
    ::glVertex2d(6.0, -6.0);
    ::glEnd();
    ::glPopMatrix();
}
void GameActivity::display_suspending_curtain() {
    ::glColor4ub(0x80, 0x00, 0x00, 0x80);
    ::glBegin(GL_QUADS);
    ::glVertex2i(0, 0);
    ::glVertex2i(0, ::Sseu::vp_height);
    ::glVertex2i(::Sseu::vp_width, ::Sseu::vp_height);
    ::glVertex2i(::Sseu::vp_width, 0);
    ::glEnd();

    ::Sseu::FontSource::start_text();
    ::glColor3ub(0xff, 0xff, 0xff);
    ::glPushMatrix();
    ::glTranslatef(128.0F, 384.0F, 0.0F);
    this->selected == 0U ? ::glColor3ub(0xff, 0xff, 0xff) : ::glColor3ub(0x80, 0x80, 0x80);
    ::Sseu::FontSource::draw_text("CONTINUE GAME", 16.0);
    ::glTranslatef(0.0F, -64.0F, 0.0F);
    this->selected == 1U ? ::glColor3ub(0xff, 0xff, 0xff) : ::glColor3ub(0x80, 0x80, 0x80);
    ::Sseu::FontSource::draw_text("BACK TO TITLE SCREEN", 16.0);
    ::glPopMatrix();
    ::Sseu::FontSource::end_text();
}
void GameActivity::tzuihczi_graze(double const set_x, double const set_y) {
    ++this->info_displayer.graze;
    this->info_displayer.target_score += 500;
    // if (this->graze_per_128_milliseconds < 114U) {
    ::QuadDisplayer *ssiaygoo{new ::QuadDisplayer(&::FuncSource::Stuffs::game_activity_ssiaygoo_updater_graze, ::TexSource::tex_ids["graze"], this->tzuihczi.x, this->tzuihczi.y, 8.0, 8.0)};
    ssiaygoo->lparam_map[::LparamUsage::LU_SETX].d = ssiaygoo->x;
    ssiaygoo->lparam_map[::LparamUsage::LU_SETY].d = ssiaygoo->y;
    ssiaygoo->lparam_map[::LparamUsage::LU_DX].d = (this->tzuihczi.x - set_x) * 4;
    ssiaygoo->lparam_map[::LparamUsage::LU_DY].d = (this->tzuihczi.y - set_y) * 4;
    ssiaygoo->lparam_map[::LparamUsage::LU_EXISTENCE].b = true;
    this->ssiaygoo_list.emplace_back(ssiaygoo);
    ssiaygoo->lparam_map[::LparamUsage::LU_IS_GRAZED].b = true;
    ::AudioSource::play_audio_once(::AudioSource::audio_ids["graze_sound"]);
    // ++this->graze_per_128_milliseconds;
    // ::std::cout << "Graze\t" << this->graze_per_128_milliseconds << '\n';
    // }
}
void GameActivity::tzuihczi_miss() {
    this->tzuihczi.lparam_map[::LparamUsage::LU_IS_INJURY_FREE].b = true;
    ::std::thread([this]() -> void {
        ::std::this_thread::sleep_for(::std::chrono::milliseconds(8192));
        this->tzuihczi.lparam_map[::LparamUsage::LU_IS_INJURY_FREE].b = false;
    }).detach();
    if (this->info_displayer.player > 0U) {
        --this->info_displayer.player;
    } else {
        ::std::cout << "Lose!\n";
    }
    this->tzuihczi.x = 256.0;
    this->tzuihczi.y = -64,0;
    this->tzuihczi.update_func = &::FuncSource::Characters::game_activity_tzuihczi_updater_recover;
    // ::AudioSource::play_audio(::AudioSource::audio_ids["biu"]);
    // ::std::thread([]() -> void {
    //     ::std::this_thread::sleep_for(::std::chrono::milliseconds(1024));
    //     ::AudioSource::pause_audio(::AudioSource::audio_ids["biu"]);
    // }).detach();
    ::AudioSource::play_audio_once(::AudioSource::audio_ids["biu"]);
}
void GameActivity::tzuihczi_shoot() {
    ::QuadDisplayer *tzuihdann;
    unsigned int tex_id_left, tex_id_right;
    if (this->tzuihczi.lparam_map[::LparamUsage::LU_IS_HMIRRORED].b) {
        tex_id_left = ::TexSource::tex_ids["shoigu"];
        tex_id_right = ::TexSource::tex_ids["gerasimov"];
    } else {
        tex_id_left = ::TexSource::tex_ids["gerasimov"];
        tex_id_right = ::TexSource::tex_ids["shoigu"];
    }
    this->tzuihdann_list.emplace_back(tzuihdann = new ::QuadDisplayer(&::FuncSource::Characters::game_activity_tzuihdann_updater, tex_id_left, this->tzuihczi.x - 16, this->tzuihczi.y, 16.0, 16.0));
    tzuihdann->lparam_map[::LparamUsage::LU_SETX].d = tzuihdann->x;
    tzuihdann->lparam_map[::LparamUsage::LU_SETY].d = tzuihdann->y;
    tzuihdann->lparam_map[::LparamUsage::LU_DX].d = 0.0;
    tzuihdann->lparam_map[::LparamUsage::LU_DY].d = 1.0;
    this->updater_status[tzuihdann] = true;
    this->tzuihdann_list.emplace_back(tzuihdann = new ::QuadDisplayer(&::FuncSource::Characters::game_activity_tzuihdann_updater, tex_id_right, this->tzuihczi.x + 16, this->tzuihczi.y, 16.0, 16.0));
    tzuihdann->lparam_map[::LparamUsage::LU_SETX].d = tzuihdann->x;
    tzuihdann->lparam_map[::LparamUsage::LU_SETY].d = tzuihdann->y;
    tzuihdann->lparam_map[::LparamUsage::LU_DX].d = 0.0;
    tzuihdann->lparam_map[::LparamUsage::LU_DY].d = 1.0;
    this->updater_status[tzuihdann] = true;
    for (::std::vector<::RotatedQuadDisplayer>::iterator tzoiczi(this->tzoiczi_list.begin()); tzoiczi != this->tzoiczi_list.end(); ++tzoiczi) {
        ::RotatedQuadDisplayer *tzoidann{new ::RotatedQuadDisplayer(&::FuncSource::Characters::game_activity_tzoidann_updater, ::TexSource::tex_ids["tracking_bullet"], tzoiczi->x, tzoiczi->y, 8.0, 8.0, M_PI_2, (0.375 - (tzoiczi - this->tzoiczi_list.begin()) * 0.25) * M_PI)};
        tzoidann->lparam_map[::LparamUsage::LU_TARGET].p = this->diqczi_list.empty() ? nullptr : this->diqczi_list[::rand() % this->diqczi_list.size()];
        this->tzuihdann_list.emplace_back(tzoidann);
        this->updater_status[tzoidann] = true;
    }
}
// void GameActivity::graze_quad_displayer(::QuadDisplayer *diqdann) {
// }

// #include <iomanip>
// union U;
// inline ::std::ostream &operator << (::std::ostream &, ::U &);
// union U{
//     unsigned long long ull;
//     double d;
//     ::std::vector<U> v;
//     inline U();
//     inline U(unsigned long long);
//     inline U(double);
//     inline U(U const &);
//     inline ~U();
//     inline friend ::std::ostream &operator << (::std::ostream &, ::U &);
// };
// U::U() { }
// U::U(unsigned long long ull): ull{ull} { }
// U::U(double d): d{d} { }
// U::U(::U const &u) {
// ::std::cout << "::U::U(U const &u)\tin\t" << ::std::hex << u.ull << '\n';
//     for (unsigned long long *src{reinterpret_cast<unsigned long long *>(reinterpret_cast<unsigned long long>(&u))}, *data{src}, *dst{reinterpret_cast<unsigned long long *>(reinterpret_cast<unsigned long long>(this))}; data - src < sizeof(::U) / sizeof(unsigned long long); ++data, ++dst) {
// ::std::cout << dst << '\n';
//         *dst = *data;
// ::std::cout << ::std::hex << *dst << '\n';
//     }
// ::std::cout << "::U::U(U const &u)\tout\t" << ::std::hex << u.ull << '\n';
// }
// U::~U() { }
// ::std::ostream &operator <<(::std::ostream &os, ::U &u) {
//     os << ::std::hex;
//     for (unsigned char *src{reinterpret_cast<unsigned char *>(reinterpret_cast<unsigned long long>(&u))}, *data{src}; data - src < sizeof(U) && os << ' '; ++data) {
//         os << ::std::setw(2) << ::std::setfill('0') << int(*data);
//     }
//     return os;
// }

int WINAPI WinMain(::HINSTANCE, ::HINSTANCE, ::LPTSTR, int) {
    // ::std::cout << sizeof(double) << '\t' << sizeof(unsigned long long int) << '\n';
    // double d{0.114514};
    // ::std::cout << *reinterpret_cast<double *>(reinterpret_cast<unsigned long long int *>(&d)) << '\n';
    // ::std::cout << (::Lparam{.b = true}.b << 1) << '\n';
    // ::U u0(0x123456789abcdefULL), u1, u2, u3;
    // u2.v.emplace_back(::U(0xfedcba987654321ULL));
    // ::std::cout << u0 << '\n' << u1 << '\n' << u2 << '\n' << u3 << '\n';
    // ::std::cout << sizeof(::std::unordered_map<::LparamUsage, ::Lparam>) << '\n';
    // return 0;

    ::Sseu::init("東綫ПРОЖЕКТ", 64, 64, 1024, 768);
    ::Sseu::FontSource::source_init();
    ::TexSource::source_init();
    ::AudioSource::source_init();
    ::Sseu::push_activity<::MainActivity>();
    ::Sseu::mainloop();
    ::AudioSource::source_quit();
    ::TexSource::source_quit();
    ::Sseu::FontSource::source_quit();
    ::Sseu::quit();
    return 0;
}

#endif
