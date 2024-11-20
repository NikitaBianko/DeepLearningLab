#include "params.h"
#include "neuralNetwork.h"
#include <stdio.h>

using namespace params;
using namespace std;

int main() {
    vector<LayerParams> layers = {LayerParams(4, true), LayerParams(1, false)};
    vector<vector<vector<double>>> weights = {{{5, -5, -5, -5}}};

    Params params(layers);

    return 0;
}