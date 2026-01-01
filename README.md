## CPP Logging Library

---

Barely Working

#### OS support
- Linux
- macOS
(not Windows primarily cause of POSIX sockets used in network sink)

#### Current Features
- Levels Of Logs
- Source Of Logs 
- Async write (with async writer thread)
- Multiple sinks for logs (console, files, network(over UDP))

#### Build
Run ./compile.sh

OR

````
mkdir -p build
cd build
cmake ..
cmake --build .
````

#### Future Features 
- Adjustable format 
- Windows support

