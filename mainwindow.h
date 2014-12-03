#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtWidgets>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum ScreenOrientation {
        ScreenOrientationLockPortrait,
        ScreenOrientationLockLandscape,
        ScreenOrientationAuto
    };

    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
    QAction *exitApp;
    QAction *actionExit;
    QPushButton *butRasch;
    QPushButton *butRaschVes;
    QPushButton *pbLbs;
    QPushButton *pbKg;
    QSpinBox *spinBoxS;
    QSpinBox *spinTks;
    QSpinBox *spinBoxSalt;
    QSpinBox *spinEk;
    QSpinBox *spinZagr;
    QSpinBox *spinZagr_2;
    QSpinBox *spinZagr_3;
    QSpinBox *spinCargoA;
    QSpinBox *spinCargoB;
    QSpinBox *spinCargoC;
    QSpinBox *spinCargoD;
    QSpinBox *spinBg4;
    QSpinBox *spinBg6;
    QSpinBox *spinBSP;
    QSpinBox *spinBSP1;
    QLabel *label_31;
    QLabel *label_32;
    QLineEdit *lineEditG;
    QLineEdit *lineEditGp;
    QLineEdit *lineEditGz;
    QLineEdit *lineEditG_2;
    QLineEdit *lineVzl;
    QLineEdit *lineCentr;
    QLineEdit *lineCG;
    QLineEdit *lineLbs1;
    QLineEdit *lineKg1;
    QLineEdit *lineLbs2;
    QLineEdit *lineKg2;
    QComboBox *cbBort;
    QComboBox *comboBrake;
    QComboBox *comboWind;
    QGraphicsView *Mnemo;
    QAction *exit;

    // Note that this will only have an effect on Symbian and Fremantle.
    void setOrientation(ScreenOrientation orientation);

    void showExpanded();

public slots:
    void fuel();
    void pola(int comboIndex);
    void ves();
    void lbs();
    void kg();
    void closeapp();

private slots:
    void about();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
