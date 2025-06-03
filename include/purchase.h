#ifndef PURCHASE_H
#define PURCHASE_H

#include <string>
#include <vector>

struct PurchaseOrder {
    int id;
    int supplierId;
    std::vector<int> productIds;
    std::vector<int> quantities;
    std::string status;
};

// Edit a purchase order by ID
bool editPurchaseOrder(int orderId, const PurchaseOrder& updatedOrder, std::vector<PurchaseOrder>& orders);
// Delete a purchase order by ID
bool deletePurchaseOrder(int orderId, std::vector<PurchaseOrder>& orders);
// Search purchase order by ID
PurchaseOrder* searchPurchaseOrder(int orderId, std::vector<PurchaseOrder>& orders);
// Search purchase order by supplier ID
std::vector<PurchaseOrder*> searchPurchaseOrderBySupplier(int supplierId, std::vector<PurchaseOrder>& orders);

#endif // PURCHASE_H
