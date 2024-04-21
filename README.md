# Домашняя работа 2

### дедлайн 21.04 23:59

## Ответвление
Создать fork, в нем создать дополнительную ветку develop, работу выполнять в ней. По итогу выполнения сделать pull-request из ветки develop в ветку main (своего репозитория), назначить меня ревьюером (assistent-ees).  

## Задание
Разработать ШАБЛОННЫЙ класс матрицы:
1) Матрица должна содержать методы для считывания (возможнен ввод данных с размерами и без размеров для матриц, ссозданных с заданым размером) и вывода(желательно перегрузить операторы >> и <<). 
Матрица может считываться из консоли или файла, а также выводить в консоль или файл. 
Пример ввода: N M строка1столбец1 строка1столбец2 … строкаNстолбецM , где N – число строк, M – число 
столбцов.
2) Реализовать несколько конструкторов: пустой матрицы, матрицы заданного размера и для считывания матрицы из файла (возможно большее количество конструкторов);
3) Перегрузить операторы - и + для вычитания и сложения матриц;
4) Перегрузить оператор * для умножения матриц, умножения матрицы на скаляры;
5) Перегрузить оператор ! для вычисления обратной матрицы (использовать исключения для обработки случая, когда матрица необратима);
6) Перегрузить оператор присваивания; 
7) Добавить статические методы создания нулевых и единичных матриц указанного размера;

(Предполагается доработка матрицы из прошлой домашней работы.)

#### Примечание
1) Матрица равняется скаляру, если на ее главной диагонали стоят элементы равные ему, а остальные 0.
Например:

|3|0|0|
|---|---|---|
|0|3|0|
|0|0|3|

2) Следует фиксировать этапы работы коммитами, а не загружать все одним, удобнее всего для этого пользоваться командной строкой или встроенными в ваше IDE инструментами.
3) Реквест закрываю я, с этой домашней работы при остуствии открытого реквеста ставится оценка 0.
4) Также с этой домашней работы слияние своей ветки домашней работы с главным репозиторием, в котором лежит задание, тоже карается оценкой 0.