#include <iostream>

using namespace std;
const int Alphabet_Size = 26;
struct TrieNode{
    TrieNode* children[Alphabet_Size];
    bool isEndWord;
    TrieNode(){
        isEndWord = false;
        for(int i = 0; i < Alphabet_Size; i++){
            children[i] = NULL;
        }
    }
};

void insert(TrieNode *root,string key){
    TrieNode *temp = root;
    for (int i = 0; i < key.length(); ++i) {
        int idx = key[i]-'a';
        if (!temp->children[idx]){
            temp->children[idx] = new TrieNode();
        }
        temp = temp->children[idx];
    }
    temp->isEndWord = true;

}
bool search(TrieNode *root,string key){
    TrieNode *temp = root;
    for (int i = 0; i < key.length(); ++i) {
        int idx = key[i]-'a';
        if(!temp->children[idx]){
            return false;
        }
        temp = temp->children[idx];
    }
    return (temp->isEndWord);
}

int main() {
    string keys[] = {"the", "a", "there",
                     "answer", "any", "by",
                     "bye", "their" };
    int n = sizeof(keys)/sizeof(keys[0]);
    TrieNode *root = new TrieNode();

    // Construct trie
    for (int i = 0; i < n; i++)
        insert(root, keys[i]);

    // Search for different keys
    char output[][32] = {"Not present in trie", "Present in trie"};

    // Search for different keys
    cout<<"the"<<" --- "<<output[search(root, "the")]<<endl;
    cout<<"these"<<" --- "<<output[search(root, "these")]<<endl;
    cout<<"their"<<" --- "<<output[search(root, "their")]<<endl;
    cout<<"thaw"<<" --- "<<output[search(root, "thaw")]<<endl;
    return 0;
}
