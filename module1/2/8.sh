#!/bin/bash

echo "Введите время для будильника (формат ЧЧ:ММ): "
read alarm_time

echo "Введите путь к звуковому файлу: "
read sound_file

current_time=$(date +"%H:%M")

while [ "$current_time" != "$alarm_time" ]
do
    current_time=$(date +"%H:%M")
    sleep 5
done

echo "Время прозвенеть!"
play $sound_file
