#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <fstream>
#include "const9var.h"

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

double Func(float x) {
    return sin(x) * log(x + 1);
}

double Diff(double* arr, double* arr_val,int i, int j) {
    if (i == j) {
        return arr_val[i];
    }
    else {
        return((Diff(arr, arr_val, i + 1, j) - Diff(arr, arr_val, i, j - 1)) / (arr[j] - arr[i]));
    }
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

double NewtonPolynomial(double current, int n, double* arr, double* arr_val) {
    double ans = arr_val[0];
    for (int i = 1; i < n; i++) {
        double temp = Diff(arr, arr_val, 0, i);
        for (int j = 0; j < i; j++) {
            temp *= (current - arr[j]);
        }
        ans += temp;
    }
    return ans;
}

double* Chebyshev(double n) {
    double* arr = new double[n];
    for (int i = 0; i < n; i++) {
        arr[i] = ((b + a)/2) + (((b - a)/2) * cos(M_PI * (((2 * i) + 1) / (2 * n))));
    }
    return arr;
}

double LangrangeSupremum(int n, double* numbers, double* array) {
    double supremum = 0;
    for (int i = 0; i <= nodes; i++) {
        double current_x = ((i * b) / nodes);
        double current_val = abs((Func(current_x) - LangrangePolynomial(current_x, n, numbers, array)));
        if (current_val > supremum) {
            supremum = current_val;
        }
    }
    return supremum;
}

double NewtonSupremum(int n, double* numbers, double* array) {
    double supremum = 0;
    for (int i = 0; i <= nodes; i++) {
        double current_x = ((i * b) / nodes);
        double current_val = abs((Func(current_x) - NewtonPolynomial(current_x, n, numbers, array)));
        if (current_val > supremum) {
            supremum = current_val;
        }
    }
    return supremum;
}

double W_n(int n, double* arr_of_nums, double* arr_for_compute) {
    double max = 0;
    for (int i = 0; i < n; i++) {
        double compute_val = 1.0;
        for (int j = 0; j < n; j++) {
            compute_val *= (arr_of_nums[i] - arr_for_compute[j]);
        }
        if (max < compute_val) {
            max = compute_val;
        }
    }
    return max;
}

void MakeDataErrorFile(int k, double* numbers, double* array) {
    std::ofstream file_err("data_err.txt");
    for (int i = 0; i <= nodesForError; i++) {
        double current = ((i * b) / nodesForError);
        file_err << current << " " << abs(Func(current) - LangrangePolynomial(current, k, numbers, array)) << "\n";
    }
    file_err.close();
}

void MakeDataEvenly(int n, double* numbers, double* array) {
    for (int i = 0; i <= n; i++) {
        array[i] = Func(b * i / n);
        numbers[i] = (b * i / n);
    }
}
void MakeDataUnevenly(int n, double* arr, double* arr_val) {
    for (int i = 0; i < n; i++) {
        arr_val[i] = Func(arr[i]);
    }
}

double CheckSupForInt(int n) {
    double* arr = new double[n + 1];
    double* arr_val = new double[n + 1];
    MakeDataEvenly(n, arr, arr_val);
    double supremum = LangrangeSupremum(n, arr, arr_val);
    delete[] arr;
    delete[] arr_val;
    return supremum;
}

int ProcessData1(int n) {

    std::ofstream file("data.txt");
    int best = 1;
    double temp = 1000;

    for (int k = 1; k <= n; k++) {

        double* arr = new double[k + 1];
        double* arr_val = new double[k + 1];

        MakeDataEvenly(k, arr, arr_val);
        double supremum = LangrangeSupremum(k, arr, arr_val);

        if (temp > supremum){
            best = k;
            temp = supremum;
        }

        file << k << " " << supremum << "\n";

        if (k == n) {
            MakeDataErrorFile(k, arr, arr_val);
        }

        delete[] arr;
        delete[] arr_val;
    }

    file.close();

    return best;
}

double* ProcessData2(int best) {
    double* arr = Chebyshev(best);
    double* arr_val = new double[best];
    MakeDataUnevenly(best, arr, arr_val);
    double supremum = LangrangeSupremum(best, arr, arr_val);
    double wn_val = W_n(best, arr, arr_val);
    double diff = Diff(arr, arr_val, 0, best);
    std::cout << wn_val << "\t" << diff << "\n";
    delete[] arr;
    delete[] arr_val;
    double* a{ new double[2] {supremum, diff*wn_val} };
    return a;
}

int InitN() {
    int n;
    std::cout << "Введите кол-во узлов: ";
    std::cin >> n;
    return n;
}

void end() {
    int choose = -1;
    while (choose != 0) {
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

int main()
{
    setlocale(LC_ALL, "RU");

    int n = InitN();

    int best = ProcessData1(n);

    double* arr = new double[n + 1];
    double* arr_val = new double[n + 1];
    MakeDataEvenly(n, arr, arr_val);
    std::cout << NewtonSupremum(n, arr, arr_val);

    /* double* sup_cheb = ProcessData2(best);
    double sup_best = CheckSupForInt(best);
    std::cout << sup_cheb[0] << "\t" << sup_cheb[1] << "\n";
    std::cout << "Разность между погрешность на неравномерной сетке и равномерной сетке: " << sup_best - sup_cheb[0] << "\n";
    std::cout << sup_cheb << "\n";*/
    end();
}
