// obs: A funcao strstr (char* text, char* pattern) da biblioteca
// <cstring> implementa KMP (C-ANSI). A funcao retorna a primeira
// ocorrencia do padrao no texto, KMP retorna todas.  nres -> O numero
// de ocorrencias do padrao no texto res[] -> posicoes das nres
// ocorrencias do padrao no texto Complexidade do algoritmo: O(n+m)*/

#define MAXN 100001
int pi[MAXN], res[MAXN], nres;
void kmp(string text, string pattern) {
  nres = 0;
  pi[0] = -1;
  rep(i, 1, pattern.size()) {
    pi[i] = pi[i - 1];
    while (pi[i] >= 0 && pattern[pi[i] + 1] != pattern[i])
      pi[i] = pi[pi[i]];
    if (pattern[pi[i] + 1] == pattern[i]) ++pi[i];
  }
  int k = -1;  // k+1 eh o tamanho do match atual
  rep(i, 0, text.size()) {
    while (k >= 0 && pattern[k + 1] != text[i]) k = pi[k];
    if (pattern[k + 1] == text[i]) ++k;
    if (k + 1 == pattern.size()) {
      res[nres++] = i - k;
      k = pi[k];
    }
  }
}