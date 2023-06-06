/********************************************************************************
** Form generated from reading UI file 'InputRecordDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTRECORDDIALOG_H
#define UI_INPUTRECORDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InputRecordDialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *labelFirstName;
    QLineEdit *lineEditFirstName;
    QLabel *labelSecondName;
    QLineEdit *lineEditSecondName;
    QLabel *labelPhone;
    QLineEdit *lineEditPhone;
    QLabel *labelEMail;
    QLineEdit *lineEditEMail;

    void setupUi(QDialog *InputRecordDialog)
    {
        if (InputRecordDialog->objectName().isEmpty())
            InputRecordDialog->setObjectName(QString::fromUtf8("InputRecordDialog"));
        InputRecordDialog->resize(400, 197);
        buttonBox = new QDialogButtonBox(InputRecordDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(290, 20, 81, 101));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        verticalLayoutWidget = new QWidget(InputRecordDialog);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(9, 9, 271, 176));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        labelFirstName = new QLabel(verticalLayoutWidget);
        labelFirstName->setObjectName(QString::fromUtf8("labelFirstName"));

        verticalLayout->addWidget(labelFirstName);

        lineEditFirstName = new QLineEdit(verticalLayoutWidget);
        lineEditFirstName->setObjectName(QString::fromUtf8("lineEditFirstName"));

        verticalLayout->addWidget(lineEditFirstName);

        labelSecondName = new QLabel(verticalLayoutWidget);
        labelSecondName->setObjectName(QString::fromUtf8("labelSecondName"));

        verticalLayout->addWidget(labelSecondName);

        lineEditSecondName = new QLineEdit(verticalLayoutWidget);
        lineEditSecondName->setObjectName(QString::fromUtf8("lineEditSecondName"));

        verticalLayout->addWidget(lineEditSecondName);

        labelPhone = new QLabel(verticalLayoutWidget);
        labelPhone->setObjectName(QString::fromUtf8("labelPhone"));

        verticalLayout->addWidget(labelPhone);

        lineEditPhone = new QLineEdit(verticalLayoutWidget);
        lineEditPhone->setObjectName(QString::fromUtf8("lineEditPhone"));

        verticalLayout->addWidget(lineEditPhone);

        labelEMail = new QLabel(verticalLayoutWidget);
        labelEMail->setObjectName(QString::fromUtf8("labelEMail"));

        verticalLayout->addWidget(labelEMail);

        lineEditEMail = new QLineEdit(verticalLayoutWidget);
        lineEditEMail->setObjectName(QString::fromUtf8("lineEditEMail"));

        verticalLayout->addWidget(lineEditEMail);


        retranslateUi(InputRecordDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), InputRecordDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), InputRecordDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(InputRecordDialog);
    } // setupUi

    void retranslateUi(QDialog *InputRecordDialog)
    {
        InputRecordDialog->setWindowTitle(QCoreApplication::translate("InputRecordDialog", "Dialog", nullptr));
        labelFirstName->setText(QCoreApplication::translate("InputRecordDialog", "\320\220\320\261\320\276\320\275\320\265\320\275\321\202 (\320\230\320\274\321\217):", nullptr));
        labelSecondName->setText(QCoreApplication::translate("InputRecordDialog", "\320\220\320\261\320\276\320\275\320\265\320\275\321\202 (\320\244\320\260\320\274\320\270\320\273\320\270\321\217):", nullptr));
        labelPhone->setText(QCoreApplication::translate("InputRecordDialog", "\320\235\320\276\320\274\320\265\321\200 \321\202\320\265\320\273\320\265\321\204\320\276\320\275\320\260:", nullptr));
        labelEMail->setText(QCoreApplication::translate("InputRecordDialog", "E-mail:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputRecordDialog: public Ui_InputRecordDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTRECORDDIALOG_H
