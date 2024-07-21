#!/bin/bash

# Запрашиваем у пользователя имя процесса
read -p "Введите имя процесса для поиска логов: " process_name

# Запрашиваем временной промежуток
read -p "Введите начальную дату и время (формат: YYYY-MM-DD HH:MM): " start_time
read -p "Введите конечную дату и время (формат: YYYY-MM-DD HH:MM): " end_time

# Преобразуем введенные даты в формат timestamp
start_timestamp=$(date -d "$start_time" +%s)
end_timestamp=$(date -d "$end_time" +%s)

# Проверяем, что даты корректны
if [[ -z "$start_timestamp" || -z "$end_timestamp" ]]; then
    echo "Некорректные даты."
    exit 1
fi

# Находим логи с указанным процессом
log_file="/var/log/syslog"  # Замените этот путь на путь к вашим логам, если это необходимо.

echo "Ищем логи для процесса '$process_name' с $start_time по $end_time..."

grep "$process_name" "$log_file" | while IFS= read -r line; do
    # Извлекаем временную метку из логов (может потребоваться настройка в зависимости от формата логов)
    log_time=$(echo "$line" | awk '{print $1 " " $2 " " $3}')
    log_timestamp=$(date -d "$log_time" +%s)

    # Проверяем, попадает ли временная метка в указанный промежуток
    if [[ $log_timestamp -ge $start_timestamp && $log_timestamp -le $end_timestamp ]]; then
        echo "$line"
    fi
done
