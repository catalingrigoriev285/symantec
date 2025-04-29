#ifndef ENGINE_INTERFACE
#define ENGINE_INTERFACE

#include <string>

namespace Engine
{
    namespace Interface
    {
        enum class ScannerType
        {
            Signature,
            // Heuristic,
            // Behavior,
            // Anomaly,
            // Hybrid
        };

        struct EngineReport {
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
            EngineReport report;
        public:
            
        };
    };
}

#endif