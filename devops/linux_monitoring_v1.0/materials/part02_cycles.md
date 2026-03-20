# Bash scripts, part 2: loops

The bash shell supports for loops, which allow you to iterate through a sequence of values. This is the basic structure of these loops:
```shell
for var in list
do
commands
done
```

The simplest example of a for loop in bash scripts is probably a list of values iteration:
```shell
for var in first "the second" third "I’ll do it"
do
echo "This is: $var"
done
```

Another way to initialise a for loop is to send it a list, which is the result of some command, for example output the contents of a file:
```shell
file="myfile"
for var in $(cat $file)
do
echo " $var"
done
```

### Field separators

In the previous example, all list items, within a file, are separated by spaces, tabs or line breaks.

There is a special environment variable called IFS (Internal Field Separator) to specify field separators.

By default, the bash shell considers the following characters as field separators:
- Space
- Tab character
- Line feed character

If bash sees any of these characters in the data, it assumes it is the next independent value in the list.

The IFS environment variable can be temporarily changed:
```shell
IFS=$'\n'
IFS=:
```

Now you can write a script that outputs the contents of the file line by line:
```shell
file="/etc/passwd"
IFS=$'\n'
for var in $(cat $file)
do
echo " $var"
done
```

For nested loops, the IFS variable can be changed and the outer loop will continue to run with the separator set before it started. This is what the /etc/passwd file processing looks like:
```shell
IFS=$'\n'
for entry in $(cat /etc/passwd)
do
echo "Values in $entry –"
IFS=:
for value in $entry
do
echo " $value"
done
done
```

### Iterating over directory files

Another example of using loops is iterating over directory files:
```shell
for file in /home/likegeeks/*
do
commands
fi
done
```

### While loops

Besides for loop, you can also use while loop in bash, for example:
```shell
var1=5
while [ $var1 -gt 0 ]
do
echo $var1
var1=$[ $var1 - 1 ]
done
```

### C-style for loops

In bash scripts, you can use for loops that look very similar to C-style loops, for example:
```shell
for (( i=1; i <= 10; i++ ))
do
echo "number is $i"
done
```

There are break and continue commands in bash scripts that work just like their C counterparts. You can use them not only in C-style for loops, but also in standard for and while loops.

### Processing output in a loop

Data output in a loop can be processed by either redirecting the output or passing it to a pipeline. This is done by adding output processing commands after the done instruction.


For example, you could write everything that is output in the loop in a file:
```shell
for (( a = 1; a < 10; a++ ))
do
echo "Number is $a"
done > myfile.txt
```

The shell will create the myfile.txt file and redirect the output of the for statement to this file.
