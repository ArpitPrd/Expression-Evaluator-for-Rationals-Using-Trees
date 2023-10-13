/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
// to be deleted
#include <iostream>
UnlimitedInt::UnlimitedInt(){
    capacity = 0;
    unlimited_int = new int[capacity];
    size = 0;
    sign = 1;
}

UnlimitedInt::UnlimitedInt(string s){
    if (s.size() > 0){
        if (s[0] == '-'){
            size = s.size() - 1;
            sign = -1;
            capacity = size;
            unlimited_int = new int[capacity];
            for (int i = 1; i < size+1; i++){
                unlimited_int[i-1] = s[i]-'0';
            }
        }
        else{
            size = s.size();
            sign = 1;
            capacity = size;
            unlimited_int = new int[capacity];
            for (int i = 0; i < size; i++){
                unlimited_int[i] = s[i]-'0';
            }
        }
    }
    else{
        size = 0;
        sign = 1;
        capacity = size;
        unlimited_int = new int[capacity];
    }
}

UnlimitedInt::UnlimitedInt(int i){
    if (i < 0){
        size = 0;
        int c =1;
        while (abs(i) / c != 0){
            c *= 10;
            size++;
        }
        int t = abs(i);
        sign = -1;
        capacity = size;
        unlimited_int = new int[capacity];
        for (int j = size - 1; j >=0; j--){
            unlimited_int[j] = t % 10;
            t /= 10;
        }
    }
    else if (i > 0){
        size = 0;
        int c =1;
        while (abs(i) / c != 0){
            c *= 10;
            size++;
        }
        sign = 1;
        capacity = size;
        unlimited_int = new int[capacity];
        int t = i;
        for (int j = size - 1; j >=0; j--){
            unlimited_int[j] = t % 10;
            t /= 10;
        }
    }
    else {
        size = 1;
        sign = 1;
        capacity = 1;
        unlimited_int = new int[capacity];
        unlimited_int[0] = 0;
    }
}

UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz){
    size = sz;
    capacity = cap;
    sign = sgn;
    unlimited_int = new int[capacity];
    for (int i =0; i < size; i++){
        unlimited_int[i] = ulimited_int[i];
    }
}
int UnlimitedInt::get_size(){
    return size;
}
int* UnlimitedInt::get_array(){
    return unlimited_int;
}
int UnlimitedInt::get_sign(){
    return sign;
}
int UnlimitedInt::get_capacity(){
    return capacity;
}
UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2){
    if (i1->get_sign() == -1 && i2->get_sign() == -1){
        UnlimitedInt* i11 = new UnlimitedInt(i1->get_array(), i1->get_capacity(), 1, i1->get_size());
        UnlimitedInt* i22 = new UnlimitedInt(i2->get_array(), i2->get_capacity(), 1, i2->get_size());
        UnlimitedInt* res = add(i11, i22);
        UnlimitedInt* fres = new UnlimitedInt(res->get_array(), res->get_capacity(), -1, res->get_size());
        return fres;
    }
    else if (i1->get_sign() == 1 && i2->get_sign() == 1){
        // real add
        int* arr = new int[max(i1->get_size(), i2->get_size())+1];
        int i = i1->get_size()-1;
        int j = i2->get_size() - 1;
        int k = max(i1->get_size() ,i2->get_size());
        int carry = 0;
        while (i >= 0 && j >= 0){
            arr[k] = (i1->get_array()[i] + i2->get_array()[j] + carry) % 10;
            carry = (i1->get_array()[i] + i2->get_array()[j] + carry) / 10;
            k--;
            i--;
            j--;
        }
        while (i >= 0){
            arr[k] = (i1->get_array()[i] + carry) % 10;
            carry = (i1->get_array()[i] + carry) / 10;
            i--;
            k--;
        }
        while (j >= 0){
            arr[k] = (i2->get_array()[j] + carry) % 10;
            carry = (i2->get_array()[j] + carry) / 10;
            j--;
            k--;
        }
        arr[0] = carry;
        int cap;
        int* arr3;
        if (carry == 0){
            arr3 = new int[max(i1->get_size(), i2->get_size())];
            for (int a = 0; a< max(i1->get_size(), i2->get_size()); a++){
                arr3[a] = arr[a+1];
            }
            cap = max(i1->get_size(), i2->get_size());
        }
        else {
            arr3 = arr;
            cap = max(i1->get_size(), i2->get_size()) + 1;
        }
        UnlimitedInt* res = new UnlimitedInt(arr3, cap, 1, cap);
        return res;
    }
    else if (i1->get_sign() == -1 && i2->get_sign() == 1){
        UnlimitedInt* i11 = new UnlimitedInt(i1->get_array(), i1->get_capacity(), 1, i1->get_size());
        UnlimitedInt* i22 = new UnlimitedInt(i2->get_array(), i2->get_capacity(), 1, i2->get_size());
        UnlimitedInt* res = sub(i22, i11);
        return res;
    }
    else{
        UnlimitedInt* i11 = new UnlimitedInt(i1->get_array(), i1->get_capacity(), 1, i1->get_size());
        UnlimitedInt* i22 = new UnlimitedInt(i2->get_array(), i2->get_capacity(), 1, i2->get_size());
        UnlimitedInt* res = sub(i11, i22);
        return res;
    }
}
bool greaterThan(UnlimitedInt* i1, UnlimitedInt* i2){
    if (i1->get_size() > i2->get_size()){
        return true;
    }
    else if (i1->get_size() == i2->get_size()){
        int i = 0;
        while (i1->get_array()[i] == i2->get_array()[i] && i < i1->get_size()){
            i++;
        }
        if (i == i1->get_size()) return true;
        else if (i1->get_array()[i] > i2->get_array()[i]) return true;
        else return false;
    }
    else{
        return false;
    }
}
bool greaterThan1(UnlimitedInt* i1, UnlimitedInt* i2){
    if (i1->get_size() > i2->get_size()){
        return true;
    }
    else if (i1->get_size() == i2->get_size()){
        int i = 0;
        while (i1->get_array()[i] == i2->get_array()[i] && i < i1->get_size()){
            i++;
        }
        if (i == i1->get_size()) return false;
        else if (i1->get_array()[i] > i2->get_array()[i]) return true;
        else return false;
    }
    else{
        return false;
    }
}
UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2){
    if (i1->get_sign() == -1 && i2->get_sign() == -1){
        UnlimitedInt* i11 = new UnlimitedInt(i1->get_array(), i1->get_capacity(), 1, i1->get_size());
        UnlimitedInt* i22 = new UnlimitedInt(i2->get_array(), i2->get_capacity(), 1, i2->get_size());
        UnlimitedInt* res = sub(i22, i11);
        return res;
    }
    else if (i1->get_sign() == 1 && i2->get_sign() == 1){
        if (greaterThan(i1, i2)){
            int* arr = new int[i1->get_size()];
            int i = i1->get_size() - 1;
            int j = i2->get_size() - 1;
            int k = i;
            int borrow = 0;
            while (i >=0 && j >= 0){
                arr[k] = (10 + i1->get_array()[i] - i2->get_array()[j] + borrow) % 10;
                if ((i1->get_array()[i] - i2->get_array()[j] + borrow) < 0) {
                    borrow = -1;
                }
                else borrow = 0;
                i--;
                j--;
                k--;
            }
            while (i >= 0){
                arr[k] = (10 + i1->get_array()[i] + borrow) % 10;
                if ((i1->get_array()[i] + borrow) < 0) {
                    borrow = -1;
                }
                else borrow = 0;
                i--;
                k--;
            }
            
            int m = 0;
            int* arr3;
            while (arr[m] == 0 && m < i1->get_size()){
                m++;
            }
            arr3 = new int[i1->get_size() - m ];
            UnlimitedInt* r;
            if (m != i1->get_size()){
                for (int f = m; f < i1->get_size(); f++){
                    arr3[f-m] = arr[f];
                }
                r = new UnlimitedInt(arr3, i1->get_size() - m, 1, i1->get_size() - m);
            }
            else r = new UnlimitedInt("0");
            return r;
        }
        else{
            UnlimitedInt* r = sub(i2, i1);
            UnlimitedInt* res = new UnlimitedInt(r->get_array(), r->get_capacity(), -1, r->get_size());
            return res;
        }
    }
    else if (i1->get_sign() == -1 && i2->get_sign() == 1){
        UnlimitedInt* i11 = new UnlimitedInt(i1->get_array(), i1->get_capacity(), 1, i1->get_size());
        UnlimitedInt* i22 = new UnlimitedInt(i2->get_array(), i2->get_capacity(), 1, i2->get_size());
        UnlimitedInt* res = add(i22, i11);
        UnlimitedInt* fres = new UnlimitedInt(res->get_array(), res->get_capacity(), -1, res->get_size());
        return fres;
    }
    else{
        UnlimitedInt* i11 = new UnlimitedInt(i1->get_array(), i1->get_capacity(), 1, i1->get_size());
        UnlimitedInt* i22 = new UnlimitedInt(i2->get_array(), i2->get_capacity(), 1, i2->get_size());
        UnlimitedInt* res = add(i22, i11);
        return res;
    }
}

UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2){
    int* arr = new int[0];
    int* farr = new int[i1->get_size() + i2->get_size()];
    UnlimitedInt* final_arr = new UnlimitedInt(farr, i1->get_size() + i2->get_size(), 1, i1->get_size() + i2->get_size());
    int carry = 0;
    int j;
    for (int i = i1->get_size() - 1; i >= 0; i--){
        carry = 0;
        delete[] arr;
        arr = new int[i1->get_size() + i2->get_size()];
        for (j = i2->get_size() - 1; j >= 0; j--){
            arr[i1->get_size() + i2->get_size() - (i2->get_size() - 1 - j) - (i1->get_size() - 1 - i) - 1] = (i1->get_array()[i] * i2->get_array()[j] + carry) % 10;
            carry = (i1->get_array()[i] * i2->get_array()[j] + carry) / 10;
        }
        arr[i1->get_size() + i2->get_size() - (i2->get_size() - 1 - j) - (i1->get_size() - 1 - i) - 1] = carry;
        UnlimitedInt* inter = new UnlimitedInt(arr, i1->get_size() + i2->get_size(), 1, i1->get_size() + i2->get_size());
        final_arr = final_arr->add(final_arr, inter);
    }
    int m = 0;
    while (final_arr->get_array()[m] == 0 && m < i1->get_size() + i2->get_size()){
        m++;
    }
    UnlimitedInt* res;
    if (m != i1->get_size() + i2->get_size()){
        int* fin_arr = new int[final_arr->get_size() - m];
        for (int g = m; g < final_arr->get_size(); g++){
            fin_arr[g - m] = final_arr->get_array()[g];
        }
        res = new UnlimitedInt(fin_arr, final_arr->get_size() - m , i1->get_sign() * i2->get_sign(), final_arr->get_size() - m );
    }
    else res = new UnlimitedInt("0");
    return res;
}

int floor(int val1, int val2){
	float a = (float) val1;
	float b = (float) val2;
	float c = b / a;
	int d = (int) c;
	int k = val2 / val1;
	if (c > 0){
		return d;
	}
	else{
		return k-1;
	}
}


int* num(UnlimitedInt* i1, UnlimitedInt* i2 = nullptr){
    int a = 0;
    int po = 1;
    int i = min(i1->get_size(), 9)-1;
    int* x= new int[2];
    while (i >= 0){
        a += i1->get_array()[i] * po;
        po = po * 10;
        i--;
    }
    x[0] = a;
    if (i2 != nullptr){
        int b = 0;
        po = 1;
        i = min(i2->get_size(), 9) - 1;
        while (i >= 0){
            b += i2->get_array()[i] * po;
            po = po * 10;
            i--;
        }
        x[1] = b;
    }
    return x;
}

UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2){
    if (i1->get_size() == 1 && i1->get_array()[0] == 0){
        UnlimitedInt* u = new UnlimitedInt("0");
        return u;
    }
    else if (i2->get_size() == 1 && i2->get_array()[0] == 0){
        return i2;
    }
    else if (i1->get_size() <= 9 && i2->get_size() <= 9){
        int* s = num(i1, i2);
        UnlimitedInt* u = new UnlimitedInt(floor(s[1] * i1->get_sign(), s[0] * i2->get_sign()));
        return u;
    }
    else if (greaterThan1(i2, i1)){
        UnlimitedInt* u;
        if (i1->get_sign() * i2->get_sign() == -1){
            u = new UnlimitedInt(-1);
        }
        else {
            u = new UnlimitedInt(0);
        }
        return u;
    }
    else {
        UnlimitedInt* u = new UnlimitedInt(i1->get_array(), i1->get_capacity(), 1, i1->get_size());
        UnlimitedInt* v = new UnlimitedInt(i2->get_array(), i2->get_capacity(), 1, i2->get_size());
        UnlimitedInt* fans = new UnlimitedInt("0");
        UnlimitedInt* one = new UnlimitedInt("1");
        UnlimitedInt* two = new UnlimitedInt("2");
        while (true){
            if (greaterThan(u, v->mul(v, two))){
                v = v->mul(v, two);
                one = one->mul(one, two);
            }
            else {
                if (one->get_size() == 1 && one->get_array()[0] == 1){
                    if (greaterThan(u, v)){
                        fans = fans->add(fans, one);
                    }
                    break;
                }
                else{
                    u = u->sub(u, v);
                    fans = fans->add(fans, one);
                    v = new UnlimitedInt(i2->get_array(), i2->get_capacity(), 1, i2->get_size());
                    delete one;
                    one = new UnlimitedInt("1");
                }
            }
        }
        if (i1->get_sign() * i2->get_sign() == 1){
            return fans;
        }
        else{
            one = new UnlimitedInt("1");
            fans = fans->add(fans, one);
            fans = new UnlimitedInt(fans->get_array(), fans->get_capacity(), -1, fans->get_size());
            return fans;
        }
    }
}

UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2){
    UnlimitedInt* u = i1->sub(i1, i1->mul(i2, i1->div(i1, i2)));
    return u;
}

string UnlimitedInt::to_string(){
    string s ="";
    if (sign == -1){
        s = s + "-";
    }
    for (int i = 0; i < size; i++){
        s = s + std::to_string(unlimited_int[i]);
    }
    return s;
}

/*
int main(){
    int* arr1 = new int[4];
    int* arr2 = new int[3];
    arr1[0] = 9;
    arr1[1] = 9;
    arr1[2] = 9;
    arr1[3] = 9;
    arr2[0] = 9;
    arr2[1] = 9;
    arr2[2] = 9;
    UnlimitedInt* i1 = new UnlimitedInt("5987656789876567898765");
    UnlimitedInt* i2 = new UnlimitedInt("3");
    std::cout << i1->to_string() << std::endl;

    UnlimitedInt* r = i1->mod(i1, i2);
    int* res = r->get_array();
    if (r->get_sign() == -1){
        std::cout << "-";
    }
    for (int i = 0; i < r->get_size(); i++){
        std::cout << res[i];
    }
    std::cout << std::endl;


}
*/