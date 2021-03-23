
/**
 *  file --> Nos.cpp
 */

#include "Nos.h"

/**
*  Constructor da classe Nós
*  Reserva espaço para a tabela com informação dos nós
*  e as variáveis
*  mMaxNos <- máximo de nós na rede
*  mpLivre <- posições livres
*/
Nos::Nos( int n ){

	mpTabNos.resize(n+1);

	if( mpTabNos.size() == 0 ) {
		cerr << "\nERROR: Nos::Nos( int n )";
		cerr << "\n       Não foi posível reservar " << n+1 << " Nos!\n";
		exit( 1 );
	}
	mpLivre = n+1;    // Não há posições livres
}

/**
*     Dado a posição (e id) de um nó em mpTabNos,
*
*     Retorna
*          true, se conseguiu alterar os campos do nó na tabela mpTabNos
*               com sucesso.
*          false, se o nó s estiver fora da tabela mpTabNos.
*/
bool Nos::InicializaNos( int t ){

	if( t > mpLivre ){
		cerr << "\nERROR: void Nos::InicializaNos( int t )";
		cerr << "\n       O nó " <<t << " não está ";
		cerr << "na tabela (1.."<< mpLivre-1 << ")!\n" << flush ;
		return false;
	}
	// Coloca o peso dos caminhos de i para s todos a MAX_INT
	// e com nó anterior desconhecido
	// capacidade zero(0).
	//
	for( int i = 1; i < mpLivre; i++ ){
		mpTabNos[i].mPesoNo = MAX_INT;
		mpTabNos[i].mPredecessorNo = -1;
		mpTabNos[i].mAltura = 0;
		mpTabNos[i].mDistance = MAX_INT;
		mpTabNos[i].mTime = MAX_INT;
	};

	// O caminho mais curto de s para para s tem comprimento 0
	mpTabNos[t].mPesoNo = 0;
	mpTabNos[t].mDistance = 0;
	mpTabNos[t].mTime = 0;
	//  t é o nó que antecede t nesse caminho
	mpTabNos[t].mPredecessorNo = t;
	//  a sua distância a a si próprio é 0
	mpTabNos[t].mAltura = 0;

	return true;
}


/**
*     Dado a posição (e id) de um nó em mpTabNos,
*     Retorna o valor do campo mPesoNoI do nó na arvore de caminhos mais curto
*/
float Nos::GetChave( int i ){
  return  mpTabNos[i].mPesoNo;
}

/**
*  Dado a posição (e id) de um nó em mpTabNos,
*  Retorna o valor do campo mDistance do nó na arvore de caminhos mais curto
*/
float Nos::GetDistance( int i ){
     return  mpTabNos[i].mDistance;

}

/**
*  Dado a posição (e id) de um nó em mpTabNos,
*  Retorna o valor do campo mTime do nó na arvore de caminhos mais curto
*/
float Nos::GetTime( int i ){
    return  mpTabNos[i].mTime;
}

/**
*     Dado a posição (e id) de um nó em mpTabNos,
*     Retorna o valor do campo mPredecessorNoI do nó na arvore de caminhos mais curto
*/
int Nos::GetPredecessor( int i ){
  return  mpTabNos[i].mPredecessorNo;
}

/**
*     Dado a posição (e id) de um nó em mpTabNos,
*     Retorna o valor do campo altura do nó na arvore de caminhos mais curto
*/
int Nos::GetAltura( int i ){
  return  mpTabNos[i].mAltura;
}


/**
*  Dado i, posição e (id) do nó na tabela dos nós mpTabNos
*       peso, novo peso do nó na arvore de caminhos mais curto, segundo
*            o algoritmo de rotulação,
*       capacity, capacidade do nó na arvore de caminhos mais curto
*       pred, predecessor do nó i na arvore de caminhos mais curto.
*       alt, altura do nó na arvore de caminho mais curto.
*       Actualiza um no segundo um criterio (custo distancia ou tempo)
*/

void Nos::ActualizeNode( int i, float valor, int pred, int alt, int crit){
    if( i < mpLivre ){
        switch(crit){
            case 1: mpTabNos[i].mPesoNo = valor;//criterio custo
            break;
            case 2: mpTabNos[i].mDistance = valor;//criterio distancia
            break;
            case 3: mpTabNos[i].mTime = valor;//criterio tempo
            break;
            default: cout<<"ERRO: Criterio indefinido!!!";
        }
        mpTabNos[i].mPredecessorNo = pred;
        mpTabNos[i].mAltura = alt;
    }else{
        cerr << "\nErro em ActualizeNode: no "<< i << " fora da tabela de nós!\n";
        exit( 1 );
    }
}

/**
*  BFS
*/
void Nos::ActualizeNode(int i, int pred, int alt){

	if( i < mpLivre ){
		mpTabNos[i].mPredecessorNo = pred;
		mpTabNos[i].mAltura = alt;
	}else{
		cerr << "\nErro em AlteraCampos: no "<< i << " fora da tabela de nós!\n";
		exit( 1 );
	}
}


/**
 * Obtem o valor do no segundo um dos criterios
 * custo, distancia ou tempo
 */
float Nos::GetValueOfNo(int k, int criterio){

    switch(criterio){
        case 1: return mpTabNos[k].mPesoNo;     //o criterio e' o custo
        break;
        case 2: return mpTabNos[k].mDistance;  //o criterio e' a distancia
        break;
        case 3: return mpTabNos[k].mTime;      //o criterio e' o tempo
        break;
    }
}

/**
*  Dado s e t (origem e destino do pedido) e o criterio da escolha do caminho
*
*  Retorna true, se conseguir encontrar um trajecto mais curto de s para t
*  Devolve em CaminhoSt <-- A sequencia de nós no trajecto entre s e t.
*  devolve em saltos <-- o número de saltos conseguido no trajecto mais custo
*/
bool Nos::GetCaminho( int s, int t, int crit, vector<int> & CaminhoSt,  float &valorCam ){

	//MostraCaminho(t);
	if( ( s < mpLivre ) && (t < mpLivre)  && (0 < s ) && (0 < t ) ) {

        CaminhoSt.push_back( 0 );

		if( mpTabNos[s].mPesoNo == MAX_INT && mpTabNos[s].mAltura == 0 ){
			//cerr << "\n Não existe caminho do nó ";
			//cerr <<s<< " para o nó " << t << "\n";
			return false;
		}else{
			CaminhoSt.push_back( s );
			//cout<<" p = < "<< s;
			int j;
			for(  j = 1; CaminhoSt[j] != t ; j++ ){
				//cout<<" -> "<< mpTabNos[CaminhoSt[j]].mPredecessorNo;
				//int no =  mpTabNos[CaminhoSt[j]].mPredecessorNo;
				//CaminhoSt.push_back( mpTabNos[no].mCorresp );
				CaminhoSt.push_back( mpTabNos[CaminhoSt[j]].mPredecessorNo );
			}
			CaminhoSt[0]= j;
			//saltos = j-1;
			valorCam = GetValueOfNo(s, crit); // mpTabNos[s].mPesoNo;
			//capacidade = mpTabNos[s].mCapacity;
            //cout<<" custo ("<<valorCam<<") \n\n"<<endl;
		}
		if( mpTabNos[t].mPesoNo != MAX_INT ) return true;
		else return false;
	}

	return false;
}
