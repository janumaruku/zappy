/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** HelpFormatter
*/

#include "HelpFormatter.hpp"

#include <algorithm>
#include <iomanip>
#include <ranges>
#include <sstream>

namespace shell {

static constexpr std::size_t MAX_WIDTH = 80;
static constexpr std::size_t INDENT    = 4;
static constexpr std::size_t COL_GAP   = 4;

static std::string wrapText(const std::string &text, std::size_t startCol)
{
    if (text.empty())
        return "\n";

    const std::string cont(startCol, ' ');
    std::istringstream words(text);
    std::string result;
    std::string word;
    std::size_t col = startCol;
    bool first = true;

    while (words >> word) {
        if (first) {
            result += word;
            col += word.size();
            first = false;
        } else if (col + 1 + word.size() > MAX_WIDTH) {
            result += "\n" + cont + word;
            col = startCol + word.size();
        } else {
            result += " " + word;
            col += 1 + word.size();
        }
    }
    return result + "\n";
}

static std::string formatSection(
    const std::string &title,
    const std::vector<std::pair<std::string, std::string>> &entries)
{
    if (entries.empty())
        return "";

    std::size_t maxLabelLen = 0;
    for (const auto &label: entries | std::views::keys)
        maxLabelLen = std::max(maxLabelLen, label.size());

    const std::size_t descStart = INDENT + maxLabelLen + COL_GAP;

    std::string result = "\n" + title + "\n";
    for (const auto &[label, desc] : entries) {
        std::ostringstream oss;
        oss << std::string(INDENT, ' ')
            << std::left << std::setw(static_cast<int>(maxLabelLen + COL_GAP))
            << label;
        result += oss.str() + wrapText(desc, descStart);
    }
    return result;
}

static void appendUsageToken(std::string &line, const std::string &token,
    const std::size_t contIndent)
{
    if (line.size() + 1 + token.size() > MAX_WIDTH)
        line += "\n" + std::string(contIndent, ' ') + token;
    else
        line += " " + token;
}

std::string formatHelp(const command::CommandDefinition &def)
{
    const std::size_t usageCont = INDENT + def.name.size() + 1;
    std::string usageLine = std::string(INDENT, ' ') + def.name;

    for (const auto &option : def.options) {
        std::string token = option.required ? "--" : "[--";
        token += option.name;
        if (!option.alias.empty())
            token += " | -" + option.alias;
        if (!option.required)
            token += "]";
        token += " <" + option.name + ">";
        appendUsageToken(usageLine, token, usageCont);
    }

    for (const auto &flag : def.flags) {
        std::string token = "[--" + flag.name;
        if (!flag.alias.empty())
            token += " | -" + flag.alias;
        token += "]";
        appendUsageToken(usageLine, token, usageCont);
    }

    for (const auto &arg : def.arguments) {
        const std::string token = arg.required
            ? "<" + arg.name + ">"
            : "[" + arg.name + "]";
        appendUsageToken(usageLine, token, usageCont);
    }

    std::string result = "Usage\n" + usageLine + "\n";

    if (!def.description.empty()) {
        result += "\nDescription\n";
        result += std::string(INDENT, ' ') + wrapText(def.description, INDENT);
    }

    std::vector<std::pair<std::string, std::string>> argEntries;
    for (const auto &arg : def.arguments)
        argEntries.emplace_back(arg.name, arg.description);
    result += formatSection("Argument(s)", argEntries);

    std::vector<std::pair<std::string, std::string>> optEntries;
    for (const auto &opt : def.options) {
        std::string label = "--" + opt.name;
        if (!opt.alias.empty())
            label += ", -" + opt.alias;
        optEntries.emplace_back(label, opt.description);
    }
    result += formatSection("Option(s)", optEntries);

    std::vector<std::pair<std::string, std::string>> flagEntries;
    for (const auto &flag : def.flags) {
        std::string label = "--" + flag.name;
        if (!flag.alias.empty())
            label += ", -" + flag.alias;
        flagEntries.emplace_back(label, flag.description);
    }
    result += formatSection("Flag(s)", flagEntries);

    return result;
}

std::string formatCommandList(
    const std::unordered_map<std::string, command::CommandDefinition> &commands)
{
    std::size_t maxLen = 0;
    for (const auto &name : commands | std::views::keys)
        maxLen = std::max(maxLen, name.size());

    const std::size_t descStart = INDENT + maxLen + COL_GAP;

    std::string result = "Available commands:\n";
    for (const auto &[name, def] : commands) {
        std::ostringstream oss;
        oss << std::string(INDENT, ' ')
            << std::left << std::setw(static_cast<int>(maxLen + COL_GAP))
            << name;
        result += oss.str() + wrapText(def.description, descStart);
    }
    return result;
}

} // namespace shell
