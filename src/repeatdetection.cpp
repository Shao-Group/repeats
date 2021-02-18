#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

const int INF = 0x7fffffff/2;

pair<int,int> findRepeat(string s, int interval)
{
    int len = s.length();
    int f[101] = {0};

    for(int i = 0; i < interval; i++)
        f[i] = 1;

    for(int i = interval; i < len; i++)
        if(s[i] == s[i-interval])
            f[i] = f[i-interval] + 1;
        else
            f[i] = 1;
    int ans = -1;
    int pos;

    for(int i = interval - 1; i < len; i++)
    {
        int cons = INF;
        for(int j = i - interval + 1; j <= i; j++)
            cons = min(cons, f[j]);

        if(cons >= ans)
        {
            ans = cons;
            pos = i;
        }
    }

    pair<int, int> ret;
    ret.first = ans;
    ret.second = pos;

    int flag = 0;
    for(int i = pos - interval + 1; i <= pos; i++)
        if(s[i] != s[pos])
        {
            flag = 1;
            break;
        }

    if(!flag)
        ret.first = -1;

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

    pair<int,int> result;
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
        if(result.first >= 10)
            fprintf(out, "%s\n%s\t%d\n", seql.c_str(), seql.substr(result.second - 2, 3).c_str(), result.first);

        result = findRepeat(seqr, 3);
        if(result.first >= 10)
            fprintf(out, "%s\n%s\t%d\n", seqr.c_str(), seqr.substr(result.second - 2, 3).c_str(), result.first);
    }

    return 0;
}
