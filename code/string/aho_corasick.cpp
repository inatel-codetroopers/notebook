const int cc = 26;
const int MAX = 100; // Tamanho maximo das somas das strings

int cnt; // Tamanho da Trie em numero de nos
int sig[MAX][cc];
int term[MAX]; // Nos terminais
int T[MAX];    // Maior prefixo que rh sufixo de cada no
int v[MAX];    // Vetor que indica qual posicao da Trie cada string
               // termina

inline int C(char c) { return c - 'a'; }

// Montando a Trie
void add(string s, int id) {
  int x = 0; // raiz
  rep(i, 0, s.size()) {
    int c = C(s[i]);
    if (!sig[x][c]) {    // No nao existente
      term[cnt] = 0;     // e ele ainda nao eh terminal
      sig[x][c] = cnt++; // Cria o no e incrementa cnt
    }
    x = sig[x][c];
  }
  term[x] = 1; // Ultima posicao da string, logo um no terminal
  v[id] = x;   // Salva no vetor onde, na Trie, termina a string
}

// Aho-Corasick
void aho() {
  queue<int> q;
  rep(i, 0, cc) {
    int x = sig[0][i]; // saindo da raiz
    if (!x)
      continue;
    q.push(x); // Joga na fila cada no existente e vizinho da raiz
    T[x] = 0;  // Maior prefixo-sufixo de uma unica letra eh a raiz
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    rep(i, 0, cc) {      // Verifica verifica a existencia de nos para
      int x = sig[u][i]; // cada valor do alfabeto saindo do no u
      if (!x)
        continue;
      int v = T[u]; // No inicio v eh o maior prefixo e sufixo de u
      while (v && !sig[v][i])
        v = T[v]; // Testa para todo v se tambem pode ser
                  // prefixo-sufixo de x
      // Se dirige a posicao do maior prefixo-sufixo de x
      v = sig[v][i];
      T[x] = v; // Salva que o maior prefixo-sufixo de x eh o no v
      term[x] += term[v]; // Se v eh terminal e sufixo de x,
      q.push(x);          // x tambem sera terminal
    }
  }
}

int init() {
  memset(sig, 0, sizeof sig);
  cnt = 1;
}