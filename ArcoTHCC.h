


/**
 *  file --> ArcoTHCC.h
 *
 */

#ifndef _ARCOTHCC_H
#define _ARCOTHCC_H

#include <iostream>


using namespace std;

/**
 * Classe ArcoTHCC
 * Classe que define a cabeça a cauda custo e capacidade contido num arco na rede.
 */

class ArcoTHCC {

 protected:

    int mTail;          /**< Identificador do nó cauda do arco */
    int mHead ;         /**< Identificador do nó cabeça do arco */
    float mCost ;       /**< Custo do arco */
    float mTime;        /**< duracao do arco */
    float mDistance;    /**< distancia do arco */

 /**
  *  O arco deve ter sido definido e h > 0
  *  Altera a cabeça do arco ArcoTHCC
  */
  void SetHead( int head );

  /**
   *  O arco deve ter sido definido e t > 0
   *  Altera a cauda de um arco ArcoTHCC
   */
  void SetTail( int tail );

 public:

	/**
	*  Cria um arco vazio
	*/
	ArcoTHCC();

	/**
	*  t, h > 0;
	*  cost     <-- Custo do arco
	*  tempo <-- duracao do arco
	*  distancia <-- distancia do arco
	*  Cria o arco (t,h)
	*/
	ArcoTHCC( int tail , int head, float cost, float distancia, float tempo );

	/**
	*  Altera o custo do arco ArcoTHCC
	*/
	void SetCost( float custo );


	/**
	*  Retorna a identificação da cabeça de um ArcoTHCC
	*/
	int GetHead( ) const;

	/**
	*  Retorna a identificação da cauda de um ArcoTHCC
	*/
	int GetTail( ) const;

	/**
	*  Retorna o Custo dum arco (ArcoTHCC)
	*/
	float GetCost( ) const;

	/**
	*  Retorna o tempo do arco (ArcoTHCC)
	*/
	float GetTime( ) const;

	/**
	*  Retorna a distancia dum arco (ArcoTHCC)
	*/
	float GetDistance( ) const;

	/**
	*  O arco deve ter sido definido.
	*  Mostra o arco.
	*/
	void Mostra( );
};
#endif
