#ifndef REPORTING_H
#define REPORTING_H

#include <vector>
#include "product.h"
#include "sales_customer.h"
#include "purchase.h"

// Generate profit/loss report
void generateProfitLossReport(const std::vector<Product>& products, const std::vector<PurchaseOrder>& purchases);

// Show customer purchase history
void showCustomerPurchaseHistory(int customerId, const std::vector<Customer>& customers, const std::vector<PurchaseOrder>& purchases);

#endif // REPORTING_H
