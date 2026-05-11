#!/usr/bin/env bats
#
# Tests for devops/linux_monitoring_v1.0 Part 2 (`config_info`).
# src/02/main.sh reads ~16 lines of system info (HOSTNAME, TIMEZONE,
# USER, OS, DATE, UPTIME, UPTIME_SEC, IP, MASK, GATEWAY, RAM_*,
# SPACE_*) and prompts the user to save the snapshot to a date-stamped
# `.status` file ("Y" to save, anything else cancels).
#
# Tests run with a temporary HOME so the optional Y-path saves into a
# scratch directory we can assert on / clean up.

setup() {
    SCRIPT="$BATS_TEST_DIRNAME/../src/02/main.sh"
    TMPDIR=$(mktemp -d)
}

teardown() {
    rm -rf "$TMPDIR"
}

@test "script exists and is readable" {
    [ -f "$SCRIPT" ]
    [ -r "$SCRIPT" ]
}

@test "answering N prints cancellation message" {
    run bash "$SCRIPT" <<< "N"
    [[ "$output" == *"Сохранение отменено"* ]]
}

@test "answering n (lowercase) prints cancellation message" {
    run bash "$SCRIPT" <<< "n"
    # Script only treats 'Y'/'y' as save — anything else cancels.
    [[ "$output" == *"Сохранение отменено"* ]]
}

@test "answering Y saves the snapshot to a .status file" {
    cd "$TMPDIR" || return 1
    run bash "$SCRIPT" <<< "Y"
    [[ "$output" == *"Данные сохранились"* ]]
    # File name has the form DD_MM_YYYY_HH_MM_SS.status — match any of those.
    shopt -s nullglob
    saved=( "$TMPDIR"/*.status )
    [ "${#saved[@]}" -ge 1 ]
}

@test "output contains the HOSTNAME field" {
    run bash "$SCRIPT" <<< "N"
    [[ "$output" == *"HOSTNAME"* ]]
}

@test "output contains the USER field" {
    run bash "$SCRIPT" <<< "N"
    [[ "$output" == *"USER"* ]]
}

@test "output contains the DATE field" {
    run bash "$SCRIPT" <<< "N"
    [[ "$output" == *"DATE"* ]]
}

@test "output contains all 3 RAM fields" {
    run bash "$SCRIPT" <<< "N"
    [[ "$output" == *"RAM TOTAL"* ]]
    [[ "$output" == *"RAM USED"* ]]
    [[ "$output" == *"RAM FREE"* ]]
}

@test "output contains all 3 SPACE fields" {
    run bash "$SCRIPT" <<< "N"
    [[ "$output" == *"SPACE ROOT"* ]]
    [[ "$output" == *"SPACE ROOT USED"* ]]
    [[ "$output" == *"SPACE ROOT FREE"* ]]
}

@test "output contains the UPTIME and UPTIME_SEC pair" {
    run bash "$SCRIPT" <<< "N"
    [[ "$output" == *"UPTIME ="* ]]
    [[ "$output" == *"UPTIME_SEC ="* ]]
}
