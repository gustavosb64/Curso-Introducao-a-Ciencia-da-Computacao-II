
int i, j, k = 0;
for (i=0; i<m; i++)
    for (j=0; j<m; j++)
        vetor[k++] = matriz[i][j];			

for(i = 0; i < m*m-1; i++){
    for(j = 0; j < m*m-1-i; j++){
        if (vetor[j] > vetor[j+1]){
            int aux = vetor[j];
            vetor[j] = vetor[j+1];
            vetor[j+1] = aux;		
        }
    }
}

k = 0;
for (i=0; i<m; i++){
    for (j=0; j<m; j++){
        matriz[i][j] = vetor[k++];


int i, j, k = 0;
//for (i=0; i<m; i++)
    
func1(vetor, m, i){

    if (i >= m) return;

    for (j=0; j<m; j++)
        vetor[k++] = matriz[i][j];			
    
    return func1(m, i+1);
}

//for(i = 0; i < m*m-1; i++){
func2(vetor, m, i){

    if (i >= m*m -1) return;

    for(j = 0; j < m*m-1-i; j++){
        if (vetor[j] > vetor[j+1]){
            int aux = vetor[j];
            vetor[j] = vetor[j+1];
            vetor[j+1] = aux;		
        }
    }

    func2(vetor, m, i+1);
}

k = 0;
for (i=0; i<m; i++){
    for (j=0; j<m; j++){
        matriz[i][j] = vetor[k++];



int i, j, k = 0;

//BLOCO 1
for (i=0; i<m; i++)
    for (j=0; j<m; j++)
        vetor[k++] = matriz[i][j];   //(m)^2 * a
//Total bloco 1: (m)^2 * a

//BLOCO 2
for(i = 0; i < m*m-1; i++){
    for(j = 0; j < m*m-1; j++){
        if (vetor[j] > vetor[j+1]){  //(m*m-1)^2 * (a+c)
            int aux = vetor[j];
            vetor[j] = vetor[j+1];   //(m*m-1)^2 * a
            vetor[j+1] = aux;		 //(m*m-1)^2 * a
        }
    }
}
//Total bloco 2: (m*m-1)^2 * (3a+c)

k = 0;
//BLOCO 3
for (i=0; i<m; i++){
    for (j=0; j<m; j++){
        matriz[i][j] = vetor[k++]; //m^2 * a
//Total bloco 3: (m)^2 * a


