#pragma once

#include "PBRecord.h"
#include <QtWidgets/QMainWindow>
#include "ui_PhoneBook.h"
#include <map>
#include "IDAL.h"

class QVBoxLayout;
class QTreeWidget;
class QTreeWidgetItem;
class QStringList;
class QLabel;

using MAP_LETTERS = std::map<ushort, QTreeWidgetItem*>;

class PhoneBook : public QMainWindow
{
    Q_OBJECT
public:
    PhoneBook(QWidget *parent = nullptr);
    ~PhoneBook();

protected:
    void resizeEvent(QResizeEvent* event) override;
    void closeEvent(QCloseEvent* event) override;
private:
    void PrepareRecords();
    void RefreshPhoneBook();
private:
    QTreeWidget* m_pTreeWidget;
    QVBoxLayout* m_pVBoxLayout;
private:
    MAP_LETTERS PrepareLetters();
    QTreeWidgetItem* AddLetterItem(ushort chrLetter);
    QTreeWidgetItem* AddRecordItem(QTreeWidgetItem* pParent, SP_PB_RECORD spRecord);
    QStringList ConvertToList(SP_PB_RECORD spRecord);
private:
    Ui::PhoneBookClass ui;
private:
    SP_DAL m_spDal;
    bool m_bIsDataBaseConnected;
    VECT_PB_RECORDS m_vectPBRecords;
    MAP_LETTERS m_mapLetters;
    long m_n_select = 0L;
    QLabel* m_pDataBaseIcon;
    QLabel* m_pSelectedRecord;
    QPixmap GetIconByIndex(int nIconIndex);
    void PrepareDataBaseIcon();
    void PrepareStatusBarSelectedRecord(long n_selected_record_id);
    SP_PB_RECORD FindRecord(long n_selected_id);
public slots:
    void slotExit();
    void slotEdit();
    void slotAddNew();
    void slotRemove();
    void slotAbout();
    void slotItemClicked(QTreeWidgetItem* ptrItem, int n_column);    
    void OnTimerStartSingleShot();
};
