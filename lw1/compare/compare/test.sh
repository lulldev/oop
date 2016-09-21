# configuration
debugBuildPath=/Users/lull/Library/Caches/AppCode2016.2/DerivedData/compare-aauthhrouyackjffygwjoenwnfwg/Build/Products/Debug/
debugBuildName="compare"
testingDataPath=/Users/lull/Yandex.Disk.localized/OOP/lw1/compare/compare/testing

cd ${debugBuildPath}

echo "Тестирование программы:\n"

#### Проверки на вход

# Отсутствие аргументов

./$debugBuildName
if [ $? -eq 0 ]; then
    echo "[ОШИБКА] Проверка на входе аргументов"
fi

./$debugBuildName ${testingDataPath}/no-exists.txt
if [ $? -eq 0 ]; then
    echo "[ОШИБКА] Проверка на вход несуществующего файла"
fi

./$debugBuildName ${testingDataPath}/empty1.txt
if [ $? -eq 0 ]; then
    echo "[ОШИБКА] Проверка на вход одного аргумента"
fi
./$debugBuildName ${testingDataPath}/empty1.txt ${testingDataPath}/empty2.txt ${testingDataPath}/file1.txt
if [ $? -eq 0 ]; then
    echo "[ОШИБКА] Проверка множества аргументов"
fi

#### Проверки на тестовых данных

# Оба пустых

./$debugBuildName ${testingDataPath}/empty1.txt ${testingDataPath}/empty2.txt
if [ $? -eq 1 ]; then
    echo "[ОШИБКА] Программа: тестирование пустых файлов"
    exit
fi
diff ${testingDataPath}/empty1.txt ${testingDataPath}/empty2.txt
if [ $? -eq 1 ]; then
    echo "[ОШИБКА] diff: тестирование пустых файлов"
    exit

fi

# Один пустой другой нет

./$debugBuildName ${testingDataPath}/empty1.txt ${testingDataPath}/no-empty.txt
if [ $? -eq 0 ]; then
    echo "[ОШИБКА] Программа: тестирование пустого и не пустого файла"
    exit
fi
diff ${testingDataPath}/empty1.txt ${testingDataPath}/no-empty.txt
if [ $? -eq 0 ]; then
    echo "[ОШИБКА] diff: тестирование пустого и не пустого файла"
    exit

fi

# Оба одинаковы

./$debugBuildName ${testingDataPath}/equal1.txt ${testingDataPath}/equal2.txt
if [ $? -eq 1 ]; then
    echo "[ОШИБКА] Программа: тестирование одинаковых файлов"
    exit
fi
diff ${testingDataPath}/equal1.txt ${testingDataPath}/equal2.txt
if [ $? -eq 1 ]; then
    echo "[ОШИБКА] diff: тестирование одинаковых файлов"
fi

# Из одной строки

./$debugBuildName ${testingDataPath}/one-lines1.txt ${testingDataPath}/one-lines2.txt
if [ $? -eq 1 ]; then
    echo "[ОШИБКА] Программа: тестирование однострочных файлов"
    exit
fi
diff ${testingDataPath}/one-lines1.txt ${testingDataPath}/one-lines2.txt
if [ $? -eq 1 ]; then
    echo "[ОШИБКА] diff: тестирование однострочных файлов"
    exit
fi

# Из нескольких строк

./$debugBuildName ${testingDataPath}/multi-lines1.txt ${testingDataPath}/multi-lines2.txt
if [ $? -eq 1 ]; then
    echo "[ОШИБКА] Программа: тестирование многострочных файлов"
    exit
fi
diff ${testingDataPath}/multi-lines1.txt ${testingDataPath}/multi-lines2.txt
if [ $? -eq 1 ]; then
    echo "[ОШИБКА] diff: тестирование многострочных файлов"
    exit
fi

# Заведомо неодинаковых произвольных файлов

./$debugBuildName ${testingDataPath}/file1.txt ${testingDataPath}/file2.txt
if [ $? -eq 0 ]; then
    echo "[ОШИБКА] Программа: сравниваемые файлы заведомо неодинаковы"
    exit
fi
diff ${testingDataPath}/file1.txt ${testingDataPath}/file2.txt
if [ $? -eq 0 ]; then
    echo "[ОШИБКА] diff: сравниваемые файлы заведомо неодинаковы"
    exit
fi

./$debugBuildName ${testingDataPath}/file2.txt ${testingDataPath}/file1.txt
if [ $? -eq 0 ]; then
    echo "[ОШИБКА] Программа: сравниваемые файлы заведомо неодинаковы"
    exit
fi
diff ${testingDataPath}/file1.txt ${testingDataPath}/file2.txt
if [ $? -eq 0 ]; then
    echo "[ОШИБКА] diff: сравниваемые файлы заведомо неодинаковы"
    exit
fi


echo "\nТестирование завершено успешно!"
exit

