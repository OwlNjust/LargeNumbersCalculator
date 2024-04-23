//�ύ����2024��4��21��
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <ctype.h>
using namespace std;

struct Number{
    int PM;//�������
    vector<int> num;//����
    int Decimal;//С��λ��
    //pmΪ������1Ϊ����0Ϊ����nΪ������decimal����С��λ��
    Number(int pm = 1, vector<int> n = { 0 }, long long int decimal = 0) {
        num = n;
        PM = pm;
        Decimal = decimal;//����С��λ��Ϊ��
    }
};


vector<int> one1 = { 1 };
Number one(1, one1, 0);//����1
vector<int> one0 = { 01 };
Number one01(1, one0, 1);//����0.1

//�����Ľ��գ��������������壬С����λ�õĶ�ȡ
Number ReceiveLargeNumbers(const char* name) {
    Number receive;
    vector<int> n;
    char input;

    cout << "������" << name << "���Իس�������" << endl;
    cin.clear(); // ����κδ���״̬
    //����������е���һ���ַ��Ƿ��ǻ��з� \n ��س��� \r
    while (cin.peek() == '\n' || cin.peek() == '\r') {
        //���������к���һ���ַ�
        cin.ignore();
    }

    bool decimal_found = false;
    while (cin.get(input) && input != '\n') {
        //����������Ϣ
        if (input == '+' || input == '-') {
            receive.PM = (input == '+') ? 1 : 0;
            continue;
        }
        //��¼����
        if (isdigit(input)) {
            //������β������
            n.push_back(input - '0');
            if (decimal_found) {
                receive.Decimal++;
            }
        }
        //����С�����ʼ��¼С��λ��
        else if (input == '.' && !decimal_found) {
            decimal_found = true; // ȷ��С����ֻ����һ��
        }
    }

    receive.num = n;
    return receive;
}

//�����Ĵ�����ӡ������������С����
void PrintLargeNumbers(Number number) {
    if (number.PM == 1)
        cout << "+";
    else
        cout << "-";
    int i1 = number.num.size() - number.Decimal;
    int i = 0;
    for (int digit : number.num) {
        cout << digit;
        i++;
        if (i == i1 && number.Decimal != 0)
            cout << ".";
    }
    cout << endl;
}

//ֻ��ӡ���岿��
void PrintNum(Number number) {
    for (int digit : number.num) {
        cout << digit;
    }
    cout << endl;
}

//��10��n�η�(n>=0)ת��Ϊ����
vector<int> powerOfTen(int n) {
    vector<int> result = { 1 };
    if (n <= 0)
        return result;
    for (int i = 0; i < n; i++) {
        result.push_back(0);
    }
    return result;
}

//��һ�����������������ת��Ϊ����
vector<int> integerToVector(long long n) {
    vector<int> result;

    // ��������λ�洢��������
    while (n > 0) {
        result.insert(result.begin(), n % 10); // ���뵽��λ
        n /= 10;
    }
    // ��Ϊ0����ֻ�洢һ��0
    if (result.size() == 1 && result[0] == 1) {
        result.push_back(0);
    }

    return result;
}

// �Ƚ������������Ĵ�С������ʱ����1������ʱ����0��С��ʱ����-1
int compareLargeNumbers(vector<int> num1, vector<int> num2) {
    //���Ժ���ǰ���㣬�������
    int start1 = 0;
    while (start1 < num1.size() && num1[start1] == 0) start1++;
    int start2 = 0;
    while (start2 < num2.size() && num2[start2] == 0) start2++;

    int size1 = num1.size() - start1;
    int size2 = num2.size() - start2;
    if (size1 != size2) {
        return size1 > size2 ? 1 : -1;
    }
    for (int i = 0; i < size1; i++) {
        if (num1[start1 + i] != num2[start2 + i]) {
            return num1[start1 + i] > num2[start2 + i] ? 1 : -1;
        }
    }
    return 0;
}

//�����ӷ�
vector<int> addLargeNumbers(Number num1, Number num2) {
    vector<int> result;

    // ȥ��ǰ���㣬ͬʱ����ȫ������Ϊ��
    while (!num1.num.empty() && num1.num.front() == 0) {
        num1.num.erase(num1.num.begin());
    }
    //ȷ���洢�������ֵ����������ٰ���һ��Ԫ��
    if (num1.num.empty()) num1.num.push_back(0);
    while (!num2.num.empty() && num2.num.front() == 0) {
        num2.num.erase(num2.num.begin());
    }
    if (num2.num.empty()) num2.num.push_back(0);

    int carry = 0;
    int i = num1.num.size() - 1;
    int j = num2.num.size() - 1;
    while (i >= 0 || j >= 0 || carry != 0) {
        int sum = carry;
        if (i >= 0) sum += num1.num[i];
        i--;
        if (j >= 0) sum += num2.num[j];
        j--;
        //ֱ�ӷ��봦�������������ظ��ı�Ԫ��λ�ã��������
        result.push_back(sum % 10);
        carry = sum / 10;
    }
    // ��ת����Ի����ȷ��˳��
    reverse(result.begin(), result.end());
    return result;
}


//����������num1��num2��ע�Ᵽ֤�����num1ʼ��num2
vector<int> subtractLargeNumbers(Number num1, Number num2) {
    vector<int> result;

    // ȥ��ǰ���㣬ͬʱ����ȫ������Ϊ��
    while (!num1.num.empty() && num1.num.front() == 0) {
        num1.num.erase(num1.num.begin());
    }
    //ȷ���洢�������ֵ����������ٰ���һ��Ԫ��
    if (num1.num.empty()) num1.num.push_back(0);
    while (!num2.num.empty() && num2.num.front() == 0) {
        num2.num.erase(num2.num.begin());
    }
    if (num2.num.empty()) num2.num.push_back(0);

    //���ٲ���Ҫ��ѭ��
    if (num1.num == num2.num) {
        result = { 0 };
        return result;
    }
    //�õ����һλ��λ��
    int i = num1.num.size() - 1;
    int j = num2.num.size() - 1;
    int borrow = 0;

    while (i >= 0 || j >= 0) {
        //�����һλ��ʼ����
        int digit = (i >= 0 ? num1.num[i] : 0) - borrow;
        if (j >= 0) {
            digit -= num2.num[j];
            j--;
        }

        if (digit < 0) {
            digit += 10;
            borrow = 1;
        }
        else {
            borrow = 0;
        }
        //ֱ�ӷ��봦�������������ظ��ı�Ԫ��λ�ã��������
        result.push_back(digit);
        i--;
    }
    // ��ת����Ի����ȷ��˳��
    reverse(result.begin(), result.end());
    // �Ƴ�����еĸ�λ��
    while (!result.empty() && result.front() == 0) {
        result.erase(result.begin());
    }
    return result;
}

//�����˷����ۼӷ���
vector<int> multiplyLargeNumbers(Number num1, Number num2) {

    // ȥ��ǰ���㣬ͬʱ����ȫ������Ϊ��
    while (!num1.num.empty() && num1.num.front() == 0) {
        num1.num.erase(num1.num.begin());
    }
    //ȷ���洢�������ֵ����������ٰ���һ��Ԫ��
    if (num1.num.empty()) num1.num.push_back(0);
    while (!num2.num.empty() && num2.num.front() == 0) {
        num2.num.erase(num2.num.begin());
    }
    if (num2.num.empty()) num2.num.push_back(0);

    //Ϊ������ض�һλ���޸ģ���Ҫ�����������������
    vector<int> result(num1.num.size() + num2.num.size(), 0);
    //����ѭ��ʵ�����㣬��ʵ��ͨ��sum�ڲ��������Ĺ����н��ۼӹ���Ҳʵ���ˣ������˵��������ӷ�������Ҳ�����˴洢����
    for (int i = num1.num.size() - 1; i >= 0; --i) {
        for (int j = num2.num.size() - 1; j >= 0; --j) {
            int product = num1.num[i] * num2.num[j];
            int pos1 = i + j, pos2 = i + j + 1;
            int sum = product + result[pos2];

            result[pos1] += sum / 10;
            result[pos2] = sum % 10;
        }
    }

    // ȥ������еĸ�λ��
    while (result.size() > 1 && result[0] == 0) {
        result.erase(result.begin());
    }

    return result;
}

//����������num1����num2����remainder�������
vector<int> divideLargeNumbers(Number num1, Number num2, vector<int>& remainder) {
    vector<int> result;
    Number dividend = num1;//������
    Number divisor = num2;//����

    // ȥ��ǰ���㣬ͬʱ����ȫ������Ϊ��
    while (!num1.num.empty() && num1.num.front() == 0) {
        num1.num.erase(num1.num.begin());
    }
    //ȷ���洢�������ֵ����������ٰ���һ��Ԫ��
    if (num1.num.empty()) num1.num.push_back(0);
    while (!num2.num.empty() && num2.num.front() == 0) {
        num2.num.erase(num2.num.begin());
    }
    if (num2.num.empty()) num2.num.push_back(0);

    Number quotient(1, { 0 }, 0);//��
    Number p;//��ʱ�洢����
    Number zero;
    //vector<int> remainder������

    // ����������� 
    if (num2.num.size() == 1 && num2.num[0] == 0) {
        cout << "Error: ��������Ϊ0!" << endl;
        return result = { 0 };
    }

    //if��ÿһ���dividend.num, divisor.num�����ܸı䣬�ʱ������±Ƚϴ�С
    if (compareLargeNumbers(dividend.num, divisor.num) == 1) {
        //��Ҫ��ӵ�0������
        int n = dividend.num.size() - divisor.num.size();
        for (int i = 0; i < n; i++) {
            //��divisorĩβ���n��0
            divisor.num.insert(divisor.num.end(), 0);
        }
        //�Ը��ĺ��num1��num2���±Ƚϴ�С��������һ��
        if (compareLargeNumbers(dividend.num, divisor.num) == -1) {
            // ɾ��������ĩβԪ��
            divisor.num.pop_back();
            n--;
        }
        while (n >= 0) {
            Number quo(1, { 0 }, 0);//����ÿ��λ����
            if (dividend.num == zero.num)break;
            while (compareLargeNumbers(dividend.num, divisor.num) == 1
                || compareLargeNumbers(dividend.num, divisor.num) == 0) {
                dividend.num = subtractLargeNumbers(dividend, divisor);
                quo.num = addLargeNumbers(quo, one);
            }
            p.num = powerOfTen(n);
            quo.num = multiplyLargeNumbers(quo, p);
            // ɾ��������ĩβԪ��
            if (n > 0)divisor.num.pop_back();
            n--;
            quotient.num = addLargeNumbers(quotient, quo);
        }
        remainder = dividend.num;
    }
    else if (compareLargeNumbers(dividend.num, divisor.num) == -1) {
        quotient.num = { 0 };
        remainder = num1.num;
    }
    else {
        quotient.num = { 1 };
        remainder = { 0 };
    }
    return result = quotient.num;
}

//�Ƚ�����������num1��num2������ʱ����1������ʱ����0��С��ʱ����-1
int compareNumber(Number& num1, Number& num2) {
    // ��ʱ�����������޸�ԭʼ����
    Number temp1 = num1;
    Number temp2 = num2;
    Number p(1, { 0 }, 0);//��ʱ�洢����

    // �Ƚ��������
    if (temp1.PM != temp2.PM) {
        return temp1.PM > temp2.PM ? 1 : -1;  // �������ڸ���
    }

    // �������������Ǹ��������
    int sign = temp1.PM == 1 ? 1 : -1;

    // ����λ��
    if (temp1.Decimal > temp2.Decimal) {
        int diff = temp1.Decimal - temp2.Decimal;
        p.num = powerOfTen(diff);
        temp2.num = multiplyLargeNumbers(temp2, p);
        temp2.Decimal += diff;
    }
    else if (temp1.Decimal < temp2.Decimal) {
        int diff = temp2.Decimal - temp1.Decimal;
        p.num = powerOfTen(diff);
        temp1.num = multiplyLargeNumbers(temp1, p);
        temp1.Decimal += diff;
    }

    // ����λ����󣬱Ƚ����ִ�С
    int result = compareLargeNumbers(temp1.num, temp2.num);
    if (result == 0) {
        return 0;  // ������ͬ
    }
    else if (result == -1) {
        return -1 * sign;  // ��һ����С
    }
    else if (result == 1) {
        return 1 * sign;  // ��һ������
    }

    return 0; // Ĭ�Ϸ�����ȣ������ϲ��ᵽ������
}

//�ӷ�num1+num2
Number add(Number num1, Number num2) {
    Number result;
    Number p(1, { 0 }, 0);//��ʱ�洢����
    Number zero(1, { 0 }, 0);

    int n1 = num1.Decimal;
    int n2 = num2.Decimal;

    //����λ��
    if (n1 > n2) {
        int nn = n1 - n2;//С��λ����ֵ
        p.num = powerOfTen(nn);
        num2.num = multiplyLargeNumbers(num2, p);
        num2.Decimal = num2.Decimal + nn;
    }
    if (n1 < n2) {
        int nn = n2 - n1;//С��λ����ֵ
        p.num = powerOfTen(nn);
        num1.num = multiplyLargeNumbers(num1, p);
        num1.Decimal = num1.Decimal + nn;
    }

    //ʵ�ּӷ�
    if (num1.PM == num2.PM) {
        result.PM = num1.PM;//=num2.PM
        result.num = addLargeNumbers(num1, num2);
    }
    if (num1.PM != num2.PM) {
        int com = compareLargeNumbers(num1.num, num2.num);
        if (com == 1) {
            result.PM = num1.PM;
            result.num = subtractLargeNumbers(num1, num2);
        }
        else if (com == -1) {
            result.PM = num2.PM;
            result.num = subtractLargeNumbers(num2, num1);
        }
        else
            result = zero;
    }

    result.Decimal = num1.Decimal;//=num2.Decimal
    //����С��һ������Ϊ�˴�ӡʱ��������Ҫ������ǰ���Ϻ���������0
    int k = result.Decimal - result.num.size() + 1;
    for (int i = 0; i < k; i++)
        result.num.insert(result.num.begin(), 0);

    return result;
}

//����num1-num2
Number subtract(Number num1, Number num2) {
    Number result;
    if (num1.PM == 1 && num2.PM == 1)
        num2.PM = 0;
    else if (num1.PM == 0 && num2.PM == 0)
        num2.PM = 1;
    else if (num1.PM == 1 && num2.PM == 0)
        num2.PM = 1;
    else
        num2.PM = 0;
    result = add(num1, num2);

    return result;
}

//�˷�num1*num2
Number multiply(Number num1, Number num2) {
    Number result;

    result.num = multiplyLargeNumbers(num1, num2);
    result.Decimal = num1.Decimal + num2.Decimal;

    if (num1.PM == num2.PM)
        result.PM = 1;
    else if (num1.PM != num2.PM)
        result.PM = 0;
    //����С��һ������Ϊ�˴�ӡʱ��������Ҫ������ǰ���Ϻ���������0
    int k = result.Decimal - result.num.size() + 1;
    for (int i = 0; i < k; i++)
        result.num.insert(result.num.begin(), 0);

    return result;
}

//����num1/num2.nΪ����뾫ȷ����С��λ��
Number divide(int n, Number num1, Number num2, Number& remainder) {
    Number result;
    Number quotient(1, { 0 }, 0);//��
    Number p(1, { 0 }, 0);//��ʱ�洢����
    remainder = p;//�������

    int n1 = num1.Decimal;
    int n2 = num2.Decimal;
    //����λ��
    if (n1 > n2) {
        int nn = n1 - n2;//С��λ����ֵ
        p.num = powerOfTen(nn);
        num2.num = multiplyLargeNumbers(num2, p);
        num2.Decimal = num2.Decimal + nn;
    }
    if (n1 < n2) {
        int nn = n2 - n1;//С��λ����ֵ
        p.num = powerOfTen(nn);
        num1.num = multiplyLargeNumbers(num1, p);
        num1.Decimal = num1.Decimal + nn;
    }

    //ʵ�ֳ���
    int com = compareLargeNumbers(num1.num, num2.num);
    if (com == 1) {
        p.num = powerOfTen(n);
        num1.num = multiplyLargeNumbers(num1, p);
        num1.Decimal = num1.Decimal + n;
        quotient.num = divideLargeNumbers(num1, num2, remainder.num);
        quotient.Decimal = n;

        int j = num1.Decimal - remainder.num.size() + 1;
        for (int i = 0; i < j; i++)
            remainder.num.insert(remainder.num.begin(), 0);
        remainder.Decimal = num1.Decimal;
    }
    if (com == -1) {
        p.num = powerOfTen(n);
        num1.num = multiplyLargeNumbers(num1, p);
        num1.Decimal = num1.Decimal + n;
        quotient.num = divideLargeNumbers(num1, num2, remainder.num);
        quotient.Decimal = n;

        int j = num1.Decimal - remainder.num.size() + 1;
        for (int i = 0; i < j; i++)
            remainder.num.insert(remainder.num.begin(), 0);
        remainder.Decimal = num1.Decimal;

        int k = quotient.Decimal - quotient.num.size() + 1;
        for (int i = 0; i < k; i++)
            quotient.num.insert(quotient.num.begin(), 0);
    }
    if (com == 0) {
        quotient.num = { 1 };
        quotient.Decimal = 0;
    }
    //���������
    remainder.PM = num1.PM;
    if (num1.PM == num2.PM)
        quotient.PM = 1;
    else
        quotient.PM = 0;

    result = quotient;
    //����С��һ������Ϊ�˴�ӡʱ��������Ҫ������ǰ���Ϻ���������0
    int k = result.Decimal - result.num.size() + 1;
    for (int i = 0; i < k; i++)
        result.num.insert(result.num.begin(), 0);

    return result;
}

// �����˷����㣬���� base �� exp �η�
Number powerNumber(Number base, int exp) {
    if (exp < 0) {
        cout << "���󣺲�֧�ָ���ָ�������������㡣" << endl;
        return Number(1, { 1 }, 0);  // ����Ĭ�Ϲ����Number����
    }
    if (exp == 0 || (base.num.size() == 1 && base.num[0] == 1)) {
        return Number(1, { 1 }, 0);  // �κ�����0������1��1���κδ�����1
    }
    if (base.num.size() == 1 && base.num[0] == 0) {
        if (exp == 0) {
            return Number(1, { 1 }, 0);  // 0��0���ݶ���Ϊ1
        }
        return Number(1, { 0 }, 0);  // 0���κ�����������0
    }

    Number result(1, { 1 }, 0);  // ��ʼ��Ϊ 1
    Number current_base = base;  // ��ǰ����Ϊ base

    while (exp > 0) {
        while (true) {
            int j = current_base.num.size();
            if (current_base.num[j - 1] == 0) {
                current_base.num.pop_back();
                current_base.Decimal = current_base.Decimal - 1;
            }
            else
                break;
        }

        //�˷��������
        if (exp % 2 == 1) {  // ���ָ��Ϊ����
            result = multiply(result, current_base);  // ������Ե�ǰ����
        }
        current_base = multiply(current_base, current_base);  // ����ƽ��
        exp /= 2;  // ָ������ 2

        while (true) {
            int i = result.num.size();
            if (result.num[i - 1] == 0) {
                result.num.pop_back();
                result.Decimal = result.Decimal - 1;
            }
            else
                break;
        }
    }

    return result;
}

//�ж�һ�������Ƿ�ӵ�һ��Ԫ�ص���k+1��Ԫ�ض�Ϊ��
bool vectorZero(const std::vector<int>& vec, int k) {
    if (vec.size() < k + 1) return false; // ȷ������������ k+1 ��Ԫ��
    for (int i = 0; i <= k; ++i) {
        if (vec[i] != 0) return false;
    }
    return true;
}

//Newton������,precisionΪ����������nΪ��������,kΪ�������
Number mySqrt(Number num, int precision = 100, int n = 10, int k = 10) {
    Number zero(1, { 0 }, 0);
    Number remainder = zero;//������� 
    // ��鸺��
    if (num.PM == 0) {
        cout << "���󣡸���û��ʵ��ƽ������" << endl;
        return zero;  // ����0
    }
    // �����ֵ���룬����������
    if (num.num == zero.num) {
        //cout << "��ʾ������Ϊ�㣬��ƽ����Ϊ�㡣" << endl;
        return zero;
    }
    // ��ʼ���²�ֵΪ num/2 �� 1��ȡ����num��ֵ
    Number guess = divide(n, num, Number(1, { 2 }, 0), remainder);  // ʹ�ó���������ȡ��ʼ�²�
    Number prevGuess = zero;

    // �߾��ȵ�ƽ�������㣬��������10�Σ�����ֱ������
    for (int i = 0; i < precision; i++) {
        prevGuess = guess;

        // ʹ��ţ�ٵ�����ʽ
        // guess = (guess + num/guess) / 2
        Number num_div_guess = divide(n, num, guess, remainder);  // num/guess
        Number sum = add(guess, num_div_guess);  // guess + num/guess
        guess = divide(n, sum, Number(1, { 2 }, 0), remainder);  // (guess + num/guess) / 2
        while (true) {
            int j = guess.num.size();
            if (guess.num[j - 1] == 0) {
                guess.num.pop_back();
                guess.Decimal = guess.Decimal - 1;
            }
            else
                break;
        }
        // ����¾ɲ²�ǳ��ӽ��ﵽ���ȣ���ֹ����
        Number chazhi = subtract(guess, prevGuess);
        if (vectorZero(chazhi.num, k))
            break;
    }
    return guess;
}

//Newton������x�ο���,precisionΪ����������nΪ�������ȣ�kΪ�������
Number SqrtX(Number num, int x = 2, int precision = 100, int n = 100, int k = 10) {
    Number zero(1, { 0 }, 0);
    Number remainder = zero;//�������
    Number xn = zero;
    for (int i = 0; i < x; i++) {
        xn = add(xn, one);
    }
    // ��鸺��
    if (num.PM == 0 && x % 2 == 0) {
        cout << "���󣡸���û��ʵ��ż����ƽ������" << endl;
        return zero;  // ����0
    }
    else if (x == 1)
        return num;
    // �����ֵ���룬����������
    if (num.num == zero.num) {
        //cout << "��ʾ������Ϊ�㣬��ƽ����Ϊ�㡣" << endl;
        return zero;
    }
    // ��ʼ���²�ֵΪ num/2 �� 1��ȡ����num��ֵ
    Number guess = divide(n, num, Number(1, { 2 }, 0), remainder);  // ʹ�ó���������ȡ��ʼ�²�
    Number prevGuess = zero;

    Number X = divide(n, subtract(xn, one), xn, remainder);
    // �߾��ȵ�ƽ�������㣬��������50�Σ�����ֱ������
    for (int i = 0; i < precision; i++) {
        prevGuess = guess;
        // ʹ��ţ�ٵ�����ʽ
        Number guess1 = multiply(X, guess);  // ((k-1)/k)*x(n-1)
        Number guess21 = powerNumber(guess, x - 1); // x(n-1)^(k-1)
        Number guess22 = multiply(xn, guess21);  // k*x(n-1)^(k-1)
        Number guess2 = divide(n, num, guess22, remainder); // a/(k*x(n-1)^(k-1))
        guess = add(guess1, guess2);  // ((k-1)/k)*x(n-1)+a/(k*x(n-1)^(k-1))
        while (true) {
            int j = guess.num.size();
            if (guess.num[j - 1] == 0) {
                guess.num.pop_back();
                guess.Decimal = guess.Decimal - 1;
            }
            else
                break;
        }
        // ����¾ɲ²�ǳ��ӽ��ﵽ���ȣ���ֹ����
        Number chazhi = subtract(guess, prevGuess); 
        if (vectorZero(chazhi.num, k))
            break;
    }
    return guess;
}