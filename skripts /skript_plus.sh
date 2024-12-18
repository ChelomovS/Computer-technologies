#!/bin/bash
# шебанг, скрипт нa bash

tl='|' 

# Цикл, добавляем '-' в tl, пока не дойдем до 0
for ((i=$2; $i; i--))
do
   tl=echo "$tl-"  # добавляем '-' к tl
done

# получаем список файлов и папок в директории "$1"
line=ls $1

# иттериуемся по каждому файлу/папке из списка
for word in $(ls -m)  # получаем имена файлов через запятую
do  
  word=${word%,}    # убираем запятую в конце имени
  echo "$tl$word,"  # печатаем текущий уровень и имя файла с запятой

  # проверяем, если уровень больше 0 и это директория
  if [ $2 -gt 0 ] && [ -d "$word" ]; then 
     nextlev=$(($2 - 1))  # уменьшаем уровень на 1 для следующего уровня
     bash $0 "$1/$word" $nextlev  # рекурсивно запускаем наш скрипт для вложенной папки
  fi
done