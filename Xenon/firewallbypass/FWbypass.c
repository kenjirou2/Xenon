#include <windows.h>
#include <netfw.h>
#include <comdef.h>
#include <stdio.h>

#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")

int main() {

    HRESULT hr;

    // Initialize COM
    hr = CoInitializeEx(0, COINIT_APARTMENTTHREADED);
    if (FAILED(hr)) return 1;

    INetFwPolicy2* pPolicy = NULL;
    INetFwRules* pRules = NULL;
    INetFwRule* pRule = NULL;

    // Create firewall policy instance
    hr = CoCreateInstance(
        __uuidof(NetFwPolicy2),
        NULL,
        CLSCTX_INPROC_SERVER,
        __uuidof(INetFwPolicy2),
        (void**)&pPolicy
    );

    if (FAILED(hr)) goto cleanup;

    // Get rules collection
    hr = pPolicy->get_Rules(&pRules);
    if (FAILED(hr)) goto cleanup;

    // Create a rule object
    hr = CoCreateInstance(
        __uuidof(NetFwRule),
        NULL,
        CLSCTX_INPROC_SERVER,
        __uuidof(INetFwRule),
        (void**)&pRule
    );

    if (FAILED(hr)) goto cleanup;

    // Set rule properties
    pRule->put_Name(_bstr_t("windowsxenon"));
    pRule->put_Description(_bstr_t("Allow inbound test traffic"));
    pRule->put_Protocol(NET_FW_IP_PROTOCOL_TCP);
    pRule->put_LocalPorts(_bstr_t("41112"));
    pRule->put_Direction(NET_FW_RULE_DIR_IN);
    pRule->put_Action(NET_FW_ACTION_ALLOW);
    pRule->put_Enabled(VARIANT_TRUE);
    pRule->put_RemoteAddresses(_bstr_t("192.168.1.45"));

    // Add rule to firewall
    hr = pRules->Add(pRule);

    if (SUCCEEDED(hr)) {
        std::cout << "Rule added successfully!\n";
    }
    else {
        std::cout << "Failed to add rule\n";
    }

    cleanup:
        if (pRule) pRule->Release();
        if (pRules) pRules->Release();
        if (pPolicy) pPolicy->Release();
        CoUninitialize();

    return 0;
}