#include "QuerySeqScan.hpp"

QuerySeqScan::QuerySeqScan(std::ifstream& ifs, const DataBase& db) : Query(ifs,db){
}

QuerySeqScan::~QuerySeqScan(){
}

void QuerySeqScan::run (int& switchquery){
}
