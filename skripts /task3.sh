#! /bin/bash
# шебанг

i=1  # начинаем с 1

# цикл пока i меньше 5
while [ $i -lt 5 ]
do
  cd dir$i  # Заходим в папку dir1, dir2 ... 
  echo $(rev file$i) > file$i  # Реверсируем содержимое file$i и записываем обратно
  i=$(( $i + 1 ))  # иттерируем
done

# echo $1  # Если нужно вывести первый аргумент, то раскомментируем

mkdir "Directory"  # Создаем папку с именем Directory
cd "Directory"  # Заходим в новую папку

# запускаем цикл от 1 до значения первого аргумента
for ((i = 1; i <= $1; i++))
do
   mkdir "Folder $i"  # создаем папку Folder i
   
   # Запускаем вложенный цикл от 1 до значения второго аргумента ($2)
   for ((j = 1; j <= $2; j++))
   do
      touch "Folder $i/File $j"  # Создаем файл File j внутри Folder i
      
      # Запускаем еще один вложенный цикл от 1 до значения третьего аргумента 
      for ((k = 1; k <= $3; k++))
      do
         # Пишем в файл сообщение о том, что мы в конкретном файле и папке
         echo You have come to the File number $j of the Folder number $i >> "Folder $i/File $j" 
      done   
   done
done