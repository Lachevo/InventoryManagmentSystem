#include "receive_stock.h"
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

bool receiveStock(int productId, int quantityReceived, std::vector<Product>& products) {
    if (quantityReceived <= 0) {
        std::cerr << "Error: Quantity received must be a positive value. Received: " << quantityReceived << std::endl;
        return false;
    }

    auto it = std::find_if(products.begin(), products.end(),
                           [productId](const Product& p) { return p.id == productId; });

    if (it != products.end()) {
        std::cout << "Receiving stock for Product ID " << productId << " ('" << it->name << "').\n";
        std::cout << "  Current stock: " << it->quantityInStock << ", Status: " << productStatusToString(it->status) << std::endl;

        it->quantityInStock += quantityReceived;
        updateProductStatus(*it);

        std::cout << "  Received " << quantityReceived << " units.\n";
        std::cout << "  New stock: " << it->quantityInStock << ", New Status: " << productStatusToString(it->status) << std::endl;
        std::cout << "Stock received and inventory updated successfully.\n";
        return true;
    } else {
        std::cerr << "Error: Product ID " << productId << " not found. Cannot receive stock.\n";
        return false;
    }
}