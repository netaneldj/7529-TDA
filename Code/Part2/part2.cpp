#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <unordered_map>

using namespace std;

#define QUANT_ARGS 3
#define MSJ_BAD_ARGS "Ha ingresado argumentos invalidos"
#define MSJ_BAD_ARCHIVE "El archivo contiene información no válida"
#define MSJ_ACCEPT_LOT "Aceptar lote."
#define MSJ_LOT_VOLUME " El volumen del lote es: "
#define MSJ_REJECT_LOT "Rechazar lote"
#define INDEX_TYPE_PROCESS 1
#define INDEX_LOT_PATH 2
#define CASE_PROCESS_A 'A' 
#define CASE_PROCESS_B 'B'
#define CASE_PROCESS_C 'C'
#define MAX_CANT 100

typedef struct vector {
    int vector[MAX_CANT];
    size_t size = 0;
    size_t maxSize = MAX_CANT;
} vector_t;

typedef struct pair {
    int first;
    int second;
} pair_t;

int compare(const void * a, const void * b);
void processA(string path);
void processB(string path);
int majorityElement(vector_t &vector, int &tiebrakerVote);
void processC(string path);
void readLotFile(char* path, bool &success);



vector_t values;

//Pre: -Se ingresa una direccion de lot válida
int main(int argc, char *argv[]) {
    if(argc != QUANT_ARGS) {
        cout << MSJ_BAD_ARGS << endl;
        return EXIT_FAILURE;
    }

    char caseIdentifier = argv[INDEX_TYPE_PROCESS][0];
    char *lotPath = argv[INDEX_LOT_PATH];
    bool successRead = false;
    vector_t lots;

    readLotFile(lotPath, successRead);

    if(!successRead) {
        cout << MSJ_BAD_ARCHIVE << endl;
        return EXIT_FAILURE;
    }

    switch(caseIdentifier) {
        case CASE_PROCESS_A:
            processA(argv[INDEX_LOT_PATH]);
            break;

        case CASE_PROCESS_B:
            processB(argv[INDEX_LOT_PATH]);
            break;

        case CASE_PROCESS_C:
            processC(argv[INDEX_LOT_PATH]);
            break;

        default:
            cout << MSJ_BAD_ARGS << endl;
            return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

void processA(string path) {
    size_t quantityPiecesLot = values.size;
    size_t counterElementsSameVolume = 1;

    for(size_t i = 0; i < quantityPiecesLot; i++){
        for(size_t j = i + 1; j < quantityPiecesLot; j++) {
            if(values.vector[i] == values.vector[j])
                counterElementsSameVolume++;
        }
        if(counterElementsSameVolume > (int) quantityPiecesLot/2) {
            cout << MSJ_ACCEPT_LOT << MSJ_LOT_VOLUME << values.vector[i] << endl;
            return;
        }
        else counterElementsSameVolume = 1;
    }

    cout << MSJ_REJECT_LOT << endl;
}

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

void processB(string path) {
    qsort(values.vector, values.size, sizeof(int), compare); //Ordena elementos

    size_t mayoritaryCount = 0;
    size_t i = (int) values.size/2;
    while(values.vector[i] == values.vector[(int) values.size/2]){
        mayoritaryCount++;
        i++;
    }
    i = (int) values.size / 2;
    while(values.vector[i] == values.vector[(int) values.size/2 - 1]){
        mayoritaryCount++;
        i--;
    }
    
    if(mayoritaryCount > (int) values.size / 2)
        cout << MSJ_ACCEPT_LOT << MSJ_LOT_VOLUME << values.vector[(int) values.size / 2]  << endl;
    else
        cout << MSJ_REJECT_LOT << endl;
}

int majorityElement(vector_t &vector, int &tiebrakerVote)
{
    if(vector.size == 0)
        return tiebrakerVote;
    
    if(vector.size % 2 != 0)
        tiebrakerVote = vector.vector[vector.size - 1];

    size_t j = 0;
	for (size_t i = 0; i < vector.size; i += 2) {
        if(vector.vector[i] == vector.vector[i + 1])
            vector.vector[j++] = vector.vector[i];
	}
    vector.size = j;

	return majorityElement(vector, tiebrakerVote);
}

void processC(string path) {
    vector_t list = values;
    int tiebrakerVote;
    int max = majorityElement(list, tiebrakerVote);

    size_t counterMax = 0;

    for(size_t i = 0; i < values.size; i++){
        if(values.vector[i] == max)
            counterMax++;
    }

    if(counterMax > (int) values.size/2) {
        cout << MSJ_ACCEPT_LOT << MSJ_LOT_VOLUME << max << endl;
    }
    else
        cout << MSJ_REJECT_LOT << endl;
}

//Pre: Archivo contiene 1 valor numérico por línea
void readLotFile(char* path, bool &success) {
    string auxPath(path);
    ifstream infile(auxPath);

    if(infile.good()) {
        string line;
        size_t i = 0;
        while (getline(infile, line)){
             values.vector[i++] = stoi(line);
        }
        values.vector[i] = -1;
        values.size = i;
        infile.close();
        success = true;
    } else 
        success = false;
        return;
}