# Bash scripts, part 4: input and output

Each process can have nine file descriptors opened at the same time.
The bash shell reserves the first three descriptors with identifiers 0, 1 and 2. This is what they mean:
- 0, STDIN - standard input stream.
- 1, STDOUT - standard output stream.
- 2, STDERR - standard error stream.

### STDIN

STDIN stands for standard input, which is the keyboard by default.
When scripts use the input redirection character - <, Linux replaces the file descriptor of the standard input with the one specified in the command. The system reads the file and processes the data as if it were entered from the keyboard.

Here is an example of the input redirection:
```shell
exec 0< testfile
count=1
while read line
do
echo "Line #$count: $line"
count=$(( $count + 1 ))
done
```

Here the read command, when trying to read data from STDIN, will read it from the file and not from the keyboard.

### STDOUT

STDOUT is the standard shell output stream. It is the screen by default.
Most bash commands output data to STDOUT, which results in it appearing in the console.
Data can be redirected to a file by attaching it to its contents, using the >> command, for example:
```shell
pwd >> myfile
```

The output of pwd will be added to myfile without deleting the existed data.

If a script needs to redirect a lot of output data, it is inconvenient to add a command to each echo call. Instead, you can redirect the output to a specific descriptor for the duration of the script by using exec:
```shell
exec 1>outfile
```
