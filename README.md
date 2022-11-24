## Supported platforms

- Windows x64

## Controls

- Press Ctrl + D to toggle various UIs displaying general and debug information of the application.
- Press Ctrl + R to reload the configuration (Debug Build only).

---

### Setting up vcpkg

1. Checkout the `vcpkg` submodule:

```
git submodule update --init
```

2. Ensure it's the latest version

```
cd vcpkg
git checkout 2022.04.12
```

3. Bootstrap it

```
.\bootstrap-vcpkg.bat
```

---

### Creating a debug build

- If you are using Visual Studio, make sure to run the commands in the Developer Prompt.

1. Configure the project:

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Debug
```

2. Build the project:

```sh
cmake --build build --target AvatarCam --config Debug
```

This will produce `AvatarCam.exe` somewhere in the `build` folder.

---

### Creating a release build

- If you are using Visual Studio, make sure to run the commands in the Developer Prompt.

1. Configure the project:

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release
```

2. Build the project:

```sh
cmake --build build --target AvatarCam --config Release
```

3. Install the release build

```sh
cmake --install build --prefix .
```

This will produce a release build in `build-release` folder at the root directory.

---

### Additional DLLs for release build:

- `dwmapi.dll`
- `vcruntime*.dll` and `msvcp*.dll` (Visual Studio only): easiest way is to have the user install the Visual Studio Redistributable for the Visual Studio version.
  - e.g. for Visual Studio 2019 the user can search "Visual Studio 2019 Redistributable" and download x64 and x86 installers.
