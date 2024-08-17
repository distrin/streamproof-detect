#include <iostream>
#include <Windows.h>
#include <dwmapi.h>
#include <TlHelp32.h>
#include <vector>
#include <string>
#include <iomanip>
#include <psapi.h>

#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "psapi.lib")

struct Xzxc {
    DWORD id;
    std::wstring nome;
    bool xor;
};

bool Abc(DWORD id) {
    HWND xyz = nullptr;
    while ((xyz = FindWindowEx(nullptr, xyz, nullptr, nullptr)) != nullptr) {
        DWORD cgh;
        GetWindowThreadProcessId(xyz, &cgh);
        if (cgh == id) {
            DWORD qwe;
            if (GetWindowDisplayAffinity(xyz, &qwe) && qwe == WDA_EXCLUDEFROMCAPTURE) {
                return true;
            }
        }
    }
    return false;
}

std::vector<Xzxc> Def() {
    std::vector<Xzxc> rty;
    HANDLE uio = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    
    if (uio == INVALID_HANDLE_VALUE) {
        std::wcerr << L"Erro ao criar snapshot." << std::endl;
        return rty;
    }

    PROCESSENTRY32W plm{sizeof(PROCESSENTRY32W)};

    if (Process32FirstW(uio, &plm)) {
        do {
            if (Abc(plm.th32ProcessID)) {
                rty.push_back({
                    plm.th32ProcessID,
                    plm.szExeFile,
                    true
                });
            }
        } while (Process32NextW(uio, &plm));
    }

    CloseHandle(uio);
    return rty;
}

void Ghi(const std::vector<Xzxc>& jkl) {
    std::wcout << std::left << std::setw(10) << L"ID" 
               << std::setw(40) << L"Nome" 
               << L"Status" << std::endl;
    std::wcout << std::wstring(60, L'-') << std::endl;

    for (const auto& p : jkl) {
        std::wcout << std::left << std::setw(10) << p.id 
                   << std::setw(40) << p.nome 
                   << L"Protegido" << std::endl;
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleTitle(L"Detector By Murizada");
    std::wcout << L"Analisando processos para detectar...\n\n";

    auto mno = Def();

    if (!mno.empty()) {
        std::wcout << L"\nProcessos com proteção streamproof detectados:\n";
        Ghi(mno);
    } else {
        std::wcout << L"Nenhum processo com proteção streamproof encontrado.\n";
    }

    std::wcout << L"\nPressione qualquer tecla para sair...";
    std::wcin.ignore();
    std::wcin.get();
    return 0;
}