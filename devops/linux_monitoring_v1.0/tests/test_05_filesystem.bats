#!/usr/bin/env bats
#
# Tests for Part 5 (filesystem research).
# src/05/main.sh takes 1 parameter — an absolute or relative path
# ending with `/` — and prints filesystem stats:
#   - folder count, top 5 folders by size
#   - file count by extension category, top 10 files by size
#   - top 10 executables by size + MD5
#   - script execution time
#
# Validation: exactly 1 arg, must be an existing directory, must
# end with `/`.

setup() {
    SCRIPT="$BATS_TEST_DIRNAME/../src/05/main.sh"
    TMPDIR=$(mktemp -d)
    # Build a small fixture tree the script can traverse.
    mkdir -p "$TMPDIR/sub1" "$TMPDIR/sub2/deep"
    echo "alpha" > "$TMPDIR/file_a.txt"
    echo "beta"  > "$TMPDIR/file_b.conf"
    echo "gamma" > "$TMPDIR/sub1/file_c.log"
}

teardown() {
    rm -rf "$TMPDIR"
}

@test "rejects zero arguments" {
    run bash "$SCRIPT"
    [[ "$output" == *"Некорректный ввод"* ]]
}

@test "rejects two arguments" {
    run bash "$SCRIPT" /tmp/ /var/
    [[ "$output" == *"Некорректный ввод"* ]]
}

@test "rejects non-existent path" {
    run bash "$SCRIPT" "/this/path/does/not/exist/"
    [[ "$output" == *"Некорректный ввод"* ]]
}

@test "rejects path without trailing slash" {
    run bash "$SCRIPT" "$TMPDIR"
    [[ "$output" == *"Некорректный ввод"* ]]
}

@test "accepts directory path ending with /" {
    # Sourcing the sister `script.sh` requires running from src/05/.
    # Just verify the rejection path is NOT triggered.
    cd "$BATS_TEST_DIRNAME/../src/05" || skip "src/05 not accessible"
    run bash main.sh "$TMPDIR/"
    [[ "$output" != *"Некорректный ввод"* ]]
}

@test "script exists and is readable" {
    [ -f "$SCRIPT" ]
    [ -r "$SCRIPT" ]
}

@test "script.sh helper is co-located" {
    [ -f "$BATS_TEST_DIRNAME/../src/05/script.sh" ]
}
