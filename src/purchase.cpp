#include "purchase.h"

bool editPurchaseOrder(int orderId, const PurchaseOrder& updatedOrder, std::vector<PurchaseOrder>& orders) {
    for (auto& order : orders) {
        if (order.id == orderId) {
            order = updatedOrder;
            return true;
        }
    }
    return false;
}
void processPurchaseOrder(const PurchaseOrder& order) {
    purchaseOrders.push_back(order);
    std::cout << "Purchase order processed successfully.\n";
}

bool deletePurchaseOrder(int orderId, std::vector<PurchaseOrder>& orders) {
    for (auto it = orders.begin(); it != orders.end(); ++it) {
        if (it->id == orderId) {
            orders.erase(it);
            return true;
        }
    }
    return false;
}

PurchaseOrder* searchPurchaseOrder(int orderId, std::vector<PurchaseOrder>& orders) {
    for (auto& order : orders) {
        if (order.id == orderId) return &order;
    }
    return nullptr;
}

std::vector<PurchaseOrder*> searchPurchaseOrderBySupplier(int supplierId, std::vector<PurchaseOrder>& orders) {
    std::vector<PurchaseOrder*> result;
    for (auto& order : orders) {
        if (order.supplierId == supplierId) result.push_back(&order);
    }
    return result;
}
