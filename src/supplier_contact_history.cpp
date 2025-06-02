#include "supplier_contact_history.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

bool addSupplierContactLog(int supplierId, const ContactLog& logEntry, std::vector<Supplier>& suppliers) {
    auto it = std::find_if(suppliers.begin(), suppliers.end(),
                           [supplierId](const Supplier& s) { return s.supplierId == supplierId; });

    if (it != suppliers.end()) {
        it->contactHistory.push_back(logEntry);
        std::cout << "Contact log added successfully for supplier ID " << supplierId << " ('" << it->name << "').\n";
        return true;
    } else {
        std::cerr << "Error: Supplier ID " << supplierId << " not found. Cannot add contact log.\n";
        return false;
    }
}

void viewSupplierContactHistory(int supplierId, const std::vector<Supplier>& suppliers) {
    auto it = std::find_if(suppliers.begin(), suppliers.end(),
                           [supplierId](const Supplier& s) { return s.supplierId == supplierId; });

    if (it != suppliers.end()) {
        std::cout << "\n--- Contact History for Supplier: " << it->name << " (ID: " << it->supplierId << ") ---\n";
        if (it->contactHistory.empty()) {
            std::cout << "No contact history found for this supplier.\n";
        } else {
            std::cout << std::left
                      << std::setw(15) << "Date"
                      << std::setw(20) << "Interaction Type"
                      << "Notes" << std::endl;
            std::cout << "-------------------------------------------------------------------------------------\n";
            for (const auto& log : it->contactHistory) {
                std::cout << std::left
                          << std::setw(15) << log.date
                          << std::setw(20) << log.interactionType
                          << log.notes << std::endl;
            }
        }
        std::cout << "-------------------------------------------------------------------------------------\n";
    } else {
        std::cerr << "Error: Supplier ID " << supplierId << " not found. Cannot view contact history.\n";
    }
}