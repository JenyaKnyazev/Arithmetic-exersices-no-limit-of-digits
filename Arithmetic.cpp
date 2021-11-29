#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h>
using namespace std;
vector<int> str_to_vec(string &s) {
    vector<int>vec;
    int i;
    i = 0;
    label:
    if (s[i] >= 'A' && s[i] <= 'F')
        vec.push_back(s[i] - 'A' + 10);
    else if (s[i] >= 'a' && s[i] <= 'f')
        vec.push_back(s[i] - 'a' + 10);
    else
        vec.push_back(s[i] - '0');
    i++;
    if (i < s.length())
        goto label;
    return vec;
}
string vec_to_str(vector<int> vec) {
    string s = "";
    int i=0;
    if (vec.size() == 0)
        return "0";
    label:
    if (vec[i] > 9)
        s += vec[i] + 'A' - 10;
    else
        s += vec[i] + '0';
    i++;
    if (i < vec.size())
        goto label;
    return s;
}
int max(int a, int b) {
    return (a > b) ? a : b;
}
void refresh(vector<int>& vec) {
    int i;
    i = vec.size() - 1;
    label:
    if (i > 0) {
        vec[i - 1] += vec[i] / 10;
        vec[i] %= 10;
    }
    i--;
    if (i > 0)
        goto label;
    vec.insert(vec.begin(), vec[0] / 10);
    vec[1] %= 10;
    label2:
    if (vec[0] == 0 && vec.size() > 1) {
        vec.erase(vec.begin());
        goto label2;
    }
}
void refreshX(vector<int>& vec) {
    int i;
    i = vec.size() - 1;
label:
    if (i > 0) {
        vec[i - 1] += vec[i] / 10;
        vec[i] %= 10;
    }
    i--;
    if (i > 0)
        goto label;
    vec.insert(vec.begin(), vec[0] / 10);
    vec[1] %= 10;
}
vector<int> add(vector<int> a, vector<int> b) {
    vector<int>vec(max(a.size(),b.size())+1,0);
    int i,r;
    i = a.size() - 1;
    r = vec.size() - 1;
    label:
    vec[r] = a[i];
    i--;
    r--;
    if (i >= 0)
        goto label;
    i = b.size() - 1;
    r = vec.size() - 1;
    label2:
    vec[r] += b[i];
    i--;
    r--;
    if (i >= 0)
        goto label2;
    refresh(vec);
    return vec;
}
void refresh2(vector<int>& vec) {
    int i=0;
    label:
    if (i < vec.size() - 1) {
        vec[i]--;
        vec[i + 1] += 10;
    }
    i++;
    if (i < vec.size() - 1)
        goto label;
    refresh(vec);
}
vector<int> sub(vector<int>a, vector<int>b) {
    int i,r;
    i = a.size()-1;
    r = b.size() - 1;
    label:
    a[i] -= b[r];
    i--;
    r--;
    if (i >= 0&&r >= 0)
        goto label;
    refresh2(a);
    return a;
    
}
int is_smaller(vector<int>& a, vector<int>& b) {
    int i;
    lab:
    if (a.size() > 1 && a[0] == 0) {
        a.erase(a.begin());
        goto lab;
    }
    lab2:
    if (b.size() > 1 && b[0] == 0) {
        b.erase(b.begin());
        goto lab2;
    }
    if (a.size() < b.size())
        return 1;
    if (a.size() > b.size())
        return 0;
    i = 0;
    label:
    if (a[i] > b[i])
        return 0;
    if (a[i] < b[i])
        return 1;
    i++;
    if (i < a.size())
        goto label;
    return 0;
}
vector<int> mul(vector<int>a, vector<int>b) {
    vector<int> vec(a.size() + b.size(), 0);
    int i, r,j;
    i = a.size()-1;
    label2:
    r = b.size() - 1;
    label:
    j = vec.size() - 1 - (a.size() - (i + 1) + b.size() - (r + 1) );
    vec[j] += a[i] * b[r];
    r--;
    refreshX(vec);
    if (r >= 0)
        goto label;
    i--;
    if (i >= 0)
        goto label2;
    refresh(vec);
    return vec;

}
vector<vector<int>> div_and_mod(vector<int> a, vector<int>b) {
    vector<vector<int>>vec;
    vector<int>div(1,0);
    vector<int>run;
    int i;
    i = 0;
    label:
    if (i<a.size()&&is_smaller(run, b)) {
        div = mul(div, { 1,0 });
        run.push_back(a[i]);
        i++;
        goto label;
    }
    label2:
    if (is_smaller(run, b) == 0) {
        div = add(div, { 1 });
        run = sub(run, b);
        goto label2;
    }
    label3:
    if (run.size() > 0 && run[0] == 0) {
        run.erase(run.begin());
        goto label3;
    }
    if (i < a.size())
        goto label;
    vec.push_back(div);
    if (run.size() == 0)
        run.push_back(0);
    vec.push_back(run);
    return vec;
}

int equals_(vector<int> a, vector<int> b) {
    if (a.size() != b.size())
        return 0;
    int i=0;
    label:
    if (i<a.size()&&a[i] != b[i])
        return 0;
    i++;
    if (i < a.size())
        goto label;
    return 1;
}
vector<int> dec_to_bin(vector<int>vec) {
    vector<int>bin;
    vector<vector<int>>d_m;
    vector<int>t(1, 0);
    label:
    if (equals_(vec,t)==0) {
        d_m = div_and_mod(vec, { 2 });
        bin.insert(bin.begin(), d_m[1].begin(),d_m[1].end());
        vec = d_m[0];
        goto label;
    }
    return bin;
}
vector<int> bin_to_dec(vector<int>bin) {
    int i;
    vector<int>m(1, 1);
    vector<int>sum(1, 0);
    i = bin.size() - 1;
    label:
    sum = add(sum, mul({ bin[i] }, m));
    m = mul(m, { 2 });
    i--;
    if (i >= 0)
        goto label;
    return sum;
}
vector<int> dec_to_octal(vector<int>vec) {
    vector<int>octal;
    vector<vector<int>>d_m;
    vector<int>t(1, 0);
label:
    if (equals_(vec, t) == 0) {
        d_m = div_and_mod(vec, { 8 });
        octal.insert(octal.begin(), d_m[1].begin(), d_m[1].end());
        vec = d_m[0];
        goto label;
    }
    return octal;
}
vector<int> octal_to_dec(vector<int>vec) {
    int i;
    vector<int>m(1, 1);
    vector<int>sum(1, 0);
    i = vec.size() - 1;
label:
    sum = add(sum, mul({ vec[i] }, m));
    m = mul(m, { 8 });
    i--;
    if (i >= 0)
        goto label;
    return sum;
}
vector<int> dec_to_hex(vector<int>vec) {
    vector<int>hex;
    vector<vector<int>>d_m;
    vector<int>t(1, 0);
    int num=0;
label:
    if (equals_(vec, t) == 0) {
        d_m = div_and_mod(vec, { 1,6 });
        num = d_m[1][0];
        if (d_m[1].size() > 1) {
            num *= 10;
            num += d_m[1][1];
        }
        hex.insert(hex.begin(),num);
        vec = d_m[0];
        goto label;
    }
    return hex;
}
vector<int> hex_to_dec(vector<int>vec) {
    int i;
    vector<int>m(1, 1);
    vector<int>sum(1, 0);
    i = vec.size() - 1;
    vector<int>t;
label:
    t.push_back(vec[i] / 10);
    t.push_back(vec[i] % 10);
    sum = add(sum, mul(t, m));
    m = mul(m, { 1,6 });
    i--;
    t.clear();
    if (i >= 0)
        goto label;
    return sum;
}
vector<int> octal_to_hex(vector<int>vec) {
    return dec_to_hex(octal_to_dec(vec));
}
vector<int> hex_to_octal(vector<int> vec) {
    return dec_to_octal(hex_to_dec(vec));
}
vector<int> generate_dec(int digits) {
    vector<int>vec;
    //srand(time(NULL));
    vec.push_back(rand() % 9 + 1);
    digits--;
label:
    if (digits > 0) {
        digits--;
        vec.push_back(rand() % 10);
        goto label;
    }
    return vec;
}
vector<int> generate_bin(int digits) {
    vector<int>vec;
    vec.push_back(1);
    digits--;
label:
    if (digits > 0) {
        digits--;
        vec.push_back(rand() % 2);
        goto label;
    }
    return vec;
}
vector<int> generate_octal(int digits) {
    vector<int>vec;
    vec.push_back(rand()%7+1);
    digits--;
label:
    if (digits > 0) {
        digits--;
        vec.push_back(rand() % 8);
        goto label;
    }
    return vec;
}
vector<int> generate_hex(int digits) {
    vector<int>vec;
    vec.push_back(rand() % 15 + 1);
    digits--;
label:
    if (digits > 0) {
        digits--;
        vec.push_back(rand() % 16);
        goto label;
    }
    return vec;
}
int again(int c, int w) {
    int n;
    cout << "\nCorrect: " + to_string(c) << endl;
    cout << "Wrong: " + to_string(w) << endl;
    cout << "Total: " + to_string(c + w) << endl;
    cout << "Again 1 back 0\n";
    cin >> n;
    cin.ignore();
    return n;
}
void bin_add(int digits, int ex) {
    int correct ;
    int wrong;
    int tasks ;
    string s;
    label2:
    correct = 0;
    wrong = 0;
    tasks = ex;
    label:
    vector<int>a=generate_bin(digits);
    vector<int>b = generate_bin(digits);
    vector<int>c;
    cout << vec_to_str(a) + " + " + vec_to_str(b) << " = " ;
    getline(cin, s);
    c = str_to_vec(s);
    if (add(bin_to_dec(a), bin_to_dec(b)) == bin_to_dec(c))
        correct++;
    else
        wrong++;
    tasks--;
    if (tasks > 0)
        goto label;
    if (again(correct, wrong))
        goto label2;
}
void bin_sub(int digits, int ex) {
    int correct;
    int wrong;
    int tasks;
    string s;
    label2:
    correct = 0;
    wrong = 0;
    tasks = ex;
    label:
    vector<int>a = generate_bin(digits);
    vector<int>b = generate_bin(digits);
    vector<int>c;
    vector<int>d = add(bin_to_dec(a), bin_to_dec(b));
    cout << vec_to_str(dec_to_bin(d)) << " - " << vec_to_str(b) << " = ";
    getline(cin, s);
    if (str_to_vec(s) == a)
        correct++;
    else
        wrong++;
    tasks--;
    if (tasks > 0)
        goto label;
    if (again(correct, wrong))
        goto label2;
}
void bin_mul(int digits, int ex) {
    int correct;
    int wrong;
    int tasks;
    string s;
    label2:
    correct = 0;
    wrong = 0;
    tasks = ex;
    label:
    vector<int>a = generate_bin(digits);
    vector<int>b = generate_bin(digits);
    vector<int>c;
    cout << vec_to_str(a) << " * " << vec_to_str(b) << " = ";
    getline(cin, s);
    if (mul(bin_to_dec(a), bin_to_dec(b)) == bin_to_dec(str_to_vec(s)))
        correct++;
    else
        wrong++;
    tasks--;
    if (tasks > 0)
        goto label;
    if (again(correct, wrong))
        goto label2;
}
void bin_div(int digits, int ex) {
    int correct;
    int wrong;
    int tasks;
    string s;
    label2:
    correct = 0;
    wrong = 0;
    tasks = ex;
    label:
    vector<int>a = generate_bin(digits);
    vector<int>b = generate_bin(digits);
    vector<int>c;
    cout << vec_to_str(dec_to_bin(mul(bin_to_dec(a), bin_to_dec(b)))) << " / " << vec_to_str(b) << " = ";
    getline(cin, s);
    if (str_to_vec(s) == a)
        correct++;
    else
        wrong++;
    tasks--;
    if (tasks > 0)
        goto label;
    if (again(correct, wrong))
        goto label2;
}
void bin_dec(int digits, int ex) {
    int correct;
    int wrong;
    int tasks;
    string s;
    label2:
    correct = 0;
    wrong = 0;
    tasks = ex;
    label:
    vector<int>a = generate_bin(digits);
    vector<int>b;
    cout << vec_to_str(a) << " = ";
    getline(cin, s);
    b = str_to_vec(s);
    if (b == bin_to_dec(a))
        correct++;
    else
        wrong++;
    tasks--;
    if (tasks > 0)
        goto label;
    if (again(correct, wrong))
        goto label2;
}
void bin_menu(int digits,int ex) {
    int n;
label:
    cout << "\nBinary" << endl;
    cout << "1 addition" << endl;
    cout << "2 substraction" << endl;
    cout << "3 multiplication" << endl;
    cout << "4 division" << endl;
    cout << "5 binary to decimal" << endl;
    cout << "other back" << endl;
    cin >> n;
    cin.ignore();
    switch (n) {
        case 1:
            bin_add(digits, ex);
            break;
        case 2:
            bin_sub(digits, ex);
            break;
        case 3:
            bin_mul(digits, ex);
            break;
        case 4:
            bin_div(digits, ex);
            break;
        case 5:
            bin_dec(digits, ex);
            break;
    }
    if (n >= 1 && n <= 5)
        goto label;
}
void octal_add(int digits, int ex) {
    int correct;
    int wrong;
    int tasks;
    string s;
    label2:
    correct = 0;
    wrong = 0;
    tasks = ex;
    label:
    vector<int>a=generate_octal(digits);
    vector<int>b=generate_octal(digits);
    cout << vec_to_str(a) + " + " << vec_to_str(b) <<" = ";
    getline(cin, s);
    if (dec_to_octal(add(octal_to_dec(a), octal_to_dec(b))) == str_to_vec(s))
        correct++;
    else
        wrong++;
    tasks--;
    if (tasks > 0)
        goto label;
    if (again(correct, wrong))
        goto label2;
}
void octal_sub(int digits, int ex) {
    int correct;
    int wrong;
    int tasks;
    string s;
    label2:
    correct = 0;
    wrong = 0;
    tasks = ex;
    label:
    vector<int>a = generate_octal(digits);
    vector<int>b = generate_octal(digits);
    vector<int>c= dec_to_octal(add(octal_to_dec(a), octal_to_dec(b)));
    cout << vec_to_str(c) << " - " << vec_to_str(b) << " = ";
    getline(cin, s);
    if (str_to_vec(s) == a)
        correct++;
    else
        wrong++;
    tasks--;
    if (tasks > 0)
        goto label;
    if (again(correct, wrong))
        goto label2;
}
void octal_mul(int digits, int ex) {
    int correct;
    int wrong;
    int tasks;
    string s;
    label2:
    correct = 0;
    wrong = 0;
    tasks = ex;
    label:
    vector<int>a = generate_octal(digits);
    vector<int>b = generate_octal(digits);
    cout << vec_to_str(a) << " * " << vec_to_str(b) << " = ";
    getline(cin, s);
    if (str_to_vec(s) == dec_to_octal(mul(octal_to_dec(a), octal_to_dec(b))))
        correct++;
    else
        wrong++;
    tasks--;
    if (tasks > 0)
        goto label;
    if (again(correct, wrong))
        goto label2;
}
void octal_div(int digits, int ex) {
    int correct;
    int wrong;
    int tasks;
    string s;
    label2:
    correct = 0;
    wrong = 0;
    tasks = ex;
    label:
    vector<int>a = generate_octal(digits);
    vector<int>b = generate_octal(digits);
    vector<int>c = dec_to_octal(mul(octal_to_dec(a), octal_to_dec(b)));
    cout << vec_to_str(c) << " / " << vec_to_str(b)<<" = ";
    getline(cin, s);
    if (str_to_vec(s) == a)
        correct++;
    else
        wrong++;
    tasks--;
    if (tasks > 0)
        goto label;
    if (again(correct, wrong))
        goto label2;
}
void octal_dec(int digits,int ex) {
    int correct;
    int wrong;
    int tasks;
    string s;
    label2:
    correct = 0;
    wrong = 0;
    tasks = ex;
    label:
    vector<int>a = generate_octal(digits);
    cout << vec_to_str(a) << " = ";
    getline(cin, s);
    if (str_to_vec(s) == octal_to_dec(a))
        correct++;
    else
        wrong++;
    tasks--;
    if (tasks > 0)
        goto label;
    if (again(correct, wrong))
        goto label2;
}
void octal_hex(int digits, int ex) {
    int correct;
    int wrong;
    int tasks;
    string s;
    label2:
    correct = 0;
    wrong = 0;
    tasks = ex;
    label:
    vector<int>a = generate_octal(digits);
    cout << vec_to_str(a) << " = ";
    getline(cin, s);
    if (str_to_vec(s) == octal_to_hex(a))
        correct++;
    else
        wrong++;
    tasks--;
    if (tasks > 0)
        goto label;
    if (again(correct, wrong))
        goto label2;
}
void octal_menu(int digits, int ex) {
    int n;
label:
    cout << "\nOctal" << endl;
    cout << "1 addition" << endl;
    cout << "2 substraction" << endl;
    cout << "3 multiplication" << endl;
    cout << "4 division" << endl;
    cout << "5 octal to decimal" << endl;
    cout << "6 octal to hexadecimal" << endl;
    cout << "other back" << endl;
    cin >> n;
    cin.ignore();
    switch (n) {
    case 1:
        octal_add(digits, ex);
        break;
    case 2:
        octal_sub(digits, ex);
        break;
    case 3:
        octal_mul(digits, ex);
        break;
    case 4:
        octal_div(digits, ex);
        break;
    case 5:
        octal_dec(digits, ex);
        break;
    case 6:
        octal_hex(digits, ex);
        break;
    }
    if (n >= 1 && n <= 6)
        goto label;
}
void dec_add(int digits, int ex) {
    int correct;
    int wrong;
    int tasks;
    string s;
label2:
    correct = 0;
    wrong = 0;
    tasks = ex;
label:
    vector<int>a = generate_dec(digits);
    vector<int>b = generate_dec(digits);
    cout << vec_to_str(a) << " + " << vec_to_str(b) << " = ";
    getline(cin, s);
    if (str_to_vec(s) == add(a, b))
        correct++;
    else
        wrong++;
    tasks--;
    if (tasks > 0)
        goto label;
    if (again(correct, wrong))
        goto label2;
}
void dec_sub(int digits, int ex) {
    int correct;
    int wrong;
    int tasks;
    string s;
label2:
    correct = 0;
    wrong = 0;
    tasks = ex;
label:
    vector<int>a = generate_dec(digits);
    vector<int>b = generate_dec(digits);
    cout << vec_to_str(add(a,b)) << " - " << vec_to_str(b) << " = ";
    getline(cin, s);
    if (str_to_vec(s) == a)
        correct++;
    else
        wrong++;
    tasks--;
    if (tasks > 0)
        goto label;
    if (again(correct, wrong))
        goto label2;
}
void dec_mul(int digits, int ex) {
    int correct;
    int wrong;
    int tasks;
    string s;
label2:
    correct = 0;
    wrong = 0;
    tasks = ex;
label:
    vector<int>a = generate_dec(digits);
    vector<int>b = generate_dec(digits);
    cout << vec_to_str(a) << " * " << vec_to_str(b) << " = ";
    getline(cin, s);
    if (str_to_vec(s) == mul(a, b))
        correct++;
    else
        wrong++;
    tasks--;
    if (tasks > 0)
        goto label;
    if (again(correct, wrong))
        goto label2;
}
void dec_div(int digits, int ex) {
    int correct;
    int wrong;
    int tasks;
    string s;
label2:
    correct = 0;
    wrong = 0;
    tasks = ex;
label:
    vector<int>a = generate_dec(digits);
    vector<int>b = generate_dec(digits);
    cout << vec_to_str(mul(a,b)) << " / " << vec_to_str(b) << " = ";
    getline(cin, s);
    if (str_to_vec(s) == a)
        correct++;
    else
        wrong++;
    tasks--;
    if (tasks > 0)
        goto label;
    if (again(correct, wrong))
        goto label2;
}
void dec_bin(int digits, int ex) {
    int correct;
    int wrong;
    int tasks;
    string s;
label2:
    correct = 0;
    wrong = 0;
    tasks = ex;
label:
    vector<int>a = generate_dec(digits);
    cout << vec_to_str(a) << " = ";
    getline(cin, s);
    if (str_to_vec(s) == dec_to_bin(a))
        correct++;
    else
        wrong++;
    tasks--;
    if (tasks > 0)
        goto label;
    if (again(correct, wrong))
        goto label2;
}
void dec_octal(int digits, int ex) {
    int correct;
    int wrong;
    int tasks;
    string s;
label2:
    correct = 0;
    wrong = 0;
    tasks = ex;
label:
    vector<int>a = generate_dec(digits);
    cout << vec_to_str(a) << " = ";
    getline(cin, s);
    if (str_to_vec(s) == dec_to_octal(a))
        correct++;
    else
        wrong++;
    tasks--;
    if (tasks > 0)
        goto label;
    if (again(correct, wrong))
        goto label2;
}
void dec_hex(int digits, int ex) {
    int correct;
    int wrong;
    int tasks;
    string s;
label2:
    correct = 0;
    wrong = 0;
    tasks = ex;
label:
    vector<int>a = generate_dec(digits);
    cout << vec_to_str(a) << " = ";
    getline(cin, s);
    if (str_to_vec(s) == dec_to_hex(a))
        correct++;
    else
        wrong++;
    tasks--;
    if (tasks > 0)
        goto label;
    if (again(correct, wrong))
        goto label2;
}
void dec_menu(int digits, int ex) {
    int n;
label:
    cout << "\nDecimal" << endl;
    cout << "1 addition" << endl;
    cout << "2 substraction" << endl;
    cout << "3 multiplication" << endl;
    cout << "4 division" << endl;
    cout << "5 decimal to binary" << endl;
    cout << "6 decimal to octal" << endl;
    cout << "7 decimal to hexadecimal" << endl;
    cout << "other back" << endl;
    cin >> n;
    cin.ignore();
    switch (n) {
    case 1:
        dec_add(digits, ex);
        break;
    case 2:
        dec_sub(digits, ex);
        break;
    case 3:
        dec_mul(digits, ex);
        break;
    case 4:
        dec_div(digits, ex);
        break;
    case 5:
        dec_bin(digits, ex);
        break;
    case 6:
        dec_octal(digits, ex);
        break;
    case 7:
        dec_hex(digits, ex);
        break;
    }
    if (n >= 1 && n <= 7)
        goto label;
}
void hex_add(int digits, int ex) {
    int correct;
    int wrong;
    int tasks;
    string s;
label2:
    correct = 0;
    wrong = 0;
    tasks = ex;
label:
    vector<int>a = generate_hex(digits);
    vector<int>b = generate_hex(digits);
    cout << vec_to_str(a) << " + " << vec_to_str(b) << " = ";
    getline(cin, s);
    if (str_to_vec(s) == dec_to_hex(add(hex_to_dec(a), hex_to_dec(b))))
        correct++;
    else
        wrong++;
    tasks--;
    if (tasks > 0)
        goto label;
    if (again(correct, wrong))
        goto label2;
}
void hex_sub(int digits, int ex) {
    int correct;
    int wrong;
    int tasks;
    string s;
label2:
    correct = 0;
    wrong = 0;
    tasks = ex;
label:
    vector<int>a = generate_hex(digits);
    vector<int>b = generate_hex(digits);
    cout << vec_to_str(dec_to_hex(add(hex_to_dec(a), hex_to_dec(b)))) << " - " << vec_to_str(b)<<" = ";
    getline(cin, s);
    if (str_to_vec(s) == a)
        correct++;
    else
        wrong++;
    tasks--;
    if (tasks > 0)
        goto label;
    if (again(correct, wrong))
        goto label2;
}
void hex_mul(int digits, int ex) {
    int correct;
    int wrong;
    int tasks;
    string s;
label2:
    correct = 0;
    wrong = 0;
    tasks = ex;
label:
    vector<int>a = generate_hex(digits);
    vector<int>b = generate_hex(digits);
    cout << vec_to_str(a) << " * " << vec_to_str(b) << " = ";
    getline(cin, s);
    if (str_to_vec(s) == dec_to_hex(mul(hex_to_dec(a), hex_to_dec(b))))
        correct++;
    else
        wrong++;
    tasks--;
    if (tasks > 0)
        goto label;
    if (again(correct, wrong))
        goto label2;
}
void hex_div(int digits, int ex) {
    int correct;
    int wrong;
    int tasks;
    string s;
label2:
    correct = 0;
    wrong = 0;
    tasks = ex;
label:
    vector<int>a = generate_hex(digits);
    vector<int>b = generate_hex(digits);
    cout << vec_to_str(dec_to_hex(mul(hex_to_dec(a), hex_to_dec(b)))) << " / " << vec_to_str(b)<<" = ";
    getline(cin, s);
    if (str_to_vec(s) == a)
        correct++;
    else
        wrong++;
    tasks--;
    if (tasks > 0)
        goto label;
    if (again(correct, wrong))
        goto label2;
}
void hex_octal(int digits, int ex) {
    int correct;
    int wrong;
    int tasks;
    string s;
label2:
    correct = 0;
    wrong = 0;
    tasks = ex;
label:
    vector<int>a = generate_hex(digits);
    cout << vec_to_str(a) << " = ";
    getline(cin, s);
    if (str_to_vec(s) == hex_to_octal(a))
        correct++;
    else
        wrong++;
    tasks--;
    if (tasks > 0)
        goto label;
    if (again(correct, wrong))
        goto label2;
}
void hex_dec(int digits, int ex) {
    int correct;
    int wrong;
    int tasks;
    string s;
label2:
    correct = 0;
    wrong = 0;
    tasks = ex;
label:
    vector<int>a = generate_hex(digits);
    cout << vec_to_str(a) << " = ";
    getline(cin, s);
    if (str_to_vec(s) == hex_to_dec(a))
        correct++;
    else
        wrong++;
    tasks--;
    if (tasks > 0)
        goto label;
    if (again(correct, wrong))
        goto label2;
}
void hex_menu(int digits, int ex) {
    int n;
label:
    cout << "\nDecimal" << endl;
    cout << "1 addition" << endl;
    cout << "2 substraction" << endl;
    cout << "3 multiplication" << endl;
    cout << "4 division" << endl;
    cout << "5 hexadecimal to octal" << endl;
    cout << "6 hexadecimal to decimal" << endl;
    cout << "other back" << endl;
    cin >> n;
    cin.ignore();
    switch (n) {
    case 1:
        hex_add(digits, ex);
        break;
    case 2:
        hex_sub(digits, ex);
        break;
    case 3:
        hex_mul(digits, ex);
        break;
    case 4:
        hex_div(digits, ex);
        break;
    case 5:
        hex_octal(digits, ex);
        break;
    case 6:
        hex_dec(digits, ex);
        break;
    }
    if (n >= 1 && n <= 6)
        goto label;
}
void run() {
    int digits;
    int ex;
    int n;
    label2:
    cout << "Arithmetic excersise\n";
    cout << "Enter number of digits\n";
    cin >> digits;
    cout << "Enter number of exercises\n";
    cin >> ex;
    label:
    cout << "1 Binary" << endl;
    cout << "2 Octal" << endl;
    cout << "3 Decimal" << endl;
    cout << "4 hexadecimal" << endl;
    cout << "0 Back" << endl;
    cout << "Other exit" << endl;
    cin >> n;
    cin.ignore();
    switch (n) {
        case 1:
            bin_menu(digits, ex);
            break;
        case 2:
            octal_menu(digits, ex);
            break;
        case 3:
            dec_menu(digits, ex);
            break;
        case 4:
            hex_menu(digits, ex);
            break;
    }
    if (n >= 1 && n <= 4)
        goto label;
    if (n == 0)
        goto label2;
    cout << "Good Bye" << endl;
    system("pause");
}
void main(){
    run();
}
