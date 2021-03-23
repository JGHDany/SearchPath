
/**
 *  file --> Arcos.cpp
 */

#include "Arcos.h"
#include "binaria.h"

/**
*  Construtor por omiss�o (assinala tudo vazio)
*/

Arcos::Arcos(){
 //n = m = 0;
}
/**
* destrutor que limpa todos os vectores. RSP FSP
*/
Arcos::~Arcos(){
	mTabInfoArcos.clear();
	mpFpont.clear();
	mpRpont.clear();
	mpTrace.clear();

}

/**
*  Construtor com fase em FSF impl�cita em rArcos.
*  Conta, indica o n�mero de n�s diferentes existentes em rArcos.
*/
Arcos::Arcos( vector<ArcoTHCC> & rArcos, int conta ){

	// Dimens�o da rede
	n = conta ;
	m = rArcos.size() ;

	if( m == 0  ) return;

	mTabInfoArcos.resize(m+1);
	// Reserva espa�o para a Forward Star Form
	mpFpont.resize(n+1);
	// Reserva espa�o para a Reverse Star Form
	mpTrace.resize(m+1);

	mpRpont.resize(n+1);


	int i, k, a, b;

  mpFpont[0] = mpRpont[0] = 1;
  for( i = 1; i <= n ; i++ )
    mpFpont[i] = mpRpont[i] = 0;

	// Procura o 1� Arco. Se cauda > 1:
	a = rArcos[0].GetTail() ;

  // Os arcos de cauda i, com i < a n�o existem
	for( i = 0; i < a; i++ ) mpFpont[i+1] = mpFpont[i];

	// Os arcos em rArcos[k] est�o em FSF implicito
	k = 0;
	while( k < m ){
		//Guarda arcos com a mesma cauda em FSF e prepara RFS

     //cout<<"\nArcos com a mesma cauda!";
	   while( k < m && a == rArcos[k].GetTail() ){

			b = rArcos[k].GetHead() ;
			//DEBUG
			//cout<<"\n("<<a<<","<<b<<")";
			mTabInfoArcos[k+1].mHead = b ;
			mTabInfoArcos[k+1].mTail = a ;
			mTabInfoArcos[k+1].mCost = rArcos[k].GetCost() ;
			mTabInfoArcos[k+1].mDist = rArcos[k].GetDistance() ;
			mTabInfoArcos[k+1].mTime = rArcos[k].GetTime() ;

			//cout<<"\n capacidade do arco "<<k+1<<" = "<<mTabInfoArcos[k+1].mCapacity;
			mpRpont[b]++ ;

			//cout<<" mpRpont["<<b<<"]="<<mpRpont[b];
			mpFpont[a]++;

			//cout<<" mpFpont["<<a<<"]="<<mpFpont[a];
			k++;

			if( a == b ) {
			   cerr << "\nArcos::Arcos(vector<ArcoTHC> &, int): k =" << k << flush ;
			   cerr << " Cabeca == Cauda " << a << " == " << b<< "\n" << flush;
			   abort() ;
			}
		}
		//cout<<"\n mpFpont["<<a<<"]="<<mpFpont[a];


	   // Saiu do ciclo anterior porque a cauda de rArcos[k] � diferente de -a-
	   // Ou seja porque rArcos[k].GetTail( ) > a
	   // Actualiza -a- e Salta n�s sem arcos emergentes
	   if( k < m )
			for(i = rArcos[k].GetTail() ;  a < i ; a++ ){
	  			mpFpont[a+1] = mpFpont[a] ;

	  			//cout<<" mpFpont["<<a+1<<"] = mpFpont["<<a<<"] => "<< mpFpont[a]<<" = "<<mpFpont[a+1] ;
	  		}
	}


	// Se os �ltimos n�s n�o t�m nenhum arco emergente
	for( k=a+1 ; k <=n ; k++ ) mpFpont[k] =  mpFpont[k-1];

	//cout<<"\n mpFpont["<<k<<"]="<<mpFpont[n];

	if( m + 1 != mpFpont[n] ) {

		cout << "\nERROR: Arcos::Arcos( vector<ArcoTHC> &, int ) ";
		cout << "\n       mpFpont[" << n << "] = " << mpFpont[n] << "\n" << flush;
		//for(int i=0; i< rArcos.size() ; i++)
		// rArcos[i].Mostra() ;
		cout << flush;
		//abort() ;
	}

	//  mpRpont[0] == 1
	//      mpRpont[i] == n� de arcos com cabeca == i, i=1,2,...n
	//
	//  mpRpont[i]-mpRpont[i-1] = n� de arcos com cabeca == i
	//
	for( i = 1 ; i <= n ; i ++ ) mpRpont[i] += mpRpont[i-1] ;

	//cout<<" mpRpont["<<n<<"]="<<mpRpont[n];

	// Cria mpTrace
	//
	// Pr�: mpRpont[0] == 1;
	//      Para i=1,2,...,n
	//      mpRpont[i]-mpRpont[i-1] == n�mero de arcos com cabe�a igual a -i-
	//
	// P�s: mpRpont[0] - 1 == n�mero de arcos com cabe�a igual a 1
	//      Para i=2,3,...,n
	//      mpRpont[i]-mpRpont[i-1] == n�mero de arcos com cabe�a igual a (i-1)
	//      mpTrace[u] = k: u (RSF) <=> k (FSF)
	//
	for( k = 1 ; k <= m ; k++ ){
	   b = mTabInfoArcos[k].mHead ; // arco k em FSF <=>

			if( b > n ) {
  			cout << "\nCabe�a == " << b << " > " << n << flush ;
  			abort() ;
      }
			if( mpRpont[b-1] > m ) {
        cout << "\nmRpont[" << b-1 << "] == " << mpRpont[b-1] ;
        cout << " > " << m << flush;
        abort() ;
      }

	   mpTrace[mpRpont[b-1]] = k ;   // mpRpont[b-1] em RSF
	   //cout << "\nmpTrace[" << mpRpont[b-1] << "] == " <<  k ;
	   //Ponteiro para o arco seguinte em RSF, de cabe�a == b
	   mpRpont[b - 1]++ ;
	 }

	// Refaz mpRpont
	//
	// Pr�: mpRpont[0] - 1 == n�mero de arcos com cabe�a igual a 1
	//      Para i=2,3,...,n
	//      mpRpont[i]-mpRpont[i-1] == n�mero de arcos com cabe�a igual a (i-1)
	//      mpTrace[u] = k: u (RSF) <=> k (FSF)
	//
	// P�s: mpRpont[0] == 1;
	//      Para i=1,2,...,n
	//      mpRpont[i]-mpRpont[i-1] == n�mero de arcos com cabe�a igual a -i-
	//
	for( i = n ; i >= 1 ; i-- ){
		mpRpont[i] = mpRpont[i-1] ;
		//cout<<"\n mpRpont["<<i<<"]="<<mpRpont[i];
	}
	mpRpont[0] = 1;

}

/**
*  Construtor com fase em FSF impl�cita em rArcos.
*  Conta, indica o n�mero de n�s diferentes existentes em rArcos.
*
* Verifica se dois n�s, s e t s�o conexos ou se existe mais algum n� na rede que n�o liga a
* a rede entre s e t estes n�s estar�o guardados no vector desconexo.
*/
Arcos::Arcos(int origem, int destino, vector<ArcoTHCC> rArcos, int conta, bool &hacaminho ){


	// Dimens�o da rede
	n = conta ;
	m = rArcos.size() ;

	if( m == 0  ) return;

	mTabInfoArcos.resize(m+1);
	// Reserva espa�o para a Forward Star Form
	mpFpont.resize(m+1);
	// Reserva espa�o para a Reverse Star Form
	mpTrace.resize(m+1);

	mpRpont.resize(m+1);

	int i, k, a, b;

  mpFpont[0] = mpRpont[0] = 1;
  for( i = 1; i <= n ; i++ )
    mpFpont[i] = mpRpont[i] = 0;

	// Procura o 1� Arco. Se cauda > 1:
	a = rArcos[0].GetTail() ;

  // Os arcos de cauda i, com i < a n�o existem
	for( i = 0; i < a; i++ ) mpFpont[i+1] = mpFpont[i];

	// Os arcos em rArcos[k] est�o em FSF implicito
	k = 0;
	while( k < m ){


		//Guarda arcos com a mesma cauda em FSF e prepara RFS

     //cout<<"\nArcos com a mesma cauda!";
	   while( k < m && a == rArcos[k].GetTail() ){

			b = rArcos[k].GetHead() ;

			mTabInfoArcos[k+1].mHead = b ;
			mTabInfoArcos[k+1].mTail = a ;
			mTabInfoArcos[k+1].mCost = rArcos[k].GetCost() ;
            mTabInfoArcos[k+1].mDist = rArcos[k].GetDistance() ;
			mTabInfoArcos[k+1].mTime = rArcos[k].GetTime() ;

			//cout<<"\n capacidade do arco "<<k+1<<" = "<<mTabInfoArcos[k+1].mCapacity;
			mpRpont[b]++ ;

			//cout<<" mpRpont["<<b<<"]="<<mpRpont[b];
			mpFpont[a]++;

			//cout<<" mpFpont["<<a<<"]="<<mpFpont[a];
			k++;

			if( a == b ) {
			   cerr << "\nArcos::Arcos(vector<ArcoTHC> &, int): k =" << k << flush ;
			   cerr << " Cabeca == Cauda " << a << " == " << b<< "\n" << flush;
			   abort() ;
      }
		}
	   //cout<<"\n mpFpont["<<a<<"]="<<mpFpont[a];
	   // Saiu do ciclo anterior porque a cauda de rY[k] � diferente de -a-
	   // Ou seja porque rArcos[k].GetTail( ) > a
	   // Actualiza -a- e Salta n�s sem arcos emergentes
	   if( k < m )
			for(i = rArcos[k].GetTail() ;  a < i ; a++ ){
	  			mpFpont[a+1] = mpFpont[a] ;
	  			//DEBUG
	  			//cout<<" mpFpont["<<a+1<<"] = mpFpont["<<a<<"] => "<< mpFpont[a]<<" = "<<mpFpont[a+1] ;
	  		}
	 }

	// Se os �ltimos n�s n�o t�m nenhum arco emergente
	for( k=a+1 ; k <=n ; k++ ) mpFpont[k] =  mpFpont[k-1];

	//cout<<"\n mpFpont["<<k<<"]="<<mpFpont[n];

	if( m + 1 != mpFpont[n] ) {
		cout << "\nERROR: Arcos::Arcos( vector<ArcoTHC> &, int ) ";
		cout << "\n       mpFpont[" << n << "] = " << mpFpont[n] << "\n" << flush;
		//for(int i=0; i< rArcos.size() ; i++)
		 //rArcos[i].Mostra() ;
		cout << flush;
		abort() ;
	}
	//  mpRpont[0] == 1
	//      mpRpont[i] == n� de arcos com cabeca == i, i=1,2,...n
	//
	//  mpRpont[i]-mpRpont[i-1] = n� de arcos com cabeca == i
	//
	for( i = 1 ; i <= n ; i ++ ) mpRpont[i] += mpRpont[i-1] ;

	//cout<<" mpRpont["<<n<<"]="<<mpRpont[n];

	// Cria mpTrace
	//
	// Pr�: mpRpont[0] == 1;
	//      Para i=1,2,...,n
	//      mpRpont[i]-mpRpont[i-1] == n�mero de arcos com cabe�a igual a -i-
	//
	// P�s: mpRpont[0] - 1 == n�mero de arcos com cabe�a igual a 1
	//      Para i=2,3,...,n
	//      mpRpont[i]-mpRpont[i-1] == n�mero de arcos com cabe�a igual a (i-1)
	//      mpTrace[u] = k: u (RSF) <=> k (FSF)
	//
	for( k = 1 ; k <= m ; k++ ){
	   b = mTabInfoArcos[k].mHead ; // arco k em FSF <=>

			if( b > n ) {
  			cout << "\nCabe�a == " << b << " > " << n << flush ;
  			abort() ;
      }
			if( mpRpont[b-1] > m ) {
        cout << "\nmRpont[" << b-1 << "] == " << mpRpont[b-1] ;
        cout << " > " << m << flush;
        abort() ;
      }

	   mpTrace[mpRpont[b-1]] = k ;   // mpRpont[b-1] em RSF
	   //cout << "\nmpTrace[" << mpRpont[b-1] << "] == " <<  k ;
	   //Ponteiro para o arco seguinte em RSF, de cabe�a == b
	   mpRpont[b - 1]++ ;
	 }

	// Refaz mpRpont
	//
	// Pr�: mpRpont[0] - 1 == n�mero de arcos com cabe�a igual a 1
	//      Para i=2,3,...,n
	//      mpRpont[i]-mpRpont[i-1] == n�mero de arcos com cabe�a igual a (i-1)
	//      mpTrace[u] = k: u (RSF) <=> k (FSF)
	//
	// P�s: mpRpont[0] == 1;
	//      Para i=1,2,...,n
	//      mpRpont[i]-mpRpont[i-1] == n�mero de arcos com cabe�a igual a -i-
	//
	for( i = n ; i >= 1 ; i-- ){
		mpRpont[i] = mpRpont[i-1] ;
		//cout<<"\n mpRpont["<<i<<"]="<<mpRpont[i];
	}
	mpRpont[0] = 1 ;

	Nos auxNos(n);
	auxNos.InicializaNos( origem );
	hacaminho = BreadthFirstSearch(origem, destino, auxNos);
}


/**-----------------------------------------------------------------------
* dados dois n�s i e j.
*
*  Retorna o arco k de origem i e destino j
*              0, se o arco n�o existe (e avisa do erro)
*
*/
int Arcos::GetArcoFSF( int i, int j ){

	for(int k = 1; k<=m ; k++){
		if( (mTabInfoArcos[ k ].mTail == i) && (mTabInfoArcos[ k ].mHead == j))
			return k;
	}
	return -1;
}

/**-----------------------------------------------------------------------
* dados dois n�s i e j.
*
*  Retorna o arco k de origem i e destino j
*              0, se o arco n�o existe (e avisa do erro)
*
*/
int Arcos::GetArcoRSF( int i, int j ){

	for(int k = 1; k<=m ; k++){
		if( (mTabInfoArcos[mpTrace[k]].mTail == i) && (mTabInfoArcos[mpTrace[k]].mHead == j))
			return k;
	}

	//cout<<"\n ERRO Arcos::GetArcoRSF ";
	return -1;
}


/**
 * Obtem o valor do no segundo um dos criterios
 * custo, distancia ou tempo
 */
float Arcos::GetValueOfNo(int k, Nos &rGrafoNos, int criterio){

    switch(criterio){
        case 1: return rGrafoNos.GetChave( k );     //o criterio e' o custo
        break;
        case 2: return rGrafoNos.GetDistance( k );  //o criterio e' a distancia
        break;
        case 3: return rGrafoNos.GetTime( k );      //o criterio e' o tempo
        break;
    }
    return 0;
}

/**
 * Obtem o valor do no segundo um dos criterios
 * custo, distancia ou tempo
 */
float Arcos::GetValueOfArc(int arco, int criterio){

    switch(criterio){
        case 1: return mTabInfoArcos[mpTrace[arco]].mCost;     //o criterio e' o custo
        break;
        case 2: return mTabInfoArcos[mpTrace[arco]].mDist;  //o criterio e' a distancia
        break;
        case 3: return mTabInfoArcos[mpTrace[arco]].mTime;      //o criterio e' a tempo
        break;
    }
    return 0;
}

/**
* Obs: os arcos entre os n�s j� devem estar criados segundo segundo a estrurra
*      Forward and reverse star form.
*/
bool Arcos::Dijkstra(int t, Nos &rGrafoNos, int criterio){

	queue<int> fila;
	vector<int> rotulado( n + 1);

	//inicializa o vector
	for( int k = 1; k <= n; k++){
		rotulado[k] = 0;
	}
	fila.push( t );
	rotulado[t] = 1;

	while( !fila.empty() ){
		// O  n� k � o que tem menor chave (pi)
		int & k = fila.front();

		//N� com r�tulo definitivo
		rotulado[k] = 2;
		// e sua essa chave vale

		//obtem o valor do no' segundo um criterio que pode ser(custo, tempo, distancia)
		float v_ch = GetValueOfNo(k, rGrafoNos, criterio);

		//cout<<" v_ch "<<k <<" = "<<v_ch;
		//float ch = rGrafoNos.GetChave( k );
		// Altera o peso dos n�s j: (j,k) cujo peso ainda n�o � definitivo
		int fim = mpRpont[k];

		//cout<<"\nO n� k = "<<k<<" tem chave :"<<ch;
		for(int arco = mpRpont[k-1]; arco < fim; arco++ ){
			int j = mTabInfoArcos[mpTrace[arco]].mTail;

            //cout<<"Vao analisar o arco ("<<k<<","<< j<<")"<<endl;

			if( rotulado[j] != 2 ){//ainda n�o � definitivo
				// custo do arco (j,k)
				float v_jk = GetValueOfArc(arco, criterio);

				float aux = v_ch + v_jk;

				// muda o r�tulo do n� j  e sua altura
				if( aux < GetValueOfNo(j, rGrafoNos, criterio) ){

					if( rotulado[j] == 1 ){ //se j� estava na heap, muda posi��o
                        rGrafoNos.ActualizeNode( j, aux,  k,  rGrafoNos.GetAltura( k ) + 1, criterio );
					}
					else{
                        rGrafoNos.ActualizeNode( j, aux, k,rGrafoNos.GetAltura( k ) + 1,   criterio );
						fila.push(j);
						rotulado[j] = 1;
					}
				}
			}
		}
		fila.pop();
	}
	return true;
}

/**
*  O caminho mais curto segundo o n�mero de saltos. (BFS)
*
*/
bool Arcos::BreadthFirstSearch(int s, int t, Nos &rGrafoNos){

	queue<int> fila;
	vector<int> rotulado( n + 1);

	//inicializa o vector
	for(int k = 0; k < n; k++){
		rotulado[k] = 0;
	}

	fila.push( s );
	rotulado[s] = 1;

	do{
		int  i = fila.front();
		//N� com r�tulo definitivo
		rotulado[i] = 2;

		int fim = mpFpont[i];
		for( int arco = mpFpont[i-1]; arco < fim; arco++ ){
			int j = mTabInfoArcos[ arco ].mHead;

			//cout<<"\nArco ("<<i<<","<<j<<").";
			if( rotulado[j] != 2 ){
				rGrafoNos.ActualizeNode(j, i, rGrafoNos.GetAltura( i ) + 1 );
				rotulado[j] = 1;
				fila.push(j);
			}
		}fila.pop();  // remove elemento na frente da fila, j� analisado
	}while( !fila.empty() );

	if( rGrafoNos.GetAltura( t ) == MAX_INT ){
		//cout<<"\nvai retornar false";
		return false;
	}
	else{
			//cout<<"\nvai retornar true";
		return true;
	}
}
