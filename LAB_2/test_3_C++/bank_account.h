//
//  Header.h
//  test_3_C++
//
//  Created by Мария Юрьевна on 24.04.2018.
//  Copyright © 2018 Мария Юрьевна. All rights reserved.
//
/* 
#ifndef Header_h
#define Header_h


#endif Header_h */

//using namespace std;
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <fstream>
#include <istream>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include "help_file_name.h"
#include "help_menu.h"
using namespace std;
//подтип данные
class Data {
        friend class bank_account;
private:

    // проверка является ли год високосным
    bool is_leap(int year) 
    {
        if ( (year % 4) || ( ( year % 100 ) == 0 && ( year % 400 ) ) )
            return false;
        return true;
    }

    // проверка даты на корректность
    bool correct_date(int day, int month, int year,string &message)
    {

        // если год вискосный                            //если не високосный
        if ((month == 2 && day > 29 && is_leap(year)) || (month == 2 && day > 28 && !is_leap(year)))
        {
            message = "Неверное кол-во дней в феврале!";
            return false;
        }
        //кол-во дней в месяце
        if (month == 4 || month == 6 || month == 9 || month == 11)
        {
            if (day > 30)
            {
                message = "Неверное кол-во дней в месяце!";
                return false;
            }
        }
        return true;
    }

    // день
    int day;
    // месяц
    int month;
    // год
    int year;
public:
    // конструктор по умолчанию
    Data()
    {
         day=1;
         month=1;
         year = 1990;
    }

    // ввод даты с консоли
    void input_date()
    {
        bool answer = true; // корректна ли введенная дата
        string message = "";  // сообщение о причине ошибки
        do
        {
            if (!answer)
                cout << message << endl;
            day = input_number(1, 31, "Ввод даты:\nВведите день (1-31): ");
            month = input_number(1, 12, "Введите номер месяца (1-12): ");
            year = input_number(1970, 2018, "Введите год (1970-2018): ");
            answer = correct_date(day, month, year, message);
        } while (!answer);  // повторять ввод пока не корректная дата
    }

    // перевод даты в строку (для последующей записи в файл)
    string date_to_string()
    {
        return (to_string(day) + ' ' + to_string(month) + ' ' + to_string(year));
    }

    // перегруженный оператор равенства
    bool operator == (const Data &c)
    {
        return ((day == c.day) && (month == c.month) && (year == c.year));
    }

    // конструктор копирования
    Data& operator = (Data c)
    {
        day = c.day;
        month = c.month;
        year = c.year;

        return (*this);
    }

    // перегруженный оператор больше
    bool operator > (const Data &c)
    {
        return ((year > c.year) || ((year == c.year) && (month > c.month)) || ((year == c.year) && (month == c.month) && (day>c.day)));
    }

    // перегруженные оператор меньше
    bool operator < (const Data &c)
    {
        return ((year < c.year) || ((year == c.year) && (month < c.month)) || ((year == c.year) && (month == c.month) && (day<c.day)));
    }

};

class bank_account {
//public:
private:
    int number_account; // номер счета
    int code_account; // код счета
    string surname;// фамилия владельца
    double sum_on_the_account;// сумма на счете
    Data date_account_opening;// дата открытия счета
    int year_percent;// годовой процент начисления
public:
    // конструктор по умолчанию
    bank_account()
    {
        number_account=0;
        code_account=0;
        surname="";
        sum_on_the_account=0.0;
        Data date_account_opening;
        year_percent=0;
    }


    // изменение структуры "счет в банке"
    bank_account сhange_bank_account(bank_account &result)
    {
        if (input_number(0,1,"Вы хотите изменить номер счета " + to_string(result.number_account) + " (0 - нет, 1 - да)\nВыш выбор: ") ==1)
            this->number_account = input_number(0,999999,"Введите новый номер счета: ");
        if (input_number(0, 1, "Вы хотите изменить код счета" + to_string(result.code_account) + " (0 - нет, 1 - да)\nВыш выбор: ") == 1)
            this->surname = input_number(0,999999,"Введите новый код счета: ");
        if (input_number(0, 1, "Вы хотите изменить фамилию владельца " + result.surname + " (0 - нет, 1 - да)\nВыш выбор: ") == 1)
            this->surname = input_information("Введите новую фамилию владельца: ");
        if (input_number(0, 1, "Вы хотите изменить сумму на счете " + to_string(result.sum_on_the_account) + " (0-нет, 1 - да)\nВыш выбор: ") == 1)
            this->sum_on_the_account = input_number(0,999999,"Введите новую сумму (0 - 1000000): ");
        if (input_number(0, 1, "Вы хотите изменить дату открытия счета (0 - нет, 1 - да) \nВыш выбор: ") == 1)
            this->date_account_opening.input_date();
        if (input_number(0, 1, "Вы хотите изменить годовой процент начисления" + to_string(result.year_percent) + " (0 - нет, 1 - да)\nВыш выбор: ") == 1)
            this->year_percent = input_number(0, 9999999, "Введите новый годовой процент (0 - 100000): ");
        return result;
    }


// функция ввода структуры "счет в банке" с консоли
static bank_account input_screen_bank_account()
{
    bank_account c;
    c.number_account = input_number(0,999999,"Введите номер счета: ");
    c.code_account = input_number(0,999999,"Введите код счета: ");
    c.surname = input_information("Введите фамилию владельца: ");
    c.sum_on_the_account = input_number(0,999999, "Введите сумму на счете(0 - 999999): ");
    c.date_account_opening.input_date();
    c.year_percent = input_number(0,5,"Введите годовой процент начисления (0 - 5): ");
    return c;
}

// функция вывода структуры "счет в банке" на консоль
static void output_screen_bank_account(bank_account c)
{
    cout << "Номер счета: " << c.number_account << endl;
    cout << "Код счета: " << c.code_account << endl;
    cout << "Фамилия владельца: " << c.surname << endl;
    cout << "Сумма на счете: " << c.sum_on_the_account << endl;
    cout << "Дата: " << c.date_account_opening.date_to_string() << endl;
    cout << "Годовой процент начисления: " << c.year_percent << endl;
}

 
//извлечение структуры "дата" из строки. Формат: день месяц год
static Data from_string  /*hack()*/ (string str)
{
    Data result;
    try
    {
        istringstream is(str);
        string s;
        if (getline(is, s, ' '))
            result.day = atoi(s.c_str());
        if (getline(is, s, ' '))
            result.month = atoi(s.c_str());
        if (getline(is, s, ' '))
            result.year = atoi(s.c_str());
    }
    catch (...)
    {
        cout << "Ошибка записи в файл!" << endl;
    }
    return result;
}

//перевод структуры "счет в банке" в строку
static string bank_account_to_string(bank_account c,int i)
{
    return  "\nНомер счета: "+to_string(c.number_account)+"\n"+"Код счета: "+to_string(c.code_account)+"\n"+"Фамилия владельца: "+c.surname+"\n"+"Сумма на счете: "+to_string(c.sum_on_the_account)+"\n"+"Дата: " + c.date_account_opening.date_to_string() + "\n"+ "Годовой процент начисления: " + to_string(c.year_percent)+"\n";
}

//считывание структуры "счет в банке" из строки
static bank_account read_from_string(ifstream& input)
{
    bank_account result;
    string s;
    try
    {
        if (!input.eof())
        {
            getline(input, s);
        }
        if (!input.eof())
        {
            getline(input, s,'\n');
            string wrd = "Номер счета: ";
            result.number_account = atoi( s.substr( wrd.length(), s.length() ).c_str() );
        }
        if (!input.eof())
        {
            getline(input, s, '\n');
            string wrd = "Код счета: ";
            result.code_account = atoi( s.substr(wrd.length(), s.length() ).c_str() );//atoi: string-> int
        }
        if (!input.eof())
        {
            getline(input, s, '\n');
            string wrd = "Фамилия владельца: ";
            result.surname = s.substr(wrd.length(), s.length());
        }
        if (!input.eof())
        {
            getline(input, s, '\n');
            string wrd = "Сумма на счете: ";
            result.sum_on_the_account = atoi( s.substr(wrd.length(), s.length() ).c_str() );
        }
        if (!input.eof())
        {
            getline(input, s, '\n');
            string wrd = "Дата открытия счета: ";
            result.date_account_opening = from_string(s.substr(wrd.length(), s.length()));
        }
        if (!input.eof())
        {
            getline(input, s, '\n');
            string wrd = "Годовой процент начисления: ";
            result.year_percent = atoi( s.substr(wrd.length(), s.length() ).c_str() );
        }
    }
    catch (...)
    {
        cout << "Ошибка записи в файл!" << endl;
    }
    return result;
}

//поиск равного элемента по владельцу
static bool search_element_surname(bank_account m, bank_account n)
{
    return (m.surname == n.surname);
}

//поиск равного элемента по номеру счета
static bool search_element_number_account(bank_account m, bank_account n)
{
    return (m.number_account == n.number_account);
}

//поиск равного элемента по по дате
static bool search_element_surname_date_account_opening(bank_account m, bank_account n)
{
    return (m.date_account_opening == n.date_account_opening);
}

/* ввод критерия поиска в зависимости от выбранного типа. type_search - тип поиска
        1 - по владельцу
        2 - по номеру счета
        3 - по дате */
static bank_account input_change_type_search(int type_search)
{
    bank_account result;
    switch (type_search)
    {
        case 1:
            result.surname = input_information("Введите фамилию ");
            return result;
        case 2:
            result.number_account = input_number(0, 999999,"Введите номер счета: ");
            return result;
        case 3:
            result.date_account_opening.input_date();
            return result;
        default:
            return result;
    }
}

//сравнения структур по владельцу
static bool sorte_surname(bank_account n, bank_account m)
{
    return n.surname > m.surname;

}

//сравнения структур по номеру счета
static bool sorte_number_account(bank_account n, bank_account m)
{
    return  n.number_account > m.number_account;
}

//сравнения структур по дате
static bool sorte_date_account_opening(bank_account n, bank_account m)
{
    return n.date_account_opening > m.date_account_opening;
}


};
