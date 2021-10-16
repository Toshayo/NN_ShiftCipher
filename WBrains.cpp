#include "WBrains.h"
#include <QRandomGenerator>


WBrains::WBrains(int nbInputs, int nbHidden, int nbOutputs) {
	this->inputNeurons = nbInputs;

	QRandomGenerator rnd;

	hiddenLayers.append(new WNeuralLayer(nbHidden, rnd.generateDouble()));
	outputLayer = new WNeuralLayer(nbOutputs, rnd.generateDouble());

	hiddenLayers.at(0)->initSynapses(nbInputs);
	outputLayer->initSynapses(nbHidden);
}

WBrains::WBrains(int nbInputs, QList<int> nbHiddens, int nbOutputs) {
	this->inputNeurons = nbInputs;

	QRandomGenerator rnd;

	foreach(int nbHidden, nbHiddens)
		hiddenLayers.append(new WNeuralLayer(nbHidden, rnd.generateDouble()));

	outputLayer = new WNeuralLayer(nbOutputs, rnd.generateDouble());

	int nbPrevNeurons = nbInputs;

	for(int i = 0; i < hiddenLayers.size(); i++) {
		hiddenLayers.at(i)->initSynapses(nbPrevNeurons);
		nbPrevNeurons = nbHiddens.at(i);
	}
	outputLayer->initSynapses(nbHiddens.last());
}

WBrains::~WBrains() {
	outputLayer->~WNeuralLayer();
	foreach(WNeuralLayer *neuralLayer, hiddenLayers)
		neuralLayer->~WNeuralLayer();
	delete outputLayer;
}

QList<double> WBrains::activate(QList<double> inputs) {
	QList<double> layerOut = inputs;
	foreach(WNeuralLayer *layer, hiddenLayers)
		layerOut = layer->activate(layerOut);
	return outputLayer->activate(layerOut);
}

void WBrains::train(QList<double> trainInputs, QList<double> trainOutputs) {
	activate(trainInputs);

	QList<double> outputDeltas = outputLayer->getOutputDeltas(trainOutputs);
	QList<QList<double>> hiddensDeltas;
	for(int i = 0; i < hiddenLayers.size(); i++)
		hiddensDeltas.append(hiddenLayers.at(i)->getHiddenDeltas(outputLayer, outputDeltas));

	outputLayer->updateSynapses(outputDeltas);
	for(int i = 0; i < hiddenLayers.size(); i++)
		hiddenLayers.at(i)->updateSynapses(hiddensDeltas.at(i));
}
