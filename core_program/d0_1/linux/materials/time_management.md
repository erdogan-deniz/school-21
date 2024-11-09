## Installing and setting the time service
In many distributions of Unix-like operating systems, there is a special time and date synchronisation utility. It is active by default so users do not need to configure or modify it in any way. Sometimes, however, it does become necessary due to various reasons, such as random malfunctions. \
Computers all over the world use NTP (Network Time Protocol) to synchronise their time with a standard reference clock via the Internet using a hierarchy of NTP servers. \
You may need to set up automatic time synchronisation, for example when switching from the default timesyncd utility to the more trusted NTPD protocol. To do this, you should:
- Disable the standard utility
- It is recommended to ensure that the system is updated to the latest version
- Install NTP, which will be activated automatically so no additional commands need to be entered.
