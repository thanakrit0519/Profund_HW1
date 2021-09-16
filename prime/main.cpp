//64010304 ธนกฤต พันสีมา
#include <bits/stdc++.h>

using namespace std;

int isPrime(int a)
{
    int qc=0;
    if(a>2)
    {
        for(int i=2;i<=sqrt(a);i++)
        {
            if(a%i==0)
            {
                qc=1;
                break;
            }
        }
    }
    else if(a<1)
    {
        qc=1;
    }
    if(qc==0) cout<<"Prime Number";
    else cout<<"Not Prime Number";
}
int main()
{
    int n;
    cin>>n;
    isPrime(n);
    return 0;
}
