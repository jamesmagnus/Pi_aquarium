#ifndef TEMP_H_INCLUDED
#define TEMP_H_INCLUDED

typedef struct sCSV {
    unsigned int nbChamps, nbEntrees;
    int err;
    int **data;
} CSV;

#endif // TEMP_H_INCLUDED
