# Eleonora Chacón Taylor 2024
# wavextract.py: python script to extract data from wav files.

import wave
import numpy as np

n_samples = 512

def extract(file, textfile):
    wavfile = wave.open(file, mode='rb')
    print(str(wavfile.getparams()))
    n_file = wavfile.getnframes()
    if (n_file == n_samples):
        print("wavextract: wav file format is correct")
        f = open(textfile, "w")
        for n in range(n_samples):
            signal = wavfile.readframes(1)
            sample = np.frombuffer(signal, dtype='int16')
            f.write(str(sample[0]) + ',\n')

        f.close()
        print("wavextract: Done")
    else:
        print("wavextract: Error: input wav file is not adequate")

    wavfile.close()

