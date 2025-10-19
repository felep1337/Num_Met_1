set terminal png size 1200,600 enhanced font 'Arial,12'
set output 'results.png'
set multiplot layout 1,2

set title '����������� ����������� �� ������� ����������'
set xlabel '������� n'
set ylabel '����������� ?_n'
set logscale y
set grid
plot 'error_vs_degree.txt' with linespoints lw 2 pt 7 ps 1 title '�����������'

set title '������ ������ ��� ����������� �������'
set xlabel 'x'
set ylabel 'f(x) - L_n(x)'
unset logscale y
set grid
plot 'error_plot.txt' with lines lw 2 title '������ ������������'

unset multiplot
