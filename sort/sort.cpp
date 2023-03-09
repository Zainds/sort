#include <iostream>
#include <chrono>
#include <fstream>
using namespace std;

void print_Arr(int* arr, int size){
    for (int i = 0; i < size; i++)
        cout << arr[i]<<endl;
}

void quickSort(int* arr, int low, int high){
    int i = low;
    int j = high;
    int pivot = arr[(i + j) / 2];

    while (i <= j)
    {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j){
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    if (j > low)
        quickSort(arr, low, j);
    if (i < high)
        quickSort(arr, i, high);
}

void select_sort(int* arr, int size) {
    
    for (int i = 0; i < size - 1; i++){
        int min_index = i;
        for (int j = i + 1; j < size; j++){
            if (arr[j] < arr[min_index]){
                min_index = j;
            }
        }
        if (min_index != i){
            swap(arr[i], arr[min_index]);
        } 
    }
}
int GetRandomNumber(int min, int max){
    int num = min + rand() % (max - min + 1);
    return num;
}

int main()
{
    setlocale(LC_ALL, "");
    cout << "Введите размерность массива\n";
    int n, arrChoice, arrUnique;
    int k = 0;
    cin >> n;
    int* arr = new int[n];

    ofstream fout;
    fout.open("output.dat");

    cout << "Включить проверку на уникальность элементов массива?:  1 - Да,  2 - Нет\n";
    cin >> arrUnique;

    if (arrUnique == 1 && n > 120) {
        cout << "Введенный размер массива больше, чем максимально возможное кол-во уникальных элементов(120) \n";
    }
    for (int i = 0; i < n; i++) {
        int x = GetRandomNumber(1, 120);

        if (arrUnique == 1) {
            
            int flag = 1;
            for (int j = 0; j < n; j++) {
                if (arr[j] == x && j != i) flag = 0;
            }
        
            if (flag == 1) {
                arr[i] = x;
                 k++;
            }
            else {
                i -= 1;
            }
        }
        else {
            arr[i] = x;
        }
    }

    cout << "Выберите метод сортировки:  1 - Сортировка выбором,  2 - QuickSort" << endl;
    cin >> arrChoice;
    auto start_time = chrono::steady_clock::now();
    if (arrChoice == 1){
        select_sort(arr, n);
    }
    else
    {
        quickSort(arr, 0, n);
    }

    auto end_time = chrono::steady_clock::now();
    auto elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
    cout << elapsed_ns.count() << " ns\n \n";
    
    for (int i = 0; i < n; i++) {
        fout << arr[i] << endl;
    }
    fout.close();
    //print_Arr(arr, n);
}


