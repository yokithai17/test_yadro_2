#include "Club.h"

#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

std::string normalize_line(const std::string& line) {
  std::string result = line;
  result.erase(std::ranges::remove(result, '\r').begin(), result.end());
  return result;
}

namespace {
  std::string get_line(std::ifstream& in, std::string& line) {
    std::getline(in, line);
    return normalize_line(line);
  }
}


int main(int argc, char* argv[]) {

  std::string input;
  std::string output = "stdout";
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "--input" && i + 1 < argc) {
      input = argv[++i];
    } else if (arg == "--help") {
      std::cout << "Usage: " << argv[0] << " --input <input>\n";
      return 0;
    } else {
      std::cerr << "Unknown option or missing argument: " << arg << "\n";
      return 1;
    }
  }

  if (input.empty()) {
    std::cerr << "--input are required\n";
    return 1;
  }

  std::ifstream input_file(input);
  if (!input_file.is_open()) {
    std::cerr << "Failed to open input file: " << input << "\n";
    return 1;
  }

  std::string t_table, t_price, t_time;
  get_line(input_file, t_table);
  get_line(input_file, t_time);
  get_line(input_file, t_price);
  auto t = club::split(t_time);

  std::string t_start =  t[0];
  std::string t_end = t[1];


  auto comp = ComputerClub(
    std::stoi(t_table),std::stoi(t_price),
    club::Time{t_start}, club::Time{t_end.substr(0, t_end.size() - 1)});


  std::string event_token;
  while (std::getline(input_file, event_token)) {
    auto inp_ev = club::event_parse(normalize_line(event_token));
    auto out_ev = comp.handle_event(inp_ev);
  }
}
