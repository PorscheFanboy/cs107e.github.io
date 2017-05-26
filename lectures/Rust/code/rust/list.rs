fn main() {
    let mut vec: Vec<i32> = Vec::new(); // std::vector<int> vec;
    vec.push(107);                      // vec.push_back(107);

    let n: &i32 = &vec[0];              // int* n = &vec[0];
    vec.push(110);                      // vec.push_back(110);
}

// fn dangling_pointer() -> &i32 {
//     let n: i32 = 0;
//     return &n;
// }
