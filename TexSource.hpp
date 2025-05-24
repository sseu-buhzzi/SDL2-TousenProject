#ifndef TEX_SOURCE_HPP
#define TEX_SOURCE_HPP

#include "headers.hpp"
// #include <iostream>
namespace TexSource {
	::std::string const tex_names[]{
		"kremlin",
		"prigozin",
		"putin",
		"gerasimov",
		"shoigu",
		"prigozin_on_plane",
		"judge_point",
		"ball_lightning_red",
		"ball_lightning_green",
		"ball_lightning_blue",
		"ball_lightning_yellow",
		"ball_lightning_purple",
		"ball_lightning_cyan",
		"dahzziuh_red",
		"dahzziuh_green",
		"dahzziuh_blue",
		"logo",
		"xi",
		"druangczea_niqluh",
		"stepan_bandera",
		"zelensikij",
		"vagner",
		"game_background",
		"wheat_field",
		"blue_sky",
		"tracking_bullet",
		"diamond_bullet_red",
		"diamond_bullet_green",
		"diamond_bullet_blue",
		"diamond_bullet_yellow",
		"diamond_bullet_purple",
		"diamond_bullet_cyan",
		"bubble",
		"player_star",
		"power_point",
		"dean_point",
		"dart_bullet_blue",
		"hexagram_blue",
		"zelensikij_name",
		"slava_ukrajni",
		"laser_blue",
		"zzingxua",
		"ssiauzzian",
		"laser_spark_red",
		"laser_spark_green",
		"laser_spark_blue",
		"laser_spark_yellow",
		"laser_spark_purple",
		"laser_spark_cyan",
		"kung",
		"heal_bar",
		"bubble_red",
		"bubble_green",
		"bubble_blue",
		"reimu_gunpuku",
		"logo_sseu"
	};
	::std::string const tex_files[]{
		"Kremlin.mem",
		"Prigozin.mem",
		"Putin.mem",
		"Gerasimov.mem",
		"Shoigu.mem",
		"PrigozinOnPlane.mem",
		"JudgePoint.mem",
		"BallLightningRed.mem",
		"BallLightningGreen.mem",
		"BallLightningBlue.mem",
		"BallLightningYellow.mem",
		"BallLightningPurple.mem",
		"BallLightningCyan.mem",
		"DahzziuhRed.mem",
		"DahzziuhGreen.mem",
		"DahzziuhBlue.mem",
		"Logo.mem",
		"Xi.mem",
		"DruangczeaNiqluh.mem",
		"StepanBandera.mem",
		"Zelensikij.mem",
		"Vagner.mem",
		"GameBackground.mem",
		"WheatField.mem",
		"BlueSky.mem",
		"TrackingBullet.mem",
		"DiamondBulletRed.mem",
		"DiamondBulletGreen.mem",
		"DiamondBulletBlue.mem",
		"DiamondBulletYellow.mem",
		"DiamondBulletPurple.mem",
		"DiamondBulletCyan.mem",
		"Bubble.mem",
		"PlayerStar.mem",
		"PowerPoint.mem",
		"DeanPoint.mem",
		"DartBulletBlue.mem",
		"HexagramBlue.mem",
		"ZelensikijName.mem",
		"SlavaUkrajni.mem",
		"LaserBlue.mem",
		"Zzingxua.mem",
		"Ssiauzzian.mem",
		"LaserSparkRed.mem",
		"LaserSparkGreen.mem",
		"LaserSparkBlue.mem",
		"LaserSparkYellow.mem",
		"LaserSparkPurple.mem",
		"LaserSparkCyan.mem",
		"Kung.mem",
		"HealBar.mem",
		"BubbleRed.mem",
		"BubbleGreen.mem",
		"BubbleBlue.mem",
		"ReimuGunpuku.mem",
		// "Vagner.mem",
		"LogoSseu.mem"
	};
	unsigned int const tex_count{sizeof tex_names / sizeof(::std::string const)};
	::std::unordered_map<::std::string, unsigned int const> tex_ids;
	inline void source_init(const ::std::string &src_dir) {
		for (unsigned int i{0U}; i < ::TexSource::tex_count; ++i) {
			::std::ifstream tex_file(src_dir + ::TexSource::tex_files[i], ::std::ios::binary);
			unsigned int tex_width, tex_height;
			tex_file.read(reinterpret_cast<char *>(&tex_width), 4ULL);
			tex_file.read(reinterpret_cast<char *>(&tex_height), 4ULL);
			unsigned int tex_length(tex_width * tex_height * 4);
			char *tex_data{new char[tex_length]};
			tex_file.read(tex_data, tex_length);
			tex_file.close();
			unsigned int tex_id;
			::glGenTextures(1, &tex_id);
			::glBindTexture(GL_TEXTURE_2D, tex_id);
			::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_width, tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_data);
			::TexSource::tex_ids.emplace(::TexSource::tex_names[i], tex_id);
		}
	}
	inline void source_quit() {
		for (::std::unordered_map<::std::string, unsigned int const>::iterator tex_it(::TexSource::tex_ids.begin()); tex_it != ::TexSource::tex_ids.end(); ++tex_it) {
			::glDeleteTextures(1, &tex_it->second);
		}
	}
}

#endif
