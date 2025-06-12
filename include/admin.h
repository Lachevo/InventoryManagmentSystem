#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <vector>
#include <ctime>

enum class UserRole { MANAGER, STAFF };

struct ActivityLog {
    std::string action;
    std::string username;
    std::time_t timestamp;
};
bool authenticateAdmin(const std::string& username, const std::string& password);

// Set user role
void setUserRole(const std::string& username, UserRole role);
// Get user role
UserRole getUserRole(const std::string& username);
// Log admin activity
void logActivity(const ActivityLog& log, std::vector<ActivityLog>& logs);
// Show activity logs
void showActivityLogs(const std::vector<ActivityLog>& logs);

#endif // ADMIN_H
