/* date = February 16th 2023 10:24 am */

#ifndef DATABASE_H
#define DATABASE_H

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <list>
#include <iterator>
#include <memory>
#include <mysql.h>

struct Database_Result
{
    MYSQL_RES* Result;
};

class Database
{
    public:
    std::string host;
    unsigned short port;
    std::string user;
    std::string pass;
    std::string db;
    bool connected;
    
    protected:
    struct impl_;
    
    std::unique_ptr<impl_> impl;
    
    public:
    Database();
    ~Database();
    
    bool Connect(const std::string& host, unsigned short port, const std::string& user, const std::string& pass, const std::string& db);
    
    bool ExecuteFile(const char* file);
    Database_Result Query(const char* query);
    
    void Close();
};

#endif