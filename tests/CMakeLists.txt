add_executable(HexTests hex-tests.cpp)
target_link_libraries(HexTests Core)

add_executable(HashRate hash-rate.cpp)
target_link_libraries(HashRate Core)
target_link_libraries(HashRate CryptoPP)

add_executable(LevelDBTests leveldb-tests.cpp)
target_link_libraries(LevelDBTests Core)
target_link_libraries(LevelDBTests leveldb)

add_executable(HashTests hash-tests.cpp)
target_link_libraries(HashTests Core)
target_link_libraries(HashTests CryptoPP)
