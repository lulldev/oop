# configuration
debugBuildPath=/Users/lull/Library/Caches/AppCode2016.2/DerivedData/calcbits-fhqguovuidcgcvcmtachtpngzqla/Build/Products/Debug
debugBuildName="calcbits"
cd ${debugBuildPath}

echo "Тестирование программы:\n"

./$debugBuildName
if [ $? -eq 0 ]; then
    echo "[ОШИБКА] Отсутствие аргумента\n"
fi

./$debugBuildName 1 1
if [ $? -eq 0 ]; then
    echo "[ОШИБКА] Недопустимое кол-во аргументов\n"
fi

./$debugBuildName s
if [ $? -eq 0 ]; then
    echo "[ОШИБКА] Недопустимое входное строковое значение\n"
fi

./$debugBuildName -1
if [ $? -eq 0 ]; then
    echo "[ОШИБКА] Недопустимое отрицательное значение\n"
fi

./$debugBuildName 0 >> testing/output1.txt
diff testing/output1.txt testing/expected0.txt
if [ $? -eq 1 ]; then
    echo "[ОШИБКА] Верное значение\n"
fi

./$debugBuildName 1 >> testing/output2.txt
diff testing/output2.txt testing/expected1.txt
if [ $? -eq 1 ]; then
    echo "[ОШИБКА] Верное значение\n"
fi

./$debugBuildName 9 >> testing/output3.txt
diff testing/output3.txt testing/expected9.txt
if [ $? -eq 1 ]; then
    echo "[ОШИБКА] Верное значение\n"
fi

echo "\nТестирование завершено успешно!"
exit

