#include "statistics_dashboard.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <numeric>
#include <iomanip>

void Sale::calculateTotalPrice() {
    totalPrice = 0.0;
    for (const auto& item : items) {
        totalPrice += item.quantitySold * item.priceAtSale;
    }
}

void displayStatisticsDashboard(const std::vector<Product>& products,
                                const std::set<std::string>& availableCategories,
                                const std::vector<Supplier>& suppliers,
                                const std::vector<Customer>& customers,
                                const std::vector<Sale>& sales) {

    std::cout << "\n========================================\n";
    std::cout << "    INVENTORY MANAGEMENT DASHBOARD    \n";
    std::cout << "========================================\n\n";

    long totalQuantityInStock = 0;
    double totalInventoryValue = 0.0;
    for (const auto& product : products) {
        totalQuantityInStock += product.quantityInStock;
        totalInventoryValue += product.price * product.quantityInStock;
    }
    std::set<std::string> uniqueCategoriesFromProducts;
     if (availableCategories.empty() && !products.empty()) {
        for(const auto& p : products) {
            if(!p.categoryName.empty()) uniqueCategoriesFromProducts.insert(p.categoryName);
        }
    }
    size_t numUniqueCategories = availableCategories.empty() ? uniqueCategoriesFromProducts.size() : availableCategories.size();

    std::cout << "--- Products ---\n";
    std::cout << std::left << std::setw(35) << "Total Number of Products:" << products.size() << std::endl;
    std::cout << std::left << std::setw(35) << "Total Quantity of Items in Stock:" << totalQuantityInStock << std::endl;
    std::cout << std::left << std::setw(35) << "Total Inventory Value:" << "$" << std::fixed << std::setprecision(2) << totalInventoryValue << std::endl;
    std::cout << std::left << std::setw(35) << "Number of Unique Categories:" << numUniqueCategories << std::endl;
    std::cout << "\n";

    long blacklistedSuppliersCount = 0;
    for (const auto& supplier : suppliers) {
        if (supplier.isBlacklisted) {
            blacklistedSuppliersCount++;
        }
    }
    std::cout << "--- Suppliers ---\n";
    std::cout << std::left << std::setw(35) << "Total Number of Suppliers:" << suppliers.size() << std::endl;
    std::cout << std::left << std::setw(35) << "Number of Blacklisted Suppliers:" << blacklistedSuppliersCount << std::endl;
    std::cout << "\n";

    std::cout << "--- Customers ---\n";
    std::cout << std::left << std::setw(35) << "Total Number of Customers:" << customers.size() << std::endl;
    std::cout << "\n";

    long completedSalesCount = 0;
    double totalSalesRevenue = 0.0;
    for (const auto& sale : sales) {
        if (!sale.isCancelled) {
            completedSalesCount++;
            totalSalesRevenue += sale.totalPrice;
        }
    }
    std::cout << "--- Sales ---\n";
    std::cout << std::left << std::setw(35) << "Total Sales Recorded (Completed):" << completedSalesCount << std::endl;
    std::cout << std::left << std::setw(35) << "Total Sales Revenue (Completed):" << "$" << std::fixed << std::setprecision(2) << totalSalesRevenue << std::endl;
    std::cout << "\n";

    std::cout << "========================================\n";
    std::cout << "          End of Dashboard          \n";
    std::cout << "========================================\n";
}