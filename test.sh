#!/bin/bash

# Запоминаем текущую директорию
original_dir=$(pwd)

# Переходим в папку build
cd build || { echo "Не удалось перейти в папку build"; exit 1; }

# Функция для проверки и выполнения команды ctest
check_and_test() {
    local dir_name="$1"
    if [ -d "$dir_name" ]; then
        cd "$dir_name" || { echo "Не удалось перейти в папку $dir_name"; return 1; }
        echo "Выполняем ctest в папке $dir_name"
        ctest --verbose
        cd .. || { echo "Не удалось вернуться в папку build"; return 1; }
    fi
}

# Перебираем все директории, соответствующие шаблону lab*
for dir in lab*/; do
    # Убираем слэш в конце имени директории
    dir=${dir%/}
    check_and_test "$dir"
done

# Возвращаемся в исходную директорию
cd "$original_dir" || { echo "Не удалось вернуться в исходную директорию"; exit 1; }
