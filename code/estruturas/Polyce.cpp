
// https://codeforces.com/blog/entry/11080

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree <
  int,       // tipo da variavel
  null_type,
  less<int>, // funcao de comparacao(greater, less_equal,
  rb_tree_tag,
  tree_order_statistics_node_update > ordered_set;

void newSet() {
  // fuciona como um set normal, mas ha 2 funcoes especiais: log(n)
  ordered_set T;
  ordered_set ::iterator it;
  int k = *T.find_by_order(0); // retorna o K-esimo elemento segundo
                               // a funcao de comparacao
  int kk = T.order_of_key(0);  // retorna a posicao que um elemento
                               // encaixaria segundo a funcao de
                               // comparacao
}

#include <ext/rope>
using namespace __gnu_cxx;

void newVector() { 
  // funciona como um vector, mas consegue algo a mais: (log(n))
  rope<int> v;
  rope<int>::iterator it;
  int l, r; // segmento
  rope<int> cur = v.substr(l, r-l+1); // copia um segmento do vector
  v.erase(l, r - l + 1);              // apaga um segmento
  v.insert(v.mutable_begin(), cur);   // insere um segmento
  for (it = cur.mutable_begin(); it != cur.mutable_end(); it++)
    cout << *it << " ";               // percorre ele
}

int main() { return 0; }