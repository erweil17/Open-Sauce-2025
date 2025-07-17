import ggwave
import pyaudio



# generate audio waveform for string "hello python"
def send_audio(bytes_to_send):
    byte_array_to_send = bytearray(bytes_to_send)
    string_to_send = byte_array_to_send.decode('cp437')

    p = pyaudio.PyAudio()
    waveform = ggwave.encode(string_to_send, protocolId = 1, volume = 20)
    stream = p.open(format=pyaudio.paFloat32, channels=1, rate=48000, output=True, frames_per_buffer=1024)
    stream.write(waveform, len(waveform)//4)
    stream.stop_stream()
    stream.close()

    p.terminate()
    return 0
