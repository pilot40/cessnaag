#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore/QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spinBSP->setVisible(false);
    ui->spinBSP1->setVisible(false);
    ui->label_31->setVisible(false);
    ui->label_32->setVisible(false);

    ui->spinBoxS->setInputMethodHints(Qt::ImhDigitsOnly);
    ui->spinBoxSalt->setInputMethodHints(Qt::ImhDigitsOnly);
    ui->spinTks->setInputMethodHints(Qt::ImhDigitsOnly);
    ui->spinZagr->setInputMethodHints(Qt::ImhDigitsOnly);
    ui->spinZagr_2->setInputMethodHints(Qt::ImhDigitsOnly);
    ui->spinZagr_3->setInputMethodHints(Qt::ImhDigitsOnly);
    ui->spinCargoA->setInputMethodHints(Qt::ImhDigitsOnly);
    ui->spinCargoB->setInputMethodHints(Qt::ImhDigitsOnly);
    ui->spinCargoC->setInputMethodHints(Qt::ImhDigitsOnly);
    ui->spinCargoD->setInputMethodHints(Qt::ImhDigitsOnly);
    ui->spinBg4->setInputMethodHints(Qt::ImhDigitsOnly);
    ui->spinBg6->setInputMethodHints(Qt::ImhDigitsOnly);
    ui->spinBSP->setInputMethodHints(Qt::ImhDigitsOnly);
    ui->spinBSP1->setInputMethodHints(Qt::ImhDigitsOnly);
    ui->lineLbs1->setInputMethodHints(Qt::ImhDigitsOnly);
    ui->lineKg2->setInputMethodHints(Qt::ImhDigitsOnly);
    ui->lineEditG_2->setInputMethodHints(Qt::ImhDigitsOnly);

    connect(ui->exit, SIGNAL(triggered()), this, SLOT(closeapp()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(closeapp()));

    connect(ui->aboutApp, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->butRasch, SIGNAL(clicked()), this, SLOT(fuel()));
    connect(ui->butRaschVes, SIGNAL(clicked()), this, SLOT(ves()));
    connect(ui->comboBrake, SIGNAL(currentIndexChanged(int)), ui->comboWind, SLOT(setCurrentIndex(int)));
    connect(ui->cbBort, SIGNAL(currentIndexChanged(int)), this, SLOT(pola(int)));
    connect(ui->pbKg, SIGNAL(clicked()), this, SLOT(kg()));
    connect(ui->pbLbs, SIGNAL(clicked()), this, SLOT(lbs()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fuel()
{
    int S = ui->spinBoxS->value();
    int Salt = ui->spinBoxSalt->value();
    float Tzap = (float)Salt/280;//Время полета до запасного
    float Tp = (float)S/280; //Время полета до ап
    int Hh = (int)Tp;
    int Mm = (int)((Tp- Hh)*60);
    QTime n;
    n.setHMS(Hh,Mm,00,00);
    int Gpol = (Tp*150*0.03)+(Tp*150);
    int Gzap = (Tzap*150)+75;
    int Gf = Gpol + Gzap;
    ui->lineEditGp->setText(QString::number(Gpol));//Вывод топлива на полет
    ui->lineEditGz->setText(QString::number(Gzap));//Вывод топлива до запасного
    ui->lineEditG->setText(QString::number(Gf));//Вывод общего топлива
    ui->lineEditG_2->setText(QString::number(Gf));//Вывод общего топлива для загрузки
    ui->timeEdit->setTime(n);//Вывод времени полёта
    /*
    QGraphicsScene * scen = new QGraphicsScene();
    QPixmap * pix = new QPixmap();
    pix->load("gr.png");
    scen->addPixmap(*pix);
    ui->Mnemo->setScene(scen);//Mnemo - компонент QGraphicsView

    */

}

void MainWindow::pola(int comboIndex)
{

//В зависимости от того какой элемент выбран в комбобоксе делаем видимыми или невидимыми
//определенные спины и лейблы
switch(comboIndex)
{
case 0:
    ui->spinBSP->setVisible(false);
    ui->spinBSP1->setVisible(false);
    ui->label_31->setVisible(false);
    ui->label_32->setVisible(false);
    ui->spinZagr->setMaximum(240);
    ui->spinZagr_2->setMaximum(240);
    ui->spinZagr_3->setMaximum(240);
    break;
case 1:
    ui->spinBSP->setVisible(true);
    ui->label_31->setVisible(true);
    ui->spinBSP1->setVisible(false);
    ui->label_32->setVisible(false);
    ui->spinZagr->setMaximum(240);
    ui->spinZagr_2->setMaximum(80);
    ui->spinZagr_3->setMaximum(80);
    break;
case 2:
    ui->spinBSP1->setVisible(true);
    ui->label_32->setVisible(true);
    ui->spinBSP->setVisible(true);
    ui->label_31->setVisible(true);
    ui->spinZagr->setMaximum(80);
    ui->spinZagr_2->setMaximum(80);
    ui->spinZagr_3->setMaximum(80);

    break;
}
}
void MainWindow::ves()
{
//67422_пасс
    if (ui->cbBort->currentIndex() == 0){
        ui->lineVzl->setStyleSheet("color: green; background-color: rgb(255, 255, 255);");
        ui->lineCentr->setStyleSheet("color: green; background-color: rgb(255, 255, 255);");
        float Gpust = 2402.41;//вес пустого кг
        int Gsl = 39;
        int Gfuel = ui->lineEditG_2->text().toInt();
        int vEk = 80;
        float Gvzl = Gpust+(float)Gsl+(float)Gfuel+((float)ui->spinTks->value()*4.1731)+((float)ui->spinEk->value()*vEk)+((float)ui->spinZagr->value())+((float)ui->spinZagr_2->value())+((float)ui->spinZagr_3->value())+((float)ui->spinCargoA->value())+((float)ui->spinCargoB->value())+((float)ui->spinCargoC->value())+((float)ui->spinCargoD->value())+((float)ui->spinBg4->value())+((float)ui->spinBg6->value())-(float)16;
        ui->lineVzl->setText(QString::number(Gvzl));
        if (Gvzl>3969) {
            ui->lineVzl->setStyleSheet("color: red; background-color: rgb(255, 255, 255);");
        }
        float CG = (((1018.60+22.35+(((float)Gfuel/0.4536)/4.92)+23.90+23.90+((((float)ui->spinZagr->value()/0.4536)*192.6)/1000)+((((float)ui->spinZagr_2->value()/0.4536)*229.2)/1000)+((((float)ui->spinZagr_3->value()/0.4536)*265.8)/1000)+((((float)ui->spinCargoA->value()/0.4536)*132.4)/1000)+((((float)ui->spinCargoB->value()/0.4536)*182.1)/1000)+((((float)ui->spinCargoC->value()/0.4536)*233.4)/1000)+((((float)ui->spinCargoD->value()/0.4536)*287.6)/1000)+((((float)ui->spinBg4->value()/0.4536)*294.5)/1000)+((((float)ui->spinBg6->value()/0.4536)*344)/1000)+((float)ui->spinTks->value()*9.2*195.77/1000)-7.11)/(Gvzl/0.4536))*1000);
        float Centr = (CG-177.57)/0.664;
        ui->lineCentr->setText(QString::number(Centr));
        if (Centr>40.33) {
            ui->lineCentr->setStyleSheet("color: red; background-color: rgb(255, 255, 255);");
        }
        ui->lineCG->setText(QString::number(CG));//вывод плеча CG location(для графика)

    }
    else if (ui->cbBort->currentIndex() == 1){
        //67422_сз1
        ui->lineVzl->setStyleSheet("color: green; background-color: rgb(255, 255, 255);");
        ui->lineCentr->setStyleSheet("color: green; background-color: rgb(255, 255, 255);");
        float Gpust = 2344.79;//вес пустого кг
        int Gsl = 39;
        int Gfuel = ui->lineEditG_2->text().toInt();
        int vEk = 80;
        float Gvzl = Gpust+(float)Gsl+(float)Gfuel+((float)ui->spinTks->value()*4.173)+((float)ui->spinEk->value()*vEk)+((float)ui->spinZagr->value())+((float)ui->spinZagr_2->value())+((float)ui->spinZagr_3->value())+((float)ui->spinBSP->value())+((float)ui->spinCargoA->value())+((float)ui->spinCargoB->value())+((float)ui->spinCargoC->value())+((float)ui->spinCargoD->value())+((float)ui->spinBg4->value())+((float)ui->spinBg6->value())-(float)16;
        ui->lineVzl->setText(QString::number(Gvzl));
        if (Gvzl>3969) {
            ui->lineVzl->setStyleSheet("color: red; background-color: rgb(255, 255, 255);");
        }
        float CG = (((996.71+22.35+(((float)Gfuel/0.4536)/4.92)+23.9+23.9+((((float)ui->spinZagr->value()/0.4536)*192.6)/1000)+((((float)ui->spinZagr_2->value()/0.4536)*229.2)/1000)+((((float)ui->spinZagr_3->value()/0.4536)*265.8)/1000)+((((float)ui->spinBSP->value()/0.4536)*248.3)/1000)+((((float)ui->spinCargoA->value()/0.4536)*132.4)/1000)+((((float)ui->spinCargoB->value()/0.4536)*182.1)/1000)+((((float)ui->spinCargoC->value()/0.4536)*233.4)/1000)+((((float)ui->spinCargoD->value()/0.4536)*287.6)/1000)+((((float)ui->spinBg4->value()/0.4536)*294.5)/1000)+((((float)ui->spinBg6->value()/0.4536)*344)/1000)+((float)ui->spinTks->value()*9.2*195.77/1000)-7.11)/(Gvzl/0.4536))*1000);
        float Centr = (CG-177.57)/0.664;
        ui->lineCentr->setText(QString::number(Centr));
        if (Centr>40.33) {
            ui->lineCentr->setStyleSheet("color: red; background-color: rgb(255, 255, 255);");
        }
        ui->lineCG->setText(QString::number(CG));

    }
    else if (ui->cbBort->currentIndex() == 2){
        //67422_сз2
        ui->lineVzl->setStyleSheet("color: green; background-color: rgb(255, 255, 255);");
        ui->lineCentr->setStyleSheet("color: green; background-color: rgb(255, 255, 255);");
        float Gpust = 2329.07;//вес пустого кг
        int Gsl = 39;
        int Gfuel = ui->lineEditG_2->text().toInt();
        int vEk = 80;
        float Gvzl = Gpust+(float)Gsl+(float)Gfuel+((float)ui->spinTks->value()*4.173)+((float)ui->spinEk->value()*vEk)+((float)ui->spinZagr->value())+((float)ui->spinZagr_2->value())+((float)ui->spinZagr_3->value())+((float)ui->spinBSP->value())+((float)ui->spinBSP1->value())+((float)ui->spinCargoA->value())+((float)ui->spinCargoB->value())+((float)ui->spinCargoC->value())+(ui->spinCargoD->value())+((float)ui->spinBg4->value())+((float)ui->spinBg6->value())-(float)16;
        ui->lineVzl->setText(QString::number(Gvzl));
        if (Gvzl>3969) {
            ui->lineVzl->setStyleSheet("color: red; background-color: rgb(255, 255, 255);");
        }
        float CG = (((991.76+22.35+(((float)Gfuel/0.4536)/4.92)+23.90+23.90+((((float)ui->spinZagr->value()/0.4536)*192.6)/1000)+((((float)ui->spinZagr_2->value()/0.4536)*229.2)/1000)+((((float)ui->spinZagr_3->value()/0.4536)*295.0)/1000)+((((float)ui->spinBSP1->value()/0.4536)*207.3)/1000)+((((float)ui->spinBSP->value()/0.4536)*261.3)/1000)+((((float)ui->spinCargoA->value()/0.4536)*132.4)/1000)+((((float)ui->spinCargoB->value()/0.4536)*182.1)/1000)+((((float)ui->spinCargoC->value()/0.4536)*233.4)/1000)+((((float)ui->spinCargoD->value()/0.4536)*287.6)/1000)+((((float)ui->spinBg4->value()/0.4536)*294.5)/1000)+((((float)ui->spinBg6->value()/0.4536)*344)/1000)+((float)ui->spinTks->value()*9.2*195.77/1000)-7.11)/(Gvzl/0.4536))*1000);
        float Centr = (CG-177.57)/0.664;
        ui->lineCentr->setText(QString::number(Centr));
        if (Centr>40.33) {
            ui->lineCentr->setStyleSheet("color: red; background-color: rgb(255, 255, 255);");
        }
        ui->lineCG->setText(QString::number(CG));

    }
}

void MainWindow::lbs()//Фунты->Кг
{
  int kg1;
  int lbs1 = ui->lineLbs1->text().toInt();
  ui->lineKg1->clear();
  kg1 =  round(lbs1*0.45359237);
  ui->lineKg1->setText(QString::number(kg1));
  ui->lineKg2->clear();
  ui->lineLbs2->clear();
}

void MainWindow::kg()//Кг->Фунты
{
  int lbs2;
  int kg2 = ui->lineKg2->text().toInt();
  ui->lineLbs2->clear();
  lbs2 = round(kg2*2.2046223302272);
  ui->lineLbs2->setText(QString::number(lbs2));
  ui->lineKg1->clear();
  ui->lineLbs1->clear();
}

void MainWindow::about()
{
    QMessageBox msgBox;
    QPushButton *okButton = msgBox.addButton(QMessageBox::Ok);
    msgBox.setStyleSheet("background-color: qlineargradient(spread:pad, x1:0.488, y1:0, x2:0.497, y2:1, stop:0 rgba(210, 216, 223, 255), stop:1 rgba(146, 165, 186, 255));font: 12pt ;Arial;font: bold;");
    msgBox.setText(tr("Расчёты для Cessna 208B \n ООО Аэрогео \n Версия 1.1\n Автор: Зуев М.Г.\n pilot40@gmail.com \n Лицензия: GPL v.3"));
    msgBox.setWindowIcon(QIcon(QDir::currentPath() + "/67430.ico"));
    okButton->setStyleSheet("background-color: rgb(255, 255, 255);");
    msgBox.exec();
}

void MainWindow::closeapp()
{
    close();
}

void MainWindow::setOrientation(ScreenOrientation orientation)
{
#if defined(Q_OS_SYMBIAN)
    // If the version of Qt on the device is < 4.7.2, that attribute won't work
    if (orientation != ScreenOrientationAuto) {
        const QStringList v = QString::fromAscii(qVersion()).split(QLatin1Char('.'));
        if (v.count() == 3 && (v.at(0).toInt() << 16 | v.at(1).toInt() << 8 | v.at(2).toInt()) < 0x040702) {
            qWarning("Screen orientation locking only supported with Qt 4.7.2 and above");
            return;
        }
    }
#endif // Q_OS_SYMBIAN

    Qt::WidgetAttribute attribute;
    switch (orientation) {
#if (QT_VERSION < QT_VERSION_CHECK(4, 7, 2)) || (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    // Qt < 4.7.2 does not yet have the Qt::WA_*Orientation attributes
    case ScreenOrientationLockPortrait:
        attribute = static_cast<Qt::WidgetAttribute>(128);
        break;
    case ScreenOrientationLockLandscape:
        attribute = static_cast<Qt::WidgetAttribute>(129);
        break;
    default:
    case ScreenOrientationAuto:
        attribute = static_cast<Qt::WidgetAttribute>(130);
        break;
#else // QT_VERSION < 0x040702
    case ScreenOrientationLockPortrait:
        attribute = Qt::WA_LockPortraitOrientation;
        break;
    case ScreenOrientationLockLandscape:
        attribute = Qt::WA_LockLandscapeOrientation;
        break;
    default:
    case ScreenOrientationAuto:
        attribute = Qt::WA_AutoOrientation;
        break;
#endif // QT_VERSION < 0x040702
    };
    setAttribute(attribute, true);
}

void MainWindow::showExpanded()
{
#if defined(Q_OS_SYMBIAN) || defined(Q_WS_SIMULATOR)
    showFullScreen();
#elif defined(Q_WS_MAEMO_5)
    showMaximized();
#else
    show();
#endif
}
