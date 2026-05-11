#!/usr/bin/env bats
#
# Smoke tests for Parts 2 and 4 — they interact with the live system
# (Part 2 reads hostname/RAM/disk; Part 4 reads colors.cfg). Full
# behavioural tests for those would need a heavy fixture; here we
# just verify script invariants.

@test "Part 2 main.sh exists and prints HOSTNAME line" {
    run bash "$BATS_TEST_DIRNAME/../src/02/main.sh" <<< "N"
    [[ "$output" == *"HOSTNAME"* ]]
}

@test "Part 4 colors.cfg exists" {
    [ -f "$BATS_TEST_DIRNAME/../src/04/colors.cfg" ]
}

@test "Part 4 main.sh exists" {
    [ -f "$BATS_TEST_DIRNAME/../src/04/main.sh" ]
}

@test "every Part has main.sh entry point" {
    for n in 01 02 03 04 05; do
        [ -f "$BATS_TEST_DIRNAME/../src/$n/main.sh" ] || \
            { echo "missing: src/$n/main.sh"; return 1; }
    done
}
