/*
Problem:
    We have two arrays
    - first one represents types of movies displayed at movie theather
    - second one represents "coolness" of each movie
    We can only visit movie theather in consecutive days, and seeing
    more than once reduces "coolness" of this movie to 0 (first seance also do not give coolness)

Goal:
    Find best sum of "coolness" we can reach

Approach:
    The biggest problem is structure. 
    Thanks to segment tree (point-segment) we can process each segment easily.
    We can assume we start at each point and then find the best prefix

Starting at position 0 sets first seance of movie to its "coolness" and each second seance to negative "coolness"
It makes second seance cancells first one.
Moving starting position have to modify tree correctly, (by only up to 2 SET operations).
For each index we find best prefix sum in tree.


Time complexity:
All tree operations are in O(log n)
O(n log n)

Link: https://szkopul.edu.pl/problemset/problem/k-RYEjhwNTo_XdaCidXQUGMU/site/?key=statement
*/


#include<bits/stdc++.h>
using namespace std;
struct node{
    long long prefix=0,sum=0;
};
struct tree{
    int M;
    vector<node> values;
    // search for maximum prefix
    tree(int n){
        M=1;
        while(M<n) M<<=1;
        values.resize(M<<1);
    }
    void pull(int v){
        values[v].sum = values[2*v].sum + values[2*v+1].sum;
        values[v].prefix = max(values[2*v].prefix,values[2*v].sum + values[2*v+1].prefix);
    }
    void update(int v,int value){
        //cout<<'x';
        v+=M;
        values[v].prefix=values[v].sum=value;
        while(v>1){
            v>>=1;
            pull(v);
        }
    }
    long long query(){
        return values[1].prefix;
    }
};
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    vector<int> values(m+1);
    unordered_map<int,vector<int>> encounters;
    vector<int> indicators(m+1);
    vector<int> films(1);
    for(int i=1;i<=n;i++) {
        int a;
        cin>>a;
        films.push_back(a);
        encounters[a].push_back(i);
    }
    tree T(n+2);
    for(int i=1;i<=m;i++) {
        cin>>values[i];
        indicators[i]=0;
        if(encounters[i].size()>0){
            T.update(encounters[i][0],values[i]);
        }
        if(encounters[i].size()>1){
            T.update(encounters[i][1],-values[i]);
        }
    }
    long long res=0;
    res = max(res,T.query());
    //cout<<res<<'\n';
    for(int i=1;i<=n;i++){
        T.update(encounters[films[i]][indicators[films[i]]++],0);
        if(indicators[films[i]]<encounters[films[i]].size()){
            T.update(encounters[films[i]][indicators[films[i]]],values[films[i]]);
        }
        if(indicators[films[i]]+1<encounters[films[i]].size()){
            T.update(encounters[films[i]][indicators[films[i]]+1],-values[films[i]]);
        }
        res = max(res,T.query());
    }
    cout<<res;
}