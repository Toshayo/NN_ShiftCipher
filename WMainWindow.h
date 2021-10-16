#ifndef WMAINWINDOW_H
#define WMAINWINDOW_H

#define LEARN_ITERATIONS 100000

#include <QWidget>
#include <QBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QRandomGenerator>
#include "WBrains.h"

class WMainWindow : public QWidget {
	Q_OBJECT

	public:
		WMainWindow();
		~WMainWindow();
		QList<double> charToList(uchar c);
		uchar listToChar(QList<double> l);
	public slots:
		void nnActivate();
		void nnTrain();
	private:
		QRandomGenerator *rnd;
		WBrains *breinz;
		QVBoxLayout *vBox_main;
			QHBoxLayout *hBox_input;
				QLabel *lbl_input;
				QLineEdit *tbx_input;
			QPushButton *btn_calc;
			QHBoxLayout *hBox_output;
				QLabel *lbl_output;
				QLineEdit *tbx_output;
			QPushButton *btn_train;
};

#endif // WMAINWINDOW_H
