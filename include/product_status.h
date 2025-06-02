#ifndef PRODUCT_STATUS_H
#define PRODUCT_STATUS_H

#include <string>
#include <vector>

enum class ProductStatus {
    IN_STOCK,
    LOW_STOCK,
    OUT_OF_STOCK,
    UNKNOWN
};

struct Product {
    int id;
    std::string name;
    std::string categoryName;
    double price;
    int quantityInStock;
    ProductStatus status;
    int lowStockThreshold;

    Product(int i = 0, const std::string& n = "", const std::string& cat = "", double p = 0.0, int q = 0, int threshold = 10)
        : id(i), name(n), categoryName(cat), price(p), quantityInStock(q),
          status(ProductStatus::UNKNOWN), lowStockThreshold(threshold) {}
};

std::string productStatusToString(ProductStatus status);
ProductStatus getCalculatedProductStatus(const Product& product);
void updateProductStatus(Product& product);
void displayProductStatus(int productId, const std::vector<Product>& products);

#endif // PRODUCT_STATUS_H