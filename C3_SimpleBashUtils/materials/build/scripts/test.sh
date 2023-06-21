#!/bin/bash
echo -e "\n"
echo "*********************_________*********
***********************_______*********
***********************_______*********
*****************************__**************
_____________________********________********
_____________________********________********
______***********************________********
______***************_*______________********
______***************_*______________********
______***************________________********
*********************________________********
********_____________________________********
********_____________________________********
*****************************________********
______***********************________********
______***********************________********
______***********************________********"

echo "__  ___/__  ____/___  / / /__  __ \__  __ \___  / 
_____ \ _  /     __  /_/ / _  / / /_  / / /__  /  
____/ / / /___   _  __  /  / /_/ / / /_/ / _  /___
/____/  \____/   /_/ /_/   \____/  \____/  /_____/"

echo -e "\nMiniVERTER is watching your code...¯\_(*_*)_/¯\n"
set -e

echo -e "-------------------------------------------------------------------------------\n"
echo -e "Style test\n"
STYLE_TEST_SCRIPT=tests/style_tests.sh
OUTPUT=$(bash ${STYLE_TEST_SCRIPT})
STYLE_TEST_RESULT=${OUTPUT: -1}
printf 'Style test output:\n %s\n' "$OUTPUT"
printf 'Style test result: %s\n' "$STYLE_TEST_RESULT"
echo -e "-------------------------------------------------------------------------------\n"

TEST_JSON=tests/tests.json

for TEST_NUMBER in $(jq ".tests[].number" ${TEST_JSON}); do
  NAME_CATEGORY=$(jq -r ".tests[$TEST_NUMBER].name" ${TEST_JSON})
  IFS='.' read -ra ARR_NAME_CATEGORY <<< "$NAME_CATEGORY"
  NAME=${ARR_NAME_CATEGORY[0]}
  CATEGORY=${ARR_NAME_CATEGORY[1]}
  PART=${CATEGORY: -1}

  if [ "$LAST_PART" != "$PART" ]
  then
    echo -e "Part:" ${NAME}"\n"
    LAST_PART=$PART
    BUILD_SCRIPT=ci-scripts/build.sh
    OUTPUT=$(bash ${BUILD_SCRIPT} ${NAME})
    BUILD_RESULT=${OUTPUT: -1}
    printf 'Build output:\n %s\n' "$OUTPUT"
    printf 'Build result: %s\n' "$BUILD_RESULT"
    echo -e "-------------------------------------------------------------------------------\n"
  fi
done


