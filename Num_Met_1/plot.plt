
        set terminal windows
        set xlabel "Ось Х"
        set ylabel "Отклонение от исходной функции"
        set zeroaxis
        set title "График ошибки приближения"
        set key top right
        set style data linespoints
        plot "data_err.txt" using 1:2 with linespoints lw 2 pt 7 ps 1.5 title "Отклонение"
		pause 15
    