#!/usr/bin/env bats
#
# Tests for Part 3 (visual output design).
# src/03/main.sh takes 4 parameters, each in [1, 6]:
#   1=white, 2=red, 3=green, 4=blue, 5=purple, 6=black
# Param 1: background of names; 2: font of names;
# Param 3: background of values; 4: font of values.
# Validation: 4 args required, each must be 1-6, columns'
# bg/fg must differ.

setup() {
    SCRIPT="$BATS_TEST_DIRNAME/../src/03/main.sh"
}

@test "rejects zero arguments" {
    run bash "$SCRIPT"
    [[ "$output" == *"4 параметра"* ]]
}

@test "rejects three arguments" {
    run bash "$SCRIPT" 1 2 3
    [[ "$output" == *"4 параметра"* ]]
}

@test "rejects five arguments" {
    run bash "$SCRIPT" 1 2 3 4 5
    [[ "$output" == *"4 параметра"* ]]
}

@test "rejects out-of-range value 0" {
    run bash "$SCRIPT" 0 2 3 4
    [[ "$output" == *"не подходит"* ]]
}

@test "rejects out-of-range value 7" {
    run bash "$SCRIPT" 1 2 3 7
    [[ "$output" == *"не подходит"* ]]
}

@test "rejects non-numeric value" {
    run bash "$SCRIPT" 1 2 3 red
    [[ "$output" == *"не подходит"* ]]
}

@test "rejects equal bg and fg in column 1 (params 1 & 2)" {
    run bash "$SCRIPT" 3 3 1 2
    [[ "$output" == *"совпадать"* ]]
}

@test "rejects equal bg and fg in column 2 (params 3 & 4)" {
    run bash "$SCRIPT" 1 2 5 5
    [[ "$output" == *"совпадать"* ]]
}

@test "script exists and is readable" {
    [ -f "$SCRIPT" ]
    [ -r "$SCRIPT" ]
}
