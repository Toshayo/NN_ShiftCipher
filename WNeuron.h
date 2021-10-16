#ifndef WNEURON_H
#define WNEURON_H

#define LEARNING_RATE 0.5

#include <QList>


class WNeuron {
	public:
		WNeuron(double bias);
		void initSynapses(int nbPrevNeurons);
		double activate(QList<double> inputs);
		double sigmoid(double input);
		double getError(double trainOutput);
		double getDeriv();
		double getPartDeriv(double trainOutput);
		double getSynapse(int neuronId);
		void updateSynapses(double delta);
	private:
		double bias;
		double output;
		QList<double> inputs;
		QList<double> synapses;
};

#endif // WNEURON_H
