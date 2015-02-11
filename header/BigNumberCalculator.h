#include <iostream>
#include <algorithm>

using namespace std;

string intToString(long long num){
    string str= "";
    while(num){
        str =  (char)((num%10) + 48) + str;
        num = num/10;
    }
    return str;
}
string _add(string str1, string str2){
    int maxi = max(str1.length(), str2.length());
    int mini = min(str1.length(), str2.length());
    int carry = 0, sum;
    int num1, num2;
    int i=0;
    string res = "";
    while((str1[i]=='0' || str2[i]=='0') && i<mini){
        if(str1[i]=='0') res = res + str2[i];
        else res = res + str1[i];
        i++;
    }
    for(; i<maxi; i++){
        num1 = 0; num2 = 0;
        if(i<str1.length()) num1 = (int)str1[i] - 48;
        if(i<str2.length()) num2 = (int)str2[i] - 48;
        sum = num1 + num2 + carry;
        carry  = sum/10;
        res = res + (char)(sum%10 + 48);
    }
    if(carry>0)res = res + (char)(carry + 48);
    return res;
}

int multiplyChars(char a, char b){
    return (((int)a - 48)*((int)b - 48));
}

string multiply(string str1, string str2){
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());
    int maxi = str1.length();
    int maxj = str2.length();
    int j;
    int carry=0; int num;
    string res = "", addStr="", zeroStr ="";
    for(int i=0; i<maxi; i++){
        carry=0;
        for(j =0; j< maxj; j++){
            num = carry + multiplyChars(str1[i], str2[j]);
            addStr = addStr + (char)(num%10 + 48);
            carry = num/10;
        }
        if(carry>0)addStr = addStr + (char)(carry + 48);
        res = _add(addStr, res);
        zeroStr = zeroStr + "0";
        addStr = zeroStr;
    }
    reverse(res.begin(), res.end());
    return res;
}

string add(string str1, string str2){
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());
    string res = _add(str1, str2);
    reverse(res.begin(), res.end());
    return res;
}

string fact(long long num){
    if(num<0){
        cout << "Invalid number for factorial: " << num << endl;
        return "";
    }
    long long n = 1;
    string fact = "1";
    for(; n<=num; n++) fact = multiply(intToString(n), fact);
    return fact;
}
