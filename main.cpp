//#pragma GCC optimize("", off)

#include <iostream>
#include <chrono>
#include <random>
#include <utility>

using namespace std;

const long long MAX_NUMBER_OF_ITERATIONS = 100'000'000;
const long long NUMBER_OF_ITERATIONS_ADD = 100'000'000;
const long long NUMBER_OF_ITERATIONS_SUB = 100'000'000;
const long long NUMBER_OF_ITERATIONS_MUL = 10'000'000;
const long long NUMBER_OF_ITERATIONS_DIV = 10'000'000;

namespace RNG {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    mt19937_64 rng_64(chrono::steady_clock::now().time_since_epoch().count());
}


namespace Bench {
    struct BenchResult {
        long long duration;
        double interations_per_second;

        string operation;
        string type;
    };

    template <typename F>
    BenchResult bench(const string& operation, const string& type, F func, int count_of_iterations = 1) {
        auto start = chrono::high_resolution_clock::now();

        for (int i = 0; i < count_of_iterations; i++) {
            func(i);
        }

        auto end = chrono::high_resolution_clock::now();

        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        auto interations_per_second
            = 1e9 * (count_of_iterations * 1.0) / (duration * 1.0);

        return {
            duration,
            interations_per_second,
            operation,
            type
        };
    }

    string gen_diagram(int percent) {
        percent /= 2;

        string result = "";
        for (int i = 0; i < percent; i++) {
            result += "X";
        }
        return result;
    }

}

int main() {
    vector <int> v(MAX_NUMBER_OF_ITERATIONS + 1, 0);

    vector <Bench::BenchResult> results;

    auto fillVector = [&v]() {
        for (int i = 0; i < MAX_NUMBER_OF_ITERATIONS; i++) {
            v[i] = RNG::rng() + 1;
        }
    };

    fillVector();

    results.emplace_back(Bench::bench("+", "int", [&](int i) {
        v[i + 1] = v[i] + v[i + 1];
    }, NUMBER_OF_ITERATIONS_ADD));

    fillVector();

    results.emplace_back(Bench::bench("-", "int", [&](int i) {
        v[i + 1] = v[i] - v[i + 1];
    }, NUMBER_OF_ITERATIONS_SUB));

    fillVector();

    results.emplace_back(Bench::bench("*", "int", [&](int i) {
        v[i + 1] = v[i] * v[i + 1];
    }, NUMBER_OF_ITERATIONS_MUL));

    fillVector();

    results.emplace_back(Bench::bench("/", "int", [&](int i) {
        v[i + 1] = v[i] / v[i + 1];
    }, NUMBER_OF_ITERATIONS_DIV));

    fillVector();

    vector <long long> v2(MAX_NUMBER_OF_ITERATIONS + 1, 0);

    auto fillVector2 = [&v2]() {
        for (int i = 0; i < MAX_NUMBER_OF_ITERATIONS; i++) {
            v2[i] = RNG::rng_64() + 1;
        }
    };

    fillVector2();

    results.emplace_back(Bench::bench("+", "long", [&](int i) {
        v2[i + 1] = v2[i] + v2[i + 1];
    }, NUMBER_OF_ITERATIONS_ADD));

    fillVector2();

    results.emplace_back(Bench::bench("-", "long", [&](int i) {
        v2[i + 1] = v2[i] - v2[i + 1];
    }, NUMBER_OF_ITERATIONS_SUB));

    fillVector2();

    results.emplace_back(Bench::bench("*", "long", [&](int i) {
        v2[i + 1] = v2[i] * v2[i + 1];
    }, NUMBER_OF_ITERATIONS_MUL));

    fillVector2();

    results.emplace_back(Bench::bench("/", "long", [&](int i) {
        v2[i + 1] = v2[i] / v2[i + 1];
    }, NUMBER_OF_ITERATIONS_DIV));

    fillVector2();

    vector <double> v3(MAX_NUMBER_OF_ITERATIONS + 1, 0);

    auto fillVector3 = [&v3]() {
        for (int i = 0; i < MAX_NUMBER_OF_ITERATIONS; i++) {
            v3[i] = RNG::rng_64() + 1;
        }
    };

    fillVector3();

    results.emplace_back(Bench::bench("+", "double", [&](int i) {
        v3[i + 1] = v3[i] + v3[i + 1];
    }, NUMBER_OF_ITERATIONS_ADD));

    fillVector3();

    results.emplace_back(Bench::bench("-", "double", [&](int i) {
        v3[i + 1] = v3[i] - v3[i + 1];
    }, NUMBER_OF_ITERATIONS_SUB));

    fillVector3();

    results.emplace_back(Bench::bench("*", "double", [&](int i) {
        v3[i + 1] = v3[i] * v3[i + 1];
    }, NUMBER_OF_ITERATIONS_MUL));

    fillVector3();

    results.emplace_back(Bench::bench("/", "double", [&](int i) {
        v3[i + 1] = v3[i] / v3[i + 1];
    }, NUMBER_OF_ITERATIONS_DIV));

    fillVector3();

    vector <char> v4(MAX_NUMBER_OF_ITERATIONS + 1, 0);

    auto fillVector4 = [&v4]() {
        for (int i = 0; i < MAX_NUMBER_OF_ITERATIONS; i++) {
            v4[i] = RNG::rng() % CHAR_MAX + 1;
        }
    };

    fillVector4();

    results.emplace_back(Bench::bench("+", "char", [&](int i) {
        v4[i + 1] = v4[i] + v4[i + 1];
    }, NUMBER_OF_ITERATIONS_ADD));

    fillVector4();

    results.emplace_back(Bench::bench("-", "char", [&](int i) {
        v4[i + 1] = v4[i] - v4[i + 1];
    }, NUMBER_OF_ITERATIONS_SUB));

    fillVector4();

    results.emplace_back(Bench::bench("*", "char", [&](int i) {
        v4[i + 1] = v4[i] * v4[i + 1];
    }, NUMBER_OF_ITERATIONS_MUL));

    fillVector4();

    results.emplace_back(Bench::bench("/", "char", [&](int i) {
        v4[i + 1] = v4[i] / v4[i + 1];
    }, NUMBER_OF_ITERATIONS_DIV));

    double best_speed = 0;

    for (auto &result : results) {
        best_speed = max(best_speed, result.interations_per_second);
    }

    for (auto &result : results) {
        int percentage = (int)round(result.interations_per_second / best_speed * 100);

        printf(
            "| %-3s| %-10s| %-15E| %-51s| %-10.2d\%|\n",
            result.operation.c_str(),
            result.type.c_str(),
            result.interations_per_second,
            Bench::gen_diagram(percentage).c_str(),
            percentage
        );
    }

    printf("System info: %s", __VERSION__);


    return 0;
}
