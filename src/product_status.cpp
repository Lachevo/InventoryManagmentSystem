#include "product_status.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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

void displayProductStatus(int productId, const std::vector<Product>& products) {
    auto it = std::find_if(products.begin(), products.end(),
                           [productId](const Product& p) { return p.id == productId; });

    if (it != products.end()) {
        std::cout << "Status for Product ID " << productId << " ('" << it->name << "'): "
                  << productStatusToString(it->status)
                  << " (Quantity: " << it->quantityInStock
                  << ", Threshold: " << it->lowStockThreshold << ")\n";
    } else {
        std::cerr << "Error: Product ID " << productId << " not found for displaying status.\n";
    }
}