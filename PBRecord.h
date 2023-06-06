#pragma once
 
#include <vector>
#include <string>
#include <memory>
 
class PBRecord
{
public:
	PBRecord();
    PBRecord(long n_id, const std::string& s_phone, const std::string& s_email,
	    const std::wstring& s_first_name, const std::wstring& s_last_name);
	~PBRecord();
public:
    long getId() const;
	std::string getPhone() const;
	std::string getEMail() const;
	std::wstring getFirstName() const;
	std::wstring getLastName() const;
	void setPhone(const std::string& s_phone);
	void setEMail(const std::string& s_email);
	void setFirstName(const std::wstring& s_first_name);
	void setLastName(const std::wstring& s_last_name);
  
private:
    long m_n_id;
	std::string m_s_phone;
	std::string m_s_email;
	std::wstring m_s_first_name;
	std::wstring m_s_last_name;
};
using SP_PB_RECORD = std::shared_ptr<PBRecord>;
using VECT_PB_RECORDS = std::vector<std::shared_ptr<PBRecord>>;
