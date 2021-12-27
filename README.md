# shell-killer-rootkit
* A kernel-level shell killer. For having only one shell process having control over the system.

  This kernel module, starts killing(SIGKILL) shell processes(depending on the shell name which can be declared in *headers.h*), except the one that has loaded the module.

Compile and install:
Just cd into the project dir and run the following commands:
```
  $ make
  $ insmod code.ko # Loads the module.
  ```
