/*
Problem:
    We have coin album and coins.
    We are given n sizes of pockets in album.
    Coins have sizes of {1,...,n}
    

Goal:
    Find number of ways to correctly place coins in album.
    Coin can be in pocket of equal or smaller size (modulo 1000000007)

Approach:
    We consider pocets from smallest to biggest. 
    We want to find product of number of coins we can put in each pocket


Time complexity:
O(n log n)

Link: https://szkopul.edu.pl/problemset/problem/GMBfzRQAdw3b7wfvC9Xf7YE4/site/?key=statement
*/
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    vector<int> places(n);
    for(int i=0;i<n;i++){
        cin>>places[i];
    }
    sort(places.begin(),places.end());
    long long res=1;
    for(int i=0;i<n;i++){
        places[i]-=i;
        if(places[i]<=0){
            cout<<'0';
            return 0;
        }
        res=(res*places[i])%1000000007;
    } 
    cout<<res;

}