#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

stringstream s;
vector <long long int> num;
vector <char> op;

int brackets(int sizenum, int sizeop) {
    string tmp;
    s >> tmp;
    while (tmp[0] != ')') {

        s >> tmp;
    }
    return 5;
}

int main(){
    int k = 0, n = 0, inter, si;
    string tmp, tmpString;
    char c;
    bool ch = true;
    op.clear();
    num.clear();
    getline(cin, tmpString);
    tmpString += "  )";
    s << tmpString;



    while (s >> tmp) {
        if (ch){
            if (tmp[0] == '(')
                k = brackets(num.size(), op.size());
            else {
                for (int i = 0; i < tmp.length(); i++){
                    if (tmp[i] < '0' || tmp[i] > '9') {
                        cout << "Wrong data!";
                        return 0;
                    }
                    k = k*10 + (int)(tmp[i] - '0');
                }
            }
            num.push_back(k);
            k = 0;
            ch = false;
        }
        else {
            if (!(tmp[0] == '+' || tmp[0] == '-' || tmp[0] == '*' || tmp[0] == '/' || tmp[0] == '%'))
                return 0;
            op.push_back(tmp[0]);
            ch = true;
        }
    }
    vector <long long int>::iterator itn = num.begin();
    vector <char>::iterator it = op.begin();
    while (it != op.end()){
        if (*it == '*' || *it == '/' || *it == '%'){
            if (*it == '*') inter = *itn * *(itn + 1);
            if (*it == '/') {
                if (*(itn + 1) != 0)
                    inter = *itn / *(itn + 1);
                else {
                    cout << "Division by zero!";
                    return 0;
                }
            }
            if (*it == '%') inter = *itn % *(itn + 1);
            num.erase(itn, itn + 2);
            op.erase(it);
            num.insert(itn, inter);
        }
        else {
            itn++;
            it++;
        }
    }
    itn = num.begin();
    it = op.begin();
    si = num.size() - 1;
    for (int i = 0; i < si; i++) {
        if (*it == '+') inter = *itn + *(itn + 1);
        if (*it == '-') inter = *itn - *(itn + 1);
        num.erase(itn, itn + 2);
        op.erase(it);
        num.insert(itn, inter);
    }
    cout << *itn;
	return 0;
}

