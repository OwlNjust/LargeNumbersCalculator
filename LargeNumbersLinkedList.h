//�ύ����2024��4��21��
#pragma once
#include <iostream>
#include"LNcalculator.h"
using namespace std;

// ��������ڵ�ṹ
struct Node {
    Number num1;
    char COtor;//CalculationOperator
    Number num2;
    Number result;
    Node* next;

    Node(Number num1,
        char CalculationOperator,
        Number num2,
        Number result) :
        num1(num1),
        COtor(CalculationOperator),
        num2(num2),
        result(result),
        next(nullptr) {}
};

// ����������
class LNLinkedList {
private:
    Node* head;//������ʽ�����ͷ

public:
    LNLinkedList() : head(nullptr) {}

    // ��������Ƿ�Ϊ�������ջ�1���ǿջ�0
    bool isEmpty() {
        return head == nullptr;
    }

//�������䣺
    // ������ĩβ����Ԫ��
    void LNLLappend(
        Number num1,
        char CalculationOperator,
        Number num2,
        Number result)
    {
        //�����½ڵ�
        Node* newNode = new Node(num1, CalculationOperator, num2, result);
        if (head == nullptr) {
            head = newNode;//��ͷΪ�գ����½ڵ㵱����ͷ
        }
        else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;//��ͷ�ǿգ����ҵ������б�ı�β
            }
            temp->next = newNode;//�ڱ�β�����½ڵ�
        }
    }

    // ���ض�λ�ò���Ԫ��
    void LNLLinsertAt(Number num1,
        char CalculationOperator,
        Number num2,
        Number result,
        int position) {
        //�����½ڵ�
        Node* newNode = new Node(num1, CalculationOperator, num2, result);
        //λ��Ϊ0���ڱ�ͷ�����½ڵ�
        if (position == 0) {
            newNode->next = head;
            head = newNode;
        }
        else {
            Node* temp = head;//��ȡ��ͷλ�ã��ӱ�ͷ��ʼ�����Ҷ�Ӧ��λ��
            for (int i = 0; i < position - 1 && temp != nullptr; ++i) {
                temp = temp->next;
            }
            //�ҵ�λ�ã�λ�ô�����Ϊ��
            if (temp != nullptr) {
                newNode->next = temp->next;
                temp->next = newNode;
            }
            //�յ�
            else {
                cout << "����λ����Ч!" << endl;
            }
        }
    }

    // ɾ���ض�λ�õ�Ԫ��
    void NLLLdeleteAt(int position) {
        if (head == nullptr) {
            cout << "����Ϊ�գ��޷�ɾ��!" << endl;
            return;
        }
        if (position == 0) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        else {
            Node* temp = head;
            for (int i = 0; i < position - 1 && temp != nullptr; ++i) {
                temp = temp->next;
            }
            //ɾ��ָ��λ�õĽڵ㣬������Ľڵ����ӵ�ǰ��
            if (temp != nullptr && temp->next != nullptr) {
                Node* toDelete = temp->next;
                temp->next = temp->next->next;
                delete toDelete;
            }
            else {
                cout << "ɾ��λ����Ч!" << endl;
            }
        }
    }

//������䣺
    // ����ض�λ�õ�Ԫ��
    void LNLLprintAt(int position) {
        Node* temp = head;
        int index = 0;
        while (temp != nullptr && index < position) {
            temp = temp->next;
            index++;
        }

        if (temp != nullptr) {
            cout << "λ�� " << position << " ��Ԫ��Ϊ: " << endl;
            PrintLargeNumbers(temp->num1);
            cout << temp->COtor;
            PrintLargeNumbers(temp->num2);
            cout << "=" << endl;
            PrintLargeNumbers(temp->result);
            cout << endl;
        }
        else {
            cout << "λ����Ч!" << endl;
        }
    }

    // ���Ҳ������������һ��Ԫ�ص�ֵ
    Number LNLLfindLastElement() {
        Number zero;
        if (head == nullptr) {
            cout << "����Ϊ��" << endl;
            return zero; // ����0��ʾ����Ϊ��
        }

        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }

        return temp->result;
    }

    // �������������Ԫ��
    void LNLLdisplay() {
        Node* temp = head;
        while (temp != nullptr) {

            PrintLargeNumbers(temp->num1);
            cout << temp->COtor << endl;
            PrintLargeNumbers(temp->num2);
            cout << "=" << endl;
            PrintLargeNumbers(temp->result);
            cout << endl;

            temp = temp->next;
        }
        cout << endl;
    }
};
