/**
 *  file --> ArcoTHCC.cpp
 */

#include "ArcoTHCC.h"

/**
 *  Cria o arco vazio
 */
ArcoTHCC::ArcoTHCC(){}

/**
 *  t, h > 0;
 *  cost     <-- Custo do arco
 *  tempo <-- duracao do arco
 *  distancia <-- distancia do arco
 *  Cria o arco (t,h)
 */
ArcoTHCC::ArcoTHCC( int tail , int head, float cost, float distancia, float tempo ){
    mTail = tail;
    mHead = head ;
    mCost = cost ;
    mTime = tempo;
    mDistance = distancia;
}

/**
 *  O arco deve ter sido definido e h > 0
 *  Altera a cabeça do arco ArcoTHCC
 */
void ArcoTHCC::SetHead( int head ){ mHead = head; }

/**
 *  O arco deve ter sido definido e t > 0
 *  Altera a cauda de um arco ArcoTHCC
 */
void ArcoTHCC::SetTail( int tail ){ mTail = tail; }

/**
 *  Altera o custo do arco ArcoTHCC
 */
void ArcoTHCC::SetCost( float custo ){ mCost = custo; }

/**
 *  Retorna a identificação da cabeça de um ArcoTHCC
 */
int ArcoTHCC::GetHead( ) const { return mHead ;}

/**
 *  Retorna a identificação da cauda de um ArcoTHCC
 */
int ArcoTHCC::GetTail( ) const{ return mTail ;}

/**
 *  Retorna o Custo dum arco (ArcoTHCC)
 */
float ArcoTHCC::GetCost( ) const{ return mCost ;}

/**
 *  Retorna o tempo do arco (ArcoTHCC)
 */
float  ArcoTHCC::GetTime( ) const{ return mTime;}

/**
 *  Retorna a distancia dum arco (ArcoTHCC)
 */
float  ArcoTHCC::GetDistance( ) const{ return mDistance;}

/**
 *  O arco deve ter sido definido.
 *  Mostra o arco.
 */
void ArcoTHCC::Mostra( ){
    cout << "\n( "<< mTail << " , " <<  mHead << " ) com mCusto = " << mCost << flush ;
}
