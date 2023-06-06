#pragma once

#include <QDialog>
#include "PBRecord.h"

namespace Ui {
class InputRecordDialog;
}

class InputRecordDialog : public QDialog
{
    Q_OBJECT
public:
    explicit InputRecordDialog(SP_PB_RECORD spRecord, QWidget *parent);
    explicit InputRecordDialog(QWidget* parent);
    ~InputRecordDialog();
    SP_PB_RECORD getPBRecord();
private:
    Ui::InputRecordDialog *ui;
    SP_PB_RECORD m_spRecord;
    void Init();

private slots:
    void OnAccept();
};