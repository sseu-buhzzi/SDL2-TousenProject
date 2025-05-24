import moviepy.editor

name = "HarudomannoYoukaiShojo"

video = moviepy.editor.VideoFileClip("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\TEST\\{}.mp4".format(name))
audio = video.audio
audio.write_audiofile("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\TEST\\{}.mp3".format(name), codec="mp3")
video.close()
