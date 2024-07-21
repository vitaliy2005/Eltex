output_file="/home/warg/Рабочий стол/Eltex/module1/3/output.txt"

current_time=$(date +"%Y-%m-%d %H:%M:%S")

if [ ! -f "$output_file" ]; then
    line_number=1
else
    line_number=$(( $(wc -l < "$output_file") + 1 ))
fi

echo "$current_time I run $line_number" >> "$output_file"
