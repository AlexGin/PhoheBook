#pragma once

#include "IDAL.h"

class CDAL : public QObject, public IDAL
{
	Q_OBJECT
public:
	CDAL();
	~CDAL() override; 
public:
	bool ConnectToDSN(SP_ODBC_DSN spOdbcDSN) override;
	void DisConnect() override;
	bool IsDBConnected() const override;
	bool InitDBConnect() override;
	SP_ODBC_DSN GetConnectionDSN() const override;
public: // Реализуем функционал CRUD:
	virtual uint CreateRecord(SP_PB_RECORD spRecord) override;
	virtual uint ReadRecords(VECT_PB_RECORDS& vectRecords) override;
	virtual uint UpdateRecord(SP_PB_RECORD spRecord) override;
	virtual uint DeleteRecord(long n_id) override;
public:
	QSqlDatabase& GetDataBase() override;
protected:
	QSharedPointer<OdbcDsn> m_odbcConnection; // For ODBC connection support
	QSqlDatabase m_dbConnection;
signals:
	void RecordLoaded(uint nCounter, int iTotalCounter);
};