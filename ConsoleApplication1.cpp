#include <iostream>
#include <string>
#include<vector>
#include <conio.h>
#include <algorithm>
#include <set>
using namespace std;


const double FI = (1 + sqrt(5)) / 2;
// добавление нулей
string addZeros(string str) {
    int dotPos = str.find('.');
    int numZerosLeft = 32 - dotPos;// количество нулей, которые нужно добавить слева от точки
    int numZerosRight = 65 - str.length() - numZerosLeft;//количество нулей, которые нужно добавить справа от строки
    string zerosLeft(numZerosLeft, '0');
    string zerosRight(numZerosRight, '0');
    str = zerosLeft + str + zerosRight; // Добавляем нули слева и справа от строки
    return str;
}
// добавление нулей
//удаление нулей
string delZeros(string str) {
    while (str[str.length() - 1] == '0' && str[str.length() - 1] != '.') {
        str.erase(str.length() - 1, 1);
    }
    while (str[0] == '0' && str[1] != '.') {
        str.erase(0, 1);
    }
    return str;
}
/// создание вектора со степенями
void convertString(std::string str, vector<int>& result) {// запись степеней фи числа в вектор

    int dotPos = -1;

    // позиция точки
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '.') {
            dotPos = i;
            break;
        }
    }

    // расстановка стееней слева от точки положительные степени
    int count = 0;
    for (int i = dotPos - 1; i >= 0; i--) {
        if (str[i] == '1') {
            result.push_back(count);
        }
        count++;
    }

    // расстановка стееней справа от точки отрицательные степени
    count = -1;
    for (int i = dotPos + 1; i < str.size(); i++) {
        if (str[i] == '1') {
            result.push_back(count);
        }
        count--;
    }

}
///создание строки по вектору степеней
string convertVectorToString(string str, vector<int> vec) {

    int dotPos = -1;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '.') {
            dotPos = i;
            break;
        }
    }
    // Идем от позиции точки +1 вправо
    int cout = -1;
    for (int i = dotPos + 1; i < str.size(); i++) {
        for (int j = 0; j < vec.size(); j++)
        {
            if (vec[j] == cout) {
                str[i] = '1';
                break;
            }
            else {
                str[i] = '0';
            }
        }
        cout--;
    }

    // Идем от позиции точки -1 влево
    cout = 0;
    for (int i = dotPos - 1; i >= 0; i--) {
        for (int j = 0; j < vec.size(); j++)
        {
            if (vec[j] == cout) {
                str[i] = '1';
                break;
            }
            else {
                str[i] = '0';
            }
        }

        cout++;
    }

    return str;
}
///создание строки по вектору степеней для суммы и вычитания
string convertVectorToString_for_summ(string str, vector<int> vec) {//////////////// откуда и куда

    str = addZeros(str);

    int dotPos = -1;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '.') {
            dotPos = i;
            break;
        }
    }
    // Идем от позиции точки +1 вправо
    int cout = -1;
    for (int i = dotPos + 1; i < str.size(); i++) {
        for (int j = 0; j < vec.size(); j++)
        {
            if (vec[j] == cout) {
                str[i] = '1';
                break;
            }
            else {
                str[i] = '0';
            }
        }
        cout--;
    }

    // Идем от позиции точки -1 влево
    cout = 0;
    for (int i = dotPos - 1; i >= 0; i--) {
        for (int j = 0; j < vec.size(); j++)
        {
            if (vec[j] == cout) {
                str[i] = '1';
                break;
            }
            else {
                str[i] = '0';
            }
        }

        cout++;
    }
    str = delZeros(str);
    return str;
}
// реализация свойств фи
void unic(vector<int>& v)
{
    while (true) {
        bool changed = false;
        std::sort(v.begin(), v.end());
        for (size_t i = 1; i < v.size(); ++i) {
            // Если текущий и следующий элементы равны
            if (v[i] == v[i - 1]) {

                ////добавить если оба новых совпадают с уже имеющимися элементами в векторе то сделась "свертку"
                auto it = std::find(v.begin(), v.end(), v[i - 1] - 1);
                auto it2 = std::find(v.begin(), v.end(), v[i - 1] - 2);
                if (it != v.end() && it2 != v.end())
                {
                    // Удаляем следующий элемент
                    v.erase(v.begin() + i - 1);
                    // Удаляем следующий элемент
                    v.erase(v.begin() + i - 2);

                    v.insert(v.end(), v[i - 2] + 1);
                }
                else
                {
                    // Удаляем следующий элемент
                    v.erase(v.begin() + i - 1);
                    // Добавляем два новых элемента
                    v.insert(v.end(), v[i - 1] - 1);
                    v.insert(v.end(), v[i - 1] - 2);
                }


                // Устанавливаем флаг, что вектор изменился
                changed = true;
                break;
            }
        }

        // Если вектор не изменился, то выходим из цикла
        if (!changed) {
            break;
        }
    }

}
/// перевод из фиеричной в десятичную
double toDec(string phiNum) {
    if (phiNum.find('.') == std::string::npos) {
        phiNum += ".";
    }
    int dot_position = phiNum.find('.');
    double number = 0;
    int i = dot_position + 1;
    int deg = -1;
    while (i < phiNum.length()) {
        if (phiNum[i] == '1') {
            number += pow(FI, deg);
        }
        deg--;
        i++;
    }
    i = dot_position - 1;
    deg = 0;
    while (i >= 0) {
        if (phiNum[i] == '1') {
            number += pow(FI, deg);
        }
        deg++;
        i--;
    }
    return number;

}
// проверка строки на ненормализированную форму
bool checkString(const std::string& s) {
    for (size_t i = 0; i < s.size() - 1; ++i) {
        if (s[i] == '1' && s[i + 1] == '1') {
            return true;
        }
    }
    return false;
}
// свертка 011 => 100
string fold(std::string number) {
    std::string result = "";

    size_t dotPos = number.find('.');
    if (dotPos != std::string::npos) {
        number.erase(dotPos, 1);
    }
    bool flag = checkString(number);
    bool flag2;
    bool changed = false;
    while (flag)
    {
        changed = true;
        flag2 = true;/// 
        result = "";
        for (int i = 0; i < number.length(); i++)
        {
            if (number[0] == '1' && number[1] == '1' && flag2)
            {
                result += "100"; i += 2; dotPos++; flag2 = false;
            }
            if (i < number.length() - 2 && number[i] == '0' && number[i + 1] == '1' && number[i + 2] == '1')
            {
                result += "100";
                i += 2;
            }
            else
            {
                result += number[i];
            }
        }
        flag = checkString(result);
        number = result;
    }

    if (dotPos != std::string::npos) {// 111.11  1001.11 1010.01 
        if (!changed) {
            result = number;
        }
        result.insert(dotPos, ".");
    }

    return result;
}
// удаление общих элементов двух векторов (для удаления)
void removeCommonElements(vector<int>& vec1, vector<int>& vec2) {

    sort(vec1.begin(), vec1.end());
    sort(vec2.begin(), vec2.end());

    vector<int> commonElements;
    set_intersection(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), back_inserter(commonElements));

    for (int element : commonElements) {
        vec1.erase(remove(vec1.begin(), vec1.end(), element), vec1.end());
        vec2.erase(remove(vec2.begin(), vec2.end(), element), vec2.end());
    }

}
//  поиск первого элемента, который больше заданного числа во втором векторе
int decompos_num(vector<int>& vec, int num) {
    for (int i : vec) { if (i > num) return i; }
    return 0;
}
// вычитание
vector<int> Del(vector<int>& v1, vector<int>& v2)
{
    int del;
    string tmp = ".";
    removeCommonElements(v1, v2);// удаление одинаковых в обоих
    auto it = adjacent_find(v1.begin(), v1.end());
    for (int i = 0; i < v2.size(); i++)
    {
        del = decompos_num(v1, v2[i]);// 

        v1.push_back(del - 1);
        v1.push_back(del - 2);
        it = std::find(v1.begin(), v1.end(), del);
        if (it != v1.end()) {
            v1.erase(it);
        }


        removeCommonElements(v1, v2);// удаление одинаковых в обоих
        sort(v1.begin(), v1.end());

        it = adjacent_find(v1.begin(), v1.end());

        if (it != v1.end()) {
            unic(v1);
            tmp = convertVectorToString_for_summ(tmp, v1);
            tmp = fold(tmp);
            v1.clear();
            convertString(tmp, v1);
        }
        removeCommonElements(v1, v2);// удаление одинаковых в обоих



    }
    return v1;
};
// развертка 
string unfold(std::string number) {
    size_t dot_position = number.find('.');
    if (dot_position != std::string::npos) {
        number.erase(dot_position, 1);
    }
    std::string res;
    for (int i = number.length() - 1; i >= 0; i--) {
        if (i >= 0 && number[i] == '1' && number[i + 1] == '0' && number[i + 2] == '0' && number[dot_position - 1] != '0') {
            number.erase(i, 3);
            number.insert(i, "011");
        }
    }
    if (dot_position != std::string::npos) {
        number.insert(dot_position, ".");
    }
    return number;
}
//функция добавления 1 в нулевой разряд
string summ(std::string number) {
    int dot_position = number.find('.');

    if (number[dot_position - 1] == '0') {
        number.erase(dot_position - 1, 1);
        number.insert(dot_position - 1, "1");
        number = delZeros(number);
        number = fold(number);
        return number;
    }
    else {
        //1.00
        if (number[dot_position + 1] == '0' && number[dot_position + 2] == '0') {
            number.erase(dot_position + 1, 2);
            number.insert(dot_position + 1, "11");
            number = fold(number);
            return number;
        }
        if (number[dot_position + 1] == '0' && number[dot_position + 2] == '1') {

            number = unfold(number);
            number.erase(dot_position - 1, 1);
            number.insert(dot_position - 1, "1");
            number = fold(number);
            return number;
        }
    }
    return number;
}
// количество дублирующихся степеней
int countDuplicates(const std::vector<int>& vec) {
    std::set<int> s(vec.begin(), vec.end());
    return vec.size() - s.size();
}

/// преобразования степеней

vector<int> replace_identical_elements(std::vector<int>& v) {//
    vector<int> tmp;
    bool double_found = false;
    string TMP = ".";
    int buf;
    int memory_size = 0;
    int tmp_size = 0;
    int tmp_size_old = 0;
    vector<int> memory2;
    vector<int> memory = v;

Loop:if (countDuplicates(memory) > 1) {

    sort(memory.begin(), memory.end());
    sort(v.begin(), v.end());
    for (size_t i = 1; i < v.size(); ++i) //проход по вектору 
    {
        if (countDuplicates(memory) > 1) {
            tmp.clear();
            if (v[i] == v[i - 1] && !double_found)
            { // поиск дубликатов
                double_found = true;
                i++;
            }
            if ((v[i] == v[i - 1]) && double_found)
            { // поиск  как минимум 2х дубликатов
                buf = v[i - 1];
                memory_size = memory.size();
                std::copy(memory.begin(), memory.begin() + (i - tmp_size), std::back_inserter(tmp));
                //           во второй заход меняется
                tmp_size_old = tmp_size;
                tmp_size += tmp.size();

                unic(tmp); // "решение" первых дубликатов

                while (find(tmp.begin(), tmp.end(), buf) != tmp.end()) {// свертка пока не уйдет один из дублирующихся
                    sort(tmp.begin(), tmp.end()); // сортировка ///greater<>()
                    TMP = convertVectorToString_for_summ(TMP, tmp);
                    TMP = fold(TMP); // свертка части 
                    tmp.clear();
                    convertString(TMP, tmp); /// запись степеней
                    auto it = find(tmp.begin(), tmp.end(), buf);
                    if (find(tmp.begin(), tmp.end(), buf) != tmp.end())////свертка не всегда возможна и нужна
                    {
                        if ((buf - tmp[distance(tmp.begin(), it) + 1]) > 1 || (buf - tmp[distance(tmp.begin(), it) + 1]) < -1)
                        {
                            break;
                        }
                    }

                }
                tmp.clear();
                convertString(TMP, tmp); /// запись степеней


                std::copy(tmp.begin(), tmp.end(), back_inserter(memory2));
                std::copy(memory.begin() + (i - tmp_size_old), memory.end(), back_inserter(tmp));//
                //     изменение memory
                memory.erase(memory.begin(), memory.begin() + (i - tmp_size_old));///

                double_found = false;
            }
        }
    }
    // дописать степени
    memory2.insert(memory2.end(), memory.begin(), memory.end());
}
else
{
    tmp = v;
    unic(tmp); // Проходимся по вектору, пока он не станет уникальным
    return tmp;
}
tmp = memory2;
if (countDuplicates(tmp) > 1)
{
    memory = tmp;
    v = tmp;
    tmp_size = 0;
    tmp_size_old = 0;
    memory2.clear();
    goto Loop;
}


unic(tmp); // Проходимся по вектору, пока он не станет уникальным
return tmp;


}

/// основная функция суммы
string Summing(string result1, string result2)
{
    string sum = ".";
    sum = addZeros(sum);
    vector <int> first;
    vector <int> second;

    result1 = delZeros(result1);

    result2 = delZeros(result2);

    convertString(result1, first);///получение степеней фи
    convertString(result2, second);
    first.insert(first.end(), second.begin(), second.end()); // совместить два вектора в first

    //// функция для работы со степенями ////// 
    first = replace_identical_elements(first);

    sum = convertVectorToString(sum, first);
    sum = delZeros(sum);
    cout << "Сумма: " << fold(sum) << endl;


    return sum;

}

//основная функция вычитания
string remove(string result1, string result2)
{
    string quotient = ".";
    quotient = addZeros(quotient);
    vector <int> first;
    vector <int> second;
    vector <int> last;
    convertString(result1, first);///получение степеней фи
    convertString(result2, second);
    while (!second.empty()) {
        last = Del(first, second);
    }
    quotient = convertVectorToString(quotient, last);
    quotient = fold(quotient);
    quotient = delZeros(quotient);
    double dec = toDec(quotient);
    cout << "Результат вычитания: " << quotient << endl;
    cout << "Результат вычитания в 10-й системе счисления: " << dec << endl;

    return quotient;

}

// произведение суммы степеней
void matrix(vector<int>& mlt1, vector<int>& mlt2, vector<int>& resMult) {
    for (int i = 0; i < mlt1.size(); i++) {
        for (int j = 0; j < mlt2.size(); j++) {
            int result = mlt1[i] + mlt2[j];
            resMult.push_back(result);
        }
    }
}
// функция умножения
string mult(string result1, string result2, string& Result)
{

    Result = addZeros(Result);
    bool check = true;
    vector <int> first;
    vector <int> second;
    vector <int> multyply;

    convertString(result1, first);///получение степеней фи
    convertString(result2, second);

    matrix(first, second, multyply);

    while (check) {
        sort(multyply.begin(), multyply.end());
        auto it = adjacent_find(multyply.begin(), multyply.end());
        if (it != multyply.end()) {
            int replace;
            replace = *it;
            auto itLess = find(multyply.begin(), multyply.end(), replace - 1);
            if (itLess != multyply.end()) {
                multyply.push_back(replace + 1);
                multyply.erase(it);
                multyply.erase(itLess);

            }
            else {
                multyply.push_back(replace - 1);
                multyply.push_back(replace - 2);
                auto it2 = find(multyply.begin(), multyply.end(), replace);
                if (it2 != multyply.end()) {
                    multyply.erase(it2);
                }

            }
        }
        else {
            check = false;
        }
    }
    Result = convertVectorToString(Result, multyply);
    Result = fold(Result);
    return delZeros(Result);

}
/// функция сравнения
bool Compose(string A, string B)//
{
    if (A.find('.') == std::string::npos) {
        A += ".";
    }

    vector <int> Degree_A;
    vector <int> Degree_B;
    double  elems_A = 0;
    double elems_B = 0;
    elems_A = toDec(A);
    elems_B = toDec(B);
    if (elems_A >= elems_B) return true;
    else
    {
        return false;
    }

}
/// вычитание для деления
string Removing(string res1, string res2)
{
    res1 += ".";
    string quotient = ".";
    quotient = addZeros(quotient);
    vector <int> first;
    vector <int> second;
    vector <int> last;
    convertString(res1, first);///получение степеней фи
    convertString(res2, second);
    while (!second.empty())
    {
        last = Del(first, second);
    }
    quotient = convertVectorToString(quotient, last);
    quotient = fold(quotient);
    quotient = delZeros(quotient);
    return quotient;
}
//перенос точки для деления
void modifyStrings(string& str1, string& str2) {
    // считаем количество знаков после точки в обоих строках
    int count1 = 0, count2 = 0;
    for (int i = str1.size() - 1; i >= 0; i--) {
        if (str1[i] == '.') break;
        if (str1[i] >= '0') count1++;
    }
    for (int i = str2.size() - 1; i >= 0; i--) {
        if (str2[i] == '.') break;
        if (str2[i] >= '0') count2++;
    }

    // если их разность не равна 0, а i, то в меньшую строку добавляется i нулей в конец
    int diff = count1 - count2;
    if (diff != 0) {
        if (diff > 0) {
            for (int i = 0; i < diff; i++) {
                str2 += '0';
            }
        }
        else {
            for (int i = 0; i < -diff; i++) {
                str1 += '0';
            }
        }
    }

    // точки удаляются в обоих строках, точки добавляются в конец каждой строки
    str1.erase(remove(str1.begin(), str1.end(), '.'), str1.end());
    str2.erase(remove(str2.begin(), str2.end(), '.'), str2.end());
    str1 += '.';
    str2 += '.';
}
// основная функция деления
string Devided(int number1, int number2)//первое делимое второе делитель 
{
    string first = "1.0";
    string second = "1.0";
    int dotPos;
    for (int i = 0; i < number1 - 1; i++) { //певод первого числа в систему счисления ф
        first = addZeros(first);
        first = summ(first);
    }
    first = delZeros(first);

    for (int i = 0; i < number2 - 1; i++) { //певод 2 числа в систему счисления ф
        second = addZeros(second);
        second = summ(second);
    }

    second = delZeros(second);

    modifyStrings(first, second);
    string result = "";
    string tmp = "";// буфер для деления А
    string tmp2 = "";// буфер для деления А
    string tmp3 = ".";// буфер для деления А
    bool flag = false;
    for (int i = 0; i < first.size() - 1; i++)///// (это деление до точки)
    {
        if (tmp.find('.') == std::string::npos) {
            tmp += ".";
        }
        dotPos = tmp.find('.');
        if (dotPos != std::string::npos) {
            tmp.erase(dotPos, 1);
        }
        tmp2 = first[i];
        tmp.insert(dotPos, tmp2);
        if (Compose(tmp, second))// сравнение
        {
            result += "1";
            tmp = Removing(tmp, second);//Вычитание ///
            tmp = delZeros(tmp);
            //dotPos = tmp.find('.');// удалить точку///   /добавить обработку случая резудбтат вычитания 0.1
            //if (dotPos != std::string::npos) {
            //    tmp.erase(dotPos, 1);
            //}
        }
        else
        {
            result += "0";
        }


    }
    if (!tmp.empty())///деление после точки
    {
        result += ".";
        for (int i = 0; i < 32; i++)
        {
            if (tmp.find('.') == std::string::npos && !flag) { tmp.insert(dotPos + 1, tmp3); }
            if (tmp.find('.') == std::string::npos && flag) {
                tmp.insert(dotPos + 1, tmp3);
            }
            flag = true;
            dotPos = tmp.find('.');
            if (dotPos != std::string::npos) {
                tmp.erase(dotPos, 1);
            }
            tmp2 = '0';
            tmp.insert(dotPos, tmp2);
            if (Compose(tmp, second))
            {
                result += "1";
                tmp = Removing(tmp, second);////вычитание , новое тмп
                tmp = delZeros(tmp);
                //size_t dotPos = tmp.find('.');// удалить точку
                //if (dotPos != std::string::npos) {
                //    tmp.erase(dotPos, 1);
                //}
            }
            else
            {
                result += "0";
            }
        }

    }
    result = delZeros(result);
    result = fold(result);// свертка
    return result;
}
/// функция меню
int menu() {
    int choice;
    cout << endl;
    cout << "1. Перевод из 10-ой системы в систему с основанием золотого сечения" << endl;
    cout << "2. Перевод из системы счисления с основанием золотого сечения в 10-ую" << endl;
    cout << "3. Сложение" << endl;
    cout << "4. Вычитание" << endl;
    cout << "5. Умножение" << endl;
    cout << "6. Деление" << endl;
    cout << "0. Выход" << endl;
    cout << endl;
    cin >> choice;
    return choice;
}

int main() {
    setlocale(LC_ALL, "ru");
    bool exit = true;
    string Phi, quotient, result = "1.0", result2, answer;
    string Result = ".";
    bool ex = true;
    int Num, sum1, sum2, num1, num2;
    double dec;
    vector<int> w = { -1, 1 };
    vector<int> s = { -7 };
    while (exit) {
        switch (menu()) {
        case 1:
            result = "1.0";
            cout << "***************** ИЗ ДЕСЯТИЧНОЙ *****************" << endl;
            cout << "Введите целое положительное число " << endl;
            cin >> Num;
            for (int i = 0; i < Num - 1; i++) {
                result = addZeros(result);
                result = summ(result);
            }
            cout << "Ваше число после преобразований: " << delZeros(result) << endl;
            break;
        case 2:
            cout << "***************** В ДЕСЯТИЧНУЮ *****************" << endl;
            cout << "Введите целое положительное число в 'фиеричной' системе счисления" << endl;
            cin >> Phi;
            dec = toDec(Phi);
            cout << "Ваше число после преобразований: " << dec << endl;

            break;
        case 3:
            result = "1.0";
            result2 = "1.0";
            cout << "***************** СЛОЖЕНИЕ *****************" << endl;
            cout << "Введите целое положительное число в 10-й системе счисления" << endl;
            cin >> sum1;
            cout << "Введите ещё одно число для сложения" << endl;
            cin >> sum2;
            for (int i = 0; i < sum1 - 1; i++) {
                result = addZeros(result);
                result = summ(result);
            }
            cout << "------------------------------------" << endl;
            cout << "Ваше 1 число после преобразований: " << delZeros(result) << endl;
            for (int i = 0; i < sum2 - 1; i++) {
                result2 = addZeros(result2);
                result2 = summ(result2);
            }
            cout << "Ваше 2 число после преобразований: " << delZeros(result2) << endl;
            cout << "Сумма чисел в 'фиеричной' системе: ";
            answer = Summing(result, result2);
            dec = toDec(answer);
            cout << "Сумма чисел в 10-ой системе: " << dec << endl;
            cout << "------------------------------------" << endl;
            break;
        case 4:
            result = "1.0";
            result2 = "1.0";
            num1 = 0;
            num2 = 0;
            cout << "***************** ВЫЧИТАНИЕ *****************" << endl;
            cout << "Введите целое положительное число в 10-й системе счисления" << endl;
            cin >> num1;
            cout << "Введите ещё одно число для вычитания (должно быть меньше предыдущего)" << endl;
            cin >> num2;
            if (num1 < num2) {
                cout << "ERROR" << endl;

            }


            for (int i = 0; i < num1 - 1; i++) {
                result = addZeros(result);
                result = summ(result);
            }
            cout << "------------------------------------" << endl;
            cout << "Ваше 1 число после преобразований: " << delZeros(result) << endl;
            for (int i = 0; i < num2 - 1; i++) {
                result2 = addZeros(result2);
                result2 = summ(result2);
            }
            cout << "Ваше 2 число после преобразований: " << delZeros(result2) << endl;
            remove(result, result2);

            cout << "------------------------------------" << endl;
            break;
        case 5:
            result = "1.0";
            result2 = "1.0";
            num1 = num2 = 0;
            cout << "***************** УМНОЖЕНИЕ *****************" << endl;
            cout << "Введите целое положительное число в 10-й системе счисления" << endl;
            cin >> num1;
            cout << "Введите ещё одно число для умножения" << endl;
            cin >> num2;
            for (int i = 0; i < num1 - 1; i++) {
                result = addZeros(result);
                result = summ(result);
            }
            cout << "------------------------------------" << endl;
            cout << "Ваше 1 число после преобразований: " << delZeros(result) << endl;
            for (int i = 0; i < num2 - 1; i++) {
                result2 = addZeros(result2);
                result2 = summ(result2);
            }
            cout << "Ваше 2 число после преобразований: " << delZeros(result2) << endl;
            answer = mult(result, result2, Result);
            cout << "Произведение чисел в 'фиеричной' системе: " << answer << endl;
            dec = toDec(answer);
            cout << "Произведение чисел в 10-ой системе: " << dec << endl;

            cout << "------------------------------------" << endl;
            break;
        case 6:
            cout << "***************** ДЕЛЕНИЕ *****************" << endl;
            cout << "Введите целое положительное число в 10-й системе счисления" << endl;
            cin >> num1;
            cout << "Введите ещё одно число" << endl;
            cin >> num2;
            quotient = Devided(num1, num2);//
            cout << quotient << endl;// вывод в форме фи - системы счисления
            dec = toDec(quotient);
            cout << "В десятичной системе счисления: " << dec << endl;


            break;
        case 0: exit = false;
            break;
        default: cout << "Выберите пункт!" << endl;
            break;
        }
    }

    return 0;
}
