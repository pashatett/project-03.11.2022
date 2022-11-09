
#include <iostream>
#include <Windows.h>
#include <stdlib.h>

using namespace std;

// Два поля
char fieldMy[10][10];
char fieldComp[10][10];
int my = 0;
int comp = 0;

//
void FieldFill();//начальная отрисовка поля
void DrawField(char(*field)[10]);//дальнейшая отрисовка поля
//
void ShipRankingOnFieldArm(char(*field)[10]);//ручная расстановка
void ShipRankingOnFieldRand(char(*field)[10]);//расстановка по рандому
//
void Attack(int x, int y, char(*field)[10]);//подбитие или иное
void AttackSmart(int x, int y, char(*field)[10]);
//
void StepPlayer2Rand();//рандомный ход компа
void StepPlayer2Smart();//умный ход компа
//
void StepPlayer1();//выбор куда ходить
void StepPlayer1Rand();//рандомный ход мой
//
bool flag = true;//для проверки победы
void Win(string name);
void WinCheck(char(*field)[10], string name);//проверка победы
//

int a; //рандомные выстрелы компа
int b;//рандомное расставление своих кораблей
int c; //рандомные выстрелы мои
int main(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);


    //будет игра или нет
    char f;
    //рестарт
                                        //реализовать надо!!!!!!!!!!!!!!!!!
    char res;
    cout << "\t\t|||Морской Бой|||\t\t\t\n\n\n";
    cout << "Желаете начать? (y/n)\n";
    cin >> f;

    if (f == 'y') {//играем
        cout << "Рандомные выстрелы компьютера или нет(0/1)"; cin >> a;
        cout << "Рандомное растановление своих кораблей или самостоятельное?(0/1)"; cin >> b;
        cout << "Рандомные выстрелы или сами будете выбирать координаты?(0/1)"; cin >> c;
        system("cls");

        int x, y;
        FieldFill();//начальная отрисовка поля
        if (b == 0) {//рандомное расставление своих кораблей
            cout << "Поле Игрока 1\n";
            ShipRankingOnFieldRand(fieldMy);
            DrawField(fieldMy);
        }
        if (b == 1) {//самостоятельное расставление своих кораблей
            cout << "Поле Игрока 1\n";
            ShipRankingOnFieldArm(fieldMy);
            DrawField(fieldMy);
        }

        cout << "Поле игрока 2\n";
        ShipRankingOnFieldRand(fieldComp);
        DrawField(fieldComp);
        cout << "Хотите ли начать заново или закончить игру?(y)\n";
        if (a == 0) {//рандомные выстрелы компа
            while (flag) {
                if (c == 0) {//рандомные выстрелы мои
                    StepPlayer1Rand();
                    StepPlayer2Rand();
                    WinCheck(fieldComp, "Игрока 1");
                    WinCheck(fieldMy, "Игрока 2");
                }
                if (c == 1) {//сам выбираю куда стрельнуть
                    StepPlayer1();
                    StepPlayer2Rand();
                    WinCheck(fieldComp, "Игрока 1");
                    WinCheck(fieldMy, "Игрока 2");
                }
            }
        }
        if (a == 1) {//не рандомные выстрелы компа
            while (flag) {
                if (c == 0) {//рандомные выстрелы мои
                    StepPlayer1Rand();
                    StepPlayer2Smart();
                    WinCheck(fieldComp, "Игрока 1");
                    WinCheck(fieldMy, "Игрока 2");
                }
                if (c == 1) { //сам выбираю куда стрельнуть
                    StepPlayer1();
                    StepPlayer2Smart();
                    WinCheck(fieldComp, "Игрока 1");
                    WinCheck(fieldMy, "Игрока 2");
                }
            }
        }
    }
    else {//не хочет играть(
        cout << "Good Bye=";
    }
}

void FieldFill() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            fieldMy[i][j] = 'o';
            fieldComp[i][j] = 'o';
        }
    }
}

void DrawField(char(*field)[10]) {
    if (field == fieldMy)cout << "Поле игрока 1" << endl;
    if (field == fieldComp)cout << "Поле игрока 2" << endl;
    cout << "    ";
    for (int i = 0; i < 10; i++) {
        cout << i << " ";
    }
    cout << endl << "   --------------------";
    cout << endl;
    for (int i = 0; i < 10; i++) {
        cout << i << " | ";
        for (int j = 0; j < 10; j++) {
            cout << field[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
}

//2)расстановка кораблей
//2.1)для себя
//2.1.1)вручню(себе)
void ShipRankingOnFieldArm(char(*field)[10]) {
    srand(time(0));
    Sleep(rand() % 1000);

    //начало корабля
    int i, j;
    //конец корабля
    int i2, j2;
    int j1, i1;
    int k=0;

    // Четырёхпалубный
    while (k < 1) {
        system("cls");
        DrawField(fieldMy);
        cout << "Введите начало 4х-палубного корабля\n";
        cin >> j; cin >> i;
        field[i][j] = '+';
        system("cls");
        DrawField(fieldMy);
        cout << "Введите конец 4х-палубного корабля\n";
        cin >> j2; cin >> i2;
        system("cls");
        if (((j2 - j == 3 || j - j2 == 3) && i == i2) || ((i2 - i == 3 || i - i2 == 3) && j == j2)) {
            field[i2][j2] = '+';
            system("cls");
        }
        system("cls");
        DrawField(fieldMy);
        if (i == i2) {
            if (j < j2) {
                field[i][j + 1] = '+';
                field[i][j + 2] = '+';
                system("cls");
                DrawField(fieldMy);
            }
            else {
                field[i][j - 1] = '+';
                field[i][j - 2] = '+';
                system("cls");
                DrawField(fieldMy);
            }

        }
        if (j == j2) {
            if (i < i2) {
                field[i + 1][j] = '+';
                field[i + 2][j] = '+';
                system("cls");
                DrawField(fieldMy);
            }
            else {
                field[i - 1][j] = '+';
                field[i - 2][j] = '+';
                system("cls");
                DrawField(fieldMy);
            }
        }
        k++;
    }


    // Трёхпалубные
    k = 0;
    while (k < 2) {
        cout << "Введите начало 3х-палубного корабля\n";
        cin >> i; cin >> j;
        field[i][j] = '+';
        system("cls");
        DrawField(fieldMy);
        cout << "Введите конец 3х-палубного корабля\n";
        cin >> i2; cin >> j2;
        field[i2][j2] = '+';
        k++;

        DrawField(fieldMy);

        if (i == i2) {
            if (j < j2) {
                field[i][j + 1] = '+';
                system("cls");
                DrawField(fieldMy);
            }
            else {
                field[i][j - 1] = '+';
                system("cls");
                DrawField(fieldMy);
            }

        }
        if (j == j2) {
            if (i < i2) {
                field[i + 1][j] = '+';
                system("cls");
                DrawField(fieldMy);
            }
            else {
                field[i - 1][j] = '+';
                system("cls");
                DrawField(fieldMy);
            }
        }

    }


    // Двупалобные
    k = 0;
    while (k < 3) {
        cout << "Введите начало 2х-палубного корабля\n";
        cin >> i; cin >> j;
        field[i][j] = '+';
        DrawField(fieldMy);
        cout << "Введите конец 2х-палубного корабля\n";
        cin >> i2; cin >> j2;
        field[i2][j2] = '+';
        k++;
        system("cls");
        DrawField(fieldMy);
        //}
    }


    // Однопалубные
    k = 0;
    while (k < 4) {
        cout << "Введите координаты 1-палубного корабля\n";
        cin >> i; cin >> j;
        field[i][j] = '+';
        k++;
        system("cls");
        DrawField(fieldMy);
    }
}


//2.1.2)рандом(себе)
void ShipRankingOnFieldRand(char(*field)[10]) {
    srand(time(0));
    Sleep(rand() % 1000);
    int i, j;
    int j1, i1;
    int k;
    int s;
    // Четырёхпалубный
    {
        s = rand() % 2;
        Sleep(rand() % 1000);

        // Горизонтально
        if (s) {
            i = rand() % 10;
            j = rand() % 7;
            field[i][j] = '+';
            field[i][j + 1] = '+';
            field[i][j + 2] = '+';
            field[i][j + 3] = '+';
        }
        // Вертикально
        else {
            i = rand() % 7;
            j = rand() % 10;
            field[i][j] = '+';
            field[i + 1][j] = '+';
            field[i + 2][j] = '+';
            field[i + 3][j] = '+';
        }
    }


    // Трёхпалубные
    k = 0;
    while (k < 2) {
        s = rand() % 2;
        // Горизонтально
        if (s) {
            i = rand() % 10;
            j = rand() % 8;
            j1 = j + 2;
            i1 = i;
            if (field[i - 1][j - 1] == 'o' && field[i + 1][j + 1] == 'o'
                && field[i][j - 1] == 'o' && field[i][j + 1] == 'o'
                && field[i + 1][j - 1] == 'o' && field[i - 1][j + 1] == 'o'
                && field[i + 1][j] == 'o' && field[i - 1][j] == 'o'
                && field[i1 - 1][j1] == 'o' && field[i1 + 1][j1 + 1] == 'o'
                && field[i1][j1 + 1] == 'o' && field[i1 + 1][j1] == 'o'
                && field[i1 - 1][j1] == 'o' && field[i + 1][j1 - 1] == 'o' && field[i - 1][j1 + 1] == '0') {

                field[i][j] = '+';
                field[i1][j1] = '+';
                field[i1][j + 1] = '+';
                k++;
            }
            else continue;
        }
        // Вертикально
        else {
            i = rand() % 8;
            j = rand() % 10;
            i1 = i + 2;
            j1 = j;
            if (field[i - 1][j - 1] == 'o' && field[i + 1][j + 1] == 'o'
                && field[i][j - 1] == 'o'
                && field[i + 1][j - 1] == 'o' && field[i - 1][j + 1] == 'o'
                && field[i + 1][j] == 'o' && field[i - 1][j] == 'o'
                && field[i1][j1 - 1] == 'o' && field[i1 + 1][j1 + 1] == 'o'
                && field[i1 + 1][j1] == 'o' && field[i1][j1 + 1] == 'o'
                && field[i1][j1 - 1] == 'o') {

                field[i][j] = '+';
                field[i1][j1] = '+';
                field[i + 1][j] = '+';
                k++;
            }
            else continue;
        }
    }


    // Двупалобные
    k = 0;
    while (k < 3) {
        s = rand() % 2;
        // Горизонтально
        if (s) {
            i = rand() % 10;
            j = rand() % 9;
            j1 = j + 1;
            i1 = i;
            if (field[i - 1][j - 1] == 'o' && field[i + 1][j + 1] == 'o'
                && field[i][j - 1] == 'o'
                && field[i + 1][j - 1] == 'o' && field[i - 1][j + 1] == 'o'
                && field[i + 1][j] == 'o' && field[i - 1][j] == 'o'
                && field[i1 - 1][j1] == 'o' && field[i1 + 1][j1 + 1] == 'o'
                && field[i1][j1 + 1] == 'o' && field[i1 + 1][j1] == 'o'
                && field[i1 - 1][j1] == 'o'
                && field[i1 + 1][j1 - 1] == 'o' && field[i1 - 1][j1 + 1] == 'o'
                && field[i][j] != '+') {
                field[i][j] = '+';
                field[i1][j1] = '+';
                k++;
            }
            else continue;
        }
        // Вертикально
        else {
            i = rand() % 9;
            j = rand() % 10;
            j1 = j;
            i1 = i + 1;
            if (field[i - 1][j - 1] == 'o' && field[i + 1][j + 1] == 'o' && field[i][j - 1] == 'o'
                && field[i + 1][j - 1] == 'o' && field[i - 1][j + 1] == 'o'
                && field[i + 1][j] == 'o' && field[i - 1][j] == 'o'
                && field[i1 - 1][j1] == 'o' && field[i1 + 1][j1 + 1] == 'o'
                && field[i1][j1 + 1] == 'o' && field[i1 + 1][j1] == 'o' && field[i1][j1 - 1] == 'o'
                && field[i1 + 1][j1 - 1] == 'o' && field[i1 - 1][j1 + 1] == 'o' && field[i][j] != '+') {
                field[i][j] = '+';
                field[i1][j1] = '+';
                k++;
            }
            else continue;
        }
    }


    // Однопалубные
    k = 0;
    while (k < 4) {
        i = rand() % 10;
        j = rand() % 10;

        if (field[i - 1][j - 1] == 'o' && field[i + 1][j + 1] == 'o'
            && field[i][j + 1] == 'o' && field[i][j - 1] == 'o'
            && field[i + 1][j] == 'o' && field[i - 1][j] == 'o'
            && field[i + 1][j - 1] == 'o' && field[i - 1][j + 1] == 'o'
            && field[i][j] != '+') {
            field[i][j] = '+';
            k++;
        }
        else continue;
    }
}


//3)стрельба
//обычная атака компа
void Attack(int x, int y, char(*field)[10]) {
    if (field[y][x] == 'o') {
        if (field == fieldMy) {
            system("cls");
            cout << endl << "\tПусто\n";
            field[y][x] = '*';
            DrawField(fieldMy);
            DrawField(fieldComp);
            StepPlayer1Rand();
        }
        else if (field == fieldComp) {
            system("cls");
            cout << endl << "\tПусто\n";
            field[y][x] = '*';
            DrawField(fieldMy);
            DrawField(fieldComp);
            StepPlayer2Rand();
        }
    }
    else if (field[y][x] == '*' || field[x][y] == '-') {
        if (field == fieldMy) {
            system("cls");
            cout << "\tПромах!\n";
            DrawField(fieldMy);
            DrawField(fieldComp);
            StepPlayer1Rand();
        }
        else if (field == fieldComp) {
            system("cls");
            cout << "\tПромах!\n";
            DrawField(fieldMy);
            DrawField(fieldComp);
            StepPlayer2Rand();
        }
    }
    else if (field[y][x] == '+') {
        system("cls");
        cout << endl << "\tКорабль подбит\n";
        field[y][x] = '-';
        if (field == fieldMy) {
            my++;
            system("cls");
            cout << "\tКорабль подбит\n";
            cout << "Поле игрока 1\n";
            DrawField(fieldMy);
            cout << "Поле игрока 2\n";
            DrawField(fieldComp);
            StepPlayer2Rand();
        }
        else if (field == fieldComp) {
            comp++;
            system("cls");
            cout << "\tКорабль подбит\n";
            cout << "Поле игрока 1\n";
            DrawField(fieldMy);
            cout << "Поле игрока 2\n";
            DrawField(fieldComp);
            StepPlayer1Rand();
        }
    }
}

//умная атака компа
void AttackSmart(int x, int y, char(*field)[10]) {
    if (field[y][x] == 'o') {
        if (field == fieldMy) {
            system("cls");
            cout << endl << "\tПусто\n";
            field[y][x] = '*';
            DrawField(fieldMy);
            DrawField(fieldComp);
            StepPlayer1();
        }
        else if (field == fieldComp) {
            system("cls");
            cout << endl << "\tПусто\n";
            field[y][x] = '*';
            DrawField(fieldMy);
            DrawField(fieldComp);
            StepPlayer2Rand();
        }
    }
    else if (field[y][x] == '*' || field[x][y] == '-') {
        if (field == fieldMy) {
            system("cls");
            cout << "\tПромах!\n";
            DrawField(fieldMy);
            DrawField(fieldComp);
            StepPlayer2Rand();
        }
        else if (field == fieldComp) {
            system("cls");
            cout << "\tПромах!\n";
            DrawField(fieldMy);
            DrawField(fieldComp);
            StepPlayer1();
        }
    }
    else if (field[y][x] == '+') {
        int x1, y1;
        if (field == fieldMy) {
            my++;
            x1 = x;
            y1 = y;
            system("cls");
            cout << endl << "\tКорабль подбит\n";
            field[y][x] = '-';
            DrawField(fieldMy);
            DrawField(fieldComp);
            StepPlayer2Rand();
        }
        else if (field == fieldComp) {
            comp++;
            system("cls");
            cout << endl << "\tКорабль подбит\n";
            field[y][x] = '-';
            DrawField(fieldMy);
            DrawField(fieldComp);
            StepPlayer1();
        }
    }
}

//3.1)рандомные выстрелы компа
void StepPlayer2Rand() {
    int x = rand() % 10;
    int y = rand() % 10;
    cout << "-----------------Ход Игрока 2-------------------\n";
    Attack(x, y, fieldMy);
    cout << "Поле Игрока 1\n";
    DrawField(fieldMy);
    cout << "Поле Игрока 2\n";
    DrawField(fieldComp);
}


//чет не понял как реализовать можно
//3.2)тип умный комп
void StepPlayer2Smart() {
    int x = rand() % 10;
    int y = rand() % 10;
    cout << "-----------------Ход Игрока 2-------------------\n";
    AttackSmart(x, y, fieldMy);
    cout << "Поле Игрока 1\n";
    DrawField(fieldMy);
    cout << "Поле Игрока 2\n";
    DrawField(fieldComp);
}


//4)моя стрельба (сам стреляю)
void StepPlayer1() {
    int x, y;
    cout << "-----------------Ход Игрока 1-------------------\n";
    cout << "Задайте координату x(если хотите выйти напишите y) - "; cin >> x;
    if (x == 'y') {}
    else {
        cout << "Задайте координату y - "; cin >> y;
        system("cls");
        AttackSmart(x, y, fieldComp);
        cout << "Поле Игрока 1\n";
        DrawField(fieldMy);
        cout << "Поле игрока 2\n";
        DrawField(fieldComp);
    }
}
//если лень то можно по рандому стрелять
void StepPlayer1Rand() {
    srand(time(0));
    int x = rand() % 10;
    int y = rand() % 10;
    cout << "-----------------Ход Игрока 1-------------------\n";
    Attack(x, y, fieldComp);
    cout << "Поле Игрока 2\n";
    DrawField(fieldComp);
    cout << "Поле Игрока 1\n";
    DrawField(fieldMy);
}

//6)остановка, приостановка, перезапуск игры(если ты лох)
//надо реализовать

//проверка победы
void WinCheck(char(*field)[10], string name) {
    int c = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (field[j][i] == '+') c++;
        }
    }
    if (c == 10)
        Win(name);
    if (comp == 10)Win("Игрок 1");
    else if (my == 10)Win("Игрок 2");
}
//победа
void Win(string name) {
    cout << "Победа " << name << "!!" << endl;
    ::flag = false;
}
