import moviepy.editor as mp

name = "Sounds_3"

# 处理视频并提取音频
video = mp.VideoFileClip("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\TEST\\{}.mp4".format(name))
trimmed_video = video.subclip(39.5, 40)
audio = trimmed_video.audio
audio.write_audiofile("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\TEST\\{}.mp3".format(name), codec="mp3")

# 关闭资源
video.close()
trimmed_video.close()
audio.close()
