//提交日期2024年4月21日
#pragma once
#include<iostream>
#include<vector>
#include<string.h>
#include <cstdlib>
#include"LNcalculator.h"
#include"LargeNumbersLinkedList.h"
using namespace std;

Number ReuseFun1(LNLinkedList TROC, char* name1) {
    Number num1;
    if (TROC.isEmpty() == 0) {
        while (true) {
            cout << endl;
            cout << "是否将上次运算的结果作为" << name1 << "?" << endl;
            cout << "         1.是           2.否            " << endl;
            cout << "输入选择：";
            char jiancha = '0';
            cin >> jiancha;
            cout << endl;
            if (jiancha == '1') {
                num1 = TROC.LNLLfindLastElement();
                break;
            }
            else if (jiancha == '2') {
                //第一个数的接收，包括正负，数体，小数点位置的读取
                num1 = ReceiveLargeNumbers(name1);
                break;
            }
            else {
                cout << endl;
                cout << "输入错误，请重新输入！" << endl;
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
    else {
        //第一个数的接收，包括正负，数体，小数点位置的读取
        num1 = ReceiveLargeNumbers(name1);
    }
    return num1;
}

void ShowMenu()//显示菜单
{
    cout << "                  注意事项                    " << endl;
    cout << "**********************************************" << endl << endl;
    cout << " 本计算器支持一亿位以下的的大数四则运算       " << endl << endl;
    cout << " 加法、减法和乘法无运算精度限制               " << endl << endl;
    cout << " 除法可自行设定精度，并可以输出余数           " << endl << endl;
    cout << " 注意！余数不被视作下次运算的有效输入         " << endl << endl;
    cout << " 如有需要，请自行保存余数！                   " << endl << endl;
    cout << " 开方、乘方为提高运算速度，会去除结果尾部的0！" << endl << endl;
    cout << "**********************************************" << endl;
    cout << "若已了解，请按任意键继续..." << endl;
    cin.get();
    system("cls");

    cout << endl;
    cout << "请输入除法精确度(保留的小数位数),建议小于1000以保证计算速度: ";
    int n;//除法精确度
    cin >> n;
    cout << endl;
    cout << "请给定一个牛顿法迭代次数上限(建议为100以保证结果精度): ";
    int precision;//牛顿法开平方迭代次数
    cin >> precision;
    cout << endl;
    cout << "请给定一个牛顿法迭代目标精度10^(-k),请输入k: ";
    int k;//牛顿法开平方迭代次数
    cin >> k;
    cout << endl;

    Number result;//计算结果
    Number remainder;//余数
    LNLinkedList TROC;//计算结果存储列表

    while (true) {
        Number num1(1, { 0 }, 0), num2(1, { 0 }, 0);//数1，数2，初始化为零
        char CalculationOperator = '0';//储存计算符号
        char name1[20] = "数1";//num1的名称
        char name2[20] = "数2";//num2的名称
        char chouse = '0';
        int jixu = 0;//判断是否输入错误
        do {
            cout << endl;
            cout << "****************************************" << endl << endl;
            cout << " 请选择你需要进行的运算：               " << endl << endl;
            cout << "         1.加法         2.减法          " << endl << endl;
            cout << "         3.乘法         4.除法          " << endl << endl;
            cout << "         5.开方         6.乘方          " << endl << endl;
            cout << "****************************************" << endl;
            cout << "输入你的选择：";
            cin >> chouse;//选择需要进行的运算
            cout << endl;
            jixu = 0;

            if (chouse == '1') {
                CalculationOperator = '+';
                strcpy_s(name1, "被加数");
                strcpy_s(name2, "加数");
                cout << "请严格按照+123.123456的形式输入，错误输入会导致接收大数错误，且无法更改！！" << endl;
                num1 = ReuseFun1(TROC, name1);
                //第二个数的接收，包括正负，数体，小数点位置的读取
                num2 = ReceiveLargeNumbers(name2);
                cout << endl << "开始计算！" << endl;
                result = add(num1, num2);
            }
            else if (chouse == '2') {
                CalculationOperator = '-';
                strcpy_s(name1, "被减数");
                strcpy_s(name2, "减数");
                cout << "请严格按照+123.123456的形式输入，错误输入会导致接收大数错误，且无法更改！！" << endl;
                num1 = ReuseFun1(TROC, name1);
                //第二个数的接收，包括正负，数体，小数点位置的读取
                num2 = ReceiveLargeNumbers(name2);
                cout << endl << "开始计算！" << endl;
                result = subtract(num1, num2);
            }
            else if (chouse == '3') {
                CalculationOperator = '*';
                strcpy_s(name1, "乘数1");
                strcpy_s(name2, "乘数2");
                cout << "请严格按照+123.123456的形式输入，错误输入会导致接收大数错误，且无法更改！！" << endl;
                num1 = ReuseFun1(TROC, name1);
                //第二个数的接收，包括正负，数体，小数点位置的读取
                num2 = ReceiveLargeNumbers(name2);
                cout << endl << "开始计算！" << endl;
                result = multiply(num1, num2);
            }
            else if (chouse == '4') {
                CalculationOperator = '/';
                strcpy_s(name1, "被除数");
                strcpy_s(name2, "除数");
                cout << "请严格按照+123.123456的形式输入，错误输入会导致接收大数错误，且无法更改！！" << endl;
                num1 = ReuseFun1(TROC, name1);
                //第二个数的接收，包括正负，数体，小数点位置的读取
                num2 = ReceiveLargeNumbers(name2);
                cout << endl << "开始计算！" << endl;
                result = divide(n, num1, num2, remainder);
            }
            else if (chouse == '5') {
                CalculationOperator = 'K';
                strcpy_s(name1, "被开方数");
                strcpy_s(name2, "开方次数");
                cout << "请输入开方次数:";
                int x;//开方次数
                cin >> x;
                cout << endl << "请严格按照+123.123456的形式输入，错误输入会导致接收大数错误，且无法更改！！" << endl;
                num1 = ReuseFun1(TROC, name1);
                for (int i = 0; i < x; i++) {
                    num2 = add(num2, one);
                }
                cout << endl << "开始计算！" << endl;
                if (x == 2)
                    result = mySqrt(num1, precision, n, k);
                else
                    result = SqrtX(num1, x, precision, n, k);
            }
            else if (chouse == '6') {
                CalculationOperator = '^';
                strcpy_s(name1, "底数");
                strcpy_s(name2, "指数");
                cout << "请输入指数:";
                int exponent;//指数
                cin >> exponent;
                cout << "请严格按照+123.123456的形式输入，错误输入会导致接收大数错误，且无法更改！！" << endl;
                num1 = ReuseFun1(TROC, name1);
                for (int i = 0; i < exponent; i++) {
                    num2 = add(num2, one);
                }
                cout << endl << "开始计算！" << endl;
                result = powerNumber(num1, exponent);
            }
            else {
                cout << "输入错误，请重新输入！" << endl;
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                jixu = 1;
            }
        } while (jixu == 1);

        //带小数点和正负的打印
        cout << "输入检查：" << endl;
        cout << name1 << ":";
        PrintLargeNumbers(num1);
        //cout << num1.PM << endl;
        //cout << num1.Decimal << endl;
        cout << name2 << ":";
        PrintLargeNumbers(num2);
        //cout << num2.PM << endl;
        //cout << num2.Decimal << endl;
        cout << endl;

        cout << "计算结果为: ";
        PrintLargeNumbers(result);
        //cout << result.PM << endl;
        //cout << result.Decimal << endl;

        if (chouse == '4') {
            cout << "除法得到的余数为: ";
            PrintLargeNumbers(remainder);
        }

        TROC.LNLLappend(num1, CalculationOperator, num2, result);

        char i = '0';
        int shifoutiaochu = 0;//是否结束计算
        do {
            i = '0'; shifoutiaochu = 0;
            cout << endl;
            cout << "运算结束！结果已保存，是否继续进行运算？" << endl;
            cout << "         1.是           2.否            " << endl;
            cout << "请输入选择：";           
            cin >> i;
            if (i == '2')
                shifoutiaochu = 1;
            if (i != '1' && i != '2') {
                cout << endl;
                cout << "输入错误，请重新输入！" << endl;
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            }
        } while (i != '1' && i != '2');
        if (shifoutiaochu == 1)
            break;
    }

    char j = '0';
    do {
        j = '0';
        cout << endl;
        cout << "是否需要打印所有计算结果？" << endl;
        cout << "         1.是           2.否            " << endl;
        cout << "请输入选择：";
        cin >> j;
        cout << endl;
        if (j == '1') {
            TROC.LNLLdisplay();
            cout << endl;
            cout << "除法精确度为: " << n << endl;
            cout << "牛顿法开平方迭代次数为: " << precision << endl;
            cout << endl;
        }
        if (j != '1' && j != '2') {
            cout << endl;
            cout << "输入错误，请重新输入！" << endl;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (j != '1' && j != '2');

}

void totolytask() {
    Number num1, num2;
    char name1[10] = "num1";
    char name2[10] = "num2";
    //第一个数的接收，包括正负，数体，小数点位置的读取
    num1 = ReceiveLargeNumbers(name1);

    //第二个数的接收，包括正负，数体，小数点位置的读取
    num2 = ReceiveLargeNumbers(name2);

    cout << "请输入除法精确度: ";
    int n;
    cin >> n;
    cout << endl;

    //只打印数的部分
    cout << "num1：";
    PrintNum(num1);
    cout << "num2：";
    PrintNum(num2);
    cout << endl;

    //带小数点和正负的打印
    cout << "num1:";
    PrintLargeNumbers(num1);
    cout << "num2:";
    PrintLargeNumbers(num2);
    cout << endl;

    //函数调用区
    vector<int> yushu;
    vector<int> a = addLargeNumbers(num1, num2);//数体加法，无关正负和小数点
    vector<int> b = subtractLargeNumbers(num1, num2);//数体减法
    vector<int> c = multiplyLargeNumbers(num1, num2);//数体乘法
    vector<int> d = divideLargeNumbers(num1, num2, yushu);//数体除法

    Number A = add(num1, num2);//加法，包含正负和小数点的处理

    Number B = subtract(num1, num2);

    Number C = multiply(num1, num2);

    Number remainder;
    Number D = divide(n, num1, num2, remainder);

    //结果打印区

    //数体部分的计算
    cout << "Result of addLargeNumbers: ";
    for (int digit : a) {
        cout << digit;
    }
    cout << endl;

    cout << "Result of subtractLargeNumbers: ";
    for (int digit : b) {
        cout << digit;
    }
    cout << endl;

    cout << "Result of multiplyLargeNumbers: ";
    for (int digit : c) {
        cout << digit;
    }
    cout << endl;

    cout << "Result of divideLargeNumbers: ";
    for (int digit : d) {
        cout << digit;
    }
    cout << endl;

    cout << "remainder of divideLargeNumbers: ";
    for (int digit : yushu) {
        cout << digit;
    }
    cout << endl;
    cout << endl;

    //大数计算
    cout << "Result of add: ";
    PrintLargeNumbers(A);

    cout << "Result of subtract: ";
    PrintLargeNumbers(B);

    cout << "Result of multiply: ";
    PrintLargeNumbers(C);

    cout << "Result of divide: ";
    PrintLargeNumbers(D);
    cout << "Remainder of divide: ";
    PrintLargeNumbers(remainder);

}