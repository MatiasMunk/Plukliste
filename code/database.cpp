#include "database.h"

#include "util.h"

struct Database::impl_
{
    MYSQL* mysql_handle;
};

Database::Database() : connected(false), impl(new impl_)
{
}

Database::~Database()
{
}

bool Database::Connect(const std::string& host, unsigned short port, const std::string& user, const std::string& pass, const std::string& db)
{
	this->host = host;
	this->user = user;
	this->pass = pass;
	this->port = port;
	this->db = db;
    
    if(this->port == 0) this->port = 3306;
    
    if(this->connected)
        return false;
    
    if ((this->impl->mysql_handle = mysql_init(0)) == 0)
    {
        fprintf(stderr, "unable to initialize connection struct\n");
        return false;
    }
    
    if (mysql_real_connect(this->impl->mysql_handle, host.c_str(), user.c_str(), pass.c_str(), db.c_str(), 3306, 0, 0) != this->impl->mysql_handle)
    {
        fprintf(stderr, "Error connecting to Server: %s\n", mysql_error(this->impl->mysql_handle));
        mysql_close(this->impl->mysql_handle);
        return false;
    }
    
    if (mysql_select_db(this->impl->mysql_handle, db.c_str()) != 0)
    {
        this->Close();
    }
    
    this->connected = true;
    
    printf("Connected to database '%s'\n", db.c_str());
    
    return true;
}

bool Database::ExecuteFile(const char* file)
{
    std::vector<std::string> queries;
    std::string query;
    
    FILE* fh;
    char buf[4096];
    
    fh = fopen(file, "r");
    if (!fh)
    {
        return false;
    }
    
    try
    {
        while (true)
        {
            if (fgets(buf, 4096, fh) != NULL)
            {
                query += buf;
                
                query.erase(query.find('\n'));
            }
        }
    }
    catch (std::exception& e)
    {
        
    }
    fclose(fh);
    
    for (int i = 0; i < Explode(';', query).size(); i++)
    {
        queries.push_back(Explode(';', query).at(i));
    }
    
    for (int i = 0; i < queries.size(); i++)
    {
        if (queries.at(i) != "")
        {
            this->Query(queries.at(i).c_str());
        }
    }
    
    queries.clear();
    query.clear();
    
    return true;
}

Database_Result Database::Query(const char* query)
{
    if (!this->connected)
    {
        //RETURN NO RESULT
    }
    
	std::size_t query_length = std::strlen(query);
    
    Database_Result Res;
    MYSQL_RES* QueryResult = nullptr;
    
    if (mysql_real_query(this->impl->mysql_handle, query, (unsigned long)query_length) != 0)
    {
        printf("Error: %s", mysql_error(this->impl->mysql_handle));
        //RETURN NO RESULT
    }
    
    if((QueryResult = mysql_store_result(this->impl->mysql_handle)) != 0)
    {
        Res.Result = QueryResult;
        if(QueryResult)
        {
            //mysql_free_result(QueryResult);
        }
    }
    
    return Res;
}

void Database::Close()
{
    if (!this->connected)
	{
		return;
	}
    
	this->connected = false;
    
	mysql_close(this->impl->mysql_handle);
}