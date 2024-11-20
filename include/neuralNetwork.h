#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "params.h"
#include <vector>

namespace neuralNetwork {
    class Network {
    private: 
        params::Params _params;
        std::vector<std::vector<double>> _layers;
    public:
        Network(params::Params& params);

        ~Network();

        void feedforward(double (*activate)(double));

        void setInput(std::vector<double>& input);

        std::vector<double> getOutput();

        std::vector<std::vector<double>> getAllLayers();

        params::Params getParams();
    };
    
}

#endif