#ifndef PARAMS_H
#define PARAMS_H

#include <vector>

namespace params {
    struct LayerParams {
        const size_t Count;
        const bool Bias;

        LayerParams(size_t count, bool bias);

        size_t size();
    };
    
    struct Params {
        std::vector<LayerParams> Layers;
        std::vector<std::vector<std::vector<double>>> Weights;

        Params(std::vector<LayerParams> layers, std::vector<std::vector<std::vector<double>>> weights);

        Params(std::vector<LayerParams> layers);

        ~Params();
    };

    void writeParamsToBinary(const std::string& filename, const Params& params);
    
    Params readParamsFromBinary(const std::string& filename);
}

#endif