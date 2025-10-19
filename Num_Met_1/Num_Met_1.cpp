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

double LangrangePolynomial(float x, int n, double* numbers, double* arr) {
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

double* Chebyshev(int n) {
    double* arr = new double[n];
    for (int i = 0; i < n; i++) {
        arr[i] = (b + a) / 2 + (b - a) / 2 * cos(M_PI * (2 * i + 1) / 2 * n);

    }
    return arr;
}

double Supremum(int k, double* numbers, double* array) {
    double supremum = 0;
    for (int i = 0; i <= nodes; i++) {
        double current = ((i * b) / nodes);
        double current_val = (func(current) - LangrangePolynomial(current, k, numbers, array));
        if (current_val > supremum) {
            supremum = current_val;
        }
    }
    return supremum;
}

void makeDataErrorFile(int k, double* numbers, double* array) {
    std::ofstream file_err("data_err.txt");
    for (int i = 0; i <= nodesForError; i++) {
        double current = ((i * b) / nodesForError);
        file_err << current << " " << func(current) - LangrangePolynomial(current, k, numbers, array) << "\n";
    }
    file_err.close();
}

void makeDataEvenly(int n, double* numbers, double* array) {
    for (int i = 0; i <= n; i++) {
        array[i] = func(b * i / n);
        numbers[i] = (b * i / n);
    }
}
void makeDataUnevenly(int n, double* numbers, double* array) {
    for (int i = 0; i < n; i++) {
        array[i] = func(numbers[i]);
    }
}

int processData1(int n) {
    std::ofstream file("data.txt");
    int best = 1;
    double temp = 1000;
    for (int k = 1; k <= n; k++) {
        double* array = new double[k + 1];
        double* numbers = new double[k + 1];

        makeDataEvenly(k, numbers, array);
        double supremum = Supremum(k, numbers, array);
        if (temp > supremum){
            best = k;
            temp = supremum;
        }
        file << k << " " << supremum << "\n";
        if (k == n) {
            makeDataErrorFile(k, numbers, array);
        }

        delete[] array;
        delete[] numbers;
    }
    file.close();
    return best;
}

void processData2(int best) {
    double* arr = Chebyshev(best);
    double* arr_val = new double[best];
    makeDataUnevenly(best, arr, arr_val);

}

int main()
{
    setlocale(LC_ALL, "RU");
    int n = 0;
    std::cout << "Введите кол-во узлов: ";
    std::cin >> n;

    int best = processData1(n);
    processData2(best);

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
