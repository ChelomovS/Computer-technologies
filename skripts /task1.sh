#!/bin/bash
# шебанг

# echo "Кису любишь!" - не будет выведено

KISA="Киса"
# печатаем содержимое переменной
echo $KISA
# печатаем случайное число
echo $RANDOM

# проверяем, есть ли директория "test"
if [ ! -d "test" ]; then
    # если нет, то создаем её
    mkdir test
else
    echo "директория 'test' уже есть."
fi

# заходим в test
cd test || exit  # если зайти не получилось, то выходим из скрипта

# счетчик n для файлов
n=0

if [ $# -ne 2 ]; then
    echo "Usage: $0 <количество уровней 1> <количество уровней 2>"
    exit 1
fi

# цикл для создания папок level1.1, level1.2 и т.д.
for ((i = 1; i <= $1; i++))
do
   # создаем папку level1.i (где i — номер уровня)
   mkdir level1.$i
   
   # вложенный цикл для создания папок level2.1, level2.2 и т.д.
   for ((j = 1; j <= $2; j++))
   do
      # создаем папку level2.j внутри level1.i
      mkdir level1.$i/level2.$j
      
      # увеличиваем счетчик n на 1
      n=$((n+1))
      
      # создаем файл TextFileN внутри level2.j и увеличиваем n 
      touch level1.$i/level2.$j/TextFile$n
      
      # пишем "This is file N" в только что созданный файл
      echo "This is file $n" > level1.$i/level2.$j/TextFile$n
      
      # показываем номер созданного файла на экране
      echo "создан файл: TextFile$n"
   done
done

# цикл для поиска всех файлов в текущей директории и её подкаталогах
for f in $(find . -type f)
do
  # переворачиваем содержимое каждого файла и записываем обратно
  rev "$f" > "$f"
done