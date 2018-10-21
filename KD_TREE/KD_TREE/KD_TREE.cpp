#include<stdlib.h>
#include<vector>
#include<cstdlib>
#include<iostream>
#include<time.h>
#include"sdl2\SDL.h"

using namespace std;

#define DIMENSAO 2

int compareX(const void*, const void*);
int compareY(const void*, const void*);

class No {
public:

	int pos[DIMENSAO];//X,Y
	int discriminador; //Plano de corte : 0=X, 1=Y
	No *filhoEsq, *filhoDir;
	
	No *criarKdTree(int **pontos, int profundidade, int tamanho) {//PASSAR TAMANHO DO VETOR
		
		if (tamanho == 0) return NULL;
		
		No *no = new No();

		int eixo, mediana;
		mediana = tamanho / 2;

		eixo = profundidade % DIMENSAO;

		no->discriminador = eixo;

		if (mediana == 0) {
			no->pos[0] = pontos[mediana][0];
			no->pos[1] = pontos[mediana][1];
			cout << "\tFOLHA: (" << no->pos[0] << "," << no->pos[1] << ")" << endl;
			cout << "\tRETORNANDO AO PAI\n";


			return no;
		}
			
		cout << "\nProfundidade " << profundidade << endl;

		if (eixo == 0) {
			qsort(pontos, tamanho, sizeof(pontos[tamanho-1]), compareX);
			cout << "-X\n";
		}
		else if (eixo == 1) {
			qsort(pontos, tamanho, sizeof(pontos[tamanho-1]), compareY);
			cout << "-Y\n";
		}


		for (int i = 0; i< tamanho; i++)
			cout << "(" << pontos[i][0] << ", " << pontos[i][1] << ") - ";

		no->pos[0] = pontos[mediana][0];
		no->pos[1] = pontos[mediana][1];


		cout << endl;

		cout << "No: (" << no->pos[0] << "," << no->pos[1]<< ")" << endl;

		cout << "\tFILHO ESQ\n";
		no->filhoEsq = criarKdTree(pontos , profundidade + 1, mediana);
		cout << "\tFILHO DIR\n";
		no->filhoDir = criarKdTree(pontos + (mediana+1), profundidade + 1, tamanho - mediana - 1);

		cout << "<=RETORNANDO AO PAI\n";
		return no;

	}
	
};

int compareX(const void* p1, const void* p2) {
	int *a, *b;
	a = *(int**)p1;
	b = *(int**)p2;

	if (a[0] < b[0]) return -1;
	if (a[0] == b[0]) return 0;
	if (a[0] > b[0]) return 1;
}

int compareY(const void* p1, const void* p2) {
	int *a, *b;
	a = *(int**)p1;
	b = *(int**)p2;

	if (a[1] < b[1]) return -1;
	if (a[1] == b[1]) return 0;
	if (a[1] > b[1]) return 1;
}

int main(int argc, char **argv) {


	int tam = 5;

	int **xy;
	
	xy = (int**) calloc(tam, sizeof(int*));
	
	srand(time(NULL));

	for (int i = 0; i< tam; i++) {
		xy[i] = (int*) calloc( DIMENSAO ,sizeof(int));
		xy[i][0] = rand() % 10;
		xy[i][1] = rand() % 10;
	}


	/*int pos[6][DIMENSAO]= { {2,3},{5,4},{9,6},{4,7},{8,1},{7,2} };

	for (int i = 0; i< tam; i++) {
		xy[i] = (int*)calloc(DIMENSAO, sizeof(int));
		xy[i] = pos[i];
	}*/

	for (int i = 0; i< tam; i++)
		cout << "(" << xy[i][0] << ", " << xy[i][1] <<  ") - ";

	cout << endl;


	No *no;
	no = new No();
	no = no->criarKdTree(xy, 0, tam);
	cout << endl;
	cout << endl;

	for (int i = 0; i< tam; i++)
		cout << "(" << xy[i][0] << ", " << xy[i][1] << ") - ";

	//qsort((xy), tam, sizeof(xy[0]), compareX);

	cout << endl;

	/*for (int i = 0; i< tam; i++)
		cout << "(" << xy[i][0] << ", " << xy[i][1] << ") - ";
	*/

	//for (int i = 0; i< tam; i++)
	//cout << ((xy[i]))[0] << ", " << (((xy[i]))[1]) << endl;
	//cout << (*(xy + i))[0] << ", " << ((*(xy + i))[1]) << endl;


	return 0;
}
