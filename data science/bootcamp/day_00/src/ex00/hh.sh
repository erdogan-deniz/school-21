#!/bin/sh.

URL="https://api.hh.ru/"

CHAPTER="vacancies"

ARG_ONE="text="
ARG_TWO="per_page="
ARG_THREE="search_field="

ARG_ONE_VAL="data%20scientist"
ARG_TWO_VAL="20"
ARG_THREE_VAL="name"

REQUEST=$URL$CHAPTER'?'$ARG_ONE$ARG_ONE_VAL"&"$ARG_TWO$ARG_TWO_VAL"&"$ARG_THREE$ARG_THREE_VAL

RES_FILE="hh.json"

curl $REQUEST | jq '.' > $RES_FILE && clear
