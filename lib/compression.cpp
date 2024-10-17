#include "compression.h"
#include "error_handler.h"

using namespace std;

Node::Node(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {}

Node::Node(char ch, int freq, Node* left, Node* right) 
    : ch(ch), freq(freq), left(left), right(right) {}

bool compare::operator()(Node* l, Node* r) {
    return l->freq > r->freq;
}

Node* buildHuffmanTree(const string& text) {
    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    priority_queue<Node*, vector<Node*>, compare> pq;
    for (const auto& pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        int sum = left->freq + right->freq;
        pq.push(new Node('\0', sum, left, right));
    }

    return pq.top();
}

void getCodes(Node* root, string str, unordered_map<char, string>& codeMap) {
    if (!root) return;
    if (!root->left && !root->right) {
        codeMap[root->ch] = str;
    }

    getCodes(root->left, str + "0", codeMap);
    getCodes(root->right, str + "1", codeMap);
}

unordered_map<char, string> encode(const string& text) {
    Node* root = buildHuffmanTree(text);
    unordered_map<char, string> codeMap;
    getCodes(root, "", codeMap);
    return codeMap;
}

void writeBits(ofstream& outFile, const string& bitString) {
    uint8_t buffer = 0;
    int bitCount = 0;

    for (char bit : bitString) {
        buffer = (buffer << 1) | (bit - '0');
        bitCount++;

        if (bitCount == 8) {
            outFile.write(reinterpret_cast<char*>(&buffer), sizeof(buffer));
            buffer = 0;
            bitCount = 0;
        }
    }

    if (bitCount > 0) {
        buffer <<= (8 - bitCount);
        outFile.write(reinterpret_cast<char*>(&buffer), sizeof(buffer));
    }
}

void saveTree(Node* root, ofstream& outFile) {
    if (!root) return;

    if (!root->left && !root->right) {
        outFile.put('1');
        outFile.put(root->ch);
    } else {
        outFile.put('0');
        saveTree(root->left, outFile);
        saveTree(root->right, outFile);
    }
}

Node* loadTree(ifstream& inFile) {
    char ch;
    inFile.get(ch);

    if (ch == '1') {
        inFile.get(ch);
        return new Node(ch, 0);
    }

    Node* left = loadTree(inFile);
    Node* right = loadTree(inFile);
    return new Node('\0', 0, left, right);
}

void compress(const string& file) {
    ifstream inFile(file);
    if (!inFile) {
        ERROR("Failed to open the file");
    }

    string lines, line;
    while (getline(inFile, line)) {
        lines += line + '\n';
    }

    if (lines.empty()) {
        ERROR("No data found for compression");
    }

    unordered_map<char, string> codeMap = encode(lines);
    string encodedText;
    for (char ch : lines) {
        encodedText += codeMap[ch];
    }

    filesystem::path inFilePath = filesystem::absolute(file);
    string outFileName = inFilePath.stem().string() + ".bin";

    ofstream outFile(outFileName, ios::binary);
    if (!outFile) {
        ERROR("Failed to create output file");
    }

    Node* root = buildHuffmanTree(lines);
    saveTree(root, outFile);
    writeBits(outFile, encodedText);

    inFile.close();
    outFile.close();
    int status = remove(inFilePath);
}

string readBits(ifstream& inFile) {
    string encodedText;
    uint8_t buffer;
    while (inFile.read(reinterpret_cast<char*>(&buffer), sizeof(buffer))) {
        for (int i = 7; i >= 0; --i) {
            encodedText += (buffer & (1 << i)) ? '1' : '0';
        }
    }
    return encodedText;
}

string decode(Node* root, const string& encodedStr) {
    string decodedStr;
    Node* current = root;

    for (char bit : encodedStr) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }

        if (!current->left && !current->right) {
            decodedStr += current->ch;
            current = root;
        }
    }
    return decodedStr;
}

void decompress(const string& file) {
    ifstream inFile(file, ios::binary);
    if (!inFile) {
        ERROR("Failed to open the file");
    }

    filesystem::path inFilePath = filesystem::absolute(file);
    if (inFilePath.extension() != ".bin") {
        ERROR("Invalid file extension for decompression");
    }

    Node* root = loadTree(inFile);

    string encodedStr = readBits(inFile);
    string decodedText = decode(root, encodedStr);

    string outFileName = inFilePath.stem().string() + ".txt";
    ofstream outFile(outFileName);
    if (!outFile) {
        ERROR("Failed to create output file");
    }
    outFile << decodedText;

    inFile.close();
    outFile.close();
    int status = remove(inFilePath);
}
