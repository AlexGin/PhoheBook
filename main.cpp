#include "PhoneBook.h"
#include <QtWidgets/QApplication>
#include "LogFile.h"

CLogFile glb_log("PhoneBook");

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setAttribute(Qt::AA_DisableWindowContextHelpButton);
    glb_log.SaveLogFile(LOG_MODES::DEBUGING, "Application 'PhoneBook' started!");
    PhoneBook w;
    w.show();
    return a.exec();
}
