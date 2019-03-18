#include <mt_sort.h>

#include <time.h>
#include <stdbool.h>

bool p_file(int t);

int main()
{
    //IMPOSTO IL SEME
    srand(time(NULL));

    static const unsigned long int N = 2000000000;

    //ISTANZIO L'ARRAY
    uint32_t *data = malloc(N * sizeof(*data));

    do
    {
        if(!data){
            free(data);
            data = malloc(N * sizeof(*data));
            puts("Rialloco...");
        }
    }while(data == NULL);

    //VARIABILI
    unsigned long int i;
    uint16_t n1, n2;
    uint32_t n3;

    //Randomize
    for(i = 0; i < N; i++){
        n1 = rand(); n2 = rand();
        n3 = ((uint32_t)n1 << 16) | n2;
        data[i] = n3;
    }

    puts("Assegnazione randomica effettuata con successo!\nPremere un tasto per continuare...");
    getchar();

    //starto il tempo
    time_t temp1 = time(NULL);

    //INIZIO L'ORDINAMENTO
    merge_sort(data, N);

    //FINE ORDINAMENTO E CALCOLO TEMPO
    time_t temp2 = time(NULL);

    bool ris = p_file(temp2 - temp1);

    if(ris){
        printf("\nFile di log salvato\n");
    }else{
        printf("\nFile di log non salvato\n");
    }

    //LIBERO LA MEMORIA
    free(data);
    return 0;
}

bool p_file(int t)
{
    FILE* fp = fopen("./Tempo esecuzione.txt", "w");

    fprintf(fp, "TIME OF EXECUTION: %d", t);

    if(fclose(fp) == EOF){
        return false;
    }else{
        return true;
    }
}
