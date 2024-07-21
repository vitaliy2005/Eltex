#!/bin/bash

read -p "Введите имя процесса: " process_name
read -p "Введите начальное время (в формате HH:MM): " start_time
read -p "Введите конечное время (в формате HH:MM): " end_time

grep "$process_name" /var/log/syslog | awk -v start="$start_time" -v end="$end_time" '$1 >= start && $1 <= end'

