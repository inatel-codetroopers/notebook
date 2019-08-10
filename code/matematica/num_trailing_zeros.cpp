// Determina o numero de zeros a direita do fatorial de N na base B
// Ideia: Se a base for B for 10, e fatorarmos N! em fatores primos
// teremos algo como N! = 2^a * 3^b * 5^c ..., como cada par de primos
// 2 e 5 formam 10 que tem um zero, a quantidade seria min(a, c).
int NumOfTrailingZeros(int N, int B) {
  int nfact = fatora(B);
  int zeros = INF;
  // para cada fator de B, aux representa qtas vezes
  // fator[i]^expoente[i] aparece na representacao de N!
  for (int i = 0; i < nfact; i++) {
    int soma = 0;
    int NN = N;
    while (NN) {
      soma += NN / fator[i];
      NN /= fator[i];
    }
    int aux = soma / expoente[i];
    zeros = min(zeros, aux);
  }
  return zeros;
}