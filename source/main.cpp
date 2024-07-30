#include <fpdfview.h>
#include <string>
#include <vector>
#include <emscripten.h>

// ʹ�� EMSCRIPTEN_KEEPALIVE ȷ�����������յ� WebAssembly �п���
EMSCRIPTEN_KEEPALIVE
extern "C" const char* readPDF(const char* pdfPath) {
    FPDF_LIBRARY_CONFIG config;
    config.version = 2;
    config.m_pUserFontPaths = nullptr;
    config.m_pIsolate = nullptr;
    config.m_v8EmbedderSlot = 0;

    FPDF_InitLibraryWithConfig(&config);

    FPDF_DOCUMENT doc = FPDF_LoadDocument(pdfPath, nullptr);
    if (!doc) {
        FPDF_DestroyLibrary();
        return "Failed to load document.";
    }

    int pageCount = FPDF_GetPageCount(doc);
    std::string result = "PDF loaded successfully. Page count: " + std::to_string(pageCount);

    // ���������Ӹ���� PDF �����߼�

    FPDF_CloseDocument(doc);
    FPDF_DestroyLibrary();

    // ע�⣺��ʵ��Ӧ���У�����Ҫȷ�����ص��ַ����� WebAssembly �ڴ�����ȷ����
    return result.c_str();
}