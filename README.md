# Simple RND OpenSSL Engine

The purpose is to demonstrate how to create a custom OpenSSL engine. **srndengine** is a primitive random number generator.

The code has been built and tested on Windows and Linux using MS Visual Studio 2019 and gcc 9.3.0 on Ubuntu 20.04

## Linux (Ubuntu-20.04)

To build the code:

```bash
mkdir -p build/x86_x64_linux
cd build/x86_x64_linux
cmake ../..
make
sudo make install
```

> The engine is installed into the default folder for OpenSSL user engines */usr/lib/x86_64-linux-gnu/engines-1.1*. If you don't want to install it then you can create a link to so file.

## Windows (MS Visual Studio 2019)

To create Microsoft Visual Studio solution and project files, and build the solution from PowerShell or CMD:

```powershell
mkdir -p build/msvs
cd build/msvs
cmake ../..
cmake --build .
```

> You can build it from PowerShell or open the Visual Studio solution file **srndengine.sln** and build it from the IDE.

**Note:** When debugging it might happen that a breakpoint inside the DLL is not hit. Then make sure that the engine project **srndengine** has **Yes (/ASSEMBLYDEBUG)** in the following settings: *properties->Linker->Debugging->Debuggable Assembly*.
{: .note}

## Run

The **srndengine** engine can be utilized in two ways. One through OpenSSL tool and another using our own **srndtool** tool, which shows how to use a custom engine in C program.

### Openssl

> The engine needs to be installed first into */usr/lib/x86_64-linux-gnu/engines-1.1* otherwise OpenSSL won't be able to find it.

To load the engine and to discover its capabilities run:

```bash
    openssl engine -t -c srndengine

    (srndengine) Simple RND OpenSSL Engine
     [RAND]
         [ available ]
```

To generate 32 bytes of random numbers using **srndengine** run:

```bash
    openssl rand -hex -engine srndengine 32

    engine "srndengine" set.
    srndengine:
    00000000  0d cb 46 ac 6a 3f 6e 16  bb 96 80 ca 82 5c 44 cc  |..F.j?n......\D.|
    00000010  7b 87 ec b8 85 3b ca 47  2e 92 25 91 b1 e3 e2 be  |{....;.G..%.....|
    0dcb46ac6a3f6e16bb9680ca825c44cc7b87ecb8853bca472e922591b1e3e2be
```

### Linux

To run the **srndtool** tool:

```bash
    ./app/srndtool/srndtool

    SSL Engine: Simple RND OpenSSL Engine
    srndengine:
    00000000  51 60 22 91 9b 10 ad 89  68 9b 01 9f 7e b2 be 8e  |Q`".....h...~...|
    00000010  f4 df c7 86 28 03 28 42  39 9e 23 33 a1 f4 92 f3  |....(.(B9.#3....|
    RAND_bytes: 516022919b10ad89689b19f7eb2be8ef4dfc7862832842399e2333a1f492f3
```

### Windows

To run the **srndtool** tool:

```powershell
    .\app\srndtool\Debug\srndtool.exe

    SSL Engine: Simple RND OpenSSL Engine
    srndengine:
    00000000  8f e5 e6 05 b1 44 ba f7  d4 33 1f 73 a0 4f 8e 1d  |.....D...3.s.O..|
    00000010  f9 77 ba ee c9 80 73 85  00 2a ca be d9 53 76 86  |.w....s..*...Sv.|
    RAND_bytes: 8fe5e65b144baf7d4331f73a04f8e1df977baeec980738502acabed9537686
```
