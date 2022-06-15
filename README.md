# ft_containers

_part of 42 common-core cursus, rewritting and complete implementation of some of the containers found in the c++ STL_  


This project consists in the reimplementation of four c++ standard library containers and a series
of helper classes and algorithms, with the aim of getting familiarized with the c++ standard
code logic and methods (SFINAE, template argument deduction, use of iterators), which will
allow us to start developing code in compliance with the c++98 std.  
These reimplementations in the *ft* namespace, and their behaviour will be compared with their stl counterparts.

## List of implemented containers
* std::vector
* std::map
* std::stack
* std::set

```
std::map y std::set have been implemented using red-black BST algorithm
```
## List of implemented helper classes & algo.
* std::iterator_traits
* std::reverse_iterator
* std::enable_if
* std::is_integral
* std::equal
* std::lexicographical_compare
* std::pair
* std::make_pair

## usage
```
make && ./ft_container_test
```
