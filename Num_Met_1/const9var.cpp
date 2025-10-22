#include "const9var.h"

const double a = 0;
const double b = 3 * M_PI;
const double delta = 2 * pow(10, -3);
const double nodes = 100000;
const double nodesForError = 100;

const char* gnuplotScript = R"gnuplot(
        set terminal windows
        set xlabel "���������� �����"
        set ylabel "�����������"
        set title "��������� �����������"
        set key top right
        set style data linespoints
        plot "data.txt" using 1:2 with linespoints lw 2 pt 7 ps 1.5 title "�����������"
		pause 15
    )gnuplot";

const char* gnuplotErrorScript = R"gnuplot(
        set terminal windows
        set xlabel "��� �"
        set ylabel "���������� �� �������� �������"
        set zeroaxis
        set title "������ ������ �����������"
        set key top right
        set style data linespoints
        plot "data_err.txt" using 1:2 with linespoints lw 2 pt 7 ps 1.5 title "����������"
		pause 15
    )gnuplot";