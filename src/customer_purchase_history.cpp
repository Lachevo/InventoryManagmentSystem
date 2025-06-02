#include "customer_purchase_history.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

void Sale::calculateTotalPrice() {
    totalPrice = 0.0;
    for (const auto& item : items) {
        totalPrice += item.quantitySold * item.priceAtSale;
    }
}

void viewCustomerPurchaseHistory(int customerId,
                                 const std::vector<Customer>& customers,
                                 const std::vector<Sale>& allSales,
                                 const std::vector<Product>& allProducts) {

    auto customerIt = std::find_if(customers.begin(), customers.end(),
                                   [customerId](const Customer& c) { return c.customerId == customerId; });

    if (customerIt == customers.end()) {
        std::cerr << "Error: Customer ID " << customerId << " not found.\n";
        return;
    }

    std::cout << "\n--- Purchase History for Customer: " << customerIt->name
              << " (ID: " << customerIt->customerId << ") ---\n";
    std::cout << "Contact: " << customerIt->contactDetails << std::endl;

    if (customerIt->saleIds.empty()) {
        std::cout << "No purchase history found for this customer.\n";
        std::cout << "--------------------------------------------------\n";
        return;
    }

    bool historyFound = false;
    for (int saleId : customerIt->saleIds) {
        auto saleIt = std::find_if(allSales.begin(), allSales.end(),
                                   [saleId](const Sale& s) { return s.saleId == saleId; });

        if (saleIt != allSales.end()) {
            historyFound = true;
            std::cout << "\n  Sale ID: " << saleIt->saleId
                      << " | Date: " << saleIt->saleDate
                      << " | Total: $" << std::fixed << std::setprecision(2) << saleIt->totalPrice
                      << " | Status: " << (saleIt->isCancelled ? "Cancelled" : "Completed") << std::endl;

            if (!saleIt->items.empty()) {
                std::cout << "    Items Purchased:\n";
                std::cout << "    " << std::left << std::setw(30) << "Product Name"
                          << std::setw(10) << "Qty"
                          << std::setw(15) << "Price/Unit"
                          << std::setw(15) << "Subtotal" << std::endl;
                std::cout << "    ---------------------------------------------------------------------\n";
                for (const auto& item : saleIt->items) {
                    std::string productName = "Unknown Product (ID: " + std::to_string(item.productId) + ")";
                    auto productIt = std::find_if(allProducts.begin(), allProducts.end(),
                                                  [id = item.productId](const Product& p) { return p.id == id; });
                    if (productIt != allProducts.end()) {
                        productName = productIt->name;
                    }

                    std::cout << "    " << std::left << std::setw(30) << productName
                              << std::setw(10) << item.quantitySold
                              << "$" << std::fixed << std::setprecision(2) << std::setw(13) << item.priceAtSale
                              << "$" << std::fixed << std::setprecision(2) << std::setw(13) << (item.quantitySold * item.priceAtSale)
                              << std::endl;
                }
            } else {
                std::cout << "    No items listed for this sale.\n";
            }
        } else {
            std::cout << "\n  Warning: Sale ID " << saleId << " listed in customer history not found in sales records.\n";
        }
    }

    if (!historyFound && !customerIt->saleIds.empty()) {
         std::cout << "Purchase history IDs found, but corresponding sales details could not be retrieved.\n";
    }
    std::cout << "--------------------------------------------------\n";
}