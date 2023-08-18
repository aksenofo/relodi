#include <argparse/argparse.hpp>
#include <common.h>
#include <exception>
#include <format.h>
#include <fstream>
#include <header_block0.h>
#include <header_block1.h>
#include <log.h>
#include <set>
#include <singleton.h>

void master(int argc, const char** argv)
{
    argparse::ArgumentParser parser;
    parser.add_argument("-i", "--input").help("specify the input file.").required();
    parser.add_argument("-l", "--log-level").help("specify the LOG Level.");

    parser.parse_args(argc, argv);

    singleton<LoggerFactory>::instance()->SetPrintTimeStamp(true);
    singleton<LoggerFactory>::instance()->SetAppPrefix(argv[0]);
    singleton<LoggerFactory>::instance()->SetOutputFileName("output.log");

    singleton<LoggerFactory>::instance()->SetLevel(
        LogLevel::Error,
        LogLevel::Panic,
        LogLevel::Debug,
        LogLevel::Info,
        LogLevel::Warning);

    if (const auto& level = parser.present("-l")) {
        std::vector<std::string> logLevel =
            array2container<std::vector<std::string>>(level->begin(), level->end(),
                [](const auto& v) { return v == '|'; });

        std::for_each(logLevel.begin(), logLevel.end(), [](auto& item) {
            item = rtrimed(ltrimed(item));
            std::for_each(item.begin(), item.end(), [](auto& c) { c = toupper(c); });
        });

        const auto& trimed =
            trim<std::vector<std::string>>(logLevel.begin(), logLevel.end(),
                [](const auto& v) { return !v.empty(); });

        std::set<std::string> trset(trimed.begin(), trimed.end());

        std::for_each(trset.begin(), trset.end(), [](const auto& p) {
            singleton<LoggerFactory>::instance()->SetLevelByString(p);
        });
    }
    std::string relogFile = parser.get<std::string>("-i");

    LOG(Info) << format("Process file:%1.", relogFile);
    std::ifstream is(relogFile);
    is.exceptions(std::ofstream::badbit | std::ofstream::failbit);
    relodi::common::Block0 b0(is);
    LOG(Info) << format("Blocksize:%1 Blockcount:%2.", b0.header().blocksize, b0.header().blockcount);
    for (size_t t = 0; t < b0.header().blockcount; ++t) {
        relodi::common::Block1 b1(b0.header().blocksize, is);
        LOG(Info) << format("Signature:%1 Blocknum: %2 Checksum:%3 Filenum:%4 offset:%5",
            b1.header().signature,
            b1.header().blocknum,
            b1.header().checksum,
            b1.header().filenum,
            b1.header().offset);
    }
}

int main(int argc, const char** argv)
{
    try {
        const char* arguments[] = {
            argv[0],
            "-i",
            "/home/aksenofo/PROJECT/mnt/LEXA/orp/1_123_1088442028.dbf",
            "-l",
            "Debug|Info|Warning"
        };
        master(sizeof(arguments) / sizeof(*arguments), arguments);
    } catch (const std::exception& ex) {
        std::cerr << "ERROR: " << ex.what() << std::endl;
        return 1;

    } catch (...) {
        std::cerr << "ERROR: Unknown error." << std::endl;
        return 1;
    }
}
