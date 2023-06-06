#include "PhoneBook.h"
#include "CDAL.h"
#include "LogFile.h"
#include "InputRecordDialog.h"

#include <algorithm>    // std::find_if
#include <QTimer>
#include <QLabel>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QStringList>
#include <QMessageBox>

extern CLogFile glb_log;
SP_DAL g_spDal;

QPixmap* g_pPixmapSmallIcons;

PhoneBook::PhoneBook(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	g_pPixmapSmallIcons = new QPixmap(":/images/smallico.bmp");

	m_pVBoxLayout = new QVBoxLayout(this);

	m_pTreeWidget = new QTreeWidget(this);
	m_pTreeWidget->setColumnCount(5);
	m_pTreeWidget->setColumnWidth(0, 35);   // "Книга"
	m_pTreeWidget->setColumnWidth(1, 175);  // "Абонент (Имя)"
	m_pTreeWidget->setColumnWidth(2, 175);  // "Абон. (Фамилия)"
	m_pTreeWidget->setColumnWidth(3, 155);   // "Номер телефона"
	m_pTreeWidget->setColumnWidth(4, 145);   // "E-mail"
	
	m_pVBoxLayout->addWidget(m_pTreeWidget);

	m_pDataBaseIcon = new QLabel(ui.statusBar);
	m_pDataBaseIcon->setMaximumWidth(18);
	m_pDataBaseIcon->setMinimumWidth(18);
	ui.statusBar->addWidget(m_pDataBaseIcon);

	m_pSelectedRecord = new QLabel(ui.statusBar);
	m_pSelectedRecord->setMaximumWidth(450);
	m_pSelectedRecord->setMinimumWidth(450);
	ui.statusBar->addWidget(m_pSelectedRecord);

	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));
	connect(ui.actionEdit, SIGNAL(triggered()), this, SLOT(slotEdit()));
	connect(ui.actionAdd_New, SIGNAL(triggered()), this, SLOT(slotAddNew()));
	connect(ui.actionRemove, SIGNAL(triggered()), this, SLOT(slotRemove()));
	connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(slotAbout()));

	connect(m_pTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)),
		this, SLOT(slotItemClicked(QTreeWidgetItem*, int)));

	QStringList slCaption;
	slCaption << "Книга" << "Абонент (Имя)" << "Абон. (Фамилия)" << "Номер телефона" << "E-mail";

	m_pTreeWidget->clear();
	m_pTreeWidget->setHeaderLabels(slCaption);

	m_spDal.reset(new CDAL);
	g_spDal = m_spDal;
	int g_cnt = g_spDal.use_count();
	int v_cnt = m_spDal.use_count();
	m_bIsDataBaseConnected = m_spDal->InitDBConnect();

	QTimer::singleShot(200, this, SLOT(OnTimerStartSingleShot())); // 0.2 sec	
}

PhoneBook::~PhoneBook()
{}

void PhoneBook::OnTimerStartSingleShot()
{
	glb_log.SaveLogFile(LOG_MODES::DEBUGING, "PhoneBook::OnTimerStartSingleShot 'PhoneBook' refresh");
	PrepareDataBaseIcon();
	PrepareRecords();
	RefreshPhoneBook();
}

void PhoneBook::slotExit()
{
	this->close();
}

void PhoneBook::slotItemClicked(QTreeWidgetItem* ptrItem, int n_column)
{
	Q_UNUSED(n_column);

	if (!ptrItem)
		return;

	QVariant var = ptrItem->data(0, Qt::UserRole);
	int n_select = var.toInt();
	if (n_select < 0)
	{
		PrepareStatusBarSelectedRecord(0L);
		m_n_select = 0L;
		return;
	}
	m_n_select = static_cast<long>(n_select);
	PrepareStatusBarSelectedRecord(m_n_select);
}

SP_PB_RECORD PhoneBook::FindRecord(long n_selected_id)
{
	auto it = std::find_if(m_vectPBRecords.begin(), m_vectPBRecords.end(),
		[=](SP_PB_RECORD spRecord) -> bool
	{
		long n_id = spRecord->getId();
		if (n_selected_id == n_id)
			return true;

		return false;
	});

	if (it == m_vectPBRecords.end())
		return nullptr;

	SP_PB_RECORD spPBRecord = *it;
	return spPBRecord;
}

void PhoneBook::slotEdit()
{
	if (m_n_select == 0L)
	{
		QMessageBox msgBox;
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.setText("Не выбрано записи для редактирования."
			"\r\nДействие отменено.");
		msgBox.exec();
		return;
	}
	
	SP_PB_RECORD spPBRecord = FindRecord(m_n_select);
	if (!spPBRecord)
		return;

	InputRecordDialog dlg(spPBRecord, this);
	if (QDialog::Accepted != dlg.exec())
		return;

	SP_PB_RECORD sp = dlg.getPBRecord();
	m_spDal->UpdateRecord(sp);

	QTimer::singleShot(1000, this, SLOT(OnTimerStartSingleShot())); // 1 sec
}

void PhoneBook::slotAddNew()
{
	InputRecordDialog dlg(this);
	if (QDialog::Accepted != dlg.exec())
		return;

	SP_PB_RECORD sp = dlg.getPBRecord();
	m_spDal->CreateRecord(sp);

	QTimer::singleShot(1000, this, SLOT(OnTimerStartSingleShot())); // 1 sec
}

void PhoneBook::slotRemove()
{
	if (m_n_select == 0L)
	{
		QMessageBox msgBox;
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.setText("Не выбрано записи для удаления."
			"\r\nДействие отменено.");
		msgBox.exec();
		return;
	}

	QMessageBox msgBoxQuestion;
	msgBoxQuestion.setIcon(QMessageBox::Question);
	msgBoxQuestion.setText("Удалить выбранную звпись из Базы?");
	msgBoxQuestion.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	int ret = msgBoxQuestion.exec();
	if (ret == QMessageBox::Cancel)
		return;

	m_spDal->DeleteRecord(m_n_select);

	QTimer::singleShot(1000, this, SLOT(OnTimerStartSingleShot())); // 1 sec
}

void PhoneBook::closeEvent(QCloseEvent* event)
{
	m_spDal->DisConnect();

	glb_log.SaveLogFile(LOG_MODES::DEBUGING, "The 'PhoneBook' - Application exit");

	QMainWindow::closeEvent(event);
}

void PhoneBook::resizeEvent(QResizeEvent* event)
{
	QMainWindow::resizeEvent(event);

	QRect rect = this->geometry();
	int iHeihgt = rect.height();
	int iWidth = rect.width();
	int iStatusBarHeight = ui.statusBar->height();
	int iMenuBarHeight = ui.menuBar->height();
	int iToolBarHeight = ui.mainToolBar->height();
	iHeihgt -= (iToolBarHeight + iStatusBarHeight + iMenuBarHeight);
	
	QRect rectView(0, (iToolBarHeight + iMenuBarHeight), iWidth, iHeihgt);
	if (m_pVBoxLayout != nullptr)
		m_pVBoxLayout->setGeometry(rectView);
}

QPixmap PhoneBook::GetIconByIndex(int nIconIndex)
{
	QPixmap pm;
	if (!g_pPixmapSmallIcons)
	{
		return pm;
	}

	pm = g_pPixmapSmallIcons->copy(16 * nIconIndex, 0, 16, 16);
	return pm;
}

void PhoneBook::PrepareRecords()
{
	m_vectPBRecords.clear();
	m_spDal->ReadRecords(m_vectPBRecords);
	glb_log.SaveLogFile(LOG_MODES::DEBUGING, "PhoneBook::PrepareRecords - 'PhoneBook' refresh");
}

void PhoneBook::RefreshPhoneBook()
{
	this->m_pTreeWidget->clear();
	m_mapLetters = PrepareLetters();	
	
	for (SP_PB_RECORD sp : m_vectPBRecords)
	{
		std::wstring s_first_name = sp->getFirstName();
		ushort n_letter = s_first_name[0];
		QTreeWidgetItem* pTreeItem = m_mapLetters[n_letter];
		AddRecordItem(pTreeItem, sp);
	}
	this->m_pTreeWidget->expandAll();
}

QStringList PhoneBook::ConvertToList(SP_PB_RECORD spRecord)
{
	QStringList list;
	list.append("");
	list.append(QString::fromStdWString(spRecord->getFirstName()));
	list.append(QString::fromStdWString(spRecord->getLastName()));
	list.append(QString::fromStdString(spRecord->getPhone()));
	list.append(QString::fromStdString(spRecord->getEMail()));
	return list;
}

QTreeWidgetItem* PhoneBook::AddLetterItem(ushort chrLetter)
{
	QTreeWidgetItem* pTreeItem = new QTreeWidgetItem(m_pTreeWidget);
	if (!pTreeItem)
		return nullptr;

	wchar_t chrTextLetter[2];
	chrTextLetter[1] = '\0';
	chrTextLetter[0] = chrLetter;
	QString s = QString::fromStdWString(chrTextLetter);
	pTreeItem->setText(0, s);
	pTreeItem->setData(0, Qt::UserRole, (QVariant)(chrLetter * -1));

	return pTreeItem;
}

QTreeWidgetItem* PhoneBook::AddRecordItem(QTreeWidgetItem* pParent, SP_PB_RECORD spRecord)
{
	QStringList list = ConvertToList(spRecord);

	QTreeWidgetItem* pTreeItem = new QTreeWidgetItem(pParent, list);
	if (!pTreeItem)
		return nullptr;

	long n_id = spRecord->getId();
	pTreeItem->setData(0, Qt::UserRole, (QVariant)n_id);

	return pTreeItem;
}

MAP_LETTERS PhoneBook::PrepareLetters()
{
	MAP_LETTERS map;
	
	// Подготовить Русские буквы:
	for (ushort chrRu = 0x410; chrRu <= 0x42f; chrRu++) 
	{
		QTreeWidgetItem* ptr = AddLetterItem(chrRu);
		map[chrRu] = ptr;
	}

	// Подготовить Английские (Латинские) буквы:
	for (ushort chrEn = 0x41; chrEn <= 0x5a; chrEn++)
	{
		QTreeWidgetItem* ptr = AddLetterItem(chrEn);
		map[chrEn] = ptr;
	}
	return map;
}

void PhoneBook::PrepareStatusBarSelectedRecord(long n_selected_record_id)
{
	SP_PB_RECORD spPBRecord = FindRecord(n_selected_record_id);
	if (!spPBRecord)
	{
		m_pSelectedRecord->setText("");
		return;
	}

	QString strOut;
	strOut =
		QString::fromStdWString(spPBRecord->getFirstName()) + " " +
		QString::fromStdWString(spPBRecord->getLastName()) + " " +
		QString::fromStdString(spPBRecord->getPhone()) + " " +
		QString::fromStdString(spPBRecord->getEMail());
		
	m_pSelectedRecord->setText(strOut);
}

void PhoneBook::PrepareDataBaseIcon()
{
	bool b_connect = m_spDal->IsDBConnected();
	int index = (true == b_connect) ? 6 : 5;
	QPixmap pxmp = GetIconByIndex(index);
	m_pDataBaseIcon->setPixmap(pxmp);
}

void PhoneBook::slotAbout()
{
	QMessageBox msgBoxAbout;
	msgBoxAbout.setIcon(QMessageBox::Information);
	msgBoxAbout.setText("Программа Телефонная Книга - 'Phone Book'");
	msgBoxAbout.setStandardButtons(QMessageBox::Ok);
	msgBoxAbout.exec();
}