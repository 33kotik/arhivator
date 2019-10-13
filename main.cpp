//#include <iostream>
#include  <bits/stdc++.h>
#include "time.h"
#include <limits.h>
#include <float.h>
//переименовать переменные без транслита
// сделать чёнить  с алгоритмом белоногова

//выыод в консоль

//#include <stdio.h>
using namespace std;
int n, w;
string s;
int j, newn;
vector<bool> a;

struct q {
    int kol;
    char sim;
    vector<bool> kod;
    double dol;
    char kod2;
};
q az[256];
q b;
vector<unsigned char> buffer;
int cur = 0;

unsigned char get_bit(int pos) {
    int byte_id = pos / 8;
    int bit_id = pos % 8;
    return (buffer[byte_id] >> bit_id) & 1;
}

void add_to_buffer(unsigned char bit) {
    if (cur == 0) {
        buffer.push_back(0);
    }
    buffer.back() = buffer.back() ^ (bit << cur);
    cur = (cur + 1) % 8;
}

bool cmp1(q x, q y) {
    return x.kol > y.kol;
}




void rec(int l, int r) {
    //cout<<l<<" "<<r<<endl;
    double x = 0.0;
    double ee = 0;
    if (r - l <= 1) {
        // az[l].kod.push_back(1);
        return;
    }

    for (int i = l; i < r; i++)
        ee = az[i].kol + ee;

    for (int i = l; i < r; i++)
        az[i].dol = az[i].kol / ee;

    //for (int i=l;i<r;i++)
    //    //     cout<<az[i].dol<<" ";
    //    // cout<<endl;
    int newr = 0;
    for (int i = l; i < r; i++) {
        if (x < 0.5) {
            az[i].kod.push_back(1);
            x = x + az[i].dol;
        } else {
            if (newr == 0)
                newr = i;
            az[i].kod.push_back(0);
        }
    }
    rec(l, newr);
    rec(newr, r);
    return;
}



int main() {
    srand(time(0));
    int i;

    cin >> s;
    n = s.length();
    for (i = 0; i < n; i++) {
        az[s[i]].kol++;
        az[s[i]].sim = s[i];
    }
    sort(az, az + 256, cmp1);
    for (i = 0; i < 256; i++) {
        if (az[i].kol > 0) {
            w++;
        }
    }
    for (i = 0; i < w; i++) {
        az[i].dol = az[i].kol / n;
    }
    double x = 0;
    newn = n;
    rec(0, w);
    for (i = 0; i < w; i++) {
        cout << az[i].sim << " " << az[i].kol << " ";
        for (j = 0; j < az[i].kod.size(); j++)
            cout << az[i].kod[j];
        cout << endl;
    }
    for (i = 0; i < 256; i++)
        for (j = 0; j < 256; j++)
            if (az[i].sim != i)
                swap(az[i], az[az[i].sim]);
    int cnt_bit = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < az[s[i]].kod.size(); j++) {
            add_to_buffer(az[s[i]].kod[j]);
            cnt_bit++;
        }
    }
    /* for (i = 0; i < a.size(); i++)
         cout << a[i];
     cout << endl;*/
    sort(az, az + 256, cmp1);

    for (i=0;i<cnt_bit;i++){
        b.kod.push_back(get_bit(i));
        for (j=0;j<w;j++)
            if (b.kod==az[j].kod){
                cout<<az[j].sim;
                b.kod.clear();
                break;
            }
    }
    cout << endl;
    char r = 0;
    return 0;

}