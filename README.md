# Key Value Store

## Team Member

1. Sagar Poudel
2. Vishal Kumar
3. Divya

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
