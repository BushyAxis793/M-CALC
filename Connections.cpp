#include "Connections.h"

namespace Connection {

bool Status::GetConnectionStatus() const{
    return isConnection;
}

void Status::SetConnectionStatus(bool isConnect){
    isConnection = isConnect;
}

}
