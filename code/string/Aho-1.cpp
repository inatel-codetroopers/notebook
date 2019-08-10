const int cc = 26;
const int MAX = 100;

int cnt;
int sig[MAX][cc];
int term[MAX];
int T[MAX];
int v[MAX];

inline int C(char c) { return c - '0'; }

void add(string s, int id) {
  int x = 0;
  rep(i, 0, s.size()) {
    int c = C(s[i]);
    if (!sig[x][c]) {
      term[cnt] = 0;
      sig[x][c] = cnt++;
    }
    x = sig[x][c];
  }
  term[x] = 1;
  v[id] = x;
}

void aho() {
  queue<int> q;
  rep(i, 0, cc) {
    int x = sig[0][i];
    if (!x) continue;
    q.push(x);
    T[x] = 0;
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    rep(i, 0, cc) {
      int x = sig[u][i];
      if (!x) continue;
      int v = T[u];
      while (v && !sig[v][i]) v = T[v];
      v = sig[v][i];
      T[x] = v;
      term[x] += term[v];
      q.push(x);
    }
  }
}

// Conta a quantidade de palavras de exatamente l caracteres que se
// pode formar com um determinado alfabeto, dado que algumas palavras
// sao "proibidas"

int mod = 1e9 + 7;
ll pd[100][MAX];

ll solve(int pos, int no) {
  if (pos == 0) return 1;
  if (pd[pos][no] != -1) return pd[pos][no];
  ll ans = 0;
  rep(i, 0, cc) {
    int v = no;
    while (v && !sig[v][i]) v = T[v];
    v = sig[v][i];
    if (term[v]) continue;
    ans = (ans + solve(pos - 1, v)) % mod;
  }
  return pd[pos][no] = ans;
}

void Qttd_de_Palavras() {
  while (1) {
    memset(sig, 0, sizeof sig);
    memset(pd, -1, sizeof pd);
    cnt = 1;
    int l = readInt();
    if (!l) break;
    int n = readInt();
    string pattern;
    rep(i, 0, n) {
      cin >> pattern;
      add(pattern, i);
    }
    aho();
    ll ans = 0;
    rep(i, 1, l + 1) ans = (ans + solve(i, 0)) % mod;
    printf("%d\n", ans);
  }
}

// Verifica quais padroes ocorreram em um texto

int alc[MAX];

void busca(string s) {
  int x = 0;
  rep(i, 0, s.size()) {
    int c = C(s[i]);
    while (x && !sig[x][c]) x = T[x];
    x = sig[x][c];
    alc[x] = 1;
  }
}

void Ql_Ocorreu() {
  string pattern, text;
  while (getline(cin, text)) {
    if (text == "*") break;
    memset(sig, 0, sizeof sig);
    memset(alc, 0, sizeof alc);
    cnt = 1;
    int n;
    cin >> n;
    rep(i, 0, n) {
      cin >> pattern;
      add(pattern, i);
    }
    aho();
    busca(text);
    for (int i = cnt - 1; i >= 0; i--) {
      if (alc[i]) alc[T[i]] = 1;
    }
    rep(i, 0, n) {
      int u = v[i];
      if (alc[u])
        printf("Ocorreu\n");
      else
        printf("Nao ocorreu\n");
    }
  }
}

// Total de ocorrencias de cada padrao em uma string, mesmo com
// sufixos iguais
ll busca2(string s) {
  ll x = 0, cont = 0;
  rep(i, 0, s.size()) {
    int c = C(s[i]);
    while (x && !sig[x][c]) x = T[x];
    x = sig[x][c];
    cont += term[x];
  }
  return cont;
}

void Qnts_vezes_Ocorreu() {
  string text, pattern;
  while (cin >> text) {
    if (text == "*") break;
    memset(sig, 0, sizeof sig);
    cnt = 1;
    int n = readInt();
    rep(i, 0, n) {
      cin >> pattern;
      add(pattern, i);
    }
    aho();
    rep(i, 1, 10) debug(T[i]) cout << busca2(text) << endl;
  }
}

// Encontra a primeira ocorrencia de cada padrao em uma string
void busca3(string s) {
  int x = 0;
  rep(i, 0, s.size()) {
    int c = C(s[i]);
    while (x && !sig[x][c]) x = T[x];
    x = sig[x][c];
    if (!alc[x]) alc[x] = i + 1;
  }
}

void Onde_Ocorreu() {
  string pattern, text;
  int tam[1000];
  while (cin >> text) {
    if (text == "*") break;
    memset(sig, 0, sizeof sig);
    memset(alc, 0, sizeof alc);
    cnt = 1;
    int n;
    cin >> n;
    rep(i, 0, n) {
      cin >> pattern;
      tam[i] = pattern.size();
      add(pattern, i);
    }

    aho();
    busca3(text);
    for (int i = cnt - 1; i >= 0; i--) {
      alc[T[i]] = min(alc[i], alc[T[i]]);
    }
    rep(i, 0, n) {
      int u = v[i];
      if (alc[u] != INF) {
        int k = alc[u] - tam[i] + 1;
        printf("De %d a %d\n", k, alc[u]);
      } else
        printf("Nao ocorreu\n");
    }
  }
}
