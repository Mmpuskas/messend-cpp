clang++ -std=c++11 client.cpp -o client -I ../../messend -lmessend -L ../../messend-rs/target/debug -I ../ -ldl -lpthread
clang++ -std=c++11 server.cpp -o server -I ../../messend -lmessend -L ../../messend-rs/target/debug -I ../ -ldl -lpthread
