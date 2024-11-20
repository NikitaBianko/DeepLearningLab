#include "params.h"
#include <algorithm>
#include <random>
#include <fstream>
#include <stdexcept>

namespace params {
    LayerParams::LayerParams(size_t count, bool bias) : Count(count), Bias(bias) {}

    size_t LayerParams::size() {
        return Count + (Bias == true ? 1 : 0);
    }

    Params::Params(std::vector<LayerParams> layers, std::vector<std::vector<std::vector<double>>> weights) 
            : Layers(layers), Weights(weights) { }

    Params::Params(std::vector<LayerParams> layers) : Layers(layers) {
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

    Params::~Params() {}

    void writeLayerParams(std::ofstream& outFile, const LayerParams& layer) {
        outFile.write(reinterpret_cast<const char*>(&layer.Count), sizeof(layer.Count));
        outFile.write(reinterpret_cast<const char*>(&layer.Bias), sizeof(layer.Bias));
    }

    LayerParams readLayerParams(std::ifstream& inFile) {
        size_t count;
        bool bias;
        inFile.read(reinterpret_cast<char*>(&count), sizeof(count));
        inFile.read(reinterpret_cast<char*>(&bias), sizeof(bias));
        return LayerParams(count, bias);
    }

    void writeParamsToBinary(const std::string& filename, const Params& params) {
        std::ofstream outFile(filename, std::ios::binary);
        if (!outFile) {
            throw std::ios_base::failure("Error opening file for writing.");
        }

        size_t layerCount = params.Layers.size();
        outFile.write(reinterpret_cast<const char*>(&layerCount), sizeof(layerCount));

        for (const auto& layer : params.Layers) {
            writeLayerParams(outFile, layer);
        }

        size_t weightsOuterSize = params.Weights.size();
        outFile.write(reinterpret_cast<const char*>(&weightsOuterSize), sizeof(weightsOuterSize));

        for (const auto& matrix : params.Weights) {
            size_t matrixSize = matrix.size();
            outFile.write(reinterpret_cast<const char*>(&matrixSize), sizeof(matrixSize));

            for (const auto& row : matrix) {
                size_t rowSize = row.size();
                outFile.write(reinterpret_cast<const char*>(&rowSize), sizeof(rowSize));
                outFile.write(reinterpret_cast<const char*>(row.data()), rowSize * sizeof(double));
            }
        }
        outFile.close();
    }

    Params readParamsFromBinary(const std::string& filename) {
        std::ifstream inFile(filename, std::ios::binary);
        if (!inFile) {
            throw std::ios_base::failure("Error opening file for reading.");
        }

        size_t layerCount;
        inFile.read(reinterpret_cast<char*>(&layerCount), sizeof(layerCount));

        std::vector<LayerParams> layers;
        for (size_t i = 0; i < layerCount; ++i) {
            layers.push_back(readLayerParams(inFile));
        }

        size_t weightsOuterSize;
        inFile.read(reinterpret_cast<char*>(&weightsOuterSize), sizeof(weightsOuterSize));

        std::vector<std::vector<std::vector<double>>> weights;
        for (size_t i = 0; i < weightsOuterSize; ++i) {
            size_t matrixSize;
            inFile.read(reinterpret_cast<char*>(&matrixSize), sizeof(matrixSize));

            std::vector<std::vector<double>> matrix(matrixSize);
            for (size_t j = 0; j < matrixSize; ++j) {
                size_t rowSize;
                inFile.read(reinterpret_cast<char*>(&rowSize), sizeof(rowSize));

                std::vector<double> row(rowSize);
                inFile.read(reinterpret_cast<char*>(row.data()), rowSize * sizeof(double));
                matrix[j] = std::move(row);
            }
            weights.push_back(std::move(matrix));
        }

        inFile.close();
        return Params(std::move(layers), std::move(weights));
    }
}