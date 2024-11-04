# Bash scripts, part 5: functions and creating libraries

The bash shell provides the ability to create functions. A function in bash can be defined in 2 ways:
```shell
functionName {
}

functionName1() {
}
```

To call a function in a script, all you have to do is specify its name.
```shell
function myfunc {
echo "This is an example of using a function"
}
count=1
while [ $count -le 3 ]
do
myfunc
count=$(( $count + 1 ))
done
echo "End of the script"
```

The result of the script described above:
```
This is an example of using a function
This is an example of using a function
This is an example of using a function
End of the script
```

Note that if you try to use a function before defining it, you will have an error.

### Using the return command

The return command allows you to specify an integer termination code returned by the function. What the function returned is in the $? variable.

If you execute any other command before retrieving the value returned by the function from the $? variable, that value will be lost. The point is that this variable stores the return code for the last executed command.

Note that the maximum number the return command can return is 255. If the function needs to return a larger number or string, it will need a different approach.

An example of how the return command works:
```shell
function myfunc {
read -p "Enter a value: " value
echo "adding value"
return $(( $value + 10 ))
}
myfunc
echo "The new value is $?"
```

### Writing function output to variable

Another way to return the results of a function is to record the data output by the function into a variable. This approach allows you to bypass the limitations of the return command and return any data from the function.

An example of using this approach:
```shell
function myfunc {
read -p "Enter a value: " value
echo $(( $value + 10 ))
}
result=$( myfunc)
echo "The value is $result"
```

### Function Arguments

Function arguments in bash work in the same way as the command line parameters passed to the script.

For example, the function name is stored in the $0 parameter, the first argument passed to it in $1, and so on. The number of arguments passed to the function is stored in the $# variable.

An example of using function arguments:
```shell
function addnum {
if [ $# -eq 0 ] || [ $# -gt 2 ]
then
echo -1
elif [ $# -eq 1 ]
then
echo $(( $1 + $1 ))
else
echo $(( $1 + $2 ))
fi
}
echo -n "Adding 10 and 15: "
value=$(addnum 10 15)
echo $value
echo -n "Adding one number: "
value=$(addnum 10)
echo $value
echo -n "Adding no numbers: "
value=$(addnum)
echo $value
echo -n "Adding three numbers: "
value=$(addnum 10 15 20)
echo $value
```

Note that the function cannot directly work with parameters that are passed to the script when it is run from the command line.

Passing an array into a function as an argument will not work. This is an example of the wrong approach:
```shell
myarray=(1 2 3 4 5)
echo "The original array is: ${myarray[*]}"
myfunc $myarray
```

Instead, you should pass all the items of the array as separate arguments. An example of the correct approach:
```shell
function myfunc {
newarray=("$@")
echo "The new array value is: ${newarray[*]}"
}
myarray=(1 2 3 4 5)
echo "The original array is ${myarray[*]}"
myfunc ${myarray[*]}
```

### Global and local variables

The way global and local variables work in bash scripts is the same as in other programming languages.

The only difference is that all variables in the bash script are considered global by default.
To create a local variable, add the word local before its name:
```shell
local temp=$(( $value + 5 ))
```

### Creating and using libraries

To use functions described in another file in the script, use the source command or the "dot" operator.

An example of connecting a function from another file:

The contents of the myfuncs file, which is a library:
```shell
function addnum {
echo $(( $1 + $2 ))
}
```

Main script:
```shell
. ./myfuncs
result=$(addnum 10 20)
echo "The result is: $result"
```
