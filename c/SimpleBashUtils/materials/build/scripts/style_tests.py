import subprocess
import os
import sys

PATH_TO_PROJECT = '/'.join(os.path.abspath(os.path.dirname(sys.argv[0])).split('/')[:-1])

devnull_stderr = sys.stdout
devnull_stdout = sys.stdout


def get_source_filenames(arr_of_files=None, depth=0, path=PATH_TO_PROJECT + '/src'):
    if arr_of_files is None:
        arr_of_files = []

    if depth == 3:
        return
    
    for file in os.listdir(path):
        new_path = os.path.join(path, file)
        if os.path.isdir(new_path):
            get_source_filenames(arr_of_files, depth + 1, new_path)
        elif file[file.find('.') + 1 : len(file)] == 'c':
            arr_of_files.append(new_path)

    return arr_of_files


def copy_config():
    subprocess.run(['cp', PATH_TO_PROJECT + '/tests/.clang-format', PATH_TO_PROJECT], stdout=devnull_stdout,
                   stderr=devnull_stderr)


def delete_config():
    subprocess.run(['rm', PATH_TO_PROJECT + '/.clang-format'], stdout=devnull_stdout, stderr=devnull_stderr)


def style_test_result(arr_of_files):
    copy_config()

    for i in range(len(arr_of_files)):
        result_style_test = subprocess.run(
            ['clang-format', '-n', arr_of_files[i]],
            stderr=subprocess.STDOUT, stdout=subprocess.PIPE, text=True)

        if len(result_style_test.stdout) != 0:
            print(result_style_test.stdout)
            delete_config()
            return False

    delete_config()

    return True


def run():
    arr_of_files = get_source_filenames()

    if style_test_result(arr_of_files):
        print('Style test: OK\n1')
    else:
        print('Style test: FAIL\n0')


run()
