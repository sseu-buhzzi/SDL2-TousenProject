# from pydub import AudioSegment
import pydub

name = "GrazeSound"

audio = pydub.AudioSegment.from_mp3("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\TEST\\{}.mp3".format(name))

audio = audio.set_sample_width(2)
audio = audio.set_channels(1)
audio = audio.set_frame_rate(44100)
audio += 8

with open("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\src\\{}.mem".format(name), 'wb') as mem:
    mem.write(len(audio.raw_data).to_bytes(4, "little"))
    mem.write(audio.raw_data)
