# Code Contributor - Ankit Shah - ankit.tronix@gmail.com
# Modified - Alexander Bakhtin - alexander.bakhtin@tuni.fi
from __future__ import unicode_literals

import os
from multiprocessing import Pool, freeze_support
import csv
import yt_dlp as yt
from tqdm import tqdm


global clip_length, sample_rate, bits, channels

clip_length = 10000
duration = 10
quality_rate = 5
sample_rate = 48000
bits = 16
channels = 2


class MyLogger(object):
    def debug(self, msg):
        pass

    def warning(self, msg):
        pass

    def error(self, msg):
        print(msg)


def my_hook(d):
    """
    Update the progress bar based on the downloaded bytes.
    """
    global pbar
    if 'status' in d:
        if d['status'] == 'downloading':
            if 'downloaded_bytes' in d:
                if 'pbar' in globals():
                    pbar.update(int(d['downloaded_bytes']))
        elif d['status'] == 'finished':
            if 'pbar' in globals():
                pbar.close()


def download_audio_wrapper(segment_id, dataset_name, clip_length):
    """
    Wrapper function to download audio.
    """
    # Split in two parts to get the query_id and start_seconds (last underscore is the separator)
    parts = segment_id.split('_')
    if len(parts) > 2:
        # Concatenate the parts until the last underscore
        parts = '_'.join(parts[:-1]), parts[-1]
    query_id = parts[0]
    start_seconds = int(parts[1].replace('.', ''))//1000
    clip_length = clip_length//1000
    return download_audio(query_id, dataset_name, start_seconds, clip_length, verbose=False)


def download_audio(query_id, dataset_name, start_seconds, clip_length, verbose=True):
    """
    This function downloads an audio file from YouTube, formats it, and segments it.
    Args:
        query_id (str): The YouTube video ID.
        dataset_name (str): The name of the dataset. Used to create folder names.
        start_seconds (int): The start time for the audio clip in seconds.
        clip_length (int): The length of the audio clip in seconds.
        verbose (bool): If True, print progress information.
    Returns:
        int: 1 if the audio file was successfully segmented, 0 otherwise.
    """
    # Create the YouTube URL
    url = "https://www.youtube.com/watch?v=" + query_id

    # Create the folder names
    download_folder = dataset_name + "_downloaded"
    formatted_folder = dataset_name + "_formatted"
    segmented_folder = dataset_name + "_segmented"

    # Create the file paths
    path_to_download = os.path.join(download_folder, f"Y{query_id}")
    path_to_formatted_audio = os.path.join(
        formatted_folder, f"Y{query_id}.wav")
    path_to_segmented_audio = os.path.join(
        segmented_folder, f"Y{query_id}.wav")

    # Try to download the audio file
    try:
        if os.path.exists(path_to_download):
            print(f"{query_id}: Downloaded file already exists.")
        else:
            # Set the options for youtube-dl
            ydl_opts = {
                'format': 'bestaudio/best',
                'outtmpl': path_to_download,
                'postprocessors': [{
                    'key': 'FFmpegExtractAudio',
                    'preferredcodec': 'wav',
                }],
                'logger': MyLogger(),
                'quiet': True,
                'progress_hooks': [my_hook],
            }

            # Download the audio file
            with yt.YoutubeDL(ydl_opts) as ydl:
                if verbose:
                    # Get the total video size in bytes
                    info_dict = ydl.extract_info(url, download=False)
                    video_bytes = info_dict.get('filesize', None)
                    global pbar
                    pbar = tqdm(
                        total=video_bytes, desc=f"Downloading {query_id}", unit='B', unit_scale=True)
                ydl.download([url])
    except Exception as ex:
        print(f"{query_id}: Error Downloading - {str(ex)}")
        return 0

    path_to_download = path_to_download + ".wav"

    # Try to format the audio file
    try:
        if os.path.exists(path_to_formatted_audio):
            print(f"{query_id}: Formatted file already exists.")
        else:
            global bits, channels, sample_rate
            cmdstring = f"sox {path_to_download} -G -c {channels} -b {bits} -r {sample_rate} {path_to_formatted_audio}"
            os.system(cmdstring)
            # Once the audio is formatted, delete the downloaded file
            os.remove(path_to_download)
    except Exception as e:
        print(f"{query_id}: Error Formatting - {str(e)}")
        return 0

    # Try to segment the audio file
    try:
        if os.path.exists(path_to_segmented_audio):
            print(f"{query_id}: Trimmed file already exists.")
        else:
            if clip_length == 0:
                cmdstring = f"sox {path_to_formatted_audio} {path_to_segmented_audio} trim {start_seconds}"
            else:
                cmdstring = f"sox {path_to_formatted_audio} {path_to_segmented_audio} trim {start_seconds} {clip_length}"
            os.system(cmdstring)
            os.remove(path_to_formatted_audio)
            return 1
    except Exception as ex:
        print(f"{query_id}: Error Segmenting - {str(ex)}")
        return 0


def download_audio_0(query_id, dataset_name, verbose=True):
    url = "https://www.youtube.com/watch?v=" + query_id
    download_folder = dataset_name + "_downloaded"
    path_to_download = os.path.join(download_folder, f"Y{query_id}")

    try:
        if os.path.exists(path_to_download):
            print(f"{query_id}: Downloaded file already exists.")
        else:
            ydl_opts = {
                'format': 'bestaudio/best',
                'outtmpl': path_to_download,
                'postprocessors': [{
                    'key': 'FFmpegExtractAudio',
                    'preferredcodec': 'wav',
                }],
                'logger': MyLogger(),
                'quiet': True,
                'progress_hooks': [my_hook],
            }
            # print yotube-dl version
            print(yt.version.__version__)
            with yt.YoutubeDL(ydl_opts) as ydl:
                if verbose:
                    # get the total video size in bytes
                    info_dict = ydl.extract_info(url, download=False)
                    video_bytes = info_dict.get('filesize', None)
                    global pbar
                    pbar = tqdm(
                        total=video_bytes, desc=f"Downloading {query_id}", unit='B', unit_scale=True)
                ydl.download([url])
    except Exception as ex:
        print(f"{query_id}: Error Downloading - {str(ex)}")


def format_audio(path_to_download, dataset_name, query_id, bits, channels, sample_rate):
    formatted_folder = dataset_name + "_formatted"
    path_to_formatted_audio = os.path.join(
        formatted_folder, f"Y{query_id}.wav")
    try:
        if os.path.exists(path_to_formatted_audio):
            print(f"{query_id}: Formatted file already exists.")
        else:
            cmdstring = f"sox {path_to_download} -G -c {bits} -b {channels} -r {sample_rate} {path_to_formatted_audio}"
            os.system(cmdstring)
            # Ones the audio is formatted, delete the downloaded file
            os.remove(path_to_download)
    except Exception as ex:
        print(f"{query_id}: Error - {str(ex)}")
    return path_to_formatted_audio


def segment_audio(path_to_formatted, dataset_name, query_id, start_seconds, clip_length):
    segmented_folder = dataset_name + "_segmented"
    path_to_segmented_audio = os.path.join(
        segmented_folder, f"Y{query_id}_{start_seconds}.wav")

    try:
        print(f"{query_id}: Trimming...")
        if os.path.exists(path_to_segmented_audio):
            print(f"{query_id}: Trimmed file already exists.")
        else:
            if clip_length == 0:
                cmdstring = f"sox {path_to_formatted} {path_to_segmented_audio} trim {start_seconds}"
            else:
                cmdstring = f"sox {path_to_formatted} {path_to_segmented_audio} trim {start_seconds} {clip_length}"
            os.system(cmdstring)
    except Exception as ex:
        print(f"{query_id}: Error - {str(ex)}")
    return path_to_segmented_audio


def parallelize_download(input_file, num_workers=None, clip_length=10000,
                         sample_rate=48000, bits=16, channels=2):
    ''' Parallelize the task of downloading data from YouTube.

    Parameters
    __________
    input_file : str
        A CSV file, with one video to download on each line in the format 
        'YTID, start_seconds, end_seconds, positive_labels', where YTID is the 
        YouTube ID of the video and start_seconds is the time stamp to trim video from.
        NOTE: the input file will be open in Python for the whole execution
        of the program.
    num_workers : int, optional (default None)
        Amount of processes (downloads) to spawn using Pool().
    clip_length : int, optional (default 10000)
        Length (in ms) of clip to trim from the STARTTIME specified in input_file.
        NOTE: if the resulting clip is actually shorter, it will NOT be extended by SOX.
        NOTE: if 0, will trim from STARTTIME until the end.
    sample_rate : int, optional (default 44100)
        Sample rate (in Hz) to resample the downloaded audios into.
        (Passed to sox -s)
    bits : int, optional (default 16)
        Quality of audiosteam to convert into. (Passed to sox -b)
    channels : int, optional (default 1)
        Number of channels to convert audio into. (Passed to sox -c)
    '''
    dataset_name = "D:\\loaiu\\MAM5\\Projet_S9\\data\\TrainSet\\Animals\\animals"
    os.makedirs(dataset_name + "_downloaded", exist_ok=True)
    os.makedirs(dataset_name + "_formatted", exist_ok=True)
    os.makedirs(dataset_name + "_segmented", exist_ok=True)

    death_count = 0
    with open(input_file, 'r') as segments_info_file:
        csv_reader = csv.reader(segments_info_file)
        while death_count < 500:
            lines_list = []
            last_loop = False
            for i in range(num_workers):
                try:
                    line = next(csv_reader)
                    segment_id = f"{line[0]}_{line[1]}"
                    start_time = float(line[1])
                    """lines_list.append((segment_id,
                                       dataset_name,
                                       clip_length,
                                       sample_rate,
                                       bits, channels, start_time))"""
                    lines_list.append((segment_id,
                                       dataset_name,
                                       clip_length))
                except StopIteration:
                    last_loop = True
                    break
            with Pool(num_workers) as P:
                results = P.starmap(download_audio_wrapper, lines_list)
            death_count += results.count(1)
            print(f"Downloaded {death_count} files")

            if last_loop:
                break


def parallelize_format(num_workers=None, clip_length=10000,
                       sample_rate=44100, bits=16, channels=1):
    ''' Parallelize the task of formatting the already downloaded data from YouTube.
    '''
    dataset_name = "dataset"
    dowload_folder = "dataset_downloaded"
    # Get all the .wav files in the download folder
    list_of_files = os.listdir(dowload_folder)

    # Create a list of tuples with the arguments for the format_audio function
    lines_list = []
    for file in list_of_files:
        query_id = file.split('.')[0][1:]
        lines_list.append((dowload_folder + '\\' + file,
                           dataset_name,
                           query_id,
                           bits, channels,
                           sample_rate))

    with Pool(num_workers) as P:
        P.starmap(format_audio, lines_list)


def parallelize_segmentation(num_workers=None, clip_length=10000,
                             sample_rate=44100, bits=16, channels=1):
    ''' Parallelize the task of segment the already fomatted data from YouTube.
    '''

    dataset_name = "dataset"
    formatted_folder = "dataset_formatted"
    # Get all the .wav files in the download folder
    list_of_files = os.listdir(formatted_folder)

    # Create a list of tuples with the arguments for the segment_audio function
    lines_list = []
    for file in list_of_files:
        query_id = file.split('.')[0][1:]
        lines_list.append((formatted_folder + '\\' + file,
                           dataset_name,
                           query_id,
                           clip_length))

    with Pool(num_workers) as P:
        P.starmap(segment_audio, lines_list)


if __name__ == '__main__':
    freeze_support()  # Add this line to prevent the RuntimeError on Windows
    input_file = 'data\\Categories\\Animals\\Animals_final_reduced.csv'
    # Get the number of workers from the number of CPUs
    num_workers = os.cpu_count()

    parallelize_download(input_file, num_workers,
                         clip_length, sample_rate, bits, channels)
