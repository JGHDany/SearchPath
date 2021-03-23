/**
 *  file --> Network.h
 */

#if !defined (_NETWORK_H)
#define _NETWORK_H

#include "ArcoTHCC.h"
#include "Arcos.h"
#include "Nos.h"

#include <string>
#include <map>
using namespace std;

  /**
   * Classe Principal para a constru��o da rede(Nos e Arcos).
  */
class Network : Arcos {
    private:
      vector<int> mNetNode;
      vector<ArcoTHCC> mNetArcs;
   public:

    /**
     *  Constructor da rede a partir de um ficheiro
     *  Extrai a informa��o a partir de um ficheiro e constroi a rede.
     */
	Network( char *fileGraph );

    /**
     * auxArcos <-- Devolve um vector com os arcos mapeados para o algoritmo de rotula��o
     * auxNos   <-- Devolve um vector de n�s mapaedos.
     *
     */
	void MapearInfo(int tipo, vector<int> &tabNos, vector<ArcoTHCC> &tabArcos, map<int,int> &Mapa);

	/**
	*  esta fun��o tem a finalidade de ver se s e t interligam entre si e apagar da rede os n�s
	*  subrafos desconexos entre s e t.
	*/
	bool NetworkConstruct(int &origem, int &destino, int tipo, vector<ArcoTHCC> &tabArcos, vector<int> &tabNos,
							 map<int,int> &Mapa );

	/**
	*  CaminhoSt <-- Sequencia de n�s do pedido que deve ser traduzida para a
	*  identifica��o dos n�s originais.
	*/
	void  TraduzDados( vector<int> &CaminhoSt, vector<int> tabNos  );

    /**
	* Mostra a informa��o da rede.
	*/
	void Mostra();

};
#endif //_NETWORK_H
