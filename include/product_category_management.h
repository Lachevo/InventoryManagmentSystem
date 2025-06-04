#ifndef PRODUCT_CATEGORY_MANAGEMENT_H
#define PRODUCT_CATEGORY_MANAGEMENT_H

#include <string>
#include <vector>
#include <set>

struct Product {
    int id;
    std::string name;
    std::string categoryName;
    double price;
    int quantityInStock;

    Product(int i = 0, const std::string& n = "", const std::string& cat = "", double p = 0.0, int q = 0)
        : id(i), name(n), categoryName(cat), price(p), quantityInStock(q) {}
};

void loadCategoriesFromFile(std::set<std::string>& availableCategories, const std::string& filePath);
void saveCategoriesToFile(const std::set<std::string>& availableCategories, const std::string& filePath);
bool addCategory(const std::string& categoryName, std::set<std::string>& availableCategories, const std::string& categoryFilePath);
bool assignProductToCategory(int productId, const std::string& categoryName, std::vector<Product>& products, const std::set<std::string>& availableCategories);
void listProductsByCategory(const std::string& categoryName, const std::vector<Product>& products);
void listAllCategories(const std::set<std::string>& availableCategories);

#endif // PRODUCT_CATEGORY_MANAGEMENT_H