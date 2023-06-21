## Using the **du** utility
du is a command to get an approximate amount of disk space used by the specified files or directories.

Here are some examples of how to use the du command:
- To simply list the folders in a certain directory and how much space they take up, for example in /var, run: \
  ![du1](../misc/images/du1.png)
- By default the size is output in bytes. Use option -h to output the size in a more readable way: \
  ![du2](../misc/images/du2.png)
- If you want to print not only the size of folders but also the size of files located in them, use -a option: \
  <img src="../misc/images/du3.png" alt="du3" width="298"/>
- -c -- option to display total size of all folders at the end
- -d -- maximum nesting depth of directories
- -s -- option to output total size only
