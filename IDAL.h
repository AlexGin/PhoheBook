#pragma once

#include "PBRecord.h"
#include <QtSql>

#include <memory>
#include <vector>

typedef struct OdbcDsn // Представляет ODBC-соединение к СУБД
{
	QString strServer;
	QString strDSN;
	QString strLogin;
	QString strPassw; 	
} OdbcDsn;
using SP_ODBC_DSN = QSharedPointer<OdbcDsn>;

class IDAL // Чисто Абстрактный класс - представление Интерфейса
{
public:
	virtual bool ConnectToDSN(SP_ODBC_DSN) = 0;
	virtual void DisConnect() = 0;
	virtual bool IsDBConnected() const = 0;
	virtual bool InitDBConnect() = 0;
	virtual SP_ODBC_DSN GetConnectionDSN() const = 0;
public: // Реализуем функционал CRUD:
	virtual uint CreateRecord(SP_PB_RECORD spRecord) = 0;
	virtual uint ReadRecords(VECT_PB_RECORDS& vectRecords) = 0;
	virtual uint UpdateRecord(SP_PB_RECORD spRecord) = 0;
	virtual uint DeleteRecord(long n_id) = 0;
public:
	virtual QSqlDatabase& GetDataBase() = 0;
    virtual ~IDAL() {}
};
using SP_DAL = std::shared_ptr<IDAL>;
