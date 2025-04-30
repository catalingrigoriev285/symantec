#ifndef ENGINE_INTERFACE
#define ENGINE_INTERFACE

#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

#include "../scanner/signature_scanner.h"

namespace Engine
{
    using Signature = Scanner::SignatureScanner;

    enum class ScannerType
    {
        Signature,
        // Heuristic,
        // Behavior,
        // Anomaly,
        // Hybrid
    };

    struct EngineReport
    {
        std::string file_path;
        std::string file_hash;
        std::string scan_time;
        std::string scan_result;
        bool is_infected;
        std::string scan_type;
        std::string scanner_name;
    };

    class EngineInterface
    {
    private:
        ScannerType scanner_type;
        std::vector<EngineReport> reports;

    public:
        EngineInterface(ScannerType type) : scanner_type(type) {}
        ~EngineInterface();

        bool initialize();
        bool scan(const std::string &file_path);

        ScannerType get_scanner_type() const { return scanner_type; }
        const std::vector<EngineReport> &get_reports() const { return reports; }
    };
}

#endif