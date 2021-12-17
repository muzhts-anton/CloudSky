class DataBaseHandler{
    soci::connection_pool* instance_;
    std::size_t size_;
    public:
    std::connection_pool* GetInstance()
    Connect()
    Close()
    Select(std::string&){}
    Insert(std::string&)
    Update(std::string&)
    Delete(std::string&)
}