#ifndef WNEURALLAYER_H
#define WNEURALLAYER_H

#include <QList>
#include "WNeuron.h"


class WNeuralLayer {
	public:
		WNeuralLayer(int nbNeurons, double bias);
		~WNeuralLayer();
		void initSynapses(int nbPrevNeurons);
		QList<double> activate(QList<double> inputs);
		QList<double> getOutputDeltas(QList<double> trainOutputs);
		QList<double> getHiddenDeltas(WNeuralLayer *nextLayer, QList<double> nextLayerDeltas);
		double getError(QList<double> deltas, int neuronId);
		void updateSynapses(QList<double> deltas);
	private:
		QList<WNeuron*> neurons;
		double bias;
};

#endif // WNEURALLAYER_H
