#!/bin/bash

check_process() {
    while true; do
        if pgrep $process_name > /dev/null; then
            echo "Процесс $process_name запущен."
        else
            echo "Процесс $process_name остановлен. Попытка возобновления..."
            systemctl start $process_name
        fi
        sleep $interval
    done
}

read -p "Введите имя процесса для контроля: " process_name

read -p "Введите периодичность проверки в секундах: " interval

check_process
