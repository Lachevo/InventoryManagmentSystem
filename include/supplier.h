#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <string>
#include <vector>

struct Supplier {
    int id;
    std::string name;
    std::string contact;
    std::vector<int> suppliedProductIds;
};
// Function to add a supplier
void addSupplier(const Supplier& supplier);

// Optional: View all suppliers
void listSuppliers();

// Function declarations
void addSupplier(const Supplier& supplier);
bool editSupplier(int id, const Supplier& updated);
Supplier* searchSupplier(int id);
// Delete a supplier by ID
bool deleteSupplier(int supplierId, std::vector<Supplier>& suppliers);

// Search supplier by ID
Supplier* searchSupplier(int supplierId, std::vector<Supplier>& suppliers);
// Search supplier by name
Supplier* searchSupplier(const std::string& name, std::vector<Supplier>& suppliers);
// Search supplier by contact
Supplier* searchSupplierByContact(const std::string& contact, std::vector<Supplier>& suppliers);

#endif // SUPPLIER_H
