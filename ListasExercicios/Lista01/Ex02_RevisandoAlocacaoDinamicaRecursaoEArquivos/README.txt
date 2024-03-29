Um parente seu estava te procurando para que você consertasse o seu celular que não estava enviando correntes no "zap".

Embora você sempre explique que cursar Ciência da Computação não é isso, a pessoa não entende e ainda espalha seus serviços para toda a vizinhança, dizendo que você faz bem rápido e de graça.

Você está prestes a ser encontrado e obrigado a realizar tal tarefa. Mas antes que isso aconteça use seus conhecimentos para escapar!

Você está preso em um labirinto, só que ao invés de paredes são seus primos, tios, avós e vizinhos desejando seus serviços.

Corra o mais rápido que puder e não seja pego!

Em cada caso de teste você receberá um arquivo de texto contendo o labirinto, formatado da seguinte forma:
    M N   //Sendo as Linhas e Colunas do Labirinto (Tipo: Inteiro)
    x y   //Sendo a Posição Inicial (Partida) (Tipo: Inteiro)
    ###....N //Sendo as linhas e colunas do Labirinto (Tipo: char)
    #.#...##
    #...#.##
    #.#.####
    #.#..... //Saída do Labirinto
    M#######

Observe que cada ponto '.' é uma posição válida enquanto que um '#' é uma pessoa bloqueando sua passagem;

Você deverá:

    Organizar todos os trechos de código solicitados em funções;
    Ler o labirinto de um arquivo de texto;
        Leia da entrada padrão o nome do arquivo e o abra em seguida para leitura; 
    Alocar dinamicamente a memória para o labirinto;
    Percorrer o labirinto a partir de uma posição inicial p(x,y) de maneira recursiva.
        Respeitar a ordem de busca (Cima, Direita, Baixo, Esquerda); 
    Marcar o seu caminho no labirinto com um caractere asterisco ('*');
    Ao encontrar a saída, você deve imprimir o labirinto com o seu percurso realizado;
    Percorra o labirinto e calcule:
        int npessoas = A quantidade de pessoas (Somar todos os '#');
        int caminhos = A quantidade de caminhos disponíveis (Somar todos os '.' no início);
        int visitados = A quantidade percorrida até encontrar a saída (Somar todos os '*' no final);
        double exploracao = O percentual de exploração do labirinto até encontrar a saída;
    Imprima os resultados obtidos no passo (6) da seguinte forma:
    printf("\nVoce escapou de todos! Ninguem conseguiu te segurar!\n");
    printf("Veja abaixo os detalhes da sua fuga:\n");
    printf("----Pessoas te procurando: %d\n", npessoas);
    printf("----Numero total de caminhos validos: %d\n", caminhos);
    printf("----Numero total de caminhos visitados: %d\n", visitados);
    printf("----Exploracao total do labirinto: %.1lf%%\n", exploracao);

Exemplo de Entrada:
        5 5
        1 1
        #####
        #.#..
        #.#.#
        #...#
        #####

Exemplo de Execução:
    Iterações    (1)      (2)      (3)      (4)      (5)      (6)      (7)      (8)
                #####    #####    #####    #####    #####    #####    #####    #####    
                #*#..    #*#..    #*#..    #*#..    #*#..    #*#..    #*#*.    #*#**    
                #.#.#    #*#.#    #*#.#    #*#.#    #*#.#    #*#*#    #*#*#    #*#*#   
                #...#    #...#    #*..#    #**.#    #***#    #***#    #***#    #***#    
                #####    #####    #####    #####    #####    #####    #####    #####    

Saída Esperada (Obs.: Somente a última iteração deve ser impressa na tela):
        #####
        #*#**
        #*#*#
        #***#
        #####

        Voce escapou de todos! Ninguem conseguiu te segurar!
        Veja abaixo os detalhes da sua fuga:
        ----Pessoas te procurando: 17
        ----Numero total de caminhos validos:   8
        ----Numero total de caminhos visitados: 8
        ----Exploracao total do labirinto: 100.0%
