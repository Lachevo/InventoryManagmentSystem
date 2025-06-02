#include "inventory_report.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <ctime>

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

namespace {
    std::string quoteCsvString(const std::string& s) {
        if (s.find(',') != std::string::npos || s.find('"') != std::string::npos || s.find('\n') != std::string::npos) {
            std::string quoted_s = "\"";
            for (char ch : s) {
                if (ch == '"') {
                    quoted_s += "\"\"";
                } else {
                    quoted_s += ch;
                }
            }
            quoted_s += "\"";
            return quoted_s;
        }
        return s;
    }
}

void generateInventoryReport(const std::vector<Product>& products,
                             bool exportToFile,
                             const std::string& filename) {

    long totalQuantityInStock = 0;
    double totalInventoryValue = 0.0;
    for (const auto& product : products) {
        totalQuantityInStock += product.quantityInStock;
        totalInventoryValue += product.price * product.quantityInStock;
    }
    size_t totalUniqueProducts = products.size();

    std::time_t now_time_t = std::time(nullptr);
    std::tm now_tm = *std::localtime(&now_time_t);

    std::cout << "\n====================================================================================================\n";
    std::cout << "                                     INVENTORY REPORT                                           \n";
    std::cout << "Generated on: " << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S") << "\n";
    std::cout << "====================================================================================================\n";
    std::cout << std::left
              << std::setw(8) << "Prod.ID"
              << std::setw(30) << "Product Name"
              << std::setw(20) << "Category"
              << std::setw(10) << "Price"
              << std::setw(10) << "In Stock"
              << std::setw(15) << "Stock Value"
              << std::setw(15) << "Status" << std::endl;
    std::cout << "----------------------------------------------------------------------------------------------------\n";

    for (const auto& product : products) {
        double stockValue = product.price * product.quantityInStock;
        std::cout << std::left
                  << std::setw(8) << product.id
                  << std::setw(30) << product.name
                  << std::setw(20) << product.categoryName
                  << "$" << std::fixed << std::setprecision(2) << std::setw(8) << product.price
                  << std::setw(10) << product.quantityInStock
                  << "$" << std::fixed << std::setprecision(2) << std::setw(13) << stockValue
                  << std::setw(15) << productStatusToString(product.status) << std::endl;
    }
    std::cout << "----------------------------------------------------------------------------------------------------\n";

    std::cout << "\n--- Inventory Summary ---\n";
    std::cout << std::left << std::setw(35) << "Total Number of Unique Products:" << totalUniqueProducts << std::endl;
    std::cout << std::left << std::setw(35) << "Total Quantity of All Items:" << totalQuantityInStock << std::endl;
    std::cout << std::left << std::setw(35) << "Total Inventory Value:" << "$" << std::fixed << std::setprecision(2) << totalInventoryValue << std::endl;
    std::cout << "====================================================================================================\n";

    if (exportToFile) {
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "Error: Could not open file '" << filename << "' for exporting inventory report.\n";
            return;
        }

        outFile << "ProductID,ProductName,Category,Price,QuantityInStock,StockValue,Status\n";

        for (const auto& product : products) {
            double stockValue = product.price * product.quantityInStock;
            outFile << product.id << ","
                    << quoteCsvString(product.name) << ","
                    << quoteCsvString(product.categoryName) << ","
                    << std::fixed << std::setprecision(2) << product.price << ","
                    << product.quantityInStock << ","
                    << std::fixed << std::setprecision(2) << stockValue << ","
                    << quoteCsvString(productStatusToString(product.status)) << "\n";
        }
        
        outFile << "\n";
        outFile << "Summary Metric,Value\n";
        outFile << quoteCsvString("Total Unique Products") << "," << totalUniqueProducts << "\n";
        outFile << quoteCsvString("Total Quantity of All Items") << "," << totalQuantityInStock << "\n";
        outFile << quoteCsvString("Total Inventory Value") << "," << std::fixed << std::setprecision(2) << totalInventoryValue << "\n";

        outFile.close();
        std::cout << "\nInventory report successfully exported to '" << filename << "'\n";
        std::cout << "====================================================================================================\n";
    }
}