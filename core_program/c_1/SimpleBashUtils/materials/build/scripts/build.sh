#!/bin/bash

# Input parameters
test_name=$1

# Path to folders
script_dir="$(dirname ${BASH_SOURCE[0]})"
project_dir="${script_dir}/.."

python3 ${project_dir}/tests/build.py ${test_name}