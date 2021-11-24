/*************************************************/
/**                                             **/
/**   Mariana Afeche Cipolla          4487495   **/
/**   Exercício-Programa 3                      **/
/**                                             **/
/*************************************************/

#include <stdio.h>
#include <stdlib.h>
#define mmax 90
#define nmax 90
void sorteiai (int *i, int m, int num) /*função que sorteia um valor para i*/
	{
	*i = num % m;
	while (*i>m-1) /*enquanto o valor for maior do que o número de linhas da matriz*/
		{
		*i = *i % m;
		}
	}
void sorteiaj (int *j, int m, int n, int num) /*função que sorteia um valor para j*/
	{
	*j = (num / m) % n;
	while (*j>n-1) /*enquanto o valor for maior do que o número de colunas da matriz*/
		{
		*j = (*j / m) % n;
		}
	}
void montamatriz(int T[][nmax], int i, int j, int m, int n) /*ao ser sorteado o local de uma bomba, soma 1 em todas as casas adjacentes e atribui -1 à casa sorteada*/
	{
	T[i][j] = -1;
	if (i > 0) /*se a casa sorteada não está na primeira linha*/
		{
		if (T[i-1][j] != -1) /*se a casa não tem uma bomba*/
			T[i-1][j] += 1;
		if (j > 0) /*se a casa sorteada não está na primeira coluna*/
			if (T[i-1][j-1] != -1)
				T[i-1][j-1] += 1;
		if (j < n-1) /*se a casa sorteada não está na última coluna*/
			if (T[i-1][j+1] != -1)
				T[i-1][j+1] += 1;
		}
	if (j > 0)
		if (T[i][j-1] != -1)
			T[i][j-1] += 1;
	if (j < n-1)
		if (T[i][j+1] != -1)
			T[i][j+1] += 1;
	if (i < m-1) /*se a casa sorteada não está na última linha*/
		{
		if (T[i+1][j] != -1)
			T[i+1][j] += 1;
		if (j > 0)
			if (T[i+1][j-1] != -1)
				T[i+1][j-1] += 1;
		if (j < n-1)
			if (T[i+1][j+1] != -1)
				T[i+1][j+1] += 1;
		}
	}
void imprimematriz(char A[][nmax], int m, int n) /*imprime a matriz para o usuario*/
	{
	int i, j;
	printf ("       ");
	for (j=1; j<=n; j++)
		{
		if (j<9)
			printf ("%d  ", j); /*imprime os números das colunas*/
		else
			printf ("%d ", j);
		}
	printf ("\n    +-");
	for (j=0; j<n; j++)
		printf ("---");
	printf ("+\n");
	for (i=0; i<m; i++)
		{
		if (i+1<10)
			printf ("  %d | ", i+1); /*imprime os números das linhas*/
		else
			printf (" %d | ", i+1);
		for (j=0; j<n; j++)
			printf (" %c ", A[i][j]); /*imprime as casas da matriz*/
		printf ("| %d\n", i+1);
		}
	printf ("    +-");
	for (j=0; j<n; j++)
		printf ("---");
	printf ("+\n");
	printf ("       ");
	for (j=1; j<=n; j++)
		{
		if (j<9)
			printf ("%d  ", j); /*imprime os números das colunas*/
		else
			printf ("%d ", j);
		}
	printf ("\n");
	}
int checaletra (char letra) /*função que checa se a letra é uma das letras válidas no jogo*/
	{
	int certo /*devolve 1 se a letra é uma das letras permitidas e 0 caso contrário*/;
	if ((letra == 'a') || (letra == 'A') || (letra == 'm') || (letra == 'M') || (letra == 'd') || (letra == 'D'))
		certo = 1;
	else
		certo = 0;
	return certo;
	}
int checalinhacoluna (int louc, int moun) /*função que checa se a linha ou coluna fornecida está no intervalo delimitado*/
	{
	int certo; /*devolve 1 se a linha ou coluna estiver no intervalo delimitado e 0 caso contrário*/
	if ((louc >= 0) && (louc <= moun-1))
		certo = 1;
	else
		certo = 0;
	return certo;
	}
void abrir (int T[][nmax], int B[][nmax], char A[][nmax], int m, int n, int i, int j, int *bomba /*manda 1 para a varíavel se o jogador clicar em uma bomba, e 0 caso contrário*/, int *livres) /*função que abre as casas do jogo*/
	{
	B[i][j] = 1; /*marca na matriz B que a casa foi aberta*/
	*livres = *livres - 1;
	if (T[i][j] > 0) /*se o jogador clicou em uma posição na qual há bombas nas posições adjacentes*/
		A[i][j] = T[i][j] + 48; /*passa o número de bombas adjacentes para a matriz a ser mostrada*/
	else if (T[i][j] < 0) /*se o jogador clicou em uma posição na qual há uma bomba*/
		{
		*bomba = 1;
		for (i=0; i<m; i++)
			for (j=0; j<n; j++)
				{
				B[i][j] = 1; /*marca na matriz B que todas as casas foram abertar*/
				if (T[i][j] == -1)
					A[i][j] = '@'; /*a matriz a ser impressa recebe @ nas casas que tem bomba*/
				else
					A[i][j] = T[i][j] + 48;
				}
		}
	else /*se o jogador clicou em uma posição na qual não há bombas nem nela nem nas posições adjacentes*/
		{
		A[i][j] = T[i][j] + 48; /*passa o número zero para a matriz a ser mostrada*/
		if (i > 0) /*dessa parte em diante, verifica qual a posição da casa e verifica se as casas em volta devem e podem ser abertas (verifica se não são casas da borda)*/
			{
			if (B[i-1][j] == 0) /*se a casa ainda não foi aberta*/
				abrir (T, B, A, m, n, i-1, j, bomba, livres);
			if (j > 0)
				if (B[i-1][j-1] == 0) /*se a casa ainda não foi aberta*/
					abrir (T, B, A, m, n, i-1, j-1, bomba, livres);
			if (j < n-1)
				if (B[i-1][j+1] == 0) /*se a casa ainda não foi aberta*/
					abrir (T, B, A, m, n, i-1, j+1, bomba, livres);
			}
		if (j > 0)
			if (B[i][j-1] == 0) /*se a casa ainda não foi aberta*/
				abrir (T, B, A, m, n, i, j-1, bomba, livres);
		if (j < n-1)
			if (B[i][j+1] == 0) /*se a casa ainda não foi aberta*/
				abrir (T, B, A, m, n, i, j+1, bomba, livres);
		if (i < m-1)
			{
			if (B[i+1][j] == 0) /*se a casa ainda não foi aberta*/
				abrir (T, B, A, m, n, i+1, j, bomba, livres);
			if (j > 0)
				if (B[i+1][j-1] == 0) /*se a casa ainda não foi aberta*/
					abrir (T, B, A, m, n, i+1, j-1, bomba, livres);
			if (j < n-1)
				if (B[i+1][j+1] == 0) /*se a casa ainda não foi aberta*/
					abrir (T, B, A, m, n, i+1, j+1, bomba, livres);
			}
		}
	}
void marcar (char A[][nmax], int B[][nmax], int i, int j, int *marcadas, int *livres) /*função que marca as casas do jogo*/
	{
	A[i][j] = '*'; 
	B[i][j] = -1;
	*marcadas = *marcadas + 1;
	*livres = *livres - 1;
	}
void desmarcar (int B[][nmax], char A[][nmax], int i, int j, int *marcadas, int *livres) /*função que desmarca as casas do jogo*/
	{
	A[i][j] = '.';
	B[i][j] = 0;
	*marcadas = *marcadas - 1;
	*livres = *livres + 1;
	}
int main()
	{
	int m, n, z, T[mmax][nmax] /*matriz que marca -1 nas casas em que há bomba e k nas outras casas, sendo k o número de bombas adjacentes*/, linha, coluna, nmarcadas, nlivres, s, cont, i, j, B[mmax][nmax] /*matriz que marca 1 se a casa está aberta, -1 se a casa está marcada e 0 se a casa está fechada*/, num, perdeu /*vale 0 enquanto o jogador não perder, e 1 se ele clicar em uma bomba*/;
	char letra, A[mmax][nmax] /*matriz que é mostrada para o usuario*/;
	m = 0;
	while ((m < 3) || (m > mmax)) /*pede por um novo valor de m até que este esteja no intervalo desejado*/
		{
		printf ("Numero de linhas (3 <= m <= 90): ");
		scanf ("%d", &m);
		}
	n = 0;
	while ((n < 3) || (n > nmax)) /*pede por um novo valor de n até que este esteja no intervalo desejado*/
		{
		printf ("Numero de colunas (3 <= n <= 90): ");
		scanf ("%d", &n);
		}
	z = 0;
	while ((z < 1) || (z > m*n)) /*pede por um novo valor de z até que este esteja no intervalo desejado*/
		{	
		printf ("Numero de bombas (1 <= z <= %d): ", m*n);	
		scanf ("%d", &z);
		}
	s = 0;
	while ((s < 1) || (s > 12345)) /*pede por um novo valor de s até que este esteja no intervalo desejado*/
		{	
		printf ("Semente (1 <= s <= 12345): ");
		scanf ("%d", &s);
		}
	for (i=0; i<m; i++)
		for (j=0; j<n; j++)
		{
		T[i][j] = 0; /*a matriz começa com zero em todas as casas*/
		B[i][j] = 0; /*a matriz começa com todas as casas fechadas*/
		A[i][j] = '.'; /*a matriz começa mostrando pontos nos lugares das casas*/
		}	
	printf ("Bem vindo ao BuscaBombas!\n");
	imprimematriz (A, m, n);
	nmarcadas = 0; /*atribui 0 ao número de casas marcadas*/
	nlivres = n*m; /*diz que nenhuma casa foi clicada ainda*/
	printf ("Proximo chute: ");
	scanf (" %c %d %d", &letra, &linha, &coluna);
	linha = linha - 1; /*já que, na matriz, os elementos da linha vão de 0 a n-1*/
	coluna = coluna - 1; /*já que, na matriz, os elementos da coluna vão de 0 a n-1*/
	srand(s);
	for (cont=0; cont<z; cont++) /*sorteia valor de i e j para posicionar as z bombas*/
		{
		num = rand();
		sorteiai (&i, m, num); 
		sorteiaj (&j, m, n, num);
		while ((i == linha) && (j == coluna)) /*se a posição sorteada para colocar uma bomba foi a posição que o jogador escolheu, troca o lugar da bomba, para que ele não perca na primeira rodada*/
			{
			num = rand();
			sorteiai (&i, m, num); /*sorteia um valor de i*/
			sorteiaj (&j, m, n, num); /*sorteia um valor de j*/
			}
		while (T[i][j] == -1) /*se ele sorteou um lugar no qual já há uma bomba, continua sorteando até encontrar um novo*/
			{
			num = rand();
			sorteiai (&i, m, num); 
			sorteiaj (&j, m, n, num); 
			while ((i == linha) && (j == coluna)) /*se foi sorteada a casa na qual o jogador clicou, troca de casa para que ele não perca na primeira rodada*/
				{
				num = rand();
				sorteiai (&i, m, num); /*sorteia um valor de i*/
				sorteiaj (&j, m, n, num); /*sorteia um valor de j*/
				}
			}
		montamatriz (T, i, j, m, n);
		}
	perdeu = 0;
	abrir (T, B, A, m, n, linha, coluna, &perdeu, &nlivres);
	printf ("Por enquanto: %d/%d marcadas, %d livres.\n", nmarcadas, z, nlivres);
	imprimematriz (A, m, n);
	while ((perdeu == 0) && ((nlivres > 0) && (nlivres != (z-nmarcadas)))) /*enquanto o jogador não houver perdido o jogo e ainda houver casas fechadas que não sejam casas que possuem bombas*/
		{
		printf ("\nProximo chute: ");
		scanf (" %c %d %d", &letra, &linha, &coluna);
		linha = linha - 1;
		coluna = coluna - 1;
		if ((checaletra(letra) == 1) && (checalinhacoluna(linha, m) == 1) && (checalinhacoluna(coluna, n))) /*se o jogador digitou a letra e valores de linha e coluna corretos*/
			{
			if (B[linha][coluna] == 0) /*se a casa ainda não foi aberta nem marcada*/
				{
				if ((letra == 'a') || (letra == 'A')) /*se o jogador deseja abrir a casa*/
					{
					abrir (T, B, A, m, n, linha, coluna, &perdeu, &nlivres);
					if ((perdeu == 0) && ((nlivres > 0) && (nlivres >= (z-nmarcadas)))) /*se o jogador não perdeu nem abriu todas as casas, mas o número de casas fechadas é diferente do número de bombas menos o número de casas marcadas*/
						{
						printf ("Por enquanto: %d/%d marcadas, %d livres.\n", nmarcadas, z, nlivres);
						imprimematriz (A, m, n);
						}	
					}
				else if ((letra == 'm') || (letra == 'M')) /*se o jogador deseja marcar a casa*/
					{
					marcar (A, B, linha, coluna, &nmarcadas, &nlivres);
					printf ("Por enquanto: %d/%d marcadas, %d livres.\n", nmarcadas, z, nlivres);
					imprimematriz (A, m, n);
					}
				else /*se ele deseja desmarcar uma casa que não foi marcada*/
					printf ("Sem efeito.\n");
				}
			else if (B[linha][coluna] == -1) /*se a casa está marcada*/
				{
				if ((letra == 'd') || (letra == 'D')) /*se o jogador deseja desmarcar a casa*/
					{
					desmarcar (B, A, linha, coluna, &nmarcadas, &nlivres);
					printf ("Por enquanto: %d/%d marcadas, %d livres.\n", nmarcadas, z, nlivres);
					imprimematriz (A, m, n);
					}
				else /*se ele deseja abrir ou marcar uma casa já marcada*/
					printf ("Sem efeito.\n");
				}
			else /*se a casa já está aberta*/
				printf ("Sem efeito.\n");
			}
		else /*se a letra ou a linha ou a coluna estão erradas*/
			{
			if (checaletra(letra) == 0)
				printf ("Comando deve ser A, D ou M\n");
			if (checalinhacoluna(linha, m) == 0)
				printf ("Linha deve estar entre 1 e %d\n", m);
			if (checalinhacoluna(coluna, n) == 0)
				printf ("Coluna deve estar entre 1 e %d\n", n);
			}
		}
	if (perdeu == 1) /*se o laço terminou porque o jogador perdeu*/
		{
		printf ("BOOOOM!  Voce acaba de pisar numa bomba!\n");
		imprimematriz (A, m, n);
		}
	else /*se o laço terminou porque não há mais casas para abrir ou porque todas as casas fechadas possuem bombas*/
		{
		if ((nlivres == 0) || (nlivres != (z-nmarcadas)))
			imprimematriz (A, m, n);
		printf ("\nPARABENS!\n");
		}
	return 0;
	}
	

