#include "InputRecordDialog.h"
#include "ui_inputrecorddialog.h"
#include <string>

InputRecordDialog::InputRecordDialog(QWidget *parent) 
    : QDialog(parent),
    ui(new Ui::InputRecordDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Добавление новой записи");

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &InputRecordDialog::OnAccept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

InputRecordDialog::InputRecordDialog(SP_PB_RECORD spRecord, QWidget* parent)
    : QDialog(parent),
    m_spRecord(spRecord),
    ui(new Ui::InputRecordDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Редактирование выбранной записи");

    Init();

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &InputRecordDialog::OnAccept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

InputRecordDialog::~InputRecordDialog()
{
    delete ui;
}

SP_PB_RECORD InputRecordDialog::getPBRecord()
{
    return m_spRecord;
}

void InputRecordDialog::Init()
{
    if (!m_spRecord)
        return;

    QString strFirstName = QString::fromStdWString(m_spRecord->getFirstName());
    QString strSecondName = QString::fromStdWString(m_spRecord->getLastName());
    QString strPhone = QString::fromStdString(m_spRecord->getPhone());
    QString strEMail = QString::fromStdString(m_spRecord->getEMail());

    ui->lineEditFirstName->setText(strFirstName);
    ui->lineEditSecondName->setText(strSecondName);
    ui->lineEditPhone->setText(strPhone);
    ui->lineEditEMail->setText(strEMail);
}

void InputRecordDialog::OnAccept()
{
    if (!m_spRecord)
    {
        m_spRecord.reset(new PBRecord);
    }

    QString strFirstName = ui->lineEditFirstName->text();
    QString strSecondName = ui->lineEditSecondName->text();
    QString strPhone = ui->lineEditPhone->text();
    QString strEMail = ui->lineEditEMail->text();

    std::wstring sFirstName = strFirstName.toStdWString();
    std::wstring sSecondName = strSecondName.toStdWString();
    std::string sPhone = strPhone.toStdString();
    std::string sEMail = strEMail.toStdString();

    m_spRecord->setFirstName(sFirstName);
    m_spRecord->setLastName(sSecondName);
    m_spRecord->setPhone(sPhone);
    m_spRecord->setEMail(sEMail);
    
    QDialog::accept();
}
