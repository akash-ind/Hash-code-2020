#include<iostream>
#include<stack>
#include<vector>
#include<fstream>
using namespace std;
int binarySearch(long *arr,long long k,int lo,int hi)
{
    if(lo>=hi)
    {
        if(arr[lo]<=k)
            return lo;
        else
            return -1;
    }
    int i=lo+(hi-lo)/2;
    if(arr[i]>k)
        return binarySearch(arr,k,lo,i-1);
    else if(arr[i]<k)
        {
            int b=binarySearch(arr,k,i+1,hi);
            if(b==-1)
                return i;
            else
                return b;
        }
    else
        return i;
}
int main()
{
    vector<int>temp_index;
    vector<int>index;
    fstream in;
    in.open("e_also_big.in",ios::binary|ios::in);
    long long m;
    int n;
    in>>m>>n;       //that is we are taking into account the maximum no of slices and different pizza
    long *arr=new long[n];
    long long *pre=new long long[n];
    in>>arr[0];
    pre[0]=arr[0];
    for(int i=1;i<n;i++)
    {
        in>>arr[i];
        pre[i]=pre[i-1]+arr[i];
    }
    long long sum=0,temp_sum=0;
    int j=n-1;
    while(pre[j]>=m)
    {
        temp_sum=0;
        temp_index.clear();
        for(int i=j;i>=0;i--)
        {
            temp_sum+=arr[i];
            temp_index.push_back(i);
            if(temp_sum>m)
            {
                temp_sum-=arr[i];
                temp_index.pop_back();
                int k=binarySearch(arr,m-temp_sum,0,i);
                if(k==-1)
                {
                    break;
                }
                else
                {
                    temp_sum+=arr[k];
                    temp_index.push_back(k);
                }
                i=k;
            }
            if(temp_sum==m)
            {
                break;
            }
        }
        if(sum<temp_sum)
        {
            sum=temp_sum;
            index.clear();
            for(int i=0;i<temp_index.size();i++)
            {
                index.push_back(temp_index[i]);
            }
        }
        if(temp_sum==m)
            break;
        j--;
    }
    fstream out("sol_e.txt",ios::binary|ios::out);
    if(!out)
        cout<<"cannot open file"<<endl;
    out<<index.size()<<endl;
    while(!index.empty())
    {
        out<<index.back()<<" ";
        index.pop_back();
    }
    delete[] arr;
    delete[] pre;
    return 0;
}
