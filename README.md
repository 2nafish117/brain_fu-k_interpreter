<h3>A simple Brain Fu*k interpreter made using cpp.</h3>

<b>Build:</b>
  
  run `make` from the root directory of the project.
  `fuck` binary in `/bin/fuck` from the root directory of project.
  
<b>Usage:</b>

  Run interpreter with `./fuck` with the `fuck` binary in the same directory. (with necessary flags)

  By default requires a file called `brain.fuck` in the same directory as `fuck` to run.

<b>Flags:</b>

  `-f <file>`     specifies a file/file path to interpret.

  `-b <size>`     specifies size of buffer to be used in bytes (currently broken).

  `-e <number>`   specifies max number of errors displayed (in the terminal) if any (default value 10).

  `-p <position>` specifies initial position of pointer (default value 0).
  
  `-n` specifies if I/O should take inputs as integers or charecters (by default uses charecters, mainly a quality of life option).
