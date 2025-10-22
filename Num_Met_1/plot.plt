
        set terminal windows
        set xlabel "Количество узлов"
        set ylabel "Погрешность"
        set title "Сравнение погрешности"
        set key top right
        set style data linespoints
        plot "data.txt" using 1:2 with linespoints lw 2 pt 7 ps 1.5 title "Погрешность"
		pause 15
    