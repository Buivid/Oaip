# Лабораторные работы ОАИП

## Содержание:

1. **[Лабораторная 1](#лабораторная-1)**
2. **[Лабораторная 2](#лабораторная-2)**

## Лабораторная 1
- Реализовать функцию для создания массива структур.
- Реализовать функцию для вывода массива структур на экран.
- Реализовать функцию для инициализации экземпляра структуры.
- Реализовать функции сортировки массива по каждому полю структуры. (Например, можно отсортировать студентов сначала по дате рождения, затем передумать и отсортировать по среднему баллу).
- Реализовать меню, для проверки функционала.
- Функции не должны привязываться к конкретному массиву: таковой должен передаваться в качестве аргумента.
- В качестве типа одного из полей структуры использовать enum (например, для цвета).
- Реализовать функцию для удаления структуры из массива.
- Реализовать сортировку по двум полям одновременно. (Например, отсортировать автомобили по цвету, на так чтобы все автомобили одного цвета шли в порядке года выпуска).
- Для заполнения структур распарсить html-файл любого списка или каталога.

## Лабораторная 2

Написать программу сжатия текстового файла по алгоритму:
1. Подсчет частоты встречи каждого слова в файле.
2. Поиск самого популярного среди длинных слов (А).
3. Поиск самого непопулярного среди коротких слов (В).
4. Замена всех слов А и В друг на друга.
5. Повтор пунктов 2-4 до тех пор, пока это имеет смысл.

- Программа должна сжать и разжать текстовый файл по приведенному выше алгоритму.
- В результате работы должно быть создано два файла: сжатый и разжатый. Последний должен полностью совпадать с исходным. Сжатый файл должен быть меньше исходного.
- При выборе слова А и В понятия «длинное слово» и «короткое слово» можно трактовать гибко. То есть, «длинное слово» необязательно «самое длинное слово», главное, чтобы его использование имело положительный эффект.
- Сжатие и разжатие файла реализовать двумя разными программами (два отдельных проекта).
- Следовательно, в сжатый файл должны быть упакованы данные, необходимые для точного разжатия.
- Для реализации пункта 1 алгоритма использовать собственный связный список (стек или очередь).
