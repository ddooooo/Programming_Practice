//grab one element from container and pass to something processor, one by one//
class Sum {
    private:
        int sum;
    public:
        Sum() : sum(0) {}
        void operator()(int value) { sum += value;}
        int result() const {return sum;}
};

int main() {
    list<int> x;
    for(int i=0; i<5, i++) {
        x.push_back(i);
    }

    Sum sum = for_each(x.begin(), x.end(), Sum()); // call Function Sum()(*first) -> and return the type of the Function object

}

//stl-transform -> for each data in container1(source) and transfrom and put it in container2(destination)//