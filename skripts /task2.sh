#!/bin/bash
# шебанг, скрипт на bash

cd ~  # переходим в корневую директорию

# проверяем, есть ли папка dirs
if [ -d dirs ]
then
  # если есть, то удаляем ее вместе со всем содержимым
  rm -r dirs
fi

num=$1  # берем первый аргумент как количество уровней
x=1     # начинаем с 1

# создаем новую папку dirs
mkdir dirs
cd dirs  # заходим в неё

# пока x меньше или равно num
while [ $x -le $num ]
do
  mkdir $x  # создаем папку с номером x
  cd $x     # заходим в эту папку
  y=1       # начинаем счетчик y с 1
  
  # пока y меньше или равно num
  while [ $y -le $num ]
  do
    mkdir $x$y  # создаем папку с номером xy (например, 11, 12 и т.д.)
    echo "$x$y" > $x$y/$x$y  # пишем в файл внутри этой папки его имя
    y=$(( $y+1 ))  # увеличиваем y на 1
  done
  
  cd ..  # возвращаемся обратно в папку dirs
  x=$(( $x+1 ))  # увеличиваем x на 1 для следующей итерации
done
 