/*
Problem:
    Given a line of fields with integer values:
    - positive values means power plants,
    - negative values means factories,
    - zero means an empty field.
    Adjacent fields can be connected into segments.
    The energy of a segment is the sum of values in that segment.

Goal:
    Find the minimum number of connections such that the sum of values
    in every connected segment is non-negative.
    If it is impossible, output is -1.

Approach:
    Let prefix_sums[i] be the sum of the first i fields.
    We use dynamic programming where dp[i] represents the minimum number
    of connections needed to partition the prefix [1..i] into valid segments.

For each position i, we find the latest position j < i such that:
prefix_sums[i] - prefix_sums[j] >= 0.

To efficiently find such j we use binary search.

Time complexity:
O(n log n)

Link: https://szkopul.edu.pl/problemset/problem/B4XL0I6ifyo5j3dfzVm6mF2r/site/?key=statement
*/

#include<bits/stdc++.h>
using namespace std;
int binsearch(vector<pair<long long,int>> &ref,long long x){
    int p=0,q=ref.size()-1;
    while(p<q){
        int mid=(p+q)/2;
        // search in left
        if(ref[mid].first<=x){
            p=mid+1;
        }
        else q=mid;
    }
    return p;
}
int main()
{
    int n;
    cin>>n;
    vector<long long> prefix_sums(n+10);
    vector<pair<long long,int>> lis(n+10,{LONG_LONG_MAX,0});
    lis[0].first=LONG_LONG_MIN;
    vector<int> dp(n+10);
    if(n==1){
        cin>>n;
        cout<<( n>=0 ? 0:-1);
        return 0;
    }
    prefix_sums[0]=0;
    dp[0]=0;
    for(int i=1;i<=n;i++){
        int a;
        cin>>a;
        prefix_sums[i]=(long long)(prefix_sums[i-1]+a);
        if(prefix_sums[i]<0){
            dp[i]=-1;
            continue;
        }
        else{
            int first=binsearch(lis,prefix_sums[i]);
            dp[i]=(long long)(dp[lis[first-1].second]+i-lis[first-1].second-1);
            if (lis[first].first>= prefix_sums[i])
                lis[first]={prefix_sums[i],i};
        }

    }
    cout<<dp[n];
}