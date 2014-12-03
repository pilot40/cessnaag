#include "mainwindow.h"

#include <QtWidgets>
#include <QtCore/QTextStream>
#include <QtCore/QTextCodec>

int main(int argc, char *argv[])
{
    QTextCodec *cyrillicCodec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(cyrillicCodec);


    QApplication app(argc, argv);
    //QApplication::setStyle("plastique");
        //QApplication::setStyle("motif");
        QApplication::setStyle("cleanlooks");
        //QApplication::setStyle("cde");
        //QApplication::setStyle("windows");

    MainWindow mainWindow;
    mainWindow.setOrientation(MainWindow::ScreenOrientationAuto);
    mainWindow.setWindowIcon(QIcon(QDir::currentPath() + "/67430.ico"));
    //mainWindow.setInputMethodHints(Qt::ImhDigitsOnly);
    //mainWindow.resize(availableGeometry().width(), availableGeometry().height());
    //mainWindow.setGeometry(QApplication::desktop()->screenGeometry());
    mainWindow.showExpanded();
    //mainWindow.showMaximized();





    return app.exec();
}
