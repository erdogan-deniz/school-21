## Installing and using the **ncdu** utility
ncdu is a command with the same purpose as du but with a nicer, more user-friendly interface.

Here are some examples of how to use the ncdu command:
- The use of the program is very simple. To scan and review the directory you are in, simply run the ncdu program: \
  <img src="../misc/images/ncdu1.png" alt="ncdu1" width="500"/>
- To scan the entire file system, you must specify a path. For the root, it is a slash. The option -x - do not go beyond the current file system - is also useful. The thing is that other disks may be mounted to the root file system, and without this option they will be counted as well.  Running the `ncdu -x /` command: \
  <img src="../misc/images/ncdu2.png" alt="ncdu2" width="500"/>
- Use one of the following buttons to navigate to the selected directory:
  - right cursor
  - ENTER
  - l
- Use one of the following buttons to return to the parent directory:
  - Cursor left
  - <
  - h
- The following buttons are used to sort directories and files (press again for reverse order):
  - n - by file name
  - s - by file size
  - C - by number of elements
  - M - by time of modification of the last child element
