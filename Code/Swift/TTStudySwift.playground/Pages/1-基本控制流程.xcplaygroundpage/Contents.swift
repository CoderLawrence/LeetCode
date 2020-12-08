//: [Previous](@previous)

import Foundation

//while循环
var n = 5
while n > 0 {
    print(n);
    n -= 1
}

repeat {
    print(n)
    n += 1
} while n <= 5

//for 循环
//MARK: -闭区间运算符

let names = ["Anna", "Alex", "Brian", "Jack"]
for i in 0...3 {
    print(names[i])
}

let range = 1...3
for i in range {
    print(names[i])
}

//i默认是let，有需要时可以声明为var
for var i in 1...3 {
    i += 5;
    print(i);
}

//忽略i
for _ in 1...3 {
    print("Rose")
}

//MARK: - 半闭区间
for i in 0..<5 {
    print(i)
}

//MARK: for - 区间运算符用在数组上
for name in names[0...3] {
    print(name)
}

//MARK: for - 单侧区间
for name in names[0...] {
    print(name);
}

for name in names[2...] {
    print(name)
}

for name in names[..<2] {
    print(name)
}

//: [Next](@next)
