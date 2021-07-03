#include <iostream>
#include <leveldb/db.h>

int main() {
	leveldb::DB* db;
	leveldb::Options options;
	options.create_if_missing = true;
	leveldb::Status status = leveldb::DB::Open(options, "./test-leveldb", &db);
	if (status.ok()) {
		std::cout << "DB opened!" << '\n';
	}
	else {
		std::cout << "DB Failed to open" << '\n';
	}

	std::string val;
	if (!(db->Get(leveldb::ReadOptions(), "hello", &val)).ok()) {
		db->Put(leveldb::WriteOptions(), "hello", "world");
	}
	db->Get(leveldb::ReadOptions(), "hello", &val);
	std::cout << "Got value from key hello " << val << '\n';
	status = db->Get(leveldb::ReadOptions(), "hello2", &val);
	if (!status.ok()) {
		std::string errorString = status.ToString();
		if (errorString.find("NotFound") != std::string::npos) {
			std::cout << "Could not find value hello2" << '\n';
			db->Put(leveldb::WriteOptions(), "hello2", "world is better");
		}
		else {
			std::cout << "Error: " << errorString << '\n';
		}
	}
	else {
		std::cout << "Got value from key hello2 " << val << '\n';
	}
	delete db;
}
