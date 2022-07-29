1 Objetivo do Trabalho
Você deverá implementar os diferentes estágios do clássico jogo “Campo Minado”.
2 Campo Minado
Campo Minado é um popular jogo de computador para um jogador. Foi inventado por
Robert Donner em 1989 e tem como objetivo revelar um campo de minas sem que alguma
seja detonada. Este jogo tem sido reescrito para as mais diversas plataformas, sendo a
sua versão mais popular a incluída nativamente com o Microsoft Windows.
2.1 Regras
A área de jogo consiste num campo de quadrados retangular. Cada quadrado pode ser
revelado clicando sobre ele, e se o quadrado clicado contiver uma mina, então o jogo
acaba. Se, por outro lado, o quadrado não contiver uma mina, uma de duas coisas
poderá acontecer:
1. Um número aparece, indicando a quantidade de quadrados adjacentes que contêm
minas;
2. Nenhum número aparece. Neste caso, o jogo revela automaticamente os quadrados
que se encontram adjacentes ao quadrado vazio, já que não podem conter minas;
O jogo é ganho quando todos os quadrados que não têm minas são revelados.
1
3 Proposta
Seu programa deverá resolver as diversas etapas do jogo campo minado. Para facilitar o
processo de desenvolvimento e correção, seu programa deverá implementar 3 diferentes
módulos: (i) Leitura, (ii) inicialização do tabuleiro e (iii) ação do usuário. Cada um destes
módulos deverão ser executados de acordo com uma opção inteira que será fornecida via
stdin. Em seguida, ele deverá ler o nome do arquivo que contém o tabuleiro inicial do
jogo. Deste modo, um exemplo de arquivo de entrada é:
1
1.board
Onde a opção 1 foi selecionada, com o tabuleiro descrito no arquivo 1.board.

Opções:
    Opção 1: Imprimir o tabuleiro
    Opção 2: Imprimir o tabuleiro com as dicas
    Opção 3: Controle do Usuário
