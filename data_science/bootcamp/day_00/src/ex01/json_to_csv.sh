#!/bin/sh.

JQ_FLAGS="-rf"

FILTER_FILE="filter.jq"

JSON_FILE="hh.json"
JSON_FILE_PATH="../ex00/"

RES_FILE="hh.csv"

jq $JQ_FLAGS $FILTER_FILE $JSON_FILE_PATH$JSON_FILE > $RES_FILE && clear
