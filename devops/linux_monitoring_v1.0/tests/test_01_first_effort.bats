#!/usr/bin/env bats
#
# Tests for devops/linux_monitoring_v1.0 Part 1 (`first effort`).
# Validates the input-validation behaviour of src/01/main.sh:
#   - exactly one parameter required
#   - the parameter must NOT match a number regex
#   - otherwise echo it back verbatim
#
# Run with:
#     bats tests/test_01_first_effort.bats

setup() {
    SCRIPT="$BATS_TEST_DIRNAME/../src/01/main.sh"
}

@test "rejects zero arguments" {
    run bash "$SCRIPT"
    [ "$status" -eq 0 ]
    [[ "$output" == *"Некорректный ввод"* ]] || [[ "$output" == *"количество параметров"* ]]
}

@test "rejects two arguments" {
    run bash "$SCRIPT" foo bar
    [ "$status" -eq 0 ]
    [[ "$output" == *"Некорректный ввод"* ]] || [[ "$output" == *"количество параметров"* ]]
}

@test "rejects integer argument 42" {
    run bash "$SCRIPT" 42
    [ "$status" -eq 0 ]
    [[ "$output" == *"текстовый"* ]] || [[ "$output" == *"Параметр должен быть"* ]]
}

@test "rejects negative integer -7" {
    run bash "$SCRIPT" -7
    [ "$status" -eq 0 ]
    [[ "$output" == *"текстовый"* ]] || [[ "$output" == *"Параметр должен быть"* ]]
}

@test "rejects float 3.14" {
    run bash "$SCRIPT" 3.14
    [ "$status" -eq 0 ]
    [[ "$output" == *"текстовый"* ]] || [[ "$output" == *"Параметр должен быть"* ]]
}

@test "accepts simple text argument" {
    run bash "$SCRIPT" hello
    [ "$status" -eq 0 ]
    [ "$output" = "hello" ]
}

@test "accepts text with spaces (quoted)" {
    run bash "$SCRIPT" "School 21"
    [ "$status" -eq 0 ]
    [ "$output" = "School 21" ]
}

@test "script exists and is readable" {
    [ -f "$SCRIPT" ]
    [ -r "$SCRIPT" ]
}
