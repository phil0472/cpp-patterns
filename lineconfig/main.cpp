#include <iostream>
#include <fstream>
#include <list>

struct join {
    bool enabled;
    std::string datacenter;
    std::string handoff;
    std::string group_ip;
    uint16_t    group_port;
    
    inline static int error_line = 0;

    static std::list<join> load(std::string fname) {
        error_line = 1;
        std::ifstream ifs(fname);
        std::list<join> l;
        if (ifs) {
            std::copy(
                std::istream_iterator<join>(ifs),
                std::istream_iterator<join>(),
                std::back_inserter(l));
        }
        else {
            throw std::invalid_argument("File not found or inaccessible");
        }
        return l;
    }
};

std::istream& operator>>(std::istream& is, join& j) {
    std::string en;
    is >> en;
    
    if (is.fail()) {
        // end of stream
        return is;
    }

    is >> std::ws >> j.datacenter >> std::ws >> j.handoff >> std::ws >> j.group_ip >> std::ws >> j.group_port;

    j.enabled = (en == "yes");

    if (is.fail()) {
        throw std::invalid_argument("Format error on line " + std::to_string(join::error_line));
    }

    is.ignore(65535, '\n');
    join::error_line++;
    return is;
}

std::ostream& operator<<(std::ostream& os, join& j) {
    os << (j.enabled ? "yes" : "no") << " " << j.datacenter << " " << j.handoff << " " << j.group_ip << " " << j.group_port << std::endl;
    return os;
}

int main(int argc, char **argv) {
    if (argc < 2)
        return 1;

    try {
        std::list<join> joins = join::load(argv[1]);
        for(auto& i: joins) {
            std::cout << i;
        }
    }
    catch(std::invalid_argument e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return 0;
}
