#ifndef WBRAINS_H
#define WBRAINS_H

#include <QList>
#include "WNeuralLayer.h"


class WBrains {
	public:
		WBrains(int nbInputs, int nbHidden, int nbOutputs);
		WBrains(int nbInputs, QList<int> nbHiddens, int nbOutputs);
		~WBrains();
		QList<double> activate(QList<double> inputs);
		void train(QList<double> trainInputs, QList<double> trainOutputs);
	private:
		int inputNeurons;
		QList<WNeuralLayer*> hiddenLayers;
		WNeuralLayer *outputLayer;
};

#endif // WBRAINS_H
