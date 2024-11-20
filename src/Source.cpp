#include "params.h"
#include <stdio.h>

using namespace params;

int main() {
    std::vector<LayerParams> layers = {LayerParams(4, true), LayerParams(1, false)};

    Params params(layers);

    const std::string filename = "params/params.bin";

    writeParamsToBinary(filename, params);

    Params loadedParams = readParamsFromBinary(filename);
    
    printf("Layers:\n");
    for (const auto& layer : loadedParams.Layers) {
        printf("Count: %zu, Bias: %s\n", layer.Count, layer.Bias ? "true" : "false");
    }

    printf("\nWeights:\n");
    for (const auto& matrix : loadedParams.Weights) {
        for (const auto& row : matrix) {
            for (double value : row) {
                printf("%f ", value);
            }
            printf("\n");
        }
        printf("\n");
    }

    return 0;
}