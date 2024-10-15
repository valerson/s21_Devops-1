#!/bin/bash

TELEGRAM_BOT_TOKEN="7435474656:AAH1aZzJYqaGMmR2ha_Q8NnLFEut6_41GcU"
TELEGRAM_USER_ID="444897129"

DATE_TIME=$(TZ="Europe/Moscow" date +"%Y-%m-%d %H:%M:%S")

TIME="10"
URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"

TEXT="Можно запустить этап deploy (размещение на "боевой" сервер).
Для запуска перейдите по ссылке и жмакните кнопочку старт
"$CI_PROJECT_URL/-/pipelines/$CI_PIPELINE_ID"

Автор:+$GITLAB_USER_LOGIN
Дата-время: $DATE_TIME"

curl -s --max-time $TIME -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null