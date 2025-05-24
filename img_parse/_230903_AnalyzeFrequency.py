from pydub import AudioSegment
import numpy as np

# 读取 MP3 文件
audio = AudioSegment.from_mp3("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\TEST\\ShootSound_0.mp3")  # 替换为你的 MP3 文件路径

# 将音频数据转换为NumPy数组
audio_data = np.array(audio.get_array_of_samples())

# 采样率
sample_rate = audio.frame_rate

# 进行傅立叶变换
frequencies = np.fft.fftfreq(len(audio_data), 1/sample_rate)
fft_values = np.fft.fft(audio_data)

# 只保留正频率部分（去掉负频率）
positive_frequencies = frequencies[:len(frequencies)//2]
positive_fft_values = np.abs(fft_values[:len(fft_values)//2])

# 找到主要频率成分的索引
main_frequency_index = np.argmax(positive_fft_values)

# 计算主要频率的周期长度（毫秒）
main_frequency = positive_frequencies[main_frequency_index]
period_length_ms = 1 / (main_frequency / 1000)

print(f"音频的主要周期长度：{period_length_ms} 毫秒")
