/*
Problem:
    We have set of operations, simulating querying reservation of train seats.
    If train can hold enough passengers it accepts the query and updates state of seating 
    if not, query is cancelled


Goal:
    For each operation decide if it will be cancelled or accepted

Approach:
    Segment tree (segment-segment) can easily simulate our problem.
    We need to check if (max{[a,b)} +l) <=hardcap. If yes, then add l to segment [a,b).
    My segment tree provides max query and add update.

Time complexity:
All tree operations are in O(log n)
O(n log n)

Link: https://szkopul.edu.pl/problemset/problem/VYTSyRwgdwmLf56i_ffWGB0L/site/?key=statement
*/


#include<bits/stdc++.h>
using namespace std;

struct tree{
    int M;
    int hardcap;
    vector<int> value;
    vector<int> mod;
    tree(int n,int m):hardcap(m){
        M = 1;
        while(M < n) {M <<= 1;}
        value.resize(M<<1,0);
        mod.resize(M<<1,0);
    }
    void push(int v){
        value[2*v]+=mod[v];
        mod[2*v]+=mod[v];
        value[2*v+1]+=mod[v];
        mod[2*v+1]+=mod[v];
        mod[v]=0;
    }
    void pull(int v){
        value[v]=max(value[2*v],value[2*v+1]);
    }
    bool query(int P,int Q,int c){
        return range_query(1,1,M,P,Q)+c<=hardcap;
    }
    int range_query(int v,int p,int q,int P,int Q){
        // v current node
        // p ,q current range
        // P, Q, searched range
        if(q<=P or p>=Q) return 0;
        if(P<=p and q<=Q){
            return value[v];
        }
        push(v);
        int mid = (p+q)/2;
        int left = range_query(2*v,p,mid,P,Q);
        int right = range_query(2*v+1,mid,q,P,Q);
        //pull(v);
        return max(left,right);
    }
    void update(int P,int Q, int x){
        range_update(1,1,M,P,Q,x);
    }
    void range_update(int v,int p,int q, int P,int Q, int x){
        if(q<=P or p>=Q) return;
        if(P<=p and q<=Q){
            mod[v]+=x;
            value[v]+=x;
            return;
        }
        push(v);
        int mid = (p+q)/2;
        range_update(2*v,  p,mid,P,Q,x);
        range_update(2*v+1,mid,q,P,Q,x);
        pull(v);
    }
};

int main()
{
    int z;
    //cin>>z;
    //while(z--){
        int n,m,q;
        cin>>n>>m>>q;
        tree T(n+1,m);
        while(q--){
            int p,k,l;
            cin>>p>>k>>l;
            if(T.query(p,k,l)){
                cout<<"T\n";
                T.update(p,k,l);
            }
            else cout<<"N\n";
        }
   // }
}