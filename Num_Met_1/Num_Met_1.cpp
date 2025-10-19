#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

//константы для функций Фуга 9 вар
const int a = 0;
const double b = 3 * M_PI;
const double delta = 2 * pow(10, -3);
const int nodes = 100000;
const int nodesForError = 100;

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

void callGnuplot() {
    std::ofstream gnuplotFile("plot.plt");
    gnuplotFile << gnuplotScript;
    gnuplotFile.close();
    system("\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\" plot.plt");
}

void callGnuplotForError() {
    std::ofstream gnuplotFile("plot.plt");
    gnuplotFile << gnuplotErrorScript;
    gnuplotFile.close();
    system("\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\" plot.plt");
}


double func(float x) {
    return sin(x) * log(x+1);
}

double interp(float x, int n, double* numbers, double* arr) {
    double answer = 0;
    for (int i = 0; i <= n; i++) {
        double result = 1.0;
        for (int j = 0; j <= n; j++) {
            if (i == j){
                continue;
            }
            result *= (x - numbers[j]) / (numbers[i] - numbers[j]);
        }
        result *= arr[i];
        answer += result;
    }
    return answer;
}

double Supremum(int k, double* numbers, double* array) {
    double supremum = 0;
    for (int i = 0; i <= nodes; i++) {
        double current = ((i * b) / nodes);
        double current_val = (func(current) - interp(current, k, numbers, array));
        if (current_val > supremum) {
            supremum = current_val;
        }
    }
    return supremum;
}

void makeDataForError(std::ofstream *file, int k, double* numbers, double* array) {
    for (int i = 0; i <= nodesForError; i++) {
        double current = ((i * b) / nodesForError);
        *file << current << " " << func(current) - interp(current, k, numbers, array) << "\n";
    }
}

void makeData(int k, double* numbers, double* array) {
    for (int i = 0; i <= k; i++) {
        array[i] = func(b * i / k);
        numbers[i] = (b * i / k);
    }
}

int main()
{
    setlocale(LC_ALL, "RU");
    int n = 0;
    std::cout << "Введите кол-во узлов: ";
    std::cin >> n;

    std::ofstream file("data.txt");

    for (int k = 1; k <= n; k++) {
        double* array = new double[k + 1];
        double* numbers = new double[k + 1];

        makeData(k,numbers,array);
        double supremum = Supremum(k, numbers, array);
        file << k << " " << supremum << "\n";
        if (k == n) {
            std::ofstream file_err("data_err.txt");
            makeDataForError(&file_err,k, numbers, array);
            file_err.close();
        }

        delete[] array;
        delete[] numbers;
    }
    file.close();

    int choose = -1;
    while (choose != 0){
        std::cout << "Выберите график (1 - оценка погрешности, 2 - график ошибки приблиежния, 0 - завершить программу): ";
        std::cin >> choose;
        if (choose == 1) {
            callGnuplot();
        }
        else if (choose == 2) {
            callGnuplotForError();
        }
    }
}
