#ifndef CUSTOMER_PURCHASE_HISTORY_H
#define CUSTOMER_PURCHASE_HISTORY_H

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

struct SoldItem {
    int productId;
    int quantitySold;
    double priceAtSale;

    SoldItem(int pid = 0, int qty = 0, double pas = 0.0)
        : productId(pid), quantitySold(qty), priceAtSale(pas) {}
};

struct Sale {
    int saleId;
    int customerId;
    std::vector<SoldItem> items;
    double totalPrice;
    std::string saleDate;
    bool isCancelled;

    Sale(int sid = 0, int custId = 0, const std::string& date = "")
        : saleId(sid), customerId(custId), saleDate(date), totalPrice(0.0), isCancelled(false) {}

    void calculateTotalPrice();
};

struct Customer {
    int customerId;
    std::string name;
    std::string contactDetails;
    std::vector<int> saleIds;

    Customer(int id = 0, const std::string& n = "", const std::string& contact = "")
        : customerId(id), name(n), contactDetails(contact) {}
};

void viewCustomerPurchaseHistory(int customerId,
                                 const std::vector<Customer>& customers,
                                 const std::vector<Sale>& allSales,
                                 const std::vector<Product>& allProducts);

#endif // CUSTOMER_PURCHASE_HISTORY_H