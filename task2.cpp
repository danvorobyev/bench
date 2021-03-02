#include <benchmark/benchmark.h>
#include <vector> 
#include <utility>
#include <iostream>
using namespace std;

#define max_size 1024


void block_mult(benchmark::State& state) {
    size_t block_size = state.range(0);
    vector<vector<double>> matrix_A(max_size, vector<double>(max_size, 1));
    vector<vector<double>> matrix_B(max_size, vector<double>(max_size, 2));
    vector<vector<double>> matrix_C(max_size, vector<double>(max_size, 0));
    double sum;

    for (auto _: state) {
        for (int xx = 0; xx < max_size; xx += block_size) {
            for (int yy = 0; yy < max_size; yy += block_size) {
                for (int kk = 0; kk < max_size; kk += block_size) {
                    for (int x = xx; x < xx + block_size; x++) {
                        for (int y = yy; y < yy + block_size; y++) {
                            sum = 0.0;
                            for (int k = kk; k < kk + block_size; k++) {
                                sum += matrix_A[y][k] * matrix_B[x][k];
                            }
                            matrix_C[y][x] += sum;
                        }
                    }
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

    benchmark::RegisterBenchmark("block_mult", block_mult)->RangeMultiplier(2)->Range(2, 1024);

    benchmark::RunSpecifiedBenchmarks();
}