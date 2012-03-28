//Complejidad: O(V^3)
//No funciona si hay ciclos de peso negativo
// g[i][j] = Distancia entre el nodo i y el j.
unsigned long long g[MAXNODES][MAXNODES];
void floyd(int n){
  //Llenar g antes
  for (int k=0; k<n; ++k){
    for (int i=0; i<n; ++i){
      for (int j=0; j<n; ++j){
        g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
      }
    }
  }
  //Acá se cumple que g[i][j] = Longitud de la ruta más corta
  //de i a j.
}

/**
 * Aplicaciones de FW.
 *
 * Maxi-min:  Encontrar el camino donde la arista más pequeña del camino es
 *            la más grande (entre las más pequeñas) - que el sitio más ruidoso
 *            sea el más tranquilo
 *            g[i][j] = max(g[i][j], min(g[i][k], g[k][j]))
 *
 * Mini-max:  Encontrar el camino donde la arista más grande del camino es
 *            la más pequeña (entre las más grandes) - que el peaje más caro,
 *            sea el más barato.
 *            g[i][j] = min(g[i][j], max(g[i][k], g[k][j]))
 *
 *
 * Ciclo Neg: Si hay un ciclo negativo, g[i][i] < 0 para algún i
 *
 * Safest Path: Maximizar la probabilidad de "sobrevivir" por algún camino. Los valores son porcentajes!
 *              g[i][j] = max(g[i][j], g[i][k] * g[k][j]);
 *
 *
 * Clausura Transitiva: Decir si se puede llegar de un nodo al otro:
 *              g[i][j] = g[i][j] || (g[i][k] && g[k][j])
**/