#!/bin/bash
source config.txt
grep "$process_name" /var/log/syslog | awk -v start="$start_time" -v end="$end_time" '$1 >= start && $1 <= end'
