# Algorithms Engineering Project

First, compile the codes in `tarjan.cpp` and `schmidt.cpp` using the following commands:

```shell
$ g++ -std=c++17 -Wshadow -Wall -o tarjan.out tarjan.cpp -O2 -Wno-unused-result
$ g++ -std=c++17 -Wshadow -Wall -o schmidt.out schmidt.cpp -O2 -Wno-unused-result
```

To run the code, use the Python script in the file `test_script.py`.
Assuming the graphs are stored in .mtx format in a directory with relative path `./to_test`,
open the script and change the `os.walk('./connected_graphs')` to `os.walk('./to_test')` in line 9.

The script will output the average time taken by both algorithms after running it
on each file. Run the following command in the terminal.

```shell
$ ulimit -s unlimited
$ python3 test_script.py
```
