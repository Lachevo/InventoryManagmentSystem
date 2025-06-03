#include <iostream>
#include <vector>
#include <ctime>
#include "product.h"
#include "supplier.h"
#include "sales_customer.h"
#include "purchase.h"
#include "reporting.h"
#include "admin.h"

int main() {
    // Sample Products
    std::vector<Product> products = {
        {1, "Laptop", "Electronics", 1000.0, 10, ProductStatus::IN_STOCK},
        {2, "Shirt", "Clothing", 25.0, 50, ProductStatus::IN_STOCK}
    };

    // Sample Suppliers
    std::vector<Supplier> suppliers = {
        {1, "TechSupplier", "123-456", {1}},
        {2, "ClothSupplier", "789-012", {2}}
    };

    // Sample Customers
    std::vector<Customer> customers = {
        {1, "Alice", "alice@email.com", {}},
        {2, "Bob", "bob@email.com", {}}
    };

    // Sample Purchase Orders
    std::vector<PurchaseOrder> orders = {
        {1, 1, {1}, {5}, "Completed"},
        {2, 2, {2}, {10}, "Pending"}
    };

    // --- Test Product Search & Delete ---
    Product* foundProduct = searchProduct(1, products);
    if (foundProduct) std::cout << "Found Product: " << foundProduct->name << std::endl;
    deleteProduct(1, products);
    std::cout << "Products after deletion: " << products.size() << std::endl;

    // --- Test Supplier Search & Delete ---
    Supplier* foundSupplier = searchSupplier("TechSupplier", suppliers);
    if (foundSupplier) std::cout << "Found Supplier: " << foundSupplier->name << std::endl;
    deleteSupplier(1, suppliers);
    std::cout << "Suppliers after deletion: " << suppliers.size() << std::endl;

    // --- Test Customer Search & Delete ---
    Customer* foundCustomer = searchCustomerByContact("bob@email.com", customers);
    if (foundCustomer) std::cout << "Found Customer: " << foundCustomer->name << std::endl;
    deleteCustomer(2, customers);
    std::cout << "Customers after deletion: " << customers.size() << std::endl;

    // --- Test Purchase Order Edit & Delete ---
    PurchaseOrder updatedOrder = {2, 2, {2}, {20}, "Completed"};
    editPurchaseOrder(2, updatedOrder, orders);
    deletePurchaseOrder(1, orders);
    std::cout << "Purchase Orders after deletion: " << orders.size() << std::endl;

    // --- Test Reporting ---
    generateProfitLossReport(products, orders);
    showCustomerPurchaseHistory(1, customers, orders);

    // --- Test Admin/User Roles & Activity Logs ---
    setUserRole("admin", UserRole::MANAGER);
    std::cout << "admin role: " << (getUserRole("admin") == UserRole::MANAGER ? "Manager" : "Staff") << std::endl;

    std::vector<ActivityLog> logs;
    logActivity({"Deleted product", "admin", std::time(nullptr)}, logs);
    showActivityLogs(logs);

    return 0;
}