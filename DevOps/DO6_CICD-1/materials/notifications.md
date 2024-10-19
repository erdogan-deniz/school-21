## GitLab CI & Telegram

- Create a telegram bot
- Send the bot a message to get it set up to work with the user (you)
- Save the required values in **GitLab**:
  - *Settings* of the required repository;
  - **CI/CD** point;
  - *Secret variables*;
  - Save the token of the created bot to the *TELEGRAM_BOT_TOKEN* variable;
  - Save the ID of the user to be notified in *TELEGRAM_USER_ID*.

To send notifications in a convenient way, create a bash script, which will call **API Telegram** and send a message to the right user through the created bot. Here is an example of such a script:
```bash
URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"
TEXT="Deploy status: $1%0A%0AProject:+$CI_PROJECT_NAME%0AURL:+$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/%0ABranch:+$CI_COMMIT_REF_SLUG"

curl -s --max-time $TIME -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null
```

P.S. This script should be passed the status of the deployment as the first parameter.
