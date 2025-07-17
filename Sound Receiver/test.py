import ggwave
import pyaudio



# generate audio waveform for string "hello python"
def send_audio(bytes_to_send):
    byte_array_to_send = bytearray(bytes_to_send)
    string_to_send = byte_array_to_send.decode('cp437')
    return string_to_send

def string_audio(string_to_send):
    return string_to_send

send_audio([254,253,255,0,1,2])