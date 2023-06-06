#include "CDAL.h"
#include "LogFile.h"

extern CLogFile glb_log;

////////////////////////////////////////////////////////////
CDAL::CDAL()
{	
}

CDAL::~CDAL()
{
}

bool CDAL::InitDBConnect()
{
    std::string sConfigIni(CFileUtils::RetrieveParentPath() + "PhoneBook.ini");
    QString strConfigINIFileName(sConfigIni.c_str());

    // .ini format example:
    // https://stackoverflow.com/questions/14365653/how-to-load-settings-in-qt-app-with-qsettings
    QSettings s(strConfigINIFileName, QSettings::IniFormat);

    QSharedPointer<OdbcDsn> spOdbcDsn;
    spOdbcDsn.reset(new OdbcDsn);

    spOdbcDsn->strServer = s.value("DB_CFG_ODBC_DSN/SERVER").toString();
    spOdbcDsn->strDSN = s.value("DB_CFG_ODBC_DSN/DSN").toString();
    spOdbcDsn->strLogin = s.value("DB_CFG_ODBC_DSN/LOGIN").toString();
    spOdbcDsn->strPassw = s.value("DB_CFG_ODBC_DSN/PASSW").toString();

    bool bIsDBConnected = ConnectToDSN(spOdbcDsn);
    return bIsDBConnected;
}

bool CDAL::ConnectToDSN(SP_ODBC_DSN spOdbcDSN)
{
	m_odbcConnection = spOdbcDSN;
#ifdef Q_OS_WIN
	m_dbConnection = QSqlDatabase::addDatabase("QODBC"); // Using qodbc (Qt plugin for ODBC support) for Windows 
#endif
#ifdef Q_OS_LINUX
	m_dbConnection = QSqlDatabase::addDatabase("QPSQL"); // Using PostgresSQL driver for Linux
#endif
	m_dbConnection.setHostName(m_odbcConnection->strServer);
	m_dbConnection.setDatabaseName(m_odbcConnection->strDSN);
	m_dbConnection.setUserName(m_odbcConnection->strLogin);
	m_dbConnection.setPassword(m_odbcConnection->strPassw);
	bool bResult = m_dbConnection.open();
	if (!bResult)
	{
		glb_log.SaveLogFile(LOG_MODES::ERRORLOG, "CDAL::Connect: Data-Base Connction error!");
	//	QSqlError err = m_dbConnection.lastError();
	//	int m = 0;
	}
	else
	{
		glb_log.SaveLogFile(LOG_MODES::DEBUGING, "Data-base '%s' Connection - SUCCESS!",
			m_odbcConnection->strDSN.toStdString().c_str());
	}
	return bResult;
}

void CDAL::DisConnect()
{
	m_dbConnection.close();
}

bool CDAL::IsDBConnected() const
{
	bool bConnected = m_dbConnection.isOpen();
	return bConnected;
}

SP_ODBC_DSN CDAL::GetConnectionDSN() const
{
	return m_odbcConnection;
}

QSqlDatabase& CDAL::GetDataBase()
{
	return m_dbConnection;
}

uint CDAL::ReadRecords(VECT_PB_RECORDS& vectRecords)
{
	QString strQuery =
		"SELECT id, name_first, name_second, phone, email \
         FROM pbk_records \
         ORDER BY id";

	QSqlQuery query(m_dbConnection);
	query.prepare(strQuery);

	if (!query.exec())
	{
		QString qsErr = query.lastError().text();
		std::string sErr = qsErr.toStdString();
		glb_log.SaveLogFile(LOG_MODES::ERRORLOG, "CDAL::ReadRecords ERROR: %s", sErr.c_str());
		return 0; // Error occur
	}

	uint nCounter = 0;
	while (query.next())
	{
		long iID = query.value(0).toUInt();

		QString strNameFirst("-");
		if (!query.value(1).isNull())
			strNameFirst = query.value(1).toString();

		QString strNameSecond("-");
		if (!query.value(2).isNull())
			strNameSecond = query.value(2).toString();

		QString strPhone("-");
		if (!query.value(3).isNull())
			strPhone = query.value(3).toString();

		QString strEMail("-");
		if (!query.value(4).isNull())
			strEMail = query.value(4).toString();

		std::string sPhone = strPhone.toStdString();
		std::string sEMail = strEMail.toStdString();
		std::wstring sNameFirst = strNameFirst.toStdWString();
		std::wstring sNameSecond = strNameSecond.toStdWString();

		SP_PB_RECORD spRecord(new PBRecord(iID, sPhone, sEMail, sNameFirst, sNameSecond));
		vectRecords.push_back(spRecord);

		nCounter++;
	}

	return nCounter;
}

uint CDAL::UpdateRecord(SP_PB_RECORD spRecord)
{
	QString strQuery =
 	 "UPDATE pbk_records SET name_first=:NM1, name_second=:NM2, phone=:PHONE, email=:EMAIL WHERE id = :ID";

	QSqlQuery query(m_dbConnection);
	query.prepare(strQuery);

	long id = spRecord->getId();
	query.bindValue(":ID", id);

	QString strFirstName = QString::fromStdWString(spRecord->getFirstName());
	query.bindValue(":NM1", strFirstName);

	QString strSecondName = QString::fromStdWString(spRecord->getLastName());
	query.bindValue(":NM2", strSecondName);

	QString strPhone = QString::fromStdString(spRecord->getPhone());
	query.bindValue(":PHONE", strPhone);

	QString strEMail = QString::fromStdString(spRecord->getEMail());
	query.bindValue(":EMAIL", strEMail);

	if (!query.exec())
	{
		QString qsErr = query.lastError().text();
		std::string sErr = qsErr.toStdString();
		glb_log.SaveLogFile(LOG_MODES::ERRORLOG, "CDAL::UpdateRecords ERROR: %s", sErr.c_str());		
		return 0; // Error occur
	}
	return 1;
}

uint CDAL::CreateRecord(SP_PB_RECORD spRecord)
{
	QString strQuery =
		"INSERT INTO pbk_records (name_first, name_second, phone, email) \
         VALUES (:NM1, :NM2, :PHONE, :EMAIL);";

	QSqlQuery query(m_dbConnection);
	query.prepare(strQuery);

	QString strFirstName = QString::fromStdWString(spRecord->getFirstName());
	query.bindValue(":NM1", strFirstName);

	QString strSecondName = QString::fromStdWString(spRecord->getLastName());
	query.bindValue(":NM2", strSecondName);

	QString strPhone = QString::fromStdString(spRecord->getPhone());
	query.bindValue(":PHONE", strPhone);

	QString strEMail = QString::fromStdString(spRecord->getEMail());
	query.bindValue(":EMAIL", strEMail);

	if (!query.exec())
	{
		QString qsErr = query.lastError().text();
		std::string sErr = qsErr.toStdString();
		glb_log.SaveLogFile(LOG_MODES::ERRORLOG, "CDAL::CreateRecord ERROR: %s", sErr.c_str());
		return 0; // Error occur
	}
	return 1;
}

uint CDAL::DeleteRecord(long n_id)
{
	QString strQuery = "DELETE FROM pbk_records WHERE id = :ID";

	QSqlQuery query(m_dbConnection);
	query.prepare(strQuery);

	query.bindValue(":ID", n_id);

	if (!query.exec())
	{
		QString qsErr = query.lastError().text();
		std::string sErr = qsErr.toStdString();
		glb_log.SaveLogFile(LOG_MODES::ERRORLOG, "CDAL::DeleteRecord ERROR: {}", sErr.c_str());
		return 0; // Error occur
	}
	return 1;
}
