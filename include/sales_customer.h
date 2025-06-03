#ifndef SALES_CUSTOMER_H
#define SALES_CUSTOMER_H

#include <string>
#include <vector>

struct Customer {
    int id;
    std::string name;
    std::string contact;
    std::vector<int> purchaseHistoryIds; // IDs of purchases
};

// Delete a customer by ID
bool deleteCustomer(int customerId, std::vector<Customer>& customers);

// Search customer by ID
Customer* searchCustomer(int customerId, std::vector<Customer>& customers);
// Search customer by name
Customer* searchCustomer(const std::string& name, std::vector<Customer>& customers);
// Search customer by contact
Customer* searchCustomerByContact(const std::string& contact, std::vector<Customer>& customers);

#endif // SALES_CUSTOMER_H
