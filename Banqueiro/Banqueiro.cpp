#include <iostream>

using namespace std;

int main(){
	/*
	Variáveis:
		n_processos: número de processos;
		rec: Recursos Totais;
		rec_disponiveis: Recursos disponiveis para alocação.
	 */
	int n_processos,rec,rec_disp;
	int rec_aloc = 0;

	cout << "Informe a quantidade de processos e a quantidade de recursos disponiveis(Separados por espaço): ";
	cin >> n_processos >> rec;
	cout << endl;

	/*
		Alocando uma matriz de n_processos linhas.
	 */
	int** mat_rec = (int**)malloc(n_processos*sizeof(int*));

	int* processo_exec = (int*)calloc(n_processos,sizeof(int));


	for (int i = 0; i < n_processos; ++i)
	{
			/*
				Variáveis:
					aloc: Recursos alocados a esse processo;
					max:  Recursos máximos necessários para completar a execução desse processo.
			 */
			int aloc,max;

			/*
				Alocação de um processo.
			 */
			int* p = (int*)malloc(2*sizeof(int));

			cout << "Informe o número de recursos alocados e máximos necessários do processo "<<i+1<<": ";
			cin >> aloc >> max;

			
			rec_aloc = rec_aloc + aloc;
			p[0] = aloc;
			p[1] = max;
			mat_rec[i] = p;
	}

	/*
		Calculo dos recursos disponiveis, calculando os recursos totais menos os recursos alocados
	*/

	rec_disp = rec - rec_aloc;

	for (int i = 0; i < n_processos; ++i)
	{
		if(processo_exec[i]==0)
		{
			if((rec_disp+mat_rec[i][0]) >= mat_rec[i][1])
			{
				processo_exec[i] = 1;
				rec_disp += mat_rec[i][0];
				printf("P%d foi executado\n", i+1);
				i = -1;
			}
		}
	}
	int i;
	for (i = 0; i < n_processos; ++i)
	{
		//cout << processo_exec[i] << endl;
		if(processo_exec[i] == 0){
			printf("Estado inseguro\n");
			break;
		}
	}
	if (i == n_processos){
		cout << "Estado Seguro"<<endl;
	}
	return 0;
}