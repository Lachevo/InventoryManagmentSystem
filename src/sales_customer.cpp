#include "sales_customer.h"

bool deleteCustomer(int customerId, std::vector<Customer>& customers) {
    for (auto it = customers.begin(); it != customers.end(); ++it) {
        if (it->id == customerId) {
            customers.erase(it);
            return true;
        }
    }
    return false;
}

Customer* searchCustomer(int customerId, std::vector<Customer>& customers) {
    for (auto& customer : customers) {
        if (customer.id == customerId) return &customer;
    }
    return nullptr;
}

Customer* searchCustomer(const std::string& name, std::vector<Customer>& customers) {
    for (auto& customer : customers) {
        if (customer.name == name) return &customer;
    }
    return nullptr;
}

Customer* searchCustomerByContact(const std::string& contact, std::vector<Customer>& customers) {
    for (auto& customer : customers) {
        if (customer.contact == contact) return &customer;
    }
    return nullptr;
}
