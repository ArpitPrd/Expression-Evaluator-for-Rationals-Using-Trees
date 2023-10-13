/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"
#include <iostream>

bool check(UnlimitedRational* i1, UnlimitedRational* i2){
    if ((i1->get_q()->get_size() == 1 && i1->get_q()->get_array()[0] == 0) || (i2->get_q()->get_size() == 1 && i2->get_q()->get_array()[0] == 0)){
        return false;
    }
    return true;
}

UnlimitedRational::UnlimitedRational(){
    p = new UnlimitedInt();
    q = new UnlimitedInt();
}
UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den){
    p = num;
    q = den;
}
UnlimitedRational::~UnlimitedRational(){
    delete p;
    delete q;
}

UnlimitedInt* UnlimitedRational::get_p(){
    return p;
}

UnlimitedInt* UnlimitedRational::get_q(){
    return q;
}

string UnlimitedRational::get_p_str(){
    int* arr = p->get_array();
    string s = "";
    if (p->get_sign() == -1){
        s = s + "-";
    }
    for (int i = 0; i < p->get_size(); i++){
        s = s + std::to_string(arr[i]);
    }
    return s;
}

string UnlimitedRational::get_q_str(){
    int* arr = q->get_array();
    string s = "";
    if (q->get_sign() == -1){
        s = s + "-";
    }
    for (int i = 0; i < q->get_size(); i++){
        s = s + std::to_string(arr[i]);
    }
    return s;
}

string UnlimitedRational::get_frac_str(){
    string s1 = get_p_str();
    string s2 = get_q_str();
    return s1 + "/" + s2;
}

UnlimitedInt* gcd(UnlimitedInt* i1, UnlimitedInt* i2){
    if (i1->get_size() == 1 && i1->get_array()[0] == 0){
        return i2;
    }
    else {
        return gcd(i1->mod(i2, i1), i1);
    }
}

bool greaterThan2(UnlimitedInt* i1, UnlimitedInt* i2){
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

UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1, UnlimitedRational* i2){
    if (check(i1, i2)){
        UnlimitedInt* num = i1->get_p()->add(i1->get_p()->mul(i1->get_p(), i2->get_q()), i1->get_p()->mul(i1->get_q(), i2->get_p()));
        UnlimitedInt* den = i1->get_p()->mul(i1->get_q(), i2->get_q());
        UnlimitedInt* g;
        if (greaterThan2(num, den)){
            g = gcd(den, num);
        }
        else g = gcd(den, num);
        UnlimitedInt* r1 = num->div(new UnlimitedInt(num->get_array(), num->get_capacity(), 1, num->get_size()), new UnlimitedInt(g->get_array(), g->get_capacity(), 1, g->get_size()));
        UnlimitedInt* r2 = den->div(new UnlimitedInt(den->get_array(), den->get_capacity(), 1, den->get_size()), new UnlimitedInt(g->get_array(), g->get_capacity(), 1, g->get_size()));
        UnlimitedRational* r = new UnlimitedRational(new UnlimitedInt(r1->get_array(), r1->get_capacity(), num->get_sign(), r1->get_size()), new UnlimitedInt(r2->get_array(), r2->get_capacity(), den->get_sign(), r2->get_size()));
        return r;
    }
    else{
        return new UnlimitedRational(new UnlimitedInt(0), new UnlimitedInt(0));
    }
}

UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1, UnlimitedRational* i2){
    if (check(i1, i2)){
        UnlimitedInt* num = i1->get_p()->sub(i1->get_p()->mul(i1->get_p(), i2->get_q()), i1->get_p()->mul(i1->get_q(), i2->get_p()));
        UnlimitedInt* den = i1->get_p()->mul(i1->get_q(), i2->get_q());
        UnlimitedInt* g;
        if (greaterThan2(num, den)){
            g = gcd(den, num);
        }
        else g = gcd(den, num);
        UnlimitedInt* r1 = num->div(new UnlimitedInt(num->get_array(), num->get_capacity(), 1, num->get_size()), new UnlimitedInt(g->get_array(), g->get_capacity(), 1, g->get_size()));
        UnlimitedInt* r2 = den->div(new UnlimitedInt(den->get_array(), den->get_capacity(), 1, den->get_size()), new UnlimitedInt(g->get_array(), g->get_capacity(), 1, g->get_size()));
        UnlimitedRational* r = new UnlimitedRational(new UnlimitedInt(r1->get_array(), r1->get_capacity(), num->get_sign(), r1->get_size()), new UnlimitedInt(r2->get_array(), r2->get_capacity(), den->get_sign(), r2->get_size()));
        return r;
    }
    else{
        return new UnlimitedRational(new UnlimitedInt(0), new UnlimitedInt(0));
    }
}

UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1, UnlimitedRational* i2){
    if (check(i1, i2)){
        UnlimitedInt* num = i1->get_p()->mul(i1->get_p(), i2->get_p());
        UnlimitedInt* den = i1->get_p()->mul(i1->get_q(), i2->get_q());
        UnlimitedInt* g;
        if (greaterThan2(num, den)){
            g = gcd(den, num);
        }
        else g = gcd(den, num);
        UnlimitedInt* r1 = num->div(new UnlimitedInt(num->get_array(), num->get_capacity(), 1, num->get_size()), new UnlimitedInt(g->get_array(), g->get_capacity(), 1, g->get_size()));
        UnlimitedInt* r2 = den->div(new UnlimitedInt(den->get_array(), den->get_capacity(), 1, den->get_size()), new UnlimitedInt(g->get_array(), g->get_capacity(), 1, g->get_size()));
        UnlimitedRational* r = new UnlimitedRational(new UnlimitedInt(r1->get_array(), r1->get_capacity(), num->get_sign(), r1->get_size()), new UnlimitedInt(r2->get_array(), r2->get_capacity(), den->get_sign(), r2->get_size()));
        return r;
    }
    else{
        return new UnlimitedRational(new UnlimitedInt(0), new UnlimitedInt(0));
    }
}

UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1, UnlimitedRational* i2){
    if (!(i2->get_p()->get_size() == 1 && i2->get_p()->get_array()[0] == 0) && check(i1, i2)){
        UnlimitedInt* num = i1->get_p()->mul(i1->get_p(), i2->get_q());
        UnlimitedInt* den = i1->get_p()->mul(i1->get_q(), i2->get_p());
        UnlimitedInt* g;
        if (greaterThan2(num, den)){
            g = gcd(den, num);
        }
        else g = gcd(den, num);
        UnlimitedInt* r1 = num->div(new UnlimitedInt(num->get_array(), num->get_capacity(), 1, num->get_size()), new UnlimitedInt(g->get_array(), g->get_capacity(), 1, g->get_size()));
        UnlimitedInt* r2 = den->div(new UnlimitedInt(den->get_array(), den->get_capacity(), 1, den->get_size()), new UnlimitedInt(g->get_array(), g->get_capacity(), 1, g->get_size()));
        UnlimitedRational* r = new UnlimitedRational(new UnlimitedInt(r1->get_array(), r1->get_capacity(), num->get_sign(), r1->get_size()), new UnlimitedInt(r2->get_array(), r2->get_capacity(), den->get_sign(), r2->get_size()));
        return r;
    }
    else{
        return new UnlimitedRational(new UnlimitedInt(0), new UnlimitedInt(0));
    }
}
/*
int main(){
    UnlimitedRational* r1 = new UnlimitedRational( new UnlimitedInt(-30), new UnlimitedInt(-44));
    UnlimitedRational* r2 = new UnlimitedRational( new UnlimitedInt(3), new UnlimitedInt(4));
    std::cout << r1->sub(r1, r2)->get_frac_str() << std::endl;
}
*/