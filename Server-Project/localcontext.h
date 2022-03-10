/**
 * Maintain the local context for each client connecting to server.
 */
class LocalContext
{
public:
    int getRpcCount();
    void setRpcCount(int rpcCount);
    void incrementRpcCount();

private:
    int m_RpcCount = 0; // Count of RPCs sent by a client
};

/**
 * @brief Get the number of RPCs
 * 
 * @return int RPC count for the specific client
 */
int LocalContext::getRpcCount()
{
    return m_RpcCount;
}

/**
 * @brief Set the number of RPCs for a specific client.
 * 
 * @param rpcCount 
 */
void LocalContext::setRpcCount(int rpcCount)
{
    m_RpcCount = rpcCount;
}

/**
 * @brief Increment the RPC count for a specific client.
 * 
 */
void LocalContext::incrementRpcCount()
{
    m_RpcCount ++;
}