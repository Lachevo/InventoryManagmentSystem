#include "supplier_blacklist.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

bool blacklistSupplier(int supplierId, std::vector<Supplier>& suppliers) {
    auto it = std::find_if(suppliers.begin(), suppliers.end(),
                           [supplierId](const Supplier& s) { return s.supplierId == supplierId; });

    if (it != suppliers.end()) {
        if (!it->isBlacklisted) {
            it->isBlacklisted = true;
            std::cout << "Supplier ID " << supplierId << " ('" << it->name << "') has been blacklisted.\n";
        } else {
            std::cout << "Info: Supplier ID " << supplierId << " ('" << it->name << "') is already blacklisted.\n";
        }
        return true;
    } else {
        std::cerr << "Error: Supplier ID " << supplierId << " not found. Cannot blacklist.\n";
        return false;
    }
}

bool unblacklistSupplier(int supplierId, std::vector<Supplier>& suppliers) {
    auto it = std::find_if(suppliers.begin(), suppliers.end(),
                           [supplierId](const Supplier& s) { return s.supplierId == supplierId; });

    if (it != suppliers.end()) {
        if (it->isBlacklisted) {
            it->isBlacklisted = false;
            std::cout << "Supplier ID " << supplierId << " ('" << it->name << "') has been removed from the blacklist.\n";
        } else {
            std::cout << "Info: Supplier ID " << supplierId << " ('" << it->name << "') is not currently blacklisted.\n";
        }
        return true;
    } else {
        std::cerr << "Error: Supplier ID " << supplierId << " not found. Cannot unblacklist.\n";
        return false;
    }
}

bool checkSupplierBlacklistStatus(int supplierId, const std::vector<Supplier>& suppliers) {
    auto it = std::find_if(suppliers.begin(), suppliers.end(),
                           [supplierId](const Supplier& s) { return s.supplierId == supplierId; });

    if (it != suppliers.end()) {
        return it->isBlacklisted;
    } else {
        std::cerr << "Error: Supplier ID " << supplierId << " not found when checking blacklist status.\n";
        return false;
    }
}

void listBlacklistedSuppliers(const std::vector<Supplier>& suppliers) {
    std::cout << "\n--- Blacklisted Suppliers ---\n";
    bool foundBlacklisted = false;
    std::cout << std::left
              << std::setw(8) << "ID"
              << std::setw(30) << "Name"
              << std::setw(25) << "Contact Person"
              << std::setw(30) << "Email"
              << std::endl;
    std::cout << "------------------------------------------------------------------------------------------\n";

    for (const auto& supplier : suppliers) {
        if (supplier.isBlacklisted) {
            std::cout << std::left
                      << std::setw(8) << supplier.supplierId
                      << std::setw(30) << supplier.name
                      << std::setw(25) << supplier.contactPerson
                      << std::setw(30) << supplier.contactEmail
                      << std::endl;
            foundBlacklisted = true;
        }
    }

    if (!foundBlacklisted) {
        std::cout << "No suppliers are currently blacklisted.\n";
    }
    std::cout << "------------------------------------------------------------------------------------------\n";
}