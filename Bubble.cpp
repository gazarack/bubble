#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
using namespace std;

// Sort function typedef
typedef void (*SortFunction)(int*, int);

void SingleTest(SortFunction, int, int);
void RunTestSuite();
void PrintArray(int*, int);
int *RandomArray(int, int);
int *CopyArray(int*, int);
void PrintTimeDiff(timeval, timeval);
void BubbleSort(int*, int);
void BiBubbleSort(int*, int);
void BitonicSort(int*, int);
void SortUp(int*, int, int);
void SortDown(int*, int, int);
void MergeUp(int*, int, int);
void MergeDown(int*, int, int);

int main() {
    //SingleTest(BiBubbleSort, 30, 99);

    RunTestSuite();

    return 0;
}

void RunTestSuite() {
    const int NUM_SORT_FUNCS = 2;
    const int MAX_KEY_VALUE = 500;
    const int NUM_TESTS = 6;
    const int NUM_SAMPLES = 10;
    const int TEST_SIZES[] = {10, 50, 100, 500, 1000, 5000,
                              10000, 50000, 100000, 500000, 1000000};

    const int BIT_TEST_SIZES[] = {16, 32, 64, 128, 256, 512, 1024, 2048, 4096,
                                  8192, 16384, 32768, 65536, 131072};

    const string sortFuncNames[] = {"Bubble Sort", "Bi-Bubble Sort"};
    const SortFunction sortFuncs[] = {BubbleSort, BiBubbleSort};

    timeval start, end;
    int *tmpArray;

    for (int i = 0; i < NUM_TESTS; i++) {
        int N = TEST_SIZES[i];
        cout << "Sorting with N=" << N << endl;

        // Generate random samples
        int **randArrays = new int*[NUM_SAMPLES];
        for (int i = 0; i < NUM_SAMPLES; i++)
            randArrays[i] = RandomArray(N, MAX_KEY_VALUE);

        for (int j = 0; j < NUM_SORT_FUNCS; j++) {
            cout << sortFuncNames[j] << '\t';
            for (int k = 0; k < NUM_SAMPLES; k++) {
                tmpArray = CopyArray(randArrays[k], N);
                gettimeofday(&start, NULL);
                (*sortFuncs[j])(tmpArray, N);
                gettimeofday(&end, NULL);
                PrintTimeDiff(start, end);
                delete[] tmpArray;
            }
            cout << endl;
        }

        cout << endl;

        for (int j = 0; j < NUM_SAMPLES; j++)
            delete[] randArrays[j];
        delete[] randArrays;
    }
}

void SingleTest(SortFunction func, int size, int maxKey) {
    int *test = RandomArray(size, maxKey);

    PrintArray(test, size);
    (*func)(test, size);
    PrintArray(test, size);

    delete[] test;
}

void PrintArray(int *ary, int size) {
    for (int i = 0; i < size; i++) {
        cout << ary[i] << " ";
    }
    cout << endl;
}

int *RandomArray(int size, int maxRandNum) {
    int *randArray = new int[size];
    timeval timeseed;
    gettimeofday(&timeseed, NULL);

    srand(timeseed.tv_usec);
    for (int i = 0; i < size; i++) {
        randArray[i] = (rand() % maxRandNum) + 1;
    }

    return randArray;
}

int *CopyArray(int *ary, int size) {
    int *tmp = new int[size];

    for (int i = 0; i < size; i++)
        tmp[i] = ary[i];

    return tmp;
}

void PrintTimeDiff(timeval start, timeval end) {
    long seconds = end.tv_sec - start.tv_sec;
    long useconds = end.tv_usec - start.tv_usec;

    //double mtime = ((seconds) + useconds/1000000.0);
    long mtime = ((seconds * 1000000) + useconds);

    cout << "\t" << mtime;
}

void BubbleSort(int *ary, int size) {
    bool swapped = true;
    int tmp;

    while (swapped == true) {
        swapped = false;

        for (int i = 0; i < size - 1; i++)
            if (ary[i] > ary[i + 1]) {
                tmp = ary[i];
                ary[i] = ary[i + 1];
                ary[i + 1] = tmp;
                swapped = true;
            }
    }
}

void BiBubbleSort(int *ary, int size) {
    bool swapped = true;
    int tmp;

    while (swapped == true) {
        swapped = false;

        for (int i = 0; i < size - 1; ++i)
            if (ary[i] > ary[i + 1]) {
                tmp = ary[i];
                ary[i] = ary[i + 1];
                ary[i + 1] = tmp;
                swapped = true;
            }

        for (int i = size - 1; i > 0; --i) {
            if (ary[i] < ary[i - 1]) {
                tmp = ary[i];
                ary[i] = ary[i - 1];
                ary[i - 1] = tmp;
                swapped = true;
            }
        }
    }
}

void BitonicSort(int* ary, int size) {

}

void SortUp(int* art, int start, int end) {

}

void SortDown(int* art, int start, int end) {

}

void MergeUp(int* art, int start, int end) {

}

void MergeDown(int* art, int start, int end) {

}