echo "Введите расположение папок(пример - ./test/to/location):"
read location

echo "Введите количество папок:"
read num_folders

echo "Введите шаблон для названия файлов(пример - file):"
read file_template

for i in $(seq 1 $num_folders)
do
    mkdir "$location/folder$i"
    for j in {1..100}
    do
        mkdir "$location/folder$i/subfolder$j"
        for k in {1..100}
        do
            touch "$location/folder$i/subfolder$j/${file_template}${k}.txt"
        done
    done
done
