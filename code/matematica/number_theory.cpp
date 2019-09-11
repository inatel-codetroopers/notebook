// Encontra os fatores primos de N .: N = p1^e1 * ... *pi^ei
// factors armazena em first o fator primo e em segundo seu expoente
map<int, int> factors;
void primeFactors(ll N) {
  factors.clear();
  while (N % 2 == 0)
    ++factors[2], N >>= 1;
  for (ll PF = 3; PF * PF <= N; PF += 2) {
    while (N % PF == 0)
      N /= PF, factors[PF]++;
  }
  if (N > 1)
    factors[N] = 1;
}

// Funcoess derivadas dos numeros primos
void NumberTheory(ll N) {
  primeFactors(N);
  map<int, int>::iterator f; // iterador
  ll Totient = N;            // Totiente ou Euler-Phi de N
  // Totient(N) = qtos naturais x, tal que x < N && gcd(x,N) == 1
  ll numDiv = 1; // Quantidade de divisores de N
  ll sumDiv = 1; // Soma dos divisores de N
  ll sumPF = 0;  // Soma dos fatores primos de N (trivial)
  ll numDiffPF = factors.size(); // qtde de fatores distintos

  for (f = factors.begin(); f != factors.end(); f++) {
    ll PF = f->first, power = f->second;
    Totient -= Totient / PF;
    numDiv *= (power + 1);
    sumDiv *= ((ll)pow((double)PF, power + 1.0) - 1) / (PF - 1);
    sumPF += PF;
  }

  printf("Totiente/Euler-Phi de N = %lld\n", Totient);
  printf("qt de divisores de N = %lld\n", numDiv);
  printf("soma dos divisores de N = %lld\n", sumDiv);
  printf("qt de fatores primos distintos = %lld\n", numDiffPF);
  printf("soma dos fatores primos = %lld\n", sumPF);
}

// Calcula Euler Phi para cada valor do intervalo [1, N]
#define MM 1000010
int phi[MM];
void crivo_euler_phi(int N) {
  for (int i = 1; i <= N; i++)
    phi[i] = i;
  for (int i = 2; i <= N; i++)
    if (phi[i] == i) {
      for (int k = i; k <= N; k += i)
        phi[k] = (phi[k] / i) * (i - 1);
    }
}

// Qtde de fatores primos distintos de cada valor do range [2, MAX_N]
#define MAX_N 10000000
int NDPF[MAX_N]; //
void NumDiffPrimeFactors() {
  memset(NDPF, 0, sizeof NDPF);
  for (int i = 2; i < MAX_N; i++)
    if (NDPF[i] == 0)
      for (int j = i; j < MAX_N; j += i)
        NDPF[j]++;
}

int main() { return 0; }
