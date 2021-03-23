
/**
 *  file --> Network.cpp
 */

#include "Network.h"
#include "binaria.h"

/**
 *  Constructor da rede a partir de um ficheiro (.txt/.bin)
 *  Extrai a informa��o a partir de um ficheiro e constroi a rede(ArcoTHCC).
 */
Network::Network( char *fileGraph ){

	int  i, j, k =0, t, h, a;
	float custo,capacidade, tempo, distancia;
	ifstream entrada( fileGraph );

	if( !entrada ){
		cout << " NetWork::Network( char * )" ;
		cout << " N�o consegui abrir o ficheiro " << fileGraph;
		return;      // Erro 1, n�o conseguiu abrir o ficheiro,
	}

	string linha;
	//L� 1� linha com legenda
	getline( entrada, linha );
	getline( entrada, linha );
	getline( entrada, linha );
	//cout<<linha<<endl;

	//L� tudo at� ao fim
	string parte;
	while( !entrada.eof() ){

		// L� uma linha com a descri��o dos campos.
		getline( entrada, linha );

		if( linha.length() !=0 ){  // Para detectar fim de ficheiro...

			// identifica a cauda
			i = 0;

			while( i < linha.length() && linha[i] != ' ' ) i++;

			if( i == linha.length() ) {  //erro de formata��o
				entrada.close();
				return ;
			}
            i--;
            j = i;

			parte = linha.substr( 0 , i ) ;

			a = atoi( parte.c_str() );    // obt�m cauda do canal

			while( i < linha.length() && linha[i] != ' ' ) i++ ;

			//i++;
			//j = i;
			// procura fim do c�digo do 1� n�
			//while( i < linha.length() && linha[i] != ' ' ) i++ ;

			if( i == linha.length() ) {  //erro de formata��o
				entrada.close();
				return ;
			}

			parte = linha.substr( j-1 , i ) ;

			//cout<<"parte 1:"<<parte<<endl;

			t = atoi( parte.c_str() );    // obt�m cauda do canal

			//cout<<"\nt:"<<t<<"("<<j<<","<<i<<")"<<endl;

			if( t == 0 ) {  entrada.close(); return ; } //erro de formata��o
			i++; //salta " "

			if( i == linha.length() ) {  //erro de formata��o
				entrada.close();
				return ;
			}
			j = i; // in�cio do c�digo do 2� n�
			// procura fim do c�digo do 2� n�
			while( i < linha.length() && linha[i] != ' ') i++ ;

			if( i == linha.length() ) {  //erro de formata��o
				entrada.close();
				return ;
			}
			parte = linha.substr( j, i-j+1 ) ;

			//cout<<"parte 2:"<<parte<<endl;

			h = atoi( parte.c_str());    // obt�m cabe�a do arco

            //cout<<"h :"<<h<<"("<<j<<","<<i-j+1<<")"<<endl;

			if( h == 0 ) {  entrada.close(); return ; } //erro de formata��o
			i++; //salta ";"

			if( i == linha.length() ) {  //erro de formata��o
				entrada.close();
				return ;
			}
			j = i; // in�cio do c�digo do eqInicial
			// procura fim do c�digo do CFO
			while( i < linha.length() && linha[i] != ' ') i++ ;
			//i++; //salta ";"

			if( i == linha.length() ) { //erro de formata��o
				entrada.close();
				return ;
			}
			parte = linha.substr( j, i-j ) ;
			custo = atof( parte.c_str());

            //cout<<"custo:"<<custo<<"("<<j<<","<<i-j<<")"<<endl;

			i++; //salta ";"

			if( i == linha.length() ) {
			entrada.close(); return ; } //erro de formata��o

			j = i; // in�cio do c�digo do equipamento Terminal do canal
			// procura fim do c�digo equipamento terminal
			while( i < linha.length() && linha[i] != ' ') i++ ;
			//i++; //Salta o ;

			parte = linha.substr( j, i-j ) ;
			distancia  = atof( parte.c_str());

            //cout<<"capacidade:"<<capacidade<<"("<<j<<","<<i-j<<")"<<endl;

            i++; //salta ";"

			if( i == linha.length() ) {
			entrada.close(); return ; } //erro de formata��o

			j = i; // in�cio do c�digo do equipamento Terminal do canal
			// procura fim do c�digo equipamento terminal
			while( i < linha.length() && linha[i] != ' ') i++ ;
			//i++; //Salta o ;

			parte = linha.substr( j, i-j ) ;
			tempo = atof( parte.c_str());

            //cout<<"tempo:"<<tempo<<"("<<j<<","<<i-j<<")"<<endl;

			if( t != h && t > 0 && h > 0 && custo > 0 && tempo > 0 && distancia > 0  ){

			    //cout<<"\n t = "<<t<<" h = "<<h;
  				int aux = 0;

  				//ordena os arcos por ordem da cauda
  			    //if( t > h ){ aux = t ; t = h ; h = aux;}

  				//Insere informa��o ordenada na tabela de arcos e sem repetic�es.
  				ArcoTHCC umTHCC( t, h, custo, distancia, tempo );

                //cout<<"\n arco ("<<t<<","<<h<<")::>["<<custo<<","<<distancia <<","<<tempo<<"] "<<endl;

  				bool existe;
  				int pos = Binaria( mNetArcs, umTHCC, Compara(), existe);

  				if( !existe ){
  					//cout<<"\nInsere o arco ("<<t<<","<<h<<")::>["<<custo<<","<<distancia <<","<<tempo<<"] pos de insercao = "<<pos;
  					mNetArcs.insert( mNetArcs.begin() + pos, umTHCC );
  				}else{
  					cout<<"\nN�o inseriu pk existe o arco ("<<t<<","<<h<<")::>["<<custo<<","<<distancia <<","<<tempo<<"]"<<endl;
  				}
			}else{
				k++;

			}
		}
	}

	entrada.close();

	return;
}

/**
 * Faz o mapeanemto a partir da informacao da rede gerada (ficehiro .txt/.bin) e guardada em mNetArcs.
 * tabArcos <-- Devolve um vector com os arcos mapeados para o algoritmo de rotula��o
 * tabNos   <-- Devolve um vector de n�s e arcos mapaedos.
 * Mapa     <-- Devolve um vector com os nos mapeados.
 */
void Network::MapearInfo(int tipo, vector<int> &tabNos, vector<ArcoTHCC> &tabArcos, map<int,int> &Mapa){

  for(int i = 0; i < mNetArcs.size(); i++ ){

    int tail = mNetArcs[i].GetTail();
    int head = mNetArcs[i].GetHead();
    float custo = mNetArcs[i].GetCost();
    float dist  = mNetArcs[i].GetDistance();
    float tempo = mNetArcs[i].GetTime();

    int h2 , t2;
    int n = tabNos.size();//contem o total de n�s da rede

    //cout<<"TOTAL de nos = "<<n;
    typedef map<int,int>::const_iterator CI;
    CI p;

    // V� se apareceu mais algum n� novo (tail)
    p = Mapa.find( tail );
    if( p == Mapa.end() ){
      Mapa[tail] = ++n;
      t2 = n ;
      tabNos.push_back( tail ) ;
    }
    else  t2 = p->second;  // tabNos[t2-1] == tail

    // V� se apareceu mais algum n� novo (head)
    p = Mapa.find( head );
    if( p == Mapa.end() ){
      Mapa[head] = ++n ;
      h2 = n ;
      tabNos.push_back( head ) ;
    }
    else h2 = p->second ; // tabNos[h2-1] = head

    bool existe = false;

	ArcoTHCC umTHCC(t2 , h2, custo, dist, tempo );
	int pos = Binaria(tabArcos, umTHCC, Compara(), existe );
	if(!existe){
		tabArcos.insert( tabArcos.begin()+ pos, umTHCC );
	}else{
		cout<<"\nN�o inseriu pk existe!";
	}
  }
  //cout<<"\nTotal de arcos mapeados = "<<tabArcos.size();
}

/**
 *  CaminhoSt <-- Sequencia de n�s do pedido que deve ser traduzida para a
 *  identifica��o dos n�s originais.
 */
void  Network::TraduzDados( vector<int> &CaminhoSt,  vector<int> tabNos ){

	for(int i = 0; i < CaminhoSt.size(); i++){
		CaminhoSt[i] = tabNos[CaminhoSt[i]-1];
	}
}

/**
 *  esta fun��o tem a finalidade de ver se s e t interligam entre si
 */
bool Network::NetworkConstruct(int &orig, int &dest, int tipo, vector<ArcoTHCC> &tabArcos, vector<int> &tabNos, map<int,int> &Mapa ){

	MapearInfo(tipo, tabNos, tabArcos, Mapa);

	int origem = Mapa[orig];
	int destino =  Mapa[dest];

	if(origem == 0 || destino == 0 || origem == destino) return false;

	bool hacaminho;

	Arcos auxArcs(origem, destino, tabArcos, tabNos.size(), hacaminho);

    //se a variavel hacaminho == false => nao existe conexao entre origem e destino, true c.c.
	return hacaminho;
}

/**
 * Mostra a informa��o da rede.
 */
void Network::Mostra(){
  cout<<"\nMostra a Informa��o da rede criada.";
  for( int i = 0; i < mNetArcs.size(); i++)
	  mNetArcs[i].ArcoTHCC::Mostra();

}

