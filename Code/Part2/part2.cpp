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
#define MSJ_ACCEPT_LOT "Aceptar lote"
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

int compare(const void * a, const void * b);
void processA(string path);
void processB(string path);
int majorityElement();
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
    size_t quantityElementsSameVolume = 0;

    for(size_t i = 0; i < quantityPiecesLot; i++){
        for(size_t j = i + 1; j < quantityPiecesLot; j++) {
            if(values.vector[i] == values.vector[j])
                quantityElementsSameVolume++;
        }
        if(quantityElementsSameVolume >= (int) quantityPiecesLot/2) {
            cout << MSJ_ACCEPT_LOT << endl;
            return;
        }
        else quantityElementsSameVolume = 0;
    }

    cout << MSJ_REJECT_LOT << endl;
}

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

void processB(string path) {
    qsort(values.vector, values.size, sizeof(int), compare);

    size_t mayoritaryCount = 0;
    size_t i = (int)values.size/2;
    while(values.vector[i] == values.vector[(int)values.size/2]){
        mayoritaryCount++;
        i++;
    }
    i = (int)values.size/2;
    while(values.vector[i] == values.vector[(int)values.size/2 - 1]){
        mayoritaryCount++;
        i--;
    }
    
    if(mayoritaryCount > (int) values.size/2)
        cout << MSJ_ACCEPT_LOT << endl;
    else
        cout << MSJ_REJECT_LOT << endl;
}

int majorityElement()
{
	size_t majority, majorityOcurrences = 0;
	
	for (size_t j = 0; j < values.size; j++)
	{
		if (majorityOcurrences == 0)
			majority = values.vector[j], majorityOcurrences = 1;
			
		else (majority == values.vector[j]) ? majorityOcurrences++ : majorityOcurrences--;
	}

	return majority;
}

void processC(string path) {
    int max = majorityElement();

    size_t quantityMax = 0;

    for(size_t i = 0; i < values.size; i++){
        if(values.vector[i] == max)
            quantityMax++;
    }

    if(quantityMax > (int) values.size/2)
        cout << MSJ_ACCEPT_LOT << endl;
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