#include <iostream>
#include <string>
#include <fstream>
#include "bcrypt/BCrypt.hpp"
#include <thread>
#include <chrono>
#include <sstream>

#define THREAD_COUNT 4

using namespace std;

atomic<bool> flag = false;
int countLines(const string& filename) {
    ifstream file(filename);   
    int count = 0;
    string line;

    while (std::getline(file, line)) {
        ++count;
    }

    return count;
}

void writeLog(const string& message) {
  stringstream filename_;
  filename_ << chrono::system_clock::to_time_t(chrono::system_clock::now());
  filename_ << "-result.log";
  string filename = filename_.str();
  ofstream file(filename);
  if(!file) {
    cerr << "Cannot open log file " << filename << "\n";
    return;
  }
  file << message << endl;
  file.close();
}

void process(string file_name, const string& hash_password, int startline, int endline){
  ifstream file(file_name);
  if(!file) {
    cerr << "Cannot open file " << file_name << "\n";
    return;
  }
  string line;
  int i;
  for(i = 0; i < startline-1; i++) {
    getline(file, line);
  }
  while(getline(file,line) && i < endline+1) {
    if(flag){
      file.close();
      return;
    }
    bool match = BCrypt::validatePassword(line, hash_password);
    if(match){
      cout << line << " matched!\n";
      flag = true;
      stringstream message;
      message << "hash " << hash_password << " found in the file " << file_name << "\n";
      message << hash_password << " - " << line;
      writeLog(message.str());
      return;
    }
    cout << i << " Tried " << line << "\n";
    i++;
  }
  file.close();
}

void usage() {
  cout << "usage: ./passwordcracker <hash> <password_file>\n";
}
int main(int argc, char** argv) {

  if(argc < 3){
    usage();
    return 1;    
  }

  string hash_password = argv[1];
  string file_name = argv[2];
  fstream _file(file_name);
  if(!_file){
    cerr << "Cannot open the file " << file_name << endl;
    return 1;
  }
  _file.close();
  cout << "hash: " << hash_password << endl;
  int total_lines = countLines(file_name);
  const int BATCH_SIZE = total_lines/THREAD_COUNT;
  cout << "Batch size: " << BATCH_SIZE << "\n";
  vector<thread> vector_thread;
  int line_count = 1;
  for(int thread_i = 0; thread_i < THREAD_COUNT; thread_i++) {
    vector_thread.emplace_back(process, file_name, ref(hash_password), line_count, line_count+BATCH_SIZE);
    line_count+=BATCH_SIZE+1;
  }

  for(auto& t : vector_thread) {
    if(t.joinable())
      t.join();
  }

  if(!flag) {
    writeLog("hash " + hash_password + " is not matched from the file " + file_name);
  }
  return 0;
}
