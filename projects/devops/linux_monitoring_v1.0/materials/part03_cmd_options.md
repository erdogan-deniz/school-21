# Bash scripts, part 3: parameters and command line keys

The most common way to pass data to scripts is by using command line parameters. It looks like this:
```shell
$ ./myscript 10 20
```

The bash shell assigns special variables, called position parameters, to the command line parameters entered when the script is called:
- $0 - name of the script.
- $1 - first parameter.
- $2 - second parameter.
- ...
- $9 - ninth parameter.
- ${10} - tenth parameter.

Here's how you can use the command line parameters in a script using these variables:
```shell
echo $0
echo ${11}
```

Note that command line parameters are separated by spaces. If a parameter contains spaces, it must be enclosed in inverted commas.

### Parameter check

To check if the parameters passed to the script when it is called, you can do the following:
```shell
if [ -n "$1" ]
then
echo Hello $1.
else
echo "No parameters found. "
fi
```

### Parameters counting

The $# variable contains the number of parameters passed to the script when called.

This variable provides an unusual way to get the last of the parameters passed to the script without needing to know the number of parameters. Here's how it looks like:
```shell
echo The last parameter was ${!#}
```

### Capture all command line parameters

In some cases, you may need to capture all parameters passed to the script. The $* and $@ variables can be used for that.

The $* variable contains all parameters entered via command line as a single item.

The $@ variable contains all parameters entered via command line as an array. You can use this variable to iterate over the parameters in cycles.

### shift command

The shift command, by default, shifts the values of the position parameters to the left. For example, the value of $3 variable becomes the value of $2 variable, the value of $2 becomes the value of $1, and what was before in $1 is lost. Note that the value of  $0 variable, which contains the script name, does not change.

Using the shift command, let's look at another way of parameters iteration passed to the script:
```shell
count=1
while [ -n "$1" ]
do
echo "Parameter #$count = $1"
count=$(( $count + 1 ))
shift
done
```

### Command line options

Command line options usually look like letters preceded by a dash.
They are used to manage scripts. This is an example:
```shell
echo
while [ -n "$1" ]
do
case "$1" in
-a) echo "Found the -a option" ;;
-b) echo "Found the -b option" ;;
-c) echo "Found the -c option" ;;
*) echo "$1 is not an option" ;;
esac
shift
done
```

Run the script:
```shell
$ ./myscript –a –b –c –d
```

The output of the script in the terminal:
```shell
Found the -a option
Found the -b option
Found the -c option
-d is not an option
```

This code uses a case construct that checks the option passed to it against the list of options handled by the script.
If the passed value is found in this list, the appropriate branch of code is executed. If any option is used when calling the script, the "*" branch will be executed.

### How to distinguish options and parameters

It is common when writing bash scripts to use both command line parameters and options. The typical way to do this is to use a special sequence of characters that tells the script when options end and parameters begin.

This sequence is a double dash. The shell uses it to indicate the position at which the list of keys ends. Let's look at an example:
```shell
while [ -n "$1" ]
do
case "$1" in
-a) echo "Found the -a option" ;;
-b) echo "Found the -b option";;
-c) echo "Found the -c option" ;;
--) shift
break ;;
*) echo "$1 is not an option";;
esac
shift
done
count=1
for param in $@
do
echo "Parameter #$count: $param"
count=$(( $count + 1 ))
done
```

This script uses the break command to break the while loop when a double dash is detected in a line.

As you can see, when the script, parsing the data passed to it, finds a double dash, it finishes the option processing and treats anything not yet processed as parameters.

### Processing options with values

As your scripts get more complex, you will face situations where normal options are no longer sufficient, which means that you have to use options with some values.
For example, a script call that uses such a feature looks like this:
```shell
./myscript -a test1 -b -c test2
```

The script should be able to detect when additional parameters are used along with the command line options.
Here is an example of processing an option that needs a parameter:
```shell
-b) param="$2"
echo "Found the -b option, with parameter value $param"
shift ;;
```

### Using standard options

When writing bash scripts you can select any letters for the command line options and randomly set how the script reacts to those options. However, in the Linux world, the values of some options have become something of a standard to which it is good to follow. Here is the list of this options:
- -a -- List all items.
- -c -- Get the count of items.
- -d -- Output directory.
- -e -- Expand items.
- -f -- Specify the file to read data from.
- -h -- Output help for the command.
- -i -- Ignore character case.
- -l -- Execute full format data output.
- -n -- Use non-interactive  (batch) mode.
- -o -- Allows you to specify the file to which output should be redirected.
- -q -- Execute script in quiet mode.
- -r -- Process folders and files recursively.
- -s -- Execute the script in silent mode.
- -v -- Execute verbose output.
- -x -- Exclude item.
- -y -- Answer «yes» to all questions.

### Receiving data from the user

The bash shell has a read command for user input at runtime. After receiving the data, this command stores it in a variable:
```shell
echo -n "Enter your name: "
read name
```

Note that the echo command, which outputs the prompt, is called with -n option. This results in no line break character being displayed at the end of the prompt, allowing the script user to enter data where the prompt is located, rather than on the next line.

You can specify multiple inputs:
```shell
read -p "Enter your name: " first last
```

If you don’t specify variables for the read command, it will save all incoming inputs in the REPLY variable.
