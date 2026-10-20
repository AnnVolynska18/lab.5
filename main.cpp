#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

const int N = 10;       // кількість студентів
const int GRADES = 5;   // кількість оцінок

// Структура Student
struct Student {
    string fullName;        // ПІБ
    string group;           // Номер групи
    int grades[GRADES];     // Успішність (5 оцінок)
};

// Середній бал студента
double average(const Student& s) {
    int sum = 0;
    for (int i = 0; i < GRADES; i++) {
        sum += s.grades[i];
    }
    return (double)sum / GRADES;
}

// Умова отримання стипендії: немає жодної оцінки нижче 4
bool hasScholarship(const Student& s) {
    for (int i = 0; i < GRADES; i++) {
        if (s.grades[i] < 4) {
            return false;
        }
    }
    return true;
}

int main() {
#ifdef _WIN32
    system("chcp 65001 > nul");   // щоб у консолі відображалась українська
#endif

    Student students[N];

    // 1. Введення даних з клавіатури
    cout << "Введіть дані про " << N << " студентів." << endl;
    for (int i = 0; i < N; i++) {
        cout << "\nСтудент " << i + 1 << endl;

        cout << "ПІБ: ";
        getline(cin, students[i].fullName);

        cout << "Номер групи: ";
        getline(cin, students[i].group);

        cout << "Введіть " << GRADES << " оцінок через пробіл: ";
        for (int j = 0; j < GRADES; j++) {
            cin >> students[i].grades[j];
        }
        cin.ignore(10000, '\n');   // прибираємо Enter з буфера перед наступним getline
    }

    // 2. Впорядкування за зростанням середнього балу (метод бульбашки)
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1 - i; j++) {
            if (average(students[j]) > average(students[j + 1])) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    cout << "\n=== Студенти за зростанням середнього балу ===" << endl;
    for (int i = 0; i < N; i++) {
        cout << students[i].fullName << ", " << students[i].group
             << ", середній бал: " << average(students[i]) << endl;
    }

    // 3. Студенти, які одержують стипендію
    cout << "\n=== Студенти, які одержують стипендію ===" << endl;
    bool found = false;
    for (int i = 0; i < N; i++) {
        if (hasScholarship(students[i])) {
            cout << students[i].fullName << ", група " << students[i].group << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Студентів, які одержують стипендію, немає." << endl;
    }

    return 0;
}