#!/bin/bash

URL="https://api.telegram.org/bot8015361574:AAFjUnW5hv_62Dsa9SfIkDgjCnAxraoxw8A/sendMessage"
TEXT="CI/CD STAGE: $1%0A%0AProject:+$CI_PROJECT_NAME%0AStatus:+$CI_JOB_STATUS%0AURL:+$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/%0ABranch:+$CI_COMMIT_REF_SLUG"

curl -s -d "chat_id=371994503&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null