#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <vector>

enum class ProductStatus { IN_STOCK, LOW_STOCK, OUT_OF_STOCK };


struct Product {
    int id;
    std::string name;
    std::string category;
    double price;
    int quantity;
    ProductStatus status;
};
void addProduct(const Product& p);


bool editProduct(int id, const Product& updated);

Product* searchProduct(int id);


Product* searchProduct(const std::string& name);

// Delete a product by ID
bool deleteProduct(int productId, std::vector<Product>& products);

// Search product by ID
Product* searchProduct(int productId, std::vector<Product>& products);
// Search product by name
Product* searchProduct(const std::string& name, std::vector<Product>& products);
// Search product by category
std::vector<Product*> searchProductByCategory(const std::string& category, std::vector<Product>& products);

#endif // PRODUCT_H
