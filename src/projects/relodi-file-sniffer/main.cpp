#include <argparse/argparse.hpp>
#include <common.h>
#include <exception>
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

    singleton<LoggerFactory>::instance()->SetLevel(
        LogLevel::Error,
        LogLevel::Panic);

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
}

int main(int argc, const char** argv)
{
    try {
        master(argc, argv);
    } catch (const std::exception& ex) {
        std::cerr << "ERROR: " << ex.what() << std::endl;
        return 1;

    } catch (...) {
        std::cerr << "ERROR: Unknown error." << std::endl;
        return 1;
    }
}