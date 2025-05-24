#ifndef FONT_SOURCE_HPP
#define FONT_SOURCE_HPP

#include ".\sseu_headers.hpp"
#include ".\FontTexData.hpp"

// #include ".\FontTexData_Test.hpp"

namespace Sseu::FontSource {
    ::uint32_t font_tex_ids[128];
    inline void source_init() {
        ::glGenTextures(128, ::Sseu::FontSource::font_tex_ids);
        for (char ch{'\x00'}; ch >= 0; ++ch) {
            ::glBindTexture(GL_TEXTURE_2D, ::Sseu::FontSource::font_tex_ids[ch]);
            ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            ::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 9, 18, 0, GL_RGBA, GL_UNSIGNED_BYTE, ::Sseu::FontSource::font_tex_data[ch]);
            // ::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 9, 18, 0, GL_RGBA, GL_UNSIGNED_BYTE, ::Sseu::FontSource::font_tex_data_Test[0]);
        }
    }

    inline void source_quit() {
        ::glDeleteTextures(128, ::Sseu::FontSource::font_tex_ids);
    }

    inline void draw_text(char const *text, double const font_size) {
        // ::std::cout << "text:" << text << '\n';
        // char s[16]{}, *t{s};
        for (double offset{0.0}; *text != '\x00'; ++text, offset += font_size) {
            // ::std::cout << t - s << " text:" << text << '\n';
            ::glBindTexture(GL_TEXTURE_2D, font_tex_ids[*text]);
            ::glBegin(GL_QUADS);
            ::glTexCoord2i(0, 1);
            ::glVertex2d(offset, 0.0);
            ::glTexCoord2i(0, 0);
            ::glVertex2d(offset, font_size * 2);
            ::glTexCoord2i(1, 0);
            ::glVertex2d(offset + font_size, font_size * 2);
            ::glTexCoord2i(1, 1);
            ::glVertex2d(offset + font_size, 0.0);
            ::glEnd();

            // *t++ = *text;
            // ::std::cout << t - s << " s:" << s << '\n';
        }
        // ::std::cout << "s:" << s << '\n';
        // ::std::cout << '\n';
    }

    inline void start_text() {
        ::glEnable(GL_TEXTURE_2D);
    }

    inline void end_text() {
        ::glDisable(GL_TEXTURE_2D);
    }
}

#endif
