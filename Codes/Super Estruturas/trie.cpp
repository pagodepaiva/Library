// Link: https://www.spoj.com/problems/ADAINDEX/

#include<bits/stdc++.h>

using namespace std;

struct Trie{
    Trie *c[26];
    int val;
    Trie(){
        for(int i = 0;i < 26;i++) c[i] = NULL;
        val = 0;
    }
    void add(string &s){
        if(s.empty()){
            val++;
            return;
        }
        int pos = s.back() - 'a';
        s.pop_back();
        if(!c[pos]) c[pos] = new Trie();
        val -= c[pos]->val;
        c[pos]->add(s);
        val += c[pos]->val;
        return;
    }
    int query(string &s){
        if(s.empty()){
            return val;
        }
        int pos = s.back()-'a';
        s.pop_back();
        if(!c[pos]) return 0;
        return c[pos]->query(s);
    }
} node;

int main(){
    int n, q;
    cin >> n >> q;
    for(int i = 0;i < n;i++){
        string s;
        cin >> s;
        reverse(s.begin(), s.end());
        node.add(s);
    }
    for(int i = 0;i < q;i++){
        string s;
        cin >> s;
        reverse(s.begin(), s.end());
        cout << node.query(s) << '\n';
    }
    return 0;
}
