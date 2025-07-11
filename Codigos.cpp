#include <iostream>
#include <cmath>
#include <iomanip>
#include <time.h>
#include <conio.h>
#include <windows.h>
#define N 9

using namespace std;

char m[N][N], i[6] = {'@', 'l', 'Y', 'H', 'C', 'F'};
int p[2] = {N/2, N/2};
int n=0, t=0, k=0, l=0, o=0, f=0;
string objetivo;

int foradomapa(int xy){
    int a=0;
    if(xy>=0 && xy<=N-1){
        a=1;
    }
    else{
        a=0;
    }
    return a;
}

void mover(){
    bool fim = false;

    while(!fim){
        if (kbhit()){
            fim = true;
            switch (getch())
            {
                case 'w':
                case 'W':  
                    p[0] -= foradomapa(p[0]);
                    break;
                case 's':
                case 'S':
                    p[0] += foradomapa(p[0]);
                    break;
                case 'a':
                case 'A':
                    p[1] -= foradomapa(p[1]);
                    break;
                case 'd':
                case 'D':
                    p[1] += foradomapa(p[1]);
                    break;
                default:
                fim = false;
                    cout << "Tecla invalida";
            }
        }
    }
}

void checar(){
    if(p[0]<0){
        p[0]=0;
    }
    if(p[0]>8){
        p[0]=8;
    }
    if(p[1]<0){
        p[1]=0;
    }
    if(p[1]>8){
        p[1]=8;
    }
}

void mapa(){
    system("cls");
    cout << "Pedra = @ | Arvore = Y | Animal = M | Graveto = l | Player = "<< (char)153 << endl;
    cout << "--- inventario ---" << endl << "Pedras = " << n << endl << "Carne = " << o << endl << "Arvores = " << t << endl << "Gravetos = " << k << endl << "Couro = " << l << endl << "Frutas = " << f << endl;
    cout << "-------------------------------" << endl;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(i==p[0] && j==p[1]){
                cout << setw(3) << (char)153;
            }
            else{
                cout << setw(3) << m[i][j];
            }
        }
        cout << endl;
    }
    cout << "-------------------------------" << endl;
    cout << objetivo << endl;
}

void itens(){
    for(int i = 0; i<(N*N)*0.1; i++){
        int x = rand()%N;
        int y = rand()%N;
        if(m[x][y]=='#' && !(x==N/2 && y==N/2)){
            m[x][y] = '@';
        }else{
            i--;
        }
    }
    for(int i = 0; i<(N*N)*0.1; i++){
        int x = rand()%N;
        int y = rand()%N;
        if(m[x][y]=='#' && !(x==N/2 && y==N/2)){
            m[x][y] = 'M';
        }else{
            i--;
        }
    }
    for(int i = 0; i<(N*N)*0.1; i++){
        int x = rand()%N;
        int y = rand()%N;
        if(m[x][y]=='#' && !(x==N/2 && y==N/2)){
            m[x][y] = 'Y';
        }else{
            i--;
        }
    }
    for(int i = 0; i<(N*N)*0.15; i++){
        int x = rand()%N;
        int y = rand()%N;
        if(m[x][y]=='#' && !(x==N/2 && y==N/2)){
            m[x][y] = 'l';
        }else{
            i--;
        }
    }
}

void pergunta(){
    char x;
    if(m[p[0]][p[1]]!='#'){
        cout << "Quer pegar esse item? (S/N)" << endl;
        cin >> x;
        if(x=='s' || x=='S'){
            switch (m[p[0]][p[1]])
            {
            case '@':
                n++;
                break;
            case 'Y':
                t++;
                if(rand()%2){
                    f++;
                }
                break;
            case 'l':
                k++;
                break;
            case 'M':
                if(rand()%2){
                    l++;
                }
                else{
                    o++;
                }
                break;
            default:
                break;
            }
            m[p[0]][p[1]]='#';
        }
    }
}

int main(){
    srand(time(NULL));
    int i, j, escolha;
    bool repouso=false, luz=false, comida=false, construcao=false;

    cout << "Escolha um objetivo: " << endl << "1 - Repouso (2 arvores e 1 couro)" << endl << "2 - Luz e calor (4 gravetos e 2 pedras)" << endl << "3 - Comida (1 fruta e 1 carne)" << endl << "4 - Construcao (8 pedras e 4 arvores)" << endl;

    while(!repouso && !luz && !comida && !construcao && cin>>escolha){
        switch (escolha)
        {
        case 1:
            repouso=true;
            objetivo="Objetivo: 2 arvores e 1 couro";
            break;
        case 2:
            luz=true;
            objetivo="Objetivo: 4 gravetos e 2 pedras";
            break;
        case 3:
            comida=true;
            objetivo="Objetivo: 1 fruta e 1 carne";
            break;
        case 4:
            construcao=true;
            objetivo="Objetivo: 8 pedras e 4 arvores";
            break;
        default:
        cout << "Escolha invalida, tente novamente!" << endl;
            break;
        }
    }
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            m[i][j] = '#';
        }
    }
    itens();
    while(repouso || luz || comida || construcao){
        mapa();
        mover();
        checar();
        pergunta();
        if(repouso){
            if(t>=2 && l>=1){
                repouso = false;
            }
        }
        if(luz){
            if(k>=4 && n >=2){
                luz = false;
            }
        }
        if(comida){
            if(f>=1 && o>=1){
                comida = false;
            }
        }
        if(construcao){
            if(n>=8 && t>=4){  
                construcao=false;
            }
        }
    }
    system("cls");
    cout << "Objetivo concluido" << endl;
    system("pause");
}