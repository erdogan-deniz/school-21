# Bash scripts: beginning

In the first line, we need to specify what kind of shell we are going to use. We are interested in bash, so the first line of the file will be:
```shell
#!/bin/bash
```

Other lines in this file use a hash character to indicate comments that the shell does not handle. However, the first line is a special case, with a hash followed by an exclamation mark (this sequence is called a shebang)

Shell commands are separated by a newline character. This is how it looks like:
```shell
#!/bin/bash
# This is a comment
pwd
whoami
```

To run the script, you need to give the script an execute permission. To do this, run this command in the terminal:

```shell
chmod +x ./myscript
```

The script can now be run by entering in the command line:
```shell
./myscript
```

### Text output

The echo command is used to output text to the Linux console:
```shell
echo "Hello World"
```

### Variables

There are two types of variables that can be used in bash scripts:
- Environment variables
- User variables

Environment variables store some system data, such as the current user's home directory:
```shell
echo "Home for the current user is: $HOME"
```

Also bash scripts allow you to set and use your own variables in the script. Such variables store the value until the script terminates.

Like system variables, user variables can be accessed using the dollar sign:

```shell
grade=5
person="Adam"
echo "$person is a good boy, he is in grade $grade"
```

### Command substitution

The bash script allows you to get information from the command output and assign it to variables.

There are two ways to do this:

- Using the reverse apostrophe character "`".
- Using the $() construction

So, saving the output of the pwd command to the mydir variable could look like this:
```shell
mydir=`pwd`
mydir=$(pwd)
```

### Mathematical operations

You can use $((*operation*)) to perform mathematical operations in a script file:
```shell
var1=$(( 5 + 5 ))
var2=$(( $var1 * 2 ))
```

### Conditional statement

The conditional statement in bash is implemented like this:
```shell
if command
then
commands
elif command
then
commands
else
commands
fi
```

Here is an example of using a conditional statement:
```shell
user=anotherUser
if grep $user /etc/passwd
then
echo "The user $user Exists"
elif ls /home
then
echo "The user doesn’t exist but anyway there is a directory under /home"
else
echo "The user $user doesn’t exist"
fi
```

### Comparison

Numerical values can be compared in scripts. Here is a list of corresponding commands:
- n1 -eq n2 -- Returns true value if n1 equals n2.
- n1 -ge n2 -- Returns true value if n1 is greater than or equal to n2.
- n1 -gt n2 -- Returns true value if n1 is greater than n2.
- n1 -le n2 -- Returns true value if n1 is less than or equal to n2.
- n1 -lt n2 -- Returns true value if n1 is less than n2.
- n1 -ne n2 -- Returns true value if n1 is not equal to n2.

String values can also be compared in scripts. Here is a list of operators:
- str1 = str2 -- Checks strings for equality, returns true if strings are identical.
- str1 != str2 -- Returns true if strings are not identical.
- str1 < str2 -- Returns true if str1 is less than str2.
- str1 > str2 -- Returns true if str1 is greater than str2.
  -n str1 -- Returns true if str1 length is greater than zero.
  -z str1 -- Returns true if str1 length is zero.

An example of performing comparison operations:
```shell
#!/bin/bash
val1=text
val2="another text"
if [ $val1 \> $val2 ]
then
echo "$val1 is greater than $val2"
else
echo "$val1 is less than $val2"
fi
```

String comparison operations have certain features:

1. ">" and "<" operators must be escaped with a backslash, otherwise the script will not work correctly, although no error messages will appear. The script interprets the ">" as a redirect output command.

2. To make the script work without warnings, variables whose values contain more than one word should be enclosed in double quotes:
```shell
val1=text
val2="another text"
if [ $val1 \> "$val2" ]
then
echo "$val1 is greater than $val2"
else
echo "$val1 is less than $val2"
fi
```

3. In comparison commands upper case letters are smaller than lower case letters because string comparisons are done by comparing ASCII character codes.

### File checks

The following commands allow you to check various file conditions:
- -d file -- Checks if file exists and is a directory.
- -e file -- Checks if file exists.
- -f file -- Checks if file exists and is a file.
- -r file -- Checks if file exists and is readable.
- -s file -- Checks if file exists and is not empty.
- -w file -- Checks if file exists and is writable.
- -x file -- Checks if file exists and is executable.
- -file1 -nt file2 -- Checks if file1 is newer than file2.
- -file1 -ot file2 -- Checks if file1 is older than file2.
- -O file -- Checks if file exists and if the current user owns it.
- -G file -- Checks if file exists and if its group ID matches the current user's group ID.

As an example, here is a script that outputs the contents of an existing directory:
```shell
mydir=/home/likegeeks
if [ -d $mydir ]
then
echo "The $mydir directory exists"
cd $ mydir
ls
else
echo "The $mydir directory does not exist"
fi
```
