#include <fpdfview.h>
#include <string>
#include <vector>
#include <emscripten.h>

// 使用 EMSCRIPTEN_KEEPALIVE 确保函数在最终的 WebAssembly 中可用
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

    // 这里可以添加更多的 PDF 处理逻辑

    FPDF_CloseDocument(doc);
    FPDF_DestroyLibrary();

    // 注意：在实际应用中，您需要确保返回的字符串在 WebAssembly 内存中正确管理
    return result.c_str();
}