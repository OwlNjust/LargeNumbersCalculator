//提交日期2024年4月21日
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <ctype.h>
using namespace std;

struct Number{
    int PM;//正负标号
    vector<int> num;//数体
    int Decimal;//小数位数
    //pm为正负，1为正，0为负；n为大数；decimal整数小数位数
    Number(int pm = 1, vector<int> n = { 0 }, long long int decimal = 0) {
        num = n;
        PM = pm;
        Decimal = decimal;//整数小数位数为零
    }
};


vector<int> one1 = { 1 };
Number one(1, one1, 0);//大数1
vector<int> one0 = { 01 };
Number one01(1, one0, 1);//大数0.1

//大数的接收，包括正负，数体，小数点位置的读取
Number ReceiveLargeNumbers(const char* name) {
    Number receive;
    vector<int> n;
    char input;

    cout << "请输入" << name << "，以回车结束：" << endl;
    cin.clear(); // 清除任何错误状态
    //检查输入流中的下一个字符是否是换行符 \n 或回车符 \r
    while (cin.peek() == '\n' || cin.peek() == '\r') {
        //从输入流中忽略一个字符
        cin.ignore();
    }

    bool decimal_found = false;
    while (cin.get(input) && input != '\n') {
        //接收正负信息
        if (input == '+' || input == '-') {
            receive.PM = (input == '+') ? 1 : 0;
            continue;
        }
        //记录数体
        if (isdigit(input)) {
            //在向量尾部存入
            n.push_back(input - '0');
            if (decimal_found) {
                receive.Decimal++;
            }
        }
        //发现小数点后开始记录小数位数
        else if (input == '.' && !decimal_found) {
            decimal_found = true; // 确保小数点只处理一次
        }
    }

    receive.num = n;
    return receive;
}

//完整的大数打印，包括正负，小数点
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

//只打印数体部分
void PrintNum(Number number) {
    for (int digit : number.num) {
        cout << digit;
    }
    cout << endl;
}

//将10的n次方(n>=0)转换为向量
vector<int> powerOfTen(int n) {
    vector<int> result = { 1 };
    if (n <= 0)
        return result;
    for (int i = 0; i < n; i++) {
        result.push_back(0);
    }
    return result;
}

//将一个大的正整数按正序转换为向量
vector<int> integerToVector(long long n) {
    vector<int> result;

    // 将整数各位存储到向量中
    while (n > 0) {
        result.insert(result.begin(), n % 10); // 插入到首位
        n /= 10;
    }
    // 若为0，则只存储一个0
    if (result.size() == 1 && result[0] == 1) {
        result.push_back(0);
    }

    return result;
}

// 比较两个大整数的大小，大于时返回1，等于时返回0，小于时返回-1
int compareLargeNumbers(vector<int> num1, vector<int> num2) {
    //忽略忽略前导零，提高性能
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

//大数加法
vector<int> addLargeNumbers(Number num1, Number num2) {
    vector<int> result;

    // 去除前导零，同时避免全零数变为空
    while (!num1.num.empty() && num1.num.front() == 0) {
        num1.num.erase(num1.num.begin());
    }
    //确保存储大数数字的向量，至少包含一个元素
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
        //直接放入处理后的数，避免重复改变元素位置，提高性能
        result.push_back(sum % 10);
        carry = sum / 10;
    }
    // 反转结果以获得正确的顺序
    reverse(result.begin(), result.end());
    return result;
}


//大数减法，num1减num2，注意保证输入的num1始终num2
vector<int> subtractLargeNumbers(Number num1, Number num2) {
    vector<int> result;

    // 去除前导零，同时避免全零数变为空
    while (!num1.num.empty() && num1.num.front() == 0) {
        num1.num.erase(num1.num.begin());
    }
    //确保存储大数数字的向量，至少包含一个元素
    if (num1.num.empty()) num1.num.push_back(0);
    while (!num2.num.empty() && num2.num.front() == 0) {
        num2.num.erase(num2.num.begin());
    }
    if (num2.num.empty()) num2.num.push_back(0);

    //减少不必要的循环
    if (num1.num == num2.num) {
        result = { 0 };
        return result;
    }
    //得到最后一位的位置
    int i = num1.num.size() - 1;
    int j = num2.num.size() - 1;
    int borrow = 0;

    while (i >= 0 || j >= 0) {
        //从最后一位开始减起
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
        //直接放入处理后的数，避免重复改变元素位置，提高性能
        result.push_back(digit);
        i--;
    }
    // 反转结果以获得正确的顺序
    reverse(result.begin(), result.end());
    // 移除结果中的高位零
    while (!result.empty() && result.front() == 0) {
        result.erase(result.begin());
    }
    return result;
}

//大数乘法（累加法）
vector<int> multiplyLargeNumbers(Number num1, Number num2) {

    // 去除前导零，同时避免全零数变为空
    while (!num1.num.empty() && num1.num.front() == 0) {
        num1.num.erase(num1.num.begin());
    }
    //确保存储大数数字的向量，至少包含一个元素
    if (num1.num.empty()) num1.num.push_back(0);
    while (!num2.num.empty() && num2.num.front() == 0) {
        num2.num.erase(num2.num.begin());
    }
    if (num2.num.empty()) num2.num.push_back(0);

    //为方便对特定一位的修改，需要将整个结果向量赋零
    vector<int> result(num1.num.size() + num2.num.size(), 0);
    //两层循环实现运算，事实上通过sum在产生乘数的过程中将累加过程也实现了，避免了调用整数加法函数，也避免了存储加数
    for (int i = num1.num.size() - 1; i >= 0; --i) {
        for (int j = num2.num.size() - 1; j >= 0; --j) {
            int product = num1.num[i] * num2.num[j];
            int pos1 = i + j, pos2 = i + j + 1;
            int sum = product + result[pos2];

            result[pos1] += sum / 10;
            result[pos2] = sum % 10;
        }
    }

    // 去除结果中的高位零
    while (result.size() > 1 && result[0] == 0) {
        result.erase(result.begin());
    }

    return result;
}

//大数除法，num1除于num2，余remainder，输出商
vector<int> divideLargeNumbers(Number num1, Number num2, vector<int>& remainder) {
    vector<int> result;
    Number dividend = num1;//被除数
    Number divisor = num2;//除数

    // 去除前导零，同时避免全零数变为空
    while (!num1.num.empty() && num1.num.front() == 0) {
        num1.num.erase(num1.num.begin());
    }
    //确保存储大数数字的向量，至少包含一个元素
    if (num1.num.empty()) num1.num.push_back(0);
    while (!num2.num.empty() && num2.num.front() == 0) {
        num2.num.erase(num2.num.begin());
    }
    if (num2.num.empty()) num2.num.push_back(0);

    Number quotient(1, { 0 }, 0);//商
    Number p;//临时存储数据
    Number zero;
    //vector<int> remainder是余数

    // 特殊情况处理 
    if (num2.num.size() == 1 && num2.num[0] == 0) {
        cout << "Error: 除数不能为0!" << endl;
        return result = { 0 };
    }

    //if中每一层的dividend.num, divisor.num都可能改变，故必须重新比较大小
    if (compareLargeNumbers(dividend.num, divisor.num) == 1) {
        //需要添加的0的数量
        int n = dividend.num.size() - divisor.num.size();
        for (int i = 0; i < n; i++) {
            //在divisor末尾添加n个0
            divisor.num.insert(divisor.num.end(), 0);
        }
        //对更改后的num1，num2重新比较大小，决定下一步
        if (compareLargeNumbers(dividend.num, divisor.num) == -1) {
            // 删除向量的末尾元素
            divisor.num.pop_back();
            n--;
        }
        while (n >= 0) {
            Number quo(1, { 0 }, 0);//储存每个位的商
            if (dividend.num == zero.num)break;
            while (compareLargeNumbers(dividend.num, divisor.num) == 1
                || compareLargeNumbers(dividend.num, divisor.num) == 0) {
                dividend.num = subtractLargeNumbers(dividend, divisor);
                quo.num = addLargeNumbers(quo, one);
            }
            p.num = powerOfTen(n);
            quo.num = multiplyLargeNumbers(quo, p);
            // 删除向量的末尾元素
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

//比较两个大数，num1比num2，大于时返回1，等于时返回0，小于时返回-1
int compareNumber(Number& num1, Number& num2) {
    // 临时副本，避免修改原始数据
    Number temp1 = num1;
    Number temp2 = num2;
    Number p(1, { 0 }, 0);//临时存储数据

    // 比较正负标号
    if (temp1.PM != temp2.PM) {
        return temp1.PM > temp2.PM ? 1 : -1;  // 正数大于负数
    }

    // 处理都是正数或都是负数的情况
    int sign = temp1.PM == 1 ? 1 : -1;

    // 对齐位数
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

    // 整数位对齐后，比较数字大小
    int result = compareLargeNumbers(temp1.num, temp2.num);
    if (result == 0) {
        return 0;  // 数字相同
    }
    else if (result == -1) {
        return -1 * sign;  // 第一个数小
    }
    else if (result == 1) {
        return 1 * sign;  // 第一个数大
    }

    return 0; // 默认返回相等，理论上不会到达这里
}

//加法num1+num2
Number add(Number num1, Number num2) {
    Number result;
    Number p(1, { 0 }, 0);//临时存储数据
    Number zero(1, { 0 }, 0);

    int n1 = num1.Decimal;
    int n2 = num2.Decimal;

    //对齐位数
    if (n1 > n2) {
        int nn = n1 - n2;//小数位数差值
        p.num = powerOfTen(nn);
        num2.num = multiplyLargeNumbers(num2, p);
        num2.Decimal = num2.Decimal + nn;
    }
    if (n1 < n2) {
        int nn = n2 - n1;//小数位数差值
        p.num = powerOfTen(nn);
        num1.num = multiplyLargeNumbers(num1, p);
        num1.Decimal = num1.Decimal + nn;
    }

    //实现加法
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
    //对于小于一的数，为了打印时不出错，需要在数体前加上合适数量的0
    int k = result.Decimal - result.num.size() + 1;
    for (int i = 0; i < k; i++)
        result.num.insert(result.num.begin(), 0);

    return result;
}

//减法num1-num2
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

//乘法num1*num2
Number multiply(Number num1, Number num2) {
    Number result;

    result.num = multiplyLargeNumbers(num1, num2);
    result.Decimal = num1.Decimal + num2.Decimal;

    if (num1.PM == num2.PM)
        result.PM = 1;
    else if (num1.PM != num2.PM)
        result.PM = 0;
    //对于小于一的数，为了打印时不出错，需要在数体前加上合适数量的0
    int k = result.Decimal - result.num.size() + 1;
    for (int i = 0; i < k; i++)
        result.num.insert(result.num.begin(), 0);

    return result;
}

//除法num1/num2.n为结果想精确到的小数位数
Number divide(int n, Number num1, Number num2, Number& remainder) {
    Number result;
    Number quotient(1, { 0 }, 0);//商
    Number p(1, { 0 }, 0);//临时存储数据
    remainder = p;//清空余数

    int n1 = num1.Decimal;
    int n2 = num2.Decimal;
    //对齐位数
    if (n1 > n2) {
        int nn = n1 - n2;//小数位数差值
        p.num = powerOfTen(nn);
        num2.num = multiplyLargeNumbers(num2, p);
        num2.Decimal = num2.Decimal + nn;
    }
    if (n1 < n2) {
        int nn = n2 - n1;//小数位数差值
        p.num = powerOfTen(nn);
        num1.num = multiplyLargeNumbers(num1, p);
        num1.Decimal = num1.Decimal + nn;
    }

    //实现除法
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
    //结果的正负
    remainder.PM = num1.PM;
    if (num1.PM == num2.PM)
        quotient.PM = 1;
    else
        quotient.PM = 0;

    result = quotient;
    //对于小于一的数，为了打印时不出错，需要在数体前加上合适数量的0
    int k = result.Decimal - result.num.size() + 1;
    for (int i = 0; i < k; i++)
        result.num.insert(result.num.begin(), 0);

    return result;
}

// 大数乘方运算，计算 base 的 exp 次方
Number powerNumber(Number base, int exp) {
    if (exp < 0) {
        cout << "错误：不支持负数指数的整数幂运算。" << endl;
        return Number(1, { 1 }, 0);  // 返回默认构造的Number对象
    }
    if (exp == 0 || (base.num.size() == 1 && base.num[0] == 1)) {
        return Number(1, { 1 }, 0);  // 任何数的0次幂是1，1的任何次幂是1
    }
    if (base.num.size() == 1 && base.num[0] == 0) {
        if (exp == 0) {
            return Number(1, { 1 }, 0);  // 0的0次幂定义为1
        }
        return Number(1, { 0 }, 0);  // 0的任何正数次幂是0
    }

    Number result(1, { 1 }, 0);  // 初始化为 1
    Number current_base = base;  // 当前底数为 base

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

        //乘方核心语句
        if (exp % 2 == 1) {  // 如果指数为奇数
            result = multiply(result, current_base);  // 结果乘以当前底数
        }
        current_base = multiply(current_base, current_base);  // 底数平方
        exp /= 2;  // 指数除以 2

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

//判断一个向量是否从第一个元素到第k+1个元素都为零
bool vectorZero(const std::vector<int>& vec, int k) {
    if (vec.size() < k + 1) return false; // 确保向量至少有 k+1 个元素
    for (int i = 0; i <= k; ++i) {
        if (vec[i] != 0) return false;
    }
    return true;
}

//Newton法开方,precision为迭代次数，n为除法精度,k为结果精度
Number mySqrt(Number num, int precision = 100, int n = 10, int k = 10) {
    Number zero(1, { 0 }, 0);
    Number remainder = zero;//存放余数 
    // 检查负数
    if (num.PM == 0) {
        cout << "错误！负数没有实数平方根。" << endl;
        return zero;  // 返回0
    }
    // 检查零值输入，避免除零错误
    if (num.num == zero.num) {
        //cout << "提示：输入为零，其平方根为零。" << endl;
        return zero;
    }
    // 初始化猜测值为 num/2 或 1，取决于num的值
    Number guess = divide(n, num, Number(1, { 2 }, 0), remainder);  // 使用除法函数获取初始猜测
    Number prevGuess = zero;

    // 高精度的平方根计算，迭代至少10次，或者直到收敛
    for (int i = 0; i < precision; i++) {
        prevGuess = guess;

        // 使用牛顿迭代公式
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
        // 如果新旧猜测非常接近达到精度，终止迭代
        Number chazhi = subtract(guess, prevGuess);
        if (vectorZero(chazhi.num, k))
            break;
    }
    return guess;
}

//Newton法任意x次开方,precision为迭代次数，n为除法精度，k为结果精度
Number SqrtX(Number num, int x = 2, int precision = 100, int n = 100, int k = 10) {
    Number zero(1, { 0 }, 0);
    Number remainder = zero;//存放余数
    Number xn = zero;
    for (int i = 0; i < x; i++) {
        xn = add(xn, one);
    }
    // 检查负数
    if (num.PM == 0 && x % 2 == 0) {
        cout << "错误！负数没有实数偶数次平方根。" << endl;
        return zero;  // 返回0
    }
    else if (x == 1)
        return num;
    // 检查零值输入，避免除零错误
    if (num.num == zero.num) {
        //cout << "提示：输入为零，其平方根为零。" << endl;
        return zero;
    }
    // 初始化猜测值为 num/2 或 1，取决于num的值
    Number guess = divide(n, num, Number(1, { 2 }, 0), remainder);  // 使用除法函数获取初始猜测
    Number prevGuess = zero;

    Number X = divide(n, subtract(xn, one), xn, remainder);
    // 高精度的平方根计算，迭代至少50次，或者直到收敛
    for (int i = 0; i < precision; i++) {
        prevGuess = guess;
        // 使用牛顿迭代公式
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
        // 如果新旧猜测非常接近达到精度，终止迭代
        Number chazhi = subtract(guess, prevGuess); 
        if (vectorZero(chazhi.num, k))
            break;
    }
    return guess;
}