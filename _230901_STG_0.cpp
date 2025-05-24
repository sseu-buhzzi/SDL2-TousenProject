#ifndef STG_CPP

#include ".\FuncSource.hpp"

Updater::Updater(void (*update_func)(void *, unsigned long long)): setting_time{::std::chrono::system_clock::now()}, update_func{update_func} { }
void Updater::update(unsigned long long lparam) {
// ::std::cout << __LINE__ << '\t' << this << '\t' << reinterpret_cast<::TzoicziDisplayer *>(this)->tzuihczi << '\n';
    (*this->update_func)(this, lparam);
}

QuadDisplayer::QuadDisplayer(void (*update_func)(void *, unsigned long long), unsigned int tex_id, double x, double y, double half_width, double half_height): ::Updater::Updater(update_func), tex_id{tex_id}, x{x}, y{y}, half_width{half_width}, half_height{half_height} { }
QuadDisplayer::~QuadDisplayer() { }
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

MirroredQuadDisplayer::MirroredQuadDisplayer(void (*update_func)(void *, unsigned long long), unsigned int tex_id, double x, double y, double half_width, double half_height, bool is_mirrored): ::QuadDisplayer::QuadDisplayer(update_func, tex_id, x, y, half_width, half_height), is_mirrored{is_mirrored} { }
void MirroredQuadDisplayer::display() {
    ::glPushMatrix();
    ::glTranslated(this->x, this->y, 0.0);
    ::glBindTexture(GL_TEXTURE_2D, this->tex_id);
    ::glBegin(GL_QUADS);
    if (this->is_mirrored) {
        ::glTexCoord2i(0, 1);
        ::glVertex2d(this->half_width, -this->half_height);
        ::glTexCoord2i(0, 0);
        ::glVertex2d(this->half_width, this->half_height);
        ::glTexCoord2i(1, 0);
        ::glVertex2d(-this->half_width, this->half_height);
        ::glTexCoord2i(1, 1);
        ::glVertex2d(-this->half_width, -this->half_height);
    } else {
        ::glTexCoord2i(0, 1);
        ::glVertex2d(-this->half_width, -this->half_height);
        ::glTexCoord2i(0, 0);
        ::glVertex2d(-this->half_width, this->half_height);
        ::glTexCoord2i(1, 0);
        ::glVertex2d(this->half_width, this->half_height);
        ::glTexCoord2i(1, 1);
        ::glVertex2d(this->half_width, -this->half_height);
    }
    ::glEnd();
    ::glPopMatrix();
}

TzuihcziDisplayer::TzuihcziDisplayer(void (*update_func)(void *, unsigned long long), unsigned int tex_id, double x, double y, double half_width, double half_height, bool is_mirrored): ::MirroredQuadDisplayer::MirroredQuadDisplayer(update_func, tex_id, x, y, half_width, half_height, is_mirrored), dx{0.0}, dy{0.0}, is_shifting{false}, is_shooting{false}, is_injury_free{false} { }
void TzuihcziDisplayer::display_judge_point() {
    ::glPushMatrix();
    ::glTranslated(this->x, this->y, 0.0);
    ::glBindTexture(GL_TEXTURE_2D, ::Sseu::TexSource::tex_ids["judge_point"]);
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

OrientedQuadDisplayer::OrientedQuadDisplayer(void (*update_func)(void *, unsigned long long), unsigned int tex_id, double x, double y, double half_width, double half_height, double theta): ::QuadDisplayer::QuadDisplayer(update_func, tex_id, x, y, half_width, half_height), set_x{x}, set_y{y}, dx{::cos(theta)}, dy{::sin(theta)} { }

RotatedQuadDisplayer::RotatedQuadDisplayer(void (*update_func)(void *, unsigned long long), unsigned int tex_id, double x, double y, double half_width, double half_height, double phi, double theta): ::QuadDisplayer::QuadDisplayer(update_func, tex_id, x, y, half_width, half_height) { }
void RotatedQuadDisplayer::display() {
    if (!this->param_list.empty()) {
        this->phi = this->param_list[0];
        this->theta = this->param_list[1];
// ::std::cout << __LINE__ << '\t' << this->x << '\t' << this->y << '\n';
    }
    ::glPushMatrix();
    ::glTranslated(this->x, this->y, 0.0);
    ::glRotated(this->theta * M_1_PI * 180, 0.0, 0.0, 1.0);
    ::glRotated((M_PI_2 - this->phi) * M_1_PI * 180, 1.0, 0.0, 0.0);
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

TrackingQuadDisplayer::TrackingQuadDisplayer(void (*update_func)(void *, unsigned long long), unsigned int tex_id, double x, double y, double half_width, double half_height, double phi, double theta, ::QuadDisplayer *target_displayer): ::RotatedQuadDisplayer::RotatedQuadDisplayer(update_func, tex_id, x, y, half_width, half_height, phi, theta), target_displayer{target_displayer} { }

TzoicziDisplayer::TzoicziDisplayer(void (*update_func)(void *, unsigned long long), unsigned int tex_id, double half_width, double half_height, double phi, double theta, ::TzuihcziDisplayer *tzuihczi, double offset_x, double offset_y): ::RotatedQuadDisplayer::RotatedQuadDisplayer(update_func, tex_id, tzuihczi->x, tzuihczi->y, half_width, half_height, phi, theta), tzuihczi{tzuihczi}, offset_x{offset_x}, offset_y{offset_y} {
// ::std::cout << __LINE__ << '\t' << this->theta << '\n';
}

DiqcziDisplayer::DiqcziDisplayer(void (*update_func)(void *, unsigned long long), unsigned int tex_id, double x, double y, double half_width, double half_height, double heal): ::LocatedQuadDisplayer::LocatedQuadDisplayer(update_func, tex_id, x, y, half_width, half_height), heal{heal} { }

GameareaDisplayer::GameareaDisplayer(): process{0.0} { }
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
    ::glBindTexture(GL_TEXTURE_2D, ::Sseu::TexSource::tex_ids["wheat_field"]);
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
    ::glBindTexture(GL_TEXTURE_2D, ::Sseu::TexSource::tex_ids["blue_sky"]);
    ::glPushMatrix();
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
    ::glColor4ub(0x00, 0x00, 0x00, 0x80);
    ::glBegin(GL_QUADS);
    ::glVertex2i(0, 0);
    ::glVertex2i(0, ::Sseu::vp_height);
    ::glVertex2i(::Sseu::vp_width, ::Sseu::vp_height);
    ::glVertex2i(::Sseu::vp_width, 0);
    ::glEnd();
    ::glEnable(GL_TEXTURE_2D);
    ::glColor3ub(0xff, 0xff, 0xff);
}
void GameareaDisplayer::update() {
    this->process += 0.015625;
}

FpsDisplayer::FpsDisplayer(): frame_count{0U} { }
void FpsDisplayer::display() {
    ++this->frame_count;
    ::glPushMatrix();
    ::glTranslatef(1024 - this->fps_text.length() * 16, 0.0F, 0.0F);
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

// unsigned long long TimedEvent::event_count{0ULL};
TimedEvent::TimedEvent(double time, void (*event_func)(void *, unsigned long long), unsigned long long lparam): time{time}, event_func{event_func}, lparam{lparam} { }

Timer::Timer(): should_refresh{false}, base_time(::std::chrono::system_clock::now()), latest_time{::std::chrono::system_clock::now()}, second_latest_time{this->latest_time} { }
double Timer::duration_from_base() {
    return (::std::chrono::system_clock::now() - this->base_time).count() * 1e-6;
}
double Timer::duration_from_latest() {
    return (this->latest_time - this->second_latest_time).count() * 1e-6;
}
void Timer::prepare(::TimedEvent event) {
    this->prepared_event_list.emplace_back(event);
}
void Timer::procedure(void *param) {
// ::std::cout << __LINE__ << '\n';
    double const duration{this->duration_from_base()};
// // ::std::cout << __LINE__ << '\t' << this->removed_event_list.size() << '\n';
//     for (unsigned long long event_id : this->removed_event_id_list) {
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
// using namespace ::Sseu::FuncSource;
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
            (*event->event_func)(param, event->lparam);
// ::std::cout << __LINE__ << '\t' << (void *)(event->event_func) << ' ' << (void *)(&::Sseu::FuncSource::game_activity_diqczi_eventer_0_quit) << '\n';
            event = this->timed_event_list.erase(event);
// ::std::cout << __LINE__ << '\n';
        } else {
            ++event;
        }
    }
// ::std::cout << __LINE__ << '\n';
}
// void Timer::remove(unsigned long long event_id) {
//     this->removed_event_id_list.emplace_back(event_id);
// }
void Timer::set_base_time() {
    this->base_time = ::std::chrono::system_clock::now();
}
void Timer::set_latest_time() {
    this->second_latest_time = this->latest_time;
    this->latest_time = ::std::chrono::system_clock::now();
}

MainActivity::MainActivity(): selected{0U}, logo_displayer(&::Sseu::FuncSource::null_updater, ::Sseu::TexSource::tex_ids["logo"], 512.0, 512.0, 128.0, 128.0) { }
MainActivity::~MainActivity() {
}
void MainActivity::init() {
    ::Sseu::AudioSource::play_audio(::Sseu::AudioSource::audio_ids["fuuinsaresi_kamigami"]);

    ::glEnable(GL_DEPTH_TEST);
    ::glDepthFunc(GL_LEQUAL);

    ::glEnable(GL_BLEND);
    ::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ::glEnable(GL_SCISSOR_TEST);


    ::glPointSize(4.0F);

    ::Sseu::set_viewport(0, 0, ::Sseu::wnd_width, ::Sseu::wnd_height);
    ::Sseu::set_base_projection();
    ::Sseu::set_base_modelview();

    this->fps_displayer.start_counting();
}
void MainActivity::quit() {
    this->fps_displayer.stop_counting();

    ::Sseu::AudioSource::pause_audio(::Sseu::AudioSource::audio_ids["fuuinsaresi_kamigami"]);
}
void MainActivity::update() {
    ::glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
    ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ::glEnable(GL_TEXTURE_2D);
    ::glColor3ub(0xff, 0xff, 0xff);
    this->logo_displayer.display();
    this->fps_displayer.display();
    this->display_selections();
    ::glDisable(GL_TEXTURE_2D);

    ::SDL_GL_SwapWindow(::Sseu::window);
    ::std::this_thread::sleep_for(::std::chrono::milliseconds(64));
}
void MainActivity::procedure(::SDL_Event const event) {
    switch (event.type) {
        case ::SDL_EventType::SDL_KEYDOWN: {
            switch (event.key.keysym.sym) {
                case ::SDL_KeyCode::SDLK_RETURN: case ::SDL_KeyCode::SDLK_z: {
                    this->selected == 0U ? ::Sseu::push_activity<::GameActivity>() : ::Sseu::pop_activity();
                    break;
                }
                case ::SDL_KeyCode::SDLK_ESCAPE: {
                    ::Sseu::pop_activity();
                    break;
                }
                case ::SDL_KeyCode::SDLK_UP: case ::SDL_KeyCode::SDLK_RIGHT: {
                    ++this->selected %= 2U;
                    break;
                }
                case ::SDL_KeyCode::SDLK_DOWN: case ::SDL_KeyCode::SDLK_LEFT: {
                    --this->selected %= 2U;
                    break;
                }
            }
            break;
        }
    }
}
void MainActivity::display_selections() {
    ::glPushMatrix();
    ::glTranslatef(768.0F, 384.0F, 0.0F);
    this->selected == 0U ? ::glColor3ub(0xff, 0xff, 0xff) : ::glColor3ub(0x80, 0x80, 0x80);
    ::Sseu::FontSource::draw_text("START", 16.0);
    ::glTranslatef(0.0F, -64.0F, 0.0F);
    this->selected == 1U ? ::glColor3ub(0xff, 0xff, 0xff) : ::glColor3ub(0x80, 0x80, 0x80);
    ::Sseu::FontSource::draw_text("QUIT", 16.0);
    ::glPopMatrix();
}

GameActivity::GameActivity(): is_exsisting{true}, is_suspending{false}, event_updater{nullptr}, logo_displayer(&::Sseu::FuncSource::null_updater, ::Sseu::TexSource::tex_ids["logo"], 800.0, 256.0, 128.0, 128.0), tzuihczi(&::Sseu::FuncSource::game_activity_tzuihczi_updater, ::Sseu::TexSource::tex_ids["prigozin_on_plane"], 256.0, 256.0, 32.0, 32.0, false), boss(&::Sseu::FuncSource::game_activity_boss_updater, ::Sseu::TexSource::tex_ids["zelensikij"], 256.0, 768.0, 128.0, 64.0, false) {
    this->tzoiczi_list.emplace_back(&::Sseu::FuncSource::game_activity_tzoiczi_updater, ::Sseu::TexSource::tex_ids["vagner"], 8.0, 8.0, M_PI_2, 0.0, &this->tzuihczi, -64.0, 0.0);
    this->tzoiczi_list.emplace_back(&::Sseu::FuncSource::game_activity_tzoiczi_updater, ::Sseu::TexSource::tex_ids["vagner"], 8.0, 8.0, M_PI_2, 0.0, &this->tzuihczi, -32.0, 32.0);
    this->tzoiczi_list.emplace_back(&::Sseu::FuncSource::game_activity_tzoiczi_updater, ::Sseu::TexSource::tex_ids["vagner"], 8.0, 8.0, M_PI_2, 0.0, &this->tzuihczi, 32.0, 32.0);
    this->tzoiczi_list.emplace_back(&::Sseu::FuncSource::game_activity_tzoiczi_updater, ::Sseu::TexSource::tex_ids["vagner"], 8.0, 8.0, M_PI_2, 0.0, &this->tzuihczi, 64.0, 0.0);

// ::TzoicziDisplayer tzd(&::Sseu::FuncSource::game_activity_tzoiczi_updater, ::Sseu::TexSource::tex_ids["vagner"], 8.0, 8.0, M_PI_2, 0.0, &this->tzuihczi, 64.0, 0.0);
// ::std::cout << __LINE__ << '\t' << &tzd << '\t' << tzd.tzuihczi << '\n';
// (*tzd.update_func)(&tzd, 42ULL);
// tzd.update(42ULL);

    // for (unsigned int i{0U}; i < 10U; ++i) {
    //     this->timer.prepare(1024 + ::rand() % 1024, &::Sseu::FuncSource::game_activity_diqczi_eventer_0, i);
    // }
    this->timer.prepare(::TimedEvent(2048, &::Sseu::FuncSource::game_activity_diqczi_eventer_0_init, 0ULL));
}
GameActivity::~GameActivity() {
    this->is_exsisting = false;
// ::std::cout << __LINE__ << '\t' << '\n';
    for (::DiqcziDisplayer *diqczi : this->diqczi_list) {
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
// ::std::cout << __LINE__ << '\t' << '\n';
}
void GameActivity::init() {
    ::Sseu::AudioSource::play_audio(::Sseu::AudioSource::audio_ids["harudomanno_youkai_shoujo"]);

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

    unsigned int audio_id{::Sseu::AudioSource::audio_ids["harudomanno_youkai_shoujo"]};
    ::Sseu::AudioSource::pause_audio(audio_id);
    ::Sseu::AudioSource::rewind_audio(audio_id);
}
void GameActivity::update() {
// ::std::cout << __LINE__ << '\t' << '\n';
// ::std::cout << __LINE__ << '\n';
    double const duration{this->timer.duration_from_latest()};
    if (!this->is_suspending) {
        unsigned long long activity_ptr{reinterpret_cast<unsigned long long>(this)};
// ::std::cout << __LINE__ << '\t' << this->event_updater << '\t' << this->updater_status[this->event_updater] << '\n';
        if (this->event_updater != nullptr && this->updater_status[this->event_updater]) {
            this->event_updater->update(activity_ptr);
        }
// ::std::cout << __LINE__ << '\n';
        this->gamearea.update();
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
// ::std::cout << __LINE__ << '\n';
        this->tzuihczi.update(activity_ptr);
// ::std::cout << __LINE__ << '\n';
        for (::std::vector<::TzoicziDisplayer>::iterator tzoiczi(this->tzoiczi_list.begin()); tzoiczi != this->tzoiczi_list.end(); ++tzoiczi) {
// ::std::cout << __LINE__ << '\t' << tzoiczi.base() << '\t' << tzoiczi->tzuihczi << '\n';
            tzoiczi->update(activity_ptr);
        }
// ::std::cout << __LINE__ << '\n';
        for (::std::vector<::DiqcziDisplayer *>::iterator diqczi(this->diqczi_list.begin()); diqczi != this->diqczi_list.end(); ) {
            (*diqczi)->update(activity_ptr);
            if ((*diqczi)->heal <= 0 || (*diqczi)->x < 0.0 || (*diqczi)->x > ::Sseu::vp_width || (*diqczi)->y < 0.0 || (*diqczi)->y > ::Sseu::vp_height) {
// ::std::cout << __LINE__ << '\t' << '\n';
                this->updater_status[*diqczi] = false;
                delete *diqczi;
                diqczi = this->diqczi_list.erase(diqczi);
            } else {
// ::std::cout << __LINE__ << '\t' << '\n';
                ++diqczi;
            }
// ::std::cout << __LINE__ << '\t' << '\n';
        }
// ::std::cout << __LINE__ << '\n';
        this->tzuihdann_list.lock();
        for (::std::vector<::QuadDisplayer *>::iterator tzuihdann(this->tzuihdann_list.begin()); tzuihdann != this->tzuihdann_list.end(); ) {
            (*tzuihdann)->update(activity_ptr);
            ::std::vector<::DiqcziDisplayer *>::iterator diqczi(this->diqczi_list.begin());
            while (diqczi != this->diqczi_list.end() && ::Sseu::FuncSource::calc_norm((*tzuihdann)->x - (*diqczi)->x, (*tzuihdann)->y - (*diqczi)->y) >= (*tzuihdann)->half_width + (*diqczi)->half_width) {
                ++diqczi;
            }
            if (diqczi != this->diqczi_list.end()) {
                this->updater_status[*tzuihdann] = false;
                delete *tzuihdann;
                tzuihdann = this->tzuihdann_list.erase(tzuihdann);
                // tzuihdann = this->tzuihdann_list.erase_displayer(tzuihdann, &this->updater_status);
                --(*diqczi)->heal;
                // this->updater_status[*diqczi] = false;
                // delete *diqczi;
                // this->diqczi_list.erase(diqczi);
                // this->diqczi_list.erase_displayer(diqczi, &this->updater_status);
            } else if ((*tzuihdann)->x < 0.0 || (*tzuihdann)->x > ::Sseu::vp_width || (*tzuihdann)->y < 0.0 || (*tzuihdann)->y > ::Sseu::vp_height) {
                this->updater_status[*tzuihdann] = false;
                delete *tzuihdann;
                tzuihdann = this->tzuihdann_list.erase(tzuihdann);
                // tzuihdann = this->tzuihdann_list.erase_displayer(tzuihdann, &this->updater_status);
            } else {
                ++tzuihdann;
            }
        }
        this->tzuihdann_list.unlock();
// ::std::cout << __LINE__ << '\n';
        this->diqdann_list.lock();
        for (::std::vector<::QuadDisplayer *>::iterator diqdann(this->diqdann_list.begin()); diqdann != this->diqdann_list.end(); ) {
            (*diqdann)->update(activity_ptr);
            if (!this->tzuihczi.is_injury_free && ::Sseu::FuncSource::calc_norm((*diqdann)->x - this->tzuihczi.x, (*diqdann)->y - this->tzuihczi.y) < (*diqdann)->half_width + 4) {
                this->tzuihczi.is_injury_free = true;
                ::std::thread([this]() -> void {
                    ::std::this_thread::sleep_for(::std::chrono::milliseconds(4096));
                    this->tzuihczi.is_injury_free = false;
                }).detach();
                ::Sseu::AudioSource::play_audio(::Sseu::AudioSource::audio_ids["biu"]);
                ::std::thread([]() -> void {
                    ::std::this_thread::sleep_for(::std::chrono::milliseconds(1024));
                    ::Sseu::AudioSource::pause_audio(::Sseu::AudioSource::audio_ids["biu"]);
                }).detach();
                diqdann = this->diqdann_list.erase(diqdann);
                ::std::cout << "Bay!" << *diqdann << '\n';
            } else if ((*diqdann)->x < 0.0 || (*diqdann)->x > ::Sseu::vp_width || (*diqdann)->y < 0.0 || (*diqdann)->y > ::Sseu::vp_height) {
                this->updater_status[*diqdann] = false;
                delete *diqdann;
                diqdann = this->diqdann_list.erase(diqdann);
                // diqdann = this->diqdann_list.erase_displayer(diqdann, &this->updater_status);
            } else {
                ++diqdann;
            }
        }
        this->diqdann_list.unlock();
// ::std::cout << __LINE__ << '\n';
        this->timer.procedure(this);
// ::std::cout << __LINE__ << '\n';
        this->timer.set_latest_time();
// ::std::cout << __LINE__ << '\n';
    }
// ::std::cout << __LINE__ << '\n';

    ::Sseu::set_viewport(0, 0, ::Sseu::wnd_width, ::Sseu::wnd_height);
    ::Sseu::set_base_projection();
    ::glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
    ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ::glEnable(GL_TEXTURE_2D);
    ::glColor3ub(0xff, 0xff, 0xff);
    this->display_background();
    this->logo_displayer.display();
    this->fps_displayer.display();
    ::glDisable(GL_TEXTURE_2D);

    ::Sseu::set_viewport(64, 64, 512, 640);
    ::glEnable(GL_TEXTURE_2D);
    ::glClear(GL_DEPTH_BUFFER_BIT);
    this->gamearea.display();
    if (!this->tzuihczi.is_injury_free || ::fmod(this->timer.duration_from_base(), 512.0) >= 256.0) {
        this->tzuihczi.display();
// ::std::cout << this->tzuihczi.x << ' ' << this->tzuihczi.y << '\n';
    }
    for (::std::vector<::TzoicziDisplayer>::iterator tzoiczi(this->tzoiczi_list.begin()); tzoiczi != this->tzoiczi_list.end(); ++tzoiczi) {
        tzoiczi->display();
    }
    this->boss.display();
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
    this->tzuihczi.display_judge_point();
    ::glDisable(GL_TEXTURE_2D);

// ::std::cout << __LINE__ << '\t' << '\n';

    if (this->is_suspending) {
        this->display_suspending_curtain();
    }

    ::SDL_GL_SwapWindow(::Sseu::window);
// ::std::cout << __LINE__ << '\t' << '\n';
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
                        --this->selected %= 2U;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_DOWN: {
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
                        this->tzuihczi.is_shifting = true;
                        this->tzoiczi_list[0].offset_x = -32.0;
                        this->tzoiczi_list[1].offset_x = -16.0;
                        this->tzoiczi_list[1].offset_y = -16.0;
                        this->tzoiczi_list[2].offset_x = 16.0;
                        this->tzoiczi_list[2].offset_y = -16.0;
                        this->tzoiczi_list[3].offset_x = 32.0;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_LEFT: {
                        this->tzuihczi.is_mirrored = true;
                        this->tzuihczi.dx = -0.5;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_RIGHT: {
                        this->tzuihczi.is_mirrored = false;
                        this->tzuihczi.dx = 0.5;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_UP: {
                        this->tzuihczi.dy = 0.5;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_DOWN: {
                        this->tzuihczi.dy = -0.5;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_z: {
                        if (!this->tzuihczi.is_shooting) {
                            this->tzuihczi.is_shooting = true;
                            this->tzuihczi.shooting_thr = ::std::thread([this]() {
                                while (this->tzuihczi.is_shooting) {
                                    double const offset{this->tzuihczi.is_mirrored ? 16.0 : -16.0};
                                    this->tzuihdann_list.lock();
                                    ::OrientedQuadDisplayer *tzuihdann;
                                    this->tzuihdann_list.emplace_back(tzuihdann = new ::OrientedQuadDisplayer(&::Sseu::FuncSource::game_activity_tzuihdann_updater, ::Sseu::TexSource::tex_ids["shoigu"], this->tzuihczi.x - offset, this->tzuihczi.y, 16.0, 16.0, M_PI_2));
                                    this->updater_status[tzuihdann] = true;
                                    this->tzuihdann_list.emplace_back(tzuihdann = new ::OrientedQuadDisplayer(&::Sseu::FuncSource::game_activity_tzuihdann_updater, ::Sseu::TexSource::tex_ids["gerasimov"], this->tzuihczi.x + offset, this->tzuihczi.y, 16.0, 16.0, M_PI_2));
                                    this->updater_status[tzuihdann] = true;
                                    for (::std::vector<::TzoicziDisplayer>::iterator tzoiczi(this->tzoiczi_list.begin()); tzoiczi != this->tzoiczi_list.end(); ++tzoiczi) {
                                        ::TrackingQuadDisplayer *tzoidann{new ::TrackingQuadDisplayer(&::Sseu::FuncSource::game_activity_tzoidann_updater, ::Sseu::TexSource::tex_ids["tracking_bullet"], tzoiczi->x, tzoiczi->y, 8.0, 8.0, M_PI_2, 0.0, this->diqczi_list.empty() ? nullptr : this->diqczi_list[::rand() % this->diqczi_list.size()])};
                                        this->tzuihdann_list.emplace_back(tzoidann);
                                        this->updater_status[tzoidann] = true;
                                    }
                                    this->tzuihdann_list.unlock();
                                    ::std::this_thread::sleep_for(::std::chrono::milliseconds(64));
                                }
                            });
                        }
                    }
                }
            }
            break;
        }
        case ::SDL_EventType::SDL_KEYUP: {
            this->key_state[event.key.keysym.sym] = false;
            if (!this->is_suspending) {
                switch (event.key.keysym.sym) {
                    case ::SDL_KeyCode::SDLK_LSHIFT: case ::SDL_KeyCode::SDLK_RSHIFT: {
                        this->tzuihczi.is_shifting = false;
                        this->tzoiczi_list[0].offset_x = -64.0;
                        this->tzoiczi_list[1].offset_x = -32.0;
                        this->tzoiczi_list[1].offset_y = 32.0;
                        this->tzoiczi_list[2].offset_x = 32.0;
                        this->tzoiczi_list[2].offset_y = 32.0;
                        this->tzoiczi_list[3].offset_x = 64.0;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_LEFT: {
                        this->tzuihczi.dx = this->key_state[::SDL_KeyCode::SDLK_RIGHT] * 0.5;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_RIGHT: {
                        this->tzuihczi.dx = this->key_state[::SDL_KeyCode::SDLK_LEFT] * -0.5;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_UP: {
                        this->tzuihczi.dy = this->key_state[::SDL_KeyCode::SDLK_DOWN] * -0.5;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_DOWN: {
                        this->tzuihczi.dy = this->key_state[::SDL_KeyCode::SDLK_UP] * 0.5;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_z: {
                        if (this->tzuihczi.is_shooting) {
                            this->tzuihczi.is_shooting = false;
                            this->tzuihczi.shooting_thr.join();
                        }
                    }
                }
            }
            break;
        }
    }
}
void GameActivity::display_background() {
    ::glBindTexture(GL_TEXTURE_2D, ::Sseu::TexSource::tex_ids["game_background"]);
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

int WINAPI WinMain(::HINSTANCE, ::HINSTANCE, ::LPTSTR, int) {
    ::Sseu::init(::std::string(__FILE__).substr(54ULL, 61ULL).c_str(), 64, 64, 1024, 768);
    ::Sseu::FontSource::source_init();
    ::Sseu::TexSource::source_init();
    ::Sseu::AudioSource::source_init();
    ::Sseu::push_activity<::MainActivity>();
    ::Sseu::mainloop();
    ::Sseu::AudioSource::source_quit();
    ::Sseu::TexSource::source_quit();
    ::Sseu::FontSource::source_quit();
    ::Sseu::quit();
    return 0;
}

#endif
