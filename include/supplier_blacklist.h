#ifndef SUPPLIER_BLACKLIST_H
#define SUPPLIER_BLACKLIST_H

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
    bool isBlacklisted;

    Supplier(int id = 0, const std::string& n = "", const std::string& person = "", const std::string& email = "", const std::string& phone = "")
        : supplierId(id), name(n), contactPerson(person), contactEmail(email), contactPhone(phone), isBlacklisted(false) {}
};

bool blacklistSupplier(int supplierId, std::vector<Supplier>& suppliers);
bool unblacklistSupplier(int supplierId, std::vector<Supplier>& suppliers);
bool checkSupplierBlacklistStatus(int supplierId, const std::vector<Supplier>& suppliers);
void listBlacklistedSuppliers(const std::vector<Supplier>& suppliers);

#endif // SUPPLIER_BLACKLIST_H