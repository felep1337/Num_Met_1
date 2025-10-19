#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <vector>

//константы для функций Фуга 9 вар
const int a = 0;
const double b = 3 * M_PI;
const double delta = 2 * pow(10, -3);

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

int main()
{
    setlocale(LC_ALL,"RU_ru");
    int n;
    std::cin >> n;

    for (int k = 1; k <= n; k++) {
        double supremum = 0;
        double* array = new double[k + 1];
        double* numbers = new double[k + 1];

        for (int i = 0; i <= k; i++) {
            array[i] = func(b * i / k);
            numbers[i] = (b * i / k);
        }

        double nodes = 100000;
        double crnt = 0;
        for (int i = 0; i <= nodes; i++) {
            double current = ((i * b) / nodes);
            double current_val = (func(current) - interp(current, k, numbers, array));
            if (current_val > supremum) {
                supremum = current_val;
                crnt = current;
            }
        }
        std::cout << "Максимальная погрешность: " << supremum << ", в точке " << crnt << "\n";
        delete[] array;
        delete[] numbers;
    }
}
    //проверка для рандомного n
    /*for (int i = 0; i <= n; i++) {
        double answer = Lang(numbers[i], n, numbers, array);
        std::cout << i << "\t" << numbers[i] << "\t" << array[i] << "\t" << answer << "\n";
    }*/
