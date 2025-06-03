#include "admin.h"
#include <map>
#include <iostream>

static std::map<std::string, UserRole> userRoles;

void setUserRole(const std::string& username, UserRole role) {
    userRoles[username] = role;
}

UserRole getUserRole(const std::string& username) {
    if (userRoles.find(username) != userRoles.end()) {
        return userRoles[username];
    }
    return UserRole::STAFF; // Default role
}

void logActivity(const ActivityLog& log, std::vector<ActivityLog>& logs) {
    logs.push_back(log);
}

void showActivityLogs(const std::vector<ActivityLog>& logs) {
    for (const auto& log : logs) {
        std::cout << "User: " << log.username << ", Action: " << log.action << ", Time: " << log.timestamp << std::endl;
    }
}
