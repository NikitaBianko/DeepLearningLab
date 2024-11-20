#include "params.h"
#include <algorithm>
#include <random>

namespace params {
    LayerParams::LayerParams(size_t count, bool bias) : Count(count), Bias(bias) {}

    size_t LayerParams::size() {
        return Count + (Bias == true ? 1 : 0);
    }

    Params::Params(std::vector<LayerParams> layers, std::vector<std::vector<std::vector<double>>> weights) 
            : Layers(layers), Weights(weights) { }

    Params::Params(std::vector<LayerParams> layers) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dist(-1, 1);

        Weights.resize(layers.size() - 1);
        for (size_t i = 0; i < layers.size() - 1; ++i) {
            Weights[i].resize(layers[i].size());
            for (size_t j = 0; j < layers[i].size(); ++j) {
                Weights[i][j].resize(layers[i + 1].Count);
                
                std::generate(Weights[i][j].begin(), Weights[i][j].end(), [&]() {
                    return dist(gen);
                });
            }
        }
    }
}