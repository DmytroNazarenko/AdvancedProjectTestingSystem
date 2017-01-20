#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <fstream>
#include <queue>
#include <vector>
#include <cstring>
#include <iomanip>

using namespace std;
typedef long long ll;
typedef long double ld;


class etalon_program {
   
    

public:
 
    etalon_program(int m, int n) {
        this->m = m;
        this->n = n;
    }
    ll execute()
    {
        d.resize(n + 1, vector<long long>(1 << m));
        d[0][0] = 1;
        for (int x = 0; x < n; ++x)
            for (int mask = 0; mask < (1 << m); ++mask)
                calc( x, 0, mask, 0);

        return d[n][0];
    }

private:
    int m;
    int n;
    vector < vector<long long> > d;
    void calc( int x = 0, int y = 0, int mask = 0, int next_mask = 0)
    {
        if (x == n)
            return;
        if (y >= m)
            d[x + 1][next_mask] += d[x][mask];
        else
        {
            int my_mask = 1 << y;
            if (mask & my_mask)
                calc(x, y + 1, mask, next_mask);
            else
            {
                calc(x, y + 1, mask, next_mask | my_mask);
                if (y + 1 < m && !(mask & my_mask) && !(mask & (my_mask << 1)))
                    calc(x, y + 2, mask, next_mask);
            }
        }
    }

};


class my_program {

private:
    ll INF = 1e18;
    ll d[16][13][4097];
    int m;
    int n;

public:
    my_program(int m, int n) {
        this->m = m;
        this->n = n;
    }

    ll execute()
    {
        

        if (n > m) swap(n, m);

        for (int i = 0; i < m + 1; ++i)
            for (int j = 0; j < n + 1; ++j)
                for (int k = 0; k < (1 << n); k++) d[i][j][k] = 0;

        d[0][0][0] = 1;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n + 1; ++j) {
                for (ll k = 0; k < (1 << n); k++) {
                    if (j == n) {
                        d[i + 1][0][k] += d[i][j][k];
                        continue;
                    }
                    if ((k & (1 << (n - j - 1))) == 0) {
                        if (i != m - 1) d[i][j + 1][k + (1 << (n - j - 1))] += d[i][j][k];
                        if (j != n - 1 && (k & (1 << (n - j - 2))) == 0) {
                            d[i][j + 1][k + (1 << (n - j - 2))] += d[i][j][k];
                        }
                    }
                    else {
                        d[i][j + 1][k - (1 << (n - j - 1))] += d[i][j][k];
                    }

                }
            }
        }

        ll sum = 0;
        for (int k = 0; k < (1 << n); k++) {
            sum += d[m][0][k];
        }
        return sum;
    }
};


int main() {
    ifstream cin("tests.txt");
    int m, n;
    string s;
    int tcount = 1;
    
    while (!cin.eof()) {
        cout << "Test number " << tcount << endl;
        cin >> s >> m >> n;
        cout << "N: " << n << endl << "M: " << m << endl;
        etalon_program *pr1 = new etalon_program(m, n);
        ll res1 = pr1 -> execute();
        etalon_program *pr2 = new etalon_program(m, n);
        ll res2 = pr2 -> execute();
        cout << "Etalon result: " << res1 << endl;
        cout << "My program result: " << res2 << endl;
        if (res1 == res2) {
            cout << ">> OK: results are the same" << endl;
        }
        else {
            cout << ">> WA: result aren't the same" << endl;
        } 
        cout << "----------------------------------" << endl;
        tcount++;
   }
}


