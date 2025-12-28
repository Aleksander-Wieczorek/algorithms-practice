/*
Problem:
    We have matchsticks in line. 
    Each has head oriented to left (matches[i]=0) or right (matches[i]=1)

Goal:
    Find how many matches we need to flip, so if we light the first one, all of them will burn

Approach:
    The most crucial observation is that all matches are oriented right to some point,
    and from that point all of matches are oriented left, other orientation will fail


Time complexity:
O(n)

Link: https://szkopul.edu.pl/problemset/problem/ZLG7FB_afACLMh8-zsupw5zV/site/?key=statement
*/

#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    vector<int> matches(n),zero_to(n+1,0),ones_from(n+1,0);
    int res=INT_MAX;
    for(int i=0;i<n;i++){
        if(i>0) zero_to[i]=zero_to[i-1];
        cin>>matches[i];
        if(matches[i]==0) zero_to[i]++;
    }
    for(int i=n-1;i>=0;i--){
        ones_from[i]=ones_from[i+1];
        if(matches[i]==1) ones_from[i]++;
    }
    for(int i=0;i<n;i++){
        res=min(res,ones_from[i]+zero_to[i]-1);
    }
    cout<<res<<'\n';
}