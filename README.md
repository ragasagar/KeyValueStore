# Key Value Store

## Team Member

1. Sagar Poudel 213051001
2. Vishal Kumar 213050081
3. Divya Kotadiya 20305R003

### Pre requisite
Installation of grpc framework in the system.

### Steps to Execute
1. Download the project and copy the folder in `{grpc_path}/examples/cpp/`
and run
   ```
   $ mkdir -p cmake/build
   $ pushd cmake/build
   $ cmake -DCMAKE_PREFIX_PATH=$MY_INSTALL_DIR ../..
   $ make
   ```
2. To Run the server: 
    ```
   ./server
    ```
3. To Run the client: 
   ```
    ./client
   ```
   

### Config file:
Change the value with proper space.
```
LISTENING_PORT 8081
CACHE_REPLACEMENT_TYPE LRU
CACHE_SIZE 10
THREAD_POOL_SIZE 10
COMPLETION_QUEUE 5
```
