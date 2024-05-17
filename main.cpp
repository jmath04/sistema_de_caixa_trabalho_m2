#include <iostream>
#include <stdlib.h>
#include <chrono>
#define tmax 100


using namespace std;



typedef struct{
    string  nome;
    int cod;
    int est;
    float preco;
}produto;

typedef struct{
    int cod;
    int totalV;
    float precoV;
}vendas;

void registraP( int &n, produto vet[]);
int ConsProdCODIGO(int n, produto vet[],int codVeri);
void relatorioP(produto unidade);
bool ConsProdNOME(int n, produto vet[], string Tnome);
void relatorioEstoque(int n,produto vet[]);
void venda(int nP, produto vetP[], int &nV, vendas vetV[]);
int validaINT(string frase);
float validaFloat(string frase);
string validaSTRING(string frase);
void relatorioVendas(int n, vendas vet[], int nP, produto vetP[]);
void achaProduto(int nP, produto vetP[]);


int main (){
    vendas vetV[tmax];
    produto vetP[tmax];
    int nP = 0;
    int nV = 0;
    int j;
    do{
        
        cout <<" 1. Registrar Produto no Estoque" << endl;
        cout <<" 2. Consultar Produto no Estoque" << endl;
        cout <<" 3. Venda de Produto" << endl;
        cout <<" 4. Relatorio do Estoque" << endl;
        cout <<" 5. Relatorio das Vendas" << endl;
        cout <<" 6. Sair do Programa" << endl;                                     
        j = validaINT(" digite uma opcao: ");

        switch(j){
            case 1:
                system("cls");
                registraP(nP,vetP);
                break;
            case 2:
                system("cls");
                achaProduto(nP,vetP);
                break;
            case 3:
                system("cls");
                venda(nP,vetP,nV,vetV);
                break;
            case 4:
                system("cls");
                relatorioEstoque(nP,vetP);
                break;
            case 5:
                system("cls");
                relatorioVendas(nV,vetV,nP,vetP);
                break;
            default:
                cout << "opcao invalida";
                break;
     
        }
        
    }while( j != 6);
    system("cls");
    return 0; 
}

void registraP( int &n, produto vet[]){
    string nome = validaSTRING("Digite o nome do produto: ");
    for (unsigned int i = 0 ; i < nome.size(); i++){
        nome[i] = toupper(nome[i]);
    }
    bool achou = ConsProdNOME(n,vet,nome);
    if (achou){
        cout << "produto ja existente" << endl;
        cout << "aperte enter para continuar";
            cin.get();
            system("cls");
    }
    else{
        vet[n].nome = nome;
        int x = validaINT("digite o codigo do produto: ");
        if (ConsProdCODIGO(n,vet,x) > -1){
            cout << "codigo ja existente" << endl;
            cout << "aperte enter para continuar";
            cin.get();
            system("cls");
        }
        else{
            vet[n].cod = x;
            vet[n].preco = validaFloat("digite o preco do produto: ");
            vet[n].est = validaINT("digite a quantidade no estoque: ");
            n++;
            cout << "aperte enter para continuar";
            cin.get();
            system("cls");
        }
    }
    
}


int ConsProdCODIGO(int n, produto vet[],int codVeri){ 
        if(n==0){
            return -1;
        }else 
        if(codVeri==vet[n-1].cod){
            return n-1;
        }else{
           return ConsProdCODIGO(n-1, vet, codVeri);
        } 
}

void relatorioP(produto unidade){
    cout << "Nome: " << unidade.nome << endl;
    cout << "Cod. de Catalogacao: " << unidade.cod << endl;
    cout << "Quant. de Unidades no Estoque: " << unidade.est << endl;
    cout << "Preco de Venda: " << unidade.preco << endl;
}

bool ConsProdNOME(int n, produto vet[], string Tnome){
    for( int i = 0; i < n; i++ ){
        if(vet[i].nome == Tnome){
            return true;
        }
    }
    return false;
}


void relatorioEstoque(int n,produto vet[]){
    cout << "Relatorio do Estoque: " <<  endl;
    for(int i=0;i<n;i++){
        relatorioP(vet[i]);
        cout << "=========================================================" << endl;
    }
    cout << "aperte enter para continuar";
    cin.get();
    system("cls");
}

void relatorioVendas(int n, vendas vet[], int nP, produto vetP[]){
    if (n > 0){
       vendas relatorio[tmax];
    int x = 1;
    relatorio[0].cod = vet[0].cod;
    relatorio[0].totalV = vet[0].totalV;
    relatorio[0].precoV = vet[0].precoV;
    bool achou;
    for (int i = 1; i < n; i++){
        achou = false;
        for(int j = 0; j < x; j++){
            if (vet[i].cod == relatorio[j].cod){ 
                achou = true;
                relatorio[j].precoV += vet[i].precoV;
                relatorio[j].totalV += vet[i].totalV;
                break;
            }
        }
        if(achou == false){
            relatorio[x].cod = vet[i].cod;
            relatorio[x].precoV = vet[i].precoV;
            relatorio[x].totalV = vet[i].totalV;
            x++;
        }

    }
    for(int i = 0; i < x; i++){
            int j = ConsProdCODIGO(nP, vetP, relatorio[i].cod);
            cout << "nome: " << vetP[j].nome << endl;
            cout << "codigo de catalagocao: " << relatorio[i].cod << endl;
            cout << "total vendido: " << relatorio[i].totalV << endl;
            cout << "valor total vendido: "<<relatorio[i].precoV << endl;
            cout << "=========================================================" << endl;
            
        }
    }else{
        cout << "nenhuma venda realizada" <<  endl;
    }
    cout << "aperte enter para continuar";
    cin.get();
    system("cls");
}
    

void venda(int nP, produto vetP[], int &nV, vendas vetV[]){
    char resp;
    int qntdV;
    int codigo = validaINT("Informe o codigo de catalogacao do produto a ser vendido: ");
    int indice = ConsProdCODIGO(nP,vetP,codigo);
    if(indice == -1){
        cout << "Produto Inexitente" << endl;
        cout << "aperte enter para continuar";
        cin.get();
        system("cls");
    }else{
        qntdV = validaINT("Informe a quantidade  a ser vendida: ");
        if(qntdV <= vetP[indice].est){
            cout << "Quantidade a ser vendida: " << qntdV << endl;
            cout << "preco a ser pago: " << qntdV * vetP[indice].preco << endl;
        }else{
            cout << "Quantidade Maior que do Estoque." << endl;
            qntdV = vetP[indice].est;
            cout << "Quantidade a ser Vendida: " << qntdV << endl;
        }
       
        do{
            cout << "Deseja Confirmar a Compra? S/N: ";
            resp = toupper(cin.get());
            cin.ignore();
        }while( resp !='S' and resp != 'N' );

        if(resp == 'S'){
            vetP[indice].est -= qntdV;
            vetV[nV].cod = codigo;
            vetV[nV].totalV = qntdV;
            vetV[nV].precoV = qntdV * vetP[indice].preco;
            nV++;
            cout << "Venda Realizada" << endl;
            cout << "aperte enter para continuar";
            cin.ignore();
            cin.get();
            system("cls");
        }else{
            if(resp == 'N'){
                cout << "Venda Cancelada" << endl;
                cout << "aperte enter para continuar";
                cin.ignore();
                cin.get();
                system("cls");
            }
        }
    }
}
int validaINT(string frase){
     
    int x; 
    unsigned int i; 
    bool validada; 
    string info;
    do{ 
        validada=true;
        cout << frase;
        getline(cin,info);
        if(info=="") 
            validada=false; 
        else 
            if(not isdigit(info[0])) 
            validada=false; 
        else 
            for(i=1; i<info.length(); i++){
                if(not isdigit(info[i])){  
                validada=false; 
                break;
            }  
                 
        } 
        if(not validada) 
            cout <<"Numero invalido, digite novamente."<<endl; 
    }while(not validada); 
        x=atoi(info.c_str());  
        return x; 
}

float validaFloat(string frase){
    bool validada;
    int ponto;
    float n;
    string info;
    do{ 
        validada=true; 
        ponto=0; 
        cout << frase; 
        getline(cin,info);  
        if(info=="") 
            validada=false; 
        else 
            if(not isdigit(info[0])) //se nao for digito/sinal 
            validada=false; 
        else 
            for(unsigned int i=1; i<info.length(); i++) // varre demais posicoes 
                if(not isdigit(info[i])){ // se nao for digito 
                    if(isdigit(info[i-1]) and info[i]=='.' and ponto==0) 
                        ponto++; // permite um ponto apenas 
                else{ 
                    validada=false;
                    break; 
                } 
            } 
        if(not validada) 
        cout <<"Numero float invalido, digite novamente."<<endl; 
    }while(not validada); 
    n=atof(info.c_str()); 
    return n;
}

string validaSTRING(string frase){
    string nome;
    cout << frase;
    do{
        getline(cin,nome);
        if(nome == "" or nome ==" "){
            cout << "nome invalido, digite novamente." << endl;
        }
    }while(nome == "" or nome ==" " );
    return nome;
}
void achaProduto(int nP, produto vetP[]){
        int codigo;
        codigo = validaINT("digite o codigo do produto: ");
        int indice = ConsProdCODIGO(nP,vetP,codigo);
        if (indice == -1){
            cout << "produto inexistente" << endl;
            }else{
                relatorioP(vetP[indice]);
            }
        cout << "precione enter para continuar";
        cin.get();
        system("cls");
        
}

