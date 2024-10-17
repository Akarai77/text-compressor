#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <fstream>
#include<filesystem>
#include <queue>
#include <unordered_map>
#include <string>

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char ch, int freq);
    Node(char ch, int freq, Node* left, Node* right);
};

class compare {
public:
    bool operator()(Node* l, Node* r);
};

    void buildHuffmanTree(const std::string& text, Node*& root, std::priority_queue<Node*, std::vector<Node*>, compare>& pq);
    void getCodes(Node* root, std::string str, std::unordered_map<char, std::string>& huffmanCode);
    std::string encode(const std::string& text, Node*& root, std::priority_queue<Node*, std::vector<Node*>, compare>& pq);
    void decode(Node* root, const std::string& code, std::ostream& outputStream);

void compress(const std::string& inputFileName);
void decompress(const std::string& inputFileName);

#endif
