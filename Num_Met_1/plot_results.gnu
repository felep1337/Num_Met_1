set terminal png size 1200,600 enhanced font 'Arial,12'
set output 'results.png'
set multiplot layout 1,2

set title 'Зависимость погрешности от степени многочлена'
set xlabel 'Степень n'
set ylabel 'Погрешность ?_n'
set logscale y
set grid
plot 'error_vs_degree.txt' with linespoints lw 2 pt 7 ps 1 title 'Погрешность'

set title 'График ошибки для оптимальной степени'
set xlabel 'x'
set ylabel 'f(x) - L_n(x)'
unset logscale y
set grid
plot 'error_plot.txt' with lines lw 2 title 'Ошибка интерполяции'

unset multiplot
