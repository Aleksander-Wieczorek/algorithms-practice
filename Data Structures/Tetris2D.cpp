/*
Problem:
    We have set of operations, simulating falling blocks, like in tetris.
    Each block has height of 1 starts at position x, and ends at position x+l.
    Of course physics of blocks are like in tetris.


Goal:
    After all operations we need to tell height of highest point

Approach:
    Segment tree (segment-segment) can easily simulate our problem.
    If block falls at segment [a,b) it sets values on this segment to (max{ [a,b) }+1)
    My segment tree provides max query and set update.

Time complexity:
All tree operations are in O(log n)
O(n log n)

Link: https://szkopul.edu.pl/problemset/problem/-0A1PC3fNc2RK-qvoUQKGGLl/site/?key=statement
*/


#include<bits/stdc++.h>
using namespace std;
struct tree{
    int M;
    vector<int> values;
    vector<int> mods;
    vector<bool> modded;
    tree(int n){
        M=1;
        while(M<n) M<<=1;
        values.resize(M<<1,0);
        modded.resize(M<<1,false);
        mods.resize(M<<1);
    }
    void push(int v){
        if(!modded[v]) return;
        values[2*v]=mods[v];
        mods[2*v]=mods[v];
        modded[2*v]=true;
        values[2*v+1]=mods[v];
        mods[2*v+1]=mods[v];
        modded[2*v+1]=true;
        modded[v]=false;
    }
    void pull(int v){
        values[v]=max(values[2*v],values[2*v+1]);
    }
    
    int range_query(int v,int P,int Q,int x, int y){
        // x, y searched interval
        // P,Q current interval

        // out of bounds
        if(P>=y or Q<=x){
            return 0;
        }
        // inside
        if(x<=P and Q<=y){
            return values[v];
        }
        push(v);
        int mid = (P+Q)/2;
        int left = range_query(2*v,P,mid,x,y);
        int right = range_query(2*v+1,mid,Q,x,y);
        pull(v);
        return(max(left,right));
    }
    int query(int x,int y){
        return range_query(1,0,M,x,y);
    }
    void range_update(int v,int P,int Q,int x, int y,int val){
        // x, y searched interval
        // P,Q current interval

        // out of bounds
        if(P>=y or Q<=x){
            return;
        }
        // inside
        if(x<=P and Q<=y){
            values[v]=val;
            modded[v]=true;
            mods[v]=val;
            return;
        }
        push(v);
        int mid = (P+Q)/2;
        range_update(2*v,P,mid,x,y,val);
        range_update(2*v+1,mid,Q,x,y,val);
        pull(v);
    }
    void update(int x,int y,int val){
        range_update(1,0,M,x,y,val);
    }
};
int main()
{
    int n,m;
    cin>>n>>m;
    tree T(n+1);
    for(int i=0;i<m;i++){
        int x,l;
        cin>>l>>x;
        int maxi=T.query(x,x+l);
        T.update(x,x+l,maxi+1);
    }
    cout<<T.query(0,n);
}