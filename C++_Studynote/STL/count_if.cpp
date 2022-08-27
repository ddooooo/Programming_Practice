//count how many items that satifies the predicate//
//keep adding 1 if the predicate returns true//

int main() {
    vector<int> x;
    for(int i=-5; i<5; i++) {
        x.push_back(i*10);
    }

    cout << count_if(x.begin(), x.end(), Haha(10)) << endl; //could ask me how to implement count_if() by using find_if()
    
}