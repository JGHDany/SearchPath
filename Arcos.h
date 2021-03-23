
/**
 *  file --> Arcos.h
 *
 */

#if !defined (_ARCOS_H)
#define _ARCOS_H

#include "ArcoTHCC.h"
#include "Nos.h"
#include <algorithm>
#include <map>

using namespace std;

class Arcos {



 public:

	struct ArcoFSF {
		int mHead;                /**< [k].mHead == cabeça(k) em FSF */
		int mTail;                /**< [k].mTail = cauda(k) em FSF */
		float mCost;              /**< [k].mCost == custo do arco k em FSF */
		float mDist;              /**< [k].mDist == dist do arco k em FSF */
		float mTime;              /**< [k].mTime== time do arco k em FSF */
	};


	/**
	*  Omission constructer (define null for all)
	*/
	Arcos();

	~Arcos();

	/**
	*	 FSF fase constructor whit implicit arcs
	*  Conta, number of diferent node existent in the vector rArcos.
	*/
	Arcos( vector<ArcoTHCC> & rArcos, int conta ) ;

	/**
	*	 FSF fase constructor whit implicit arcs
	*  Conta, number of diferent node existent in the vector rArcos.
	*
	*  Verify if s and t are conect, or exists an others node in the network that
	*  are disconect, and this node will be in the vector desconexo.
	*/
	Arcos(int origem, int destino, vector<ArcoTHCC> rArcos, int conta, bool &hacaminho );

	/**
	*  Dados dois nós i e j.
	*
	*  Retorna o arco k de origem i e destino j
	*              -1, se o arco não existe (e avisa do erro)
	*
	*/
	int GetArcoFSF( int i, int j );


	/**
	*  Dados dois nós i e j.
	*
	*  Retorna o arco k de origem i e destino j
	*              -1, se o arco não existe (e avisa do erro)
	*
	*/
	int GetArcoRSF( int i, int j );


	/**
	* Mostra as soluções
	*
	*/
	void MostraCaminho(int s, int t);


	/**
	* Obs: os arcos entre os nós já devem estar criados segundo segundo a estrurra
	*       Forward and reverse star form.
	*
	*/
	bool Dijkstra(int t, Nos &rGrafoNos, vector<int> &desconexo );

    /**
     * Obtem o valor do no segundo um dos criterios
     * custo, distancia ou tempo
     */
    float GetValueOfNo(int k, Nos &rGrafoNos,  int criterio);

    /**
     * Obtem o valor do no segundo um dos criterios
     * custo, distancia ou tempo
     */
    float GetValueOfArc(int k, int criterio);


	/** 26/05
    * Obs: os arcos entre os nós já devem estar criados segundo segundo a estrurra
    *      Forward and reverse star form.
    *
    */
    bool Dijkstra(int t, Nos &rGrafoNos, int criterio);

	/**
	*  O caminho mais curto segundo o número de saltos. (BFS)
	*
	*/
	bool BreadthFirstSearch(int s, int t, Nos &rGrafoNos);

	private:

	int n; /** n == número de nós do grafo (N), convenção  */
	int m; /** m == número de arcos do grafo (M), convenção. */

	/**  mTabInfoArcos tabela dos arcos em formato FSF
	*                mTabInfoArcos[k].mHead = cabeça(k)
	*                mTabInfoArcos[k].mTail = cauda(k)
	*                mTabInfoArcos[k].mCost = custo(k)
	*                mTabInfoArcos[k].mDistance = distance(k)
	*                mTabInfoArcos[k].mTime = Tempo(k)
	*/
	vector<struct ArcoFSF> mTabInfoArcos;


	//------------------
	// FORWARD STAR FORM
	//
	vector<int> mpFpont;   /**  k = fpont[i-1]...fpont[i]-1: cauda(k)=i */

	//------------------
	// REVERSE STAR FORM
	//
	vector<int> mpRpont;  /**  u = mpRpont[i-1]..-fpont[i]-1: cabeça(u)=i */

	/**
	*     mpTrace[u] = k
	*             Seja k (FSF) \in [fpont[i-1], fpont[i][
	*                 u /RSF) \in [mpRpont[j-1]..mpRpont[j][
	*             Então Se mpTrace[u] == k
	*                   Então tail[k] == i e head[k] == j
	*/
	vector<int> mpTrace;

	vector<int> mTeta;

};
#endif //_ARCOS_H
