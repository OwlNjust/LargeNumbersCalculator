//�ύ����2024��4��21��
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
            cout << "�Ƿ��ϴ�����Ľ����Ϊ" << name1 << "?" << endl;
            cout << "         1.��           2.��            " << endl;
            cout << "����ѡ��";
            char jiancha = '0';
            cin >> jiancha;
            cout << endl;
            if (jiancha == '1') {
                num1 = TROC.LNLLfindLastElement();
                break;
            }
            else if (jiancha == '2') {
                //��һ�����Ľ��գ��������������壬С����λ�õĶ�ȡ
                num1 = ReceiveLargeNumbers(name1);
                break;
            }
            else {
                cout << endl;
                cout << "����������������룡" << endl;
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
    else {
        //��һ�����Ľ��գ��������������壬С����λ�õĶ�ȡ
        num1 = ReceiveLargeNumbers(name1);
    }
    return num1;
}

void ShowMenu()//��ʾ�˵�
{
    cout << "                  ע������                    " << endl;
    cout << "**********************************************" << endl << endl;
    cout << " ��������֧��һ��λ���µĵĴ�����������       " << endl << endl;
    cout << " �ӷ��������ͳ˷������㾫������               " << endl << endl;
    cout << " �����������趨���ȣ��������������           " << endl << endl;
    cout << " ע�⣡�������������´��������Ч����         " << endl << endl;
    cout << " ������Ҫ�������б���������                   " << endl << endl;
    cout << " �������˷�Ϊ��������ٶȣ���ȥ�����β����0��" << endl << endl;
    cout << "**********************************************" << endl;
    cout << "�����˽⣬�밴���������..." << endl;
    cin.get();
    system("cls");

    cout << endl;
    cout << "�����������ȷ��(������С��λ��),����С��1000�Ա�֤�����ٶ�: ";
    int n;//������ȷ��
    cin >> n;
    cout << endl;
    cout << "�����һ��ţ�ٷ�������������(����Ϊ100�Ա�֤�������): ";
    int precision;//ţ�ٷ���ƽ����������
    cin >> precision;
    cout << endl;
    cout << "�����һ��ţ�ٷ�����Ŀ�꾫��10^(-k),������k: ";
    int k;//ţ�ٷ���ƽ����������
    cin >> k;
    cout << endl;

    Number result;//������
    Number remainder;//����
    LNLinkedList TROC;//�������洢�б�

    while (true) {
        Number num1(1, { 0 }, 0), num2(1, { 0 }, 0);//��1����2����ʼ��Ϊ��
        char CalculationOperator = '0';//����������
        char name1[20] = "��1";//num1������
        char name2[20] = "��2";//num2������
        char chouse = '0';
        int jixu = 0;//�ж��Ƿ��������
        do {
            cout << endl;
            cout << "****************************************" << endl << endl;
            cout << " ��ѡ������Ҫ���е����㣺               " << endl << endl;
            cout << "         1.�ӷ�         2.����          " << endl << endl;
            cout << "         3.�˷�         4.����          " << endl << endl;
            cout << "         5.����         6.�˷�          " << endl << endl;
            cout << "****************************************" << endl;
            cout << "�������ѡ��";
            cin >> chouse;//ѡ����Ҫ���е�����
            cout << endl;
            jixu = 0;

            if (chouse == '1') {
                CalculationOperator = '+';
                strcpy_s(name1, "������");
                strcpy_s(name2, "����");
                cout << "���ϸ���+123.123456����ʽ���룬��������ᵼ�½��մ����������޷����ģ���" << endl;
                num1 = ReuseFun1(TROC, name1);
                //�ڶ������Ľ��գ��������������壬С����λ�õĶ�ȡ
                num2 = ReceiveLargeNumbers(name2);
                cout << endl << "��ʼ���㣡" << endl;
                result = add(num1, num2);
            }
            else if (chouse == '2') {
                CalculationOperator = '-';
                strcpy_s(name1, "������");
                strcpy_s(name2, "����");
                cout << "���ϸ���+123.123456����ʽ���룬��������ᵼ�½��մ����������޷����ģ���" << endl;
                num1 = ReuseFun1(TROC, name1);
                //�ڶ������Ľ��գ��������������壬С����λ�õĶ�ȡ
                num2 = ReceiveLargeNumbers(name2);
                cout << endl << "��ʼ���㣡" << endl;
                result = subtract(num1, num2);
            }
            else if (chouse == '3') {
                CalculationOperator = '*';
                strcpy_s(name1, "����1");
                strcpy_s(name2, "����2");
                cout << "���ϸ���+123.123456����ʽ���룬��������ᵼ�½��մ����������޷����ģ���" << endl;
                num1 = ReuseFun1(TROC, name1);
                //�ڶ������Ľ��գ��������������壬С����λ�õĶ�ȡ
                num2 = ReceiveLargeNumbers(name2);
                cout << endl << "��ʼ���㣡" << endl;
                result = multiply(num1, num2);
            }
            else if (chouse == '4') {
                CalculationOperator = '/';
                strcpy_s(name1, "������");
                strcpy_s(name2, "����");
                cout << "���ϸ���+123.123456����ʽ���룬��������ᵼ�½��մ����������޷����ģ���" << endl;
                num1 = ReuseFun1(TROC, name1);
                //�ڶ������Ľ��գ��������������壬С����λ�õĶ�ȡ
                num2 = ReceiveLargeNumbers(name2);
                cout << endl << "��ʼ���㣡" << endl;
                result = divide(n, num1, num2, remainder);
            }
            else if (chouse == '5') {
                CalculationOperator = 'K';
                strcpy_s(name1, "��������");
                strcpy_s(name2, "��������");
                cout << "�����뿪������:";
                int x;//��������
                cin >> x;
                cout << endl << "���ϸ���+123.123456����ʽ���룬��������ᵼ�½��մ����������޷����ģ���" << endl;
                num1 = ReuseFun1(TROC, name1);
                for (int i = 0; i < x; i++) {
                    num2 = add(num2, one);
                }
                cout << endl << "��ʼ���㣡" << endl;
                if (x == 2)
                    result = mySqrt(num1, precision, n, k);
                else
                    result = SqrtX(num1, x, precision, n, k);
            }
            else if (chouse == '6') {
                CalculationOperator = '^';
                strcpy_s(name1, "����");
                strcpy_s(name2, "ָ��");
                cout << "������ָ��:";
                int exponent;//ָ��
                cin >> exponent;
                cout << "���ϸ���+123.123456����ʽ���룬��������ᵼ�½��մ����������޷����ģ���" << endl;
                num1 = ReuseFun1(TROC, name1);
                for (int i = 0; i < exponent; i++) {
                    num2 = add(num2, one);
                }
                cout << endl << "��ʼ���㣡" << endl;
                result = powerNumber(num1, exponent);
            }
            else {
                cout << "����������������룡" << endl;
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                jixu = 1;
            }
        } while (jixu == 1);

        //��С����������Ĵ�ӡ
        cout << "�����飺" << endl;
        cout << name1 << ":";
        PrintLargeNumbers(num1);
        //cout << num1.PM << endl;
        //cout << num1.Decimal << endl;
        cout << name2 << ":";
        PrintLargeNumbers(num2);
        //cout << num2.PM << endl;
        //cout << num2.Decimal << endl;
        cout << endl;

        cout << "������Ϊ: ";
        PrintLargeNumbers(result);
        //cout << result.PM << endl;
        //cout << result.Decimal << endl;

        if (chouse == '4') {
            cout << "�����õ�������Ϊ: ";
            PrintLargeNumbers(remainder);
        }

        TROC.LNLLappend(num1, CalculationOperator, num2, result);

        char i = '0';
        int shifoutiaochu = 0;//�Ƿ��������
        do {
            i = '0'; shifoutiaochu = 0;
            cout << endl;
            cout << "�������������ѱ��棬�Ƿ�����������㣿" << endl;
            cout << "         1.��           2.��            " << endl;
            cout << "������ѡ��";           
            cin >> i;
            if (i == '2')
                shifoutiaochu = 1;
            if (i != '1' && i != '2') {
                cout << endl;
                cout << "����������������룡" << endl;
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
        cout << "�Ƿ���Ҫ��ӡ���м�������" << endl;
        cout << "         1.��           2.��            " << endl;
        cout << "������ѡ��";
        cin >> j;
        cout << endl;
        if (j == '1') {
            TROC.LNLLdisplay();
            cout << endl;
            cout << "������ȷ��Ϊ: " << n << endl;
            cout << "ţ�ٷ���ƽ����������Ϊ: " << precision << endl;
            cout << endl;
        }
        if (j != '1' && j != '2') {
            cout << endl;
            cout << "����������������룡" << endl;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (j != '1' && j != '2');

}

void totolytask() {
    Number num1, num2;
    char name1[10] = "num1";
    char name2[10] = "num2";
    //��һ�����Ľ��գ��������������壬С����λ�õĶ�ȡ
    num1 = ReceiveLargeNumbers(name1);

    //�ڶ������Ľ��գ��������������壬С����λ�õĶ�ȡ
    num2 = ReceiveLargeNumbers(name2);

    cout << "�����������ȷ��: ";
    int n;
    cin >> n;
    cout << endl;

    //ֻ��ӡ���Ĳ���
    cout << "num1��";
    PrintNum(num1);
    cout << "num2��";
    PrintNum(num2);
    cout << endl;

    //��С����������Ĵ�ӡ
    cout << "num1:";
    PrintLargeNumbers(num1);
    cout << "num2:";
    PrintLargeNumbers(num2);
    cout << endl;

    //����������
    vector<int> yushu;
    vector<int> a = addLargeNumbers(num1, num2);//����ӷ����޹�������С����
    vector<int> b = subtractLargeNumbers(num1, num2);//�������
    vector<int> c = multiplyLargeNumbers(num1, num2);//����˷�
    vector<int> d = divideLargeNumbers(num1, num2, yushu);//�������

    Number A = add(num1, num2);//�ӷ�������������С����Ĵ���

    Number B = subtract(num1, num2);

    Number C = multiply(num1, num2);

    Number remainder;
    Number D = divide(n, num1, num2, remainder);

    //�����ӡ��

    //���岿�ֵļ���
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

    //��������
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