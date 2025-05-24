// #define STG_CPP
#ifndef STG_CPP

#include ".\FuncSource.hpp"

QuadDisplayer::QuadDisplayer(unsigned int tex_id, double half_width, double half_height, void (*updater)(void *), double x, double y): is_exsisting{true}, exsist_time{::std::chrono::system_clock::now().time_since_epoch().count()}, tex_id{tex_id}, half_width{half_width}, half_height{half_height}, updater{updater}, x{x}, y{y} { }
QuadDisplayer::~QuadDisplayer() {
    this->is_exsisting = false;
}
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
void QuadDisplayer::update() {
    (*this->updater)(this);
}

MirroredQuadDisplayer::MirroredQuadDisplayer(unsigned int tex_id, double half_width, double half_height, void (*updater)(void *), double x, double y, bool is_mirrored): ::QuadDisplayer::QuadDisplayer(tex_id, half_width, half_height, updater, x, y), is_mirrored{is_mirrored} { }
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

TzuihcziDisplayer::TzuihcziDisplayer(unsigned int tex_id, double half_width, double half_height, void (*updater)(void *), double x, double y, bool is_mirrored): ::MirroredQuadDisplayer::MirroredQuadDisplayer(tex_id, half_width, half_height, updater, x, y, is_mirrored), moving_speed{256.0}, is_shooting{false}, is_injury_free{false} { }
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

OrientedQuadDisplayer::OrientedQuadDisplayer(unsigned int tex_id, double half_width, double half_height, void (*updater)(void *), double x, double y, double theta): ::QuadDisplayer::QuadDisplayer(tex_id, half_width, half_height, updater, x, y), set_x{x}, set_y{y}, dx{::cos(theta)}, dy{::sin(theta)} { }

RotatedQuadDisplayer::RotatedQuadDisplayer(unsigned int tex_id, double half_width, double half_height, void (*updater)(void *), double x, double y, double phi, double theta): ::QuadDisplayer::QuadDisplayer(tex_id, half_width, half_height, updater, x, y), phi{phi}, theta{theta} { }
void RotatedQuadDisplayer::display() {
    ::glPushMatrix();
    ::glTranslated(this->x, this->y, 0.0);
    ::glRotated(this->theta, 0.0, 0.0, 1.0);
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

TzoicziDisplayer::TzoicziDisplayer(unsigned int tex_id, double half_width, double half_height, void (*updater)(void *), double phi, double theta, ::TzuihcziDisplayer *tzuihczi, double offset_x, double offset_y): ::RotatedQuadDisplayer::RotatedQuadDisplayer(tex_id, half_width, half_height, updater, tzuihczi->x, tzuihczi->y, phi, theta), tzuihczi{tzuihczi}, offset_x{offset_x}, offset_y{offset_y} { }

GameareaBackgroundDisplayer::GameareaBackgroundDisplayer(): offset{0.0} { }
void GameareaBackgroundDisplayer::display() {
    ::glMatrixMode(GL_PROJECTION);
    ::glLoadIdentity();
// 這裏看看要不要把參數調一下，換成簡單一點的
    // ::glFrustum(-0.125, 0.125, -0.09375, 0.09375, 0.0625, 1024.0);
    ::glFrustum(-1.0, 1.0, -double(::Sseu::vp_height) / ::Sseu::vp_width, double(::Sseu::vp_height) / ::Sseu::vp_width, 1.0, 1024.0);
    ::glPushMatrix();
    ::glTranslatef(0.0F, 0.0F, -256.0F);
    ::glRotatef(-75.0F, 1.0F, 0.0F, 0.0F);
    ::glRotatef(15.0F, 0.0F, 0.0F, 1.0F);
    ::glColor3ub(0xff, 0xff, 0xff);
    ::glBindTexture(GL_TEXTURE_2D, ::Sseu::TexSource::tex_ids["wheat_field"]);
    ::glBegin(GL_QUADS);
    for (int i{-2}; i < 8; ++i) {
        for (int j{-4}; j < 8; ++j) {
            ::glTexCoord2i(0, 1);
            ::glVertex2d(j * 256 - this->offset, i * 128 - this->offset);
            ::glTexCoord2i(0, 0);
            ::glVertex2d(j * 256 - this->offset, (i + 1) * 128 - this->offset);
            ::glTexCoord2i(1, 0);
            ::glVertex2d((j + 1) * 256 - this->offset, (i + 1) * 128 - this->offset);
            ::glTexCoord2i(1, 1);
            ::glVertex2d((j + 1) * 256 - this->offset, i * 128 - this->offset);
        }
    }
    ::glEnd();
    ::glPopMatrix();
    ::Sseu::set_base_projection();
    ::glBindTexture(GL_TEXTURE_2D, ::Sseu::TexSource::tex_ids["blue_sky"]);
    ::glBegin(GL_QUADS);
    ::glTexCoord2i(0, 1);
    ::glVertex2i(0, 352);
    ::glTexCoord2i(0, 0);
    ::glVertex2i(0, 864);
    ::glTexCoord2i(1, 0);
    ::glVertex2i(512, 864);
    ::glTexCoord2i(1, 1);
    ::glVertex2i(512, 352);
    ::glEnd();
}
void GameareaBackgroundDisplayer::update() {
    this->offset += 0.0625;
    while (this->offset >= 256) {
        this->offset -= 256;
    }
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
// ::std::cout << this->counting_thr.joinable() << '\n';
    this->counting_thr.join();
}

EventTimer::EventTimer(void *activity_ptr): activity_ptr{activity_ptr}, basetime(::std::chrono::system_clock::now()) { }
void EventTimer::procedure() {
    double duration((::std::chrono::system_clock::now() - this->basetime).count() * 1e-6);
    // ::std::unordered_set<double> passed_events;
    ::std::vector<double> passed_events;
    for (::std::unordered_map<double, void (*)(void *)>::iterator event(this->begin()); event != this->end() && duration >= event->first; ++event) {
        (*event->second)(this->activity_ptr);
// ::std::cout << __LINE__ << '\t';
// ::std::cout << event->first << '\n';
        passed_events.emplace_back(event->first);
    }
// ::std::cout << __LINE__ << '\t';
// ::std::cout << passed_events.size() << '\n';
    // for (::std::unordered_set<double>::iterator event_time(passed_events.begin()); event_time != passed_events.end(); ++event_time) {
    //     ::std::cout << *event_time << '\n';
    //     // this->erase(*event_time);
    // }
    for (double event : passed_events) {
// ::std::cout << __LINE__ << '\t';
// ::std::cout << event << '\n';
        this->erase(event);
    }
// ::std::cout << __LINE__ << '\t';
// ::std::cout << passed_events.size() << '\n';
}
void EventTimer::set_basetime() {
    this->basetime = ::std::chrono::system_clock::now();
}

MainActivity::MainActivity(): selected{0U}, logo_displayer(::Sseu::TexSource::tex_ids["logo"], 128.0, 128.0, &::Sseu::FuncSource::null_updater, 512.0, 512.0) { }
MainActivity::~MainActivity() {
    // ::Sseu::AudioSource::pause_audio();
}
void MainActivity::init() {
    ::Sseu::AudioSource::play_audio(::Sseu::AudioSource::audio_ids["fuuinsaresi_kamigami"]);

    ::glEnable(GL_DEPTH_TEST);
    ::glDepthFunc(GL_LEQUAL);

    ::glEnable(GL_BLEND);
    ::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ::glEnable(GL_SCISSOR_TEST);

    // ::glMatrixMode(GL_PROJECTION);
    // ::glLoadIdentity();
    // ::glOrtho(-::Sseu::wnd_width * 0.5, ::Sseu::wnd_width * 0.5, -::Sseu::wnd_height * 0.5, ::Sseu::wnd_height * 0.5, 0.0, 2.0);
    // ::glMatrixMode(GL_MODELVIEW);
    // ::glLoadIdentity();
    // ::gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

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

GameActivity::GameActivity(): is_exsisting{true}, is_suspending{false}, timestamp{::std::chrono::system_clock::now().time_since_epoch().count()}, event_timer(this), logo_displayer(::Sseu::TexSource::tex_ids["logo"], 128.0, 128.0, &::Sseu::FuncSource::null_updater, 800.0, 256.0), tzuihczi(::Sseu::TexSource::tex_ids["prigozin_on_plane"], 32.0, 32.0, &::Sseu::FuncSource::null_updater, 256.0, 256.0, false), boss(::Sseu::TexSource::tex_ids["zelensikij"], 128.0, 64.0, &::Sseu::FuncSource::game_activity_boss_updater, 256.0, 512.0, false) {
    this->tzoiczi_list.emplace_back(::Sseu::TexSource::tex_ids["vagner"], 8.0, 8.0, &::Sseu::FuncSource::game_activity_tzoiczi_updater, M_PI_2, 0.0, &this->tzuihczi, -64.0, 0.0);
    this->tzoiczi_list.emplace_back(::Sseu::TexSource::tex_ids["vagner"], 8.0, 8.0, &::Sseu::FuncSource::game_activity_tzoiczi_updater, M_PI_2, 0.0, &this->tzuihczi, -32.0, 32.0);
    this->tzoiczi_list.emplace_back(::Sseu::TexSource::tex_ids["vagner"], 8.0, 8.0, &::Sseu::FuncSource::game_activity_tzoiczi_updater, M_PI_2, 0.0, &this->tzuihczi, 32.0, 32.0);
    this->tzoiczi_list.emplace_back(::Sseu::TexSource::tex_ids["vagner"], 8.0, 8.0, &::Sseu::FuncSource::game_activity_tzoiczi_updater, M_PI_2, 0.0, &this->tzuihczi, 64.0, 0.0);

    this->thr_list.emplace_back([this]() -> void {
        while (this->is_exsisting) {
            if (!this->is_suspending) {
                ::std::this_thread::sleep_for(::std::chrono::milliseconds(2048));
                double choice{double(::rand()) / RAND_MAX};
                if ((choice -= 0.35) < 0) {
                    for (unsigned int i{0U}; this->is_exsisting && i < 8U; ++i) {
                        ::std::this_thread::sleep_for(::std::chrono::milliseconds(256));
                        double x{this->boss.x + ::rand() % 128 - 64};
                        double y{this->boss.y + ::rand() % 128 - 64};
                        ::std::thread([this, x, y]() -> void {
                            for (unsigned int j{0U}; this->is_exsisting && j < 16U; ++j) {
                                ::std::this_thread::sleep_for(::std::chrono::milliseconds(64));
                                // this->bullet_list_mutex.lock();
                                // this->bullet_list.emplace_back(new ::OrientedQuadDisplayer(::Sseu::TexSource::tex_ids["ball_lightning_red"], 8.0, 8.0, &::Sseu::FuncSource::game_activity_diqdann_updater, x, y, ::atan2(this->tzuihczi.y - y, this->tzuihczi.x - x)));
                                // this->bullet_list_mutex.unlock();
                                this->diqdann_list.lock();
                                this->diqdann_list.emplace_back(new ::OrientedQuadDisplayer(::Sseu::TexSource::tex_ids["ball_lightning_red"], 8.0, 8.0, &::Sseu::FuncSource::game_activity_diqdann_updater, x, y, ::atan2(this->tzuihczi.y - y, this->tzuihczi.x - x)));
                                this->diqdann_list.unlock();
                            }
                        }).detach();
                    }
                } else if ((choice -= 0.35) < 0) {
                    for (unsigned int i{0U}; this->is_exsisting && i < 16U; ++i) {
                        ::std::this_thread::sleep_for(::std::chrono::milliseconds(64));
                        double theta{::atan2(this->tzuihczi.y - this->boss.y, this->tzuihczi.x - this->boss.x)};
                        // this->bullet_list_mutex.lock();
                        // this->bullet_list.emplace_back(new ::OrientedQuadDisplayer(::Sseu::TexSource::tex_ids["ball_lightning_purple"], 8.0, 8.0, &::Sseu::FuncSource::game_activity_diqdann_updater, this->boss.x, this->boss.y, theta - M_PI / 12));
                        // this->bullet_list.emplace_back(new ::OrientedQuadDisplayer(::Sseu::TexSource::tex_ids["ball_lightning_blue"], 8.0, 8.0, &::Sseu::FuncSource::game_activity_diqdann_updater, this->boss.x, this->boss.y, theta));
                        // this->bullet_list.emplace_back(new ::OrientedQuadDisplayer(::Sseu::TexSource::tex_ids["ball_lightning_cyan"], 8.0, 8.0, &::Sseu::FuncSource::game_activity_diqdann_updater, this->boss.x, this->boss.y, theta + M_PI / 12));
                        // this->bullet_list_mutex.unlock();
                        this->diqdann_list.lock();
                        this->diqdann_list.emplace_back(new ::OrientedQuadDisplayer(::Sseu::TexSource::tex_ids["ball_lightning_purple"], 8.0, 8.0, &::Sseu::FuncSource::game_activity_diqdann_updater, this->boss.x, this->boss.y, theta - M_PI / 12));
                        this->diqdann_list.emplace_back(new ::OrientedQuadDisplayer(::Sseu::TexSource::tex_ids["ball_lightning_blue"], 8.0, 8.0, &::Sseu::FuncSource::game_activity_diqdann_updater, this->boss.x, this->boss.y, theta));
                        this->diqdann_list.emplace_back(new ::OrientedQuadDisplayer(::Sseu::TexSource::tex_ids["ball_lightning_cyan"], 8.0, 8.0, &::Sseu::FuncSource::game_activity_diqdann_updater, this->boss.x, this->boss.y, theta + M_PI / 12));
                        this->diqdann_list.unlock();
                    }
                } else if ((choice -= 0.3) < 0) {
                    for (unsigned int i{0U}; this->is_exsisting && i < 32U; ++i) {
                        ::std::this_thread::sleep_for(::std::chrono::milliseconds(512));
                        for (int j{0}; this->is_exsisting && j < 8; ++j) {
                            double line_y(j * 128 - 384);
                            // this->bullet_list_mutex.lock();
                            // this->bullet_list.emplace_back(new ::OrientedQuadDisplayer(::Sseu::TexSource::tex_ids["ball_lightning_green"], 8.0, 8.0, &::Sseu::FuncSource::game_activity_diqdann_1_updater, 0.0, line_y, 0));
                            // this->bullet_list.emplace_back(new ::OrientedQuadDisplayer(::Sseu::TexSource::tex_ids["ball_lightning_green"], 8.0, 8.0, &::Sseu::FuncSource::game_activity_diqdann_1_updater, ::Sseu::vp_width, line_y + 64, M_PI));
                            // this->bullet_list_mutex.unlock();
                            this->diqdann_list.lock();
                            this->diqdann_list.emplace_back(new ::OrientedQuadDisplayer(::Sseu::TexSource::tex_ids["ball_lightning_green"], 8.0, 8.0, &::Sseu::FuncSource::game_activity_diqdann_updater_1, 0.0, line_y, 0));
                            this->diqdann_list.emplace_back(new ::OrientedQuadDisplayer(::Sseu::TexSource::tex_ids["ball_lightning_green"], 8.0, 8.0, &::Sseu::FuncSource::game_activity_diqdann_updater_1, ::Sseu::vp_width, line_y + 64, M_PI));
                            this->diqdann_list.unlock();
                        }
                    }
                }
            }
        }
    });
    // ::std::thread([this]() -> {
        
    // }).detach();
    this->event_timer.emplace(1024, &::Sseu::FuncSource::game_activity_diqczi_eventer);
}
GameActivity::~GameActivity() {
    this->is_exsisting = false;
    for (::std::vector<::std::thread>::iterator thr(this->thr_list.begin()); thr != this->thr_list.end(); ++thr) {
// ::std::cout << thr.base() << '\t';
        thr->join();
// ::std::cout << thr->joinable() << '\n';
    }
// ::std::cout << this->thr_list.size() << '\n';
    // ::Sseu::AudioSource::pause_audio(::Sseu::AudioSource::audio_ids["sluziti_rossii"]);
// ::std::cout << this->fps_displayer.is_counting << '\n';
    // ::Sseu::AudioSource::pause_audio(::Sseu::AudioSource::audio_ids["biu"]);
}
void GameActivity::init() {
    ::Sseu::AudioSource::play_audio(::Sseu::AudioSource::audio_ids["sluziti_rossii"]);

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

    ::Sseu::AudioSource::pause_audio(::Sseu::AudioSource::audio_ids["sluziti_rossii"]);
}
void GameActivity::update() {
    double duration{(::std::chrono::system_clock::now().time_since_epoch().count() - this->timestamp) * 1e-9};
    this->timestamp = ::std::chrono::system_clock::now().time_since_epoch().count();
    if (!this->is_suspending) {
        this->gamearea_background.update();
        // this->gamearea_background_offset += duration * 16;
        // while (this->gamearea_background_offset >= 256.0) {
        //     this->gamearea_background_offset -= 256.0;
        // }
        double tzuihczi_speed{this->tzuihczi.moving_speed * duration};
        if (this->key_state[::SDL_KeyCode::SDLK_UP]) {
            this->tzuihczi.y += tzuihczi_speed;
        } else if (this->key_state[::SDL_KeyCode::SDLK_DOWN]) {
            this->tzuihczi.y -= tzuihczi_speed;
        }
        if (this->key_state[::SDL_KeyCode::SDLK_LEFT]) {
            this->tzuihczi.is_mirrored = true;
            this->tzuihczi.x -= tzuihczi_speed;
        } else if (this->key_state[::SDL_KeyCode::SDLK_RIGHT]) {
            this->tzuihczi.is_mirrored = false;
            this->tzuihczi.x += tzuihczi_speed;
        }
        // if (this->key_state[::SDL_KeyCode::SDLK_z]) {
        //     this->bullet_list_mutex.lock();
        //     this->bullet_list.emplace_back(new ::OrientedQuadDisplayer(::Sseu::TexSource::tex_ids[::rand() * 2 < RAND_MAX ? "shoigu" : "gerasimov"], 16.0, 16.0, &::Sseu::FuncSource::game_activity_tzuihdann_updater, this->tzuihczi.x, this->tzuihczi.y, M_PI_2));
        //     this->bullet_list_mutex.unlock();
        // }
        for (::std::vector<::TzoicziDisplayer>::iterator tzoiczi(this->tzoiczi_list.begin()); tzoiczi != this->tzoiczi_list.end(); ++tzoiczi) {
            tzoiczi->update();
        }
        for (::QuadDisplayer *diqczi : this->diqczi_list) {
            diqczi->update();
        }
        // this->bullet_list_mutex.lock();
        // for (::std::vector<::QuadDisplayer *>::iterator bullet(this->bullet_list.begin()); bullet != this->bullet_list.end(); ) {
        //     (*bullet)->update();
        //     if (!this->tzuihczi.is_injury_free && ::Sseu::FuncSource::calc_norm((*bullet)->x - this->tzuihczi.x, (*bullet)->y - this->tzuihczi.y) < (*bullet)->half_width + 4) {
        //         this->tzuihczi.is_injury_free = true;
        //         ::std::thread([this]() -> void {
        //             ::std::this_thread::sleep_for(::std::chrono::milliseconds(4096));
        //             this->tzuihczi.is_injury_free = false;
        //         }).detach();
        //         ::Sseu::AudioSource::play_audio(::Sseu::AudioSource::audio_ids["biu"]);
        //         ::std::thread([]() -> void {
        //             ::std::this_thread::sleep_for(::std::chrono::milliseconds(2048));
        //             ::Sseu::AudioSource::pause_audio(::Sseu::AudioSource::audio_ids["biu"]);
        //         }).detach();
        //         ::std::cout << "Bay!" << *bullet << '\n';
        //     }
        //     if ((*bullet)->x < 0.0 || (*bullet)->x > ::Sseu::vp_width || (*bullet)->y < 0.0 || (*bullet)->y > ::Sseu::vp_height) {
        //         delete *bullet;
        //         this->bullet_list.erase(bullet);
        //     } else {
        //         ++bullet;
        //     }
        // }
        // this->bullet_list_mutex.unlock();
        this->tzuihdann_list.lock();
        for (::std::vector<::QuadDisplayer *>::iterator tzuihdann(this->tzuihdann_list.begin()); tzuihdann != this->tzuihdann_list.end(); ) {
            (*tzuihdann)->update();
            if ((*tzuihdann)->x < 0.0 || (*tzuihdann)->x > ::Sseu::vp_width || (*tzuihdann)->y < 0.0 || (*tzuihdann)->y > ::Sseu::vp_height) {
                delete *tzuihdann;
                this->tzuihdann_list.erase(tzuihdann);
            } else {
                ++tzuihdann;
            }
        }
        this->tzuihdann_list.unlock();
        this->diqdann_list.lock();
        for (::std::vector<::QuadDisplayer *>::iterator diqdann(this->diqdann_list.begin()); diqdann != this->diqdann_list.end(); ) {
            (*diqdann)->update();
            if (!this->tzuihczi.is_injury_free && ::Sseu::FuncSource::calc_norm((*diqdann)->x - this->tzuihczi.x, (*diqdann)->y - this->tzuihczi.y) < (*diqdann)->half_width + 4) {
                this->tzuihczi.is_injury_free = true;
                ::std::thread([this]() -> void {
                    ::std::this_thread::sleep_for(::std::chrono::milliseconds(4096));
                    this->tzuihczi.is_injury_free = false;
                }).detach();
                ::Sseu::AudioSource::play_audio(::Sseu::AudioSource::audio_ids["biu"]);
                ::std::thread([]() -> void {
                    ::std::this_thread::sleep_for(::std::chrono::milliseconds(2048));
                    ::Sseu::AudioSource::pause_audio(::Sseu::AudioSource::audio_ids["biu"]);
                }).detach();
                ::std::cout << "Bay!" << *diqdann << '\n';
            }
            if ((*diqdann)->x < 0.0 || (*diqdann)->x > ::Sseu::vp_width || (*diqdann)->y < 0.0 || (*diqdann)->y > ::Sseu::vp_height) {
                delete *diqdann;
                this->diqdann_list.erase(diqdann);
            } else {
                ++diqdann;
            }
        }
        this->diqdann_list.unlock();
        this->event_timer.procedure();
    }
// ::std::cout << __LINE__ << ' ' << this->diqczi_list.size() << '\n';

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

    // ::Sseu::set_viewport(64, 64, 512, 640);
    // // ::glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
    // // ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // // ::glClear(GL_DEPTH_BUFFER_BIT);
    // ::Sseu::set_base_projection();
    // // ::Sseu::set_base_modelview();
    // this->display_gamearea_box();
    ::Sseu::set_viewport(64, 64, 512, 640);
    ::glEnable(GL_TEXTURE_2D);
    ::glClear(GL_DEPTH_BUFFER_BIT);
    this->gamearea_background.display();
    // this->display_gamearea_background();
    // ::glColor3ub(0xff, 0xff, 0xff);
    this->tzuihczi.display();
    for (::std::vector<::TzoicziDisplayer>::iterator tzoiczi(this->tzoiczi_list.begin()); tzoiczi != this->tzoiczi_list.end(); ++tzoiczi) {
        tzoiczi->display();
    }
    this->boss.display();
// ::std::cout << __LINE__ << '\n';
    for (::QuadDisplayer *diqczi : this->diqczi_list) {
        diqczi->display();
    }
// ::std::cout << __LINE__ << '\n';
    this->diqdann_list.lock();
    for (::QuadDisplayer *tzuihdann : this->tzuihdann_list) {
        tzuihdann->display();
    }
    for (::QuadDisplayer *diqdann : this->diqdann_list) {
        diqdann->display();
    }
    this->diqdann_list.unlock();
    this->tzuihczi.display_judge_point();
    ::glDisable(GL_TEXTURE_2D);

    if (this->is_suspending) {
        this->display_suspending_curtain();
    }

    ::SDL_GL_SwapWindow(::Sseu::window);
}
void GameActivity::procedure(::SDL_Event const event) {
    switch (event.type) {
        case ::SDL_EventType::SDL_KEYDOWN: {
            // this->key_down[event.key.keysym.sym] = !this->key_state[event.key.keysym.sym];
            // this->key_up[event.key.keysym.sym] = false;
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
// ::std::cout << "__LINE__" << __LINE__ << '\n';
                                ::Sseu::pop_activity();
// ::std::cout << "__LINE__" << __LINE__ << '\n';
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
                        this->tzuihczi.moving_speed = 64.0;
                        this->tzoiczi_list[0].offset_x = -32.0;
                        this->tzoiczi_list[1].offset_x = -16.0;
                        this->tzoiczi_list[1].offset_y = -16.0;
                        this->tzoiczi_list[2].offset_x = 16.0;
                        this->tzoiczi_list[2].offset_y = -16.0;
                        this->tzoiczi_list[3].offset_x = 32.0;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_z: {
                        if (!this->tzuihczi.is_shooting) {
                            this->tzuihczi.is_shooting = true;
                            this->tzuihczi.shooting_thr = ::std::thread([this]() {
                                while (this->tzuihczi.is_shooting) {
                                    this->tzuihdann_list.lock();
                                    this->tzuihdann_list.emplace_back(new ::OrientedQuadDisplayer(::Sseu::TexSource::tex_ids[::rand() * 2 < RAND_MAX ? "shoigu" : "gerasimov"], 16.0, 16.0, &::Sseu::FuncSource::game_activity_tzuihdann_updater, this->tzuihczi.x, this->tzuihczi.y, M_PI_2));
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
            // this->key_down[event.key.keysym.sym] = false;
            // this->key_up[event.key.keysym.sym] = this->key_state[event.key.keysym.sym];
            this->key_state[event.key.keysym.sym] = false;
            if (!this->is_suspending) {
                switch (event.key.keysym.sym) {
                    case ::SDL_KeyCode::SDLK_LSHIFT: case ::SDL_KeyCode::SDLK_RSHIFT: {
                        this->tzuihczi.moving_speed = 256.0;
                        this->tzoiczi_list[0].offset_x = -64.0;
                        this->tzoiczi_list[1].offset_x = -32.0;
                        this->tzoiczi_list[1].offset_y = 32.0;
                        this->tzoiczi_list[2].offset_x = 32.0;
                        this->tzoiczi_list[2].offset_y = 32.0;
                        this->tzoiczi_list[3].offset_x = 64.0;
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
    // ::glMatrixMode(GL_PROJECTION);
    // ::glLoadIdentity();
    // ::glFrustum(-0.125, 0.125, -0.09375, 0.09375, 0.0625, 1024.0);
    // // ::glMatrixMode(GL_MODELVIEW);
    // // ::glLoadIdentity();
    // // ::gluLookAt(-64.0, -256.0, 64.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    // // ::Sseu::set_base_modelview();
    // ::glPushMatrix();
    // ::glTranslatef(0.0F, 0.0F, -256.0F);
    // // static double rotation{0.0};
    // // ::GetAsyncKeyState(VK_SPACE) && ++rotation && ::std::cout << rotation << '\n';
    // ::glRotatef(-75.0F, 1.0F, 0.0F, 0.0F);
    // ::glRotatef(15.0F, 0.0F, 0.0F, 1.0F);
    // // ::glRotatef(-67.5F, 1.0F, -::tanf(M_PI / 12), 0.0F);
    // // ::glRotatef(-67.5F, ::sqrtf(3.0F), 1.0F, 0.0F);
    // // ::glEnable(GL_TEXTURE_2D);
    // ::glColor3ub(0xff, 0xff, 0xff);
    // ::glBindTexture(GL_TEXTURE_2D, ::Sseu::TexSource::tex_ids["wheat_field"]);
    // ::glBegin(GL_QUADS);
    // for (int i{-2}; i < 8; ++i) {
    //     for (int j{-4}; j < 8; ++j) {
    //         ::glTexCoord2i(0, 1);
    //         ::glVertex2d(j * 256 - this->gamearea_background_offset, i * 128 - this->gamearea_background_offset);
    //         ::glTexCoord2i(0, 0);
    //         ::glVertex2d(j * 256 - this->gamearea_background_offset, (i + 1) * 128 - this->gamearea_background_offset);
    //         ::glTexCoord2i(1, 0);
    //         ::glVertex2d((j + 1) * 256 - this->gamearea_background_offset, (i + 1) * 128 - this->gamearea_background_offset);
    //         ::glTexCoord2i(1, 1);
    //         ::glVertex2d((j + 1) * 256 - this->gamearea_background_offset, i * 128 - this->gamearea_background_offset);
    //     }
    // }
    // ::glEnd();
    // // ::glDisable(GL_TEXTURE_2D);
    // ::glPopMatrix();
    // ::Sseu::set_base_projection();
    // // ::Sseu::set_base_modelview();
    // ::glBindTexture(GL_TEXTURE_2D, ::Sseu::TexSource::tex_ids["blue_sky"]);
    // ::glBegin(GL_QUADS);
    // ::glTexCoord2i(0, 1);
    // ::glVertex2i(0, 352);
    // ::glTexCoord2i(0, 0);
    // ::glVertex2i(0, 864);
    // ::glTexCoord2i(1, 0);
    // ::glVertex2i(512, 864);
    // ::glTexCoord2i(1, 1);
    // ::glVertex2i(512, 352);
    // ::glEnd();
}
void GameActivity::display_gamearea_box() {
// ::std::cout << ::Sseu::vp_width << ' ' << ::Sseu::vp_height << '\n';
    // ::glColor3ub(0x00, 0x00, 0x00);
    // ::glBegin(GL_QUADS);
    // ::glVertex2i(0, 0);
    // ::glVertex2i(0, ::Sseu::vp_height - 0);
    // ::glVertex2i(::Sseu::vp_width - 0, ::Sseu::vp_height - 0);
    // ::glVertex2i(::Sseu::vp_width - 0, 0);
    // ::glEnd();
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
    // ::Sseu::set_viewport(0, 0, ::Sseu::wnd_width, ::Sseu::wnd_height);
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
// try{
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
// }catch(::std::exception const &e){::std::cout<<"here:"<<'\n'<<e.what()<<'\n';}
    return 0;
}

#endif
