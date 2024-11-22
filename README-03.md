# Commands

The project supports the following commands:

sort: Sorts a list of integers.
quit: Exits the program.
igrade: Inserts a grade into a list.
pgrade: Prints the list of grades.
avgrade: Calculates the average grade.
maxgrade: Finds the maximum grade.
mingrade: Finds the minimum grade.
avgsgrade: Calculates the average grade per student.
dice: Simulates rolling a dice.
fact: Calculates the factorial of a number.
Usage
To use the program, compile the source code and run the executable. You will be prompted to enter a command followed by any necessary arguments. For example:

```
> sort 5 3 8 1
Sorted list: 1 3 5 8
```

# Function Descriptions

## sort_int

Sorts a list of integers in ascending order.

## quit

Exits the program.

## grade_insert

Inserts a grade into a list of grades.

## grade_print

Prints the list of grades.

## grade_average

Calculates the average grade from the list.

## grade_maximum

Finds the maximum grade in the list.

## grade_minimum

Finds the minimum grade in the list.

## grade_average_student

Calculates the average grade per student.

## dice

Simulates rolling a dice and returns a random number between 1 and 6.

## factorial

Calculates the factorial of a given number.

# libs

`src/vec.c`: my Vector and Big Integer library.

> 别的不说，至少能用
> 虽然内存到处泄漏...先不管了
