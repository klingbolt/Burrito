#define WIN32_LEAN_AND_MEAN
#include <d3d11.h>
#include <stdint.h>
#include <stdio.h>
#include <windows.h>

// Forward declare the run_link() function defined in burrito_link.c
void run_link();
void end_process();

#ifndef true
#define true TRUE
#endif

#ifndef false
#define false FALSE
#endif

#ifndef nullptr
#define nullptr 0
#endif

////////////////////////////////////////////////////////////////////////////////
// GetOriginalD3D11Module
//
// This loads the original d3d11.dll file so that we can pass the function
// calls made to this library into that library as if they were implemented in
// this library.
////////////////////////////////////////////////////////////////////////////////
HMODULE D3D11Library = nullptr;
HMODULE GetOriginalD3D11Module() {
    // If we have already loaded the library into this process return the
    // pointer to it instead of loading it a second time.
    if (!D3D11Library) {
        char infoBuf[4096];
        GetSystemDirectory(infoBuf, 4096);
        lstrcat(infoBuf, "\\d3d11.dll");

        // Load this library and track it. We don't want to use GetModuleHandle
        // here because GetModuleHandle does not increment the internal
        // reference count meaning that FreeLibrary would incorrectly decrement
        // it when we unload.
        D3D11Library = LoadLibrary(infoBuf);
    }

    return D3D11Library;
}

////////////////////////////////////////////////////////////////////////////////
// FreeD3D11Module
//
// This frees the original d3d11.dll file so that this process no longer is
// using it.
////////////////////////////////////////////////////////////////////////////////
void FreeD3D11Module() {
    if (D3D11Library) {
        FreeLibrary(D3D11Library);
    }
}

////////////////////////////////////////////////////////////////////////////////
// D3D11CreateDeviceAndSwapChainOriginal
//
// A pointer to a function that looks like D3D11CreateDeviceAndSwapChain()
////////////////////////////////////////////////////////////////////////////////
typedef HRESULT(WINAPI* D3D11CreateDeviceAndSwapChainFunc)(
    IDXGIAdapter* pAdapter,
    D3D_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    const D3D_FEATURE_LEVEL* pFeatureLevels,
    UINT FeatureLevels,
    UINT SDKVersion,
    const DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
    IDXGISwapChain** ppSwapChain,
    ID3D11Device** ppDevice,
    D3D_FEATURE_LEVEL* pFeatureLevel,
    ID3D11DeviceContext** ppImmediateContext
);
D3D11CreateDeviceAndSwapChainFunc D3D11CreateDeviceAndSwapChainOriginal = nullptr;

////////////////////////////////////////////////////////////////////////////////
// D3D11CreateDeviceAndSwapChain
//
// A proxy function that calls the original d3d11.dll's
// D3D11CreateDeviceAndSwapChain function, then returns the result.
////////////////////////////////////////////////////////////////////////////////
extern HRESULT WINAPI D3D11CreateDeviceAndSwapChain(
    IDXGIAdapter* pAdapter,
    D3D_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    const D3D_FEATURE_LEVEL* pFeatureLevels,
    UINT FeatureLevels,
    UINT SDKVersion,
    const DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
    IDXGISwapChain** ppSwapChain,
    ID3D11Device** ppDevice,
    D3D_FEATURE_LEVEL* pFeatureLevel,
    ID3D11DeviceContext** ppImmediateContext
) {
    printf("FUNCTION: D3D11CreateDeviceAndSwapChain\n");
    fflush(stdout);
    // Get the function address if we don't have it yet.
    if (!D3D11CreateDeviceAndSwapChainOriginal) {
        HMODULE original_d3d11 = GetOriginalD3D11Module();
        D3D11CreateDeviceAndSwapChainOriginal = (D3D11CreateDeviceAndSwapChainFunc)GetProcAddress(original_d3d11, "D3D11CreateDeviceAndSwapChain");
    }

    return D3D11CreateDeviceAndSwapChainOriginal(
        pAdapter,
        DriverType,
        Software,
        Flags,
        pFeatureLevels,
        FeatureLevels,
        SDKVersion,
        pSwapChainDesc,
        ppSwapChain,
        ppDevice,
        pFeatureLevel,
        ppImmediateContext
    );
}

////////////////////////////////////////////////////////////////////////////////
// D3D11CreateDeviceOriginal
//
// A pointer to a function that looks like D3D11CreateDevice()
////////////////////////////////////////////////////////////////////////////////
typedef HRESULT(WINAPI* D3D11CreateDeviceFunc)(
    IDXGIAdapter* pAdapter,
    D3D_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    const D3D_FEATURE_LEVEL* pFeatureLevels,
    UINT FeatureLevels,
    UINT SDKVersion,
    ID3D11Device** ppDevice,
    D3D_FEATURE_LEVEL* pFeatureLevel,
    ID3D11DeviceContext** ppImmediateContext
);
D3D11CreateDeviceFunc D3D11CreateDeviceOriginal = nullptr;

////////////////////////////////////////////////////////////////////////////////
// D3D11CreateDevice
//
// A proxy function that call the original d3d11.dll's D3D11CreateDevice
// function, then returns the result.
////////////////////////////////////////////////////////////////////////////////
extern HRESULT WINAPI D3D11CreateDevice(
    IDXGIAdapter* pAdapter,
    D3D_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    const D3D_FEATURE_LEVEL* pFeatureLevels,
    UINT FeatureLevels,
    UINT SDKVersion,
    ID3D11Device** ppDevice,
    D3D_FEATURE_LEVEL* pFeatureLevel,
    ID3D11DeviceContext** ppImmediateContext
) {
    printf("FUNCTION: D3D11CreateDevice\n");
    fflush(stdout);
    // Get the function address if we don't have it yet.
    if (!D3D11CreateDeviceOriginal) {
        HMODULE original_d3d11 = GetOriginalD3D11Module();
        D3D11CreateDeviceOriginal = (D3D11CreateDeviceFunc)GetProcAddress(original_d3d11, "D3D11CreateDevice");
    }

    return D3D11CreateDeviceOriginal(
        pAdapter,
        DriverType,
        Software,
        Flags,
        pFeatureLevels,
        FeatureLevels,
        SDKVersion,
        ppDevice,
        pFeatureLevel,
        ppImmediateContext
    );
}

////////////////////////////////////////////////////////////////////////////////
// D3D11CoreCreateDeviceOriginal
//
// A pointer to a function that looks like D3D11CoreCreateDevice()
////////////////////////////////////////////////////////////////////////////////
typedef HRESULT(WINAPI* D3D11CoreCreateDeviceFunc)(
    IDXGIFactory* pFactory,
    IDXGIAdapter* pAdapter,
    UINT Flags,
    const D3D_FEATURE_LEVEL* pFeatureLevels,
    UINT FeatureLevels,
    ID3D11Device** ppDevice
);
D3D11CoreCreateDeviceFunc D3D11CoreCreateDeviceOriginal = nullptr;

////////////////////////////////////////////////////////////////////////////////
// D3D11CoreCreateDevice
//
// A proxy function that call the original d3d11.dll's D3D11CoreCreateDevice
// function, then returns the result.
////////////////////////////////////////////////////////////////////////////////
extern HRESULT WINAPI D3D11CoreCreateDevice(
    IDXGIFactory* pFactory,
    IDXGIAdapter* pAdapter,
    UINT Flags,
    const D3D_FEATURE_LEVEL* pFeatureLevels,
    UINT FeatureLevels,
    ID3D11Device** ppDevice
) {
    printf("FUNCTION: D3D11CoreCreateDevice\n");
    fflush(stdout);
    // Get the function address if we don't have it yet.
    if (!D3D11CoreCreateDeviceOriginal) {
        HMODULE original_d3d11 = GetOriginalD3D11Module();
        D3D11CoreCreateDeviceOriginal = (D3D11CoreCreateDeviceFunc)GetProcAddress(original_d3d11, "D3D11CoreCreateDevice");
    }

    return D3D11CoreCreateDeviceOriginal(
        pFactory,
        pAdapter,
        Flags,
        pFeatureLevels,
        FeatureLevels,
        ppDevice
    );
}

////////////////////////////////////////////////////////////////////////////////
// BurritoLinkThread
//
// A helper function that calls the burrito link run_link() function. It exists
// so that it can be passed into the Windows API CreateThread and can be run
// within a the new thread instead of the DLL's main thread.
////////////////////////////////////////////////////////////////////////////////
void WINAPI BurritoLinkThread() {
    run_link();
    return;
}

////////////////////////////////////////////////////////////////////////////////
// start_burrito_link_thread
//
// Creates a new burrito link thread if there is no existing burrito link
// thread running.
////////////////////////////////////////////////////////////////////////////////
HANDLE burrito_link_thread_handle = nullptr;
void start_burrito_link_thread() {
    if (burrito_link_thread_handle != nullptr) {
        return;
    }

    burrito_link_thread_handle = CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)BurritoLinkThread,
        NULL,
        0,
        NULL
    );

    if (burrito_link_thread_handle == nullptr) {
        // Failed to create the thread.
        printf("Failed to create burrito link thread");
    }
}

////////////////////////////////////////////////////////////////////////////////
// stop_burrito_link_thread
//
// Kills a burrito link thread if there is a burrito link thread running. This
// is necessary to avoid an error message on exit.
////////////////////////////////////////////////////////////////////////////////
void stop_burrito_link_thread() {
    if (burrito_link_thread_handle != nullptr) {
        end_process();
    }
}

////////////////////////////////////////////////////////////////////////////////
// DllMain
//
// DllMain is the entry point called when this dll is loaded. We use this
// function to spawn the background threads for burrito_link.
//
// The windows documentation says not to create threads inside of DllMain
// because of two reasons:
//   1) If you wait on the thread you will cause a deadlock.
//   2) Anybody who loads a DLL files would not expect purely loading the file
//      to do business logic.
// The first reason is relevant to us, we must make sure to not ever wait on
// the thread or else we will cause a deadlock. The second reason is irrelevant
// as this behavior is the exact unexpected behavior we are trying to take
// advantage of in order to inject our code into the running process. Thus it
// is safe and a good idea to call CreateThread in DllMain.
////////////////////////////////////////////////////////////////////////////////
BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to the DLL module
    DWORD fdwReason,  // reason for calling DllMain
    LPVOID lpvReserved  // Reserved
) {
    // Perform actions based on the reason for calling.
    switch (fdwReason) {
        // Do process initialization. Return false if initialization fails.
        case DLL_PROCESS_ATTACH:
            printf("DLL_PROCESS_ATTACH\n");
            start_burrito_link_thread();
            break;

        // Do thread-specific initialization.
        case DLL_THREAD_ATTACH:
            break;

        // Do thread-specific cleanup.
        case DLL_THREAD_DETACH:
            break;

        // Do process cleanup
        case DLL_PROCESS_DETACH:
            // Skip cleanup if process termination scenario
            if (lpvReserved != nullptr) {
                printf("DLL_PROCESS_DETACH no cleanup\n");
                break;
            }
            printf("DLL_PROCESS_DETACH\n");
            stop_burrito_link_thread();

            // Cleanup process
            FreeD3D11Module();
            break;
    }
    fflush(stdout);

    return true;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////// Arcdps Entrypoints //////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// arcdps_exports
//
// The Arcdps linked library metadata struct that contains information about
// this linked library.
// TODO: Rename this ArcdpsExports and have it initizlie the singleton itself
// instead of creating a typedef of it to be used later. See the raidcore nexus
// section as an example.
////////////////////////////////////////////////////////////////////////////////
#ifndef ImGuiContext
#define ImGuiContext void
#endif
typedef struct arcdps_exports {
    uintptr_t size;
    uint32_t sig;
    uint32_t imguivers;
    const char* out_name;
    const char* out_build;
    void* wnd_nofilter;
    void* combat;
    void* imgui;
    void* options_end;
    void* combat_local;
    void* wnd_filter;
    void* options_windows;
} arcdps_exports;
arcdps_exports arc_exports;

////////////////////////////////////////////////////////////////////////////////
// mod_init
//
// This function is called by arcdps when it loads this linked library. The
// address of this function is returned by get_init_adder() which is how arcdps
// knows to call it.
////////////////////////////////////////////////////////////////////////////////
arcdps_exports* mod_init() {
    memset(&arc_exports, 0, sizeof(arcdps_exports));
    arc_exports.sig = 0xFFFA;
    arc_exports.size = sizeof(arcdps_exports);
    arc_exports.out_name = "BurritoLink";
    arc_exports.out_build = "1.0";
    return &arc_exports;
}

////////////////////////////////////////////////////////////////////////////////
// get_init_addr
//
// One of the two required functions to be exposed for arcdps to load this
// linked library as an addon. It returns a pointer to the function that should
// be calle when the addon is loaded.
////////////////////////////////////////////////////////////////////////////////
extern __declspec(dllexport) void* get_init_addr(
    char* arcversion,
    ImGuiContext* imguictx,
    void* id3dptr,
    HANDLE arcdll,
    void* mallocfn,
    void* freefn,
    uint32_t d3dversion
) {
    return mod_init;
}

////////////////////////////////////////////////////////////////////////////////
// mod_release
//
// This function is called by acdps when it unloads this linked library. The
// address of this function is returned by get_release_addr() which is how
// arcdps knows to call it.
////////////////////////////////////////////////////////////////////////////////
uintptr_t mod_release() {
    FreeConsole();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
// get_release_addr
//
// One of the two required functions to be exposed for arcdps to load this
// linked library as an addon. It returns a pointer to the function that should
// be called when the addon is unloaded.
////////////////////////////////////////////////////////////////////////////////
extern __declspec(dllexport) void* get_release_addr() {
    return mod_release;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////// Raidcore Nexus Entrypoints //////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// AddonDefinition
//
// The Raidcore Nexus addon definition struct that contains information about
// this linked library which nexus is able to read.
////////////////////////////////////////////////////////////////////////////////
struct AddonDefinition {
    // Required for nexus

    // Raidcore Addon ID, set to random unqiue negative integer if not on Raidcore
    int32_t Signature;

    // Determines which AddonAPI struct revision the Loader will pass, use the NEXUS_API_VERSION define from Nexus.h
    int32_t APIVersion;

    // Name of the addon as shown in the library
    const char* Name;

    // Vesion number of the addon
    struct AddonVersion {
        int16_t Major;
        int16_t Minor;
        int16_t Build;
        int16_t Revision;
    } Version;

    // Author of the addon
    const char* Author;

    // Short description
    const char* Description;

    // Pointer to Load Function of the addon
    void* Load;

    // Pointer to Unload Function of the addon. Not required if EAddonFlags::DisableHotloading is set.
    void* Unload;

    // Information about the addon
    int32_t Flags;

    // Update fallback
    // What platform is the the addon hosted on
    int32_t Provider;

    // Link to the update resource
    const char* UpdateLink;
} AddonDef;

////////////////////////////////////////////////////////////////////////////////
// GetAddonDef()
//
// This function is used to communicate with Nexus and allow the linked library
// to be loaded by nexus.
////////////////////////////////////////////////////////////////////////////////
extern __declspec(dllexport) struct AddonDefinition* GetAddonDef() {
    AddonDef.Signature = -1032686481;
    AddonDef.APIVersion = 6;  // taken from Nexus.h
    AddonDef.Name = "Burrito Link";
    AddonDef.Version.Major = 0;
    AddonDef.Version.Minor = 0;
    AddonDef.Version.Build = 0;
    AddonDef.Version.Revision = 1;
    AddonDef.Author = "AsherGlick";
    AddonDef.Description = "Automatically provides the link for Burrito.";
    AddonDef.Load = start_burrito_link_thread;
    AddonDef.Unload = stop_burrito_link_thread;
    AddonDef.Flags = 0;

    return &AddonDef;
}
