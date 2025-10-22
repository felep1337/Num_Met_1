#include "const9var.h"

const double a = 0;
const double b = 3 * M_PI;
const double delta = 2 * pow(10, -3);
const double nodes = 100000;
const double nodesForError = 100;

const char* gnuplotScript = R"gnuplot(
        set terminal windows
        set xlabel "Количество узлов"
        set ylabel "Погрешность"
        set title "Сравнение погрешности"
        set key top right
        set style data linespoints
        plot "data.txt" using 1:2 with linespoints lw 2 pt 7 ps 1.5 title "Погрешность"
		pause 15
    )gnuplot";

const char* gnuplotErrorScript = R"gnuplot(
        set terminal windows
        set xlabel "Ось Х"
        set ylabel "Отклонение от исходной функции"
        set zeroaxis
        set title "График ошибки приближения"
        set key top right
        set style data linespoints
        plot "data_err.txt" using 1:2 with linespoints lw 2 pt 7 ps 1.5 title "Отклонение"
		pause 15
    )gnuplot";