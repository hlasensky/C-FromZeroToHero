/**
 * Kostra programu pro 2. projekt IZP 2022/23
 *
 * Jednoducha shlukova analyza: 2D nejblizsi soused.
 * Single linkage
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>   // sqrtf
#include <limits.h> // INT_MAX

/*****************************************************************
 * Ladici makra. Vypnout jejich efekt lze definici makra
 * NDEBUG, napr.:
 *   a) pri prekladu argumentem prekladaci -DNDEBUG
 *   b) v souboru (na radek pred #include <assert.h>
 *      #define NDEBUG
 */
#ifdef NDEBUG
#define debug(s)
#define dfmt(s, ...)
#define dint(i)
#define dfloat(f)
#else

// vypise ladici retezec
#define debug(s) printf("- %s\n", s)

// vypise formatovany ladici vystup - pouziti podobne jako printf
#define dfmt(s, ...) printf(" - "__FILE__ \
                            ":%u: "s      \
                            "\n",         \
                            __LINE__, __VA_ARGS__)

// vypise ladici informaci o promenne - pouziti dint(identifikator_promenne)
#define dint(i) printf(" - " __FILE__ ":%u: " #i " = %d\n", __LINE__, i)

// vypise ladici informaci o promenne typu float - pouziti
// dfloat(identifikator_promenne)
#define dfloat(f) printf(" - " __FILE__ ":%u: " #f " = %g\n", __LINE__, f)

#endif

/*****************************************************************
 * Deklarace potrebnych datovych typu:
 *
 * TYTO DEKLARACE NEMENTE
 *
 *   struct obj_t - struktura objektu: identifikator a souradnice
 *   struct cluster_t - shluk objektu:
 *      pocet objektu ve shluku,
 *      kapacita shluku (pocet objektu, pro ktere je rezervovano
 *          misto v poli),
 *      ukazatel na pole shluku.
 */

struct obj_t
{
    int id;
    float x;
    float y;
};

struct cluster_t
{
    int size;
    int capacity;
    struct obj_t *obj;
};

/*****************************************************************
 * Deklarace potrebnych funkci.
 *
 * PROTOTYPY FUNKCI NEMENTE
 *
 * IMPLEMENTUJTE POUZE FUNKCE NA MISTECH OZNACENYCH 'TODO'
 *
 */

/*
 Inicializace shluku 'c'. Alokuje pamet pro cap objektu (kapacitu).
 Ukazatel NULL u pole objektu znamena kapacitu 0.
*/
void init_cluster(struct cluster_t *c, int cap)
{
    assert(c != NULL);
    assert(cap >= 0);
    c->capacity = cap;
    c->size = 0;
    c->obj = malloc(cap * sizeof(struct obj_t));
}

/*
 Odstraneni vsech objektu shluku a inicializace na prazdny shluk.
 */
void clear_cluster(struct cluster_t *c)
{
    free(c->obj);
    c->obj = NULL;
    c->size = 0;
    c->capacity = 0;
}

/// Chunk of cluster objects. Value recommended for reallocation.
const int CLUSTER_CHUNK = 10;

/*
 Zmena kapacity shluku 'c' na kapacitu 'new_cap'.
 */
struct cluster_t *resize_cluster(struct cluster_t *c, int new_cap)
{
    // TUTO FUNKCI NEMENTE
    assert(c);
    assert(c->capacity >= 0);
    assert(new_cap >= 0);

    if (c->capacity >= new_cap)
        return c;

    size_t size = sizeof(struct obj_t) * new_cap;

    void *arr = realloc(c->obj, size);
    if (arr == NULL)
        return NULL;

    c->obj = (struct obj_t *)arr;
    c->capacity = new_cap;
    return c;
}

/*
 Prida objekt 'obj' na konec shluku 'c'. Rozsiri shluk, pokud se do nej objekt
 nevejde.
 */
void append_cluster(struct cluster_t *c, struct obj_t obj)
{
    c->obj[c->size].id = obj.id;
    c->obj[c->size].x = obj.x;
    c->obj[c->size].y = obj.y;
    int newSize = c->size + 1;
    c->size = newSize;
}

void sort_cluster(struct cluster_t *c);

/*
 Do shluku 'c1' prida objekty 'c2'. Shluk 'c1' bude v pripade nutnosti rozsiren.
 Objekty ve shluku 'c1' budou serazeny vzestupne podle identifikacniho cisla.
 Shluk 'c2' bude nezmenen.
 */
void merge_clusters(struct cluster_t *c1, struct cluster_t *c2)
{
    assert(c1 != NULL);
    assert(c2 != NULL);

    int newCap = c1->size + c2->size;
    if (newCap > c1->capacity)
    {
        resize_cluster(c1, newCap);
    }
    for (int i = 0; i < c2->size; i++)
    {
        append_cluster(c1, c2->obj[i]);
    }
    sort_cluster(c1);

}

/**********************************************************************/
/* Prace s polem shluku */

/*
 Odstrani shluk z pole shluku 'carr'. Pole shluku obsahuje 'narr' polozek
 (shluku). Shluk pro odstraneni se nachazi na indexu 'idx'. Funkce vraci novy
 pocet shluku v poli.
*/
int remove_cluster(struct cluster_t *carr, int narr, int idx)
{
    assert(idx < narr);
    assert(narr > 0);
    int capacity = narr;
    for (int i = idx; i < capacity; i++)
    {
        carr[i] = carr[i + 1];
    }
    int newCapArr = --capacity;
    return newCapArr;
}

/*
 Pocita Euklidovskou vzdalenost mezi dvema objekty.
 */
float obj_distance(struct obj_t *o1, struct obj_t *o2)
{
    assert(o1 != NULL);
    assert(o2 != NULL);

    double distance = sqrt(powf((o1->x - o2->x), 2) + powf((o1->y - o2->y), 2));
    // printf("%f", distance);
    return distance;
}

/*
 Pocita vzdalenost dvou shluku.
*/
float cluster_distance(struct cluster_t *c1, struct cluster_t *c2, int *c1id, int *c2id)
{
    assert(c1 != NULL);
    assert(c1->size > 0);
    assert(c2 != NULL);
    assert(c2->size > 0);

    double minDistance = obj_distance(&c1->obj[0], &c2->obj[1]);

    for (int c1_i = 0; c1_i < c1->size; c1_i++)
    {
        for (int c2_y = 0; c2_y < c2->size; c2_y++)
        {
            double distanceOfObjects = obj_distance(&c1->obj[c1_i], &c2->obj[c2_y]);
            if (distanceOfObjects < minDistance)
            {
                minDistance = distanceOfObjects;
                *c1id = c1->obj[c1_i].id;
                *c2id = c2->obj[c2_y].id;
            }
        }
    }
    return minDistance;
}

/*
 Funkce najde dva nejblizsi shluky. V poli shluku 'carr' o velikosti 'narr'
 hleda dva nejblizsi shluky. Nalezene shluky identifikuje jejich indexy v poli
 'carr'. Funkce nalezene shluky (indexy do pole 'carr') uklada do pameti na
 adresu 'c1' resp. 'c2'.
*/
void find_neighbours(struct cluster_t *carr, int narr, int *c1, int *c2)
{
    assert(narr > 0);
    int c1id;
    int c2id;

    *c1 = 0;
    *c2 = 1;

    double minDistance = cluster_distance(&carr[0], &carr[1], &c1id, &c2id);
    for (int i = 0; i < narr; i++)
    {
        for (int y = 0; y < narr; y++)
        {
            if (i != y)
            {
                double distance = cluster_distance(&carr[i], &carr[y], &c1id, &c2id);
                if (minDistance > distance)
                {
                    minDistance = distance;
                    // printf("%f\n", minDistance);
                    *c1 = i;
                    *c2 = y;
                }
            }
        }
    }
}

// pomocna funkce pro razeni shluku
static int obj_sort_compar(const void *a, const void *b)
{
    // TUTO FUNKCI NEMENTE
    const struct obj_t *o1 = (const struct obj_t *)a;
    const struct obj_t *o2 = (const struct obj_t *)b;
    if (o1->id < o2->id)
        return -1;
    if (o1->id > o2->id)
        return 1;
    return 0;
}

/*
 Razeni objektu ve shluku vzestupne podle jejich identifikatoru.
*/
void sort_cluster(struct cluster_t *c)
{
    // TUTO FUNKCI NEMENTE
    qsort(c->obj, c->size, sizeof(struct obj_t), &obj_sort_compar);
}

/*
 Tisk shluku 'c' na stdout.
*/
void print_cluster(struct cluster_t *c)
{
    // TUTO FUNKCI NEMENTE
    for (int i = 0; i < c->size; i++)
    {
        if (i)
            putchar(' ');
        printf("%d[%g,%g]", c->obj[i].id, c->obj[i].x, c->obj[i].y);
    }
    putchar('\n');
}

/*
 Ze souboru 'filename' nacte objekty. Pro kazdy objekt vytvori shluk a ulozi
 jej do pole shluku. Alokuje prostor pro pole vsech shluku a ukazatel na prvni
 polozku pole (ukalazatel na prvni shluk v alokovanem poli) ulozi do pameti,
 kam se odkazuje parametr 'arr'. Funkce vraci pocet nactenych objektu (shluku).
 V pripade nejake chyby uklada do pameti, kam se odkazuje 'arr', hodnotu NULL.
*/
int load_clusters(char *filename, struct cluster_t **arr)
{
    assert(arr != NULL);
    FILE *fp;
    struct obj_t temporaryObj;
    char *line = NULL;
    char *parsed = NULL;
    char *countPointer = NULL;
    int lineCounter = 0;
    size_t len = 0;
    int read;

    fp = fopen(filename, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != EOF)
    {
        int parsedItemCount = 0;

        parsed = strtok(line, " ");

        while (parsed != NULL)
        {
            if (lineCounter > 0)
            {
                switch (parsedItemCount)
                {
                case 0:
                    temporaryObj.id = atoi(parsed);
                    // printf("%d\n", (*arr)[lineCounter - 1].obj[0].id);
                    break;
                case 1:
                    temporaryObj.x = atof(parsed);
                    // printf("%f\n", (*arr)[lineCounter - 1].obj[0].x);
                    break;
                case 2:
                    temporaryObj.y = atof(parsed);
                    init_cluster(&(*arr)[lineCounter - 1], 1);
                    append_cluster(&(*arr)[lineCounter - 1], temporaryObj);
                    break;
                }
            }
            else
            {
                countPointer = strtok(parsed, "=");
                int i = 0;
                while (countPointer != NULL)
                {
                    if (i > 0)
                    {
                        int count = atoi(countPointer);
                        *arr = malloc(count * sizeof(struct cluster_t));
                    }
                    countPointer = strtok(NULL, "=");
                    i++;
                }
            }

            parsed = strtok(NULL, " ");
            parsedItemCount++;
        }
        lineCounter++;
    }

    fclose(fp);
    if (line)
        free(line);

    return --lineCounter;
}

/*
 Tisk pole shluku. Parametr 'carr' je ukazatel na prvni polozku (shluk).
 Tiskne se prvnich 'narr' shluku.
*/
void print_clusters(struct cluster_t *carr, int narr)
{
    printf("Clusters:\n");
    for (int i = 0; i < narr; i++)
    {
        printf("cluster %d: ", i);
        print_cluster(&carr[i]);
    }
}

int main(int argc, char *argv[])
{
    // TODO check arguments
    // TODO check data
    struct cluster_t *clusters;
    char *fileName = argv[1];
    char *numClas = argv[2];
    int numberOfFinallClusters;
    int indexC1, indexC2;
    int numberOfClusters;

    if (!fileName)
    {
        fprintf(stderr, "Please enter filename!");
        exit(EXIT_FAILURE);
    }
    if (argc == 3)
    {
        numberOfFinallClusters = atoi(numClas);
    }
    if (numberOfFinallClusters <= 0)
    {
        fprintf(stderr, "Please enter valide argument!");
        exit(EXIT_FAILURE);
    }
    if (argc == 2)
    {
        numberOfFinallClusters = 1;
    }
    if (argc > 3)
    {
        fprintf(stderr, "Too many arguments!");
        exit(EXIT_FAILURE);
    }

    numberOfClusters = load_clusters(fileName, &clusters);

    while (numberOfClusters > numberOfFinallClusters)
    {

        find_neighbours(clusters, numberOfClusters, &indexC1, &indexC2);
        merge_clusters(&clusters[indexC1], &clusters[indexC2]);
        numberOfClusters = remove_cluster(clusters, numberOfClusters, indexC2);
        // printf("HI%d a %d\n", numberOfFinallClusters, numberOfClusters);
    }

    print_clusters(clusters, numberOfClusters);

    for (int i = 0; i < numberOfClusters; i++)
    {
        clear_cluster(&clusters[i]);
    }
    free(clusters);
    exit(EXIT_SUCCESS);
}
