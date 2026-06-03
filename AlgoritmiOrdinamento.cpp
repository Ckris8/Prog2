#include <iostream>

using namespace std;

// ==========================================
// FUNZIONI DI SUPPORTO
// ==========================================

// Funzione per scambiare fisicamente due elementi
void swapElements(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Funzione di utilità per stampare l'array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

// Funzione per copiare un array (serve a non modificare l'originale)
void copyArray(const int source[], int dest[], int size) {
    for(int i = 0; i < size; i++) {
        dest[i] = source[i];
    }
}

// ==========================================
// ALGORITMI DI ORDINAMENTO (O(N^2))
// ==========================================

void bubbleSort(int A[], int size) {
    for(int i = 0; i < size - 1; i++) {
        // Il limite corretto è size - i - 1 per evitare di uscire dall'array
        for (int j = 0; j < size - i - 1; j++) {
            if(A[j] > A[j+1]) {
                swapElements(A[j], A[j+1]);
            }
        }
    }
}

void insertSort(int A[], int size) {
    int appoggio;
    for(int i = 1; i < size; i++) {
        appoggio = A[i];
        int j = i - 1;
        while((j >= 0) && (A[j] > appoggio)) {
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = appoggio;
    }
}

void selectionSort(int A[], int size) {
    int posMin;
    for(int i = 0; i < size - 1; i++) {
        posMin = i;
        int j = i + 1;
        while(j < size) {
            if(A[j] < A[posMin]) {
                posMin = j;
            }
            j++;
        }
        // MANCAVA QUESTO: Se abbiamo trovato un minimo diverso, lo scambiamo
        if (posMin != i) {
            swapElements(A[i], A[posMin]);
        }
    }
}

// ==========================================
// ALGORITMI DI ORDINAMENTO (O(N log N))
// ==========================================

// --- MERGE SORT ---
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0; 
    int j = 0; 
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Aggiunti i delete per prevenire memory leak
    delete[] L;
    delete[] R;
}

void mergeSort(int A[], int left, int right) {
    if (left >= right) {
        return; 
    }
    int mid = left + (right - left) / 2;
    mergeSort(A, left, mid);
    mergeSort(A, mid + 1, right);
    merge(A, left, mid, right);
}

// --- QUICK SORT ---
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; 
    int i = (low - 1);     

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++; 
            swapElements(arr[i], arr[j]);
        }
    }
    swapElements(arr[i + 1], arr[high]);
    return (i + 1);
}

// Corretta la firma: servono low e high per la ricorsione
void quickSort(int A[], int low, int high) {
    if (low < high) {
        int pi = partition(A, low, high);
        quickSort(A, low, pi - 1);
        quickSort(A, pi + 1, high);
    }
}


// ==========================================
// MAIN
// ==========================================

int main() {
    // Array originale che non verrà mai alterato
    int arrayOriginale[] = {64, 34, 25, 12, 22, 11, 90, 45, 3};
    int size = sizeof(arrayOriginale) / sizeof(arrayOriginale[0]);
    
    // Array temporaneo da usare per gli ordinamenti
    int tempArr[size];

    cout << "========================================\n";
    cout << "ARRAY ORIGINALE: \n";
    printArray(arrayOriginale, size);
    cout << "========================================\n\n";

    // --- Test Bubble Sort ---
    copyArray(arrayOriginale, tempArr, size);
    bubbleSort(tempArr, size);
    cout << "Risultato Bubble Sort: \n";
    printArray(tempArr, size);
    cout << "\n";

    // --- Test Insertion Sort ---
    copyArray(arrayOriginale, tempArr, size);
    insertSort(tempArr, size);
    cout << "Risultato Insertion Sort: \n";
    printArray(tempArr, size);
    cout << "\n";

    // --- Test Selection Sort ---
    copyArray(arrayOriginale, tempArr, size);
    selectionSort(tempArr, size);
    cout << "Risultato Selection Sort: \n";
    printArray(tempArr, size);
    cout << "\n";

    // --- Test Merge Sort ---
    copyArray(arrayOriginale, tempArr, size);
    mergeSort(tempArr, 0, size - 1);
    cout << "Risultato Merge Sort: \n";
    printArray(tempArr, size);
    cout << "\n";

    // --- Test Quick Sort ---
    copyArray(arrayOriginale, tempArr, size);
    quickSort(tempArr, 0, size - 1);
    cout << "Risultato Quick Sort: \n";
    printArray(tempArr, size);
    cout << "\n";
    
    return 0;
}