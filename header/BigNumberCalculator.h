#include <iostream>
#include <algorithm>

#define DEBUG 0
using namespace std;

bool aBiggerThanB(string a, string b){
    bool ans = true;
    if(a[0] == b[0]){
        if(a[0] == '-'){
            ans = false;        // reverse answer
            a = a.substr(1);
            b = b.substr(1);
        }
    }else{
        if(a[0] == '-'){    // a negative b positive
            return false;
        }
        if(b[0] == '-'){    // a pos b neg
            return true;
        }
    }
    if(a.size()!=b.size()){
        if(a.size() > b.size()) return ans;
        return !ans;
    }
    for(int i=0; i<a.size(); i++){
        if(a[i]==b[i]) continue;
        if((int)a[i]<(int)b[i]) return !ans;
        return ans;
    }
    return ans;
}

string intToString(long long num){
    string str= ""; bool negSign = (num < 0);
    if(num < 0) num = -num ;
    if(num==0) return "0";
    while(num){
        str =  (char)((num%10) + 48) + str;
        num = num/10;
    }
    if(negSign) str = "-" + str;
    return str;
}

// str1 - str2
string _subtract(string str1, string str2){
    if(DEBUG) cout << "To subtract " << str1 << "," << str2 << endl;
    bool resNeg = false;
    if(str1.length() < str2.length()){  // if str1 is less than str2 in length then just swap and put a minus sign at the end
        swap(str1, str2);
        resNeg = true;
    }else if(str1.length() == str2.length() && str1>str2){
        swap(str1, str2);
        resNeg = true;
    }
    if(DEBUG) cout << "To subtract with sign " << str1 << "," << str2 << endl;
    int maxi = max(str1.length(), str2.length());
    int mini = min(str1.length(), str2.length());
    int carry = 0, diff;
    int num1, num2;
    int i=0;
    string res = "";
    while(str2[i]=='0' && str1[i]=='0' && i<mini){
        res = res + "0";
        i++;
    }
    while(str2[i]=='0' && i<mini){
        res = res + str1[i];
        i++;
    }
    for(; i<maxi; i++){
        num1 = 0; num2 = 0;
        if(i<str1.length()) num1 = (int)str1[i] - 48;
        if(i<str2.length()) num2 = (int)str2[i] - 48;
        num1 = num1 + carry;
        carry = 0;
        if(num1 < num2) {
            num1 = 10 + num1;
            carry = -1;
        }
        diff = num1 - num2;
        res = res + (char)(diff + 48);
        if(DEBUG) cout << "res = " << res << ", carry" << carry << endl;
    }
    reverse(res.begin(), res.end());
    while(res.length() > 0 && res[0]=='0') res = res.substr(1);
    if(res == "") return "0";
    if(resNeg){
        res = "-" + res;
    }
    return res;
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
    bool negSign = false;
    if(str1[0]=='-' && str2[0]=='-' ){
        str1 = str1.substr(1);
        str2 = str2.substr(1);
        negSign = false;
    }else if(str1[0]=='-'){
        str1 = str1.substr(1);
        negSign = true;
    }else if(str2[0]=='-'){
        str2 = str2.substr(1);
        negSign = true;
    }
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
    while(res.length() > 0 && res[0]=='0') res = res.substr(1);
    if(res == "") return "0";
    if(negSign) res = "-" + res;
    return res;
}

string add(string str1, string str2){
    string res = "";
    if(str1[0]!='-' && str2[0]!='-' ){
        reverse(str1.begin(), str1.end());
        reverse(str2.begin(), str2.end());
        res = _add(str1, str2);
        reverse(res.begin(), res.end());
    }else if(str1[0]=='-' && str2[0]=='-' ){
        str1 = str1.substr(1);
        str2 = str2.substr(1);
        reverse(str1.begin(), str1.end());
        reverse(str2.begin(), str2.end());
        res = _add(str1, str2);
        reverse(res.begin(), res.end());
        res = "-" + res;
    }else if(str1[0]=='-'){
        str1 = str1.substr(1);
        reverse(str1.begin(), str1.end());
        reverse(str2.begin(), str2.end());
        res = _subtract(str2, str1);
    }else if(str2[0]=='-'){
        str2 = str2.substr(1);
        reverse(str1.begin(), str1.end());
        reverse(str2.begin(), str2.end());
        res = _subtract(str1, str2);
    }
    return res;
}

string subtract(string str1, string str2){
    if(str2[0]=='-')
        str2 = str2.substr(1);
    else
        str2 = "-" + str2;
    return add(str1, str2);
}

string fact(long long num){
    if(num<0){
        if(DEBUG) cout << "Invalid number for factorial: " << num << endl;
        return "";
    }
    long long n = 1;
    string fact = "1";
    for(; n<=num; n++) fact = multiply(intToString(n), fact);
    return fact;
}
