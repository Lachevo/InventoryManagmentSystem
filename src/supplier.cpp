#include "supplier.h"

void addSupplier(const Supplier& supplier) {
    suppliers.push_back(supplier);
}
oid addSupplier(const Supplier& supplier) {
    suppliers.push_back(supplier);
    std::cout << "Supplier added successfully.\n";
}

void listSuppliers() {
    for (const auto& s : suppliers) {
        std::cout << "ID: " << s.id << ", Name: " << s.name
            << ", Contact: " << s.contact << "\n";
    }
}


bool editSupplier(int id, const Supplier& updated) {
    for (auto& s : suppliers) {
        if (s.id == id) {
            s = updated;
            return true;
        }
    }
    std::cerr << "Supplier not found!\n";
    return false;
}

Supplier* searchSupplier(int id) {
    for (auto& s : suppliers) {
        if (s.id == id)
            return &s;
    }
    return nullptr;
}


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
