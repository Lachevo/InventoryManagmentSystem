#include "product.h"

bool deleteProduct(int productId, std::vector<Product>& products) {
    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->id == productId) {
            products.erase(it);
            return true;
        }
    }
    return false;
}

Product* searchProduct(int productId, std::vector<Product>& products) {
    for (auto& product : products) {
        if (product.id == productId) return &product;
    }
    return nullptr;
}

Product* searchProduct(const std::string& name, std::vector<Product>& products) {
    for (auto& product : products) {
        if (product.name == name) return &product;
    }
    return nullptr;
}

std::vector<Product*> searchProductByCategory(const std::string& category, std::vector<Product>& products) {
    std::vector<Product*> result;
    for (auto& product : products) {
        if (product.category == category) result.push_back(&product);
    }
    return result;
}
