
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
   * Classe com a informa��o dos n�s da rede
  */
  class Nos{

  public:
    //Informa��o requerida para cada n� da rede
    struct No{
      float mPesoNo;         /**< Custo actual do trajecto de s para i */
      float mDistance;       /**< Dist�ncia actual do trajecto de s para i */
      float mTime;           /**< tempo actual do trajecto de s para i */
      int mPredecessorNo;    /**< N� que antecede i na �rvore dos caminhos mais curtos */
      int mAltura;           /**< Altura do n� na �rvore dos caminhos mais curtos para t (conta o numero de arcos)*/
    };
   private:
    //tabela dos nos da rede
	vector<No> mpTabNos;

   public:
	    int mpLivre;   /**< primeira posi��o livre de mpTabNos. */

	/**
	*  Constructor da classe N�s
	*  Reserva espa�o para a tabela com informa��o dos n�s
	*  e as variaveis
	*  mMaxNos <- maximo de n�s na rede
	*  mpLivre <- posi��es livres na tabela dos n�s.
	*/
	Nos(int n);

	/**
	*  Deve existir um objecto definido.
	*  Assigment (Atribui��o!)
	*  Faz uma atribui��o de um objecto do tipo No par T.
	*/
	Nos& operator=(const Nos & rT);


	/**   Dado a posi��o (e id) de um n� em mpTabNos,
	*     Retorna
	*          true, se conseguiu alterar os campos do n� na tabela mpTabNos
	*               com sucesso.
	*          false, se o n� s estiver fora da tabela mpTabNos.
	*/
	bool InicializaNos( int i );

	/**
	*  Dado a posi��o (e id) de um n� em mpTabNos,
	*  Retorna o valor do campo mPesoNoI do n� na arvore de caminhos mais curto
	*/
	float GetChave( int i );


    /**
	*  Dado a posi��o (e id) de um n� em mpTabNos,
	*  Retorna o valor do campo mDistance do n� na arvore de caminhos mais curto
	*/
	float GetDistance( int i );

	 /**
	*  Dado a posi��o (e id) de um n� em mpTabNos,
	*  Retorna o valor do campo mTime do n� na arvore de caminhos mais curto
	*/
	float GetTime( int i );

	/**
	* Dado a posi��o (e id) de um n� em mpTabNos,
	* Retorna o valor do campo mPredecessorNoI do n� na arvore de caminhos mais curto
	*/
	int GetPredecessor( int i );

	/**   Dado a posi��o (e id) de um n� em mpTabNos,
	*     Retorna o valor do campo altura do n� na arvore de caminhos mais curto
	*/
	int GetAltura( int i );

	/**
	* Dado a posi��o (e id) de um n� em mpTabNos,
	* Retorna o valor do campo mCapacidadeI do n� na arvore de caminhos mais curto
	*/
	int GetCapacity( int i );

    /**
    *  Dado i, posi��o e (id) do n� na tabela dos n�s mpTabNos
    *       peso, novo peso do n� na arvore de caminhos mais curto, segundo
    *            o algoritmo de rotula��o,
    *       capacity, capacidade do n� na arvore de caminhos mais curto
    *       pred, predecessor do n� i na arvore de caminhos mais curto.
    *       alt, altura do n� na arvore de caminho mais curto.
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
    *  Devolve em CaminhoSt <-- A sequencia de n�s no trajecto entre s e t.
    *  devolve em saltos <-- o n�mero de saltos conseguido no trajecto mais custo
    */
    bool GetCaminho( int s, int t, int crit, vector<int> & CaminhoSt,  float &valorCam );

};
#endif // _NOS_H
