from pydub import AudioSegment

name = "GrazeSound_0"

audio = AudioSegment.from_mp3("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\TEST\\{}.mp3".format(name))

audio = audio[128 : ] + 0

audio.export("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\TEST\\{}_new.mp3".format(name), format="mp3")
