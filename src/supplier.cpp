#include "supplier.h"

bool deleteSupplier(int supplierId, std::vector<Supplier>& suppliers) {
    for (auto it = suppliers.begin(); it != suppliers.end(); ++it) {
        if (it->id == supplierId) {
            suppliers.erase(it);
            return true;
        }
    }
    return false;
}

Supplier* searchSupplier(int supplierId, std::vector<Supplier>& suppliers) {
    for (auto& supplier : suppliers) {
        if (supplier.id == supplierId) return &supplier;
    }
    return nullptr;
}

Supplier* searchSupplier(const std::string& name, std::vector<Supplier>& suppliers) {
    for (auto& supplier : suppliers) {
        if (supplier.name == name) return &supplier;
    }
    return nullptr;
}

Supplier* searchSupplierByContact(const std::string& contact, std::vector<Supplier>& suppliers) {
    for (auto& supplier : suppliers) {
        if (supplier.contact == contact) return &supplier;
    }
    return nullptr;
}
