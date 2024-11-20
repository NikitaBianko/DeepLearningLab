#include "neuralNetwork.h"

namespace neuralNetwork {
    Network::Network(params::Params& params) : _params(params) {
        _layers.reserve(params.Layers.size());
        for (size_t i = 0; i < params.Layers.size(); ++i) {
            _layers.push_back(std::vector<double>(params.Layers[i].size(), 0));

            if (params.Layers[i].Bias == true) {
                _layers[i][params.Layers[i].Count] = 1;
            }
        }
    }

    Network::~Network() {}

    void Network::feedforward(double (*activate)(double)) {

    }

    void Network::setInput(std::vector<double>& input) {

    }

    std::vector<double> Network::getOutput() {
        return *(_layers.end() - 1);
    }

    std::vector<std::vector<double>> Network::getAllLayers() {
        return _layers;
    }

    params::Params Network::getParams() {
        return _params;
    }
}