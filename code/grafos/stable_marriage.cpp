/*Seja um conjunto de m homens e n mulheres, onde cada pessoa tem uma
preferencia por outra de sexo oposto. O algoritmo produz o casamento
estavel de cada homem com uma mulher. Estavel:
- Cada homem se casara com uma mulher diferente (n >= m)
- Dois casais H1M1 e H2M2 nao serao instaveis.
Dois casais H1M1 e H2M2 sao instaveis se:
- H1 prefere M2 ao inves de M1, e
- M1 prefere H2 ao inves de H1.
Entrada
(1) m = #homens, n = #mulheres
(2) R[x][y] = i, i: eh a ordem de preferencia do homem y pela mulher x
Obs.: Quanto maior o valor de i menor eh a preferencia do homem y pela
mulher x

(3) L[x][i] = y : A mulher y eh a i-esima preferencia do homem x
Obs.: 0 <= i <= n-1, quanto menor o valor de i maior eh a preferencia
do homem x pela mulher y
Saida
L2R[i]: a mulher do homem i (sempre entre 0 e n-1)
R2L[j]: o homem da mulher j (-1 se a mulher for solteira)

Complexidade O(m^2)
*/
#define MAXM 1000
#define MAXW 1000
int L[MAXM][MAXW];
int R[MAXW][MAXM];
int L2R[MAXM], R2L[MAXW];
int m, n;
int p[MAXM];

void stableMarriage() {
  static int p[MAXM];
  memset(R2L, -1, sizeof(R2L));
  memset(p, 0, sizeof(p));
  for (int i = 0; i < m; ++i) {
    int man = i;
    while (man >= 0) {
      int wom;
      while (42) {
        wom = L[man][p[man]++];
        if (R2L[wom] < 0 || R[wom][man] > R[wom][R2L[wom]]) break;
      }
      int hubby = R2L[wom];
      R2L[L2R[man] = wom] = man;
      man = hubby;
    }
  }
}

int main() { return 0; }