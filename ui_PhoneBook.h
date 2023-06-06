/********************************************************************************
** Form generated from reading UI file 'PhoneBook.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PHONEBOOK_H
#define UI_PHONEBOOK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PhoneBookClass
{
public:
    QAction *actionExit;
    QAction *actionAdd_New;
    QAction *actionRemove;
    QAction *actionEdit;
    QAction *actionAbout;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menuRecord;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PhoneBookClass)
    {
        if (PhoneBookClass->objectName().isEmpty())
            PhoneBookClass->setObjectName(QString::fromUtf8("PhoneBookClass"));
        PhoneBookClass->resize(744, 450);
        actionExit = new QAction(PhoneBookClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionAdd_New = new QAction(PhoneBookClass);
        actionAdd_New->setObjectName(QString::fromUtf8("actionAdd_New"));
        actionRemove = new QAction(PhoneBookClass);
        actionRemove->setObjectName(QString::fromUtf8("actionRemove"));
        actionEdit = new QAction(PhoneBookClass);
        actionEdit->setObjectName(QString::fromUtf8("actionEdit"));
        actionAbout = new QAction(PhoneBookClass);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        centralWidget = new QWidget(PhoneBookClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        PhoneBookClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PhoneBookClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 744, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menuRecord = new QMenu(menuBar);
        menuRecord->setObjectName(QString::fromUtf8("menuRecord"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        PhoneBookClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PhoneBookClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        PhoneBookClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PhoneBookClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        PhoneBookClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menuRecord->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menu->addAction(actionExit);
        menuRecord->addAction(actionAdd_New);
        menuRecord->addAction(actionRemove);
        menuRecord->addAction(actionEdit);
        menuHelp->addAction(actionAbout);

        retranslateUi(PhoneBookClass);

        QMetaObject::connectSlotsByName(PhoneBookClass);
    } // setupUi

    void retranslateUi(QMainWindow *PhoneBookClass)
    {
        PhoneBookClass->setWindowTitle(QCoreApplication::translate("PhoneBookClass", "PhoneBook", nullptr));
        actionExit->setText(QCoreApplication::translate("PhoneBookClass", "\320\222\321\213\321\205\320\276\320\264", nullptr));
#if QT_CONFIG(tooltip)
        actionExit->setToolTip(QCoreApplication::translate("PhoneBookClass", "\320\222\321\213\321\205\320\276\320\264", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAdd_New->setText(QCoreApplication::translate("PhoneBookClass", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\267\320\260\320\277\320\270\321\201\321\214...", nullptr));
#if QT_CONFIG(tooltip)
        actionAdd_New->setToolTip(QCoreApplication::translate("PhoneBookClass", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\267\320\260\320\277\320\270\321\201\321\214...", nullptr));
#endif // QT_CONFIG(tooltip)
        actionRemove->setText(QCoreApplication::translate("PhoneBookClass", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\267\320\260\320\277\320\270\321\201\321\214", nullptr));
#if QT_CONFIG(tooltip)
        actionRemove->setToolTip(QCoreApplication::translate("PhoneBookClass", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\267\320\260\320\277\320\270\321\201\321\214", nullptr));
#endif // QT_CONFIG(tooltip)
        actionEdit->setText(QCoreApplication::translate("PhoneBookClass", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214...", nullptr));
#if QT_CONFIG(tooltip)
        actionEdit->setToolTip(QCoreApplication::translate("PhoneBookClass", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214...", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAbout->setText(QCoreApplication::translate("PhoneBookClass", "\320\236 \320\237\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265...", nullptr));
#if QT_CONFIG(tooltip)
        actionAbout->setToolTip(QCoreApplication::translate("PhoneBookClass", "\320\236 \320\237\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265...", nullptr));
#endif // QT_CONFIG(tooltip)
        menu->setTitle(QCoreApplication::translate("PhoneBookClass", "\320\244\320\260\320\271\320\273", nullptr));
        menuRecord->setTitle(QCoreApplication::translate("PhoneBookClass", "\320\227\320\260\320\277\320\270\321\201\321\214", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("PhoneBookClass", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PhoneBookClass: public Ui_PhoneBookClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PHONEBOOK_H
