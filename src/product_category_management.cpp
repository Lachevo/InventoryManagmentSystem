#include "product_category_management.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>

void loadCategoriesFromFile(std::set<std::string>& availableCategories, const std::string& filePath) {
    availableCategories.clear();
    std::ifstream inFile(filePath);
    if (!inFile) {
        return;
    }
    std::string category;
    while (std::getline(inFile, category)) {
        if (!category.empty()) {
            availableCategories.insert(category);
        }
    }
    inFile.close();
}

void saveCategoriesToFile(const std::set<std::string>& availableCategories, const std::string& filePath) {
    std::ofstream outFile(filePath);
    if (!outFile) {
        std::cerr << "Error: Could not open category file (" << filePath << ") for writing.\n";
        return;
    }
    for (const auto& category : availableCategories) {
        outFile << category << std::endl;
    }
    outFile.close();
}

bool addCategory(const std::string& categoryName, std::set<std::string>& availableCategories, const std::string& categoryFilePath) {
    if (categoryName.empty()) {
        std::cerr << "Error: Category name cannot be empty.\n";
        return false;
    }
    auto result = availableCategories.insert(categoryName);
    if (result.second) {
        std::cout << "Category '" << categoryName << "' added successfully.\n";
        saveCategoriesToFile(availableCategories, categoryFilePath);
        return true;
    } else {
        std::cout << "Info: Category '" << categoryName << "' already exists.\n";
        return false;
    }
}

bool assignProductToCategory(int productId, const std::string& categoryName, std::vector<Product>& products, const std::set<std::string>& availableCategories) {
    if (availableCategories.find(categoryName) == availableCategories.end()) {
        std::cerr << "Error: Category '" << categoryName << "' does not exist. Cannot assign product.\n";
        return false;
    }
    auto it = std::find_if(products.begin(), products.end(),
                           [productId](const Product& p) { return p.id == productId; });
    if (it != products.end()) {
        it->categoryName = categoryName;
        std::cout << "Product ID " << productId << " successfully assigned to category '" << categoryName << "'.\n";
        return true;
    } else {
        std::cerr << "Error: Product ID " << productId << " not found. Cannot assign category.\n";
        return false;
    }
}

void listProductsByCategory(const std::string& categoryName, const std::vector<Product>& products) {
    std::cout << "\n--- Products in Category: " << categoryName << " ---\n";
    bool found = false;
    std::cout << std::left << std::setw(8) << "ID"
              << std::setw(30) << "Name"
              << std::setw(15) << "Price"
              << std::setw(10) << "Stock Qty" << std::endl;
    std::cout << "---------------------------------------------------------------------\n";
    for (const auto& product : products) {
        if (product.categoryName == categoryName) {
            std::cout << std::left
                      << std::setw(8) << product.id
                      << std::setw(30) << product.name
                      << std::fixed << std::setprecision(2) << std::setw(15) << product.price
                      << std::setw(10) << product.quantityInStock << std::endl;
            found = true;
        }
    }
    if (!found) {
        std::cout << "No products currently found in category '" << categoryName << "'.\n";
    }
    std::cout << "---------------------------------------------------------------------\n";
}

void listAllCategories(const std::set<std::string>& availableCategories) {
    std::cout << "\n--- Available Product Categories ---\n";
    if (availableCategories.empty()) {
        std::cout << "No categories defined in the system yet.\n";
    } else {
        int count = 1;
        for (const auto& category : availableCategories) {
            std::cout << count++ << ". " << category << std::endl;
        }
    }
    std::cout << "-----------------------------------\n";
}