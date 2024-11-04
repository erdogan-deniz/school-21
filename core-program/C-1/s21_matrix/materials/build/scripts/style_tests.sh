#!/bin/bash

# Path to folders
script_dir="$(dirname ${BASH_SOURCE[0]})"
project_dir="${script_dir}/.."

python3 ${project_dir}/tests/style_tests.py