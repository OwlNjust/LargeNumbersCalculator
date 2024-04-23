//提交日期2024年4月21日
#pragma once
#include <iostream>
#include"LNcalculator.h"
using namespace std;

// 定义链表节点结构
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

// 定义链表类
class LNLinkedList {
private:
    Node* head;//保护形式储存表头

public:
    LNLinkedList() : head(nullptr) {}

    // 检查链表是否为空链表，空回1，非空回0
    bool isEmpty() {
        return head == nullptr;
    }

//输入区间：
    // 在链表末尾插入元素
    void LNLLappend(
        Number num1,
        char CalculationOperator,
        Number num2,
        Number result)
    {
        //建立新节点
        Node* newNode = new Node(num1, CalculationOperator, num2, result);
        if (head == nullptr) {
            head = newNode;//表头为空，则将新节点当作表头
        }
        else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;//表头非空，则找到现有列表的表尾
            }
            temp->next = newNode;//在表尾插入新节点
        }
    }

    // 在特定位置插入元素
    void LNLLinsertAt(Number num1,
        char CalculationOperator,
        Number num2,
        Number result,
        int position) {
        //建立新节点
        Node* newNode = new Node(num1, CalculationOperator, num2, result);
        //位置为0，在表头插入新节点
        if (position == 0) {
            newNode->next = head;
            head = newNode;
        }
        else {
            Node* temp = head;//读取表头位置，从表头开始往后找对应的位置
            for (int i = 0; i < position - 1 && temp != nullptr; ++i) {
                temp = temp->next;
            }
            //找到位置，位置处链表不为空
            if (temp != nullptr) {
                newNode->next = temp->next;
                temp->next = newNode;
            }
            //空的
            else {
                cout << "插入位置无效!" << endl;
            }
        }
    }

    // 删除特定位置的元素
    void NLLLdeleteAt(int position) {
        if (head == nullptr) {
            cout << "链表为空，无法删除!" << endl;
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
            //删除指定位置的节点，将后面的节点连接到前面
            if (temp != nullptr && temp->next != nullptr) {
                Node* toDelete = temp->next;
                temp->next = temp->next->next;
                delete toDelete;
            }
            else {
                cout << "删除位置无效!" << endl;
            }
        }
    }

//输出区间：
    // 输出特定位置的元素
    void LNLLprintAt(int position) {
        Node* temp = head;
        int index = 0;
        while (temp != nullptr && index < position) {
            temp = temp->next;
            index++;
        }

        if (temp != nullptr) {
            cout << "位置 " << position << " 的元素为: " << endl;
            PrintLargeNumbers(temp->num1);
            cout << temp->COtor;
            PrintLargeNumbers(temp->num2);
            cout << "=" << endl;
            PrintLargeNumbers(temp->result);
            cout << endl;
        }
        else {
            cout << "位置无效!" << endl;
        }
    }

    // 查找并返回链表最后一个元素的值
    Number LNLLfindLastElement() {
        Number zero;
        if (head == nullptr) {
            cout << "链表为空" << endl;
            return zero; // 返回0表示链表为空
        }

        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }

        return temp->result;
    }

    // 遍历并输出链表元素
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
