#include "PBRecord.h"

PBRecord::PBRecord()
	: m_n_id(0L)
{
}

PBRecord::PBRecord(long n_id, const std::string& s_phone, const std::string& s_email,
	const std::wstring& s_first_name, const std::wstring& s_last_name)
		: m_n_id(n_id), 
		m_s_phone(s_phone),
		m_s_email(s_email),
		m_s_first_name(s_first_name), 
		m_s_last_name(s_last_name)
{
}

PBRecord::~PBRecord()
{
	m_s_phone.clear();
	m_s_email.clear();
	m_s_first_name.clear();
	m_s_last_name.clear();
}

long PBRecord::getId() const
{
	return m_n_id;
}

std::string PBRecord::getPhone() const
{
	return m_s_phone;
}

std::string PBRecord::getEMail() const
{
	return m_s_email;
}

std::wstring PBRecord::getFirstName() const
{
	return m_s_first_name;;
}
std::wstring PBRecord::getLastName() const
{
	return m_s_last_name;
}

void PBRecord::setPhone(const std::string& s_phone)
{
	m_s_phone = s_phone;
}

void PBRecord::setEMail(const std::string& s_email)
{
	m_s_email = s_email;
}

void PBRecord::setFirstName(const std::wstring& s_first_name)
{
	m_s_first_name = s_first_name;
}
void PBRecord::setLastName(const std::wstring& s_last_name)
{
	m_s_last_name = s_last_name;
}