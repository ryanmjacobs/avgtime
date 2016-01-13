avgtime
=======

Command Benchmarking Tool
-------------------------

avgtime is a CLI benchmarking tool for commands. Run a command for **n**
iterations and derive the average execution time, among other things.

Build & Install
---------------

```
make
make install
```

Uninstall
---------

```
make uninstall
```

Command Synopsis
----------------

```
Usage: ./avgtime [-n num_trials] [options] <command>
avgtime, Command Benchmarking Tool.

  -h,   --help               Display this help and exit
  -n,   --trials             Number of trials
  -q,   --quiet              Don't display each run
  -s,   --suppress           Suppress command stdout and stderr
  -v,   --verbose            Enable verbose output
        --version            Display version information and exit

Examples:
  ./avgtime -n 100 'echo hi'  Find avg. execution time of the command: 'echo hi'

Report bugs to <ryan.mjacobs@gmail.com>
```

License
-------

MIT License - see LICENSE

Copyright (c) 2016 Ryan Jacobs
