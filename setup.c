#include <windows.h>
#include <shobjidl.h>
#include <objbase.h>
#include <shlguid.h>

HRESULT CreateLink()
{
    HRESULT hres;
    IShellLinkW* psl = NULL;

    hres = CoCreateInstance(
        &CLSID_ShellLink,
        NULL,
        CLSCTX_INPROC_SERVER,
        &IID_IShellLinkW,
        (void**)&psl
    );

    if (SUCCEEDED(hres))
    {
        IPersistFile* ppf = NULL;

        psl->lpVtbl->SetPath(
            psl,
            L"C:\\Users\\zoroj\\OneDrive\\Documents\\Xenon\\xenon\\sXenon\\src\\Xenon.exe"
        );

        psl->lpVtbl->SetDescription(
            psl,
            L"Xenon program shortcut"
        );

        hres = psl->lpVtbl->QueryInterface(
            psl,
            &IID_IPersistFile,
            (void**)&ppf
        );

        if (SUCCEEDED(hres))
        {
            hres = ppf->lpVtbl->Save(
                ppf,
                L"C:\\Users\\zoroj\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Xenon.lnk",
                TRUE
            );

            ppf->lpVtbl->Release(ppf);
        }

        psl->lpVtbl->Release(psl);
    }

    return hres;
}

int main()
{
    CoInitialize(NULL);

    CreateLink();

    CoUninitialize();

    return 0;
}