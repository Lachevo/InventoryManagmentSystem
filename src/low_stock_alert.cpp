#include "low_stock_alert.h"
#include <iostream>
#include <string>
#include <vector>

std::string productStatusToString(ProductStatus status) {
    switch (status) {
        case ProductStatus::IN_STOCK:     return "In Stock";
        case ProductStatus::LOW_STOCK:    return "Low Stock";
        case ProductStatus::OUT_OF_STOCK: return "Out of Stock";
        case ProductStatus::UNKNOWN:      return "Unknown";
        default:                          return "Undefined Status";
    }
}

ProductStatus getCalculatedProductStatus(const Product& product) {
    if (product.quantityInStock <= 0) {
        return ProductStatus::OUT_OF_STOCK;
    } else if (product.quantityInStock < product.lowStockThreshold) {
        return ProductStatus::LOW_STOCK;
    } else {
        return ProductStatus::IN_STOCK;
    }
}

void updateProductStatus(Product& product) {
    product.status = getCalculatedProductStatus(product);
}

void generateLowStockAlerts(const std::vector<Product>& products) {
    std::cout << "\n--- Low Stock & Out of Stock Alerts ---\n";
    bool alertsFound = false;

    for (const auto& product : products) {
        if (product.status == ProductStatus::LOW_STOCK) {
            std::cout << "ALERT: LOW STOCK!\n"
                      << "  Product ID: " << product.id << "\n"
                      << "  Name: " << product.name << "\n"
                      << "  Quantity in Stock: " << product.quantityInStock << "\n"
                      << "  Low Stock Threshold: " << product.lowStockThreshold << "\n"
                      << "  Please reorder soon.\n"
                      << "---------------------------------------\n";
            alertsFound = true;
        } else if (product.status == ProductStatus::OUT_OF_STOCK) {
            std::cout << "ALERT: OUT OF STOCK!\n"
                      << "  Product ID: " << product.id << "\n"
                      << "  Name: " << product.name << "\n"
                      << "  Quantity in Stock: 0\n"
                      << "  This product needs immediate restocking.\n"
                      << "---------------------------------------\n";
            alertsFound = true;
        }
    }

    if (!alertsFound) {
        std::cout << "No low stock or out of stock products at the moment. All stock levels are good.\n";
        std::cout << "---------------------------------------\n";
    }
}