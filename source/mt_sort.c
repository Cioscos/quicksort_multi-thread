#include <mt_sort.h>

// SINCRONIZZO IL MUTEX PER LA VISUALIZZAZIONE DELL'OUTPUT SUI THREADS.
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void merge(uint32_t *start, uint32_t *mid, uint32_t *end)
{
    uint32_t *res = malloc((end - start)*sizeof(*res));
    uint32_t *lhs = start, *rhs = mid, *dst = res;

    while (lhs != mid && rhs != end)
        *dst++ = (*lhs < *rhs) ? *lhs++ : *rhs++;

    while (lhs != mid)
        *dst++ = *lhs++;

    // copy results
    memcpy(start, res, (rhs - start) * sizeof *res);
    free(res);
}

void merge_sort_mt(uint32_t *start, unsigned int len, uint32_t depth)
{
    if (len < 2)
        return;

    if (depth <= 0 || len < 4)
    {
        merge_sort_mt(start, len/2, 0);
        merge_sort_mt(start+len/2, len-len/2, 0);
    }
    else
    {
        struct Params params = { start, len/2, depth/2 };
        pthread_t thrd;

        pthread_mutex_lock(&mtx);
        printf("avvio subthread...\n");
        pthread_mutex_unlock(&mtx);

        // CREO THREAD
        pthread_create(&thrd, NULL, merge_sort_thread, &params);

        // CHIAMATA RICORSIVA TOP-END
        merge_sort_mt(start+len/2, len-len/2, depth/2);

        // join thread chiamato
        pthread_join(thrd, NULL);

        pthread_mutex_lock(&mtx);
        printf("fine subthread.\n");
        pthread_mutex_unlock(&mtx);
    }

    // ORDINO LA PARTIZIONE.
    merge(start, start+len/2, start+len);
}

//Procedura che invoca il merge sort. Passo solo i parametri dati all'algoritmo di marge sort.
void *merge_sort_thread(void *pv)
{
    struct Params *params = pv;
    merge_sort_mt(params->start, params->len, params->depth);
    return pv;
}

// Chiamata main
void merge_sort(uint32_t *start, unsigned int len)
{
    merge_sort_mt(start, len, 4); // 4 is a nice number, will use 7 threads.
}
