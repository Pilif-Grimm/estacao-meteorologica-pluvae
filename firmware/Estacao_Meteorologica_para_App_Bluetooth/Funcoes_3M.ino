/*
 * Colocar aqui as funções nescessárias para calcular a média, mediana e moda.
 * Incluindo funções para organizar os vetores
 */

// Função para copiar um vetor:
void copy(int* src, int* dst, int len) {
  // Serial.print(" copy complete ");
  memcpy(dst, src, sizeof(src[0])*len);
}

// Função para ordenar um vetor em ordem crescente:
void isort(int *a, int n)
{
  for (int i = 1; i < n; ++i)
  {
    int j = a[i];
    int k;
    for (k = i - 1; (k >= 0) && (j < a[k]); k--)
    {
      a[k + 1] = a[k];
    }
    a[k + 1] = j;
  }
  // Serial.println(" sort complete ");
}
// Função para ordenar um vetor float
void isort_f(float *a, int n)
{
  for (int i = 1; i < n; ++i)
  {
    float j = a[i];
    int k;
    for (k = i - 1; (k >= 0) && (j < a[k]); k--)
    {
      a[k + 1] = a[k];
    }
    a[k + 1] = j;
  }
  // Serial.println(" sort complete ");
}

// Função para calcular a moda do vetor já ordenado:
int calculateMode(int *sortedQ, int numItems) {
  int modeCt = 0;
  int modeV = -1;

  int ct = 0;
  int v = -1;

  for(int i = 0; i< numItems; i++) {
    if(sortedQ[i] != v) {
      v = sortedQ[i];
      ct = 0;
    }

    ct ++;

    if(ct > modeCt) {
      modeCt = ct;
      modeV = v;
    }
  }
  /*
  Serial.print("   ");
  Serial.print("mode: ");
  Serial.print(modeV);
  Serial.print(" count: ");
  Serial.println(modeCt);
  */
  return modeV;
}

// Função para calcular a Mediana
