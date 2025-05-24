// compile command:
// cd D:\Sseu\Tryingssiuh\Ssianxmuh\_230515_STGs\_230824_STG
// g++ -Ofast -o 東綫ПРОЖЕКТ.exe 東綫ПРОЖЕКТ.cpp -Llib -lfreeglut -lglu32 -lopengl32 -lSDL2; .\東綫ПРОЖЕКТ
// g++ -Ofast -o ToukenProject.exe ToukenProject.cpp -Llib -lfreeglut -lglu32 -lopengl32 -lSDL2; .\ToukenProject

#ifndef STG_CPP

#include "./FuncDefinationData.hpp"

Updater::Updater(unsigned int duration_from_base, void (*update_func)(void *)): setting_duration{duration_from_base}, update_func{update_func} { }
void Updater::update() {
    (*this->update_func)(this);
}

QuadDisplayer::QuadDisplayer(unsigned int duration_from_base, void (*update_func)(void *), unsigned int tex_id, double x, double y, double half_width, double half_height): ::Updater::Updater(duration_from_base, update_func), tex_id{tex_id}, x{x}, y{y}, half_width{half_width}, half_height{half_height} { }
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

MirroredQuadDisplayer::MirroredQuadDisplayer(unsigned int duration_from_base, void (*update_func)(void *), unsigned int tex_id, double x, double y, double half_width, double half_height, bool is_hmirrored, bool is_vmirrored): ::QuadDisplayer::QuadDisplayer(duration_from_base, update_func, tex_id, x, y, half_width, half_height) {
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

RotatedQuadDisplayer::RotatedQuadDisplayer(unsigned int duration_from_base, void (*update_func)(void *), unsigned int tex_id, double x, double y, double half_width, double half_height, double phi, double theta): ::QuadDisplayer::QuadDisplayer(duration_from_base, update_func, tex_id, x, y, half_width, half_height) {
    this->lparam_map[::LparamUsage::LU_PHI].d = phi;
    this->lparam_map[::LparamUsage::LU_THETA].d = theta;
}
void RotatedQuadDisplayer::display() {
    double const vp_half_height{this->half_height * ::sin(this->lparam_map[::LparamUsage::LU_PHI].d)};
    ::glPushMatrix();
    ::glTranslated(this->x, this->y, 0.0);
    ::glRotated(this->lparam_map[::LparamUsage::LU_THETA].d * M_1_PI * 180, 0.0, 0.0, 1.0);
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

RectDisplayer::RectDisplayer(unsigned int duration_from_base, void (*update_func)(void *), unsigned int tex_id, double x, double y, double half_width, double half_height, double rotation): ::Updater::Updater(duration_from_base, update_func), tex_id{tex_id}, x{x}, y{y}, half_width{half_width}, half_height{half_height}, rotation{rotation} { }
void RectDisplayer::display() {
    ::glPushMatrix();
    ::glTranslated(this->x, this->y, 0.0);
    ::glRotated(this->rotation * M_1_PI * 180, 0.0, 0.0, 1.0);
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

SelectionDisplayer::SelectionDisplayer(unsigned int duration_from_base, void (*update_func)(void *)): ::Updater::Updater(duration_from_base, update_func), selected{0U} { }
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
    // for (int i{-2}; i < 8; ++i) {
    //     for (int j{-4}; j < 8; ++j) {
    //         ::glTexCoord2i(0, 1);
    //         ::glVertex2d(j * 32, i * 16);
    //         ::glTexCoord2i(0, 0);
    //         ::glVertex2d(j * 32, i * 16 + 16);
    //         ::glTexCoord2i(1, 0);
    //         ::glVertex2d(j * 32 + 32, i * 16 + 16);
    //         ::glTexCoord2i(1, 1);
    //         ::glVertex2d(j * 32 + 32, i * 16);
    //     }
    // }
    ::glEnd();
    ::glPopMatrix();
    ::Sseu::set_base_projection();
    ::Sseu::set_base_modelview();
    ::glBindTexture(GL_TEXTURE_2D, ::TexSource::tex_ids["blue_sky"]);
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
void GameareaDisplayer::update(const unsigned int duration) {
    this->process += duration * 0.015625;
}

InfoDisplayer::InfoDisplayer(): hi_score{0U}, score{0U}, player{2U}, power{0U}, graze{0U}, target_score{0U}, target_power{400U} { }
void InfoDisplayer::display() {
    char hi_score_text[11]{}, score_text[11]{};
    this->get_padded_score(this->hi_score, hi_score_text);
    this->get_padded_score(this->score, score_text);
    ::glPushMatrix();
    ::glTranslatef(640.0F, 640.0F, 0.0F);
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

TimedEvent::TimedEvent(const unsigned int duration, void (*event_func)(::std::unordered_map<::LparamUsage, ::Lparam> *)): duration{duration}, event_func{event_func} { }

Timer::Timer(): base_time(::std::chrono::system_clock::now()), curr_time{::std::chrono::system_clock::now()}, prev_time{this->curr_time}, susp_time{this->base_time}, duration_from_base{0U}, duration_from_prev{0U}, duration_suspending{0U}, duration_suspending_prev{0U} { }
void Timer::prepare(::TimedEvent event) {
    this->prepared_event_list.push_back(event);
}
void Timer::procedure() {
    this->timed_event_list.insert(this->timed_event_list.end(), this->prepared_event_list.rbegin(), this->prepared_event_list.rend());
    this->prepared_event_list.clear();
    for (::std::vector<::TimedEvent>::iterator event(this->timed_event_list.begin()); event != this->timed_event_list.end(); ) {
        if (this->duration_from_base >= event->duration) {
            (*event->event_func)(&event->lparam_map);
            event = this->timed_event_list.erase(event);
        } else {
            ++event;
        }
    }
}
void Timer::update() {
    this->prev_time = this->curr_time;
    this->curr_time = ::std::chrono::system_clock::now();
    this->duration_from_base = ((this->curr_time - this->base_time).count() >> 20) - this->duration_suspending_prev - this->duration_suspending;
    if (this->susp_time > this->base_time) {
        this->duration_from_prev = 0U;
        this->duration_suspending = (this->curr_time - this->susp_time).count() >> 20;
    } else {
        this->duration_from_prev = (this->curr_time - this->prev_time).count() >> 20;
    }
}
void Timer::pause() {
    this->susp_time = ::std::chrono::system_clock::now();
}
void Timer::resume() {
    this->duration_suspending_prev += this->duration_suspending;
    this->susp_time = this->base_time;
    this->duration_suspending = 0;
}

LaunchActivity::LaunchActivity(): logo_sseu(0U, &::FuncSource::General::null_updater, ::TexSource::tex_ids["logo_sseu"], 512.0, 384.0, 316.0, 116.0), alpha{0xffU}, should_quit{false} { }
LaunchActivity::~LaunchActivity() { }
void LaunchActivity::init() {
    ::glEnable(GL_DEPTH_TEST);
    ::glDepthFunc(GL_LEQUAL);

    ::glEnable(GL_BLEND);
    ::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ::glEnable(GL_SCISSOR_TEST);

    ::Sseu::set_viewport(0, 0, ::Sseu::wnd_width, ::Sseu::wnd_height);
    ::Sseu::set_base_projection();
    ::Sseu::set_base_modelview();
}
void LaunchActivity::quit() { }
void LaunchActivity::update() {
    if (this->should_quit) {
        ::Sseu::pop_activity();
        return;
    }
    this->logo_sseu.update();
    if (this->timer.duration_from_base < 4000) {
        const double process{this->timer.duration_from_base * 500e-6 - 1};
        this->alpha = process * process * 0xff;
    } else {
        this->should_quit = true;
        ::Sseu::push_activity<::MainActivity>();
    }

    ::glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
    ::glEnable(GL_TEXTURE_2D);
    ::glColor3ub(0xff, 0xff, 0xff);
    this->logo_sseu.display();
    ::glDisable(GL_TEXTURE_2D);
    ::glBegin(GL_QUADS);
    ::glColor4ub(0x00F, 0x00F, 0x00F, this->alpha);
    ::glVertex2i(0, 0);
    ::glVertex2i(0, ::Sseu::wnd_height);
    ::glVertex2i(::Sseu::wnd_width, ::Sseu::wnd_height);
    ::glVertex2i(::Sseu::wnd_width, 0);
    ::glEnd();

    ::SDL_GL_SwapWindow(::Sseu::window);
    this->timer.procedure();
    ::std::this_thread::sleep_until(this->timer.curr_time + ::std::chrono::milliseconds(16));
    this->timer.update();
}
void LaunchActivity::procedure(const ::SDL_Event) { }

MainActivity::MainActivity(): logo_displayer(0U, &::FuncSource::General::null_updater, ::TexSource::tex_ids["logo"], 512.0, 1024.0, 128.0, 128.0), selection_displayer(0U, &::FuncSource::General::null_updater), bgm_player(::AudioSource::audio_ids["fuuinsaresi_kamigami"]) { }
MainActivity::~MainActivity() { }
void MainActivity::init() {
    this->bgm_player.play();

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

    this->logo_displayer.setting_duration = this->timer.duration_from_base;
    this->logo_displayer.update_func = &::FuncSource::MainActivity::updater_smooth;
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

    this->bgm_player.pause();
}
void MainActivity::update() {
    this->logo_displayer.update();
    this->selection_displayer.update();
    for (::std::vector<::RotatedQuadDisplayer *>::iterator zzingxua(this->zzingxua_list.begin()); zzingxua != this->zzingxua_list.end(); ) {
        (*zzingxua)->update();
        if ((*zzingxua)->x > ::Sseu::vp_width + 128.0 || (*zzingxua)->y < -128.0) {
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
    this->display_background();
    this->logo_displayer.display();
    this->selection_displayer.display();
    this->fps_displayer.display();
    for (::RotatedQuadDisplayer *zzingxua : this->zzingxua_list) {
        zzingxua->display();
    }
    ::glDisable(GL_TEXTURE_2D);

    ::SDL_GL_SwapWindow(::Sseu::window);
    this->timer.procedure();
    ::std::this_thread::sleep_until(this->timer.curr_time + ::std::chrono::milliseconds(16));
    this->timer.update();
}
void MainActivity::procedure(::SDL_Event const event) {
    switch (event.type) {
        case ::SDL_EventType::SDL_KEYDOWN: {
            if (this->is_selection_hiden) {
                if (this->has_animation_completed) {
                    this->is_selection_hiden = false;
                    this->has_animation_completed = false;

                    this->logo_displayer.setting_duration = this->timer.duration_from_base;
                    this->logo_displayer.update_func = &::FuncSource::MainActivity::updater_smooth;
                    this->logo_displayer.lparam_map[::LparamUsage::LU_SETX].d = 512.0;
                    this->logo_displayer.lparam_map[::LparamUsage::LU_SETY].d = 384.0;
                    this->logo_displayer.lparam_map[::LparamUsage::LU_DX].d = -256.0;
                    this->logo_displayer.lparam_map[::LparamUsage::LU_DY].d = 0.0;

                    this->selection_displayer.setting_duration = this->timer.duration_from_base;
                    this->selection_displayer.update_func = &::FuncSource::MainActivity::updater_smooth;
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
                                ::Sseu::push_activity<::GameActivity>();
                                break;
                            }
                            case 1U: {
                                ::AudioSource::play_audio_once(::AudioSource::audio_ids["option_quit"]);
                                ::Sseu::pop_activity();
                                break;
                            }
                        }
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_ESCAPE: {
                        ::AudioSource::play_audio_once(::AudioSource::audio_ids["option_quit"]);
                        this->selection_displayer.selected = 1U;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_UP: case ::SDL_KeyCode::SDLK_RIGHT: {
                        ::AudioSource::play_audio_once(::AudioSource::audio_ids["option_change"]);
                        ++this->selection_displayer.selected %= 2U;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_DOWN: case ::SDL_KeyCode::SDLK_LEFT: {
                        ::AudioSource::play_audio_once(::AudioSource::audio_ids["option_change"]);
                        --this->selection_displayer.selected %= 2U;
                        break;
                    }
                }
            }
            break;
        }
    }
}
void MainActivity::display_background() {
    ::glBindTexture(GL_TEXTURE_2D, ::TexSource::tex_ids["reimu_gunpuku"]);
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
void MainActivity::generate_zzingxua() {
    if (this->zzingxua_list.size() < 32ULL) {
        const unsigned int tex_id{::TexSource::tex_ids[::rand() * 8 < RAND_MAX ? "ssiauzzian" : "zzingxua"]};
        const double start_x{::rand() * ::Sseu::vp_width * 2.0 / RAND_MAX - ::Sseu::vp_width};
        const double start_y{(start_x / ::Sseu::vp_width + 1.0) * ::Sseu::vp_height};
        const double half_size{::rand() * 6.0 / RAND_MAX + 2.0};
        ::RotatedQuadDisplayer *zzingxua{new ::RotatedQuadDisplayer(this->timer.duration_from_base, &::FuncSource::MainActivity::updater_zzingxua, tex_id, start_x, start_y, half_size, half_size, M_PI_2, 0.0)};
        zzingxua->lparam_map[::LparamUsage::LU_DX].d = ::rand() * 256e-3 / RAND_MAX;
        zzingxua->lparam_map[::LparamUsage::LU_DY].d = -::rand() * 256e-3 / RAND_MAX;
        this->zzingxua_list.push_back(zzingxua);
    }
}

GameActivity::GameActivity(): is_suspending{false}, event_updater{nullptr}, logo_displayer(0U, &::FuncSource::General::null_updater, ::TexSource::tex_ids["logo"], 800.0, 256.0, 128.0, 128.0), tzuihczi(0U, &::FuncSource::Characters::updater_tzuihczi, ::TexSource::tex_ids["prigozin_on_plane"], 256.0, 256.0, 32.0, 32.0, false, false), boss{nullptr}, bgm_player{new ::AudioSource::AudioPlayer(::AudioSource::audio_ids["harudomanno_youkai_shoujo"])}, shooting_sound_player(::AudioSource::audio_ids["shooting_sound"]), selected{0U} {
// GameActivity::GameActivity(): is_suspending{false}, event_updater{nullptr}, logo_displayer(0U, &::FuncSource::General::null_updater, ::TexSource::tex_ids["logo"], 800.0, 256.0, 128.0, 128.0), tzuihczi(0U, &::FuncSource::Characters::updater_tzuihczi, ::TexSource::tex_ids["prigozin_on_plane"], 256.0, 256.0, 32.0, 32.0, false, false), boss(0U, &::FuncSource::Characters::updater_boss, ::TexSource::tex_ids["zelensikij"], 256.0, 768.0, 128.0, 64.0, false, false), bgm_player{new ::AudioSource::AudioPlayer(::AudioSource::audio_ids["harudomanno_youkai_shoujo"])}, shooting_sound_player(::AudioSource::audio_ids["shooting_sound"]), selected{0U} {
    int *tzoiczi_offset_list{new int[60]{
        0, 64,
        -64, 0, 64, 0,
        -55, 32, 0, -64, 55, 32,
        -64, 0, -32, 32, 32, 32, 64, 0,
        -64, 0, -32, 32, 0, -32, 32, 32, 64, 0,
        0, -32,
        -32, -32, 32, -32,
        -28, -16, 0, 32, 28, -16,
        -32, 0, -16, -16, 16, -16, 32, 0,
        -32, 0, -16, -16, 0, 16, 16, -16, 32, 0
    }};
    this->tzuihczi.lparam_map[::LparamUsage::LU_APPENDAGE].p = &this->tzoiczi_list;
    this->tzuihczi.lparam_map[::LparamUsage::LU_LIST].p = new int *[6]{tzoiczi_offset_list, tzoiczi_offset_list, tzoiczi_offset_list + 2, tzoiczi_offset_list + 6, tzoiczi_offset_list + 12, tzoiczi_offset_list + 20};
    // this->tzoiczi_list.emplace_back(this->timer.duration_from_base, &::FuncSource::Characters::updater_tzoiczi, ::TexSource::tex_ids["vagner"], this->tzuihczi.x, this->tzuihczi.y, 8.0, 8.0, M_PI_2, 0.0);
    // this->tzoiczi_list.back().lparam_map[::LparamUsage::LU_TARGET].p = &this->tzuihczi;
    // this->tzoiczi_list.back().lparam_map[::LparamUsage::LU_DX].d = -64.0;
    // this->tzoiczi_list.back().lparam_map[::LparamUsage::LU_DY].d = 0.0;
    // this->tzoiczi_list.emplace_back(this->timer.duration_from_base, &::FuncSource::Characters::updater_tzoiczi, ::TexSource::tex_ids["vagner"], this->tzuihczi.x, this->tzuihczi.y, 8.0, 8.0, M_PI_2, 0.0);
    // this->tzoiczi_list.back().lparam_map[::LparamUsage::LU_TARGET].p = &this->tzuihczi;
    // this->tzoiczi_list.back().lparam_map[::LparamUsage::LU_DX].d = -32.0;
    // this->tzoiczi_list.back().lparam_map[::LparamUsage::LU_DY].d = 32.0;
    // this->tzoiczi_list.emplace_back(this->timer.duration_from_base, &::FuncSource::Characters::updater_tzoiczi, ::TexSource::tex_ids["vagner"], this->tzuihczi.x, this->tzuihczi.y, 8.0, 8.0, M_PI_2, 0.0);
    // this->tzoiczi_list.back().lparam_map[::LparamUsage::LU_TARGET].p = &this->tzuihczi;
    // this->tzoiczi_list.back().lparam_map[::LparamUsage::LU_DX].d = 32.0;
    // this->tzoiczi_list.back().lparam_map[::LparamUsage::LU_DY].d = 32.0;
    // this->tzoiczi_list.emplace_back(this->timer.duration_from_base, &::FuncSource::Characters::updater_tzoiczi, ::TexSource::tex_ids["vagner"], this->tzuihczi.x, this->tzuihczi.y, 8.0, 8.0, M_PI_2, 0.0);
    // this->tzoiczi_list.back().lparam_map[::LparamUsage::LU_TARGET].p = &this->tzuihczi;
    // this->tzoiczi_list.back().lparam_map[::LparamUsage::LU_DX].d = 64.0;
    // this->tzoiczi_list.back().lparam_map[::LparamUsage::LU_DY].d = 0.0;

    this->timer.prepare(::TimedEvent(2048, &::FuncSource::Gungczi_0::eventer_init));
    // this->timer.prepare(::TimedEvent(512, &::FuncSource::Gungczi_Test::eventer_init));
}
GameActivity::~GameActivity() {
    int **tzoiczi_offset_list{static_cast<int **>(this->tzuihczi.lparam_map[::LparamUsage::LU_LIST].p)};
    delete[] *tzoiczi_offset_list;
    delete[] tzoiczi_offset_list;
    // this->is_exsisting = false;
    for (::RotatedQuadDisplayer *tzoiczi : this->tzoiczi_list) {
        delete tzoiczi;
    }
    for (::QuadDisplayer *diqczi : this->diqczi_list) {
        delete diqczi;
    }
    for (::QuadDisplayer *tzuihdann : this->tzuihdann_list) {
        delete tzuihdann;
    }
    for (::QuadDisplayer *diqdann : this->diqdann_list) {
        delete diqdann;
    }
    for (::Updater *diqczi : this->removed_updater_list) {
        delete diqczi;
    }
}
void GameActivity::init() {
    this->bgm_player->play();

    ::glEnable(GL_DEPTH_TEST);
    ::glDepthFunc(GL_LEQUAL);

    ::glEnable(GL_BLEND);
    ::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ::glEnable(GL_SCISSOR_TEST);

    // ::glMatrixMode(GL_MODELVIEW);
    // ::glLoadIdentity();
    // ::gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    ::glPointSize(4.0F);

    this->fps_displayer.start_counting();
}
void GameActivity::quit() {
    this->fps_displayer.stop_counting();

    this->bgm_player->pause();
    this->bgm_player->offset = 0U;
}
void GameActivity::update() {
    this->info_displayer.update();
    if (this->event_updater != nullptr && this->updater_status[this->event_updater]) {
        this->event_updater->update();
    }
    this->gamearea.update(this->timer.duration_from_prev);
    for (::std::vector<::QuadDisplayer *>::iterator ssiaygoo(this->back_ssiaygoo_list.begin()); ssiaygoo != this->back_ssiaygoo_list.end(); ) {
        (*ssiaygoo)->update();
        if (!(*ssiaygoo)->lparam_map[::LparamUsage::LU_EXISTENCE].b) {
            delete *ssiaygoo;
            ssiaygoo = this->back_ssiaygoo_list.erase(ssiaygoo);
        } else {
            ++ssiaygoo;
        }
    }
    this->tzuihczi.update();
    for (::RotatedQuadDisplayer *tzoiczi : this->tzoiczi_list) {
        tzoiczi->update();
    }
    for (::std::vector<::QuadDisplayer *>::iterator diqczi(this->diqczi_list.begin()); diqczi != this->diqczi_list.end(); ) {
        (*diqczi)->update();
        if ((*diqczi)->lparam_map[::LparamUsage::LU_HEAL].ll <= 0 || (*diqczi)->x < -128.0 || (*diqczi)->x > ::Sseu::vp_width + 128.0 || (*diqczi)->y < -128.0 || (*diqczi)->y > ::Sseu::vp_height + 128.0) {
            ::QuadDisplayer *daycziuh{new ::QuadDisplayer(this->timer.duration_from_base, &::FuncSource::Stuffs::updater_daycziuh_explode, ::TexSource::tex_ids[::rand() * 2 < RAND_MAX ? "power_point" : "dean_point"], (*diqczi)->x, (*diqczi)->y, 8.0, 8.0)};
            double const theta{M_PI * 2 * ::rand() / RAND_MAX};
            double const distance{256.0 * ::rand() / RAND_MAX};
            daycziuh->lparam_map[::LparamUsage::LU_SETX].d = daycziuh->x;
            daycziuh->lparam_map[::LparamUsage::LU_SETY].d = daycziuh->y;
            daycziuh->lparam_map[::LparamUsage::LU_DX].d = ::std::min(::std::max(distance * ::cos(theta), -daycziuh->x), ::Sseu::vp_width - daycziuh->x);
            daycziuh->lparam_map[::LparamUsage::LU_DY].d = ::std::min(::std::max(distance * ::sin(theta), -daycziuh->y), ::Sseu::vp_height - daycziuh->y);
            daycziuh->lparam_map[::LparamUsage::LU_EFFECT].ull = daycziuh->tex_id == ::TexSource::tex_ids["power_point"] ? 0ULL : 1ULL;
            this->daycziuh_list.push_back(daycziuh);
            this->updater_status[daycziuh] = true;
            this->updater_status[*diqczi] = false;
            this->removed_updater_list.push_back(*diqczi);
            diqczi = this->diqczi_list.erase(diqczi);
        } else {
            ++diqczi;
        }
    }
    for (::std::vector<::QuadDisplayer *>::iterator tzuihdann(this->tzuihdann_list.begin()); tzuihdann != this->tzuihdann_list.end(); ) {
        (*tzuihdann)->update();
        ::std::vector<::QuadDisplayer *>::iterator diqczi(this->diqczi_list.begin());
        while (diqczi != this->diqczi_list.end() && ::FuncSource::General::calc_norm((*tzuihdann)->x - (*diqczi)->x, (*tzuihdann)->y - (*diqczi)->y) >= (*tzuihdann)->half_width + ::std::min((*diqczi)->half_width, (*diqczi)->half_height)) {
            ++diqczi;
        }
        if (diqczi != this->diqczi_list.end()) {
            this->updater_status[*tzuihdann] = false;
            delete *tzuihdann;
            tzuihdann = this->tzuihdann_list.erase(tzuihdann);
            --(*diqczi)->lparam_map[::LparamUsage::LU_HEAL].ll;
        } else if ((*tzuihdann)->x < -128.0 || (*tzuihdann)->x > ::Sseu::vp_width + 128.0 || (*tzuihdann)->y < -128.0 || (*tzuihdann)->y > ::Sseu::vp_height + 128.0) {
            this->updater_status[*tzuihdann] = false;
            delete *tzuihdann;
            tzuihdann = this->tzuihdann_list.erase(tzuihdann);
        } else {
            ++tzuihdann;
        }
    }
    for (::std::vector<::QuadDisplayer *>::iterator diqdann(this->diqdann_list.begin()); diqdann != this->diqdann_list.end(); ) {
        (*diqdann)->update();
        double const distance{::FuncSource::General::calc_norm((*diqdann)->x - this->tzuihczi.x, (*diqdann)->y - this->tzuihczi.y) - (*diqdann)->half_width};
        if (!(*diqdann)->lparam_map[::LparamUsage::LU_IS_GRAZED].b && distance < 16) {
            (*diqdann)->lparam_map[::LparamUsage::LU_IS_GRAZED].b = true;
            this->tzuihczi_graze((*diqdann)->x, (*diqdann)->y);
        }
        if (!this->tzuihczi.lparam_map[::LparamUsage::LU_IS_INJURY_FREE].b && distance < 0) {
            this->tzuihczi_miss();
            diqdann = this->diqdann_list.erase(diqdann);
        } else if ((*diqdann)->x < -128.0 || (*diqdann)->x > ::Sseu::vp_width + 128.0 || (*diqdann)->y < -128.0 || (*diqdann)->y > ::Sseu::vp_height + 128.0) {
            this->updater_status[*diqdann] = false;
            delete *diqdann;
            diqdann = this->diqdann_list.erase(diqdann);
        } else {
            ++diqdann;
        }
    }
    for (::std::vector<::RectDisplayer *>::iterator cziguang(this->cziguang_list.begin()); cziguang != this->cziguang_list.end(); ) {
        (*cziguang)->update();
        const double cos_rotation{::cos((*cziguang)->rotation)};
        const double sin_rotation{::sin((*cziguang)->rotation)};
        const double dx = this->tzuihczi.x - (*cziguang)->x;
        const double dy = this->tzuihczi.y - (*cziguang)->y;
        const double paral_diff{dy * cos_rotation - dx * sin_rotation};
        const double verti_diff{dx * cos_rotation + dy * sin_rotation};
        const double paral_dist{::fabs(paral_diff) - (*cziguang)->half_height};
        const double verti_dist{::fabs(verti_diff) - (*cziguang)->half_width};
        if (!(*cziguang)->lparam_map[::LparamUsage::LU_IS_GRAZED].b && paral_dist < 16 && verti_dist < 16) {
            // 這裏補上擦彈判定和碰撞判定，其中下面一句在擦彈中是需要的
            ::TimedEvent event(this->timer.duration_from_base + 256, &::FuncSource::Stuffs::eventer_cziguang_recover);
            event.lparam_map[::LparamUsage::LU_TARGET].p = *cziguang;
            this->timer.prepare(event);
            (*cziguang)->lparam_map[::LparamUsage::LU_IS_GRAZED].b = true;
            this->tzuihczi_graze((*cziguang)->x - paral_diff * sin_rotation, (*cziguang)->y + paral_diff * cos_rotation);
        }
        if (!this->tzuihczi.lparam_map[::LparamUsage::LU_IS_INJURY_FREE].b && paral_dist < 0 && verti_dist < 0) {
            this->tzuihczi_miss();
            // ::std::cout << "Collide cziguang\n";
        }
        if (!(*cziguang)->lparam_map[::LparamUsage::LU_EXISTENCE].b) {
            cziguang = this->cziguang_list.erase(cziguang);
        } else {
            ++cziguang;
        }
    }
    for (::std::vector<::QuadDisplayer *>::iterator daycziuh(this->daycziuh_list.begin()); daycziuh != this->daycziuh_list.end(); ) {
        (*daycziuh)->update();
        if (this->tzuihczi.y > 384) {
            (*daycziuh)->update_func = &::FuncSource::Stuffs::updater_daycziuh_catch;
        }
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
        (*ssiaygoo)->update();
        if (!(*ssiaygoo)->lparam_map[::LparamUsage::LU_EXISTENCE].b) {
            delete *ssiaygoo;
            ssiaygoo = this->ssiaygoo_list.erase(ssiaygoo);
        } else {
            ++ssiaygoo;
        }
    }

    ::Sseu::set_viewport(0, 0, ::Sseu::wnd_width, ::Sseu::wnd_height);
    ::Sseu::set_base_projection();
    ::Sseu::set_base_modelview();
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
    ::Sseu::set_base_projection();
    ::Sseu::set_base_modelview();
    ::glEnable(GL_TEXTURE_2D);
    ::glClear(GL_DEPTH_BUFFER_BIT);
    this->gamearea.display();

    for (::QuadDisplayer *ssiaygoo : this->back_ssiaygoo_list) {
        ssiaygoo->display();
    }
    if (!this->tzuihczi.lparam_map[::LparamUsage::LU_IS_INJURY_FREE].b || this->timer.duration_from_base % 512U >= 256U) {
        this->tzuihczi.display();
    }
    for (::RotatedQuadDisplayer *tzoiczi : this->tzoiczi_list) {
        tzoiczi->display();
    }
    for (::QuadDisplayer *diqczi : this->diqczi_list) {
        diqczi->display();
    }
    for (::QuadDisplayer *tzuihdann : this->tzuihdann_list) {
        tzuihdann->display();
    }
    for (::QuadDisplayer *diqdann : this->diqdann_list) {
        diqdann->display();
    }
    for (::RectDisplayer *cziguang : this->cziguang_list) {
        cziguang->display();
    }
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

    if (this->is_suspending) {
        this->display_suspending_curtain();
    }

    ::SDL_GL_SwapWindow(::Sseu::window);
    this->timer.procedure();
    ::std::this_thread::sleep_until(this->timer.curr_time + ::std::chrono::milliseconds(16));
    this->timer.update();
}
void GameActivity::procedure(::SDL_Event const event) {
    switch (event.type) {
        case ::SDL_EventType::SDL_KEYDOWN: {
            this->key_state[event.key.keysym.sym] = true;
            if (this->is_suspending) {
                switch (event.key.keysym.sym) {
                    case ::SDL_KeyCode::SDLK_ESCAPE: {
                        this->is_suspending = false;
                        this->timer.resume();
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_RETURN: case ::SDL_KeyCode::SDLK_z: {
                        switch (this->selected) {
                            case 0U: {
                                this->is_suspending = false;
                                this->timer.resume();
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
                        this->timer.pause();
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_LSHIFT: case ::SDL_KeyCode::SDLK_RSHIFT: {
                        this->tzuihczi.lparam_map[::LparamUsage::LU_IS_SLOW].b = true;
                        // this->tzoiczi_list[0].lparam_map[::LparamUsage::LU_DX].d = -32.0;
                        // this->tzoiczi_list[0].lparam_map[::LparamUsage::LU_DY].d = 0.0;
                        // this->tzoiczi_list[1].lparam_map[::LparamUsage::LU_DX].d = -16.0;
                        // this->tzoiczi_list[1].lparam_map[::LparamUsage::LU_DY].d = -16.0;
                        // this->tzoiczi_list[2].lparam_map[::LparamUsage::LU_DX].d = 16.0;
                        // this->tzoiczi_list[2].lparam_map[::LparamUsage::LU_DY].d = -16.0;
                        // this->tzoiczi_list[3].lparam_map[::LparamUsage::LU_DX].d = 32.0;
                        // this->tzoiczi_list[3].lparam_map[::LparamUsage::LU_DY].d = 0.0;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_LEFT: {
                        this->tzuihczi.lparam_map[::LparamUsage::LU_IS_HMIRRORED].b = true;
                        this->tzuihczi.lparam_map[::LparamUsage::LU_DX].d = -1;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_RIGHT: {
                        this->tzuihczi.lparam_map[::LparamUsage::LU_IS_HMIRRORED].b = false;
                        this->tzuihczi.lparam_map[::LparamUsage::LU_DX].d = 1;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_UP: {
                        this->tzuihczi.lparam_map[::LparamUsage::LU_DY].d = 1;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_DOWN: {
                        this->tzuihczi.lparam_map[::LparamUsage::LU_DY].d = -1;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_z: {
                        if (!this->tzuihczi.lparam_map[::LparamUsage::LU_IS_SHOOTING].b) {
                            this->shooting_sound_player.play();
                        }
                        this->tzuihczi.lparam_map[::LparamUsage::LU_IS_SHOOTING].b = true;
                        break;
                    }
                    case ::SDL_KeyCode::SDLK_x: {
                        if (this->info_displayer.target_power >= 100) {
                            this->info_displayer.target_power -= 100;
                            this->timer.prepare(::TimedEvent(this->timer.duration_from_base, &::FuncSource::Stuffs::eventer_bomb));
                        }
                        break;
                    }
case ::SDL_KeyCode::SDLK_c: {
    if (this->info_displayer.target_power <= 400) {
        this->info_displayer.target_power += 100;
    } else {
        this->info_displayer.target_power = 500;
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
                        this->tzuihczi.lparam_map[::LparamUsage::LU_IS_SLOW].b = false;
                        // this->tzoiczi_list[0].lparam_map[::LparamUsage::LU_DX].d = -64.0;
                        // this->tzoiczi_list[0].lparam_map[::LparamUsage::LU_DY].d = 0.0;
                        // this->tzoiczi_list[1].lparam_map[::LparamUsage::LU_DX].d = -32.0;
                        // this->tzoiczi_list[1].lparam_map[::LparamUsage::LU_DY].d = 32.0;
                        // this->tzoiczi_list[2].lparam_map[::LparamUsage::LU_DX].d = 32.0;
                        // this->tzoiczi_list[2].lparam_map[::LparamUsage::LU_DY].d = 32.0;
                        // this->tzoiczi_list[3].lparam_map[::LparamUsage::LU_DX].d = 64.0;
                        // this->tzoiczi_list[3].lparam_map[::LparamUsage::LU_DY].d = 0.0;
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
                        if (this->tzuihczi.lparam_map[::LparamUsage::LU_IS_SHOOTING].b) {
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
    const double dx{this->tzuihczi.x - set_x};
    const double dy{this->tzuihczi.y - set_y};
    const double rho{::sqrt(dx * dx + dy * dy) * 4};
    const double theta{::atan2(dy, dx) + (static_cast<double>(::rand()) / RAND_MAX - 0.5) * M_PI};
    ::QuadDisplayer *ssiaygoo{new ::QuadDisplayer(this->timer.duration_from_base, &::FuncSource::Stuffs::updater_ssiaygoo_graze, ::TexSource::tex_ids["bubble"], this->tzuihczi.x, this->tzuihczi.y, 8.0, 8.0)};
    ssiaygoo->lparam_map[::LparamUsage::LU_SETX].d = ssiaygoo->x;
    ssiaygoo->lparam_map[::LparamUsage::LU_SETY].d = ssiaygoo->y;
    ssiaygoo->lparam_map[::LparamUsage::LU_DX].d = rho * ::cos(theta);
    ssiaygoo->lparam_map[::LparamUsage::LU_DY].d = rho * ::sin(theta);
    ssiaygoo->lparam_map[::LparamUsage::LU_EXISTENCE].b = true;
    this->ssiaygoo_list.push_back(ssiaygoo);
    ssiaygoo->lparam_map[::LparamUsage::LU_IS_GRAZED].b = true;
    ::AudioSource::play_audio_once(::AudioSource::audio_ids["graze_sound"]);
}
void GameActivity::tzuihczi_miss() {
    // ::std::thread([this]() -> void {
    //     ::std::this_thread::sleep_for(::std::chrono::milliseconds(8192));
    //     this->tzuihczi.lparam_map[::LparamUsage::LU_IS_INJURY_FREE].b = false;
    // }).detach();
    this->tzuihczi.lparam_map[::LparamUsage::LU_IS_INJURY_FREE].b = true;
    this->timer.prepare(::TimedEvent(this->timer.duration_from_base + 8192, &::FuncSource::Characters::eventer_tzuihczi_injury_free_quit));
    // ::TimedEvent event(this->timer.duration_from_base + 8192, &::FuncSource::General::eventer_set_something<bool>);
    // event.lparam_map[::LparamUsage::LU_TARGET].p = &this->tzuihczi.lparam_map[::LparamUsage::LU_IS_INJURY_FREE];
    // event.lparam_map[::LparamUsage::LU_APPENDAGE].b = false;
    // this->timer.prepare(event);
    if (this->info_displayer.player > 0U) {
        --this->info_displayer.player;
    } else {
        // ::std::cout << "Lose!\n";
    }
    this->tzuihczi.x = 256.0;
    this->tzuihczi.y = -64.0;
    this->tzuihczi.update_func = &::FuncSource::Characters::updater_tzuihczi_recover;
    ::AudioSource::play_audio_once(::AudioSource::audio_ids["biu"]);
}
void GameActivity::tzuihczi_shoot() {
    ::QuadDisplayer *tzuihdann;
    unsigned int tex_id_left, tex_id_right;
    if (this->tzuihczi.lparam_map[::LparamUsage::LU_IS_HMIRRORED].b) {
        tex_id_left = ::TexSource::tex_ids["gerasimov"];
        tex_id_right = ::TexSource::tex_ids["shoigu"];
    } else {
        tex_id_left = ::TexSource::tex_ids["shoigu"];
        tex_id_right = ::TexSource::tex_ids["gerasimov"];
    }
    this->tzuihdann_list.push_back(tzuihdann = new ::QuadDisplayer(this->timer.duration_from_base, &::FuncSource::Characters::updater_tzuihdann, tex_id_left, this->tzuihczi.x - 16, this->tzuihczi.y, 16.0, 16.0));
    tzuihdann->lparam_map[::LparamUsage::LU_DX].d = 0.0;
    tzuihdann->lparam_map[::LparamUsage::LU_DY].d = 1.0;
    this->updater_status[tzuihdann] = true;
    this->tzuihdann_list.push_back(tzuihdann = new ::QuadDisplayer(this->timer.duration_from_base, &::FuncSource::Characters::updater_tzuihdann, tex_id_right, this->tzuihczi.x + 16, this->tzuihczi.y, 16.0, 16.0));
    tzuihdann->lparam_map[::LparamUsage::LU_DX].d = 0.0;
    tzuihdann->lparam_map[::LparamUsage::LU_DY].d = 1.0;
    this->updater_status[tzuihdann] = true;
    for (::std::vector<::RotatedQuadDisplayer *>::iterator tzoiczi(this->tzoiczi_list.begin()); tzoiczi != this->tzoiczi_list.end(); ++tzoiczi) {
        // ::RotatedQuadDisplayer *tzoidann{new ::RotatedQuadDisplayer(this->timer.duration_from_base, &::FuncSource::Characters::updater_tzoidann, ::TexSource::tex_ids["tracking_bullet"], (*tzoiczi)->x, (*tzoiczi)->y, 8.0, 8.0, M_PI_2, (0.375 - (tzoiczi - this->tzoiczi_list.begin()) * 0.25) * M_PI)};
        ::RotatedQuadDisplayer *tzoidann{new ::RotatedQuadDisplayer(this->timer.duration_from_base, &::FuncSource::Characters::updater_tzoidann, ::TexSource::tex_ids["tracking_bullet"], (*tzoiczi)->x, (*tzoiczi)->y, 8.0, 8.0, M_PI_2, ::atan2((*tzoiczi)->y - this->tzuihczi.y, (*tzoiczi)->x - this->tzuihczi.x) - M_PI_2)};
        tzoidann->lparam_map[::LparamUsage::LU_TARGET].p = this->diqczi_list.empty() ? nullptr : this->diqczi_list[::rand() % this->diqczi_list.size()];
        this->tzuihdann_list.push_back(tzoidann);
        this->updater_status[tzoidann] = true;
    }
}
void GameActivity::tzuihczi_shoot_and_break() {
    if (this->tzuihczi.lparam_map[::LparamUsage::LU_IS_SHOOTING].b && !this->tzuihczi.lparam_map[::LparamUsage::LU_IS_IN_SHOOTING_BREAK].b) {
        this->tzuihczi.lparam_map[::LparamUsage::LU_IS_IN_SHOOTING_BREAK].b = true;
        // ::std::thread([this->tzuihczi]() -> void {
        //     ::std::this_thread::sleep_for(::std::chrono::milliseconds(64));
        //     this->tzuihczi.lparam_map[::LparamUsage::LU_IS_IN_SHOOTING_BREAK].b = false;
        // }).detach();
        this->timer.prepare(::TimedEvent(this->timer.duration_from_base + 64, &::FuncSource::Characters::eventer_tzuihczi_shooting_break_recover));
        this->tzuihczi_shoot();
    }
}

#ifndef PATH_MAX
#define PATH_MAX 0x1000
#endif

int main() {
    // ::TimedEvent timed_event(0.0, nullptr);
    // ::std::cout << sizeof timed_event << '\n' << (char *)(&timed_event.lparam_map) - (char *)(&timed_event) << '\t' << sizeof timed_event.lparam_map << '\n' << (char *)(&timed_event.time) - (char *)(&timed_event) << '\t' << sizeof timed_event.time << '\n' << (char *)(&timed_event.event_func) - (char *)(&timed_event) << '\t' << sizeof timed_event.event_func << '\n';
    // double d{1.0};
    // ::std::cout << static_cast<unsigned long long>(d) << '\n';
    // ::std::cout << ::__get_rho(0) << '\n';
    // ::std::cout << *reinterpret_cast<double *>(const_cast<wchar_t *>(L"\u0000\u0000\u0000\u7ff0")) << '\n';
    // int *p{new int[0]};
    // ::std::cout << p << '\n';
    // delete[] p;
    // ::std::cout << p << '\n';
    ::std::cout << __TIMESTAMP__ << '\n';
    // return 0;

    ::Sseu::init("東綫ПРОЖЕКТ", 64, 64, 1024, 768);
    ::Sseu::FontSource::source_init();
    ::TexSource::source_init("src/");
    ::AudioSource::source_init("src/");
    ::Sseu::push_activity<::LaunchActivity>();
    ::Sseu::mainloop();
    ::AudioSource::source_quit();
    ::TexSource::source_quit();
    ::Sseu::FontSource::source_quit();
    ::Sseu::quit();
    return 0;
}

#endif
