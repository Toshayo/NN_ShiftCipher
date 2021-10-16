#include "WNeuron.h"
#include <QtMath>
#include <QRandomGenerator>


WNeuron::WNeuron(double bias) {
	this->bias = bias;
}

void WNeuron::initSynapses(int nbPrevNeurons) {
	QRandomGenerator rnd;
	for(int i = 0; i < nbPrevNeurons; i++)
		synapses.append(rnd.generateDouble());
}

double WNeuron::activate(QList<double> inputs) {
	this->inputs = inputs;
	double sum = 0;
	for(int i = 0; i < inputs.size(); i++)
		sum += inputs.at(i) * synapses.at(i);
	output = sigmoid(sum + bias);
	return output;
}

double WNeuron::sigmoid(double input) {
	return 1 / (1 + qExp(-input));
}

double WNeuron::getError(double trainOutput) {
	return getDeriv() * getPartDeriv(trainOutput);
}

double WNeuron::getDeriv() {
	return output * (1 - output);
}

double WNeuron::getPartDeriv(double trainOutput) {
	return -(trainOutput - output);
}

double WNeuron::getSynapse(int neuronId) {
	return synapses.at(neuronId);
}

void WNeuron::updateSynapses(double delta) {
	for(int i = 0; i < synapses.size(); i++)
		synapses[i] -= LEARNING_RATE * delta * inputs.at(i);
}
