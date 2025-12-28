/*
Problem:
    We wait in queue at position 0.
    For each position j (1<=j<=n) there is customer with value a[j]/
    If we are at position i, we can move to j > i
    by paying a cost exual to a[j] * (j - i) money

Goal:
    Find the minimum cost to reach position n.

Approach:
    We always want to pay customer in front of with smallest cost. 
    If two customers have the same cost choose any

The easiest approach is to make pairs {cost,idx} and then sort it,
However using monotonic dequeue solves this problem with better complexity

Time complexity:
O(n)
*/

#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin>>n;
    deque<pair<int,int>> best;
    for(int i=1;i<=n;i++){
        int a;
        cin>>a;
        while(!best.empty() and best.front().first>a){
            best.pop_front();
        }
        best.push_front({a,i});
    }
    int start=0;
    long long res=0;
    while(!best.empty()){
        res+=(long long)(best.back().second-start)*(long long)(best.back().first);
        start = best.back().second;
        best.pop_back();
    }
    cout<<res;
}