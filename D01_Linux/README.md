# UNIX/Linux operating systems (Basic).

Linux system installation and updates. Administration basics.

The russian version of the task can be found in the repository.

## Contents

1. [Chapter I](#chapter-i)
2. [Chapter II](#chapter-ii) \
   2.1. [Linux](#linux)  
   2.2. [Administration](#administration)  
   2.3. [Virtual machines](#virtual-machines)
3. [Chapter III](#chapter-iii) \
   3.1 [Installation of the OS](#part-1-installation-of-the-os)  
   3.2 [Creating a user](#part-2-creating-a-user)  
   3.3 [Setting up the OS network](#part-3-setting-up-the-os-network)   
   3.4 [OS Update](#part-4-os-update)  
   3.5 [Using the sudo command](#part-5-using-the-sudo-command)  
   3.6 [Installing and configuring the time service](#part-6-installing-and-configuring-the-time-service)  
   3.7 [Installing and using text editors](#part-7-installing-and-using-text-editors)  
   3.8 [Installing and basic setup of SSHD service](#part-8-installing-and-basic-setup-of-the-sshd-service)  
   3.9 [Installing and using the top, htop utilities](#part-9-installing-and-using-the-top-htop-utilities)   
   3.10 [Using the fdisk utility](#part-10-using-the-fdisk-utility)   
   3.11 [Using the df utility](#part-11-using-the-df-utility)    
   3.12 [Using the du utility](#part-12-using-the-du-utility)    
   3.13 [Installing and using the ncdu utility](#part-13-installing-and-using-the-ncdu-utility)    
   3.14 [Working with system logs](#part-14-working-with-system-logs)     
   3.15 [Using the CRON job scheduler](#part-15-using-the-cron-job-scheduler)


## Chapter I

![linux](misc/images/linux.png)

>Developer’s note: \
>For full immersion, you can play your favorite jazz song while reading the assignment.

Planet Earth, USA, California, Compton, Seb's Jazz Club, nowadays.

`-` Well, Sebastian, you didn't expect me to believe that you called me just to sit and relax, did you? You're not the type to write to an old comrade in the middle of the work week if you have nothing to say.

`-` Nothing can ever be hidden from you! I thought I'd get down to business more smoothly, but since you're so perceptive...

`-` Stop flattering me, I just wonder why we’re here.

`-` The thing is, I recently joined a development company that needed an administrator. But there is problem: they use Linux as their operating system.

`-` And you, as a confident Windows user, want to understand the basics of Linux and also the administration?

`-` Exactly! As far as I remember, you’re good at both.

`-` Well, then, get your laptop! Of course I haven't done this in a while, but I'll try to help. The main thing is to finish before the club closes, otherwise we'll have to continue tomorrow

\> *The song ends, the music slowly fades, they bring you the drinks you ordered*

\> *While Sebastian takes his laptop out and turns it on, you decide to share a little historical background.*


## Chapter II

### Linux

`-` The history of Linux goes back to 1991 when a Finnish graduate programmer Linus Torvalds began to work on his own operating system kernel.

`-` He put his work on a public server and it became a milestone in the history of Linux. First dozens, then hundreds and thousands of developers supported his project, and that’s how a complete operating system was born.

`-` The first official version of Linux 1.0 was released in 1994. From the beginning to the present day, Linux has been distributed as free software under the GPL license. This means that the source code of the operating system can be seen by anyone - and not only seen but also modified. The only condition is that the changed, modified code must also be available to everybody and distributed under the GPL. This is important because it allows developers to use the code and at the same time not be afraid of copyright issues.

`-` Today, Linux is the best known and most used open-source operating system. As an operating system, Linux is a software that is underneath other software on a computer, receiving requests from those programs and passing those requests to the computer's hardware.

\> *The waitress brings you the drinks you ordered, the musicians start playing again*

### Administration

`-` Administration is, without going into too much detail, the support and improvement of all computer and office equipment, peripheral devices, network connectivity, etc. When administering Linux, most of the work is done in the terminal, so it's better to start with basic utilities.

\> *At this point Sebastian's laptop boots up and you see a horrible picture: it doesn't even have the right operating system...*

\> *In order not to reinstall Sebastian's operating system, you decide to use a virtual machine*

### Virtual machines

`-` A virtual machine (VM) is just like a physical computer, it has a CPU, memory, disks for storing files, and can connect to the Internet if necessary. The only difference is that the components of your computer (the hardware) are tangible, while virtual machines exist only as code.

`-` To put it simply, it's a virtual computer on which you can install an operating system and all the associated software, with no changes to your main operating system.

`-` Virtualisation is the process of creating a software (virtual) version of a computer with dedicated CPU, memory and storage resources that are "borrowed" from a physical computer. A virtual machine is a computer file (image) that works like a normal computer.

`-` _VirtualBox_ is a virtualisation software product, i.e. a tool for creating virtual machines.

\> *You wanted to share some more useful information later, so you created a materials folder on Sebastian's laptop with useful information.*


## Chapter III

As a result of the work you should provide a report with completed tasks. Each part of the task describe what should be added to the report once it has been completed. This can be screenshots, some data, etc.

- A report with a .md extension must be uploaded to the repository, in the src folder.
- All parts of the task should be highlighted in the report as level 2 headers.
- Within one part of the task, everything that is added to the report must be in the form of the list.
- Each screenshot in the report must be briefly captioned (what’s in the screenshot).
- All screenshots must be cropped so that only the relevant part of the screen is shown.

## Part 1. Installation of the OS

`-` Well, let's finally get this Linux installed,'' -- Sebastian moves the laptop closer to you.

`-` Yes, it's about time. I saw a great instruction on *Linuxconfig* to install the version we need.

**== Task ==**

##### Install **Ubuntu 20.04 Server LTS** without GUI. (Use VirtualBox).
- There should be no GUI.
- Check Ubuntu version by running the command \
  `cat /etc/issue`
- Add a screenshot of the command output to the report.

## Part 2. Creating a user

`-` An installed system is a good thing, but what if someone else uses it? I'll teach you how to create a new user.

**== Task ==**

##### Create a user other than the one created during installation. The user must be added to `adm` group.
- Add a screenshot of command call to create user.
- The new user must be in the output of the command: \
  `cat /etc/passwd`
- Add a screenshot of the command output.

## Part 3. Setting up the OS network

`-` In our world, you can't go far without the Internet. However, since we want to train you for the role of a system administrator, I'll show you a little more than just setting up a network.

`-` Before we begin, I suggest reading about network interfaces and DHCP.

**== Task ==**

##### Set the machine name as user-1
##### Set the time zone corresponding to your current location.

##### Output the names of the network interfaces using a console command.
- In the report give an explanation for the presence of the lo interface.
##### Use the console command to get the ip address of the device you are working on from the DHCP server.
- Decode DHCP in the report.
##### Define and display the external ip address of the gateway (ip) and the internal IP address of the gateway, aka default ip address (gw).
##### Set static (manually set, not received from DHCP server) ip, gw, dns settings (use public DNS servers, e.g. 1.1.1.1 or 8.8.8.8).

##### Reboot the virtual machine. Make sure that the static network settings (ip, gw, dns) correspond to those set in the previous point.
- Describe in the report what you have done to complete all seven points (you can do it in text or with screenshots).
- Successfully ping 1.1.1.1 and ya.ru remote hosts and add a screenshot of the output command to the report. There should be "0% packet loss" phrase in command output.

## Part 4. OS Update

`-` You're probably wondering, "Is the system ready now?" It's not ready at all! We haven't updated it to the latest version yet.

**== Task ==**

##### Update the system packages to the latest version
- After updating the system packages, if you enter the update command again, a message should appear saying there are no updates.
- Add a screenshot of this message to the report.

## Part 5. Using the **sudo** command

`-` How often were you told as a child that you forgot to say the "magic" word? One of those "magic" words was "please". Linux has its counterpart – _sudo_. The system won't perform some operations until it hears the "magic" word.

**== Task ==**

##### Allow user created in [Part 2](#part-2-creating-a-user) to execute sudo command.
- In the report explain the *true* purpose of sudo command (don’t write about the fact that this word is "magic" one).
- Change the OS hostname via the user created in [Part 2](#part-2-creating-a-user) (using sudo).
- Add screenshot with changed hostname to the report.

## Part 6. Installing and configuring the time service

`-` Although we have the correct time now, it may not always be that way. To avoid having to set it every time yourself, there are time sync services.

**== Task ==**

##### Set up the automatic time synchronisation service.
- Output the time of the time zone in which you are currently located.
- The output of the following command must contain `NTPSynchronized=yes`: \
  `timedatectl show`
- Add screenshots of the correct time and command output to the report.

## Part 7. Installing and using text editors

`-` I think we're ready to move on to one of the scariest parts. You’re pointing toward the Netherlands on the map of the world hanging on the wall.

`-` Here, Bram Moolenaar has unraveled the mysteries of harmony and inner concentration. \
This is where the first version of VIM was released on 2 November 1991. \
Do you want to learn how to work in VIM?

`-` Yes...

`-` Then I am your master.

`-` Okay...

`-` Just don't cry.

`-` I won’t.

**== Task ==**

##### Install **VIM** text editor (+ any two others if you like **NANO**, **MCEDIT**, **JOE** etc.)

##### Using each of the three selected editors, create a *test_X.txt* file, where X is the name of the editor in which the file is created. Write your nickname in it, close the file and save the changes.
- Add screenshots to the report:
    - Of each editor with the contents of the file before closing.
- Write down in the report what you have done to exit with the changes saved.

##### Using each of the three selected editors, open the file for editing, edit the file by replacing the nickname with the "21 School 21" string, close the file without saving the changes.
- Add screenshots to the report:
    - Of each editor with the contents of the file after editing.
- Write down in the report what you have done to exit without saving the changes.
##### Using each of the three selected editors, edit the file again (similar to the previous point) and then master the functions of searching through the contents of a file (a word) and replacing a word with any other one.
- Add screenshots to the report:
    - Of each editor with word search results.
    - Of each editor with commands entered to replace a word with another.

## Part 8. Installing and basic setup of the **SSHD** service

`-` It's convenient to have access from one computer to another over a network, isn't it? But to make it not only convenient, but also safe, you should use SSH service.

**== Task ==**

##### Install the SSHd service.
##### Add an auto-start of the service whenever the system boots.
##### Reset the SSHd service to port 2022.
##### Show the presence of the sshd process using the ps command. To do this, you need to match the keys to the command.
- Explain in the report the meaning of the command and each key in it.
##### Reboot the system.
- Describe in the report what you have done to complete all five points (you can do this in text or with screenshots).
- The output of the netstat -tan command should contain \
  `tcp 0 0.0.0.0:2022 0.0.0.0:* LISTEN` \
  (if there is no netstat command, it needs to be installed)
- Add a screenshot of the command output to the report.
- Explain the meaning of the -tan keys, the value of each output column, the value 0.0.0.0. in the report.

## Part 9. Installing and using the **top**, **htop** utilities

`-` If I were asked what useful things **top** and **htop** utilities do, I would answer in one word: everything.

**== Task ==**

##### Install and run the top and htop utilities.
- From the output of the top command determine and write in the report:
    - uptime
    - number of authorised users
    - total system load
    - total number of processes
    - cpu load
    - memory load
    - pid of the process with the highest memory usage
    - pid of the process taking the most CPU time
- Add a screenshot of the htop command output to the report:
    - sorted by PID, PERCENT_CPU, PERCENT_MEM, TIME
    - filtered for sshd process
    - with the syslog process found by searching
    - with hostname, clock and uptime output added

## Part 10. Using the **fdisk** utility

`-` Now let's figure out how to get information about your hard disk. Especially for you I've put together a couple of examples of how to use the fdisk utility.

**== Task ==**

##### Run the fdisk -l command.
- In the report write the name of the hard disk, its capacity and number of sectors, and also the swap size.

## Part 11. Using the **df** utility

`-` We got the information about the hard disk, but often it is much more interesting to get information about the disk space, which can be obtained with the df utility.

**== Task ==**

##### Run the df command.
- In the report write for the root partition (/):
    - partition size
    - space used
    - space free
    - percentage used
- Determine and write the measurement unit in the report.

##### Run the df -Th command.
- In the report write for the root partition (/):
    - partition size
    - space used
    - space free
    - percentage used
- Determine and write the file system type for the partition in the report.

## Part 12. Using the **du** utility

`-` df is not the only way to get information about disk space. I'll tell you about another one.

**== Task ==**

##### Run the du command.
##### Output the size of the /home, /var, /var/log folders (in bytes, in human readable format)
##### Output the size of all contents in /var/log (not the total, but each nested element using *)
- Add screenshots with the output of all used commands to the report.

## Part 13. Installing and using the **ncdu** utility

`-` You probably didn’t like much the format in which the du command outputs information. I understand you perfectly. So now we'll take a look at its improved version.

**== Task ==**

##### Install the ncdu utility.
##### Output the size of the /home, /var, /var/log folders.
- The size should be approximately the same as in [Part 12](#part-12-using-the-du-utility).

- Add screenshots of the used commands to the report.

## Part 14. Working with system logs

`-` A system administrator sometimes needs to review events which happened in a system in the recent past. Linux has system logs for that.

**== Task ==**

##### Open for viewing:
##### 1. /var/log/dmesg
##### 2. /var/log/syslog
##### 3. /var/log/auth.log
- Write the last successful login time, user name and login method in the report.
- Restart SSHd service.
- Add a screenshot of the service restart message to the report (search for it in the logs).

## Part 15. Using the **CRON** job scheduler

`-` Phew, we finally got to the last part of my long narrative. I will now show you the program, which, among other things, noticeably simplifies the periodic invocation of other programs.

**== Task ==**

##### Using the job scheduler, run the uptime command in every 2 minutes.
- Find lines in the system logs (at least two within a given time range) about the execution.
- Display a list of current jobs for CRON.
- Add screenshots of the execution lines and the list of current tasks to the report.

##### Remove all tasks from the job scheduler.
- Add a screenshot of the list of current tasks for CRON to the report.


💡 [Tap here](https://forms.yandex.ru/u/6357f435c09c02345cf48f1a/) **to leave your feedback on the project**. Pedago Team really tries to make your educational experience better.
