import numpy as np
# Check that all the .wav files have the same length, sample rate, number of channels and bit depth
import os

import soundfile as sf

def check_common_lines(filepaths):
    sets = [set(open(filepath, 'r')) for filepath in filepaths]
    common_lines = set.intersection(*sets)
    assert not common_lines, f"Common lines found: {common_lines}" 
    print("No common lines found")
    

filepaths = [
    "data\\Categories\\Music\\Instruments_final_reduced.csv",
    "data\\Categories\\SoT\\sound_of_things_final_reduced.csv",
    "data\\Categories\\Animals\\Animals_final_reduced.csv"
]

check_common_lines(filepaths)

def get_properties(filepath):
    data, samplerate = sf.read(filepath)
    length = len(data) / samplerate
    channels = len(data.shape)
    bit_depth = data.dtype
    #print(f"Length: {length}, Sample rate: {samplerate}, Channels: {channels}, Bit depth: {bit_depth}")
    return [length, samplerate, channels, bit_depth]



def check_properties(filepaths):
    properties_dict = {}
    for filepath in filepaths:
        print(filepath)
        # in the parent directory
        for file in os.listdir(filepath):
            if file.endswith(".wav"):
                # get the properties of the .wav file
                properties = tuple(get_properties(os.path.join(filepath, file)))
                if properties not in properties_dict:
                    properties_dict[properties] = 1
                else:
                    properties_dict[properties] += 1

    # print the properties and their counts
    for properties, count in properties_dict.items():
        length, rate, channels, bit_depth = properties
        print(f"Length: {length}, Sample rate: {rate}, Channels: {channels}, Bit depth: {bit_depth}, Count: {count}")

    return properties_dict

                

filepaths = [
    "data\\TrainSet\\Music\\instruments_segmented",
    "data\\TrainSet\\SoT\\sound_of_things_segmented",
    "data\\TrainSet\\Animals\\animals_segmented"
]

"""os.mkdir("data\\TrainSet\\Music\\instruments_segmented")
os.mkdir("data\\TrainSet\\SoT\\sound_of_things_segmented")
os.mkdir("data\\TrainSet\\Animals\\animals_segmented")
"""
check_properties(filepaths)

def delete_not_homogeneise_file(filepaths):
    for filepath in filepaths:
        print(filepath)
        # in the parent directory
        for file in os.listdir(filepath):
            if file.endswith(".wav"):
                # get the properties of the .wav file
                properties = tuple(get_properties(os.path.join(filepath, file)))
                if properties != (10.0, 48000, 2, np.float64): 
                    os.remove(os.path.join(filepath, file))
                    print(f"Removed {file}")

#delete_not_homogeneise_file(filepaths)