#include "WNeuralLayer.h"

WNeuralLayer::WNeuralLayer(int nbNeurons, double bias) {
	this->bias = bias;

	for(int i = 0; i < nbNeurons; i++)
		neurons.append(new WNeuron(bias));
}

WNeuralLayer::~WNeuralLayer() {

}

void WNeuralLayer::initSynapses(int nbPrevNeurons) {
	foreach(WNeuron *neuron, neurons)
		neuron->initSynapses(nbPrevNeurons);
}

QList<double> WNeuralLayer::activate(QList<double> inputs) {
	QList<double> outputs;
	foreach(WNeuron *neuron, neurons)
		outputs.append(neuron->activate(inputs));
	return outputs;
}

QList<double> WNeuralLayer::getOutputDeltas(QList<double> trainOutputs) {
	QList<double> deltas;
	for(int i = 0; i < neurons.size(); i++)
		deltas.append(neurons.at(i)->getError(trainOutputs.at(i)));
	return deltas;
}

QList<double> WNeuralLayer::getHiddenDeltas(WNeuralLayer *nextLayer, QList<double> nextLayerDeltas) {
	QList<double> deltas;
	for(int i = 0; i < neurons.size(); i++)
		deltas.append(nextLayer->getError(nextLayerDeltas, i) * neurons.at(i)->getDeriv());
	return deltas;
}

double WNeuralLayer::getError(QList<double> deltas, int neuronId) {
	double error = 0;
	for(int i = 0; i < neurons.size(); i++)
		error += deltas.at(i) * neurons.at(i)->getSynapse(neuronId);
	return error;
}

void WNeuralLayer::updateSynapses(QList<double> deltas) {
	for(int i = 0; i < neurons.size(); i++)
		neurons.at(i)->updateSynapses(deltas.at(i));
}
