#include <benchmark/benchmark.h>
#include <vector> 
using namespace std;

void mult_A_column_B_column(benchmark::State& state) { // the tested function always has this prototype
    // do all initialization here:
    size_t size = state.range(0); 
    vector<vector<double>> matrix_A(size, vector<double>(size, 1.));
    vector<vector<double>> matrix_B(size, vector<double>(size, 1.));
    vector<vector<double>> matrix_C(size, vector<double>(size, 0));

    // Put the measured code inside this loop:
    for (auto _: state) {
        for (int x = 0; x < size; x++) {
            for (int y = 0; y < size; y++) { 
                for (int k = 0; k < size; k++) {
                    matrix_C[y][x] += matrix_A[k][y] * matrix_B[x][k];
                 }
            }
        }
    }
}

void mult_A_row_B_column(benchmark::State& state) { // the tested function always has this prototype
    // do all initialization here:
    size_t size = state.range(0); 
    vector<vector<double>> matrix_A(size, vector<double>(size, 1.));
    vector<vector<double>> matrix_B(size, vector<double>(size, 1.));
    vector<vector<double>> matrix_C(size, vector<double>(size, 0.));
    double res;

    // Put the measured code inside this loop:
    for (auto _: state) {
        for (int x = 0; x < size; x++) {
            for (int y = 0; y < size; y++) { 
                for (int k = 0; k < size; k++) {
                    res += matrix_A[y][k] * matrix_B[x][k];
                }
            }
        }
    }
}

void mult_A_column_B_row(benchmark::State& state) { // the tested function always has this prototype
    // do all initialization here:
    size_t size = state.range(0); 
    vector<vector<double>> matrix_A(size, vector<double>(size, 1.));
    vector<vector<double>> matrix_B(size, vector<double>(size, 1.));
    vector<vector<double>> matrix_C(size, vector<double>(size, 0.));

    // Put the measured code inside this loop:
    for (auto _: state) {
        for (int x = 0; x < size; x++) {
            for (int y = 0; y < size; y++) { 
                for (int k = 0; k < size; k++) {
                    matrix_C[y][x] += matrix_A[k][y] * matrix_B[k][x];
                }
            }
        }
    }
}

void mult_A_row_B_row(benchmark::State& state) { // the tested function always has this prototype
    // do all initialization here:
    size_t size = state.range(0); 
    vector<vector<double>> matrix_A(size, vector<double>(size, 1.));
    vector<vector<double>> matrix_B(size, vector<double>(size, 1.));
    vector<vector<double>> matrix_C(size, vector<double>(size, 0.));

    // Put the measured code inside this loop:
    for (auto _: state) {
        for (int x = 0; x < size; x++) {
            for (int y = 0; y < size; y++) { 
                for (int k = 0; k < size; k++) {
                    matrix_C[y][x] += matrix_A[y][k] * matrix_B[k][x];
                }
            }
        }
    }
}

struct Func {
    const char * name;
    void (*ptr)(benchmark::State&) ;
};


int main() {
    //pass the test name and the tested function in "RegisterBenchmark",
    //pass arguments in "Args":
    const Func func_array[] {
        // {"mult_A_row_B_row", &mult_A_row_B_row},
        // {"mult_A_column_B_column", &mult_A_column_B_column},
        // {"mult_A_column_B_row", &mult_A_column_B_row},
        {"mult_A_row_B_column", &mult_A_row_B_column}
    };
    
    for (auto func: func_array) {
        benchmark::RegisterBenchmark(func.name, func.ptr)->Arg(1024);//DenseRange(2, 1024, 73);
    }
    
    benchmark::RunSpecifiedBenchmarks();
}

