#include<bits/stdc++.h>

using namespace std;

const int N = 200010;
vector <int> g[N];
vector <int> gc[N];
int n, m;
int rep[N];
int mark[N];
stack <int> s;
int cnt;

void dfs2(int v){
    rep[v] = cnt;
    for(auto x : gc[v]){
        if(rep[x])
            continue;
        dfs2(x);
    }
    return;
}

void dfs(int v){
    mark[v] = 1;
    for(auto x : g[v]){
        if(mark[x])
            continue;
        dfs(x);
    }
    s.push(v);
    return;
}

int neg(int x){
    if(x > m)
        return x-m;
    else 
        return x+m;
}

void add(int a, int b){
    g[a].push_back(b);
    gc[b].push_back(a);
}

vector <int> gg[N], ggc[N];

void add2(int a, int b){
    if(a == b)
        return;
    gg[a].push_back(b);
    ggc[b].push_back(a);
}

int deg[N];
vector <int> topsort;
int idx[N];

int main(){
    cnt = 1;
    cin >> n >> m;
    for(int i = 0;i < n;i++){
        char c1, c2;
        int v1, v2;
        cin >> c1 >> v1 >> c2 >> v2;
        if(c1 == '-')
            v1 += m;
        if(c2 == '-')
            v2 += m;
        add(neg(v1), v2);
        add(neg(v2), v1);
    }
    for(int i = 1;i <= 2*m;i++){
        if(mark[i] == 0){
            dfs(i);
        }
    }   
    while(!s.empty()){
        int v = s.top();
        s.pop();
        if(rep[v] != 0)
            continue;
        dfs2(v);
        cnt++;
    }
    for(int i = 1;i <= 2*m;i++){
        for(auto x : g[i]){
            add2(rep[i], rep[x]);
        }
    }
    queue <int> q;
    for(int i = 1;i < cnt;i++){
        deg[i] = gg[i].size();
        if(deg[i] == 0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int v = q.front();
        q.pop();
        topsort.push_back(v);
        for(auto x : ggc[v]){
            deg[x]--;
            if(deg[x] == 0)
                q.push(x);
        }
    }
    for(int i = 1;i < cnt;i++){
        idx[topsort[i-1]] = i;
    }
    for(int i = 1;i <= m;i++){
        //cout << rep[i] << ' ' << rep[neg(i)] << '\n';
        if(idx[rep[i]] == idx[rep[neg(i)]]){
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }
    for(int i = 1;i <= m;i++){
        if(idx[rep[i]] < idx[rep[neg(i)]]){
            cout << "+ ";
        }
        else{
            cout << "- ";
        }
    }
    cout << '\n';
}
