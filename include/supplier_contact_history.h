#ifndef SUPPLIER_CONTACT_HISTORY_H
#define SUPPLIER_CONTACT_HISTORY_H

#include <string>
#include <vector>

struct ContactLog {
    std::string date;
    std::string interactionType;
    std::string notes;

    ContactLog(const std::string& d = "", const std::string& type = "", const std::string& n = "")
        : date(d), interactionType(type), notes(n) {}
};

struct Supplier {
    int supplierId;
    std::string name;
    std::string contactPerson;
    std::string contactEmail;
    std::string contactPhone;
    std::vector<ContactLog> contactHistory;

    Supplier(int id = 0, const std::string& n = "", const std::string& person = "", const std::string& email = "", const std::string& phone = "")
        : supplierId(id), name(n), contactPerson(person), contactEmail(email), contactPhone(phone) {}
};

bool addSupplierContactLog(int supplierId, const ContactLog& logEntry, std::vector<Supplier>& suppliers);
void viewSupplierContactHistory(int supplierId, const std::vector<Supplier>& suppliers);

#endif // SUPPLIER_CONTACT_HISTORY_H