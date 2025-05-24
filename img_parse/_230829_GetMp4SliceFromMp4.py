import moviepy.video.io.VideoFileClip

name = "HarudomannoYoukaiShojo"

video = moviepy.video.io.VideoFileClip.VideoFileClip("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\TEST\\{}_raw.mp4".format(name))
trimmed_video = video.subclip(7, 290)
trimmed_video.write_videofile("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\TEST\\{}.mp4".format(name), codec="libx264")
video.close()
trimmed_video.close()
