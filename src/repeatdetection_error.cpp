#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

const int INF = 0x7fffffff/2;
int max_error = 3;

vector<int> findRepeat(string s, int interval)
{
    int len = s.length();
    int f[101][5] = {0};

    int last[26] = {0};
    int pre[101];

    for(int i = 0; i < interval; i++)
    {
        last[0] = -1;
        last[2] = -1;
        last[6] = -1;
        last[19] = -1;

        for(int j = i ; j < len; j += interval)
        {
            pre[j] = last[s[j] - 'A'];
            last[s[j] - 'A'] = j;
        }
    }


    for(int i = 0; i < interval; i++)
        f[i][0] = 1;


    for(int i = interval; i < len; i++)
    {
        if(s[i] == s[i-interval])
            f[i][0] = f[i-interval][0] + 1;
        else
            f[i][0] = 1;

        if(pre[i] != -1)
        {
            int k = (i - pre[i]) / interval - 1;
        
            for(int j = k; j <= max_error; j++)
                f[i][j] = f[pre[i]][j-k] + k + 1;
        }
    }

    int ans = -1;
    int pos, err;

    for(int i = interval - 1; i < len; i++)
    {

        for(int k1 = 0; k1 <= max_error; k1++) //only for interval = 3
            for(int k2 = 0; k1 + k2 <= max_error; k2 ++)
                for(int k3 = 0; k1 + k2 + k3 <= max_error; k3++)
                {
                    int cons = INF;
                    // for(int j = i - interval + 1; j <= i; j++)
                    //     cons = min(cons, f[j]);
                    cons = min(f[i-2][k1], f[i-1][k2]);
                    cons = min(cons, f[i][k3]);

                    if(cons > ans || cons == ans && err > k1 + k2 + k3)
                    {
                        ans = cons;
                        pos = i;
                        err = k1 + k2 + k3;
                    }
                }
    }
    
    vector<int> ret(3);
    ret[0] = ans;
    ret[1] = pos;
    ret[2] = err;

    int flag = 0;
    for(int i = pos - interval + 1; i <= pos; i++)
        if(s[i] != s[pos])
        {
            flag = 1;
            break;
        }

    if(!flag)
        ret[0] = -1;

    return ret;
}

int main(int argc, char *argv[])
{
    string readl;
    string readr;
    FILE * out; 

    readl = argv[1];
    readr = argv[2];
    out = fopen (argv[3], "w");

    ifstream infilel(readl.c_str());
    ifstream infiler(readr.c_str());

    string seql, seqr;
    string tmp;

    vector<int> result(3);
    int readsnb = 0;

    while(1)
    {
        if(!getline(infilel, tmp))
            break;

        getline(infilel, seql);

        getline(infiler, tmp);
        getline(infiler, seqr);

        getline(infilel, tmp);
        getline(infilel, tmp);
        getline(infiler, tmp);
        getline(infiler, tmp);

        readsnb++;
        result = findRepeat(seql, 3);
        if(result[0] >= 10)
            fprintf(out, "%s\n%s\t%d\terror: %d\n", seql.c_str(), seql.substr(result[1] - 2, 3).c_str(), result[0], result[2]);

        result = findRepeat(seqr, 3);
        if(result[0] >= 10)
            fprintf(out, "%s\n%s\t%d\terror: %d\n", seqr.c_str(), seqr.substr(result[1] - 2, 3).c_str(), result[0], result[2]);
    }

    return 0;
}
