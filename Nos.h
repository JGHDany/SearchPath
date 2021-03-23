
/**
 *  file --> Nos.h
 *
 */

#if !defined (_NOS_H)
#define _NOS_H

const int MAX_INT = 147483647;//0x7FFFFFFF; // 2147483647; // 32 bits

#include <cstdio>
#include <fstream>
#include <iostream>
#include <fstream>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstdio>

using namespace std;

  /**
   * Classe com a informação dos nós da rede
  */
  class Nos{

  public:
    //Informação requerida para cada nó da rede
    struct No{
      float mPesoNo;         /**< Custo actual do trajecto de s para i */
      float mDistance;       /**< Distância actual do trajecto de s para i */
      float mTime;           /**< tempo actual do trajecto de s para i */
      int mPredecessorNo;    /**< Nó que antecede i na árvore dos caminhos mais curtos */
      int mAltura;           /**< Altura do nó na árvore dos caminhos mais curtos para t (conta o numero de arcos)*/
    };
   private:
    //tabela dos nos da rede
	vector<No> mpTabNos;

   public:
	    int mpLivre;   /**< primeira posição livre de mpTabNos. */

	/**
	*  Constructor da classe Nós
	*  Reserva espaço para a tabela com informação dos nós
	*  e as variaveis
	*  mMaxNos <- maximo de nós na rede
	*  mpLivre <- posições livres na tabela dos nós.
	*/
	Nos(int n);

	/**
	*  Deve existir um objecto definido.
	*  Assigment (Atribuição!)
	*  Faz uma atribuição de um objecto do tipo No par T.
	*/
	Nos& operator=(const Nos & rT);


	/**   Dado a posição (e id) de um nó em mpTabNos,
	*     Retorna
	*          true, se conseguiu alterar os campos do nó na tabela mpTabNos
	*               com sucesso.
	*          false, se o nó s estiver fora da tabela mpTabNos.
	*/
	bool InicializaNos( int i );

	/**
	*  Dado a posição (e id) de um nó em mpTabNos,
	*  Retorna o valor do campo mPesoNoI do nó na arvore de caminhos mais curto
	*/
	float GetChave( int i );


    /**
	*  Dado a posição (e id) de um nó em mpTabNos,
	*  Retorna o valor do campo mDistance do nó na arvore de caminhos mais curto
	*/
	float GetDistance( int i );

	 /**
	*  Dado a posição (e id) de um nó em mpTabNos,
	*  Retorna o valor do campo mTime do nó na arvore de caminhos mais curto
	*/
	float GetTime( int i );

	/**
	* Dado a posição (e id) de um nó em mpTabNos,
	* Retorna o valor do campo mPredecessorNoI do nó na arvore de caminhos mais curto
	*/
	int GetPredecessor( int i );

	/**   Dado a posição (e id) de um nó em mpTabNos,
	*     Retorna o valor do campo altura do nó na arvore de caminhos mais curto
	*/
	int GetAltura( int i );

	/**
	* Dado a posição (e id) de um nó em mpTabNos,
	* Retorna o valor do campo mCapacidadeI do nó na arvore de caminhos mais curto
	*/
	int GetCapacity( int i );

    /**
    *  Dado i, posição e (id) do nó na tabela dos nós mpTabNos
    *       peso, novo peso do nó na arvore de caminhos mais curto, segundo
    *            o algoritmo de rotulação,
    *       capacity, capacidade do nó na arvore de caminhos mais curto
    *       pred, predecessor do nó i na arvore de caminhos mais curto.
    *       alt, altura do nó na arvore de caminho mais curto.
    *       Actualiza um no segundo um criterio (custo distancia ou tempo)
    */
    void ActualizeNode( int i, float valor, int pred, int alt, int crit);

	/**
	*  BFS
	*/
	void ActualizeNode(int i, int pred, int alt);

    /**
     * Obtem o valor do no segundo um dos criterios
     * custo, distancia ou tempo
     */
    float GetValueOfNo(int k, int criterio);

    /**
    *  Dado s e t (origem e destino do pedido) e o criterio da escolha do caminho
    *
    *  Retorna true, se conseguir encontrar um trajecto mais curto de s para t
    *  Devolve em CaminhoSt <-- A sequencia de nós no trajecto entre s e t.
    *  devolve em saltos <-- o número de saltos conseguido no trajecto mais custo
    */
    bool GetCaminho( int s, int t, int crit, vector<int> & CaminhoSt,  float &valorCam );

};
#endif // _NOS_H
