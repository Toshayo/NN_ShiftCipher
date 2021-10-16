#include "WMainWindow.h"
#include <QMessageBox>


WMainWindow::WMainWindow() : QWidget() {
	vBox_main = new QVBoxLayout;

	hBox_input = new QHBoxLayout;

	lbl_input = new QLabel("Input :");
	tbx_input = new QLineEdit;

	hBox_input->addWidget(lbl_input);
	hBox_input->addWidget(tbx_input);
	hBox_input->addSpacing(100);

	btn_calc = new QPushButton("Calculate");
	btn_calc->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	QObject::connect(btn_calc, SIGNAL(clicked()), this, SLOT(nnActivate()));

	hBox_output = new QHBoxLayout;

	lbl_output = new QLabel("Output :");
	tbx_output = new QLineEdit;
	tbx_output->setEnabled(false);

	hBox_output->addSpacing(100);
	hBox_output->addWidget(lbl_output);
	hBox_output->addWidget(tbx_output);

	btn_train = new QPushButton("Train");
	btn_train->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	QObject::connect(btn_train, SIGNAL(clicked()), this, SLOT(nnTrain()));

	vBox_main->addLayout(hBox_input);
	vBox_main->addWidget(btn_calc);
	vBox_main->addLayout(hBox_output);
	vBox_main->addWidget(btn_train);
	vBox_main->setAlignment(btn_calc, Qt::AlignHCenter);

	setLayout(vBox_main);

	breinz = new WBrains(8, QList<int>{20, 20}, 8);
	rnd = new QRandomGenerator;
}

WMainWindow::~WMainWindow() {
	breinz->~WBrains();
	delete breinz;
	delete btn_train;
	delete tbx_output;
	delete lbl_output;
	delete btn_calc;
	delete tbx_input;
	delete lbl_input;
	delete hBox_output;
	delete hBox_input;
	delete vBox_main;
	delete rnd;
}

void WMainWindow::nnActivate() {
	QString outTxt = "";
	for(int i = 0; i < tbx_input->text().length(); i++) {
		QList<double> inputs;
		uchar input = tbx_input->text().at(i).toLatin1();

		inputs.append((input & 0b10000000) != 0 ? 1 : 0);
		inputs.append((input & 0b01000000) != 0 ? 1 : 0);
		inputs.append((input & 0b00100000) != 0 ? 1 : 0);
		inputs.append((input & 0b00010000) != 0 ? 1 : 0);
		inputs.append((input & 0b00001000) != 0 ? 1 : 0);
		inputs.append((input & 0b00000100) != 0 ? 1 : 0);
		inputs.append((input & 0b00000010) != 0 ? 1 : 0);
		inputs.append((input & 0b00000001) != 0 ? 1 : 0);

		QList<double> outputs = breinz->activate(inputs);
		uchar chr = listToChar(outputs);
		
		if(chr == 255)
			outTxt.append(input);
		else
			outTxt.append(chr);
	}
	tbx_output->setText(outTxt);
}

void WMainWindow::nnTrain() {
	QString trainInputSet  = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz ";
	QString trainOutputSet = "DEFGHIJKLMNOPQRSTUVWXYZABCdefghijklmnopqrstuvwxyzabc ";

	for(uchar c = 0; c < 255; c++)
		if(!trainInputSet.contains(QChar::fromLatin1(c))) {
			trainInputSet.append(c);
			trainOutputSet.append(255);
		}
	
	for(int i = 0; i < LEARN_ITERATIONS; i++) {
		int randomItem = rnd->generate() % trainInputSet.size();
		QList<double> trainInputs = charToList(trainInputSet.at(randomItem).toLatin1());
		QList<double> trainOutputs = charToList(trainOutputSet.at(randomItem).toLatin1());

		breinz->train(trainInputs, trainOutputs);
	}

	QMessageBox::information(this, "Info", "Training finished");
}

QList<double> WMainWindow::charToList(uchar c) {
	QList<double> inputs;

	inputs.append((c & 0b10000000) != 0 ? 1 : 0);
	inputs.append((c & 0b01000000) != 0 ? 1 : 0);
	inputs.append((c & 0b00100000) != 0 ? 1 : 0);
	inputs.append((c & 0b00010000) != 0 ? 1 : 0);
	inputs.append((c & 0b00001000) != 0 ? 1 : 0);
	inputs.append((c & 0b00000100) != 0 ? 1 : 0);
	inputs.append((c & 0b00000010) != 0 ? 1 : 0);
	inputs.append((c & 0b00000001) != 0 ? 1 : 0);

	return inputs;
}

uchar WMainWindow::listToChar(QList<double> l) {
	uchar out = 0;
	int weights[] = {
		0b10000000,
		0b01000000,
		0b00100000,
		0b00010000,
		0b00001000,
		0b00000100,
		0b00000010,
		0b00000001
	};
	for(int i = 0; i < l.size(); i++)
		out += round(l.at(i)) * weights[i];
	return out;
}
