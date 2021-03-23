
#if !defined (_BINARIA_H)
#define _BINARIA_H

#include <vector>
#include "ArcoTHCC.h"

//==============================================================================
//  class Compara--------------  Definição dos métodos -------------------------
//==============================================================================
/** Classe Compara
 * Compara dois objectos diferentes e retorna true  <-- se objecto a é menor que
 * objecto b. false <-- se objecto a é maior ou igual que objecto b, caso sejam
 * iguais devolve na variável igual == true.
 *
 * OBS: Os objectos a e b devem ser do mesmo tipo.
*/

class Compara{
 public:
  /**
  	*  Existe pelo menos dois objectos da classe ArcoTHCC definidos,com
  	*  identificação de ( tail , head )  de ordem  diferentes.
  	*  Se dois arcos tiverem a mesma cauda, então compara as cabeças
  	*  Senão compara as caudas.
  	*
  	*  Retorna um valor boleano de acordo com os valores do head e do tail
  	*  entre dois arcos comparados.
  	*
  	*  true  <-- se as caudas dos arcos rX e rY forem iguais e cabeça de do
  	*            arco rX for menor que cabeça do arco rY, ou
  	*            Se a cauda de rX for menor que a cauda de rY.
  	*
  	*  false <-- Se as caudas dos arcos forem iguais e cabeça de rX é maior
  	*            que cabeça de rY , ou
  	*            Se cauda do arco rX for maior que a cauda de rY.
  	*  rIgual == true se o arco rX é rIgual a  arco rY.
  	*/
    bool operator()( const ArcoTHCC& rX, const ArcoTHCC& rY , bool & rIgual) const {
        rIgual = false;
        if( rX.GetTail() == rY.GetTail() )
            if( rX.GetHead() > rY.GetHead() ) return false;
            else if((rX.GetHead() == rY.GetHead())&&(rX.GetCost() == rY.GetCost())&&
                    (rX.GetTime() == rY.GetTime())&&(rX.GetDistance() == rY.GetDistance())){
                        rIgual = true; return false;
            }else return true;
        else if( rX.GetTail() > rY.GetTail() ) return false;
        else return true;
    }
};

using namespace std;

template<class T, class Compara>

int Binaria( const vector<T> & rV, const T & rVal, Compara cmp, bool & rExiste){

	rExiste = false ; // Por omissão considera-se que não rExiste -rVal- em -rpV-
	int inic = 0;
	int dim = rV.size();
	int fim = dim - 1 ;
	int i ; //Estado da pesquisa (ponto médio)
	if( dim > 0 ){
		do {  // Pesquisa binária  para sistema ordenado
			i = (fim + inic)/2;
			if( cmp( rVal, rV[i] , rExiste) ) fim = i - 1  ; // se rVal < rV[i]
			else inic = i + 1 ;                              // Se rVal >= rV[i]
		}while (inic <= fim && !rExiste);
		if( rExiste )
			return i;
		else return inic;
	}
	else return 0 ;
};
#endif
