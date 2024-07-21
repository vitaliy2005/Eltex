#!/bin/bash
SOURCE_DIR=""
DEST_DIR=""
ARCHIVE_NAME="backup_$(date +%Y%m%d).tar"


backup() {

    mkdir -p "$TARGET_DIR"

    tar -cvf "$TARGET_DIR/$ARCHIVE_NAME" -C "$SOURCE_DIR" .

    echo "Резервная копия была успешно создана в $dest_dir"

    if [ ! -f "$TARGET_DIR/$ARCHIVE_NAME" ]; then
        echo "Архив не найден: $TARGET_DIR/$ARCHIVE_NAME"
        exit 1
      fi

      # Распаковываем архив
      tar -xvf "$TARGET_DIR/$ARCHIVE_NAME" -C "$TARGET_DIR"
      echo "Архив распакован в: $TARGET_DIR"
}

# Пользовательский интерфейс
echo "Введите путь к директории, которую хотите сохранить: "
read -r SOURCE_DIR

echo "Введите путь к директории для хранения резервной копии: "
read -r DEST_DIR

echo "Укажите периодичность в часах"
read -r frequency

TARGET_DIR="$DEST_DIR/backup_folder"

while true; do
  backup   # Создаем резервную копию
  sleep $(($frequency*3600))  # Ждем перед следующим выполнением
done
