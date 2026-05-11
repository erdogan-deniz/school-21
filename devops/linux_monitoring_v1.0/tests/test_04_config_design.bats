#!/usr/bin/env bats
#
# Tests for devops/linux_monitoring_v1.0 Part 4 (`config_design`).
# src/04/main.sh sources colors.cfg (with column1_background,
# column1_font_color, column2_background, column2_font_color in
# [1, 6]) and prints the system snapshot coloured according to those
# four codes. Output is the same set of fields as Part 2 plus a
# coloured ANSI envelope.
#
# Part 4 is single-shot (no interactive prompt) and must be run from
# src/04/ so that `source colors.cfg` resolves correctly.

setup() {
    SRCDIR="$BATS_TEST_DIRNAME/../src/04"
    SCRIPT="$SRCDIR/main.sh"
    CONFIG="$SRCDIR/colors.cfg"
}

@test "script exists and is readable" {
    [ -f "$SCRIPT" ]
    [ -r "$SCRIPT" ]
}

@test "colors.cfg exists and is readable" {
    [ -f "$CONFIG" ]
    [ -r "$CONFIG" ]
}

@test "colors.cfg declares the 4 expected variables" {
    run grep -E '^column[12]_(background|font_color)=' "$CONFIG"
    [ "$status" -eq 0 ]
    [ $(wc -l <<< "$output") -eq 4 ]
}

@test "output contains the HOSTNAME field" {
    cd "$SRCDIR" || skip "src/04 not accessible"
    run bash main.sh
    [[ "$output" == *"HOSTNAME"* ]]
}

@test "output contains all 3 RAM fields" {
    cd "$SRCDIR" || skip "src/04 not accessible"
    run bash main.sh
    [[ "$output" == *"RAM_TOTAL"* ]]
    [[ "$output" == *"RAM_USED"* ]]
    [[ "$output" == *"RAM_FREE"* ]]
}

@test "output contains all 3 SPACE_ROOT fields" {
    cd "$SRCDIR" || skip "src/04 not accessible"
    run bash main.sh
    [[ "$output" == *"SPACE_ROOT"* ]]
    [[ "$output" == *"SPACE_ROOT_USED"* ]]
    [[ "$output" == *"SPACE_ROOT_FREE"* ]]
}

@test "output reports the selected colour codes verbatim" {
    cd "$SRCDIR" || skip "src/04 not accessible"
    run bash main.sh
    # The script trailers echo the 4 colour codes back as plain text.
    [[ "$output" == *"Column 1 background ="* ]]
    [[ "$output" == *"Column 1 font color ="* ]]
    [[ "$output" == *"Column 2 background ="* ]]
    [[ "$output" == *"Column 2 font color ="* ]]
}

@test "output embeds ANSI colour-reset escape \\033[0m" {
    cd "$SRCDIR" || skip "src/04 not accessible"
    run bash main.sh
    # The coloured `echo -e` lines all close with the reset sequence.
    [[ "$output" == *$'\033[0m'* ]]
}

@test "default config values are within [1, 6] range" {
    # Sourcing the config in a subshell to avoid leaking vars.
    (
        set -e
        # shellcheck source=/dev/null
        source "$CONFIG"
        [[ "$column1_background" =~ ^[1-6]$ ]]
        [[ "$column1_font_color" =~ ^[1-6]$ ]]
        [[ "$column2_background" =~ ^[1-6]$ ]]
        [[ "$column2_font_color" =~ ^[1-6]$ ]]
    )
}
