#!/bin/bash

TELEGRAM_BOT_TOKEN="7435474656:AAH1aZzJYqaGMmR2ha_Q8NnLFEut6_41GcU"
TELEGRAM_USER_ID="444897129"

# TELEGRAM_BOT_TOKEN="тут токен"
# TELEGRAM_USER_ID="тут id"
DATE_TIME=$(TZ="Europe/Moscow" date +"%Y-%m-%d %H:%M:%S")

TIME="10"
URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/"

status="🚫"

if [ "$CI_JOB_STATUS" == "success" ]; then 
   #  все хорошо
   # статус текущего этапа
   status="✅"
   TEXT="Статус этапа +$CI_JOB_STAGE по задаче $CI_JOB_NAME: $status
   Дата-время: $DATE_TIME"

   curl -s --max-time $TIME -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL"sendMessage" > /dev/null

   # статус итого
   sheldon_to_end=https://avatars.dzeninfra.ru/get-zen_doc/3668119/pub_5f4a88cafe0a9948592b02a0_5f4a88f16f855d0a7aa70e37/scale_1200; 

   # Отправка изображения Шелдона
   curl -s --max-time $TIME -F "chat_id=$TELEGRAM_USER_ID" -F "photo=$sheldon_to_end" $URL"sendPhoto" > /dev/null

   TEXT="Статус продакш: ✅
      
      Проект:+$CI_PROJECT_NAME
      Репозиторий:+$CI_PROJECT_URL
      Ветка:+$CI_COMMIT_REF_SLUG
      
   Автор:+$GITLAB_USER_LOGIN
   Дата-время: $DATE_TIME"

   curl -s --max-time $TIME -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL"sendMessage" > /dev/null

else

   # КОНЕЦ((
   # статус текущего этапа
   TEXT="Статус этапа +$CI_JOB_STAGE по задаче $CI_JOB_NAME: $status
   Дата-время: $DATE_TIME"

   curl -s --max-time $TIME -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL"sendMessage" > /dev/null
   
   # статус итого
   sheldon_to_end=https://donate.petridish.pw/sites/default/files/stickers/127260/7_88.png?1633075049
   # Отправка изображения Шелдона
   curl -s --max-time $TIME -F "chat_id=$TELEGRAM_USER_ID" -F "photo=$sheldon_to_end" $URL"sendPhoto" > /dev/null

   TEXT="Статус продакш: ❌
    
   Проект:+$CI_PROJECT_NAME
   Репозиторий:+$CI_PROJECT_URL
   Ветка:+$CI_COMMIT_REF_SLUG
    
   Автор:+$GITLAB_USER_LOGIN
   Дата-время: $DATE_TIME"

   curl -s --max-time $TIME -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL"sendMessage" > /dev/null

fi

