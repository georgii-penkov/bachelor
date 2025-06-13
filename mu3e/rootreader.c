#include <variant>
#include <vector>
#include <string>

struct Branch
{
    std::string name;
    std::string type;
    bool is_vector;
    void* value = nullptr;
}

class RootReader
{
    std::string file_address;
    std::string tree_path;
    std::variant<Int_t, UInt_t, Double_t, Float_t, bool, std::vector<Int_t>, std::vector<UInt_t>, std::vector<Double_t>, std::vector<Float_t>, std::vector<bool>> branch_value;
    
};