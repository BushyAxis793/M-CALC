#ifndef CONNECTIONS_H
#define CONNECTIONS_H



namespace Connection {

class Status{
private:
    bool isConnection = false;
public:
    bool GetConnectionStatus() const;
    void SetConnectionStatus(bool);
};
}

#endif // CONNECTIONS_H
