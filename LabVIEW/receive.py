import ggwave
import pyaudio

def receive_audio_init():
    global p
    p = pyaudio.PyAudio()
    global stream
    stream = p.open(format=pyaudio.paFloat32, channels=1, rate=48000, input=True, frames_per_buffer=1024)
    global instance
    instance = ggwave.init()

def receive_audio():
    data = stream.read(1024, exception_on_overflow=False)
    res = ggwave.decode(instance, data)
    if (not res is None):
        return list(res)
    else:
        return [48]
    
def receive_audio_close():
    ggwave.free(instance)
    stream.stop_stream()
    stream.close()
    p.terminate()

receive_audio_init()
returned = receive_audio()
while (returned == [48]):
    returned = receive_audio()
receive_audio_close()
print(returned)