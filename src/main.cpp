#include <CLI/CLI.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "html_scrape.h"
#include <regex>




void parse_html(const std::string& html) {
    std::regex re("<div class=\"gs_r gs_or gs_scl\">.*?<h3 class=\"gs_rt\"><a href=\"(.*?)\">(.*?)</a></h3>.*?<div class=\"gs_a\">(.*?)</div>.*?</div>");
    std::smatch match;

    std::string::const_iterator search_start(html.cbegin());
    int index = 1;

    while (std::regex_search(search_start, html.cend(), match, re)) {
        std::string url = match[1];
        std::string title = match[2];
        std::string author_info = match[3];

        // Split author_info by " - "
        std::vector<std::string> authors;
        std::stringstream ss(author_info);
        std::string token;
        while (std::getline(ss, token, '-')) {
            authors.push_back(token);
        }

        // Format and print the data
        std::cout << index++ << " & " 
                  << authors[0] << " & "
                  << title << " & "
                  << authors[1] << " & "
                  << "\\href{" << url << "}{Link} \\\\ \n";
        search_start = match.suffix().first;
    }
}


int main(int argc, char** argv) {
    CLI::App app{"Citation Generator - Charles Ueltschey 2024"};

    std::string search_phrase;
    std::string output_format;
    std::string database_type;
    std::string output_filepath;
    bool is_verbose;

    app.add_option("search_phrase", search_phrase, "Phrase to use with the chosen database")
        ->required();

    app.add_option("-f,--format", output_format, "Output format (plaintext or bib)")
        ->check(CLI::IsMember({"plaintext", "bib"}))->default_val("plaintext");

    app.add_option("-d,--database", database_type, "database to use (arXiv | google )")
        ->check(CLI::IsMember({"google", "arxiv"}))->default_val("google");

    app.add_option("-o,--output", output_filepath, "Filepath to output")
        ->default_val("");

    app.add_flag("-v,--verbose", is_verbose, "Show status messages")->default_val(false);

    CLI11_PARSE(app, argc, argv);

    if (is_verbose) {
        std::cout << "Search Keywords: " << search_phrase << "\n";
        std::cout << "Format: " << output_format << "\n";
    }

    std::replace(search_phrase.begin(), search_phrase.end(), ' ', '+');

    // TODO: add num_papers
    std::string received_html = fetchHtml(database_type, search_phrase);


    // TODO: parse HTML
    parse_html(received_html);

    return 0;
}

