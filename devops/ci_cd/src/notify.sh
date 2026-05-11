#!/bin/bash
#
# Telegram CI/CD pipeline notifier.
#
# Reads two secrets from the environment so the bot token never ends up
# in version control. Set both in your CI provider's secret store
# (GitLab CI → Settings → CI/CD → Variables; GitHub Actions →
# repository secrets):
#
#   TELEGRAM_BOT_TOKEN   The full bot token returned by @BotFather.
#   TELEGRAM_CHAT_ID     The numeric chat ID to push notifications to
#                        (use @userinfobot to look it up).
#
# Stage name (e.g. "build", "deploy") is the only positional arg.
# Other CI metadata is read from the standard GitLab CI env vars.
#
# NOTE: a previous version of this file had the bot token hard-coded.
# That token has been rotated; do not attempt to reuse what `git log`
# might surface.

set -euo pipefail

stage="${1:-unknown}"

: "${TELEGRAM_BOT_TOKEN:?env var TELEGRAM_BOT_TOKEN must be set}"
: "${TELEGRAM_CHAT_ID:?env var TELEGRAM_CHAT_ID must be set}"

url="https://api.telegram.org/bot${TELEGRAM_BOT_TOKEN}/sendMessage"
text="CI/CD STAGE: ${stage}%0A%0AProject:+${CI_PROJECT_NAME:-?}%0AStatus:+${CI_JOB_STATUS:-?}%0AURL:+${CI_PROJECT_URL:-?}/pipelines/${CI_PIPELINE_ID:-?}/%0ABranch:+${CI_COMMIT_REF_SLUG:-?}"

curl -s -d "chat_id=${TELEGRAM_CHAT_ID}&disable_web_page_preview=1&text=${text}" "$url" > /dev/null
