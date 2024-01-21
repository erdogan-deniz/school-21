import re  # Module for regular expression of audio format files
import sys  # Module for parsing cmd args
import yaml  # Module for working temporary file
import atexit  # Module for "last" function
import subprocess  # Module for using linux command
from os import walk  # Function for working with file in current directory
from flask import Flask, render_template, request  # Flask functions


def is_audio_file(file):  # Checking file for audio format
    if ((re.match(r"^.*\.mp3$", file) is not None) or
            (re.match(r"^.*\.ogg$", file) is not None) or
            (re.match(r"^.*\.wav$", file) is not None) or
            (re.match(r"^.*\.mpeg$", file) is not None)):
        return True

    return False


music_list = []  # Our current list of musics

disk_musics = next(walk("music"), (None, None, []))[2]  # Real files on the disk
disk_musics = [i for i in disk_musics if (":Zone.Identifier" not in i) and (is_audio_file(i))]  # Delete identifiers

app = Flask(__name__)  # Main flask window


def create_music_file(music):  # Save our musics to the file
    with open("musics.yml", 'w') as file:
        yaml.safe_dump({"key": music}, file)


# Papers for watching:
@app.route('/', methods=["POST", "GET"])
@app.route("/main", methods=["POST", "GET"])
@app.route("/home", methods=["POST", "GET"])
def home_page():
    # Upload new track:
    try:
        with open("new_tracks.yml", 'r') as file:
            data = yaml.load(file, Loader=yaml.FullLoader)

        music_list.append(data["key"])  # Add music in current list
        subprocess.run("rm -rf new_tracks.yml", shell=True)  # Delete file
    except FileNotFoundError:
        pass

    create_music_file(music_list)

    return render_template("index.html", new_track="", musics=convert_to_string(music_list))


def convert_to_string(musics):
    answer = []

    for music in musics:
        answer.append(str(music))

    return answer


@app.route("/new_list", methods=["POST", "GET"])
def result():
    try:
        with open("new_tracks.yml", 'r') as file:
            data = yaml.load(file, Loader=yaml.FullLoader)

        music_list.append(data["key"])
        subprocess.run("rm -rf new_tracks.yml", shell=True)  # Delete uploads tracks
    except FileNotFoundError:
        pass

    create_music_file(music_list)

    output = request.form.to_dict()

    try:
        new_track = output["new_track"]
    except KeyError:
        new_track = ""

    if (new_track in disk_musics) and (new_track not in music_list):
        music_list.append(new_track)

        create_music_file(music_list)

        return render_template("index.html", new_track=new_track, musics=convert_to_string(music_list))
    else:
        create_music_file(music_list)

        return render_template("index.html", new_track="Incorrect File Or Format!",
                               musics=convert_to_string(music_list))


if __name__ == "__main__":
    if len(sys.argv) > 1 and (str(sys.argv[1]) == "list"):  # Check current list of tracks
        try:
            with open("musics.yml", 'r') as file:
                data = yaml.load(file, Loader=yaml.FullLoader)

            for value in data["key"]:
                print(value)

        except FileNotFoundError:
            pass
    elif (len(sys.argv) > 2) and (str(sys.argv[1]) == "upload"):  # If we upload track
        if is_audio_file(str(sys.argv[2].split('/ ')[-1])):
            subprocess.run(f"cp {sys.argv[2]} music/", shell=True)

            with open("new_tracks.yml", 'w') as file:
                yaml.safe_dump({"key": str(sys.argv[2]).split('/')[-1]}, file)
        else:
            print("ERROR!")
    else:
        app.run(debug=False, host="localhost", port=8888)
        atexit.register(subprocess.run("rm -rf musics.yml", shell=True))
