
        set terminal windows
        set xlabel "��� �"
        set ylabel "���������� �� �������� �������"
        set zeroaxis
        set title "������ ������ �����������"
        set key top right
        set style data linespoints
        plot "data_err.txt" using 1:2 with linespoints lw 2 pt 7 ps 1.5 title "����������"
		pause 15
    