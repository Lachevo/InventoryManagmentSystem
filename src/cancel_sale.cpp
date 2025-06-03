#include "cancel_sale.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

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

void Sale::calculateTotalPrice() {
    totalPrice = 0.0;
    for (const auto& item : items) {
        totalPrice += item.quantitySold * item.priceAtSale;
    }
}

bool cancelSale(int saleId, std::vector<Sale>& sales, std::vector<Product>& products) {
    auto saleIt = std::find_if(sales.begin(), sales.end(),
                               [saleId](const Sale& s) { return s.saleId == saleId; });

    if (saleIt == sales.end()) {
        std::cerr << "Error: Sale ID " << saleId << " not found. Cannot cancel sale.\n";
        return false;
    }

    if (saleIt->isCancelled) {
        std::cout << "Info: Sale ID " << saleId << " is already cancelled.\n";
        return false;
    }

    std::cout << "Attempting to cancel Sale ID: " << saleIt->saleId << " dated " << saleIt->saleDate << std::endl;

    bool allProductsRestockedWell = true;
    for (const auto& soldItem : saleIt->items) {
        auto productIt = std::find_if(products.begin(), products.end(),
                                      [id = soldItem.productId](const Product& p) { return p.id == id; });

        if (productIt != products.end()) {
            std::cout << "  Restoring " << soldItem.quantitySold << " unit(s) of Product ID "
                      << soldItem.productId << " ('" << productIt->name << "').\n";
            std::cout << "    Old stock: " << productIt->quantityInStock;
            productIt->quantityInStock += soldItem.quantitySold;
            updateProductStatus(*productIt);
            std::cout << ", New stock: " << productIt->quantityInStock
                      << ", New status: " << productStatusToString(productIt->status) << std::endl;
        } else {
            std::cerr << "  Warning: Product ID " << soldItem.productId
                      << " from sale not found in current product list. Cannot restore stock for this item.\n";
            allProductsRestockedWell = false;
        }
    }

    saleIt->isCancelled = true;

    if (allProductsRestockedWell) {
        std::cout << "Sale ID " << saleId << " successfully cancelled. All items restocked where possible.\n";
    } else {
        std::cout << "Sale ID " << saleId << " marked as cancelled. Some items could not be restocked due to missing product IDs.\n";
    }
    return true;
}