
/**
 *  file --> grafico.cpp
 */

#include "Network.h"
#include <iostream>
#include <vector>
#include <time.h>

#include <string>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <cstdio>
#include <stack>
#include <string>
#include <sstream>

using namespace std;


/**
 *  Validate the source and terminal of the path.
 */

bool IsOk(int origem, int destino){
	if(origem == destino){
		cerr <<"\n\t OP's, origem/destino invalido, Tente novamente!\n";
		return false;
	}
	if(origem <= 0 || destino <= 0){
		cerr <<"\n\t OP's, origem/destino invalido, Tente novamente!\n";
		return false;
	}
	return true;
}
/**
 * verifica se o criterio fornecido e' um dos seguintes:
 *                 (1 - custo, 2 - distancia, 3 - tempo)
 */

bool CriterioValido(int crit){
    return ((crit != 1) && (crit != 2) && (crit != 3));
}

string getCriterio(int criterio){

    switch(criterio){
        case 1: return "Custo total";
        break;
        case 2: return "Distancia total";
        break;
        case 3: return "Duracao total";
        break;
    }
}
string calculaHoraChegada(int horaPart, float valorCam){
    float total = horaPart*60 + valorCam;

    stringstream infotime;

    //converte em horas e minutos.
    int h = 0;
    while(total >=60){
        total = total - 60;
        h++;
    }
    infotime <<"("<<h<<":"<<total<<")";

    string time( infotime.str() );
    return const_cast<char*>( time.c_str() );

    //return aux;
    //return s<<"("<<h<<":"<<total<<")";
}

/**
 * Gera o ficheiro responsavel para a criacao do grafo do caminho gerado
 *
 */
void CreateGraphByDot( vector<int> CaminhoSt, Arcos auxArcos, map<int,int> Mapa, int crit ){
    //------------------------------------------------

	//Escrita dos dados em ficheiro.
	stringstream info;
	info<<"GraphByDot.dot";
	string ficheiroEscrita( info.str() );
	ofstream myfile;

    //myfile.open( ficheiroEscrita.c_str(), ios::app);
    myfile.open( ficheiroEscrita.c_str(), ios::ate);
    if ( !myfile.is_open() ){
        // The file could not be opened
        cerr << "\nERROR: Não conseguiu abrir o ficheiro " ;
        cerr << ficheiroEscrita.c_str() << " para escrita."<<flush ;
    }

    //escreve no ficheiro
    myfile << "digraph G {"<<"\n";
    myfile << "\t    rankdir=LR; \n" ;
    myfile << "\t    rankdir=LR; \n";
    myfile << "\t    size = \"8,5\"\n";
    myfile << "\t    orientation = land;\n";
    myfile << "\t    node[shape=doublecircle];\n";
    myfile << "\t    "<< CaminhoSt[1]<<" "<<CaminhoSt[CaminhoSt.size()-1]<<"\n";
    myfile << "\t    node[shape=circle];\n";
    for( int i = 1; i < CaminhoSt.size()-1; i++){
        int k = auxArcos.GetArcoRSF( Mapa[CaminhoSt[i]], Mapa[CaminhoSt[i+1]]);
        float value = auxArcos.GetValueOfArc(k, crit);
        myfile<<"\t    "<<CaminhoSt[i]<<" -> "<<CaminhoSt[i+1]<<"[label=\""<<value<<"\"];\n";
    }

    myfile<<"}";
    myfile.close();
}


/**
 * Main Program
 */

int main(){

	clock_t ti, tf, tpi;
	ti = clock();//initial time

	//----------construtor que cria rede (nos e arcos) a partir de um ficheiro .txt/ .bin
	Network net("redeN.txt");

	//net.Mostra();
	//----------

	tf = clock();
	cout<<"\n\t Time to create the Network ("<<(float)(clock()-ti)/CLOCKS_PER_SEC<<" sec. )\n";

	int origem,	destino, horaPart, crit, tipo;

	for(;;){//Geracao infinita de Guia de Caminhos

		do{ //validação da origem e destino do pedido.
			cout<<"\n\tStarting path ::";
			cin>> origem;
			cout<<"\n\tEnd path ::";
			cin>> destino;

            if(!IsOk(origem, destino)){
			    cout<<"\nERRO: Invalid Source/destination!"<<endl;
			    break;
            }
            //int aux = 0;
            //ordena os arcos por ordem da cauda
            //if( origem > destino ){ int aux = origem ; origem = destino ; destino = aux;}

			cout<<"\n\tDigite the starting time::";
			cin>> horaPart;

			do{
			    cout<<"\n\tChose the criteria::\n\t\t 1 -> Cost\n\t\t 2 -> Distance\n\t\t 3 -> Time\n\t(1/2/3)?::";
			    cin>>crit;
			    if(CriterioValido(crit)){
			        cout<<"Invalid Criteria! \n Try Again! "<<endl;
                }
            }while(CriterioValido(crit));

		}while(!IsOk(origem, destino));

        vector<int> tabNos;         //nós conectos entre s e t
        vector<ArcoTHCC> tabArcos;  //arcos
        map<int,int> Mapa;          //nós traduzidos (1..n) para alimentar o algoritmo

        int s = origem, t = destino; //salvaguarde s e t antes de mapea-los

        //ve se eh possivel conexao entre a origem e destino (verifica se a rede eh conexa)
        if( !net.NetworkConstruct(origem, destino, 4, tabArcos, tabNos, Mapa) ){
           cout<<"ERRO: Impossible to create the network between "<<origem<<" e "<<destino<<endl;
        }else{
            int conta = tabNos.size();
            Nos auxNos( conta );      //constroi o objecto da classe nó com o total de elementos

            origem = Mapa[origem];    //mapea a origem do pedido.
            destino = Mapa[destino];  //mapea o destino do pedido.

            auxNos.InicializaNos( destino );  // inicializa os nós
            Arcos auxArcs( tabArcos, conta ); // constroi a tabela dos arcos.

            //if( auxArcs.BreadthFirstSearch( auxNos, origem, destino )){
            if( auxArcs.Dijkstra( destino, auxNos, crit )){

                //auxNos.MostraCaminho(destino);
                vector<int> CaminhoSt;
                int saltos;
                float custo, capacidade, valorCam;

                if(auxNos.GetCaminho(origem, destino, crit, CaminhoSt, valorCam)){
                    net.TraduzDados( CaminhoSt,  tabNos ); //volta a traduzir os nos do caminho de acordo com o ficheiro original
                    cout<<"\n\n\t Path p => { "<<CaminhoSt[1];
                    for( int i = 2; i < CaminhoSt.size(); cout<<" -> "<<CaminhoSt[i++]);

                    cout<<" } "<<getCriterio(crit)<<" with ("<<valorCam<<")\n\n";
                    if( crit ==3 ){
                        cout<<"\n\tStarting the path at ("<<horaPart<<":00)";
                        cout<<" Finish estimated at "<<calculaHoraChegada(horaPart, valorCam)<<"\n\n";
                    }

                    ///funcao que cria o ficheiro dot para desenhar o grafo.
                    CreateGraphByDot(CaminhoSt, auxArcs, Mapa, crit);

                }else{
                    cerr << "\n\t Does not exit path between  ";
                    cerr << s << " and " << t << "\n\n";
                }
            }else{
                cout<<"Nao Calculou o caminho segundo Dijkstra ";
            }
        }
        char op;
        cout<<"\t\t Want to continue?\n\t\t\t y/Y - Yes \n\t\t\t n/N - No\n\t\t(y/n):";
        cin>>op;
        if(op == 'n' || op == 'N') return 0;
        system("cls");
	}
	cout<<"\n Exiting...";
	return 0;
}

