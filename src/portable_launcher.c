#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

#define PAYLOAD_RES_ID 100

#ifndef NIMUH_VERSION_STR
#error "NIMUH_VERSION_STR must be defined at compile time"
#endif

#ifndef NIMUH_ARCH_STR
#if defined(_WIN64) || defined(__x86_64__)
#define NIMUH_ARCH_STR "x64"
#else
#define NIMUH_ARCH_STR "x86"
#endif
#endif

static void create_parent_dirs(char* filepath) {
    char* p = filepath;
    while (*p) {
        if (*p == '/' || *p == '\\') {
            char c = *p;
            *p = '\0';
            CreateDirectoryA(filepath, NULL);
            *p = c;
        }
        p++;
    }
}

static int extract_tar_gz(const char* gz_path, const char* dest_dir) {
    gzFile gz = gzopen(gz_path, "rb");
    if (!gz) return 0;

    char header[512];
    char long_name[MAX_PATH] = { 0 };

    while (gzread(gz, header, 512) == 512) {
        if (header[0] == '\0') break;

        char type = header[156];
        char size_buf[13];
        strncpy(size_buf, header + 124, 12);
        size_buf[12] = '\0';
        long long size = strtoll(size_buf, NULL, 8);

        if (type == 'L') {
            int to_read = (int)(((size + 511) / 512) * 512);
            char* buf = (char*)malloc(to_read);
            if (buf) {
                gzread(gz, buf, to_read);
                size_t cpy = size < (MAX_PATH - 1) ? size : (MAX_PATH - 1);
                strncpy(long_name, buf, cpy);
                long_name[cpy] = '\0';
                free(buf);
            }
            continue;
        }

        char name[MAX_PATH];
        if (long_name[0] != '\0') {
            strncpy(name, long_name, MAX_PATH - 1);
            name[MAX_PATH - 1] = '\0';
            long_name[0] = '\0';
        } else {
            strncpy(name, header, 99);
            name[99] = '\0';
        }

        // Skip leading ./ or /
        char* rel_name = name;
        if (rel_name[0] == '.' && (rel_name[1] == '/' || rel_name[1] == '\\')) {
            rel_name += 2;
        }
        while (*rel_name == '/' || *rel_name == '\\') {
            rel_name++;
        }
        if (*rel_name == '\0') continue;

        char fullpath[MAX_PATH];
        snprintf(fullpath, sizeof(fullpath), "%s\\%s", dest_dir, rel_name);
        for (char* p = fullpath; *p; p++) {
            if (*p == '/') *p = '\\';
        }

        if (type == '5') {
            create_parent_dirs(fullpath);
            CreateDirectoryA(fullpath, NULL);
        } else if (type == '0' || type == '\0') {
            create_parent_dirs(fullpath);
            FILE* out = fopen(fullpath, "wb");
            if (out) {
                char buf[16384];
                long long remaining = size;
                while (remaining > 0) {
                    int to_read = remaining > sizeof(buf) ? sizeof(buf) : (int)remaining;
                    int read_bytes = gzread(gz, buf, to_read);
                    if (read_bytes <= 0) break;
                    fwrite(buf, 1, read_bytes, out);
                    remaining -= read_bytes;
                }
                fclose(out);
            }
            int pad = (int)((512 - (size % 512)) % 512);
            if (pad > 0) {
                char dummy[512];
                gzread(gz, dummy, pad);
            }
        } else {
            int pad = (int)((512 - (size % 512)) % 512);
            if (pad > 0) {
                char dummy[512];
                gzread(gz, dummy, pad);
            }
        }
    }

    gzclose(gz);
    return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    char tempPath[MAX_PATH];
    char targetDir[MAX_PATH];
    char exePath[MAX_PATH];

    if (GetTempPathA(MAX_PATH, tempPath) == 0) {
        MessageBoxA(NULL, "No se pudo obtener el directorio temporal.", "Nimuh", MB_ICONERROR);
        return 1;
    }

    snprintf(targetDir, sizeof(targetDir), "%snimuh-%s-%s", tempPath, NIMUH_VERSION_STR, NIMUH_ARCH_STR);
    snprintf(exePath, sizeof(exePath), "%s\\nimuh.exe", targetDir);

    if (GetFileAttributesA(exePath) == INVALID_FILE_ATTRIBUTES) {
        CreateDirectoryA(targetDir, NULL);

        HRSRC hRes = FindResourceA(NULL, MAKEINTRESOURCEA(PAYLOAD_RES_ID), RT_RCDATA);
        if (!hRes) {
            MessageBoxA(NULL, "No se encontró el recurso de datos del juego.", "Nimuh", MB_ICONERROR);
            return 1;
        }

        HGLOBAL hMem = LoadResource(NULL, hRes);
        DWORD resSize = SizeofResource(NULL, hRes);
        void* pData = LockResource(hMem);

        char gzTempPath[MAX_PATH];
        snprintf(gzTempPath, sizeof(gzTempPath), "%s\\nimuh_payload.tar.gz", targetDir);

        FILE* fp = fopen(gzTempPath, "wb");
        if (!fp) {
            MessageBoxA(NULL, "No se pudo escribir el archivo temporal de extracción.", "Nimuh", MB_ICONERROR);
            return 1;
        }
        fwrite(pData, 1, resSize, fp);
        fclose(fp);

        if (!extract_tar_gz(gzTempPath, targetDir)) {
            MessageBoxA(NULL, "Error al descomprimir los archivos del juego.", "Nimuh", MB_ICONERROR);
            DeleteFileA(gzTempPath);
            return 1;
        }
        DeleteFileA(gzTempPath);
    }

    char cmd[MAX_PATH * 3];
    snprintf(cmd, sizeof(cmd), "\"%s\" %s", exePath, lpCmdLine ? lpCmdLine : "");

    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_SHOWNORMAL;

    if (!CreateProcessA(NULL, cmd, NULL, NULL, FALSE, 0, NULL, targetDir, &si, &pi)) {
        MessageBoxA(NULL, "No se pudo ejecutar nimuh.exe.", "Nimuh", MB_ICONERROR);
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    DWORD exitCode = 0;
    GetExitCodeProcess(pi.hProcess, &exitCode);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return (int)exitCode;
}
